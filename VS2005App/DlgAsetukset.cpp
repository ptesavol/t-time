// DlgAsetukset.cpp : implementation file
//

#include "stdafx.h"
#include "taika.h"
#include "DlgAsetukset.h"
#include "Props.h"
#include "taikaDlg.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAsetukset dialog


CDlgAsetukset::CDlgAsetukset(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAsetukset::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAsetukset)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAsetukset::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAsetukset)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_STCLASKOHJ, m_stcLaskOhj);
	DDX_Control(pDX, IDC_CMBLASKYRITYS, m_cmbLaskYritys);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAsetukset, CDialog)
	//{{AFX_MSG_MAP(CDlgAsetukset)
	ON_BN_CLICKED(IDC_RADLASKOHJ1, OnRadlaskohj)
	ON_CBN_SELCHANGE(IDC_CMBLASKYRITYS, OnSelchangeCmblaskyritys)
	ON_BN_CLICKED(IDC_RADLASKOHJ2, OnRadlaskohj)
	ON_BN_CLICKED(IDC_RADLASKOHJ3, OnRadlaskohj)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAsetukset message handlers
BOOL CDlgAsetukset::OnInitDialog() 
{
	CDialog::OnInitDialog();

    int i;

    CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGASETUKSET_C1"));
	SetDlgItemText(IDC_STATIC, Props::i().lang("DLGASETUKSET_C2"));
	SetDlgItemText(IDC_RADLASKOHJ1, Props::i().lang("DLGASETUKSET_C3"));
	SetDlgItemText(IDC_RADLASKOHJ2, Props::i().lang("DLGASETUKSET_C4"));
	SetDlgItemText(IDC_RADLASKOHJ3, Props::i().lang("DLGASETUKSET_C5"));
	SetDlgItemText(IDC_STATIC3, Props::i().lang("DLGASETUKSET_C6"));
	SetDlgItemText(IDOK, Props::i().lang("DLGASETUKSET_C7"));
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGASETUKSET_C8"));

    // LASKUTUSOHJELMA ///////////////////////
    m_OPTIONS_LASKUTUSOHJELMA = Props::i().get(OPTIONS_LASKUTUSOHJELMA).c_str();
    m_OPTIONS_LASKUTUSOHJELMA_POLKU = Props::i().get(OPTIONS_LASKUTUSOHJELMA_POLKU).c_str();
    m_OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU = Props::i().get(OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU).c_str();
    m_OPTIONS_LASKUTUSOHJELMA_YRITYS = Props::i().get(OPTIONS_LASKUTUSOHJELMA_YRITYS).c_str();

    if(m_OPTIONS_LASKUTUSOHJELMA == LAS_NONE) i = IDC_RADLASKOHJ1;
    else if(m_OPTIONS_LASKUTUSOHJELMA == LAS_MAATALOUSNEUVOS) i = IDC_RADLASKOHJ2;
    else if(m_OPTIONS_LASKUTUSOHJELMA == LAS_PASSELI) i = IDC_RADLASKOHJ3;
    CheckRadioButton(IDC_RADLASKOHJ1, IDC_RADLASKOHJ3, i);

    if(m_OPTIONS_LASKUTUSOHJELMA != LAS_NONE)        // Polku ja yritykset
	{
      haeYritykset(m_OPTIONS_LASKUTUSOHJELMA_POLKU, m_OPTIONS_LASKUTUSOHJELMA_YRITYS);
      m_stcLaskOhj.SetWindowText(m_OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU);
	}
    else
	{
      m_stcLaskOhj.SetWindowText("");
      m_cmbLaskYritys.EnableWindow(FALSE);
	}

    // Asetuksia ei ole muutettu. Enabloidaan, kun asiakas muuttaa asetuksia.
    m_btnOK.EnableWindow(FALSE);

	return TRUE;
}

void CDlgAsetukset::OnRadlaskohj() 
{ // Muutetaan käytettävä laskutusohjelma
    int i;
    BROWSEINFO bri;
    TCHAR szDir[MAX_PATH];
    LPMALLOC pMalloc = NULL;
    LPITEMIDLIST pidl = NULL;
    CString cs, ohjelma, yritys;

    try
	{
      i = GetCheckedRadioButton(IDC_RADLASKOHJ1, IDC_RADLASKOHJ3);   // Laskutusohjelman tyyppi
      if(i == IDC_RADLASKOHJ1) throw(GEN_RESET);                         // ei laskutusohjelmaa

      if(!SUCCEEDED(SHGetMalloc(&pMalloc))) throw(ERR_IMALLOC);      // tarvitaan LPITEMIDLIST:n vapauttamisessa

      cs = Props::i().get(OPTIONS_LASKUTUSOHJELMA_POLKU).c_str();    // Laskutusohjelman polku (antaa polun LPITEMIDLIST-struktuurina)
      bri.hwndOwner = this->GetSafeHwnd();
      bri.pidlRoot = NULL; 
      bri.pszDisplayName = szDir; 
      bri.lpszTitle = Props::i().lang("DLGASETUKSET_1");
      bri.ulFlags = BIF_RETURNONLYFSDIRS|BIF_STATUSTEXT;
      bri.lpfn = BrowseCallbackProc;
      bri.lParam = (LPARAM)&cs;
      bri.iImage = 0; 
      if(!(pidl = SHBrowseForFolder(&bri))) throw(RETURN_NOACTION);

      if(!SHGetPathFromIDList(pidl, szDir)) throw(ERR_SHGET);        // Muunnetaan polku mjonoksi

      if(i == IDC_RADLASKOHJ2) ohjelma = LAS_MAATALOUSNEUVOS;        // Haetaan tiedot
      else if(i == IDC_RADLASKOHJ3) ohjelma = LAS_PASSELI;
      if((yritys = haeYritykset(szDir, "")) == "") throw(RETURN_NOACTION);

      cs.Format("%s\\", szDir);                                      // tärkeää lisätä!!!
      m_OPTIONS_LASKUTUSOHJELMA_POLKU = cs;                          // Talletaan tiedot
      m_OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU = cs + yritys + "\\";
      m_OPTIONS_LASKUTUSOHJELMA = ohjelma;
      m_OPTIONS_LASKUTUSOHJELMA_YRITYS = yritys;
                    
      CheckRadioButton(IDC_RADLASKOHJ1, IDC_RADLASKOHJ3, i);         // Päivitä kontrollit
      m_stcLaskOhj.SetWindowText(m_OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU);   

      pMalloc->Free(pidl);                                           // Vapautetaan muisti ja rajapinta
      pMalloc->Release();
	}
    catch(int err)
	{
      if(pMalloc) {                                                  // Vapautetaan muisti ja rajapinta
      if(pidl) pMalloc->Free(pidl);
      pMalloc->Release(); }

      if(err == ERR_IMALLOC || err == ERR_SHGET || err == GEN_RESET)
	  {
        if(err == ERR_IMALLOC) cs = Props::i().lang("DLGASETUKSET_2");
        else if(err == ERR_SHGET) cs = Props::i().lang("DLGASETUKSET_3");
        else if(err == GEN_RESET) cs = "";

        CheckRadioButton(IDC_RADLASKOHJ1, IDC_RADLASKOHJ3, IDC_RADLASKOHJ1);
        m_stcLaskOhj.SetWindowText("");
        m_cmbLaskYritys.ResetContent();
        m_cmbLaskYritys.EnableWindow(FALSE);

		if(cs != "") MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

        m_OPTIONS_LASKUTUSOHJELMA = LAS_NONE;
		m_OPTIONS_LASKUTUSOHJELMA_POLKU = "";                          // Nollataan tiedot
        m_OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU = "";
        m_OPTIONS_LASKUTUSOHJELMA_YRITYS = "";
	  }
      else
	  {
        cs = Props::i().get(OPTIONS_LASKUTUSOHJELMA).c_str(); // Toiminto peruttu -> palauta laskutusohjelma vanhaan arvoonsa
        if(cs == LAS_NONE) i = IDC_RADLASKOHJ1;
        else if(cs == LAS_MAATALOUSNEUVOS) i = IDC_RADLASKOHJ2;
        else if(cs == LAS_PASSELI) i = IDC_RADLASKOHJ3;
        CheckRadioButton(IDC_RADLASKOHJ1, IDC_RADLASKOHJ3, i);
	  }
	}

    m_btnOK.EnableWindow(TRUE);
}

void CDlgAsetukset::OnSelchangeCmblaskyritys() 
{
    int s;
    CString yritys, polku;

    if((s = m_cmbLaskYritys.GetCurSel()) != CB_ERR)
	{
      m_cmbLaskYritys.GetLBText(s, yritys);                          // ota valittu yritys
      polku = Props::i().get(OPTIONS_LASKUTUSOHJELMA_POLKU).c_str(); // ota laskutusohjeleman polku
      m_OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU = polku + yritys + "\\";  // talleta uusi polku ja valittu uusi yritys
      m_OPTIONS_LASKUTUSOHJELMA_YRITYS = yritys;

      m_stcLaskOhj.SetWindowText(m_OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU);
      m_btnOK.EnableWindow(TRUE);
	}	
}

CString CDlgAsetukset::haeYritykset(CString polku, CString yritys)
{
    __int32 ret = 0;
    long hFile;
    struct _finddata_t c_file;
    CString cs = polku + "\\*.*";

    if(polku == "") return "";

    m_cmbLaskYritys.ResetContent();                  // Haetaan kaikki yritys-alikansiot
    hFile = _findfirst(cs, &c_file);
    while(ret != -1)
	{
      if((c_file.attrib & _A_SUBDIR))
	  {
        ret = atoi(c_file.name); cs = c_file.name;
        if(cs == "0" || ret > 0) m_cmbLaskYritys.AddString(cs);
	  }
      ret = _findnext(hFile, &c_file);
	}
    _findclose(hFile);

    if(m_cmbLaskYritys.GetCount() > 0)
	{
      if(yritys != "")
	    m_cmbLaskYritys.SetCurSel(m_cmbLaskYritys.FindString(0, yritys)); // Valitaan annettu listasta paluuarvoksi
      else
	    m_cmbLaskYritys.SetCurSel(0);

      m_cmbLaskYritys.GetLBText(0, cs);
      m_cmbLaskYritys.EnableWindow(TRUE);            // 
	}
    else
	{
      m_cmbLaskYritys.EnableWindow(FALSE);           // Lista tyhä -> virhe, pitäisi löytyä yrityksiä

      cs.Format(Props::i().lang("DLGASETUKSET_4"), polku);
      MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      cs = "";                                       // Paluuarvoksi virhe: ""
	}

    return cs;
}

int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData)
{
    if(uMsg == BFFM_INITIALIZED)
	{
      CString *cs = (CString*)pData;
      SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)(LPCSTR)*cs);
	  SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)(LPCSTR)*cs);
	}
    else if(uMsg == BFFM_SELCHANGED)
	{
      TCHAR szDir[MAX_PATH];
      if(SHGetPathFromIDList((LPITEMIDLIST)lp ,szDir))
	    SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
	}

    return 0;
}

void CDlgAsetukset::OnOK() 
{
    Props::i().set(OPTIONS_LASKUTUSOHJELMA, (LPCSTR)m_OPTIONS_LASKUTUSOHJELMA);
    Props::i().set(OPTIONS_LASKUTUSOHJELMA_POLKU, (LPCSTR)m_OPTIONS_LASKUTUSOHJELMA_POLKU);
    Props::i().set(OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU, (LPCSTR)m_OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU);
    Props::i().set(OPTIONS_LASKUTUSOHJELMA_YRITYS, (LPCSTR)m_OPTIONS_LASKUTUSOHJELMA_YRITYS);

    CDialog::OnOK();
}
