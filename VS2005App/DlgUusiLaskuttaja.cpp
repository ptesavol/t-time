// DlgUusiLaskuttaja.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "taikaDlg.h"
#include "Props.h"
#include "DlgUusiLaskuttaja.h"

// DlgUusiLaskuttaja dialog
IMPLEMENT_DYNAMIC(DlgUusiLaskuttaja, CDialog)

DlgUusiLaskuttaja::DlgUusiLaskuttaja(CWnd* pParent /*=NULL*/)
	: CDialog(DlgUusiLaskuttaja::IDD, pParent)
{}

DlgUusiLaskuttaja::~DlgUusiLaskuttaja()
{}

void DlgUusiLaskuttaja::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, PIC_QUESTION, m_picQuestion);
	DDX_Control(pDX, IDC_STCQUESTION, m_stcQuestion);
	DDX_Control(pDX, IDC_EDTNAME, m_edtName);
	DDX_Control(pDX, IDC_EDTEMAIL, m_edtEmail);
	DDX_Control(pDX, IDOK, m_btnOK);
}

BEGIN_MESSAGE_MAP(DlgUusiLaskuttaja, CDialog)
	ON_BN_CLICKED(IDOK, &DlgUusiLaskuttaja::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDTNAME, &DlgUusiLaskuttaja::OnEnChangeEdtname)
END_MESSAGE_MAP()

// DlgUusiLaskuttaja message handlers
BOOL DlgUusiLaskuttaja::OnInitDialog() 
{
    CDialog::OnInitDialog();

	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSILASKUTTAJA_C1"));
	SetDlgItemText(IDC_STATIC2, Props::i().lang("DLGUUSILASKUTTAJA_C2"));
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGUUSILASKUTTAJA_C3"));

	// m_pid = NULL -> uusi, != null -> muokkaus
	if(m_pid == NULL)
	{
	    m_picQuestion.SetIcon(LoadIcon(NULL, IDI_QUESTION));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSILASKUTTAJA_1"));
		this->SetWindowText(Props::i().lang("DLGUUSILASKUTTAJA_2"));
		m_stcQuestion.SetWindowText(Props::i().lang("DLGUUSILASKUTTAJA_3"));
	}
	else
	{
	    m_picQuestion.SetIcon(LoadIcon(Props::e().m_hInstance, MAKEINTRESOURCE(IDI_EDIT)));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSILASKUTTAJA_4"));
		this->SetWindowText(Props::i().lang("DLGUUSILASKUTTAJA_5"));
		m_stcQuestion.SetWindowText(Props::i().lang("DLGUUSILASKUTTAJA_6"));
	}

	m_edtName.SetWindowTextA((m_pid != NULL ? m_pid->Name : ""));
	m_edtEmail.SetWindowTextA((m_pid != NULL ? m_pid->Email : ""));

	m_sync = 0;                                      // Listoihin ei ole lisätty uusia rivejä

    return TRUE;
}

void DlgUusiLaskuttaja::OnBnClickedOk()
{
	CString cs;

	try
	{
		m_edtName.GetWindowText(m_name);
		if(m_name == "") throw(ERR_NEWBILLER_1);

		m_edtEmail.GetWindowText(m_email);
		if(m_email == "") throw(ERR_NEWBILLER_2);
	}
	catch(int err)
	{
		if(err == ERR_NEWBILLER_1) cs = Props::i().lang("DLGUUSILASKUTTAJA_7");
		else if(err == ERR_NEWBILLER_2) cs = Props::i().lang("DLGUUSILASKUTTAJA_8");

		if(err > ERR_NEWBILLER_0)
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return;
	}

	if(((CTaikaDlg*)(Props::e().m_pMainWnd))->pageListat.lisaaLaskuttaja(this) != RETURN_OK)
		return;

	CDialog::OnOK();
}

void DlgUusiLaskuttaja::OnEnChangeEdtname()
{ m_sync |= SYNC_LASKUTTAJAT; }