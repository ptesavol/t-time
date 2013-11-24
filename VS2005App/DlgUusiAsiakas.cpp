// DlgUusiAsiakas.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "taikaDlg.h"
#include "Props.h"
#include "DlgUusiAsiakas.h"

// DlgUusiAsiakas dialog
IMPLEMENT_DYNAMIC(DlgUusiAsiakas, CDialog)

DlgUusiAsiakas::DlgUusiAsiakas(CWnd* pParent /*=NULL*/)
	: CDialog(DlgUusiAsiakas::IDD, pParent)
{}

DlgUusiAsiakas::~DlgUusiAsiakas()
{}

void DlgUusiAsiakas::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, PIC_QUESTION, m_picQuestion);
	DDX_Control(pDX, IDC_STCQUESTION, m_stcQuestion);
	DDX_Control(pDX, IDC_EDTNAME, m_edtName);
	DDX_Control(pDX, IDC_EDTADDRESS, m_edtAddress);
	DDX_Control(pDX, IDC_CMBBILLER, m_cmbBiller);
	DDX_Control(pDX, IDC_EDTNOTE, m_edtNote);
	DDX_Control(pDX, IDC_EDTSHORTNOTE, m_edtShortNote);
	DDX_Control(pDX, IDC_EDTINFO, m_edtInfo);
	DDX_Control(pDX, IDC_EDTCUSTOMERNUMBER, m_edtCustomerNumber);
	DDX_Control(pDX, IDOK, m_btnOK);
}

BEGIN_MESSAGE_MAP(DlgUusiAsiakas, CDialog)
	ON_BN_CLICKED(IDOK, &DlgUusiAsiakas::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_CMBBILLER, &DlgUusiAsiakas::OnCbnSelchangeCmbbiller)
	ON_CBN_EDITCHANGE(IDC_CMBBILLER, &DlgUusiAsiakas::OnCbnEditchangeCmbbiller)
	ON_EN_CHANGE(IDC_EDTNAME, &DlgUusiAsiakas::OnEnChangeEdtname)
END_MESSAGE_MAP()

// DlgUusiAsiakas message handlers
BOOL DlgUusiAsiakas::OnInitDialog() 
{
    int i, s;
    DbSqlite db;
    vector <CString> vect;

    CDialog::OnInitDialog();

	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSIASIAKAS_C1"));
	SetDlgItemText(IDC_STATIC2, Props::i().lang("DLGUUSIASIAKAS_C2"));
	SetDlgItemText(IDC_STATIC3, Props::i().lang("DLGUUSIASIAKAS_C3")); 
	SetDlgItemText(IDC_STATIC4, Props::i().lang("DLGUUSIASIAKAS_C4")); 
	SetDlgItemText(IDC_STATIC5, Props::i().lang("DLGUUSIASIAKAS_C5")); 
	SetDlgItemText(IDC_STATIC6, Props::i().lang("DLGUUSIASIAKAS_C6")); 
	SetDlgItemText(IDC_STATIC7, Props::i().lang("DLGUUSIASIAKAS_C7")); 
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGUUSIASIAKAS_C8"));

	// m_pid = NULL -> uusi, != null -> muokkaus
	if(m_pid == NULL)
	{
	    m_picQuestion.SetIcon(LoadIcon(NULL, IDI_QUESTION));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSIASIAKAS_1"));
		this->SetWindowText(Props::i().lang("DLGUUSIASIAKAS_2"));
		m_stcQuestion.SetWindowText(Props::i().lang("DLGUUSIASIAKAS_3"));
	}
	else
	{
	    m_picQuestion.SetIcon(LoadIcon(Props::e().m_hInstance, MAKEINTRESOURCE(IDI_EDIT)));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSIASIAKAS_4"));
		this->SetWindowText(Props::i().lang("DLGUUSIASIAKAS_5"));
		m_stcQuestion.SetWindowText(Props::i().lang("DLGUUSIASIAKAS_6"));
	}

    s = (vect = db.haeTaulusta("Biller", "Name", 1, "Name", 1, "", "Name", "<>", DFLT_BILLER)).size();  // Laskuttajien nimet tietokannasta
    for(i=0; i<s; i++) m_cmbBiller.AddString(vect[i]);
	db.findCBItem(FALSE, &m_cmbBiller, "Biller", "Name", (m_pid != NULL ? m_pid->Biller_id : ""));

	m_edtName.SetWindowTextA((m_pid != NULL ? m_pid->Name : ""));
	m_edtAddress.SetWindowTextA((m_pid != NULL ? m_pid->Address : ""));
	m_edtNote.SetWindowTextA((m_pid != NULL ? m_pid->Note : ""));
	m_edtShortNote.SetWindowTextA((m_pid != NULL ? m_pid->Shortnote : ""));
	m_edtInfo.SetWindowTextA((m_pid != NULL ? m_pid->Info : ""));
	m_edtCustomerNumber.SetWindowTextA((m_pid != NULL ? m_pid->CustomerNumber : ""));

	m_sync = 0;                                      // Listoihin ei ole lisätty uusia rivejä

    return TRUE;
}

void DlgUusiAsiakas::OnBnClickedOk()
{
	CString cs;

	try
	{
		m_edtName.GetWindowText(m_name);
		if(m_name == "") throw(ERR_NEWWORKPLACE_1);

		m_edtAddress.GetWindowText(m_address);
		//if(m_address == "") throw(ERR_NEWWORKPLACE_2);

		m_cmbBiller.GetWindowText(m_biller_name);
		if(m_biller_name == "") throw(ERR_NEWWORKPLACE_3);

		m_edtNote.GetWindowText(m_note);
		//if(m_note == "") throw(ERR_NEWWORKPLACE_4);

		m_edtShortNote.GetWindowText(m_shortnote);
		//if(m_shortnote == "") throw(ERR_NEWWORKPLACE_5);

		m_edtInfo.GetWindowText(m_info);
		//if(m_info == "") throw(ERR_NEWWORKPLACE_6);

		m_edtCustomerNumber.GetWindowText(m_customernumber);
		//if(m_customernumber == "") throw(ERR_NEWWORKPLACE_7);*/
	}
	catch(int err)
	{
		if(err == ERR_NEWWORKPLACE_1) cs = Props::i().lang("DLGUUSIASIAKAS_7");
		//else if(err == ERR_NEWWORKPLACE_2) cs = Props::i().lang("DLGUUSIASIAKAS_8");
		else if(err == ERR_NEWWORKPLACE_3) cs = Props::i().lang("DLGUUSIASIAKAS_9");
		//else if(err == ERR_NEWWORKPLACE_4) cs = Props::i().lang("DLGUUSIASIAKAS_10");
		//else if(err == ERR_NEWWORKPLACE_5) cs = Props::i().lang("DLGUUSIASIAKAS_11");
		//else if(err == ERR_NEWWORKPLACE_6) cs = Props::i().lang("DLGUUSIASIAKAS_12");
		//else if(err == ERR_NEWWORKPLACE_7) cs = Props::i().lang("DLGUUSIASIAKAS_13");

		if(err > ERR_NEWWORKPLACE_0)
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return;
	}

	if(((CTaikaDlg*)(Props::e().m_pMainWnd))->pageListat.lisaaAsiakas(this) != RETURN_OK)
		return;

	CDialog::OnOK();
}

void DlgUusiAsiakas::OnCbnSelchangeCmbbiller()
{ m_sync &= ~SYNC_LASKUTTAJAT; }

void DlgUusiAsiakas::OnCbnEditchangeCmbbiller()
{ m_sync |= SYNC_LASKUTTAJAT; }

void DlgUusiAsiakas::OnEnChangeEdtname()
{ m_sync |= SYNC_ASIAKKAAT; }
