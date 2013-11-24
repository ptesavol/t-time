// DlgSiivoaTietokanta.cpp : implementation file
//

#include "stdafx.h"
#include "taika.h"
#include "DbSqlite.h"
#include "DlgSiivoaTietokanta.h"
#include "Props.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSiivoaTietokanta dialog


DlgSiivoaTietokanta::DlgSiivoaTietokanta(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSiivoaTietokanta::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSiivoaTietokanta)
	//}}AFX_DATA_INIT
}


void DlgSiivoaTietokanta::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSiivoaTietokanta)
	DDX_Control(pDX, IDC_CHKLASKUTTAMATTOMATMYYNNIT, m_chkLaskuttamattomatMyynnit);
	DDX_Control(pDX, IDC_CHKLASKUTETUTMYYNNIT, m_chkLaskutetutMyynnit);
	DDX_Control(pDX, IDC_CHKTUOTTEET, m_chkTuotteet);
	DDX_Control(pDX, IDC_CHKTUOTERYMAT, m_chkTuoteryhmat);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BTNPOISTA, m_btnPoista);
	DDX_Control(pDX, IDC_STCINFO, m_stcInfo);
	DDX_Control(pDX, IDC_CHKLASKUTTAMATTOMATTYOAJAT, m_chkLaskuttamattomatTyoajat);
	DDX_Control(pDX, IDC_CHKLASKUTETUTTYOAJAT, m_chkLaskutetutTyoajat);
	DDX_Control(pDX, IDC_CHKTYOTYYPIT, m_chkTyotyypit);
	DDX_Control(pDX, IDC_CHKTYONTEKIJAT, m_chkTyontekijat);
	DDX_Control(pDX, IDC_CHKTYOMATKAT, m_chkTyomatkat);
	DDX_Control(pDX, IDC_CHKLASKUTTAJAT, m_chkLaskuttajat);
	DDX_Control(pDX, IDC_CHKASIAKKAAT, m_chkAsiakkaat);
	DDX_Control(pDX, IDC_CHKASIAKASRYHMAT, m_chkAsiakasryhmat);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgSiivoaTietokanta, CDialog)
	//{{AFX_MSG_MAP(DlgSiivoaTietokanta)
	ON_BN_CLICKED(IDC_BTNPOISTA, OnBtnpoista)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSiivoaTietokanta message handlers
BOOL DlgSiivoaTietokanta::OnInitDialog() 
{
    CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C1"));
	SetDlgItemText(IDC_STATIC1 , Props::i().lang("DLGSIIVOATIETOKANTA_C2"));
	m_chkLaskuttamattomatTyoajat.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C3"));
	m_chkLaskutetutTyoajat.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C4"));
	m_chkLaskuttamattomatMyynnit.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C5"));
	m_chkLaskutetutMyynnit.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C6"));
	m_chkTyomatkat.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C7"));
	m_chkAsiakasryhmat.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C8"));
	m_chkAsiakkaat.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C9"));
	m_chkTuoteryhmat.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C10"));
	m_chkTuotteet.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C11"));
	m_chkTyotyypit.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C12"));
	m_chkTyontekijat.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C13"));
	m_chkLaskuttajat.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C14"));
	m_btnPoista.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C15"));
	m_btnCancel.SetWindowText(Props::i().lang("DLGSIIVOATIETOKANTA_C16"));

    if(Props::e().m_db_path == "")
	{
      MessageBox(Props::i().lang("DLGSIIVOATIETOKANTA_1") , Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      EndDialog(0);
	}

    m_siivottu = FALSE;

    // Värillinen tausta info-tekstille. Oletuksena taustan värinen.
    m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), "");

    return TRUE;
}


void DlgSiivoaTietokanta::OnBtnpoista() 
{
    DbSqlite db;
    CString sql;
    int i, s, cnv;
    vector <CString> vect;
    vector <CString> r_vect;

    if(MessageBox(Props::i().lang("DLGSIIVOATIETOKANTA_2"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_YESNO) == IDNO) return;

    m_chkLaskuttamattomatTyoajat.EnableWindow(FALSE);
    m_chkLaskutetutTyoajat.EnableWindow(FALSE);
    m_chkLaskuttamattomatMyynnit.EnableWindow(FALSE);
    m_chkLaskutetutMyynnit.EnableWindow(FALSE);
    m_chkTyomatkat.EnableWindow(FALSE);
    m_chkAsiakasryhmat.EnableWindow(FALSE);
    m_chkAsiakkaat.EnableWindow(FALSE);
    m_chkTyontekijat.EnableWindow(FALSE);
    m_chkLaskuttajat.EnableWindow(FALSE);
    m_chkTyotyypit.EnableWindow(FALSE);
    m_chkTuoteryhmat.EnableWindow(FALSE);
    m_chkTuotteet.EnableWindow(FALSE);
    m_btnPoista.EnableWindow(FALSE);
    m_btnCancel.EnableWindow(FALSE);

    try
	{
      if(m_chkLaskuttamattomatTyoajat.GetCheck() == 1) // Poista laskuttamattomat työajat
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_3"));
	    sql.Format("DELETE FROM WorkUnit WHERE Charged='%s' AND Type='%s';", C_FALSE, ID_WORKUNIT);
        if(db.freeSQLStatement(sql, FALSE) != RETURN_OK) throw(0);
	  }

      if(m_chkLaskutetutTyoajat.GetCheck() == 1)     // Poista laskutetut työajat
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_4"));
	    sql.Format("DELETE FROM WorkUnit WHERE Charged='%s' AND Type='%s';", C_TRUE, ID_WORKUNIT);
        if(db.freeSQLStatement(sql, FALSE) != RETURN_OK) throw(0);
	  }

      if(m_chkLaskuttamattomatMyynnit.GetCheck() == 1) // Poista laskuttamattomat myynnit
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_5"));
	    sql.Format("DELETE FROM WorkUnit WHERE Charged='%s' AND Type='%s';", C_FALSE, ID_SALESUNIT);
        if(db.freeSQLStatement(sql, FALSE) != RETURN_OK) throw(0);
	  }

      if(m_chkLaskutetutMyynnit.GetCheck() == 1)     // Poista laskutetut työajat
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_6"));
	    sql.Format("DELETE FROM WorkUnit WHERE Charged='%s' AND Type='%s';", C_TRUE, ID_SALESUNIT);
        if(db.freeSQLStatement(sql, FALSE) != RETURN_OK) throw(0);
	  }

      if(m_chkTyomatkat.GetCheck() == 1)             // Poista työmatkat
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_7"));
        if(db.poistaYleinen("TravelUnit", "", "", TRUE, "") != RETURN_OK) throw(0);
	  }

      // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // 
      if(m_chkAsiakkaat.GetCheck() == 1)             // Poista turhat asiakkaat
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_8"));

        s = (r_vect = db.freeQuery("SELECT id FROM WorkPlace WHERE id NOT IN (SELECT DISTINCT WorkPlace_id FROM WorkUnit);", 1)).size();
        for(i=0; i<s; i++) {                             // :: poista jos ei ole käytetty yhdessäkään WorkUnit-taulun rivissä
          if(db.poistaYleinen("WorkPlace", "id", r_vect[i], TRUE, "") != RETURN_OK) throw(0); }

        s = (r_vect = db.haeTaulusta("Region", "id", 1, "", 0)).size();
        for(i=0; i<s; i++)                               // :: järjestetään positionit
          if(db.jarjestaPosition("WorkPlace", "Region_id", r_vect[i], "position", TRUE) != RETURN_OK) throw(0);
	  }

      // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // 
      if(m_chkAsiakasryhmat.GetCheck() == 1)         // Poista turhat asiakasryhmät
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_9"));

        s = (r_vect = db.freeQuery("SELECT id FROM region WHERE id NOT IN (SELECT DISTINCT region_id FROM WorkPlace);", 1)).size();
        for(i=0; i<s; i++) {                             // : poista jos ei ole käytetty yhdessäkään WorkPlace-taulun rivissä
          if(db.poistaYleinen("Region", "id", r_vect[i], TRUE, "") != RETURN_OK) throw(0); }

        if(db.jarjestaPosition("Region", "", "", "position", TRUE) != RETURN_OK) throw(0); // position!!!
	  }

      // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // 
      if(m_chkTyontekijat.GetCheck() == 1)           // Poista turhat työntekijät
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_10"));

        s = (r_vect = db.haeTaulusta("Worker", "id", 1, "", 0)).size();
        for(i=0, cnv = 0; i<s; i++)                      // ::: poista jos ei ole käytetty yhdessäkään WorkUnit- tai TravelUnit-taulun rivissä
		{
          if((vect = db.haeTaulusta("WorkUnit", "count(id)", 1, "", 1, "", "Worker_id", "=", r_vect[i])).size() > 0)
            cnv = atoi(vect[0]);
          if((vect = db.haeTaulusta("TravelUnit", "count(id)", 1, "", 1, "", "Worker_id", "=", r_vect[i])).size() > 0)
            cnv += atoi(vect[0]);

          if(cnv == 0) {                                 // :::
            if(db.poistaYleinen("Worker", "id", r_vect[i], TRUE, "") != RETURN_OK) throw(0); }
		}
	  }

      // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // 
      if(m_chkLaskuttajat.GetCheck() == 1)           // Poista turhat laskuttajat
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_11"));

        s = (r_vect = db.haeTaulusta("Biller", "id", 1, "", 1, "", "Name", "<>", DFLT_BILLER)).size();
        for(i=0, cnv= 0; i<s; i++)                        // :::: poista jos ei ole käytetty yhdessäkään WorkUnit- tai TravelUnit-taulun rivissä
		{
          if((vect = db.haeTaulusta("WorkUnit", "count(id)", 1, "", 1, "", "Biller_id", "=", r_vect[i])).size() > 0)
            cnv = atoi(vect[0]);
          if((vect = db.haeTaulusta("TravelUnit", "count(id)", 1, "", 1, "", "Biller_id", "=", r_vect[i])).size() > 0)
            cnv += atoi(vect[0]);

          if(cnv == 0) {                                 // ::::
            if(db.poistaYleinen("Biller", "id", r_vect[i], TRUE, "") != RETURN_OK) throw(0); }
		}
	  }

      // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // 
      if(m_chkTyotyypit.GetCheck() == 1)             // Poista turhat työtyypit
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_12"));

        s = (r_vect = db.freeQuery("SELECT id FROM WorkType WHERE Type='WORK' AND id NOT IN (SELECT DISTINCT WorkType_id FROM WorkUnit);", 1)).size();
        for(i=0; i<s; i++) {                             // ::::: poista jos ei ole käytetty yhdessäkään WorkUnit-taulun rivissä
          if(db.poistaYleinen("WorkType", "id", r_vect[i], TRUE, "") != RETURN_OK) throw(0); }

        if(db.jarjestaPosition("WorkType", WORKTYPE_TYPE, WORK, WORKTYPE_POSITION_WORK, TRUE) != RETURN_OK) throw(0);
	  }

      // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // 
      if(m_chkTuotteet.GetCheck() == 1)              // Poista turhat tuotteet
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_13"));

        s = (r_vect = db.freeQuery("SELECT id FROM WorkType WHERE Type='PRODUCT' AND id NOT IN (SELECT DISTINCT WorkType_id FROM WorkUnit);", 1)).size();
        for(i=0; i<s; i++) {                             // :: poista jos ei ole käytetty yhdessäkään WorkUnit-taulun rivissä
          if(db.poistaYleinen("WorkType", "id", r_vect[i], TRUE, "") != RETURN_OK) throw(0); }

        s = (r_vect = db.haeTaulusta("ProductGroup", "id", 1, "", 0)).size();
        for(i=0; i<s; i++)                     // :: järjestetään positionit
          if(db.jarjestaPosition("WorkType", "ProductGroup_id", r_vect[i], WORKTYPE_POSITION_PRODUCT, TRUE) != RETURN_OK) throw(0);
	  }

      // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // 
      if(m_chkTuoteryhmat.GetCheck() == 1)           // Poista turhat tuoteryhmät
	  {
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_14"));

        s = (r_vect = db.freeQuery("SELECT id FROM ProductGroup WHERE id NOT IN (SELECT DISTINCT id FROM WorkType);", 1)).size();
        for(i=0; i<s; i++) {                             // ::::: poista jos ei ole käytetty yhdessäkään WorkType-taulun rivissä
          if(db.poistaYleinen("ProductGroup", "id", r_vect[i], TRUE, "") != RETURN_OK) throw(0); }

        if(db.jarjestaPosition("ProductGroup", "", "", "position", TRUE) != RETURN_OK) throw(0); // position!!!
	  }

      // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // 
	  // Yksiköt? !_UNIT_MIN_

      m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGSIIVOATIETOKANTA_15"));
      db.vacuum(Props::e().m_db_path);

      m_stcInfo.coloredInfo(LIGHTGREEN, Props::i().lang("DLGSIIVOATIETOKANTA_16"));
	}
    catch(int err)
	{
      if(err > 0)
        MessageBox(Props::i().lang("DLGSIIVOATIETOKANTA_17"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  m_stcInfo.coloredInfo(LIGHTRED, Props::i().lang("DLGSIIVOATIETOKANTA_18"));
	}

    m_chkLaskuttamattomatTyoajat.EnableWindow(TRUE);
    m_chkLaskutetutTyoajat.EnableWindow(TRUE);
    m_chkLaskuttamattomatMyynnit.EnableWindow(TRUE);
    m_chkLaskutetutMyynnit.EnableWindow(TRUE);
    m_chkTyomatkat.EnableWindow(TRUE);
    m_chkAsiakasryhmat.EnableWindow(TRUE);
    m_chkAsiakkaat.EnableWindow(TRUE);
    m_chkTyontekijat.EnableWindow(TRUE);
    m_chkLaskuttajat.EnableWindow(TRUE);
    m_chkTyotyypit.EnableWindow(TRUE);
    m_chkTuoteryhmat.EnableWindow(TRUE);
    m_chkTuotteet.EnableWindow(TRUE);
    m_btnPoista.EnableWindow(TRUE);
    m_btnCancel.EnableWindow(TRUE);

    m_chkLaskuttamattomatTyoajat.SetCheck(0);
    m_chkLaskutetutTyoajat.SetCheck(0);
    m_chkLaskuttamattomatMyynnit.SetCheck(0);
    m_chkLaskutetutMyynnit.SetCheck(0);
    m_chkTyomatkat.SetCheck(0);
    m_chkAsiakasryhmat.SetCheck(0);
    m_chkAsiakkaat.SetCheck(0);
    m_chkTyontekijat.SetCheck(0);
    m_chkLaskuttajat.SetCheck(0);
    m_chkTyotyypit.SetCheck(0);
    m_chkTuoteryhmat.SetCheck(0);
    m_chkTuotteet.SetCheck(0);

    m_siivottu = TRUE;
}

void DlgSiivoaTietokanta::OnCancel() 
{
    if(m_siivottu) EndDialog(IDOK);
    else EndDialog(IDCANCEL);

	//CDialog::OnCancel();
}
