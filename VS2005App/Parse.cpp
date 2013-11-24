// Parse.cpp: implementation of the Parse class.
//
#include "stdafx.h"
#include "taika.h"
#include "Parse.h"
#include "Props.h"
#include "TaikaDlg.h"
#include "Buffer.h"
#include "Parse.h"
#include <io.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Parse::Parse()
{}

Parse::~Parse()
{}

//////////////////////////////////////////////////////////////////////
// Member functions
//////////////////////////////////////////////////////////////////////
void Parse::parseSaapuneet(int tila)
{
    static DlgParseInfo dlg;

    int s = 0;
    long hFile;
    __int32 fe = 0;
    struct _finddata_t c_file;
    CString find, path;

    path = Props::e().m_app_path + Props::i().lang("PARSE_1");    // Onko tiedostoja?
    find = path + "*.*";
    hFile = _findfirst((LPCTSTR)find, &c_file);
    while(fe != -1) {
      if(!(c_file.attrib & _A_SUBDIR)) s++;
      fe = _findnext(hFile, &c_file); }
    if(s == 0) return;

    // Parsitaan saapuneet kansion tiedostot tilan mukaisesti
    if(dlg.GetSafeHwnd() == NULL)
	{
      dlg.m_tila = tila;
      dlg.DoModal();
	}
    else
      dlg.AddFiles();
}

BOOL Parse::parseTTI(CString path, CString filename, int como, DlgParseInfo *pdlg)
{
    int ret;
    BOOL cm_tila = TRUE;
    DWORD e, r;
    DbSqlite db;
    CString errstr, open, cs;
    HANDLE hfile = NULL;
    char *pmem = NULL;
    string apu, worker, biller, workplace, worktype, reportdate;
    Tokenizer *pTokenizer = NULL;
    vector<string> *pvect;
    vector <CString> vect;

    // Lisätään työt tietokannan WorkUnit tai TravelUnit tauluun
    try
	{
      // tti-tiedostoja käsitellessä ei kysellä tietojen päivityksistä (vain tta-tiedotoja käsitellessä). tti-tiedostot ei ikinä kirjoita listoja (asiakasryhmät, asiakkaat, laskuttajat ja työtyypit) uusiksi!!!
      Props::e().m_yanc_wt = Props::e().m_yanc_wp = Props::e().m_yanc_b = R_NOTA;  // Eli No to All niin ei kysellä mitään!!!

      // Aukaistaan raportti tiedosto, tutkitaan koko, varataan muistia ja luetaan muistiin.
      open = path + filename;
      if((hfile = CreateFile(open, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL)) == INVALID_HANDLE_VALUE) throw(0);
      if((e = GetFileSize(hfile, NULL)) == 0xFFFFFFFF) throw(0);
      if(!(pmem = new char[e])) throw(0);
      if(!ReadFile(hfile, pmem, e, &r, NULL)) throw(0);
      CloseHandle(hfile); hfile = NULL;

      pTokenizer = new Tokenizer(pmem, e);
	  pvect = pTokenizer->getNext(); reportdate = pvect->at(1);
      pvect = pTokenizer->getNext(); worker = pvect->at(1);
	  pTokenizer->getNext(); biller = pvect->at(1);
	  pTokenizer->getNext(); pTokenizer->getNext(); pTokenizer->getNext();

	  while((pvect = pTokenizer->getNext()) != NULL)
	  {
        vect.clear();                                // Vaihdetaan CStringeihin (escapointi helpompaa)
        for(int i=0; i<pvect->size(); i++) vect.push_back(pvect->at(i).c_str());

        if(pvect->size() == 5)
          ret = db.lisaaWorkUnit(&vect, worker.c_str(), filename, reportdate.c_str(), biller.c_str(), _UNIT_MIN_, "0", "0");
		if(pvect->size() > 5)
		{
          apu = pvect->at(5);
          if(apu == WORKUNIT || apu == WORKSESSION)
		    ret = db.lisaaWorkUnit(&vect, worker.c_str(), filename, reportdate.c_str(), biller.c_str(), _UNIT_MIN_, "0", "0");
          else if(apu == TRAVELUNIT)
            ret = db.lisaaTravelUnit(&vect, worker.c_str(), filename, reportdate.c_str(), biller.c_str());
          else if(apu == SALESUNIT)
            ret = db.lisaaSalesUnit(&vect, worker.c_str(), filename, reportdate.c_str(), biller.c_str());
		}

        if(ret != RETURN_OK && ret != RETURN_EXISTS) // Estetään tiedoston kopiointi/siirto jos tapahtui jokin virhe
          cm_tila = FALSE;

		if(pdlg)                                     // Jos dialogi annettu, näytetään edistyminen (parsiminen voi viedä jonkin aikaa)
          pdlg->edistyminen(ret);
	  }

      delete [] pmem; pmem = NULL;

      // Lopuksi kopioidaan tai siirretään tiedosto raportit-kansioon (jos sen käsittely onnistui täydellisesti)
      if(cm_tila)
	  { if(!cmFile(path, filename, como)) throw(0); }
	}
    catch(...)
	{
      e = GetLastError();

      LPVOID lpMsgBuf;
      FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL, e, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

      errstr.Format(Props::i().lang("PARSE_2"), e); errstr += (LPCSTR)lpMsgBuf; errstr += "\r\n\r\n";
	  cs.Format(Props::i().lang("PARSE_3"), filename);
      errstr += cs;
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), errstr, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      LocalFree(lpMsgBuf);

      if(pdlg) pdlg->m_virhe_str.Format("%d", e);

      if(hfile) CloseHandle(hfile);

      if(pmem) delete [] pmem;

      return FALSE; 
	}

    return TRUE;
}

BOOL Parse::parseTTA(CString path, CString filename, int como, DlgParseInfo *pdlg)
{
	int mode = 0;
    DWORD e, r;
    DbSqlite db;
    char *pmem = NULL;
    HANDLE hfile = NULL;
    BOOL cm_tila = TRUE;
    vector <CString> vect;
    vector<string> *pvect;
    Tokenizer *pTokenizer = NULL;
    CString type, datetime;
    CString cs, cs2, group_id, name, custno, address, note, shortnote, info, billername, email, prodno;
    CString unit, purchaseprice, sellprice, alv, productgroup;

    /*
    * Props::e().m_yanc_b = Props::e().m_yanc_b, Props::e().m_yanc_wp, Props::e().m_yanc_wt --> Kysymyksen paluuarvo dialogilta (ks. DbSqlite-luokka)
    */

    try
	{
      // Aukaistaan raportti tiedosto, tutkitaan koko, varataan muistia ja luetaan muistiin.
      cs = path + filename;
      if((hfile = CreateFile(cs, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL)) == INVALID_HANDLE_VALUE) throw(0);
      if((e = GetFileSize(hfile, NULL)) == 0xFFFFFFFF) throw(0);
      if(!(pmem = new char[e])) throw(0);
      if(!ReadFile(hfile, pmem, e, &r, NULL)) throw(0);
      CloseHandle(hfile); hfile = NULL;

      pTokenizer = new Tokenizer(pmem, e);
      if((pvect = pTokenizer->getNext())->size() < 2) return FALSE;  // jos alle 2 -> pois, tuntematon tiedosto
      type = pvect->at(0).c_str(); datetime = pvect->at(1).c_str();
      if(type != TTA_TAIKALISTAT) return FALSE;                      // tunnistinta e löydy -> pois, tuntematon tiedosto

      while((pvect = pTokenizer->getNext()) != NULL)
	  {
        if(pvect->size() == 0) continue;                 // hypi yli tyhjät rivit

        type = pvect->at(0).c_str();                     // Lisättävä lista, rivien määrä listassa
        if(type == TTA_LASKUTTAJAT)
		{ mode = 1; Props::e().m_yanc_b = 0; continue; }
        if(type == TTA_ASIAKKAAT)
		{ mode = 2; Props::e().m_yanc_wp = 0; group_id = "1"; continue;  }
        if(type == TTA_TYOTYYPIT)
		{ mode = 3; Props::e().m_yanc_wt = 0; continue; }
        if(type == TTA_TUOTTEET)
		{ mode = 4; Props::e().m_yanc_wt = 0; group_id = "1"; continue; }

        if(mode == 1)        // LASKUTTAJAT
		{
          name = pvect->at(0).c_str();
          email = pvect->at(1).c_str();
          r = db.lisaaBiller(name, email, &name, B_UPDATE);

          if(r != RETURN_OK && r != RETURN_EXISTS) cm_tila = FALSE;
          if(Props::e().m_yanc_b == R_NO || Props::e().m_yanc_b == R_NOTA) r = R_NO;
          if(pdlg) pdlg->edistyminen(r);               // Jos dialogi annettu, näytetään edistyminen (parsiminen voi viedä jonkin aikaa)

          if(Props::e().m_yanc_b != R_YESTA && Props::e().m_yanc_b != R_NOTA) Props::e().m_yanc_b = 0; // Nollaa, jos ei tarkoitettu pysyväksi valinnaksi
		}
        else if(mode == 2)   // ASIAKASRYHMÄT JA ASIAKKAAT
		{
          if(!pvect->at(0).empty())                    // kaikila riveillä ei ole erikseen asiakasryhmää -> käytä edellisen kierroksen asiakasryhmän nimeä
             db.lisaaRegion(pvect->at(0).c_str(), &group_id);
          if(pvect->size() == 1) 
            continue;             // rivillä voi - ja saa - olla vain asiakasryhmän nimi

          name = pvect->at(1).c_str();
          address = pvect->at(2).c_str();
          note = pvect->at(3).c_str();
          shortnote = pvect->at(4).c_str();
          info = pvect->at(5).c_str();
          billername = pvect->at(6).c_str();
          custno = pvect->at(7).c_str();

          vect = db.haeTaulusta("Biller", "id", 1, "", 1, "", "Name", "=", billername);
          if(vect.size() > 0) // vanha laskuttaja löytyi -> ota id talteen
            billername = vect[0];
          else                // laskuttajaa ei löytynyt -> talleta ja ota id talteen
            db.lisaaBiller(billername, "", &billername, B_UPDATE);

          r = db.lisaaWorkPlace(name, group_id, custno, address, note, shortnote, info, billername, NULL, WP_UPDATE);

          if(r != RETURN_OK && r != RETURN_EXISTS) cm_tila = FALSE;
          if(Props::e().m_yanc_wp == R_NO || Props::e().m_yanc_wp == R_NOTA) r = R_NO;
          if(pdlg) pdlg->edistyminen(r);

          if(Props::e().m_yanc_wp != R_YESTA && Props::e().m_yanc_wp != R_NOTA) Props::e().m_yanc_wp = 0;
		}
        else if(mode == 3)   // TYÖTYYPIT
		{
          name = pvect->at(0).c_str();
          prodno = pvect->at(1).c_str();

          r = db.lisaaWorkType(name, prodno, WORK, "", "", "", "", "", WORKTYPE_POSITION_WORK, &name, WT_UPDATE);

          if(r != RETURN_OK && r != RETURN_EXISTS) cm_tila = FALSE;
          if(Props::e().m_yanc_wt == R_NO || Props::e().m_yanc_wt == R_NOTA) r = R_NO;
          if(pdlg) pdlg->edistyminen(r);

          if(Props::e().m_yanc_wt != R_YESTA && Props::e().m_yanc_wt != R_NOTA) Props::e().m_yanc_wt = 0;
		}
        else if(mode == 4)   // TUOTERYHMÄT JA TUOTTEET
		{
          if(!pvect->at(0).empty())                    // kaikila riveillä ei ole erikseen tuoteryhmää -> käytä edellisen kierroksen tuoteryhmän nimeä
             db.lisaaProductGroup(pvect->at(0).c_str(), &group_id);
          if(pvect->size() == 1) continue;             // rivillä voi - ja saa - olla vain tuoteryhmän nimi

          name = pvect->at(1).c_str();
          prodno = pvect->at(2).c_str();
          unit = pvect->at(3).c_str();
          purchaseprice = pvect->at(4).c_str();
          sellprice = pvect->at(5).c_str();
          alv = pvect->at(6).c_str();

          r = db.lisaaWorkType(name, prodno, PRODUCT, unit, purchaseprice, sellprice, alv, group_id, WORKTYPE_POSITION_PRODUCT, &name, WT_UPDATE);

          if(r != RETURN_OK && r != RETURN_EXISTS) cm_tila = FALSE;
          if(Props::e().m_yanc_wt == R_NO || Props::e().m_yanc_wt == R_NOTA) r = R_NO;
          if(pdlg) pdlg->edistyminen(r);

          if(Props::e().m_yanc_wt != R_YESTA && Props::e().m_yanc_wt != R_NOTA) Props::e().m_yanc_wt = 0;
		}	
	  }

      delete [] pmem; pmem = NULL;

      // Lopuksi kopioidaan tai siirretään tiedosto raportit-kansioon (jos sen käsittely onnistui täydellisesti)
      if(cm_tila)
	  { if(!cmFile(path, filename, como)) throw(0); }
	}
    catch(...)
	{
      e = GetLastError();

      LPVOID lpMsgBuf;
      FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL, e, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

      cs.Format(Props::i().lang("PARSE_2"), e); cs += (LPCSTR)lpMsgBuf; cs += "\r\n\r\n";
      if(e == ERROR_FILE_EXISTS)
		cs2.Format(Props::i().lang("PARSE_4"), filename);
      else
		cs2.Format(Props::i().lang("PARSE_3"), filename);
	  cs += cs2;
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      LocalFree(lpMsgBuf);

      if(pdlg) pdlg->m_virhe_str.Format("%d", e);

      if(hfile) CloseHandle(hfile);

      if(pmem) delete [] pmem;

      return FALSE; 
	}

    return RETURN_OK;
}

BOOL Parse::cmFile(CString path, CString filename, int como)
{ // Siirrä tai kopioi tiedosto raportit kansioon
    CString srcepath, destpath;

    srcepath = path + filename;
    destpath = Props::e().m_app_path + Props::i().lang("PARSE_5") + filename;

    if(como == MOVE_FILE)
	{ if(!MoveFile(srcepath, destpath)) return FALSE; }
    else if(como == COPY_FILE)
	{ if(!CopyFile(srcepath, destpath, TRUE)) return FALSE; }
    //else if(como == NOCM_FILE) {}

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
BOOL Parse::avaaTTI(HWND hwnd)
{
    DWORD e;
    CString file;
    OPENFILENAME ofn;
    DlgParseInfo dlg_pi;
	char buf[128] = {0};
    char *lpstrFile = NULL, strFileTitle[MAX_PATH];

    try
	{
      file = Props::i().get(OPTIONS_OPENPATH).c_str();

      if(!(lpstrFile = new char[MAX_PATH * 100])) throw(0);          // Tarpeeksi tilaa useammalle tiedostonimelle

      ofn.lStructSize = sizeof(OPENFILENAME);
      ofn.hwndOwner = hwnd;
      ofn.lpstrFilter = Props::i().langs("PARSE_6", buf, 128);
      ofn.lpstrTitle = Props::i().lang("PARSE_7");
      ofn.lpstrInitialDir = file;
      ofn.lpstrCustomFilter = NULL; ofn.nFilterIndex = 1;
      *lpstrFile = NULL; ofn.lpstrFile = lpstrFile; ofn.nMaxFile = MAX_PATH * 100;
      ofn.lpstrFileTitle = strFileTitle; ofn.nMaxFileTitle = MAX_PATH;
      ofn.Flags = OFN_EXPLORER|OFN_HIDEREADONLY|OFN_LONGNAMES|OFN_PATHMUSTEXIST|OFN_ALLOWMULTISELECT;
      ofn.lpstrDefExt = NULL; ofn.lCustData = NULL;
      if(!GetOpenFileName(&ofn)) throw(0);
      file = ofn.lpstrFile; file = file.Left(ofn.nFileOffset); // talleta, mahdollisesti uusi, polku asetuksiin
      Props::i().set(OPTIONS_OPENPATH, (LPCSTR)file);
 
      dlg_pi.m_tila = PARSE_FILES;                   // Parsitaan kansion kaikki valitut tiedostot
      dlg_pi.m_lpcstr = ofn.lpstrFile;
      dlg_pi.m_path = ofn.lpstrFileTitle;
      dlg_pi.m_kaikki = (int)ofn.nFileOffset;
      dlg_pi.DoModal();

      delete [] lpstrFile;                           // Vapauta muisti
	}
    catch(...)
	{
      if(lpstrFile) delete [] lpstrFile;

      if((e = CommDlgExtendedError()) != ERROR_SUCCESS)
      {
        file.Format(Props::i().lang("PARSE_8"), e);
        MessageBox(hwnd, file, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }

      return FALSE;
	}

    return TRUE;
}

BOOL Parse::avaaTTA(HWND hwnd)
{
    DWORD e;
    CString file;
    OPENFILENAME ofn;
    DlgParseInfo dlg;
	char buf[128] = {0};
    char *lpstrFile = NULL, strFileTitle[MAX_PATH];

    try
	{
      file = Props::i().get(OPTIONS_OPENPATH).c_str();

      if(!(lpstrFile = new char[MAX_PATH * 100])) throw(0);          // Tarpeeksi tilaa useammalle tiedostonimelle

      ofn.lStructSize = sizeof(OPENFILENAME);
      ofn.hwndOwner = hwnd;
      ofn.lpstrFilter = Props::i().langs("PARSE_9", buf, 128);
      ofn.lpstrTitle = Props::i().lang("PARSE_10");
      ofn.lpstrInitialDir = file;
      ofn.lpstrCustomFilter = NULL; ofn.nFilterIndex = 1;
      *lpstrFile = NULL; ofn.lpstrFile = lpstrFile; ofn.nMaxFile = MAX_PATH * 100;
      ofn.lpstrFileTitle = strFileTitle; ofn.nMaxFileTitle = MAX_PATH;
      ofn.Flags = OFN_EXPLORER|OFN_HIDEREADONLY|OFN_LONGNAMES|OFN_PATHMUSTEXIST;
      ofn.lpstrDefExt = NULL; ofn.lCustData = NULL;
      if(!GetOpenFileName(&ofn)) throw(0);
      file = ofn.lpstrFile; file = file.Left(ofn.nFileOffset);       // talleta, mahdollisesti uusi, polku asetuksiin
      Props::i().set(OPTIONS_OPENPATH, (LPCSTR)file);

      dlg.m_tila = PARSE_FILES;                      // Parsitaan kansion kaikki valitut tiedostot
      dlg.m_lpcstr = ofn.lpstrFile;
      dlg.m_path = ofn.lpstrFileTitle;
      dlg.m_kaikki = (int)ofn.nFileOffset;
      dlg.DoModal();

      delete [] lpstrFile;                           // Vapauta muisti
	}
    catch(...)
	{
      if(lpstrFile) delete [] lpstrFile;

      if((e = CommDlgExtendedError()) != ERROR_SUCCESS)
      {
        file.Format(Props::i().lang("PARSE_8"), e);
        MessageBox(hwnd, file, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }

      return FALSE;
	}

    return TRUE;
}

BOOL Parse::talletaTTI(HWND hwnd, int mode)
{
    DWORD d;
    int i, s;
    DbSqlite db;
    CBuffer buffer;
    SYSTEMTIME syt;
    Paivays paivays;
    OPENFILENAME ofn;
    COleDateTime odt;
	char buf[128] = {0};
    HANDLE hfile = NULL;
    CString file, cs;
    vector <CString> wp_vect;
    vector <CString> r_vect;
    vector <CString> wt_vect;
    vector <ItemData*> id_vect;
    char strFile[MAX_PATH * 2], strFileTitle[MAX_PATH * 2], strDefExt[4] = {TTI_EXT};

    try
	{
      if(mode == 0) throw(0x10000000);               // Talletus ei mahdollista nyt

      file = Props::i().get(OPTIONS_SAVEPATH).c_str();

      ofn.lStructSize = sizeof(OPENFILENAME);
      ofn.hwndOwner = hwnd;
      ofn.lpstrFilter = Props::i().langs("PARSE_11", buf, 128);
      ofn.lpstrTitle = Props::i().lang("PARSE_12");
      ofn.lpstrInitialDir = file;
      ofn.lpstrCustomFilter = NULL; ofn.nFilterIndex = 1;
      *strFile = NULL; ofn.lpstrFile = strFile; ofn.nMaxFile = MAX_PATH * 2;
      ofn.lpstrFileTitle = strFileTitle; ofn.nMaxFileTitle = MAX_PATH * 2;
      ofn.Flags = OFN_ENABLEHOOK|OFN_ENABLETEMPLATE|OFN_EXPLORER|OFN_HIDEREADONLY|OFN_LONGNAMES|OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT;
      ofn.lpstrDefExt = strDefExt;
      ofn.lpTemplateName = MAKEINTRESOURCE(IDD_DLGSAVE); // Lisäkontrollit
      ofn.lpfnHook = OFNHookProc_Raportti;               // Viestit
      ofn.hInstance = Props::e().m_hInstance;            // Instanssin kahva
      ofn.lCustData = (long)this;                        // Välitetään luokan osoitin
      m_mode = mode;                                     // Mahdolliset talletustilat
      if(!GetSaveFileName(&ofn)) throw(0);               // Huomioi OFNHookProc_Raportti-funktiossa tehtävä lisäkäsittely
      file = ofn.lpstrFile; file = file.Left(ofn.nFileOffset);
      Props::i().set(OPTIONS_SAVEPATH, (LPCSTR)file);    // talleta, mahdollisesti uusi, polku asetuksiin

      // Haetaan GetSaveFileName()-funktiossa valitun tilan mukaan vektoriin talletettavat tiedot
      ((CTaikaDlg*)Props::e().GetMainWnd())->pageRaportit.haeItemDataList(&id_vect, m_mode);
      if((s = id_vect.size()) == 0) throw(0x10000001);

      if((s = id_vect.size()) > 0)
	  {
        GetLocalTime(&syt);                          // Työaikaraportti: dd.mm.yyyy hh.mm
        file.Format("%d.%d.%d %d.%d", syt.wDay, syt.wMonth, syt.wYear, syt.wHour, syt.wMinute);
        buffer + "Työaikaraportti:\t";
        buffer + (LPCSTR)file; buffer + "\n";
        buffer + "Työntekijä:\t";                    // Työntekijä: ...
        buffer + (LPCSTR)m_tyontekija; buffer + "\n";
        buffer + "Laskuttaja:\t";                    // Laskuttaja: ...
        buffer + (LPCSTR)m_laskuttaja; buffer + "\n";
        buffer + "\nAsiakas\tTyötyyppi\tAloitusaika\tLopetusaika\tTehokas työaika(min)\n\n";

        for(i=0; i<s; i++)
		{
          if((wp_vect = db.haeTaulusta("WorkPlace", "Name, Region_id", 2, "", 1, "", "id", "=", id_vect[i]->WorkPlace_id)).size() == 0) throw(0x10000002);
          if((r_vect = db.haeTaulusta("Region", "Name", 1, "", 1, "", "id", "=", wp_vect[1])).size() == 0) throw(0x10000002);
          if((wt_vect = db.haeTaulusta("WorkType", "Name, ProductNumber", 2, "", 1, "", "id", "=", id_vect[i]->WorkType_id)).size() == 0) throw(0x10000002);

          buffer + wp_vect[0]; buffer + "\t";                                  // WorkPlace.Name
          buffer + wt_vect[0]; buffer + "\t";                                  // WorkType.Name
          if(id_vect[i]->Type == ID_WORKUNIT)
		  {
            buffer + paivays.date2string(id_vect[i]->StartDate); buffer + " "; // WorkUnit.StartDate + WorkUnit.StartTime
            buffer + paivays.time2filetime(id_vect[i]->StartTime); buffer + "\t";
            buffer + paivays.date2string(id_vect[i]->EndDate); buffer + " ";   // WorkUnit.EndDate + WorkUnit.EndTime
            buffer + paivays.time2filetime(id_vect[i]->EndTime); buffer + "\t";
            buffer + id_vect[i]->UnitValue; buffer + "\t";                     // WorkUnit.UnitValue
            buffer + WORKUNIT; buffer + "\t";                                  // TYPE_WORKUNIT
            buffer + r_vect[0]; buffer + "\t";                                 // Region.Name
            buffer + id_vect[i]->Alv; buffer + "\n";                           // WorkUnit.Alv
		  }
          else if(id_vect[i]->Type == ID_SALESUNIT)
		  {
            buffer + paivays.date2string(id_vect[i]->StartDate); buffer + " "; // WorkUnit.StartDate + WorkUnit.StartTime
            buffer + paivays.time2filetime(id_vect[i]->StartTime); buffer + "\t";
            buffer + id_vect[i]->Unit; buffer + "\t";                          // WorkUnit.Unit
            buffer + id_vect[i]->UnitValue; buffer + "\t";                     // WorkUnit.UnitValue
            buffer + SALESUNIT; buffer + "\t";                                 // TYPE_SALESUNIT
            buffer + id_vect[i]->UnitPrice; buffer + "\t";                     // WorkUnit.UnitPrice
            buffer + id_vect[i]->TotalPrice; buffer + "\t";                    // WorkUnit.TotalPrice
            buffer + wt_vect[1]; buffer + "\t";                                // WorkType.ProductNumber
            buffer + id_vect[i]->Alv; buffer + "\n";                           // WorkUnit.Alv
		  }
		}

        if((hfile = CreateFile(ofn.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL)) == INVALID_HANDLE_VALUE) throw(0);
        if(!WriteFile(hfile, buffer.getBuffer(), buffer.getSize(), &d, NULL)) throw(0);
        if(d < buffer.getSize()) throw(0x10000003);
        CloseHandle(hfile); hfile = NULL;
	  }

      // Vapautetaan muisti
      ((CTaikaDlg*)Props::e().GetMainWnd())->pageRaportit.vapautaItemDataLists(&id_vect, NULL, m_mode);

      MessageBox(hwnd, Props::i().lang("PARSE_13"), Props::e().m_app_title, MB_ICONINFORMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}
    catch(int err)
	{
      i = 0;
      if(err == 0x10000000)
	    file.Format(Props::i().lang("PARSE_14"), TYOTKOHTEISSA, ASIAKKAAT);
      else if(err == 0x10000001)
        file = Props::i().lang("PARSE_15");
      else if(err == 0x10000002)
        file = Props::i().lang("PARSE_16");
      else if(err == 0x10000003)
		file.Format(Props::i().lang("PARSE_17"), ofn.lpstrFile);
      else if((i = (int)CommDlgExtendedError()) != ERROR_SUCCESS)
        file.Format(Props::i().lang("PARSE_18"), i);
	  else
	  {
        LPVOID lpMsgBuf;
        if((i = GetLastError()) != ERROR_SUCCESS)
		{
          FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, i, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
          file.Format(Props::i().lang("PARSE_19"), i, (LPCSTR)lpMsgBuf, ofn.lpstrFile);
          LocalFree(lpMsgBuf);
		}
	  }

      if(err != 0 || i != 0) MessageBox(hwnd, file, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      return FALSE;

      if(hfile) CloseHandle(hfile);
	}

    return TRUE;
}

BOOL Parse::talletaTTI_tyomatkat(HWND hwnd, vector <ItemData_travel*> id_vect)
{
    DWORD d;
    int i, s;
    DbSqlite db;
    CBuffer buffer;
    SYSTEMTIME syt;
    Paivays paivays;
    OPENFILENAME ofn;
    COleDateTime odt;
	char buf[128] = {0};
    HANDLE hfile = NULL;
    CString file;
    vector <CString> vect;
    char strFile[MAX_PATH * 2], strFileTitle[MAX_PATH * 2], strDefExt[4] = {TTI_EXT};

    try
	{
      file = Props::i().get(OPTIONS_SAVEPATH).c_str();

      ofn.lStructSize = sizeof(OPENFILENAME);
      ofn.hwndOwner = hwnd;
      ofn.lpstrFilter = Props::i().langs("PARSE_11", buf, 128);
      ofn.lpstrTitle = Props::i().lang("PARSE_20");
      ofn.lpstrInitialDir = file;
      ofn.lpstrCustomFilter = NULL; ofn.nFilterIndex = 1;
      *strFile = NULL; ofn.lpstrFile = strFile; ofn.nMaxFile = MAX_PATH * 2;
      ofn.lpstrFileTitle = strFileTitle; ofn.nMaxFileTitle = MAX_PATH * 2;
      ofn.Flags = OFN_ENABLEHOOK|OFN_ENABLETEMPLATE|OFN_EXPLORER|OFN_HIDEREADONLY|OFN_LONGNAMES|OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT;
      ofn.lpstrDefExt = strDefExt;
      ofn.lpTemplateName = MAKEINTRESOURCE(IDD_DLGSAVE2);// Lisäkontrollit
      ofn.lpfnHook = OFNHookProc_Tyomatkat;              // Viestit
      ofn.hInstance = Props::e().m_hInstance;            // Instanssin kahva
      ofn.lCustData = (long)this;                        // Välitetään luokan osoitin
      if(!GetSaveFileName(&ofn)) throw(0);               // Huomioi OFNHookProc_Raportti-funktiossa tehtävä lisäkäsittely
      file = ofn.lpstrFile; file = file.Left(ofn.nFileOffset);  // talleta, mahdollisesti uusi, polku asetuksiin
      Props::i().set(OPTIONS_SAVEPATH, (LPCSTR)file);

      GetLocalTime(&syt);                          // Työaikaraportti: dd.mm.yyyy hh.mm
      file.Format("%d.%d.%d %d.%d", syt.wDay, syt.wMonth, syt.wYear, syt.wHour, syt.wMinute);
      buffer + "Työaikaraportti:\t";
      buffer + (LPCSTR)file; buffer + "\n";
      buffer + "Työntekijä:\t";                    // Työntekijä: ...
      if((vect = db.haeTaulusta("Worker", "Name", 1, "", 1, "", "id", "=", id_vect[0]->Worker_id)).size() == 0) throw(0x10000002);
      buffer + (LPCSTR)vect[0]; buffer + "\n";
      buffer + "Laskuttaja:\t";                    // Laskuttaja: ...
      buffer + (LPCSTR)m_laskuttaja; buffer + "\n";
      buffer + "\nAsiakas\tTyötyyppi\tAloitusaika\tLopetusaika\tTehokas työaika(min)\n\n";

      s = id_vect.size();
      for(i=0; i<s; i++)
      {
        buffer + id_vect[i]->StartMeter; buffer + "\t";                      // TravelUnit.StartMeter
        buffer + id_vect[i]->EndMeter; buffer + "\t";                        // TravelUnit.EndMeter
        buffer + paivays.date2string(id_vect[i]->StartDate); buffer + " ";   // TravelUnit.StartTime
        buffer + paivays.time2filetime(id_vect[i]->StartTime); buffer + "\t";
        buffer + paivays.date2string(id_vect[i]->EndDate); buffer + " ";     // TravelUnit.EndTime
        buffer + paivays.time2filetime(id_vect[i]->EndTime); buffer + "\t";
        buffer + id_vect[i]->Private; buffer + "\t";                         // TravelUnit.Private
        buffer + TRAVELUNIT; buffer + "\t";                                  // TYPE_TRAVELUNIT
        buffer + id_vect[i]->StartPlace; buffer + "\t";                      // TravelUnit.StartPlace
        buffer + id_vect[i]->EndPlace; buffer + "\t";                        // TravelUnit.EndPlace
        buffer + id_vect[i]->Purpose; buffer + "\n";                         // TravelUnit.Purpose
	  }

      if((hfile = CreateFile(ofn.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL)) == INVALID_HANDLE_VALUE) throw(0);
      if(!WriteFile(hfile, buffer.getBuffer(), buffer.getSize(), &d, NULL)) throw(0);
      if(d < buffer.getSize()) throw(0x10000003);
      CloseHandle(hfile); hfile = NULL;

      MessageBox(hwnd, Props::i().lang("PARSE_21"), Props::e().m_app_title, MB_ICONINFORMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}
    catch(int err)
	{
      i = 0;
      if(err == 0x10000001)
        file = Props::i().lang("PARSE_15");
      else if(err == 0x10000002)
        file = Props::i().lang("PARSE_16");
      else if(err == 0x10000003)
		file.Format(Props::i().lang("PARSE_17"), ofn.lpstrFile);
      else if((i = (int)CommDlgExtendedError()) != ERROR_SUCCESS)
        file.Format("Järjestelmän virhekoodi: %d - Tiedoston talletus epäonnistui", i);
	  else
	  {
        LPVOID lpMsgBuf;
        if((i = GetLastError()) != ERROR_SUCCESS)
		{
          FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, i, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
		  file.Format(Props::i().lang("PARSE_19"), i, (LPCSTR)lpMsgBuf, ofn.lpstrFile);
          LocalFree(lpMsgBuf);
		}
	  }

      if(err != 0 || i != 0) MessageBox(hwnd, file, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      return FALSE;

      if(hfile) CloseHandle(hfile);
	}

    return TRUE;
}

BOOL Parse::talletaTTA(HWND hwnd, CString par_filepath, UINT par_asiakkaat, UINT par_laskuttajat, UINT par_tyotyypit, UINT par_tuotteet, int mode)
{
    DWORD d;
    DbSqlite db;
    SYSTEMTIME syt;
    CBuffer buffer;
    COleDateTime odt;
    OPENFILENAME ofn;
	char buf[128] = {0};
    HANDLE hfile = NULL;
    vector <CString> vect, vect2;
    vector <CString> r_vect;
    vector <CString> wp_vect;
    CString cs, cnv, region, file, filepath;
    int i, j, s, c, count_wp = 0, count_b = 0, count_wt = 0, count_pr = 0;
    char strFile[MAX_PATH * 2], strFileTitle[MAX_PATH * 2], strDefExt[4] = {TTA_EXT};

    try
	{
      if(par_filepath == "")                         // Kysytään tiedostopolku ja talletuksen asetukset
	  {
        file = Props::i().get(OPTIONS_SAVEPATH).c_str();

        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = hwnd;
        ofn.lpstrFilter = Props::i().langs("PARSE_23", buf, 128);
        ofn.lpstrTitle = Props::i().lang("PARSE_24");
        ofn.lpstrInitialDir = file;
        ofn.lpstrCustomFilter = NULL; ofn.nFilterIndex = 1;
        *strFile = NULL; ofn.lpstrFile = strFile; ofn.nMaxFile = MAX_PATH * 2;
        ofn.lpstrFileTitle = strFileTitle; ofn.nMaxFileTitle = MAX_PATH * 2;
        ofn.Flags = OFN_ENABLEHOOK|OFN_ENABLETEMPLATE|OFN_EXPLORER|OFN_HIDEREADONLY|OFN_LONGNAMES|OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT;
        ofn.lpstrDefExt = strDefExt;
        ofn.lpTemplateName = MAKEINTRESOURCE(IDD_DLGSAVELISTAT);     // Lisäkontrollit
        ofn.lpfnHook = OFNHookProc_Listat;                           // Viestit
        ofn.hInstance = Props::e().m_hInstance;                      // Instanssin kahva
        ofn.lCustData = (long)this;                                  // Välitetään luokan osoitin
        if(!GetSaveFileName(&ofn)) throw(0);                         // Huomioi OFNHookProc_Raportti-funktiossa tehtävä lisäkäsittely
        file = ofn.lpstrFile; file = file.Left(ofn.nFileOffset);     // talleta, mahdollisesti uusi, polku asetuksiin
        Props::i().set(OPTIONS_SAVEPATH, (LPCSTR)file);

        filepath = ofn.lpstrFile;
	  }
      else                                           // Tiedostopolku ja talletuksen asetukset annettu parametreina
	  {
        filepath = par_filepath;
        m_asiakkaat = par_asiakkaat;
        m_laskuttajat = par_laskuttajat;
        m_tyotyypit = par_tyotyypit;
        m_tuotteet = par_tuotteet;
	  }

      // Otsikko
      GetLocalTime(&syt);                            // t-aika-listat:	dd.mm.yyyy hh.mm
      cs.Format("%02d.%02d.%d %02d:%02d", syt.wDay, syt.wMonth, syt.wYear, syt.wHour, syt.wMinute);
      buffer + TTA_TAIKALISTAT; buffer + "\t";
      buffer + (LPCSTR)cs; buffer + "\n";


      // HUOM! JÄRJESTYS - ENSIN BILLER, SITTEN MUUT. WorkPlace-taulussa voi olla käytetty laskuttajia (Biller), jotka löytyvät vain tiedostosta!!!
      // 1.1 Biller-taulu - ENSIMMÄISENÄ!!!
      if((vect = db.haeTaulusta("Biller", "count(id)", 1, "", 0)).size() > 0)
	  {
        if(atoi(vect[0]) > 0 && m_laskuttajat == BST_CHECKED)
		{
          count_b = atoi(vect[0]);

          i = 0; // Ei lisätä oletus laskuttajaa, jos sitä ei ole käytetty missään taulussa
		  if((vect = db.haeTaulusta("Biller", "id", 2, "", 1, "", "Name", "=", DFLT_BILLER)).size() > 0)
		  {
            cs = vect[0];
            if((vect = db.haeTaulusta("WorkUnit", "count(id)", 1, "", 1, "", "Biller_id", "=", cs)).size() > 0)
              i += atoi(vect[0]);
            if((vect = db.haeTaulusta("TravelUnit", "count(id)", 1, "", 1, "", "Biller_id", "=", cs)).size() > 0)
              i += atoi(vect[0]);
            if((vect = db.haeTaulusta("WorkPlace", "count(id)", 1, "", 1, "", "Biller_id", "=", cs)).size() > 0)
              i += atoi(vect[0]);
		  }

          if(i == 0) count_b -= 1;
		  cs.Format("%d", count_b);
          buffer + TTA_LASKUTTAJAT; buffer + "\t"; buffer + cs; buffer + "\n";

          if(i > 0)
          { if((s = (vect = db.haeTaulusta("Biller", "Name, Email", 2, "id", 0)).size()) == 0) throw(0x10000002); }
          else
		  { if((s = (vect = db.haeTaulusta("Biller", "Name, Email", 2, "id", 1, "", "Name", "<>", DFLT_BILLER)).size()) == 0) throw(0x10000002); }
          for(i=0; i<s; i+=2)
		  {
            buffer + safe(vect[i + 0]); buffer + "\t";       // Biller.Name
            buffer + safe(vect[i + 1]); buffer + "\n";       // Biller.Email
		  }
		}
	  }

      // 1.2 Region- ja WorkPlace-taulut
      if(m_asiakkaat == BST_CHECKED)
	  {
        wp_vect = db.haeTaulusta("WorkPlace", "count(id)", 1, "", 0);
        count_wp = atoi(wp_vect[0]);
        wp_vect = db.freeQuery("SELECT count(id) FROM region WHERE id NOT IN (SELECT DISTINCT region_id FROM workplace);", 1);
        count_wp += atoi(wp_vect[0]);

        if(count_wp > 0)
		{
          cs.Format("%d", count_wp);
          buffer + TTA_ASIAKKAAT; buffer + "\t"; buffer + cs; buffer + "\n";

          s = (r_vect = db.haeTaulusta("Region", "id, Name", 2, "position", 0)).size();
          for(i=0; i<s; i+=2)
		  {
            buffer + safe((LPCSTR)r_vect[i + 1]);            // Region.Name vain kerran, seuraavat rivit alkavat pelkällä tabulaattorilla
            c = (wp_vect = db.haeTaulusta("WorkPlace", "Name, Address, Note, Shortnote, Info, Biller_id, CustomerNumber", 7, "position", 1, "", "Region_id", "=", r_vect[i])).size();
            for(j=0; j<c; j+=7)
			{
              buffer + "\t";
              buffer + safe(wp_vect[j + 0]); buffer + "\t";  // WorkPlace.Name
              buffer + safe(wp_vect[j + 1]); buffer + "\t";  // WorkPlace.Address
              buffer + safe(wp_vect[j + 2]); buffer + "\t";  // WorkPlace.Note
              buffer + safe(wp_vect[j + 3]); buffer + "\t";  // WorkPlace.Shortnote
              buffer + safe(wp_vect[j + 4]); buffer + "\t";  // WorkPlace.Info
              if((vect = db.haeTaulusta("Biller", "Name", 1, "", 1, "", "id", "=", wp_vect[j + 5])).size() == 0) throw(0x10000002);
              buffer + safe(vect[0]);        buffer + "\t";  // Biller.Name
              buffer + safe(wp_vect[j + 6]); buffer + "\n";  // WorkPlace.CustomerNumber
			}
            if(c == 0) buffer + "\n";                  // Pelkkä regionin nimi ilman workplaceja?
		  }
		}
	  }

      // 2. WorkType-taulu - työtyypit ja tuotteet
      if((vect = db.haeTaulusta("WorkType", "count(id)", 1, "", 1, "", WORKTYPE_TYPE, "=", WORK)).size() > 0)
	  {
        if(atoi(vect[0]) > 0 && m_tyotyypit == BST_CHECKED)
		{
          // Työtyypit
          count_wt = atoi(vect[0]);
          buffer + TTA_TYOTYYPIT; buffer + "\t"; buffer + (LPCSTR)vect[0]; buffer + "\n";

          if((s = (vect = db.haeTaulusta("WorkType", "Name, ProductNumber", 2, WORKTYPE_POSITION_WORK, 1, "", WORKTYPE_TYPE, "=", WORK)).size()) == 0) throw(0x10000002);
          for(i=0; i<s; i+=2)
		  {
            buffer + safe(vect[i + 0]); buffer + "\t";         // WorkType.Name
            buffer + safe(vect[i + 1]); buffer + "\n";         // WorkType.ProductNumber
		  }
		}
	  }

      if(m_tuotteet == BST_CHECKED)
	  {
        vect = db.haeTaulusta("WorkType", "count(id)", 1, "", 1, "", WORKTYPE_TYPE, "=", PRODUCT);
        count_pr += atoi(vect[0]);
        vect = db.freeQuery("SELECT count(id) FROM ProductGroup WHERE id NOT IN (SELECT DISTINCT ProductGroup_id FROM worktype WHERE Type='PRODUCT');", 1);
        count_pr += atoi(vect[0]);

        if(count_pr > 0)
		{
          // Tuotteet
          cs.Format("%d", count_pr);
          buffer + TTA_TUOTTEET; buffer + "\t"; buffer + cs; buffer + "\n";

          s = (r_vect = db.haeTaulusta("ProductGroup", "id, Name", 2, "position", 0)).size();
          for(i=0; i<s; i+=2)
		  {
            buffer + safe((LPCSTR)r_vect[i + 1]);              // ProductGroup.Name vain kerran, seuraavat rivit alkavat pelkällä tabulaattorilla
            c = (vect = db.haeTaulusta("WorkType", "Name, ProductNumber, Unit, PurchasePrice, SellPrice, Alv", 6, WORKTYPE_POSITION_PRODUCT, 2, "", WORKTYPE_TYPE, "=", PRODUCT, "AND", WORKTYPE_PRODUCTGROUP_ID, "=", r_vect[i])).size();
            for(j=0; j<c; j+=6)
			{
              buffer + "\t";
              buffer + safe(vect[j + 0]); buffer + "\t";       // WorkType.Name
              buffer + safe(vect[j + 1]); buffer + "\t";       // WorkType.ProductNumber
              buffer + safe(vect[j + 2]); buffer + "\t";       // WorkType.Unit
              buffer + safe(vect[j + 3]); buffer + "\t";       // WorkType.PurchasePrice
              buffer + safe(vect[j + 4]); buffer + "\t";       // WorkType.sellPrice
              buffer + safe(vect[j + 5]); buffer + "\n";       // WorkType.Alv
			}
			if(c == 0) buffer + "\n";                    // Pelkkä tuoteryhmän nimi ilman tuotteita?
		  }
		}
	  }

      if((count_wp + count_b + count_wt + count_pr) > 0)
	  {
        if((hfile = CreateFile(filepath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL)) == INVALID_HANDLE_VALUE) throw(0);
        if(!WriteFile(hfile, buffer.getBuffer(), buffer.getSize(), &d, NULL)) throw(0);
        if(d < buffer.getSize()) throw(0x10000003);
        CloseHandle(hfile); hfile = NULL;

        if(mode == MODE_SAVE) MessageBox(hwnd, Props::i().lang("PARSE_25"), Props::e().m_app_title, MB_ICONINFORMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }
      else
	  {
        if(mode == MODE_SAVE) cs = Props::i().lang("PARSE_26");
        else if(mode == MODE_ATTACH) cs = Props::i().lang("PARSE_27");
        MessageBox(hwnd, cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }
	}
    catch(int err)
	{
      i = 0;
      if(err == 0x10000002)
        cs = Props::i().lang("PARSE_16");
      else if(err == 0x10000003)
		file.Format(Props::i().lang("PARSE_17"), filepath);
	  else
	  {
        LPVOID lpMsgBuf;
        if((i = GetLastError()) != ERROR_SUCCESS)
		{
          FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, i, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
		  cs.Format(Props::i().lang("PARSE_19"), i, (LPCSTR)lpMsgBuf, filepath);
          LocalFree(lpMsgBuf);
		}
	  }

      if(hfile) CloseHandle(hfile);

      if(err != 0 || i != 0) MessageBox(hwnd, cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      return FALSE;
	}

    return TRUE;
}

int Parse::fileExists(CString filepath, CString samat, DWORD disp)
{
    DWORD dw;
    CString cs;
    int r = IDYES;
    HANDLE hfile = NULL;

    if(filepath == samat)
	{
      cs.Format(Props::i().lang("PARSE_28"), filepath, samat);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      return IDNO;
	}

    hfile = CreateFile(filepath, GENERIC_READ, 0, NULL, disp, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    dw = GetLastError();
    if(dw == ERROR_SUCCESS)
	{
      cs.Format(Props::i().lang("PARSE_29"), filepath);
      r = MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_YESNO);
	}
    else if(dw == ERROR_PATH_NOT_FOUND)
	{
      cs.Format(Props::i().lang("PARSE_30"), filepath);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      r = IDNO;
	}
    else if(dw == ERROR_ACCESS_DENIED || dw == ERROR_SHARING_VIOLATION)
	{
      cs.Format(Props::i().lang("PARSE_31"), filepath);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      r = IDNO;
	}

    if(hfile != INVALID_HANDLE_VALUE) CloseHandle(hfile);

    return r;
}

UINT CALLBACK OFNHookProc_Raportti(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    static Parse *pParse;

    if(uiMsg == WM_INITDIALOG)
	{
      int i, s;
      DbSqlite db;
      CString lask;
      char str[MAX_PATH];
      vector <CString> vect;

      // WM_INITDIALOG -> lParam sisältää OPENFILENAME-struktuurin osittimen -> lCustData sisältää Parse-luokan osoittimen
      pParse = (Parse*)((OPENFILENAME*)lParam)->lCustData;

	  ::SetDlgItemText(hdlg, IDC_STATIC4, Props::i().lang("DLGSAVE_C1"));
	  ::SetDlgItemText(hdlg, IDC_STATIC3, Props::i().lang("DLGSAVE_C2"));
	  ::SetDlgItemText(hdlg, IDC_STATIC1, Props::i().lang("DLGSAVE_C3"));
	  ::SetDlgItemText(hdlg, IDC_STATIC2, Props::i().lang("DLGSAVE_C4"));

      // Aseta mahdolliset talletustilat
      if((pParse->m_mode & 0x01) == MODE_VALITUT) {
          i = SendDlgItemMessage(hdlg, IDC_CMBMODE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Props::i().lang("PARSE_32"));
          SendDlgItemMessage(hdlg, IDC_CMBMODE, CB_SETITEMDATA, i, (LPARAM)(DWORD)MODE_VALITUT); }
      if((pParse->m_mode & 0x02) == MODE_KAIKKINAYTETYT) {
          i = SendDlgItemMessage(hdlg, IDC_CMBMODE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Props::i().lang("PARSE_33"));
          SendDlgItemMessage(hdlg, IDC_CMBMODE, CB_SETITEMDATA, i, (LPARAM)(DWORD)MODE_KAIKKINAYTETYT); }
      if((pParse->m_mode & 0x04) == MODE_ASIAKAANTIEDOT) {
          i = SendDlgItemMessage(hdlg, IDC_CMBMODE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Props::i().lang("PARSE_34"));
          SendDlgItemMessage(hdlg, IDC_CMBMODE, CB_SETITEMDATA, i, (LPARAM)(DWORD)MODE_ASIAKAANTIEDOT); }
      SendDlgItemMessage(hdlg, IDC_CMBMODE, CB_SETCURSEL, 0, 0);
      pParse->m_mode = SendDlgItemMessage(hdlg, IDC_CMBMODE, CB_GETITEMDATA, 0, 0);    // Ota tila ylös

      // Työntekijät
      s = (vect = db.haeTaulusta("Worker", "DISTINCT Name", 1, "Name", 0)).size();
      for(i=0; i<s; i++)
        SendDlgItemMessage(hdlg, IDC_CMBTYONTEKIJA, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)vect[i]);
      SendDlgItemMessage(hdlg, IDC_CMBTYONTEKIJA, CB_SETCURSEL, 0, 0);
      SendDlgItemMessage(hdlg, IDC_CMBTYONTEKIJA, CB_GETLBTEXT, 0, (LPARAM)(LPCSTR)str); // Ota tila ylös
      pParse->m_tyontekija = str;

      // Laskuttajien nimet tietokannasta
      s = (vect = db.haeTaulusta("Biller", "Name", 1, "Name", 1, "", "Name", "<>", DFLT_BILLER)).size();
      for(i=0; i<s; i++)
        SendDlgItemMessage(hdlg, IDC_CMB_LASKUTTAJA, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)vect[i]);

      pParse->m_laskuttaja = lask;

      SendDlgItemMessage(hdlg, IDC_CMB_LASKUTTAJA, CB_SETCURSEL, 0, 0);
	}
    else if(uiMsg == WM_COMMAND)
	{
	}
    else if(uiMsg == WM_NOTIFY)
	{
      LPOFNOTIFY lpon = (LPOFNOTIFY)lParam; 
      if(lpon->hdr.code == CDN_FILEOK)               // Tiedostonimi valittu ja Avaa-painettu
	  {
        int s;
        char str[MAX_PATH];

        s = SendDlgItemMessage(hdlg, IDC_CMBMODE, CB_GETCURSEL, 0, 0);   // Talletuksen tila
        if(s != CB_ERR) pParse->m_mode = SendDlgItemMessage(hdlg, IDC_CMBMODE, CB_GETITEMDATA, s, 0);
        else pParse->m_mode = 0;
        GetDlgItemText(hdlg, IDC_CMBTYONTEKIJA, (LPSTR)str, MAX_PATH);   // Työntekijän nimi
        pParse->m_tyontekija = str;
        GetDlgItemText(hdlg, IDC_CMB_LASKUTTAJA, (LPSTR)str, MAX_PATH);  // Laskuttaja
        pParse->m_laskuttaja = str;

		if(pParse->m_laskuttaja == "")               // Ei laskuttajan nimeä -> estä dialogia sulkeutumasta
		{
          MessageBox(hdlg, Props::i().lang("PARSE_35"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_OK);
          SetFocus(GetDlgItem(hdlg, IDC_CMB_LASKUTTAJA));
          SetWindowLong(hdlg, DWL_MSGRESULT, 1L);
		}
        else if(pParse->m_tyontekija == "")          // Ei työntekijän nimeä
		{
          MessageBox(hdlg, Props::i().lang("PARSE_36"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_OK);
          SetFocus(GetDlgItem(hdlg, IDC_CMBTYONTEKIJA));
          SetWindowLong(hdlg, DWL_MSGRESULT, 1L);
		}
        else if(pParse->m_mode == 0)                 // Ei talletustilaa
		{
          MessageBox(hdlg, Props::i().lang("PARSE_37"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_OK);
          SetFocus(GetDlgItem(hdlg, IDC_CMBMODE));
          SetWindowLong(hdlg, DWL_MSGRESULT, 1L);
		}

		return 1;
	  }
	}

    return 0;
}

UINT CALLBACK OFNHookProc_Listat(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    static Parse *pParse;

    if(uiMsg == WM_INITDIALOG)
	{
      // WM_INITDIALOG -> lParam sisältää OPENFILENAME-struktuurin osittimen -> lCustData sisältää Parse-luokan osoittimen
      pParse = (Parse*)((OPENFILENAME*)lParam)->lCustData;

	  ::SetDlgItemText(hdlg, IDC_STATIC, Props::i().lang("DLGSAVELISTAT_C1"));
	  ::SetDlgItemText(hdlg, IDC_CHKASIAKKAAT, Props::i().lang("DLGSAVELISTAT_C2"));
	  ::SetDlgItemText(hdlg, IDC_CHKLASKUTTAJAT, Props::i().lang("DLGSAVELISTAT_C3"));
	  ::SetDlgItemText(hdlg, IDC_CHKTYOTYYPIT, Props::i().lang("DLGSAVELISTAT_C4"));
	  ::SetDlgItemText(hdlg, IDC_CHKTUOTTEET, Props::i().lang("DLGSAVELISTAT_C5"));

      // Aseta talletustila
      pParse->m_asiakkaat = BST_CHECKED;
      pParse->m_laskuttajat = BST_CHECKED;
      pParse->m_tyotyypit = BST_CHECKED;
      pParse->m_tuotteet = BST_CHECKED;
      CheckDlgButton(hdlg, IDC_CHKASIAKKAAT, BST_CHECKED);
      CheckDlgButton(hdlg, IDC_CHKLASKUTTAJAT, BST_CHECKED);
      CheckDlgButton(hdlg, IDC_CHKTYOTYYPIT, BST_CHECKED);
      CheckDlgButton(hdlg, IDC_CHKTUOTTEET, BST_CHECKED);
	}
    else if(uiMsg == WM_COMMAND)
	{	}
    else if(uiMsg == WM_NOTIFY)
	{
      LPOFNOTIFY lpon = (LPOFNOTIFY)lParam; 
      if(lpon->hdr.code == CDN_FILEOK)               // Tiedostonimi valittu ja Avaa-painettu
	  {
        pParse->m_asiakkaat = IsDlgButtonChecked(hdlg, IDC_CHKASIAKKAAT);
        pParse->m_laskuttajat = IsDlgButtonChecked(hdlg, IDC_CHKLASKUTTAJAT);
        pParse->m_tyotyypit = IsDlgButtonChecked(hdlg, IDC_CHKTYOTYYPIT);
        pParse->m_tuotteet = IsDlgButtonChecked(hdlg, IDC_CHKTUOTTEET);

		if(pParse->m_asiakkaat == BST_UNCHECKED && pParse->m_laskuttajat == BST_UNCHECKED  && pParse->m_tyotyypit == BST_UNCHECKED && pParse->m_tuotteet == BST_UNCHECKED)
		{
          MessageBox(hdlg, Props::i().lang("PARSE_38"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_OK);
          SetWindowLong(hdlg, DWL_MSGRESULT, 1L);
		}

		return 1;
	  }
	}

    return 0;
}

UINT CALLBACK OFNHookProc_Tyomatkat(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    static Parse *pParse;

    if(uiMsg == WM_INITDIALOG)
	{
      int i, s;
      DbSqlite db;
      CString lask;
      vector <CString> vect;

      // WM_INITDIALOG -> lParam sisältää OPENFILENAME-struktuurin osittimen -> lCustData sisältää Parse-luokan osoittimen
      pParse = (Parse*)((OPENFILENAME*)lParam)->lCustData;

	  ::SetDlgItemText(hdlg, IDC_STATIC1, Props::i().lang("DLGSAVE2_C1"));
	  ::SetDlgItemText(hdlg, IDC_STATIC2, Props::i().lang("DLGSAVE2_C2"));

      // Laskuttajien nimet tietokannasta
      s = (vect = db.haeTaulusta("Biller", "Name", 1, "Name", 1, "", "Name", "<>", DFLT_BILLER)).size();
      for(i=0; i<s; i++)
        SendDlgItemMessage(hdlg, IDC_CMB_LASKUTTAJA_TM, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)vect[i]);
      pParse->m_laskuttaja = lask;
      SendDlgItemMessage(hdlg, IDC_CMB_LASKUTTAJA_TM, CB_SETCURSEL, 0, 0);
	}
    else if(uiMsg == WM_NOTIFY)
	{
      LPOFNOTIFY lpon = (LPOFNOTIFY)lParam; 
      if(lpon->hdr.code == CDN_FILEOK)               // Tiedostonimi valittu ja Avaa-painettu
	  {
        char str[MAX_PATH];

        GetDlgItemText(hdlg, IDC_CMB_LASKUTTAJA_TM, (LPSTR)str, MAX_PATH);   // Laskuttaja
        pParse->m_laskuttaja = str;

		if(pParse->m_laskuttaja == "")               // Ei laskuttajan nimeä -> estä dialogia sulkeutumasta
		{
          MessageBox(hdlg, Props::i().lang("PARSE_35"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_OK);
          SetFocus(GetDlgItem(hdlg, IDC_CMB_LASKUTTAJA_TM));
          SetWindowLong(hdlg, DWL_MSGRESULT, 1L);
		}

		return 1;
	  }
	}

    return 0;
}

CString Parse::safe(CString value)
{ // Poistetaan kaikki tiltin aiheuttavat merkit
    CString apu(value);

	apu.Replace("\n", "");
	apu.Replace("\r", "");
	apu.Replace("\t", "");

	return apu;
}

// VANHA TTA-TIEDOSTO
// DEL      while((pvect = pTokenizer->getNext()) != NULL)
// DEL		{
// DEL          if(!pvect->at(0).empty()) region = pvect->at(0).c_str();     // kaikila asiakasnimiriveillä ei ole erikseen asiakasryhmää -> käytä edellisen kierroksen asiakasryhmänimeä
// DEL
// DEL          if((name = pvect->at(1).c_str()) == "") name = " ";
// DEL          if(pvect->size() > 3)                        // Täydellinen .tta tiedosto (ilman asiakasnumeroa)
// DEL		  {
// DEL            address = pvect->at(2).c_str();
// DEL            note = pvect->at(3).c_str();
// DEL            shortnote = pvect->at(4).c_str();
// DEL            info = pvect->at(5).c_str();
// DEL            custno = _UNSET_;
// DEL		  }
// DEL          else
// DEL		  {
// DEL            custno = pvect->at(2).c_str();
// DEL            address = note = shortnote = info = " ";
// DEL		  }
// DEL
// DEL        biller = DFLT_BILLER; // poista, tulee tiedostosta
// DEL		 
// DEL        if((r = db.lisaaRegion(region, &region_id)) == RETURN_OK)    // Uusi Region ja WorkPlace - WorkPlace tarvitsee Region_id:n!!!
// DEL          r = db.lisaaWorkPlace(name, region_id, custno, address, note, shortnote, info, &biller, &name, WP_UPDATE);
// DEL
// DEL        if(r != RETURN_OK && r != RETURN_EXISTS)         // Estetään tiedoston kopiointi/siirto jos tapahtui jokin virhe
// DEL          cm_tila = FALSE;
// DEL
// DEL		if(pdlg) pdlg->edistyminen(r);                   // Jos dialogi annettu, näytetään edistyminen (parsiminen voi viedä jonkin aikaa)
// DEL	  }