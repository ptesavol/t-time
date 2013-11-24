// DlgLuoUusiTietokanta.cpp : implementation file
//

#include "stdafx.h"
#include "taika.h"
#include "DlgLuoUusiTietokanta.h"
#include "Props.h"
#include "dbsqlite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLuoUusiTietokanta dialog


CDlgLuoUusiTietokanta::CDlgLuoUusiTietokanta(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLuoUusiTietokanta::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLuoUusiTietokanta)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgLuoUusiTietokanta::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLuoUusiTietokanta)
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_STCPATHNAME, m_stcPathName);
	DDX_Control(pDX, IDC_BTNFOLDER, m_btnFolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLuoUusiTietokanta, CDialog)
	//{{AFX_MSG_MAP(CDlgLuoUusiTietokanta)
	ON_BN_CLICKED(IDC_BTNFOLDER, OnBtnfolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLuoUusiTietokanta message handlers

BOOL CDlgLuoUusiTietokanta::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGLUOUUSITIETOKANTA_C1"));
	SetDlgItemText(IDC_STATIC, Props::i().lang("DLGLUOUUSITIETOKANTA_C2"));
	SetDlgItemText(IDOK, Props::i().lang("DLGLUOUUSITIETOKANTA_C3"));
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGLUOUUSITIETOKANTA_C4"));

    m_cbm.LoadBitmap(IDB_FOLDER);                                    // Folder-bitmap
    m_btnFolder.SetBitmap(m_cbm);

    m_filename = "";
    m_path = "";
	
    return TRUE;
}

void CDlgLuoUusiTietokanta::OnBtnfolder() 
{
    DWORD e;
    CString file;
    OPENFILENAME ofn;
	char buf[128] = {0};
    char *lpstrFile = NULL, strFileTitle[MAX_PATH];

    try
	{
      file = Props::i().get(OPTIONS_DB_PATH).c_str();

      if(!(lpstrFile = new char[MAX_PATH * 100])) throw(0);          // Tarpeeksi tilaa useammalle tiedostonimelle

      ofn.lStructSize = sizeof(OPENFILENAME);
      ofn.hwndOwner = this->GetSafeHwnd();
      ofn.lpstrFilter = Props::i().langs("DLGLUOUUSITIETOKANTA_1", buf, 128);
      ofn.lpstrTitle = Props::i().lang("DLGLUOUUSITIETOKANTA_2");
      ofn.lpstrInitialDir = file;
      ofn.lpstrCustomFilter = NULL; ofn.nFilterIndex = 1;
      *lpstrFile = NULL; ofn.lpstrFile = lpstrFile; ofn.nMaxFile = MAX_PATH * 100;
      ofn.lpstrFileTitle = strFileTitle; ofn.nMaxFileTitle = MAX_PATH;
      ofn.Flags = OFN_EXPLORER|OFN_HIDEREADONLY|OFN_LONGNAMES|OFN_PATHMUSTEXIST/*|OFN_OVERWRITEPROMPT*/;
      ofn.lpstrDefExt = ".db"; ofn.lCustData = NULL;
      if(!GetSaveFileName(&ofn)) throw(0);
 
      m_path = ofn.lpstrFile; m_path = m_path.Left(ofn.nFileOffset);
      m_filename = (ofn.lpstrFile + ofn.nFileOffset);

      m_btnOK.EnableWindow(TRUE);
      m_stcPathName.SetWindowText(ofn.lpstrFile);
	}
    catch(...)
	{
      if((e = CommDlgExtendedError()) != ERROR_SUCCESS)
      {
        file.Format(Props::i().lang("DLGLUOUUSITIETOKANTA_3"), e);
        MessageBox(file, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }

      m_btnOK.EnableWindow(FALSE);
      m_stcPathName.SetWindowText("");
	}

    if(lpstrFile) delete [] lpstrFile;               // Vapauta muisti	
}

void CDlgLuoUusiTietokanta::OnOK() 
{
    int err;
    DbSqlite db;
    CString path;

    if(!m_btnOK.IsWindowEnabled()) return;

    try
	{
      m_btnFolder.EnableWindow(FALSE);
      m_btnOK.EnableWindow(FALSE);
      m_btnCancel.EnableWindow(FALSE);
      m_stcPathName.SetWindowText(Props::i().lang("DLGLUOUUSITIETOKANTA_4"));

      path = m_path + m_filename;
      if((err = db.luoTaulut(&path, true)) != RETURN_OK) throw(0);

      Props::i().set(OPTIONS_DB_PATH, (LPCSTR)path);
      Props::i().set(OPTIONS_DB_NAME, (LPCSTR)m_filename);

	  Props::e().m_db_path = path;

      EndDialog(IDOK);
	}
    catch(int err)
	{
      CString errstr;
      errstr.Format(Props::i().lang("DLGLUOUUSITIETOKANTA_5"), err, path);
      MessageBox(errstr, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      m_stcPathName.SetWindowText(m_path + m_filename);
      m_btnFolder.EnableWindow(TRUE);
      m_btnOK.EnableWindow(TRUE);
      m_btnCancel.EnableWindow(TRUE);
	}
}

void CDlgLuoUusiTietokanta::OnCancel() 
{	
    EndDialog(IDCANCEL);
}