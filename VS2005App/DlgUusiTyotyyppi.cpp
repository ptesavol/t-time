// DlgUusiTyotyyppi.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "taikaDlg.h"
#include "Props.h"
#include "DlgUusiTyotyyppi.h"

// DlgUusiTyotyyppi dialog
IMPLEMENT_DYNAMIC(DlgUusiTyotyyppi, CDialog)

DlgUusiTyotyyppi::DlgUusiTyotyyppi(CWnd* pParent /*=NULL*/)
	: CDialog(DlgUusiTyotyyppi::IDD, pParent)
{}

DlgUusiTyotyyppi::~DlgUusiTyotyyppi()
{}

void DlgUusiTyotyyppi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, PIC_QUESTION, m_picQuestion);
	DDX_Control(pDX, IDC_STCQUESTION, m_stcQuestion);
	DDX_Control(pDX, IDC_EDTNAME, m_edtName);
	DDX_Control(pDX, IDC_EDTPRODUCTNUMBER, m_edtProductNumber);
	DDX_Control(pDX, IDOK, m_btnOK);
}

BEGIN_MESSAGE_MAP(DlgUusiTyotyyppi, CDialog)
	ON_BN_CLICKED(IDOK, &DlgUusiTyotyyppi::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDTNAME, &DlgUusiTyotyyppi::OnEnChangeEdtname)
END_MESSAGE_MAP()

// DlgUusiTyotyyppi message handlers
BOOL DlgUusiTyotyyppi::OnInitDialog() 
{
    CDialog::OnInitDialog();

	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITYOTYYPPI_C1"));
	SetDlgItemText(IDC_STATIC2, Props::i().lang("DLGUUSITYOTYYPPI_C2"));
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGUUSITYOTYYPPI_C3"));

	// m_pid = NULL -> uusi, != null -> muokkaus
	if(m_pid == NULL)
	{
	    m_picQuestion.SetIcon(LoadIcon(NULL, IDI_QUESTION));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSITYOTYYPPI_1"));
		this->SetWindowText(Props::i().lang("DLGUUSITYOTYYPPI_2"));
		m_stcQuestion.SetWindowText(Props::i().lang("DLGUUSITYOTYYPPI_3"));
	}
	else
	{
	    m_picQuestion.SetIcon(LoadIcon(Props::e().m_hInstance, MAKEINTRESOURCE(IDI_EDIT)));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSITYOTYYPPI_4"));
		this->SetWindowText(Props::i().lang("DLGUUSITYOTYYPPI_5"));
		m_stcQuestion.SetWindowText(Props::i().lang("DLGUUSITYOTYYPPI_6"));
	}

	m_edtName.SetWindowTextA((m_pid != NULL ? m_pid->Name : ""));
	m_edtProductNumber.SetWindowTextA((m_pid != NULL ? m_pid->ProductNumber : ""));

	m_sync = 0;                                      // Listoihin ei ole lisätty uusia rivejä

    return TRUE;
}
void DlgUusiTyotyyppi::OnBnClickedOk()
{
	CString cs;

	try
	{
		m_edtName.GetWindowText(m_name);
		if(m_name == "") throw(ERR_NEWWORKTYPE_1);

		m_edtProductNumber.GetWindowText(m_productnumber);
		//if(m_productnumber == "") throw(ERR_NEWWORKTYPE_2);
	}
	catch(int err)
	{
		if(err == ERR_NEWWORKTYPE_1) cs = Props::i().lang("DLGUUSITYOTYYPPI_7");
		else if(err == ERR_NEWWORKTYPE_2) cs = Props::i().lang("DLGUUSITYOTYYPPI_8");

		if(err > ERR_NEWWORKTYPE_0)
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return;
	}

	if(((CTaikaDlg*)(Props::e().m_pMainWnd))->pageListat.lisaaTyotyyppi(this) != RETURN_OK)
		return;

	CDialog::OnOK();
}

void DlgUusiTyotyyppi::OnEnChangeEdtname()
{ m_sync |= SYNC_TYOTYYPIT; }
