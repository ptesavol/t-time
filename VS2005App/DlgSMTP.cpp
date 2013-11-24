// DlgSMTP.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "DlgSMTP.h"
#include "Props.h"
#include "PJNSMTP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSMTP dialog
DlgSMTP::DlgSMTP(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSMTP::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSMTP)
	//}}AFX_DATA_INIT
}

void DlgSMTP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSMTP)
	DDX_Control(pDX, IDC_STCATTACHMENT, m_stcAttachment);
	DDX_Control(pDX, IDC_CHKLASKUTTAJAT, m_chkLaskuttajat);
	DDX_Control(pDX, IDC_CHKASIAKKAAT, m_chkAsiakkaat);
	DDX_Control(pDX, IDC_CHKTUOTTEET, m_chkTuotteet);
	DDX_Control(pDX, IDC_CMBSMTPSERVER, m_cmbSMTPServer);
	DDX_Control(pDX, IDC_EDTPASSWORD, m_edtPassword);
	DDX_Control(pDX, IDC_CHKKAYTAAUTH, m_chkKaytaAuth);
	DDX_Control(pDX, IDC_CHKMUISTAUN, m_chkMuistaUn);
	DDX_Control(pDX, IDC_STCINFO, m_stcInfo);
	DDX_Control(pDX, IDC_EDTUSERNAME, m_edtUsername);
	DDX_Control(pDX, IDC_EDTPORT, m_edtSMTPPort);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_EDTRECIPIENTS, m_edtRecipients);
	DDX_Control(pDX, IDC_BTNLAHETA, m_btnLaheta);
	DDX_Control(pDX, IDC_CHKTYOTYYPIT, m_chkTyotyypit);
	DDX_Control(pDX, IDC_BTNPOLKU, m_btnPolku);
	DDX_Control(pDX, IDC_EDTFROM, m_edtFrom);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgSMTP, CDialog)
	//{{AFX_MSG_MAP(DlgSMTP)
	ON_BN_CLICKED(IDC_BTNPOLKU, OnBtnpolku)
	ON_BN_CLICKED(IDC_BTNLAHETA, OnBtnlaheta)
	ON_EN_CHANGE(IDC_EDTRECIPIENTS, OnChangeEdtrecipients)
	ON_EN_CHANGE(IDC_EDTFROM, OnChangeEdtfrom)
	ON_EN_CHANGE(IDC_EDTPORT, OnChangeEdtport)
	ON_BN_CLICKED(IDC_CHKMUISTAUN, OnChkmuistaun)
	ON_EN_CHANGE(IDC_EDTPASSWORD, OnChangeEdtpassword)
	ON_EN_CHANGE(IDC_EDTUSERNAME, OnChangeEdtusername)
	ON_BN_CLICKED(IDC_CHKKAYTAAUTH, OnChkkaytaauth)
	ON_CBN_EDITCHANGE(IDC_CMBSMTPSERVER, OnEditchangeCmbsmtpserver)
	ON_CBN_SELCHANGE(IDC_CMBSMTPSERVER, OnSelchangeCmbsmtpserver)
	ON_BN_CLICKED(IDC_CHKTYOTYYPIT, OnChktyotyypit)
	ON_BN_CLICKED(IDC_CHKTUOTTEET, OnChktuotteet)
	ON_BN_CLICKED(IDC_RADLAHDE1, OnRadlahde)
	ON_BN_CLICKED(IDC_CHKASIAKKAAT, OnChkasiakkaat)
	ON_BN_CLICKED(IDC_CHKLASKUTTAJAT, OnChklaskuttajat)
	ON_BN_CLICKED(IDC_RADLAHDE2, OnRadlahde)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSMTP message handlers

BOOL DlgSMTP::OnInitDialog() 
{
    CString cs;

    CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGSMTP_C1"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGSMTP_C2"));
	SetDlgItemText(IDC_STATIC2, Props::i().lang("DLGSMTP_C3"));
	SetDlgItemText(IDC_STATIC3, Props::i().lang("DLGSMTP_C4"));
	SetDlgItemText(IDC_STATIC4, Props::i().lang("DLGSMTP_C5"));
	SetDlgItemText(IDC_STATIC5, Props::i().lang("DLGSMTP_C6"));
	SetDlgItemText(IDC_STATIC6, Props::i().lang("DLGSMTP_C7"));
	SetDlgItemText(IDC_STATIC7, Props::i().lang("DLGSMTP_C8"));
	SetDlgItemText(IDC_RADLAHDE1, Props::i().lang("DLGSMTP_C9"));
	SetDlgItemText(IDC_RADLAHDE2, Props::i().lang("DLGSMTP_C10"));
	SetDlgItemText(IDC_CHKASIAKKAAT, Props::i().lang("DLGSMTP_C11"));
	SetDlgItemText(IDC_CHKLASKUTTAJAT, Props::i().lang("DLGSMTP_C12"));
	SetDlgItemText(IDC_CHKTYOTYYPIT, Props::i().lang("DLGSMTP_C13"));
	SetDlgItemText(IDC_CHKTUOTTEET, Props::i().lang("DLGSMTP_C14"));
	SetDlgItemText(IDC_CHKKAYTAAUTH, Props::i().lang("DLGSMTP_C15"));
	SetDlgItemText(IDC_CHKMUISTAUN, Props::i().lang("DLGSMTP_C16"));
	SetDlgItemText(IDC_BTNLAHETA, Props::i().lang("DLGSMTP_C17"));
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGSMTP_C18"));

    m_recipients = Props::i().get(OPTIONS_EM_RECIPIENTS).c_str();         //
    m_edtRecipients.SetWindowText(m_recipients);

    m_from = Props::i().get(OPTIONS_EM_FROM).c_str();                     //
    m_edtFrom.SetWindowText(m_from);

    m_SMTPServer = Props::i().get(OPTIONS_EM_SMTP_SERVER).c_str();        //
    m_cmbSMTPServer.SetWindowText(m_SMTPServer);

    m_SMTPPort = Props::i().get(OPTIONS_EM_SMTP_PORT).c_str();            //
    m_edtSMTPPort.SetWindowText(m_SMTPPort);

    cs = Props::i().get(OPTIONS_EM_SMTP_USE_AUTH).c_str();                //
    if(cs == C_TRUE) m_kayta_auth = TRUE;
    else m_kayta_auth = FALSE;
    m_chkKaytaAuth.SetCheck(m_kayta_auth);
    if(m_kayta_auth)
	{
      m_edtUsername.EnableWindow(TRUE);
      m_edtPassword.EnableWindow(TRUE);
      m_chkMuistaUn.EnableWindow(TRUE);
	}
    else
	{
      m_edtUsername.EnableWindow(FALSE);
      m_edtPassword.EnableWindow(FALSE);
      m_chkMuistaUn.EnableWindow(FALSE);
	}

    cs = Props::i().get(OPTIONS_EM_SMTP_RMBR_UN).c_str();                 //
    if(cs == C_TRUE) m_muista_un = TRUE;
    else m_muista_un = FALSE;
    m_chkMuistaUn.SetCheck(m_muista_un);

    m_username = Props::i().get(OPTIONS_EM_SMTP_USERNAME).c_str();        //
    m_edtUsername.SetWindowText(m_username);

    m_password = "";                                                 //
    m_edtPassword.SetWindowText(m_password);

    m_cbm.LoadBitmap(IDB_FOLDER);                                    // Folder-bitmap
    m_btnPolku.SetBitmap(m_cbm);

    if(m_mode == MODE_EMAIL_RAPORTIT)
	{
	
	}
    else if(m_mode == MODE_EMAIL_LISTAT)
	{
      m_attachmentpath = "";
      m_attachmentfilename = "";
      m_attach_from = IDC_RADLAHDE1;                                 // Liite t-aika -ohjelmasta
      m_asiakkaat = BST_CHECKED;
      m_laskuttajat = BST_CHECKED;
      m_tyotyypit = BST_CHECKED;
      m_tuotteet = BST_CHECKED;
      m_chkAsiakkaat.SetCheck(BST_CHECKED);
      m_chkLaskuttajat.SetCheck(BST_CHECKED);
      m_chkTyotyypit.SetCheck(BST_CHECKED);
	  m_chkTuotteet.SetCheck(BST_CHECKED);
      m_btnPolku.EnableWindow(FALSE);
	  CheckRadioButton(IDC_RADLAHDE1, IDC_RADLAHDE2, IDC_RADLAHDE1);
	}

    // Värillinen tausta info-tekstille. Oletuksena taustan värinen.
	m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), "");

    return TRUE;
}

void DlgSMTP::OnBtnpolku() 
{
    DWORD e;
    CString file;
    OPENFILENAME ofn;
    DlgSMTP dlg_smtp;
	char buf[128] = {0};
    char *lpstrFile = NULL, strFileTitle[MAX_PATH];

    try
	{
      file = Props::i().get(OPTIONS_OPENPATH).c_str();

      if(!(lpstrFile = new char[MAX_PATH * 100])) throw(0);          // Tarpeeksi tilaa useammalle tiedostonimelle

      ofn.lStructSize = sizeof(OPENFILENAME);
      ofn.hwndOwner = this->GetSafeHwnd();
      ofn.lpstrFilter = Props::i().langs("DLGSMTP_1", buf, 128);
      ofn.lpstrTitle = Props::i().lang("DLGSMTP_2");
      ofn.lpstrInitialDir = file;
      ofn.lpstrCustomFilter = NULL; ofn.nFilterIndex = 1;
      *lpstrFile = NULL; ofn.lpstrFile = lpstrFile; ofn.nMaxFile = MAX_PATH * 100;
      ofn.lpstrFileTitle = strFileTitle; ofn.nMaxFileTitle = MAX_PATH;
      ofn.Flags = OFN_EXPLORER|OFN_HIDEREADONLY|OFN_LONGNAMES|OFN_PATHMUSTEXIST;
      ofn.lpstrDefExt = NULL; ofn.lCustData = NULL;
      if(!GetOpenFileName(&ofn)) throw(0);
      file = ofn.lpstrFile; file = file.Left(ofn.nFileOffset); // talleta, mahdollisesti uusi, polku asetuksiin
      Props::i().set(OPTIONS_OPENPATH, (LPCSTR)file);
 
      m_stcAttachment.SetWindowText(ofn.lpstrFileTitle);
      m_attachmentpath = ofn.lpstrFile;
      m_attachmentfilename = ofn.lpstrFileTitle;
      m_attachmentfilename = m_attachmentfilename.Left(m_attachmentfilename.GetLength() - 4);
	}
    catch(...)
	{
      if((e = CommDlgExtendedError()) != ERROR_SUCCESS)
      {
        file.Format(Props::i().lang("DLGSMTP_3"), e);
        MessageBox(file, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }
	}

    if(lpstrFile) delete [] lpstrFile;               // Vapauta muisti
}

void DlgSMTP::OnRadlahde() 
{
    CString cs;
    COleDateTime odt;

    m_attach_from = GetCheckedRadioButton(IDC_RADLAHDE1, IDC_RADLAHDE2);
    if(m_attach_from == IDC_RADLAHDE1)
	{
      m_chkAsiakkaat.EnableWindow(TRUE);
      m_chkLaskuttajat.EnableWindow(TRUE);
      m_chkTyotyypit.EnableWindow(TRUE);
      m_chkTuotteet.EnableWindow(TRUE);
      m_btnPolku.EnableWindow(FALSE);
      m_stcAttachment.SetWindowText("");
	}
    else if(m_attach_from == IDC_RADLAHDE2)
	{
      m_chkAsiakkaat.EnableWindow(FALSE);
      m_chkLaskuttajat.EnableWindow(FALSE);
      m_chkTyotyypit.EnableWindow(FALSE);
      m_chkTuotteet.EnableWindow(FALSE);
      m_btnPolku.EnableWindow(TRUE);
      m_stcAttachment.SetWindowText("");
	}	
}

void DlgSMTP::OnChkkaytaauth() 
{
    CString cs;

    if(m_chkKaytaAuth.GetCheck() == 0) { m_kayta_auth = FALSE; cs = C_FALSE; }
    else { m_kayta_auth = TRUE; cs = C_TRUE; }

    Props::i().set(OPTIONS_EM_SMTP_USE_AUTH, (LPCSTR)cs);

    if(m_kayta_auth)
	{
      m_edtUsername.EnableWindow(TRUE);
      m_edtPassword.EnableWindow(TRUE);
      m_chkMuistaUn.EnableWindow(TRUE);
	}
    else
	{
      m_edtUsername.EnableWindow(FALSE);
      m_edtPassword.EnableWindow(FALSE);
      m_chkMuistaUn.EnableWindow(FALSE);
	}
}

void DlgSMTP::OnChkmuistaun() 
{
    CString cs;

    if(m_chkMuistaUn.GetCheck() == 0) { m_muista_un = FALSE; cs = C_FALSE; }
    else { m_muista_un = TRUE; cs = C_TRUE; }

    Props::i().set(OPTIONS_EM_SMTP_RMBR_UN, (LPCSTR)cs);
}

void DlgSMTP::OnChkasiakkaat() 
{ m_asiakkaat = m_chkAsiakkaat.GetCheck(); }

void DlgSMTP::OnChklaskuttajat() 
{ m_laskuttajat = m_chkLaskuttajat.GetCheck(); }

void DlgSMTP::OnChktyotyypit() 
{ m_tyotyypit = m_chkTyotyypit.GetCheck(); }

void DlgSMTP::OnChktuotteet() 
{ m_tuotteet = m_chkTuotteet.GetCheck(); }

void DlgSMTP::OnChangeEdtrecipients() 
{ m_edtRecipients.GetWindowText(m_recipients); }

void DlgSMTP::OnChangeEdtfrom() 
{ m_edtFrom.GetWindowText(m_from); }

void DlgSMTP::OnChangeEdtport() 
{  m_edtSMTPPort.GetWindowText(m_SMTPPort); }

void DlgSMTP::OnChangeEdtusername() 
{ m_edtUsername.GetWindowText(m_username); }

void DlgSMTP::OnChangeEdtpassword() 
{  m_edtPassword.GetWindowText(m_password); }

void DlgSMTP::OnEditchangeCmbsmtpserver() 
{
    CString cs;

	m_cmbSMTPServer.GetWindowText(cs);
	m_SMTPServer = cs;
	//m_cmbSMTPServer.GetWindowText(m_SMTPServer);
 }

void DlgSMTP::OnSelchangeCmbsmtpserver() 
{
    int s;
    CString cs;

    if((s = m_cmbSMTPServer.GetCurSel()) == CB_ERR) return;
    m_cmbSMTPServer.GetLBText(s, cs);

    if((s = cs.Find("(", 0)) == -1) return;          // Poistetaan (...) tekstistä
    cs = cs.Left(s - 1);
    m_SMTPServer = cs;
}

void DlgSMTP::OnCancel() 
{
    Props::i().set(OPTIONS_EM_FROM, (LPCSTR)m_from);
    Props::i().set(OPTIONS_EM_RECIPIENTS, (LPCSTR)m_recipients);
    Props::i().set(OPTIONS_EM_SMTP_SERVER, (LPCSTR)m_SMTPServer);
    Props::i().set(OPTIONS_EM_SMTP_PORT, (LPCSTR)m_SMTPPort);
    if(m_muista_un) Props::i().set(OPTIONS_EM_SMTP_USERNAME, (LPCSTR)m_username);
    else Props::i().set(OPTIONS_EM_SMTP_USERNAME, "");

	CDialog::OnCancel();
}

void DlgSMTP::OnBtnlaheta() 
{
    // Käyttää tiedostoja: smtp.h, smtp.cpp --- md5.h, md5.cpp --- glob-md5.h --- Base64Coder.h, Base64Coder.cpp
    DWORD e;
    int port;
    time_t tt;
    Parse parse;
    COleDateTime odt;
    CPJNSMTPMessage cmes;
    CPJNSMTPConnection csmtp;
    CPJNSMTPBodyPart cbodypart;
    char temp_path[MAX_PATH * 2];
    CString cs, body, attach_path, subatt;

    this->EnableWindow(FALSE);                       // Kaikki nappulat pois käytöstä
    m_btnLaheta.EnableWindow(FALSE);
    /*m_edtFrom.EnableWindow(FALSE);
    m_edtRecipients.EnableWindow(FALSE);
    m_cmbSMTPServer.EnableWindow(FALSE);
    m_edtSMTPPort.EnableWindow(FALSE);
    m_chkAsiakkaat.EnableWindow(FALSE);
    m_chkLaskuttajat.EnableWindow(FALSE);
    m_chkTyotyypit.EnableWindow(FALSE);
    m_chkTuotteet.EnableWindow(FALSE);
    m_btnPolku.EnableWindow(FALSE); 
    m_btnCancel.EnableWindow(FALSE);
    m_chkKaytaAuth.EnableWindow(FALSE);
    m_chkMuistaUn.EnableWindow(FALSE);
    m_edtUsername.EnableWindow(FALSE);
    m_edtPassword.EnableWindow(FALSE);*/

    try
	{
      if(m_edtRecipients.GetWindowTextLength() == 0) throw(ERR_SMPTP_3);
      if(m_edtFrom.GetWindowTextLength() == 0) throw(ERR_SMPTP_4);
      if(m_cmbSMTPServer.GetWindowTextLength() == 0) throw(ERR_SMPTP_7);
      if(m_edtSMTPPort.GetWindowTextLength() == 0) throw(ERR_SMPTP_8);

	  m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSMTP_4"));

      time(&tt);                                     // Luodaan liitteen ja subject-kentän nimi
      subatt.Format("taikalistat%s%d", _IDENTIFIER_, tt);

      e = GetTempPath(2 * MAX_PATH, temp_path);      // polku TMP- tai TEMP-ympäristömuuttujan kansioon
      if(e == 0 || e > 2 * MAX_PATH) throw(ERR_SMPTP_0);

      // Liite lisätään aina tiedostosta CPJNSMTPBodyPart-luokalle
      if(m_attach_from == IDC_RADLAHDE1)             // Liite t-aika -ohjelmasta (tietokannasta)
	  {
        attach_path = temp_path + subatt + DOT_TTA_EXT;  // polku/tiedostonimi väliaikaiseen tiedostoon
        if(!parse.talletaTTA(this->GetSafeHwnd(), attach_path, m_asiakkaat, m_laskuttajat, m_tyotyypit, m_tuotteet, MODE_ATTACH)) throw(GEN_ERROR);
	  }
      else                                           // Liite tiedostosta
	  {
        attach_path = temp_path + subatt + DOT_TTA_EXT;
        CopyFile(m_attachmentpath, attach_path, FALSE);
	  }

      // NoLoginMethod (HELO), AuthLoginMethod (EHLO -> AUTH LOGIN authentication), CramMD5Method (EHLO -> AUTH CRAM-MD5), LoginPlainMethod (EHLO-> AUTH LOGIN PLAIN)
      port = atoi(m_SMTPPort);
      if(!m_kayta_auth)                              // Ei tunnistautumista palvelimelle
	    csmtp.Connect(m_SMTPServer, CPJNSMTPConnection::AUTH_NONE, "", "", port);
      else                                           // Tunnistaudu palvelimelle
	    csmtp.Connect(m_SMTPServer, CPJNSMTPConnection::AUTH_PLAIN, m_username, m_password, port);

      cmes.SetCharset(_T("iso-8859-1"));                       // : merkistö
      cbodypart.SetCharset(_T("iso-8859-1"));
	  cmes.ParseMultipleRecipients(m_recipients, cmes.m_To);   // :: vastaanottajat
      cmes.m_From = CPJNSMTPAddress(m_from);                   // ::: lähettäjä
      cmes.m_sSubject = subatt;                                // :::: otsikko
      odt = odt.GetCurrentTime();                              // ::::: selkokielinen viesti (jos käyttäjä tutkii sähköpostiaan manuaalisesti)
	  body.Format(Props::i().lang("DLGSMTP_5"), odt.GetDay(), odt.GetMonth(), odt.GetYear(), odt.GetHour(), odt.GetMinute(), odt.GetSecond());
      cmes.AddTextBody(body);
      if(!(cbodypart.SetFilename(attach_path))) throw(ERR_SMPTP_2);	// :::::: liite
      cmes.AddBodyPart(cbodypart);

      csmtp.SendMessage(cmes);                       // Lähetä viesti

	  m_stcInfo.coloredInfo(LIGHTGREEN, Props::i().lang("DLGSMTP_6"));
	}
    catch(int err)
	{
      LPVOID lpMsgBuf;

      e = 0;
      if(err == ERR_SMPTP_0)
	  {
        e = GetLastError();
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, e, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL/*(va_list *)(DWORD)args*/);
        body.Format(Props::i().lang("DLGSMTP_7"), e, (LPCSTR)lpMsgBuf);
        body.Replace("\r\n", "");
        LocalFree(lpMsgBuf);
	  }
      else if(err == ERR_SMPTP_2) body = Props::i().lang("DLGSMTP_8");
      else if(err == ERR_SMPTP_3) { m_edtRecipients.SetFocus(); body = Props::i().lang("DLGSMTP_9"); }
      else if(err == ERR_SMPTP_4) { m_edtFrom.SetFocus();       body = Props::i().lang("DLGSMTP_10"); }
      else if(err == ERR_SMPTP_7) { m_cmbSMTPServer.SetFocus(); body = Props::i().lang("DLGSMTP_11"); }
      else if(err == ERR_SMPTP_8) { m_edtSMTPPort.SetFocus();   body = Props::i().lang("DLGSMTP_12"); }

      if(e == ERROR_SUCCESS && err == ERR_SMPTP_0) body = Props::i().lang("DLGSMTP_13");

      MessageBox(Props::i().lang("DLGSMTP_14") + body, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  m_stcInfo.coloredInfo(LIGHTRED, Props::i().lang("DLGSMTP_15") + body);
	}
    catch(CPJNSMTPException* pEx)
    {
      CString sMsg;
      if (HRESULT_FACILITY(pEx->m_hr) == FACILITY_ITF)
        sMsg.Format(_T(Props::i().lang("DLGSMTP_16")), pEx->m_hr, pEx->GetErrorMessage().operator LPCTSTR());
      else
        sMsg.Format(_T(Props::i().lang("DLGSMTP_17")), pEx->m_hr, pEx->GetErrorMessage().operator LPCTSTR(), pEx->m_sLastResponse.operator LPCTSTR());

      sMsg.Replace("\r\n", "");
      MessageBox(Props::i().lang("DLGSMTP_18") + sMsg, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  m_stcInfo.coloredInfo(LIGHTRED, Props::i().lang("DLGSMTP_15") + CString(pEx->GetErrorMessage().operator LPCTSTR()));

      pEx->Delete();
	}

    DeleteFile(attach_path);                         // Poista väliaikainen tiedosto

    this->EnableWindow(TRUE);                        // Kaikki nappulat takaisin käyttöön
    m_btnLaheta.EnableWindow(TRUE);
    /*m_edtFrom.EnableWindow(TRUE);
    m_edtRecipients.EnableWindow(TRUE);
    m_cmbSMTPServer.EnableWindow(TRUE);
    m_edtSMTPPort.EnableWindow(TRUE);
    m_btnCancel.EnableWindow(TRUE);
    if(m_attach_from == IDC_RADLAHDE1)
	{
      m_chkAsiakkaat.EnableWindow(TRUE);
      m_chkLaskuttajat.EnableWindow(TRUE);
      m_chkTyotyypit.EnableWindow(TRUE);
      m_chkTuotteet.EnableWindow(TRUE);
      m_btnPolku.EnableWindow(FALSE);
	}
    else
	{
      m_chkAsiakkaat.EnableWindow(TRUE);
      m_chkLaskuttajat.EnableWindow(TRUE);
      m_chkTyotyypit.EnableWindow(FALSE);
      m_chkTuotteet.EnableWindow(FALSE);
      m_btnPolku.EnableWindow(TRUE);
	}
    m_chkKaytaAuth.EnableWindow(TRUE);
    if(m_kayta_auth)
	{
      m_chkMuistaUn.EnableWindow(TRUE);
      m_edtUsername.EnableWindow(TRUE);
      m_edtPassword.EnableWindow(TRUE);
	}
    else
	{
      m_chkMuistaUn.EnableWindow(FALSE);
      m_edtUsername.EnableWindow(FALSE);
      m_edtPassword.EnableWindow(FALSE);
	}*/
}