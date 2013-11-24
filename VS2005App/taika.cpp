// taika.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "taika.h"
#include "taikaDlg.h"
#include "Props.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaikaApp

BEGIN_MESSAGE_MAP(CTaikaApp, CWinApp)
	//{{AFX_MSG_MAP(CTaikaApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaikaApp construction
CTaikaApp::CTaikaApp()
{
	m_pCImageList = NULL;
	m_sync_raportit = 0;                             // Eri näyttöjen synkronointi
    m_sync_listat = 0;
    m_sync_tyomatkat = 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTaikaApp object
CTaikaApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTaikaApp initialization
BOOL CTaikaApp::InitInstance()
{
    int i;
    CString cs;
    HBITMAP hbm;
    CBitmap cBmA;
    CBitmap cBmD;
    char getpath[MAX_PATH];

    // Winsock - Sähköpostin lähetykselle
    if(!AfxSocketInit())
	{}

    /*WSADATA WsaData;
    DWORD VersionRequested = MAKEWORD(1, 0);
    int Error = WSAStartup(VersionRequested, &WsaData); */

    // Haetaan ohjelman polku ja nimi
    GetModuleFileName(m_hInstance, getpath, MAX_PATH);
    cs = getpath; i = cs.GetLength() - 1;
    while(cs[i] != '\\') i--; cs = cs.Left(i+1);
    m_app_path = cs;

    // Ohjelman nimi
    m_app_title = Props::i().lang("APPNAME");

    // Asetusten polku\nimi
    m_opt_path = m_app_path + OPTIONS_FILENAME;

    // Luodaan oma luokka dialogille: taika_savereport.exe etsii taika.exe:n dialogia luokan nimellä
    // HUOM! Luokan nimi tulee asettaa myös dialogin resurssiin (taika.rc) jotta tämä toimisi.
    //     CLASS "taikadlgclassV2"
    WNDCLASS wc;
    ::GetClassInfo(NULL, MAKEINTRESOURCE(0x8002), &wc);  // Normaalin dialogin "hardwired class name" 0x8002
    wc.lpszClassName = "taikadlgclassV2";
    RegisterClass(&wc);

    // Accelerator keys
    m_hAccelerators = LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ACCKEYS));

	// CImageList
    if((m_pCImageList = new CImageList()))
	{
      m_pCImageList->Create(16, 16, ILC_MASK|ILC_COLOR32, 8, 8);
      m_pCImageList->Add(theApp.LoadIcon(IDI_KELLO));
      m_pCImageList->Add(theApp.LoadIcon(IDI_EURO));
      m_pCImageList->Add(theApp.LoadIcon(IDI_CLIENT));
      m_pCImageList->Add(theApp.LoadIcon(IDI_WORK));
      m_pCImageList->Add(theApp.LoadIcon(IDI_TRAVEL));
      m_pCImageList->Add(theApp.LoadIcon(IDI_CASH));
      hbm = (HBITMAP)LoadImage(theApp.m_hInstance, MAKEINTRESOURCE(IDB_BMPASC),  IMAGE_BITMAP, 16, 16, LR_LOADMAP3DCOLORS|LR_LOADTRANSPARENT);
      cBmA.Attach(hbm);
      hbm = (HBITMAP)LoadImage(theApp.m_hInstance, MAKEINTRESOURCE(IDB_BMPDESC), IMAGE_BITMAP, 16, 16, LR_LOADMAP3DCOLORS|LR_LOADTRANSPARENT);
      cBmD.Attach(hbm);
      m_pCImageList->Add(&cBmA, RGB(0,0,0));
      m_pCImageList->Add(&cBmD, RGB(0,0,0));
	}

	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTaikaDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{}
	else if (nResponse == IDCANCEL)
	{}

	return FALSE;  // Since the dialog has been closed, return FALSE so that we exit the application, rather than start the application's message pump.
}

int CTaikaApp::ExitInstance()
{
    if(m_pCImageList) delete m_pCImageList;          // Tuhoa CImageList

	return 0;
}

BOOL CTaikaApp::ProcessMessageFilter(int code, LPMSG lpMsg) 
{
    if(m_hAccelerators)                    // Käsittele kaasutusnäppäimet jos luotu
	{
      if(::TranslateAccelerator(m_pMainWnd->m_hWnd, m_hAccelerators, lpMsg)) return(TRUE);
	}

	return CWinApp::ProcessMessageFilter(code, lpMsg);
}

BOOL CTaikaApp::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_DELETE)	// poista listasta (työaika, tuote, ...) item, jos lista valittuna
			return ((CTaikaDlg*)m_pMainWnd)->poista();
	}

	return CWinApp::PreTranslateMessage(pMsg);
}