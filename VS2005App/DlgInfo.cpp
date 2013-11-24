// DlgInfo.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "DlgInfo.h"
#include "Props.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgInfo dialog
DlgInfo::DlgInfo(CWnd* pParent /*=NULL*/)
	: CDialog(DlgInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgInfo)
	//}}AFX_DATA_INIT
}


void DlgInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgInfo)
	DDX_Control(pDX, IDC_LSTLISTA, m_lstLista);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgInfo, CDialog)
	//{{AFX_MSG_MAP(DlgInfo)
    ON_WM_MOVING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgInfo message handlers

BOOL DlgInfo::OnInitDialog() 
{
    int i, s, ins, uni, uns, wti, wts;
    CRect cr;
    RECT rect;
    float cnv;
    BOOL bVal;
    CString cs;
    DbSqlite db;
    vector <CString> vect;
    vector <CString> un_vect;
    pair<CString,CString> pari;
    vector <ItemData*> info_vect;
    vector <pair<CString,CString> > wt_vect;

	CDialog::OnInitDialog();
	
    // Merkitään In Place Edit -ikkunaksi
    ::SetWindowLong(this->GetSafeHwnd(), GWL_USERDATA, INPLACEEDIT);

    // Otsikko
    this->SetWindowText(m_caption);

	ListView_SetExtendedListViewStyleEx(m_lstLista.GetSafeHwnd(),  // Valitsee koko rivin kerralla
		    LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
    m_lstLista.GetClientRect(&cr);                                // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
    m_lstLista.InsertColumn(0, Props::i().lang("DLGINFO_1"), LVCFMT_LEFT, cr.right * 0.48, -1);
    m_lstLista.InsertColumn(1, Props::i().lang("DLGINFO_2"), LVCFMT_LEFT, cr.right * 0.45, -1);

    this->GetWindowRect(&rect);                      // Dialogin koko
    m_dlgWidth = rect.right - rect.left;
    m_dlgHeight = rect.bottom - rect.top;
    this->SetWindowPos(NULL, m_dlgXPos - m_dlgWidth, m_dlgYPos - m_dlgHeight, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

    ins = m_pCListCtrl->GetItemCount();              // Haetaan vektoriin ItemData:t
    if(m_mode == MODE_VALITUT)
	{
      for(i=0; i<ins; i++)
	  {
        if(m_pCListCtrl->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		  info_vect.push_back((ItemData*)m_pCListCtrl->GetItemData(i));
	  }
	}
    else if(m_mode == MODE_KAIKKINAYTETYT)
	{
      for(i=0; i<ins; i++)
	    info_vect.push_back((ItemData*)m_pCListCtrl->GetItemData(i));
	}

    try
	{
      if((ins = info_vect.size()) == 0) throw(ERR_INFO_0);    // Pois jos ei näytettävää

      // Hae kaikki yksiköt
      if((vect = db.haeTaulusta("Units", "*", 1, "", 0)).size() == 0) throw(ERR_INFO_1);
      for(i=0, uns=vect.size(); i<uns; i++) un_vect.push_back(vect[i]);

      // Hae kaikki työtyypit tai tuotteet
      if((s = (vect = db.haeTaulusta("WorkType", "id, Name", 2, "Name", 0)).size()) == 0) throw(ERR_INFO_1);
      for(i=0; i<s; i+=2)
	  {
        pari.first = vect[i];
        pari.second = vect[i + 1];
        wt_vect.push_back(pari);
	  }
      wts = wt_vect.size();

      for(uni=0; uni<uns; uni++)                     // Käydään läpi yksiköittäin
	  {
        for(wti=0; wti<wts; wti++)                       // tietyn työtyypin tai tuotteen tapahtumat tietylle yksikölle
		{
          cnv = 0.0f;
          bVal = FALSE;
          for(i=0; i<ins; i++)                           // annetuista ItemDatatoista
		  {
            if(info_vect[i]->WorkType_id != wt_vect[wti].first) continue;    // väärä työtyyppiid/tuoteid -> seuraava
            if(info_vect[i]->Unit != un_vect[uni]) continue;                 // väärä yksikkö -> seuraava

            if(un_vect[uni] == _UNIT_MIN_ &&                                 // käyntikerrat (vain työajoille)
               info_vect[i]->Type == ID_WORKUNIT &&
               m_time_mode == TIME_CALLS) { cnv += 1.0f; bVal = TRUE; }
            else { cnv += atof(info_vect[i]->UnitValue); bVal = TRUE; }      // muuten aina summataan yhteen
		  }

          if(bVal)                             // vain jos jotain näytettävää
		  {
            if(un_vect[uni] == _UNIT_MIN_ && m_time_mode == TIME_MINUTES) cs.Format("%.0f %s", cnv, _UNIT_MIN_);
            else if(un_vect[uni] == _UNIT_MIN_ && m_time_mode == TIME_HOURS) cs.Format("%.2f %s", cnv / 60.0f, _UNIT_HOUR_);
            else if(un_vect[uni] == _UNIT_MIN_ && m_time_mode == TIME_CALLS) cs.Format("%.0f %s", cnv, cnv == 1.0f ? Props::i().lang("DLGINFO_3") : Props::i().lang("DLGINFO_4"));
            else cs.Format("%.2f %s", cnv, un_vect[uni]);

            i = m_lstLista.GetItemCount();                           // Työtyyppi
            s = m_lstLista.InsertItem(LVIF_TEXT, i, wt_vect[wti].second, 0, 0, 0, 0);
            m_lstLista.SetItem(s, 1, LVIF_TEXT, cs, 0, 0, 0, 0); // Yksikköä
		  }
		}
	  }
	}
    catch(int err)
	{
      if(err > ERR_INFO_0) MessageBox(Props::i().lang("DLGINFO_5"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      EndDialog(IDCANCEL);
	}

    return TRUE;
}

void DlgInfo::OnCancel()
{
	CDialog::OnCancel();
}

BOOL DlgInfo::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN)                  // Napataan Enter, Escape ja Tab
	{
      if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_TAB || pMsg->wParam == 0x58)
        this->OnCancel();
	}

    return CDialog::PreTranslateMessage(pMsg);
}

void DlgInfo::OnMoving(UINT nSide, LPRECT lpRect)
{
    lpRect->top = m_dlgYPos - m_dlgHeight;
    lpRect->left = m_dlgXPos - m_dlgWidth;
    lpRect->bottom = lpRect->top + m_dlgHeight;
    lpRect->right = lpRect->left + m_dlgWidth;
}