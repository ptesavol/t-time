// DlgUusiTuote.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "taikaDlg.h"
#include "Props.h"
#include "DlgUusiTuote.h"

// DlgUusiTuote dialog
IMPLEMENT_DYNAMIC(DlgUusiTuote, CDialog)

DlgUusiTuote::DlgUusiTuote(CWnd* pParent /*=NULL*/)
	: CDialog(DlgUusiTuote::IDD, pParent)
{}

DlgUusiTuote::~DlgUusiTuote()
{}

void DlgUusiTuote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, PIC_QUESTION, m_picQuestion);
	DDX_Control(pDX, IDC_STCQUESTION, m_stcQuestion);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_EDTNAME, m_edtName);
	DDX_Control(pDX, IDC_EDTPRODUCTNUMBER, m_edtProductNumber);
	DDX_Control(pDX, IDC_CMBUNIT, m_cmbUnit);
	DDX_Control(pDX, IDC_EDTPURCHASEPRICE, m_edtPurchasePrice);
	DDX_Control(pDX, IDC_EDTSELLPRICE, m_edtSellPrice);
	DDX_Control(pDX, IDC_EDTALV, m_edtAlv);
}

BEGIN_MESSAGE_MAP(DlgUusiTuote, CDialog)
	ON_BN_CLICKED(IDOK, &DlgUusiTuote::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDTNAME, &DlgUusiTuote::OnEnChangeEdtname)
	ON_CBN_SELCHANGE(IDC_CMBUNIT, &DlgUusiTuote::OnCbnSelchangeCmbunit)
	ON_CBN_EDITCHANGE(IDC_CMBUNIT, &DlgUusiTuote::OnCbnEditchangeCmbunit)
END_MESSAGE_MAP()

// DlgUusiTuote message handlers
BOOL DlgUusiTuote::OnInitDialog() 
{
    int i, s;
    DbSqlite db;
    vector <CString> vect;

    CDialog::OnInitDialog();

	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITUOTE_C1"));
	SetDlgItemText(IDC_STATIC2, Props::i().lang("DLGUUSITUOTE_C2"));
	SetDlgItemText(IDC_STATIC3, Props::i().lang("DLGUUSITUOTE_C3"));
	SetDlgItemText(IDC_STATIC4, Props::i().lang("DLGUUSITUOTE_C4"));
	SetDlgItemText(IDC_STATIC5, Props::i().lang("DLGUUSITUOTE_C5"));
	SetDlgItemText(IDC_STATIC6, Props::i().lang("DLGUUSITUOTE_C6"));
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGUUSITUOTE_C7"));

	// m_pid = NULL -> uusi, != null -> muokkaus
	if(m_pid == NULL)
	{
	    m_picQuestion.SetIcon(LoadIcon(NULL, IDI_QUESTION));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSITUOTE_1"));
		this->SetWindowText(Props::i().lang("DLGUUSITUOTE_2"));
		m_stcQuestion.SetWindowText(Props::i().lang("DLGUUSITUOTE_3"));
	}
	else
	{
	    m_picQuestion.SetIcon(LoadIcon(Props::e().m_hInstance, MAKEINTRESOURCE(IDI_EDIT)));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSITUOTE_4"));
		this->SetWindowText(Props::i().lang("DLGUUSITUOTE_5"));
		m_stcQuestion.SetWindowText(Props::i().lang("DLGUUSITUOTE_6"));
	}

	m_edtName.SetWindowTextA((m_pid != NULL ? m_pid->Name : ""));
	m_edtProductNumber.SetWindowTextA((m_pid != NULL ? m_pid->ProductNumber : ""));

    s = (vect = db.haeTaulusta("Units", "Unit", 1, "Unit", 0)).size();										//
    for(i=0; i<s; i++) m_cmbUnit.AddString(vect[i]);
	db.findCBItem(TRUE, &m_cmbUnit, "", "", (m_pid != NULL ? m_pid->Unit : ""));
	m_edtPurchasePrice.SetWindowTextA((m_pid != NULL ? db.fixFloat(m_pid->PurchasePrice, FALSE) : "0.00"));	//
	m_edtSellPrice.SetWindowTextA((m_pid != NULL ? db.fixFloat(m_pid->SellPrice, FALSE) : "0.00"));			//
	m_edtAlv.SetWindowTextA((m_pid != NULL ? db.fixFloat(m_pid->Alv, FALSE) : "0.00"));						//

	m_sync = 0;                                      // Listoihin ei ole lisätty uusia rivejä

    return TRUE;
}
void DlgUusiTuote::OnBnClickedOk()
{
	CString cs;

	try
	{
		m_edtName.GetWindowText(m_name);
		if(m_name == "") throw(ERR_NEWPRODUCT_1);

		m_edtProductNumber.GetWindowText(m_productnumber);
		//if(m_productnumber == "") throw(ERR_NEWPRODUCT_2);

		m_cmbUnit.GetWindowText(m_unit);
		if(m_unit == "") throw(ERR_NEWPRODUCT_3);

		m_edtPurchasePrice.GetWindowText(m_purchaseprice);
		//if(m_purchaseprice == "") throw(ERR_NEWPRODUCT_4);

		m_edtSellPrice.GetWindowText(m_sellprice);
		//if(m_sellprice == "") throw(ERR_NEWPRODUCT_5);

		m_edtAlv.GetWindowText(m_alv);
		//if(m_alv == "") throw(ERR_NEWPRODUCT_6);

		m_purchaseprice = DbSqlite::fixFloat(m_purchaseprice, FALSE);
		m_sellprice = DbSqlite::fixFloat(m_sellprice, FALSE);
		m_alv = DbSqlite::fixFloat(m_alv, FALSE);
	}
	catch(int err)
	{
		if(err == ERR_NEWPRODUCT_1) cs = Props::i().lang("DLGUUSITUOTE_7");
		//else if(err == ERR_NEWPRODUCT_2) cs = Props::i().lang("DLGUUSITUOTE_8");
		else if(err == ERR_NEWPRODUCT_3) cs = Props::i().lang("DLGUUSITUOTE_9");
		//else if(err == ERR_NEWPRODUCT_4) cs =	Props::i().lang("DLGUUSITUOTE_10");
		//else if(err == ERR_NEWPRODUCT_5) cs = Props::i().lang("DLGUUSITUOTE_11");
		//else if(err == ERR_NEWPRODUCT_6) cs = Props::i().lang("DLGUUSITUOTE_12");

		if(err > ERR_NEWPRODUCT_0)
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return;
	}

	if(((CTaikaDlg*)(Props::e().m_pMainWnd))->pageListat.lisaaTuote(this) != RETURN_OK)
		return;

	CDialog::OnOK();
}

void DlgUusiTuote::OnEnChangeEdtname()
{ m_sync |= SYNC_TUOTTEET; }

void DlgUusiTuote::OnCbnSelchangeCmbunit()
{ /*m_sync &= ~SYNC_;*/ }

void DlgUusiTuote::OnCbnEditchangeCmbunit()
{ /*m_sync |= SYNC_;*/ }
