// DlgUusiTyomatka.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "taikaDlg.h"
#include "DlgUusiTyomatka.h"
#include "Paivays.h"
#include "DbSqlite.h"
#include "Props.h"

// DlgUusiTyomatka dialog
IMPLEMENT_DYNAMIC(DlgUusiTyomatka, CDialog)

DlgUusiTyomatka::DlgUusiTyomatka(CWnd* pParent /*=NULL*/)
	: CDialog(DlgUusiTyomatka::IDD, pParent)
{}

DlgUusiTyomatka::~DlgUusiTyomatka()
{}

void DlgUusiTyomatka::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBWORKER, m_cmbWorker);
	DDX_Control(pDX, IDC_EDTSTARTMETER, m_edtStartMeter);
	DDX_Control(pDX, IDC_EDTENDMETER, m_edtEndMeter);
	DDX_Control(pDX, IDC_EDTPRIVATE, m_edtPrivate);
	DDX_Control(pDX, IDC_EDTSTARTTIME, m_edtStartTime);
	DDX_Control(pDX, IDC_EDTENDTIME, m_edtEndTime);
	DDX_Control(pDX, IDC_EDTSTARTPLACE, m_edtStartPlace);
	DDX_Control(pDX, IDC_EDTENDPLACE, m_edtEndPlace);
	DDX_Control(pDX, IDC_EDTPURPOSE, m_edtPurpose);
	DDX_Control(pDX, IDC_CMBBILLER, m_cmbBiller);
	DDX_Control(pDX, PIC_QUESTION, m_picQuestion);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_STCQUESTION, m_stcQuestion);
}

BEGIN_MESSAGE_MAP(DlgUusiTyomatka, CDialog)
	ON_BN_CLICKED(IDOK, &DlgUusiTyomatka::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_CMBWORKER, &DlgUusiTyomatka::OnCbnSelchangeCmbworker)
	ON_CBN_EDITCHANGE(IDC_CMBWORKER, &DlgUusiTyomatka::OnCbnEditchangeCmbworker)
	ON_CBN_SELCHANGE(IDC_CMBBILLER, &DlgUusiTyomatka::OnCbnSelchangeCmbbiller)
	ON_CBN_EDITCHANGE(IDC_CMBBILLER, &DlgUusiTyomatka::OnCbnEditchangeCmbbiller)
END_MESSAGE_MAP()

// DlgUusiTyomatka message handlers
BOOL DlgUusiTyomatka::OnInitDialog() 
{
    int i, s;
    DbSqlite db;
    Paivays paivays;
    SYSTEMTIME systemTime;
    CString cs, date, time;
    vector <CString> vect;

    CDialog::OnInitDialog();

	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITYOMATKA_C1"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITYOMATKA_C2"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITYOMATKA_C3"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITYOMATKA_C4"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITYOMATKA_C5"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITYOMATKA_C6"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITYOMATKA_C7"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITYOMATKA_C8"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITYOMATKA_C9"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSITYOMATKA_C10"));
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGUUSITYOMATKA_C11"));

	// m_pid = NULL -> uusi, != null -> muokkaus
	if(m_pid == NULL)
	{
	    m_picQuestion.SetIcon(LoadIcon(NULL, IDI_QUESTION));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSITYOMATKA_1"));
		this->SetWindowText(Props::i().lang("DLGUUSITYOMATKA_2"));
		m_stcQuestion.SetWindowText(Props::i().lang("DLGUUSITYOMATKA_3"));
	}
	else
	{
	    m_picQuestion.SetIcon(LoadIcon(Props::e().m_hInstance, MAKEINTRESOURCE(IDI_EDIT)));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSITYOMATKA_4"));
		this->SetWindowText(Props::i().lang("DLGUUSITYOMATKA_5"));
		m_stcQuestion.SetWindowText(Props::i().lang("DLGUUSITYOMATKA_6"));
	}

    s = (vect = db.haeTaulusta("Worker", "Name", 1, "Name", 0)).size();		 // Työntekijöiden nimet tietokannasta
	for(int i=0; i<s; i++) m_cmbWorker.AddString(vect[i]);
	db.findCBItem(FALSE, &m_cmbWorker, "Worker", "Name", (m_pid != NULL ? m_pid->Worker_id : ""));

    s = (vect = db.haeTaulusta("Biller", "Name", 1, "Name", 1, "", "Name", "<>", DFLT_BILLER)).size();  // Laskuttajien nimet tietokannasta
    for(i=0; i<s; i++) m_cmbBiller.AddString(vect[i]);
	db.findCBItem(FALSE, &m_cmbBiller, "Biller", "Name", (m_pid != NULL ? m_pid->Biller_id : ""));

	m_edtStartMeter.SetWindowTextA((m_pid != NULL ? db.fixFloat(m_pid->StartMeter, TRUE) : "0.00"));
	m_edtEndMeter.SetWindowTextA((m_pid != NULL ? db.fixFloat(m_pid->EndMeter, TRUE) : "0.00"));
	m_edtPrivate.SetWindowTextA((m_pid != NULL ? db.fixFloat(m_pid->Private, TRUE) : "0.00"));
	m_edtStartPlace.SetWindowTextA((m_pid != NULL ? m_pid->StartPlace : ""));
	m_edtEndPlace.SetWindowTextA((m_pid != NULL ? m_pid->EndPlace : ""));
	m_edtPurpose.SetWindowTextA((m_pid != NULL ? m_pid->Purpose : ""));

	if(m_pid == NULL)
	{
		GetLocalTime(&systemTime);                     // Päiväys
		date.Format("%d", paivays.makeDate(systemTime.wYear, systemTime.wMonth, systemTime.wDay));
		time.Format("%d", systemTime.wHour * 60 + systemTime.wMinute);
		cs = paivays.date2string(date) + DATETIME_SEP + paivays.time2string(time);
		m_edtStartTime.SetWindowTextA(cs);
		m_edtEndTime.SetWindowTextA(cs);
	}
	else
	{
		m_edtStartTime.SetWindowTextA(paivays.date2string(m_pid->StartDate) + DATETIME_SEP + paivays.time2string(m_pid->StartTime));
		m_edtEndTime.SetWindowTextA(paivays.date2string(m_pid->EndDate) + DATETIME_SEP + paivays.time2string(m_pid->EndTime));
	}

	m_sync = 0;                                      // Listoihin ei ole lisätty uusia rivejä

    return TRUE;
}

void DlgUusiTyomatka::OnBnClickedOk()
{
	CString cs;
	Paivays paivays;
	float sm, em, pr;
    pair <CString, CString> pari_s;
    pair <CString, CString> pari_e;

	try
	{
		m_cmbWorker.GetWindowText(m_worker_name);
		if(m_worker_name == "") throw(ERR_NEWTRAVEL_1);

		m_cmbBiller.GetWindowText(m_biller_name);
		if(m_biller_name == "") throw(ERR_NEWTRAVEL_2);

		m_edtStartMeter.GetWindowText(m_startmeter);
		if(m_startmeter == "") throw(ERR_NEWTRAVEL_3);

		m_edtEndMeter.GetWindowText(m_endmeter);
		if(m_endmeter == "") throw(ERR_NEWTRAVEL_4);

		m_edtPrivate.GetWindowText(m_private);
		if(m_private == "") throw(ERR_NEWTRAVEL_5);

		m_edtStartTime.GetWindowText(m_starttime);
		if(m_starttime == "") throw(ERR_NEWTRAVEL_6);

		m_edtEndTime.GetWindowText(m_endtime);
		if(m_endtime == "") throw(ERR_NEWTRAVEL_7);

		m_edtStartPlace.GetWindowText(m_startplace);
		if(m_startplace == "") throw(ERR_NEWTRAVEL_8);

		m_edtEndPlace.GetWindowText(m_endplace);
		if(m_endplace == "") throw(ERR_NEWTRAVEL_9);

		m_edtPurpose.GetWindowText(m_purpose);
		if(m_purpose == "") throw(ERR_NEWTRAVEL_10);

		// AJAT
		if((pari_s = paivays.str2pair(m_starttime)).first == "") throw(ERR_NEWTRAVEL_0);
		if((pari_e = paivays.str2pair(m_endtime)).first == "") throw(ERR_NEWTRAVEL_0);
		paivays.makeTimesLogical(pari_s, pari_e);			//

		m_StartDate = pari_s.first;							// 
		m_StartTime = pari_s.second;
		m_EndDate = pari_e.first;
		m_EndTime = pari_e.second;
		m_starttime = paivays.date2string(pari_s.first) + DATETIME_SEP + paivays.time2filetime(pari_s.second);		//
		m_endtime = paivays.date2string(pari_e.first) + DATETIME_SEP + paivays.time2filetime(pari_e.second);

		// MITTARILUKEMAT
		sm = abs(atof(DbSqlite::fixFloat(m_startmeter, TRUE)));
		em = abs(atof(DbSqlite::fixFloat(m_endmeter, TRUE)));
		if(em < sm) { pr = em; em = sm; sm = pr;}
		if(em == 0.0f) throw(ERR_NEWTRAVEL_11);

		pr = atof(DbSqlite::fixFloat(m_private, TRUE));

		m_startmeter.Format("%.2f", sm);
		m_endmeter.Format("%.2f", em);
		m_private.Format("%.2f", pr);
	}
	catch(int err)
	{
		if(err == ERR_NEWTRAVEL_1) cs = Props::i().lang("DLGUUSITYOMATKA_7");
		else if(err == ERR_NEWTRAVEL_2) cs = Props::i().lang("DLGUUSITYOMATKA_8");
		else if(err == ERR_NEWTRAVEL_3) cs = Props::i().lang("DLGUUSITYOMATKA_9");
		else if(err == ERR_NEWTRAVEL_4) cs = Props::i().lang("DLGUUSITYOMATKA_10");
		else if(err == ERR_NEWTRAVEL_5) cs = Props::i().lang("DLGUUSITYOMATKA_11");
		else if(err == ERR_NEWTRAVEL_6) cs = Props::i().lang("DLGUUSITYOMATKA_12");
		else if(err == ERR_NEWTRAVEL_7) cs = Props::i().lang("DLGUUSITYOMATKA_13");
		else if(err == ERR_NEWTRAVEL_8) cs = Props::i().lang("DLGUUSITYOMATKA_14");
		else if(err == ERR_NEWTRAVEL_9) cs = Props::i().lang("DLGUUSITYOMATKA_15");
		else if(err == ERR_NEWTRAVEL_10) cs = Props::i().lang("DLGUUSITYOMATKA_16");
		else if(err == ERR_NEWTRAVEL_11) cs = Props::i().lang("DLGUUSITYOMATKA_17");

		if(err > ERR_NEWTRAVEL_0)
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return;
	}

	if(((CTaikaDlg*)(Props::e().m_pMainWnd))->pageTyomatkat.lisaaUusi(this) != RETURN_OK)
		return;

	CDialog::OnOK();
}

void DlgUusiTyomatka::OnCbnSelchangeCmbworker()
{ m_sync &= ~SYNC_TYONTEKIJAT; }

void DlgUusiTyomatka::OnCbnEditchangeCmbworker()
{ m_sync |= SYNC_TYONTEKIJAT; }

void DlgUusiTyomatka::OnCbnSelchangeCmbbiller()
{ m_sync &= ~SYNC_LASKUTTAJAT; }

void DlgUusiTyomatka::OnCbnEditchangeCmbbiller()
{ m_sync |= SYNC_LASKUTTAJAT; }
