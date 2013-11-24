// DlgUusiRaportti.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "taikaDlg.h"
#include "Paivays.h"
#include "DlgUusiRaportti.h"
#include "Props.h"
#include "StringHelper_luokka.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgUusiRaportti dialog
DlgUusiRaportti::DlgUusiRaportti(CWnd* pParent /*=NULL*/)
	: CDialog(DlgUusiRaportti::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgUusiRaportti)
	//}}AFX_DATA_INIT
}

void DlgUusiRaportti::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgUusiRaportti)
	DDX_Control(pDX, IDC_STCTYPE, m_stcType);
	DDX_Control(pDX, IDC_CMBTYOTYYPPI, m_cmbTyotyyppi);
	DDX_Control(pDX, IDC_CMBTYONTEKIJA, m_cmbTyontekija);
	DDX_Control(pDX, IDC_CMBASIAKASRYHMA, m_cmbAsiakasryhma);
	DDX_Control(pDX, IDC_CMBASIAKAS, m_cmbAsiakas);
	DDX_Control(pDX, IDC_CMBLASKUTTAJA, m_cmbLaskuttaja);
	DDX_Control(pDX, IDC_STCQUESTION, m_stcQuestion);
	DDX_Control(pDX, PIC_QUESTION, m_picQuestion);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDTALOITUSAIKA, m_edtAloitusaika);
	DDX_Control(pDX, IDC_EDTLOPETUSAIKA, m_edtLopetusaika);
	DDX_Control(pDX, IDC_EDTMAARA, m_edtMaara);
	DDX_Control(pDX, IDC_CMBYKSIKKO, m_cmbYksikko);
	DDX_Control(pDX, IDC_EDTMYYNTIHINTA, m_edtMyyntihinta);
	DDX_Control(pDX, IDC_EDTKOKONAISHINTA, m_edtKokonaishinta);
	DDX_Control(pDX, IDC_EDTALVPROSENTTI, m_edtAlvprosentti);
	DDX_Control(pDX, IDC_STCMAARA, m_stcMaara);
	DDX_Control(pDX, IDOK, m_btnOK);
}

BEGIN_MESSAGE_MAP(DlgUusiRaportti, CDialog)
	//{{AFX_MSG_MAP(DlgUusiRaportti)
	ON_CBN_SELCHANGE(IDC_CMBASIAKASRYHMA, OnSelchangeCmbasiakasryhma)
	ON_CBN_EDITCHANGE(IDC_CMBASIAKAS, OnEditchangeCmbasiakas)
	ON_CBN_SELCHANGE(IDC_CMBASIAKAS, OnSelchangeCmbasiakas)
	ON_CBN_EDITCHANGE(IDC_CMBASIAKASRYHMA, OnEditchangeCmbasiakasryhma)
	ON_CBN_EDITCHANGE(IDC_CMBLASKUTTAJA, OnEditchangeCmblaskuttaja)
	ON_CBN_SELCHANGE(IDC_CMBLASKUTTAJA, OnSelchangeCmblaskuttaja)
	ON_CBN_EDITCHANGE(IDC_CMBTYONTEKIJA, OnEditchangeCmbtyontekija)
	ON_CBN_SELCHANGE(IDC_CMBTYONTEKIJA, OnSelchangeCmbtyontekija)
	ON_CBN_EDITCHANGE(IDC_CMBTYOTYYPPI, OnEditchangeCmbtyotyyppi)
	ON_CBN_SELCHANGE(IDC_CMBTYOTYYPPI, OnSelchangeCmbtyotyyppi)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDTALOITUSAIKA, &DlgUusiRaportti::OnEnChangeEdtaloitusaika)
	ON_EN_CHANGE(IDC_EDTLOPETUSAIKA, &DlgUusiRaportti::OnEnChangeEdtlopetusaika)
	ON_EN_CHANGE(IDC_EDTMAARA, &DlgUusiRaportti::OnEnChangeEdtmaara)
	ON_EN_CHANGE(IDC_EDTMYYNTIHINTA, &DlgUusiRaportti::OnEnChangeEdtmyyntihinta)
	ON_EN_CHANGE(IDC_EDTKOKONAISHINTA, &DlgUusiRaportti::OnEnChangeEdtkokonaishinta)
	ON_EN_CHANGE(IDC_EDTALVPROSENTTI, &DlgUusiRaportti::OnEnChangeEdtalvprosentti)
	ON_BN_CLICKED(IDC_RDCHARGED1, &DlgUusiRaportti::OnBnClickedCharged)
	ON_BN_CLICKED(IDC_RDCHARGED2, &DlgUusiRaportti::OnBnClickedCharged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgUusiRaportti message handlers

BOOL DlgUusiRaportti::OnInitDialog() 
{
    int i, s;
    DbSqlite db;
    Paivays paivays;
    SYSTEMTIME systemTime;
    CString cs, date, time;
    vector <CString> vect;

    CDialog::OnInitDialog();

	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGUUSIRAPORTTI_C1"));
	SetDlgItemText(IDC_STATIC2, Props::i().lang("DLGUUSIRAPORTTI_C2"));
	SetDlgItemText(IDC_STATIC3, Props::i().lang("DLGUUSIRAPORTTI_C3"));
	SetDlgItemText(IDC_STATIC4, Props::i().lang("DLGUUSIRAPORTTI_C4"));
	SetDlgItemText(IDC_STATIC5, Props::i().lang("DLGUUSIRAPORTTI_C5"));
	SetDlgItemText(IDC_STATIC6, Props::i().lang("DLGUUSIRAPORTTI_C6"));
	SetDlgItemText(IDC_STATIC7, Props::i().lang("DLGUUSIRAPORTTI_C7"));
	SetDlgItemText(IDC_STATIC8, Props::i().lang("DLGUUSIRAPORTTI_C8"));
	SetDlgItemText(IDC_STATIC9, Props::i().lang("DLGUUSIRAPORTTI_C9"));
	SetDlgItemText(IDC_STATIC10, Props::i().lang("DLGUUSIRAPORTTI_C10"));
	SetDlgItemText(IDC_STATIC11, Props::i().lang("DLGUUSIRAPORTTI_C11"));
	SetDlgItemText(IDC_RDCHARGED1, Props::i().lang("DLGUUSIRAPORTTI_C12"));
	SetDlgItemText(IDC_RDCHARGED2, Props::i().lang("DLGUUSIRAPORTTI_C13"));
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGUUSIRAPORTTI_C14"));

	m_init = TRUE;

	// m_pid = NULL -> uusi, != null -> muokkaus
	if(m_pid == NULL)
	{
	    m_picQuestion.SetIcon(LoadIcon(NULL, IDI_QUESTION));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSIRAPORTTI_1"));
		this->SetWindowText(Props::i().lang("DLGUUSIRAPORTTI_2"));
	}
	else
	{
	    m_picQuestion.SetIcon(LoadIcon(Props::e().m_hInstance, MAKEINTRESOURCE(IDI_EDIT)));
		m_btnOK.SetWindowText(Props::i().lang("DLGUUSIRAPORTTI_3"));
		this->SetWindowText(Props::i().lang("DLGUUSIRAPORTTI_4"));
	}

	if(m_tyyppi == ID_WORKUNIT)                                              // Työtyyppien tai tuotteiden nimet tietokannasta
	{
		m_stcQuestion.SetWindowText((m_pid == NULL ? Props::i().lang("DLGUUSIRAPORTTI_5") : Props::i().lang("DLGUUSIRAPORTTI_6")));
		m_stcType.SetWindowText(Props::i().lang("DLGUUSIRAPORTTI_7"));
		m_stcMaara.SetWindowText(Props::i().lang("DLGUUSIRAPORTTI_8"));
		s = (vect = db.haeTaulusta("WorkType", "Name", 1, WORKTYPE_POSITION_WORK, 1, "", "Type", "=", WORK)).size();
	}
	else
	{
		m_stcQuestion.SetWindowText((m_pid == NULL ? Props::i().lang("DLGUUSIRAPORTTI_9") : Props::i().lang("DLGUUSIRAPORTTI_10")));
		m_stcType.SetWindowText(Props::i().lang("DLGUUSIRAPORTTI_11"));
		m_stcMaara.SetWindowText(Props::i().lang("DLGUUSIRAPORTTI_12"));
		s = (vect = db.haeTaulusta("WorkType", "Name", 1, WORKTYPE_POSITION_WORK, 1, "", "Type", "=", PRODUCT)).size();
	}

	for(int i=0; i<s; i++) m_cmbTyotyyppi.AddString(vect[i]);
	db.findCBItem(FALSE, &m_cmbTyotyyppi, "WorkType", "Name", (m_pid != NULL ? m_pid->WorkType_id : ""));

	s = (vect = db.haeTaulusta("Region", "Name", 1, "position", 0)).size();  // Asiakasryhmien nimet tietokannasta
	for(i=0; i<s; i++) m_cmbAsiakasryhma.AddString(vect[i]);
	db.findCBItem(FALSE, &m_cmbAsiakasryhma, "Region", "Name", db.haeArvoID("WorkPlace", "Region_id", (m_pid != NULL ? m_pid->WorkPlace_id : "")));

	OnSelchangeCmbasiakasryhma();                                            // Asiakkaat asiakasryhmän perusteella
	db.findCBItem(FALSE, &m_cmbAsiakas, "WorkPlace", "Name", (m_pid != NULL ? m_pid->WorkPlace_id : ""));

    s = (vect = db.haeTaulusta("Worker", "Name", 1, "Name", 0)).size();		 // Työntekijöiden nimet tietokannasta
    for(i=0; i<s; i++) m_cmbTyontekija.AddString(vect[i]);
	db.findCBItem(FALSE, &m_cmbTyontekija, "Worker", "Name", (m_pid != NULL ? m_pid->Worker_id : ""));

    s = (vect = db.haeTaulusta("Biller", "Name", 1, "Name", 1, "", "Name", "<>", DFLT_BILLER)).size();  // Laskuttajien nimet tietokannasta
    for(i=0; i<s; i++) m_cmbLaskuttaja.AddString(vect[i]);
	db.findCBItem(FALSE, &m_cmbLaskuttaja, "Biller", "Name", (m_pid != NULL ? m_pid->Biller_id : ""));

    s = (vect = db.haeTaulusta("Units", "Unit", 1, "Unit", 0)).size();   // Yksiköiden nimet tietokannasta
    for(i=0; i<s; i++) m_cmbYksikko.AddString(vect[i]);
	if(m_tyyppi == ID_WORKUNIT)                                              // Työtyyppien tai tuotteiden nimet tietokannasta
	{
		m_ajat = StringHelper::parseInt(Props::i().get(OPTIONS_AJAT).c_str());
		if(m_ajat == TIME_MINUTES) m_cmbYksikko.SetWindowTextA(_UNIT_MIN_);
		else if(m_ajat == TIME_HOURS) m_cmbYksikko.SetWindowTextA(_UNIT_HOUR_);
		else if(m_ajat == TIME_CALLS) m_cmbYksikko.SetWindowTextA(Props::i().lang("_UNIT_CALL_"));
		m_cmbYksikko.EnableWindow(FALSE);

		if(m_ajat == TIME_CALLS)
		{
			m_edtMaara.SetWindowTextA("1");
			m_edtMaara.EnableWindow(FALSE);
		}
		else
		{
			m_edtMaara.SetWindowTextA((m_pid != NULL ? m_pid->UnitValue : "0"));
			m_edtMaara.EnableWindow(TRUE);
		}

		m_edtMyyntihinta.SetWindowTextA("0.00");	//
		m_edtMyyntihinta.EnableWindow(FALSE);
		m_edtKokonaishinta.SetWindowTextA("0.00");	//
		m_edtKokonaishinta.EnableWindow(FALSE);
		m_edtAlvprosentti.SetWindowTextA("0.00");	//
		m_edtAlvprosentti.EnableWindow(FALSE);
	}
	else
	{
		vect = getProduct();
		db.findCBItem(TRUE, &m_cmbYksikko, "", "", (m_pid != NULL ? m_pid->Unit : vect[1]));				//
		m_cmbYksikko.EnableWindow(TRUE);
		m_edtMaara.SetWindowTextA((m_pid != NULL ? db.fixFloat(m_pid->UnitValue, TRUE) : "0.00"));			//
		m_edtMaara.EnableWindow(TRUE);
		m_edtMyyntihinta.SetWindowTextA(db.fixFloat((m_pid != NULL ? m_pid->UnitPrice : vect[0]), TRUE));	//
		m_edtMyyntihinta.EnableWindow(TRUE);
		m_edtKokonaishinta.SetWindowTextA((m_pid != NULL ? db.fixFloat(m_pid->TotalPrice, TRUE) : "0.00"));	//
		m_edtKokonaishinta.EnableWindow(TRUE);
		m_edtAlvprosentti.SetWindowTextA((m_pid != NULL ? db.fixFloat(m_pid->Alv, TRUE) : vect[2]));		//
		m_edtAlvprosentti.EnableWindow(TRUE);
	}

	if(m_pid == NULL)
	{
		GetLocalTime(&systemTime);                     // Päiväys
		date.Format("%d", paivays.makeDate(systemTime.wYear, systemTime.wMonth, systemTime.wDay));
		time.Format("%d", systemTime.wHour * 60 + systemTime.wMinute);
		cs = paivays.date2string(date) + DATETIME_SEP + paivays.time2string(time);
		m_edtAloitusaika.SetWindowTextA(cs);
		m_edtLopetusaika.SetWindowTextA(cs);

		CheckRadioButton(IDC_RDCHARGED1, IDC_RDCHARGED2, IDC_RDCHARGED1);
	}
	else
	{
		m_edtAloitusaika.SetWindowTextA(paivays.date2string(m_pid->StartDate) + DATETIME_SEP + paivays.time2string(m_pid->StartTime));
		m_edtLopetusaika.SetWindowTextA(paivays.date2string(m_pid->EndDate) + DATETIME_SEP + paivays.time2string(m_pid->EndTime));

		CheckRadioButton(IDC_RDCHARGED1, IDC_RDCHARGED2, (m_pid->Charged == C_FALSE ? IDC_RDCHARGED1 : IDC_RDCHARGED2));
	}

	m_sync = 0;                                      // Listoihin ei ole lisätty uusia rivejä

	m_init = FALSE;

    return TRUE;
}

void DlgUusiRaportti::OnOK() 
{
	int dm;
	CString cs;
	Paivays paivays;
    pair <CString, CString> pari_s;
    pair <CString, CString> pari_e;
	float unitvalue;

    try
	{
		m_cmbAsiakasryhma.GetWindowText(m_region_name);
		if(m_region_name == "") throw(ERR_NEWREPORT_2);

		m_cmbAsiakas.GetWindowText(m_workplace_name);
		if(m_workplace_name == "") throw(ERR_NEWREPORT_3);

		m_cmbTyontekija.GetWindowText(m_worker_name);
		if(m_worker_name == "") throw(ERR_NEWREPORT_4);

		m_cmbTyotyyppi.GetWindowText(m_worktype_name);
		if(m_worktype_name == "") throw(ERR_NEWREPORT_5);

		m_cmbLaskuttaja.GetWindowText(m_biller_name);
		if(m_biller_name == "") throw(ERR_NEWREPORT_6);

		m_edtAloitusaika.GetWindowText(m_starttime);
		if(m_starttime == "") throw(ERR_NEWREPORT_7);

		m_edtLopetusaika.GetWindowText(m_endtime);
		if(m_endtime == "") throw(ERR_NEWREPORT_8);

		m_edtMaara.GetWindowText(m_unitvalue);
		if(m_unitvalue == "") throw(ERR_NEWREPORT_9);

		m_cmbYksikko.GetWindowText(m_unit);
		if(m_unit == "") throw(ERR_NEWREPORT_10);
		if(m_tyyppi == ID_SALESUNIT && (m_unit == _UNIT_MIN_ || m_unit == _UNIT_HOUR_)) throw(ERR_NEWREPORT_14);

		m_edtMyyntihinta.GetWindowText(m_unitprice);
		if(m_unitprice == "") throw(ERR_NEWREPORT_11);

		m_edtKokonaishinta.GetWindowText(m_totalprice);
		if(m_totalprice == "") throw(ERR_NEWREPORT_12);

		m_edtAlvprosentti.GetWindowText(m_alv);
		if(m_alv == "") throw(ERR_NEWREPORT_13);

		if((dm = GetCheckedRadioButton(IDC_RDCHARGED1, IDC_RDCHARGED2)) == 0) throw(ERR_NEWREPORT_15);
		m_charged = (dm == IDC_RDCHARGED1 ? C_FALSE : C_TRUE);

		// AJAT JA UNITVALUE (joka on aika tai hinta riippuen tilasta)
		unitvalue = atof(DbSqlite::fixFloat(m_unitvalue, TRUE));

		if((pari_s = paivays.str2pair(m_starttime)).first == "") throw(ERR_NEWREPORT_0);
		if((pari_e = paivays.str2pair(m_endtime)).first == "") throw(ERR_NEWREPORT_0);
		paivays.makeTimesLogical(pari_s, pari_e);			// 

		if(m_tyyppi == ID_WORKUNIT && m_ajat != TIME_CALLS)	// laske työaika annetuista ajoista
		{
			dm = paivays.caclTimeDiff(pari_s, pari_e);
			if(unitvalue > dm)								// syötetty aika suurempi kuin päiväysten erotus -> käytä annettua aikaa ja aseta lopetuspäiväys vastaamaan sitä
			{
				cs.Format("%.0f", unitvalue);
				pari_e = paivays.calcEndTime(cs, pari_s.first, pari_s.second);
			}
			else											// päiväysten erotus suurempi -> käytä aikana sitä
				unitvalue = dm;
		}

		m_StartDate = pari_s.first;							// 
		m_StartTime = pari_s.second;
		m_EndDate = pari_e.first;
		m_EndTime = pari_e.second;
		m_starttime = paivays.date2string(pari_s.first) + DATETIME_SEP + paivays.time2filetime(pari_s.second);		//
		m_endtime = paivays.date2string(pari_e.first) + DATETIME_SEP + paivays.time2filetime(pari_e.second);

		m_unitvalue.Format((m_tyyppi == ID_WORKUNIT ? "%.0f" : "%.2f"), unitvalue);

		// HINNAT / ALV
		m_unitprice = DbSqlite::fixFloat(m_unitprice, TRUE);
		m_totalprice = DbSqlite::fixFloat(m_totalprice, TRUE);
		m_alv = DbSqlite::fixFloat(m_alv, TRUE);
	}
    catch(int err)
	{
		if(err == ERR_NEWREPORT_2) cs = Props::i().lang("DLGUUSIRAPORTTI_13");
		else if(err == ERR_NEWREPORT_3) cs = Props::i().lang("DLGUUSIRAPORTTI_14");
		else if(err == ERR_NEWREPORT_4) cs = Props::i().lang("DLGUUSIRAPORTTI_15");
		else if(err == ERR_NEWREPORT_5) cs = Props::i().lang("DLGUUSIRAPORTTI_16");
		else if(err == ERR_NEWREPORT_6) cs = Props::i().lang("DLGUUSIRAPORTTI_17");
		else if(err == ERR_NEWREPORT_7) cs = Props::i().lang("DLGUUSIRAPORTTI_18");
		else if(err == ERR_NEWREPORT_8) cs = Props::i().lang("DLGUUSIRAPORTTI_19");
		else if(err == ERR_NEWREPORT_9) cs = Props::i().lang("DLGUUSIRAPORTTI_20");
		else if(err == ERR_NEWREPORT_10) cs = Props::i().lang("DLGUUSIRAPORTTI_21");
		else if(err == ERR_NEWREPORT_11) cs = Props::i().lang("DLGUUSIRAPORTTI_22");
		else if(err == ERR_NEWREPORT_12) cs = Props::i().lang("DLGUUSIRAPORTTI_23");
		else if(err == ERR_NEWREPORT_13) cs = Props::i().lang("DLGUUSIRAPORTTI_24");
		else if(err == ERR_NEWREPORT_14) cs = Props::i().lang("DLGUUSIRAPORTTI_25");
		else if(err == ERR_NEWREPORT_15) cs = Props::i().lang("DLGUUSIRAPORTTI_26");

		if(err > ERR_NEWREPORT_0)
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return;
	}

	if(((CTaikaDlg*)(Props::e().m_pMainWnd))->pageRaportit.lisaaTapahtuma(this) != RETURN_OK)
		return;

	CDialog::OnOK();
}

void DlgUusiRaportti::OnSelchangeCmbasiakasryhma() 
{
    int i, s;
    CString cs;
    DbSqlite db;
    vector <CString> vect;

    if((s = m_cmbAsiakasryhma.GetCurSel()) != CB_ERR)
	{
      m_cmbAsiakas.ResetContent();                       // Tyhjennä asiakaslista

      m_cmbAsiakasryhma.GetLBText(s, cs);                // Hae valitun asiakasryhmän id
      vect = db.haeTaulusta("Region", "id", 1, "", 1, "", "Name", "=", cs);
                                                         // Asiakkaiden nimet tietokannasta listaansa
	  s = (vect = db.haeTaulusta("WorkPlace", "DISTINCT Name", 1, "position", 1, "", "Region_id", "=", vect[0])).size();
      for(i=0; i<s; i++) m_cmbAsiakas.AddString(vect[i]);
      m_cmbAsiakas.SetCurSel(0);
	}

    m_sync &= ~SYNC_ASIAKASRYHMAT;         // Ei uusia asiakasryhmiä tai asiakkaita
    m_sync &= ~SYNC_ASIAKKAAT;
}

void DlgUusiRaportti::OnEditchangeCmbasiakasryhma() 
{ m_sync |=	SYNC_ASIAKASRYHMAT; }

void DlgUusiRaportti::OnSelchangeCmbasiakas() 
{ m_sync &= ~SYNC_ASIAKKAAT; }

void DlgUusiRaportti::OnEditchangeCmbasiakas() 
{ m_sync |= SYNC_ASIAKKAAT; }

void DlgUusiRaportti::OnSelchangeCmblaskuttaja() 
{ m_sync &= ~SYNC_LASKUTTAJAT; }

void DlgUusiRaportti::OnEditchangeCmblaskuttaja() 
{ m_sync |= SYNC_LASKUTTAJAT; }

void DlgUusiRaportti::OnSelchangeCmbtyontekija() 
{ m_sync &= ~SYNC_TYONTEKIJAT; }

void DlgUusiRaportti::OnEditchangeCmbtyontekija() 
{ m_sync |= SYNC_TYONTEKIJAT; }

void DlgUusiRaportti::OnSelchangeCmbtyotyyppi() 
{
	DbSqlite db;
	vector<CString> vect;

	if(m_tyyppi == ID_SALESUNIT)
	{
		vect = getProduct();
		m_edtMyyntihinta.SetWindowText(vect[0]);
		db.findCBItem(TRUE, &m_cmbYksikko, "", "", vect[1]);
		m_edtAlvprosentti.SetWindowText(vect[2]);
	}

	m_sync &= ~SYNC_TYOTYYPIT;
	m_sync &= ~SYNC_TUOTTEET;
	m_sync &= ~SYNC_TUOTERYHMAT;
}

void DlgUusiRaportti::OnEditchangeCmbtyotyyppi() 
{ if(m_tyyppi == ID_WORKUNIT) m_sync |= SYNC_TYOTYYPIT; else m_sync |= (SYNC_TUOTTEET|SYNC_TUOTERYHMAT); }

void DlgUusiRaportti::OnEnChangeEdtaloitusaika() {}
void DlgUusiRaportti::OnEnChangeEdtlopetusaika() {}
void DlgUusiRaportti::OnEnChangeEdtmaara() { setValues(0); }
void DlgUusiRaportti::OnEnChangeEdtmyyntihinta() { setValues(1); }
void DlgUusiRaportti::OnEnChangeEdtkokonaishinta() { setValues(2); }
void DlgUusiRaportti::OnEnChangeEdtalvprosentti() {}
void DlgUusiRaportti::setValues(int from)
{
	float val[3];
	CString cs[3];
	static BOOL editing = FALSE;

	if(editing || m_init) return;
	editing = TRUE;

	if(m_tyyppi == ID_WORKUNIT) {}
	else
	{
		m_edtMaara.GetWindowText(cs[0]);
		val[0] = atof(cs[0]);
		m_edtMyyntihinta.GetWindowText(cs[1]);
		val[1] = atof(cs[1]);
		m_edtKokonaishinta.GetWindowText(cs[2]);
		val[2] = atof(cs[2]);

		if(from == 0 || from == 1)
			val[2] = val[0] * val[1];
		else if(from == 2)
			val[1] = (val[0] != 0.0f ? val[2] / val[0] : 0.0f);

		if(from != 1)
		{
			cs[1].Format("%.2f", val[1]);
			m_edtMyyntihinta.SetWindowText(cs[1]);
		}
		if(from != 2)
		{
			cs[2].Format("%.2f", val[2]);
			m_edtKokonaishinta.SetWindowText(cs[2]);
		}
	}

	editing = FALSE;
}

vector <CString> DlgUusiRaportti::getProduct()
{
	CString cs;
	DbSqlite db;
	float sellprice;
    vector <CString> vect, vect_return;

	m_cmbTyotyyppi.GetWindowText(cs);
	if((vect = db.haeTaulusta("WorkType", "SellPrice, Unit, Alv", 3, "", 1, "", "Name", "=", cs)).size() > 0)
	{
		cs.Format("%.2f", atof(vect[0]));
		vect_return.push_back(cs);
		vect_return.push_back((vect[1] != _UNSET_ ? vect[1] : ""));
		vect_return.push_back((vect[2] != "" ? vect[2] : "0.00"));
	}
	else
	{
		vect_return.push_back("0.00");
		vect_return.push_back("");
		vect_return.push_back("0.00");
	}

	return vect_return;
}

void DlgUusiRaportti::OnBnClickedCharged()
{
    int s = GetCheckedRadioButton(IDC_RDCHARGED1, IDC_RDCHARGED2);
	m_charged = (s == IDC_RDCHARGED1 ? C_FALSE : C_TRUE);
    CheckRadioButton(IDC_RDCHARGED1, IDC_RDCHARGED2, s);
}

/*
// Funktio pointteri
void Foo(int anInt, double aDouble);

void Bar()
{
	void (*funcPtr)(int, double) = &Foo;
	(*funcPtr)( 1, 2.0 );
}

// Pointteri luokan jäsenfunktioon
class Foo
{
public:
	double One(long inVal);
	double Two(long inVal);
};

void main(int argc, char **argv)
{
	double (Foo::*funcPtr)(long) = &Foo::One;
	Foo aFoo;
	double result =(aFoo.*funcPtr)( 2 );
	
	return 0;
}
*/