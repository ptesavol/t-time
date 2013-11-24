// DlgParseInfo.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "DlgParseInfo.h"
#include "Parse.h"
#include "Props.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgParseInfo dialog


DlgParseInfo::DlgParseInfo(CWnd* pParent /*=NULL*/)
	: CDialog(DlgParseInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgParseInfo)
	//}}AFX_DATA_INIT
}

void DlgParseInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgParseInfo)
	DDX_Control(pDX, IDC_LSTTIEDOSTOT, m_lstTiedostot);
	DDX_Control(pDX, IDC_STCEDISTYS, m_stcEdistys);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_BTNLISAA, m_btnLisaa);
	DDX_Control(pDX, IDC_STCINFO, m_stcInfo);
	DDX_Control(pDX, IDC_CHKPARSE, m_chkParse);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgParseInfo, CDialog)
	//{{AFX_MSG_MAP(DlgParseInfo)
	ON_BN_CLICKED(IDC_CHKPARSE, OnChkparse)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTNLISAA, OnBtnlisaa)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgParseInfo message handlers
BOOL DlgParseInfo::OnInitDialog() 
{
    CRect cr;
    int t, sel;
    char *lpStr;
    CString find, path;

    CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGPARSEINFO_C1"));
	m_chkParse.SetWindowText(Props::i().lang("DLGPARSEINFO_C2"));
	m_btnLisaa.SetWindowText(Props::i().lang("DLGPARSEINFO_C3"));
	m_btnOK.SetWindowText(Props::i().lang("DLGPARSEINFO_C4"));

	ListView_SetExtendedListViewStyleEx(m_lstTiedostot.GetSafeHwnd(),  // Valitsee koko rivin kerralla ja näytä ruudukko
		    LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    m_lstTiedostot.GetClientRect(&cr);                                // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
    m_lstTiedostot.InsertColumn(0, Props::i().lang("DLGPARSEINFO_1"), LVCFMT_LEFT, cr.right * 0.40, -1);
    m_lstTiedostot.InsertColumn(1, Props::i().lang("DLGPARSEINFO_2"), LVCFMT_LEFT, cr.right * 0.599, -1);

	m_pCWinThread = NULL;                            // Nollataan säikeen osoitin

    find = Props::i().get(OPTIONS_AUTOPARSE).c_str();     // Automaattinen parsinta päällä/pois?
    if(find == "TRUE") m_chkParse.SetCheck(TRUE);

    if(m_tila == PARSE_SAAPUNEET)
	{
      m_stcInfo.SetWindowText(Props::i().lang("DLGPARSEINFO_3"));

      AddFiles();

      m_como = MOVE_FILE;                            // saapuneet viedään aina raportit kansioon
      if(m_chkParse.GetCheck() == 1)                 // Parsitaan automaattisesti
	  {
        m_btnLisaa.EnableWindow(FALSE);
        m_btnOK.EnableWindow(FALSE);
        OnBtnlisaa();
	  }
	}
    else if(m_tila == PARSE_FILES)
	{
      lpStr = (char*)(m_lpcstr + m_kaikki - 1);
      if(lpStr[0] == 0)                              // Multiple files
	  {
        m_path.Format("%s\\", m_lpcstr);               // Polku valittujen tiedostojen kansiion

        lpStr = (char*)(m_lpcstr + m_kaikki);
        while(*lpStr != NULL)
		{
          t = m_lstTiedostot.GetItemCount();
          sel = m_lstTiedostot.InsertItem(LVIF_TEXT, t, lpStr, 0, 0, 0, 0);
          m_lstTiedostot.SetItem(sel, 1, LVIF_TEXT, Props::i().lang("DLGPARSEINFO_4"), 0, 0, 0, 0);
          m_lstTiedostot.SetItemData(sel, FALSE);

          lpStr = (char*)(lpStr + strlen(lpStr) + 1);    // seuraava tiedosto
		}

        m_stcInfo.SetWindowText(Props::i().lang("DLGPARSEINFO_5"));
	  }
      else                                           // Single File
	  {
        find = m_path;                                   // tiedostonimi talteen
        m_path = m_lpcstr;                               // : polku muistiin
        m_path.Replace(find, "");                        // : poista polusta tiedostonimi

        t = m_lstTiedostot.GetItemCount();
        sel = m_lstTiedostot.InsertItem(LVIF_TEXT, t, find, 0, 0, 0, 0);
        m_lstTiedostot.SetItem(sel, 1, LVIF_TEXT, Props::i().lang("DLGPARSEINFO_6"), 0, 0, 0, 0);
        m_lstTiedostot.SetItemData(sel, FALSE);

        m_stcInfo.SetWindowText(Props::i().lang("DLGPARSEINFO_5"));
	  }

      m_como = COPY_FILE;                            // Aukaistut tiedostot kopioidana raportit kansioon
      m_chkParse.EnableWindow(FALSE);
	}

    else if(m_tila == PARSE_ADD_FILE)                // Ohjelma on käynnissä ja taika_savereport.exe lähettää tiedoston saapuneet-kansioon
	{
      m_stcInfo.SetWindowText(Props::i().lang("DLGPARSEINFO_3"));

      AddFiles();

      m_como = MOVE_FILE;
      m_chkParse.EnableWindow(FALSE);
	}

    return TRUE;
}

void DlgParseInfo::OnChkparse() 
{
    CString cs;

    if(m_chkParse.GetCheck() == 0) cs = "FALSE";
    else cs = "TRUE";

    Props::i().set(OPTIONS_AUTOPARSE, (LPCSTR)cs);   // Automaattinen parsinta päällä/pois (talleta asetus)
}

void DlgParseInfo::OnDestroy() 
{
    DWORD dwExitCode = STILL_ACTIVE;

	CDialog::OnDestroy();

    if(m_pCWinThread)
	{
      while(dwExitCode == STILL_ACTIVE)              // Odota, että säie lopettelee itsensä
        GetExitCodeThread(m_pCWinThread->m_hThread, &dwExitCode);
      delete m_pCWinThread;                          // Destroy thread
	}
}

BOOL DlgParseInfo::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN)  // Estetään RETURNIN ja ESCAPEN painaminen dialogissa (dialogi ei sulkeudu vahingossa)
	{
      if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
        return TRUE;
	}

    return CDialog::PreTranslateMessage(pMsg);
}

void DlgParseInfo::OnBtnlisaa() 
{
    if(!(m_pCWinThread = AfxBeginThread((AFX_THREADPROC)ThreadFunction, (LPVOID)this, 0, 0, 0, NULL)))
      m_stcInfo.SetWindowText(Props::i().lang("DLGPARSEINFO_7"));
    else
	{
      m_pCWinThread->m_bAutoDelete = FALSE;       // Self-inflicted thread deletion :)

      m_btnOK.EnableWindow(FALSE);
      m_btnLisaa.EnableWindow(FALSE);
	}
}

void DlgParseInfo::edistyminen(int tila)
{
    CString cs;
    CString anim[8] = { "-", " -", "  -", "   -", "    -", "   -", "  -", " -" };

    m_kaikki++;
    if(tila == RETURN_OK) m_lisatty++;
    else if(tila == RETURN_EXISTS) m_samoja++;
    else if(tila == R_NO) m_ohitettu++;
    else m_virhe++;

    cs.Format("%d %s", m_kaikki, anim[m_kaikki % 8]);
    m_stcEdistys.SetWindowText(cs);
}

/////////////////////////////////////////////////////////////////////////////
// Parsintasäie
UINT ThreadFunction(LPVOID pParam)
{
    //MSG msg;
    int i, c;
    Parse parse;
    BOOL ok = TRUE, b;
    CString cs, file, ext; 
    DlgParseInfo *pdlg = (DlgParseInfo*)pParam;
    CListCtrl *plc = &pdlg->m_lstTiedostot;
    CString path = pdlg->m_path;

    //PeekMessage(&msg, NULL, MSG_THREADEXIT, MSG_THREADEXIT, PM_REMOVE);  // Alustetaan viestijärjestelmä

    c = plc->GetItemCount();
    for(i=0; i<c; i++)
	{
      plc->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);            // Käsiteltävä valittuna ja näkyvissä
      plc->EnsureVisible(i, FALSE);
      plc->SetFocus();

      if(plc->GetItemData(i) == FALSE)             // Tiedostoa ei vielä käsitelty
	  {
        file = plc->GetItemText(i, 0);               // otetaan tiedostonimi ja sen pääte
        ext = file.Right(3); ext.MakeLower();
                                                     // näytetään infoa parsinnan edistymisestä
        cs.Format(Props::i().lang("DLGPARSEINFO_8"), i + 1, c, file); 
        pdlg->m_stcInfo.SetWindowText(cs);
        plc->SetItem(i, 1, LVIF_TEXT, Props::i().lang("DLGPARSEINFO_9"), 0, 0, 0, 0);

        pdlg->m_kaikki = 0;                          // nollataan käsiteltyjen/onnistuneiden määrätät
        pdlg->m_lisatty = 0;
        pdlg->m_samoja = 0;
        pdlg->m_ohitettu = 0;
        pdlg->m_virhe = 0;
        pdlg->m_virhe_str = "";

        if(ext == TTI_EXT)                           // parsitaan tiedosto
          b = parse.parseTTI(path, file, pdlg->m_como, pdlg);
        else if(ext == TTA_EXT)
          b = parse.parseTTA(path, file, pdlg->m_como, pdlg);

        ok = min(b, ok);                             // säilytetään FALSE arvoa, jos se on asettunut joskus siihen (yleisvirhe)
        if(b && pdlg->m_virhe == 0)                  // käsittely onnistui
		{
          plc->SetItemData(i, TRUE);                     // merkitse käsitellyksi
          cs.Format(Props::i().lang("DLGPARSEINFO_10"), pdlg->m_kaikki, pdlg->m_lisatty, pdlg->m_samoja, pdlg->m_virhe, pdlg->m_ohitettu);
          plc->SetItem(i, 1, LVIF_TEXT, cs, 0, 0, 0, 0);
		}
        else
		{
          cs.Format(Props::i().lang("DLGPARSEINFO_11"), pdlg->m_virhe_str, pdlg->m_kaikki, pdlg->m_lisatty, pdlg->m_samoja, pdlg->m_virhe);
          plc->SetItem(i, 1, LVIF_TEXT, cs, 0, 0, 0, 0);
		}

        pdlg->m_stcEdistys.SetWindowText("");        // 
	  }

      //if(PeekMessage(&msg, NULL, MSG_THREADEXIT, MSG_THREADEXIT/*yläraja*/, PM_REMOVE))    // peruuta
	  //  if(msg.message == MSG_THREADEXIT) break;
	}

    if(ok)                                           // Tiedotojen käsittelyn kokonaistilanne
	{
      pdlg->m_stcInfo.SetWindowText(Props::i().lang("DLGPARSEINFO_12"));
      pdlg->m_btnLisaa.EnableWindow(FALSE);
	}
    else
	{
      pdlg->m_stcInfo.SetWindowText(Props::i().lang("DLGPARSEINFO_13"));
      pdlg->m_btnLisaa.EnableWindow(TRUE);
	}

    pdlg->m_btnOK.EnableWindow(TRUE);

    return 0;
}

void DlgParseInfo::AddFiles()
{
    long hFile;
    int t, sel;
    CString find;
    __int32 fe = 0;
    struct _finddata_t c_file;

    m_lstTiedostot.DeleteAllItems();

    m_path = Props::e().m_app_path + Props::i().lang("DLGPARSEINFO_14");	// m_path-osoittaa ...\saapuneet kansioon
AfxMessageBox(m_path);
    find = m_path + "*.*";													// Kaikki nimet listaan nähtäväksi
    hFile = _findfirst((LPCTSTR)find, &c_file);
    while(fe != -1)
	{
      if(!(c_file.attrib & _A_SUBDIR))
	  {
        t = m_lstTiedostot.GetItemCount();           // Tiedostonimi
        sel = m_lstTiedostot.InsertItem(LVIF_TEXT, t, c_file.name, 0, 0, 0, 0);
        m_lstTiedostot.SetItem(sel, 1, LVIF_TEXT, Props::i().lang("DLGPARSEINFO_6"), 0, 0, 0, 0); // Käsittelemätön
        m_lstTiedostot.SetItemData(sel, FALSE);      // itemdataksi tila : käsittelemätön
	  }
      fe = _findnext(hFile, &c_file);
	}
}
