// DlgVarmuuskopioi.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "DlgVarmuuskopioi.h"
#include "Props.h"
#include "Parse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgVarmuuskopioi dialog
DlgVarmuuskopioi::DlgVarmuuskopioi(CWnd* pParent /*=NULL*/)
	: CDialog(DlgVarmuuskopioi::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgVarmuuskopioi)
	//}}AFX_DATA_INIT
}

void DlgVarmuuskopioi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgVarmuuskopioi)
	DDX_Control(pDX, IDC_STCVKOPIOITAVA, m_stcVKopioitava);
	DDX_Control(pDX, IDC_STCINFO, m_stcInfo);
	DDX_Control(pDX, IDC_BTNVARMUUSKOPIOI, m_btnVarmuuskopioi);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_CHKMATKA, m_chkMatka);
	DDX_Control(pDX, IDC_EDTPATH, m_edtPath);
	DDX_Control(pDX, IDC_EDTFILENAME, m_edtFileName);
	DDX_Control(pDX, IDC_CHKPOISTA, m_chkPoista);
	DDX_Control(pDX, IDC_BTNPOLKU, m_btnPolku);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgVarmuuskopioi, CDialog)
	//{{AFX_MSG_MAP(DlgVarmuuskopioi)
	ON_BN_CLICKED(IDC_BTNVARMUUSKOPIOI, OnBtnvarmuuskopioi)
	ON_BN_CLICKED(IDC_BTNPOLKU, OnBtnpolku)
	ON_BN_CLICKED(IDC_RADKOPIOI1, OnRadkopioi)
	ON_EN_CHANGE(IDC_EDTFILENAME, OnChangeEdtfilename)
	ON_EN_CHANGE(IDC_EDTPATH, OnChangeEdtpath)
	ON_BN_CLICKED(IDC_CHKMATKA, OnChkmatka)
	ON_BN_CLICKED(IDC_RADKOPIOI2, OnRadkopioi)
	ON_BN_CLICKED(IDC_RADKOPIOI3, OnRadkopioi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgVarmuuskopioi message handlers

BOOL DlgVarmuuskopioi::OnInitDialog() 
{
    COleDateTime odt;

	CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGVARMUUSKOPIOI_C1"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGVARMUUSKOPIOI_C2"));
	SetDlgItemText(IDC_STATIC2, Props::i().lang("DLGVARMUUSKOPIOI_C3"));
	SetDlgItemText(IDC_STATIC3, Props::i().lang("DLGVARMUUSKOPIOI_C4"));
	SetDlgItemText(IDC_STATIC4, Props::i().lang("DLGVARMUUSKOPIOI_C5"));
	SetDlgItemText(IDC_STATIC5, Props::i().lang("DLGVARMUUSKOPIOI_C6"));
	SetDlgItemText(IDC_RADKOPIOI1, Props::i().lang("DLGVARMUUSKOPIOI_C7"));
	SetDlgItemText(IDC_RADKOPIOI2, Props::i().lang("DLGVARMUUSKOPIOI_C8"));
	SetDlgItemText(IDC_RADKOPIOI3, Props::i().lang("DLGVARMUUSKOPIOI_C9"));
	SetDlgItemText(IDC_CHKMATKA, Props::i().lang("DLGVARMUUSKOPIOI_C10"));
	SetDlgItemText(IDC_CHKPOISTA, Props::i().lang("DLGVARMUUSKOPIOI_C11"));
	SetDlgItemText(IDC_BTNVARMUUSKOPIOI, Props::i().lang("DLGVARMUUSKOPIOI_C12"));
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGVARMUUSKOPIOI_C13"));

    m_bVarmuuskopioitu = FALSE;

    m_cbm.LoadBitmap(IDB_FOLDER);                    // Folder-bitmap
    m_btnPolku.SetBitmap(m_cbm);
                                                     // Varmuuskopiointitila
    CheckRadioButton(IDC_RADKOPIOI1, IDC_RADKOPIOI3, IDC_RADKOPIOI1);
    m_tila = C_TRUE;

    m_chkMatka.SetCheck(1);                          // Varmuuskopioi TravelUnit
    m_matka = TRUE;

    m_stcVKopioitava.SetWindowText(Props::e().m_db_path);// Varmuuskopioitava tietokanta

    m_path = Props::i().get(OPTIONS_DB_BACKUP_PATH).c_str();
    m_edtPath.SetWindowText(m_path);

    odt = odt.GetCurrentTime();
    m_filename.Format("vk_%02d%02d%d_%s", odt.GetDay(), odt.GetMonth(), odt.GetYear(), DEFAULT_DB_NAME);
    m_edtFileName.SetWindowText(m_filename);

    // V‰rillinen tausta info-tekstille. Oletuksena taustan v‰rinen.
    m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), "");

	return TRUE;
}

void DlgVarmuuskopioi::OnBtnpolku() 
{
    CString cs;
    BROWSEINFO bri;
    TCHAR szDir[MAX_PATH * 2];
    LPMALLOC pMalloc = NULL;
    LPITEMIDLIST pidl = NULL;

    try
	{
      if(!SUCCEEDED(SHGetMalloc(&pMalloc))) throw(ERR_IMALLOC);      // tarvitaan LPITEMIDLIST:n vapauttamisessa

      bri.hwndOwner = this->GetSafeHwnd();                           // Laskutusohjelman polku (antaa polun LPITEMIDLIST-struktuurina)
      bri.pidlRoot = NULL; 
      bri.pszDisplayName = szDir; 
      bri.lpszTitle = Props::i().lang("DLGVARMUUSKOPIOI_1");
      bri.ulFlags = BIF_RETURNONLYFSDIRS|BIF_STATUSTEXT;
      bri.lpfn = BrowseCallbackProc_SL;
      bri.lParam = (LPARAM)&m_path;
      bri.iImage = 0; 
      if(!(pidl = SHBrowseForFolder(&bri))) throw(RETURN_NOACTION);

      if(!SHGetPathFromIDList(pidl, szDir)) throw(ERR_SHGET);        // Muunnetaan polku mjonoksi, polku talteen
      m_path.Format("%s\\", szDir);
      m_edtPath.SetWindowText(m_path);

      Props::i().set(OPTIONS_DB_BACKUP_PATH, (LPCSTR)m_path);

      pMalloc->Free(pidl);                                           // Vapautetaan muisti ja rajapinta
      pMalloc->Release();
	}
    catch(int err)
	{
      if(pMalloc) {                                                  // Vapautetaan muisti ja rajapinta
      if(pidl) pMalloc->Free(pidl);
      pMalloc->Release(); }

      if(err == ERR_IMALLOC) cs = Props::i().lang("DLGVARMUUSKOPIOI_2");
      else if(err == ERR_SHGET) cs = Props::i().lang("DLGVARMUUSKOPIOI_3");
      else if(err == GEN_RESET) cs = "";
      if(cs != "") MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}
}

void DlgVarmuuskopioi::OnRadkopioi() 
{
    int s = GetCheckedRadioButton(IDC_RADKOPIOI1, IDC_RADKOPIOI3);
    if(s == IDC_RADKOPIOI1) m_tila = C_TRUE;
    else if(s == IDC_RADKOPIOI2) m_tila = C_FALSE;
    else if(s == IDC_RADKOPIOI3) m_tila = C_ALL;
}

void DlgVarmuuskopioi::OnChangeEdtfilename() 
{ m_edtFileName.GetWindowText(m_filename); }

void DlgVarmuuskopioi::OnChangeEdtpath() 
{ m_edtPath.GetWindowText(m_path); }

void DlgVarmuuskopioi::OnChkmatka() 
{
    if(m_chkMatka.GetCheck() == 0) m_matka = FALSE;
    else m_matka = TRUE;
}

void DlgVarmuuskopioi::OnBtnvarmuuskopioi() 
{
    int e;
    DbSqlite db;
    Parse parse;
    HANDLE hfile = NULL;
    CString cs, filepath, tila;

    m_edtFileName.EnableWindow(FALSE);
    m_edtPath.EnableWindow(FALSE);
    m_btnCancel.EnableWindow(FALSE);
    m_btnVarmuuskopioi.EnableWindow(FALSE);
    m_btnPolku.EnableWindow(FALSE);
    m_chkMatka.EnableWindow(FALSE);
    m_chkPoista.EnableWindow(FALSE);

	try
	{
      filepath = m_path + m_filename;                                // 0. Kohteen tiedostopolun/nimen tarkistus
      if(parse.fileExists(filepath, Props::e().m_db_path, OPEN_EXISTING) == IDNO) throw(ERR_BACKUP_1);

      m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGVARMUUSKOPIOI_4")); // 1. Kopioi tietokanta (tiedostosta->tiedostoon)
      if(!CopyFile(Props::e().m_db_path, filepath, FALSE)) throw(ERR_BACKUP_0);

      if(m_tila != C_ALL)                                            // 2. Poistetaan kohteesta tiedot joita ei haluta tallettaa
	  {
        m_stcInfo.SetWindowText(Props::i().lang("DLGVARMUUSKOPIOI_5"));
        if(db.poistaYleinen("WorkUnit", "Charged", m_tila == C_TRUE ? C_FALSE : C_TRUE, TRUE, filepath) != RETURN_OK) throw(ERR_BACKUP_1);
	  }

      if(m_matka == FALSE)                                           // 3. Poistetaan TravelUnit-rivit, jos niit‰ ei haluta varmuuskopioida
	  {
        m_stcInfo.SetWindowText(Props::i().lang("DLGVARMUUSKOPIOI_6"));
        if(db.poistaYleinen("TravelUnit", "", "", TRUE, filepath) != RETURN_OK) throw(ERR_BACKUP_1);
	  }

      if(m_chkPoista.GetCheck() == 1)                                // 4. Poistetaan l‰hteest‰ tiedot, jotka kopioitiin kohteeseen
	  {
        m_stcInfo.SetWindowText(Props::i().lang("DLGVARMUUSKOPIOI_7"));
        if(db.poistaYleinen("WorkUnit", m_tila == C_ALL ? "" : "Charged", m_tila, TRUE, Props::e().m_db_path) != RETURN_OK) throw(ERR_BACKUP_1);

        if(m_matka)
          if(db.poistaYleinen("TravelUnit", "", "", TRUE, Props::e().m_db_path) != RETURN_OK) throw(ERR_BACKUP_1);
	  }
                                                                     // 5. Tiivistet‰‰n kohdetietokanta
      m_stcInfo.SetWindowText(Props::i().lang("DLGVARMUUSKOPIOI_8"));
      if(db.vacuum(Props::e().m_db_path) != RETURN_OK) throw(ERR_BACKUP_1);
      m_stcInfo.SetWindowText(Props::i().lang("DLGVARMUUSKOPIOI_9"));
      if(db.vacuum(filepath) != RETURN_OK) throw(ERR_BACKUP_1);

      m_stcInfo.coloredInfo(LIGHTGREEN, Props::i().lang("DLGVARMUUSKOPIOI_10"));
	}
    catch(int err)
	{
      LPVOID lpMsgBuf;
      if((e = GetLastError()) != ERROR_SUCCESS && err == ERR_BACKUP_0)
	  {
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, e, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
        cs.Format(Props::i().lang("DLGVARMUUSKOPIOI_11"), e, (LPCSTR)lpMsgBuf, filepath);
        LocalFree(lpMsgBuf);

        MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		m_stcInfo.coloredInfo(LIGHTRED, Props::i().lang("DLGVARMUUSKOPIOI_12"));
	  }

      DeleteFile(filepath);                          // Poista vailinainen tiedosto
	}

    m_edtFileName.EnableWindow(TRUE);
    m_edtPath.EnableWindow(TRUE);
    m_btnCancel.EnableWindow(TRUE);
    m_btnVarmuuskopioi.EnableWindow(TRUE);
    m_btnPolku.EnableWindow(TRUE);
    m_chkMatka.EnableWindow(TRUE);
    m_chkPoista.EnableWindow(TRUE);

    m_bVarmuuskopioitu = TRUE;
}

int CALLBACK BrowseCallbackProc_SL(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData)
{
    if(uMsg == BFFM_INITIALIZED)
	{
      CString *cs = (CString*)pData;
      SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)(LPCSTR)*cs);
	  SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)(LPCSTR)*cs);
	}
    else if(uMsg == BFFM_SELCHANGED)
	{
      TCHAR szDir[MAX_PATH];
      if(SHGetPathFromIDList((LPITEMIDLIST)lp ,szDir))
	    SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
	}

    return 0;
}

void DlgVarmuuskopioi::OnCancel() 
{
    if(m_bVarmuuskopioitu) EndDialog(IDOK);
    else EndDialog(IDCANCEL);
	
	//CDialog::OnCancel();
}
