// DbSqlite.cpp: implementation of the dbSqlite class.
//////////////////////////////////////////////////////////////////////
#include <stdarg.h>
#include "stdafx.h"
#include "taika.h"
#include "Paivays.h"
#include "DbSqlite.h"
#include "Tokenizer.h"
#include "ATLCONV.H"
#include "DlgPaivita.h"
#include "Props.h"
#include "StringHelper_luokka.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DbSqlite::DbSqlite()
{}

DbSqlite::~DbSqlite()
{}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Apu-/Yhteiset funktiot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbSqlite::check()
{
    int err = RETURN_OK;
    DWORD dw = 0;
    CString dbpath, cs;
    HANDLE hfile = NULL;
    sqlite3 *pdb = NULL;

    dbpath = Props::e().m_db_path;                       // Polku tietokantaan

    // Testataan onko tietokanta jo luotu. Jos ei, luodaan uusi tyhjä tietokanta.
    hfile = CreateFile(dbpath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    dw = GetLastError();
    if(dw == ERROR_PATH_NOT_FOUND)
	{
      cs.Format(Props::i().lang("DBSQLITE_1"), dbpath);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      return GEN_ERROR;
	}
    else if(dw == ERROR_ACCESS_DENIED || dw == ERROR_SHARING_VIOLATION)
	{
      cs.Format(Props::i().lang("DBSQLITE_2"), dbpath);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      return GEN_ERROR;
	}

    if(hfile != INVALID_HANDLE_VALUE) CloseHandle(hfile);

    if(dw == ERROR_FILE_NOT_FOUND)
	{
      cs.Format(Props::i().lang("DBSQLITE_3"), dbpath);
      if(MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_YESNO) == IDNO) return GEN_ERROR;

      if((err = luoTaulut(&dbpath, TRUE)) != RETURN_OK)
	  {
        cs.Format(Props::i().lang("DBSQLITE_4"), err, dbpath);
        MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }
	}

    return RETURN_OK;
}

int DbSqlite::luoTaulut(CString *db_path, BOOL oletukset)
{ // Luo tyhjän tietokannan - virhe teksi palautetaan db_path:ssa
    CString sql;
    sqlite3 *pdb = NULL;

    try
	{
      if(sqlite3_open(_2UTF8(*db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));
      sql = "CREATE TABLE WorkUnit(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Worker_id INTEGER, WorkPlace_id INTEGER, WorkType_id INTEGER, StartDate Integer(4), StartTime Integer(4), EndDate Integer(4), EndTime Integer(4), Unit Varchar(160), UnitValue Varchar(32), Charged Varchar(8), UnitPrice Varchar(32), TotalPrice Varchar(32), Alv Varchar(32), ReportName Varchar(160), ReportDate Integer(4), Biller_id INTEGER, Type Integer(4));";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "CREATE TABLE TravelUnit(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, StartMeter Varchar(32), EndMeter Varchar(32), StartDate Integer(4), StartTime Integer(4), EndDate Integer(4), EndTime Integer(4), StartPlace Varchar(160), EndPlace Varchar(160), Purpose Varchar(160), Private Varchar(160), Worker_id Varchar(160), ReportName Varchar(160), ReportDate Integer(4), Biller_id INTEGER);";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "CREATE TABLE WorkPlace(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Name Varchar(160), CustomerNumber Varchar(32), Region_id INTEGER, Address Varchar(160), Note Varchar(160), Shortnote Varchar(160), Info Varchar(160), Biller_id INTEGER, position INTEGER);";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "CREATE TABLE Region(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Name Varchar(160), position INTEGER);";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "CREATE TABLE ProductGroup(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Name Varchar(160), position INTEGER);";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "CREATE TABLE WorkType(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Name Varchar(160), ProductNumber Varchar(160), Type Varchar(32), Unit Varchar(32), PurchasePrice Varchar(32), SellPrice Varchar(32), Alv Varchar(32), ProductGroup_id INTEGER, position_work INTEGER, position_product INTEGER);";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "CREATE TABLE Worker(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Name Varchar(160));";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "CREATE TABLE Biller(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Name Varchar(160), Email Varchar(160), position INTEGER);";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "CREATE TABLE Units(Unit Varchar(32));";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      if(oletukset)
	  {
        // Lisätään joitain suureita Unit-tauluun
        sql  = "INSERT INTO Units(Unit) VALUES('"; sql += _UNIT_MIN_; sql += "');";
        sql += "INSERT INTO Units(Unit) VALUES('h');";
        sql += "INSERT INTO Units(Unit) VALUES('kg');";
        sql += "INSERT INTO Units(Unit) VALUES('g');";
        sql += "INSERT INTO Units(Unit) VALUES('mg');";
        sql += "INSERT INTO Units(Unit) VALUES('km');";
        sql += "INSERT INTO Units(Unit) VALUES('m');";
        sql += "INSERT INTO Units(Unit) VALUES('cm');";
        sql += "INSERT INTO Units(Unit) VALUES('mm');";
        if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

        // Piilotettu "oletus" laskuttaja. Laskuttaja poistettaessa kytkös laskuttajaan rikkoutuu -> aseta tähän (eli Biller_id = 1)
        sql = "INSERT INTO Biller(Name, Email) VALUES('" + CString(DFLT_BILLER) + "', '" + CString(DFLT_BILLER) + "');";
        if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));
	  }

      sqlite3_close(pdb);
	}
    catch(int err)
	{
      DeleteFile(*db_path);                          // tuhotaan mahdollisesti keskeneräiseksi jäänyt tiedosto (tietokanta)

      if(pdb)
	  {
		*db_path = dbErrMsg(pdb);                    // virheteksti
        sqlite3_close(pdb);                          // Tietokanta kiinni
	  }

      return err;
	}

    return RETURN_OK;
}

CString DbSqlite::_2UTF8(CString srce)
{
    int len;
    CString dest;
    char *lpstr;

    // Muunnetaan CString UTF8-merkistön mukaiseksi, koska sqlite käyttää em. merkistöä
    USES_CONVERSION;                       // määritetty ATLCONV.H
    len = (srce.GetLength() + 1) * 2;      // Tarpeeksi tilaa mjonolle jonka kaikki merkit täytyisi muuntaa
    if((lpstr = new char[len]))
	{
      WideCharToMultiByte(CP_UTF8, 0, A2W(srce), -1, lpstr, len, NULL,  NULL);
      dest = lpstr;
      delete [] lpstr;
	}
    else dest = "";

    return dest;
}

CString DbSqlite::dbErrMsg(sqlite3 *pdb)
{
    CString errmsg = sqlite3_errmsg(pdb);
    return errmsg;
}

void DbSqlite::eiDB(BOOL verbose)
{
    if(verbose) {}; // MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), Props::i().lang("DBSQLITE_5"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
}

// CString DbSqlite::_2MBCS(CString srce)
// {
//     int len;
//     CString dest;
//     LPWSTR lpwstr;
// 
//     // Muunnetaan UTF8 Unicode-merkistön mukaiseksi
//     USES_CONVERSION;                       // määritetty ATLCONV.H
//     len = (srce.GetLength() + 1) * 2;      // Tarpeeksi tilaa mjonolle jonka kaikki merkit täytyisi muuntaa
//     if((lpwstr = new unsigned short[len]))
// 	{
//       MultiByteToWideChar(CP_UTF8, 0, srce, -1, lpwstr, len);
//       dest = lpwstr;
//       delete [] lpwstr;
// 	}
//     else dest = "";
// 
//     return dest;
// }

vector<int > DbSqlite::haePaivaykset(CString taulu, CString sarake)
{  // Haetaan annetun taulun kaikki [StartDate|EndDate]-sarakkeet
    int i;
    sqlite3 *pdb = NULL;
    sqlite3_stmt *pstmt = NULL;
    const char *pzTail;
    int col; // const unsigned char *pCol;
    CString sql;
    vector<int > vect;

    if(Props::e().m_db_path == "") { eiDB(1); return vect; }  // Tietokanta määrittämättä -> poistu
    try
	{
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "SELECT DISTINCT " + sarake + " FROM " + taulu + ";";// SQL-lause
      pzTail = sql; pzTail += sql.GetLength();       // Asetaan osoittaamaan SQL-lauseen loppuun
      if(sqlite3_prepare(pdb, sql, sql.GetLength(), &pstmt, &pzTail) != SQLITE_OK) throw(sqlite3_errcode(pdb)); // Valmistellaan tulosjoukko

      while(1)
	  {
        i = sqlite3_step(pstmt);                     // Otetaan rivi tulosjoukosta
        if(i == SQLITE_DONE) break;
        else if(i == SQLITE_ERROR) throw(0);

        col = sqlite3_column_int(pstmt, 0);          // Otetaan sarakkeesta tieto (kokonaisluku)
        vect.push_back(col);
	  }
	}
    catch(...)
	{}

    if(pstmt) sqlite3_finalize(pstmt);
    if(pdb != 0) sqlite3_close(pdb);

    return vect;
}

int DbSqlite::callback(void *pArg, int argc, char **argv, char **azColName)
{ // Palauttaa SQL-kyselyn tuloksesta saadun tulosten lukumäärän (SELECT ...)
    return argc;
}

int DbSqlite::vacuum(CString dbpath)
{ // Tiivistetään määritetty tietokanta
    sqlite3 *pdb = NULL;
	CString sql;
    vector <CString> col_data, vect;

    if(dbpath == "") { eiDB(1); return NODB; }           // Tietokanta määrittämättä -> poistu
    try
	{
      if(sqlite3_open(_2UTF8(dbpath), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));
      sql = "VACUUM";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));
      sqlite3_close(pdb);
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_6"), err, errmsg);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

void DbSqlite::escape_vc(vector <CString> *pvect)
{ // Poistetaan hipsut ja varmistetaan, että mjono ei ole tyhjä (tiedonhaku "kaatuu" muuten <- ? onko näin!)
    int i, s;

    s = pvect->size();
    for(i=0; i<s; i++)
	{
      //if(pvect->at(i) == "") pvect->at(i) = " ";     // Tyhjät mjonot pois
      pvect->at(i).Replace("\'", "");                // Hipsut pois
	}

}

void DbSqlite::escape_c(CString *pcs)
{ // Poistetaan hipsut ja varmistetaan, että mjono ei ole tyhjä
    //if(*pcs == "") *pcs = " ";                       // Tyhjät mjonot pois
    pcs->Replace("\'", "");                          // Hipsut pois
}

vector<CString > DbSqlite::haeTaulusta(CString table, CString cols, int num_cols, CString order, int num_ehto, ...)
{  // Haetaan annetusta tiettyjen annettujen sarakkeiden tiedot annetulla määrällä ehtoja tai ilman ehtoja annetussa järjestyksessä
   // Ehdot: looginen operaattori, sarake, operaattori,   arvo    -> eli 4 LPCSTR:iä per ehto-lause, num_ehto ilmoittaa ehtojen määrän
   //  esim.         AND            Name        =       't-aika'
    int i;
    sqlite3 *pdb = NULL;
    sqlite3_stmt *pstmt = NULL;
    const char *pzTail;
    const unsigned char *pCol;
    CString sql;
    vector<CString > vect;

    if(Props::e().m_db_path == "") { eiDB(1); return vect; }  // Tietokanta määrittämättä -> poistu
    try
	{
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "SELECT " + cols + " FROM " + table;     // Sarakkeet (col voi sisältää useita pilkulla erotettuja sarakkeita)

      va_list args;                                  // alusta variable arguments
      va_start(args, num_ehto);
      if(num_ehto > 0) sql += " WHERE";              // WHERE täytyy olla
      while(num_ehto > 0)
	  {
        sql += " "; sql += va_arg(args, LPCSTR); sql += " ";         // ehtojen välinen looginen operaattori
                    sql += va_arg(args, LPCSTR);                     // sarake josta haetaan
                    sql += va_arg(args, LPCSTR);                     // operaattori jolla verrataan (<, >, =, ...)
        sql += "'"; sql += va_arg(args, LPCSTR); sql += "'";         // arvo johon verrataan
        num_ehto--;
	  }
      va_end(args);                                  // asetetaan variable arguments NULL-arvoon

      if(order != "")
        sql += " ORDER BY " + order + ";";           // : järjestys
      else sql += ";";

      pzTail = sql; pzTail += sql.GetLength();                                     // Asetaan osoittaamaan SQL-lauseen loppuun
      if(sqlite3_prepare(pdb, sql, sql.GetLength(), &pstmt, &pzTail) != SQLITE_OK) throw(sqlite3_errcode(pdb)); // Valmistellaan tulosjoukko

      while(1)
	  {
        i = sqlite3_step(pstmt);                     // Otetaan rivi tulosjoukosta
        if(i == SQLITE_DONE) break;
        else if(i == SQLITE_ERROR) throw(0);

        for(i=0; i<num_cols; i++)
		{
          pCol = sqlite3_column_text(pstmt, i);    // otetaan haettava sarake talteen
          vect.push_back(pCol);
		}
	  }
	}
    catch(...)
	{}

    if(pstmt) sqlite3_finalize(pstmt);
    if(pdb != 0) sqlite3_close(pdb);

    return vect;
}

int DbSqlite::poistaYleinen(CString table, CString column, CString value, BOOL verbose, CString dbpath)
{ // Päivitä annetun taulun annettu kenttä annetulla uudella arvolla
    sqlite3 *pdb = NULL;
	CString sql, db_path;
    vector <CString> col_data, vect;

    if(dbpath != "") db_path = dbpath;               // Voidaan antaa joku toinen kuin oletustietokanta
    else db_path = Props::e().m_db_path;

    if(db_path == "") { eiDB(1); return NODB; }          // Tietokanta määrittämättä -> poistu
    try
	{
      if(sqlite3_open(_2UTF8(db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));
      sql = "DELETE FROM " + table;
      if(column != "")                               // ehto
        sql += " WHERE " + column + "='" + value + "';";
      else                                           // ei ehtoa, tyhjennä koko taulu
        sql += ";";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));
      sqlite3_close(pdb);
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_7"), err, errmsg);
      if(verbose) MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

int DbSqlite::paivitaYleinen(CString table, CString column, CString vanha, CString uusi, BOOL verbose)
{ // Päivitä annetun taulun annettu kenttä annetulla uudella arvolla
	CString sql;
    sqlite3 *pdb = NULL;

    escape_c(&uusi);                                 // escapointi

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));
      sql = "UPDATE " + table + " SET " + column + "='" + uusi + "' WHERE " + column + "='" + vanha + "';";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));
      sqlite3_close(pdb);
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_8"), err, errmsg);
      if(verbose) MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

int DbSqlite::paivitaYleinen_id(CString table, CString col1, CString data1, CString col2, CString data2, CString id, BOOL exists)
{ // Päivitetään annetut kentät tauluun, kentät annettu sarake/tieto-pareina
	CString sql;
    sqlite3 *pdb = NULL;
    vector <CString> col_data, vect;

    escape_c(&col1);                                 // escapointi
    escape_c(&col2);
    escape_c(&data1);
    escape_c(&data2);
    escape_c(&id);

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      // Aukaistaan tietokanta
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      // Tarkista onko jo olemassa samalla tiedolla jossain toisessa (miksi kahdella olisi esim. sama nimi? voi olla, mutta miksi?)
      if(exists)
	  {
        sql = "SELECT " + col1 + " FROM " + table + " WHERE " + col1 + "='" + data1 + "' AND id<>'" + id + "';";
        if((sqlite3_exec(pdb, sql, callback, 0, NULL)) != SQLITE_OK)
          throw(RETURN_EXISTS);                          // Oli olemassa -> ei voi muokata
	  }

      // Voi muokata, muutetaan annetut kentät
      sql = "UPDATE " + table + " SET " + col1 + "='" + data1 + "'";
      if(col2 != "") sql += ", " + col2 + "='" + data2 + "'";
      sql += " WHERE id='" + id + "';";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sqlite3_close(pdb);
	}
    catch(int err)
	{
      if(err != RETURN_EXISTS)
	  {
        CString errmsg;

        if(pdb) errmsg = dbErrMsg(pdb);
        sql.Format(Props::i().lang("DBSQLITE_9"), err, errmsg);
        MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

int DbSqlite::jarjestaPosition(CString table, CString col, CString data, CString pos_field, BOOL verbose)
{
	CString sql, cs;
    int i, j, pos = 1;
    sqlite3 *pdb = NULL;
    vector <CString> col_data, vect;

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      if(col == "")                                  // Hae päivitettävien rivien id:t (ehdossa (=col) esim. Region_id = ...)
	  { if((j = (vect = haeTaulusta(table, "id", 1, pos_field, 0)).size()) == 0) throw(SQLITE_OK); }
      else
	  { if((j = (vect = haeTaulusta(table, "id", 1, pos_field, 1, "", col, "=", data)).size()) == 0) throw(SQLITE_OK); }

      for(i=0; i<j; i++)
	  {
        cs.Format("%d", pos++);
        sql = "UPDATE " + table + " SET " + pos_field + "='" + cs + "' WHERE id='" + vect[i] + "';";
        if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));
	  }

      sqlite3_close(pdb);
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_10"), err, errmsg);
      if(verbose && err != SQLITE_OK) MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      if(err != SQLITE_OK) return err;
	}

    return RETURN_OK;
}

int DbSqlite::jarjestaPosition_fast(CString table, CString pos_field, CString position, BOOL verbose, CString col, CString data)
{
	CString sql, cs;
    sqlite3 *pdb = NULL;

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

	  if(col == "")   // ei lisäehtoja
        sql = "UPDATE " + table + " SET " + pos_field + "=" + pos_field + "-1 WHERE " + pos_field + ">" + position + ";";
	  else
        sql = "UPDATE " + table + " SET " + pos_field + "=" + pos_field + "-1 WHERE " + pos_field + ">" + position + " AND " + col + "='" + data + "';";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sqlite3_close(pdb);
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_11"), err, errmsg);
      if(verbose && err != SQLITE_OK) MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      if(err != SQLITE_OK) return err;
	}

    return RETURN_OK;
}

vector <CString> DbSqlite::etsi(CString table, CString ret_col, int num_cols, CString find_col, CString find_data, CString order)
{
    int i;
    sqlite3 *pdb = NULL;
    const char *pzTail;
    sqlite3_stmt *pstmt = NULL;
    const unsigned char *pCol;
    CString sql;
    vector<CString > vect;

    escape_c(&find_data);                            // escapointi

    if(Props::e().m_db_path == "") { eiDB(1); return vect; } // Tietokanta määrittämättä -> poistu
    try
	{
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "SELECT " + ret_col + " FROM " + table + " WHERE " + find_col + " LIKE '%" + find_data + "%' ORDER BY " + order + ";";

      pzTail = sql; pzTail += sql.GetLength();           // Asetaan osoittaamaan SQL-lauseen loppuun
      if(sqlite3_prepare(pdb, sql, sql.GetLength(), &pstmt, &pzTail) != SQLITE_OK) throw(sqlite3_errcode(pdb)); // Valmistellaan tulosjoukko

      while(1)
	  {
        i = sqlite3_step(pstmt);                         // Otetaan rivi tulosjoukosta
        if(i == SQLITE_DONE) break;
        else if(i == SQLITE_ERROR) throw(0);

        for(i=0; i<num_cols; i++)
		{
          pCol = sqlite3_column_text(pstmt, i);          // otetaan haettava sarake talteen
          vect.push_back(pCol);
		}
	  }
	}
    catch(int err)
	{
      CString errmsg;
      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_12"), err, errmsg);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}

    if(pstmt) sqlite3_finalize(pstmt);
    if(pdb != 0) sqlite3_close(pdb);

    return vect;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WorkUnit-tauluun kohdistuvat funktiot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbSqlite::lisaaWorkUnit(vector<CString> *pvect, CString WorkerName, CString ReportName, CString ReportDate, CString BillerName, CString Unit, CString Uprize, CString Tprize)
{
    int i;
    Paivays paivays;
    sqlite3 *pdb = NULL;
	CString sql, /*sqlu,*/ selectheader;
    CString WorkPlaceName, WorkTypeName, StartDate, StartTime, EndDate, EndTime, UnitValue, Type;
	CString Region = AUTOMATIC;
    CString Alv = ALV_TYOAIKA;
    vector <CString> vect;

    escape_vc(pvect);                                // escapointi
    escape_c(&WorkerName);
    escape_c(&ReportName);
    escape_c(&ReportDate);
    escape_c(&BillerName);
    escape_c(&Unit);
    escape_c(&Uprize);
    escape_c(&Tprize);

    if(Props::e().m_db_path == "") { eiDB(0); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      WorkPlaceName = pvect->at(0); WorkTypeName = pvect->at(1);
      StartTime = pvect->at(2); EndTime = pvect->at(3); UnitValue = pvect->at(4);
      //if(pvect->size() > 5) Type = pvect->at(5);
      //else Type = WORKUNIT;
      Type = ID_WORKUNIT;                            // Pakotetaan työajat TYPE_WORKUNIT-tyyppisiksi (id: 0)
      if(pvect->size() > 6)
	  {
	     Region = pvect->at(6);
	     Alv = pvect->at(7);
	  }
      StartDate = paivays.formatDateTime(StartTime, FORMAT_DATE);
      StartTime = paivays.formatDateTime(StartTime, FORMAT_TIME);
      EndDate = paivays.formatDateTime(EndTime, FORMAT_DATE);
      EndTime = paivays.formatDateTime(EndTime, FORMAT_TIME);
      ReportDate = paivays.formatDateTime(ReportDate, FORMAT_DATE);

      // Testataan ensin onko työ jo taulukossa
	  selectheader = "SELECT * FROM WorkUnit ";

	  sql = "WHERE StartDate='" + StartDate;
      sql += "' AND StartTime='" + StartTime; 
      sql += "' AND EndDate='" + EndDate;
      sql += "' AND EndTime='" + EndTime + "'";

      //sqlu = "UPDATE WorkUnit SET WorkerName='" + WorkerName + "' " + sql + ";";
      sql = selectheader + sql;

	  i = isWorkUnit(sql, &WorkPlaceName, &WorkTypeName, &WorkerName, Region, _UNSET_, Unit, &BillerName, WORK, _UNSET_, _UNSET_, _UNSET_, NULL, WORKTYPE_POSITION_WORK/*, sqlu*/);
      if(i == RETURN_EXISTS)
        return RETURN_EXISTS;    // Työ on jo taulussa -> pois
	  else if(i != RETURN_OK)
        throw(i);                // Virhe -> viesti käyttäjälle

      // Lisätään työ tietokantaan
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sql = "INSERT INTO WorkUnit(Worker_id, WorkPlace_id, WorkType_id, StartDate, StartTime, EndDate, EndTime, UnitValue, Charged, Unit, UnitPrice, TotalPrice, Alv, ReportName, ReportDate, Biller_id, Type) VALUES('" + WorkerName + "', '";
      sql += WorkPlaceName + "', '";
      sql += WorkTypeName + "', '";
      sql += StartDate + "', '";
      sql += StartTime + "', '";
      sql += EndDate + "', '";
      sql += EndTime + "', '";
      sql += UnitValue + "', '" + C_FALSE + "', '";
      sql += Unit + "', '";
      sql += Uprize + "', '";
      sql += Tprize + "', '";
      sql += Alv + "', '";
      sql += ReportName + "', '";
      sql += ReportDate + "', '";
      sql += BillerName + "', '";
      sql += Type + "');";
      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sqlite3_close(pdb);

      // Haetaan lisätyn WorkUnitin id ja laitetaan se paluuarvoksi vektoriin
      pvect->clear();
      vect = haeTaulusta("WorkUnit", "id", 1, "", 16,  "",    "Worker_id",   "=", WorkerName,
                                                       "AND", "WorkPlace_id", "=", WorkPlaceName,
                                                       "AND", "WorkType_id", "=", WorkTypeName,
                                                       "AND", "StartDate",    "=", StartDate,
                                                       "AND", "StartTime",    "=", StartTime,
                                                       "AND", "EndDate",      "=", EndDate,
                                                       "AND", "EndTime",      "=", EndTime,
                                                       "AND", "UnitValue",    "=", UnitValue,
                                                       "AND", "Charged",      "=", C_FALSE,
                                                       "AND", "Unit",         "=", Unit,
                                                       "AND", "UnitPrice",    "=", Uprize,
                                                       "AND", "TotalPrice",   "=", Tprize,
                                                       "AND", "Alv",          "=", Alv,
                                                       "AND", "ReportName",   "=", ReportName,
                                                       "AND", "ReportDate",   "=", ReportDate,
                                                       "AND", "Biller_id",    "=", BillerName,
                                                       "AND", "Type",         "=", Type);
      if(vect.size() > 0) pvect->push_back(vect[0]);
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_13"), err, errmsg);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

int DbSqlite::lisaaSalesUnit(vector<CString> *pvect, CString WorkerName, CString ReportName, CString ReportDate, CString BillerName)
{
	int i;
    Paivays paivays;
    sqlite3 *pdb = NULL;
    vector <CString> vect;
    CString Region = AUTOMATIC;
	CString ProductGroup = PRODUCTLIST_ASSUMED;
    CString WorkPlaceName, WorkTypeName, StartDate, StartTime, EndDate, EndTime, Unit, UnitValue, UnitPrice, TotalPrice, ProductNumber, Alv, Type, sql, /*sqlu,*/ selectheader;

    escape_vc(pvect);                                // escapointi
    escape_c(&WorkerName);
    escape_c(&ReportName);
    escape_c(&ReportDate);
    escape_c(&BillerName);

    if(Props::e().m_db_path == "") { eiDB(0); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      WorkPlaceName = pvect->at(0); WorkTypeName = pvect->at(1);
	  StartTime = pvect->at(2);
      Unit = pvect->at(3); UnitValue = pvect->at(4);
      Type = ID_SALESUNIT; // Pakotetaan TYPE_SALESUNIT (id: 1) pvect->at(5);
      UnitPrice = pvect->at(6); TotalPrice = pvect->at(7);
      ProductNumber = pvect->at(8); Alv = pvect->at(9);
      if(pvect->size()>10)
		Region = pvect->at(10);       // koon ollessa alle 10 ryhmä on AUTOMATIC (asetettu muuttujan alustuksessa)
	  if(pvect->size()>11)
		ProductGroup = pvect->at(11); // koon ollessa alle 11 ryhmä on PRODUCTLIST_ASSUMED (asetettu muuttujan alustuksessa)

      StartDate = EndDate = paivays.formatDateTime(StartTime, FORMAT_DATE);
      StartTime = EndTime = paivays.formatDateTime(StartTime, FORMAT_TIME);
      ReportDate = paivays.formatDateTime(ReportDate, FORMAT_DATE);

      // Muunnetaan UnitValue, UnitPrice ja TotalPrice liukuluvuksi
      //---!!!muutettu, nyt tulee valmiiksi desimaalilukuja
	/*
      char cnv[16];
	  i = atoi(UnitValue.c_str()); j = i % 100; i /= 100;
      itoa(i, cnv, 10); UnitValue = cnv; UnitValue += ".";
      itoa(j, cnv, 10); UnitValue += cnv;

      i = atoi(UnitPrice.c_str()); j = i % 100; i /= 100;
      itoa(i, cnv, 10); UnitPrice = cnv; UnitPrice += ".";
      itoa(j, cnv, 10); UnitPrice += cnv;

      i = atoi(TotalPrice.c_str()); j = i % 100; i /= 100;
      itoa(i, cnv, 10); TotalPrice = cnv; TotalPrice += ".";
      itoa(j, cnv, 10); TotalPrice += cnv;
	*/
      // Testataan onko SalesUnit jo taulukossa
      selectheader = "SELECT * FROM WorkUnit ";

	  sql = "WHERE Unit='" + Unit;
      sql += "' AND StartDate='" + StartDate;
      sql += "' AND StartTime='" + StartTime;
      sql += "' AND EndDate='" + EndDate;
      sql += "' AND EndTime='" + EndTime + "'";
	  
      //sqlu = "UPDATE WorkUnit set WorkerName='" + WorkerName + "' " + sql +  + ";";
      sql = selectheader + sql;
	  
	  i = isWorkUnit(sql, &WorkPlaceName, &WorkTypeName, &WorkerName, Region, ProductNumber, Unit, &BillerName, PRODUCT, _UNSET_, _UNSET_, Alv, &ProductGroup, WORKTYPE_POSITION_PRODUCT/*, sqlu*/);
      if(i == RETURN_EXISTS)
        return RETURN_EXISTS;    // kassa on jo taulussa -> pois
	  else if(i != RETURN_OK)
        throw(i);                // Virhe -> viesti käyttäjälle

      // Lisätään työ tietokantaan
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));
	
      sql = "INSERT INTO WorkUnit(Worker_id, WorkPlace_id, WorkType_id, StartDate, StartTime, EndDate, EndTime, UnitValue, Charged, Unit, UnitPrice, TotalPrice, Alv, ReportName, ReportDate, Biller_id, Type) VALUES('" + WorkerName + "', '";
      sql += WorkPlaceName + "', '";
      sql += WorkTypeName + "', '";
      sql += StartDate + "', '";
      sql += StartTime + "', '";
      sql += StartDate + "', '";
      sql += StartTime + "', '";
      sql += UnitValue + "', '" + C_FALSE + "', '";
      sql += Unit + "', '";
      sql += UnitPrice + "', '";
	  sql += TotalPrice + "', '";
      sql += Alv + "', '";
      sql += ReportName + "', '";
      sql += ReportDate + "', '";
      sql += BillerName + "', '";
      sql += Type + "');";
      if((sqlite3_exec(pdb, sql, NULL, 0, NULL)) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sqlite3_close(pdb);

      // Haetaan lisätyn WorkUnitin id ja laitetaan se paluuarvoksi vektoriin
      pvect->clear();
      vect = haeTaulusta("WorkUnit", "id", 1, "", 16,  "",    "Worker_id",   "=", WorkerName,
                                                       "AND", "WorkPlace_id", "=", WorkPlaceName,
                                                       "AND", "WorkType_id", "=", WorkTypeName,
                                                       "AND", "StartDate",    "=", StartDate,
                                                       "AND", "StartTime",    "=", StartTime,
                                                       "AND", "EndDate",      "=", EndDate,
                                                       "AND", "EndTime",      "=", EndTime,
                                                       "AND", "UnitValue",    "=", UnitValue,
                                                       "AND", "Charged",      "=", C_FALSE,
                                                       "AND", "Unit",         "=", Unit,
                                                       "AND", "UnitPrice",    "=", UnitPrice,
                                                       "AND", "TotalPrice",   "=", TotalPrice,
                                                       "AND", "Alv",          "=", Alv,
                                                       "AND", "ReportName",   "=", ReportName,
                                                       "AND", "ReportDate",   "=", ReportDate,
                                                       "AND", "Biller_id",    "=", BillerName,
                                                       "AND", "Type",         "=", Type);
      if(vect.size() > 0) pvect->push_back(vect[0]);
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_14"), err, errmsg); // Myyntitapahtuman lisääminen epäonnistui
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

int DbSqlite::isWorkUnit(CString check, CString *WorkPlaceName, CString *WorkTypeName, CString *WorkerName, CString Region, CString ProductNumber, CString Unit, CString *BillerName, CString Type, CString PurchasePrice, CString SellPrice, CString Alv, CString *ProductGroup, CString pos_field/*, CString sqlu*/)
{
	CString apu;
    vector <CString> vect;
    sqlite3 *pdb = NULL;

    try
	{
      // Aukaistaan tietokanta
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      // Haetaan alueen id. Jos aluetta ei ole, lisätään se.
      lisaaRegion(Region, &Region);

      // Haetaan laskuttajan id. Jos laskuttajaa ei ole, lisätään se.
      lisaaBiller(*BillerName, "", BillerName, B_NOUPDATE);

      // Haetaan työkohteen id. Jos työkohdetta ei ole, lisätään se. Biller_id on BillerNamessa.
      lisaaWorkPlace(*WorkPlaceName, Region, _UNSET_, "", "", "", "", *BillerName, WorkPlaceName, WP_NOUPDATE);

      // Haetaan tuoteryhmän id. Jos tuoteryhmää ei ole, lisätään se.
	  if(ProductGroup != NULL)
	    lisaaProductGroup(*ProductGroup, ProductGroup);

      // Haetaan työtyypin id. Jos työtyyppiä ei ole, lisätään se.
      lisaaWorkType(*WorkTypeName, ProductNumber, Type, Unit, PurchasePrice, SellPrice, Alv, ProductGroup == NULL ? "" : *ProductGroup, pos_field, WorkTypeName, WT_NOUPDATE);

      // Haetaan työntekijän id. Jos työntekijää ei ole, lisätään se.
      lisaaWorker(*WorkerName, WorkerName);

      // Testataan onko suure jo mainittu WorkUnit-taulussa. Lisätään tarvittaessa.
	  lisaaUnit(Unit);

      check += " AND WorkPlace_id=" + *WorkPlaceName;// Taydennä hakuehtoon id:t ennen tarkistusta
      check += " AND WorkType_id=" + *WorkTypeName;
      check += " AND Worker_id=" + *WorkerName + ";";

      //Tarkistetaan, onko työsuoritus jo tallennettu
	  if((sqlite3_exec(pdb, check, callback, NULL, NULL)) == SQLITE_OK)
        sqlite3_close(pdb);
      else
		throw(RETURN_EXISTS);
	}
    catch(int err)
	{
      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

vector<CString > DbSqlite::suodataWorkUnit(vector <CString> asiakkaat, vector <CString> tyotyypit, vector <CString> tyontekijat, CString startdate, CString enddate, int charged, CString type, CString order)
{ // Hae tietyt asiakkaat, joille tietyt työntekijät ovat tehneet tiettyä työtä, tietyllä aikavälillä huomioiden myös laskutuksen tilan
    int i, s;
    sqlite3 *pdb = NULL;
    sqlite3_stmt *pstmt = NULL;
    const char *pzTail;
    const unsigned char *pCol;
    CString sql;
    vector<CString > vect;

    if(Props::e().m_db_path == "") { eiDB(1); return vect; }  // Tietokanta määrittämättä -> poistu
    try
	{
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      escape_vc(&asiakkaat);                         // escapointi
      escape_vc(&tyotyypit);
      escape_vc(&tyontekijat);

      sql = "SELECT * FROM WorkUnit WHERE";

      if(!(s = asiakkaat.size())) return vect;       // Haetut asiakkaiden nimet hakuehtoihin, asiakkaita täytyy olla valittuna!!!
      sql += " (WorkPlace_id=";                      // ehdot sulkuihin, koska useista mjonoista muodostetaan yksi totuusarvo!!!
      for(i=0; i<s; i+=4) // 4, koska vektorissa id, Name, CustomerNumber, Region_id
	  {
        sql += "'" + asiakkaat[i] + "'";
        if(i + 4 < s) sql += " OR WorkPlace_id=";
	  }
      sql += ")";

      if(!(s = tyotyypit.size())) return vect;       // Haetut työtyypit hakuehtoihin, työtyyppejä täytyy olla valittuna!!!
      sql += " AND (WorkType_id=";
      for(i=0; i<s; i++)
	  {
        sql += "'" + tyotyypit[i] + "'";
        if(i + 1 < s) sql += " OR WorkType_id=";
	  }
      sql += ")";

      if(!(s = tyontekijat.size())) return vect;     // Haetut työntekijat hakuehtoihin, työntekijöitä täytyy olla valittuna!!!
      sql += " AND (Worker_id=";
      for(i=0; i<s; i++)
	  {
        sql += "'" + tyontekijat[i] + "'";
        if(i + 1 < s) sql += " OR Worker_id=";
	  }
      sql += ")";
                                                     // Aikaväliltä startdate - enddate
      sql += " AND (StartDate BETWEEN " + startdate + " AND " + enddate + ")";

      if(charged == UNCHARGED)                       // Laskutettu, laskuttamaton vai kaikki (eli ei rajoiteta)
	  { sql += " AND Charged='"; sql += C_FALSE; sql += "'"; }
      else if(charged == CHARGED)
	  { sql += " AND Charged='"; sql += C_TRUE; sql += "'"; }

      /*if(type != TM_BOTH && type != MT_BOTH)*/ sql += " AND Type='" + type +  "'";

      sql += " ORDER BY ";                           // SQL-lause loppuu -> tyyppi (ASC/DESC), aikajärjestys (ASC/DESC)
      /*if(type == TM_BOTH) sql += " Type ASC,";
      else if(type == MT_BOTH) sql += " Type DESC,";*/
      sql += " StartDate " + order + ", StartTime " + order + ";";

      pzTail = sql; pzTail += sql.GetLength();       // Asetaan osoittaamaan SQL-lauseen loppuun
      if(sqlite3_prepare(pdb, sql, sql.GetLength(), &pstmt, &pzTail) != SQLITE_OK) throw(sqlite3_errcode(pdb)); // Valmistellaan tulosjoukko

      while(1)
	  {
        i = sqlite3_step(pstmt);                     // Otetaan rivi tulosjoukosta
        if(i == SQLITE_DONE) break;
        else if(i == SQLITE_ERROR) throw(0);

        for(i=0; i<WORKUNIT_COLS; i++)
		{
          pCol = sqlite3_column_text(pstmt, i);      // Worker_id, WorkPlace_id, WorkType_id, StartDate, StartTime, EndDate, EndTime, Unit, UnitValue, Charged, UnitPrice, TotalPrice, Alv, ReportName, ReportDate, Biller_id, Type
          vect.push_back(pCol);
		}
	  }
	}
    catch(...)
	{}

    if(pstmt) sqlite3_finalize(pstmt);
    if(pdb != 0) sqlite3_close(pdb);

    return vect;
}

int DbSqlite::paivitaWorkUnit(ItemData *pid, int num_cols, ...)
{ // Päivitetään annetut kentät WorkUnit-tauluun, kentät annettu sarake/tieto-pareina, num_cols ilmoittaaa parien määrän
    int i, j, s;
    ItemData id;
	CString sql;
    sqlite3 *pdb = NULL;
    vector <CString> col_data, vect;
    CString cols[(WORKUNIT_COLS - 1) * 2] = { WORKUNIT_WORKER_ID, "", WORKUNIT_WORKPLACE_ID, "", WORKUNIT_WORKTYPE_ID, "", WORKUNIT_STARTDATE,  "", WORKUNIT_STARTTIME, "", 
		                                      WORKUNIT_ENDDATE, "", WORKUNIT_ENDTIME, "", WORKUNIT_UNIT, "", WORKUNIT_UNITVALUE, "", WORKUNIT_CHARGED, "", WORKUNIT_UNITPRICE, "", 
								              WORKUNIT_TOTALPRICE, "", WORKUNIT_ALV, "", WORKUNIT_REPORTNAME,  "", WORKUNIT_REPORTDATE, "", WORKUNIT_BILLER_ID, "", WORKUNIT_TYPE, "" };

    va_list args;                                    // alusta variable arguments
    va_start(args, num_cols);
    while(num_cols-- > 0)                            // Haetaan sarake/tieto-parit vektoriin (päivitettävät tiedot)
	{
      col_data.push_back(va_arg(args, LPCSTR));          // sarake
      col_data.push_back(va_arg(args, LPCSTR));          // tieto
	}
    va_end(args);                                    // asetetaan variable arguments NULL-arvoon

    escape_vc(&col_data);                            // escapointi

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      // Aukaistaan tietokanta
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      if(!(s = col_data.size())) return RETURN_NOACTION; // sarake/data-parit SET-osaan

      // Tarkistetaan ensin onko samanlainen rivi jo olemassa. Vektorissa tulee col/data-pareja -> mitkä tahansa kentät voi muuttua -> tutkitaan mitä tuli, ja tehdään sen mukaan SELECT-lause muutettavista ja entisistä arvoista
      for(i=0; i<(WORKUNIT_COLS - 1)* 2; i+=2)
	  {
        for(j=0; j<s; j+=2)                              // Mitä tuli, otetaan ylös (muut pysyvät "" arvossa)
		{
          if(col_data[j] == cols[i]) 
			  cols[i + 1] = col_data[j + 1];
		}
	  }
      if(cols[1] == "") cols[1] = pid->Worker_id;        // -> Mitkä jäi ""-arvoihin, niihin vanhat arvot ItemDatasta
      if(cols[3] == "") cols[3] = pid->WorkPlace_id;
      if(cols[5] == "") cols[5] = pid->WorkType_id;
      if(cols[7] == "") cols[7] = pid->StartDate;
      if(cols[9] == "") cols[9] = pid->StartTime;
      if(cols[11] == "") cols[11] = pid->EndDate;
      if(cols[13] == "") cols[13] = pid->EndTime;
      if(cols[15] == "") cols[15] = pid->Unit;
      if(cols[17] == "") cols[17] = pid->UnitValue;
      if(cols[19] == "") cols[19] = pid->Charged;
      if(cols[21] == "") cols[21] = pid->UnitPrice;
      if(cols[23] == "") cols[23] = pid->TotalPrice;
      if(cols[25] == "") cols[25] = pid->Alv;
      if(cols[27] == "") cols[27] = pid->ReportName;
      if(cols[29] == "") cols[29] = pid->ReportDate;
      if(cols[31] == "") cols[31] = pid->Biller_id;
      if(cols[33] == "") cols[33] = pid->Type;
      sql = "SELECT DISTINCT Unit FROM WorkUnit WHERE "; // Muodostetaan SELECT-lause
      for(i=0; i<(WORKUNIT_COLS - 1) * 2; i+=2)
	  {
        sql += cols[i];                                  // sarake
        if(cols[i] != WORKUNIT_STARTDATE && cols[i] != WORKUNIT_ENDDATE)
          sql += "='" + cols[i + 1] + "'";               // teksti-data
        else
          sql += "=" + cols[i + 1];                      // integer-data
        if(i + 2 < (WORKUNIT_COLS - 1) * 2) sql += " AND ";    // jos ei ollut viimeinen col/data-pari
	  }
      sql += ";";

      if((sqlite3_exec(pdb, sql, callback, 0, NULL)) != SQLITE_OK)
        throw(RETURN_EXISTS);                            // Oli olemassa -> ei voi muokata

      // Voi muokata, muutetaan annetut kentät
      sql = "UPDATE WorkUnit SET ";
      for(i=0; i<s; i+=2)
	  {
        sql += col_data[i];                          // sarake
        sql += "='" + col_data[i + 1] + "'";         // data
        if(i + 2 < s) sql += ", ";                   // jos ei ollut viimeinen col/data-pari
	  }
      sql += " WHERE id=" + pid->id + ";";

      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sqlite3_close(pdb);
	}
    catch(int err)
	{
      if(err != RETURN_EXISTS)
	  {
        CString errmsg;

        if(pdb) errmsg = dbErrMsg(pdb);
        sql.Format(Props::i().lang("DBSQLITE_15"), err, errmsg);
        MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WorkPlace-tauluun kohdistuvat funktiot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbSqlite::lisaaWorkPlace(CString Name, CString Region_id, CString CustomerNumber, CString Address, CString Note, CString Shortnote, CString Info, CString Biller_id, CString *id, int update)
{  // Lisää tauluun uuden työkohteen, palauttaa sen yksilöllisen id:n
    DlgPaivita dlg;
    sqlite3 *pdb = NULL;
    vector <CString> vect;
    vector <CString> vect_r;
    vector <CString> vect_b;
	CString sql, position;

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      escape_c(&Name);                               // escapointi
      escape_c(&Region_id);
      escape_c(&CustomerNumber);
      escape_c(&Address);
      escape_c(&Note);
      escape_c(&Shortnote);
      escape_c(&Info);

      vect = haeTaulusta("WorkPlace", "id, Name, Region_id, CustomerNumber, Address, Note, Shortnote, Info, Biller_id", 9, "", 2, "", "Name", "=", Name, "AND", "Region_id", "=", Region_id);
      if(vect.size() == 0)                                   // Uusi työkohde
	  {
        // Haetaan järjestysnumerot asiakkaalle - asiakkaat tietyssä asiakasryhmässä!!!
        vect = haeTaulusta("WorkPlace", "max(position)", 1, "", 1, "", "Region_id", "=", Region_id);
        position.Format("%d", atoi(vect[0]) + 1);

        // Aukaistaan tietokanta
        if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

        // Lisätään uusi asiakas
        sql = "INSERT INTO WorkPlace(Name, Region_id, CustomerNumber, Address, Note, Shortnote, Info, Biller_id, position) VALUES('";
        sql += Name + "', '" + Region_id + "', '" + CustomerNumber + "', '" + Address +  "', '" + Note + "', '" + Shortnote + "', '" + Info + "', '" + Biller_id+ "', '" + position + "');";
        if((sqlite3_exec(pdb, sql, NULL, 0, NULL)) != SQLITE_OK) throw(sqlite3_errcode(pdb));

        sqlite3_close(pdb);

        // Haetaan uusi id
        vect = haeTaulusta("WorkPlace", "id", 1, "", 4, "", "Name", "=", Name, "AND", "Region_id", "=", Region_id, "AND", "CustomerNumber", "=", CustomerNumber, "AND", "Address", "=", Address);
	  }
      else if(update == WP_JUSTADD && vect.size() != 0)
		  return RETURN_EXISTS;
      else if(update == WP_UPDATE && Props::e().m_yanc_wp != R_NOTA)	// Päivitä vanha ja ei valittu aiemmin 'No to All'?
	  {
        if(Props::e().m_yanc_wp != R_YESTA)									// Kysytään toiminto, jos ei valittu aiemmin 'Yes to All'
		{
          vect_r = haeTaulusta("Region", "Name", 1, "", 1, "", "id", "=", vect[2]);    // 
          vect_b = haeTaulusta("Biller", "Name", 1, "", 1, "", "id", "=", vect[8]);
          dlg.m_vect_v.push_back(vect_r[0]); dlg.m_vect_v.push_back(vect[1]);
          dlg.m_vect_v.push_back(vect[3]);   dlg.m_vect_v.push_back(vect[4]);
          dlg.m_vect_v.push_back(vect[5]);   dlg.m_vect_v.push_back(vect[6]);
          dlg.m_vect_v.push_back(vect[7]);   dlg.m_vect_v.push_back(vect_b[0]);
          vect_r = haeTaulusta("Region", "Name", 1, "", 1, "", "id", "=", Region_id);  // 
          vect_b = haeTaulusta("Biller", "Name", 1, "", 1, "", "id", "=", Biller_id);
          dlg.m_vect_u.push_back(vect_r[0]);
          dlg.m_vect_u.push_back(Name);      dlg.m_vect_u.push_back(CustomerNumber);
          dlg.m_vect_u.push_back(Address);   dlg.m_vect_u.push_back(Note);
          dlg.m_vect_u.push_back(Shortnote); dlg.m_vect_u.push_back(Info);
          dlg.m_vect_u.push_back(vect_b[0]);
          dlg.m_mode = UPDATE_ASIAKAS;                                                 // 
          Props::e().m_yanc_wp = dlg.DoModal();
		}

        if(Props::e().m_yanc_wp == R_YES || Props::e().m_yanc_wp == R_YESTA)                   //
		{
          if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));
          sql  = "UPDATE WorkPlace SET Name='"           + Name           + "', " +
                                      "Region_id='"      + Region_id      + "', " +
                                      "CustomerNumber='" + CustomerNumber + "', " +
                                      "Address='"        + Address        + "', " +
                                      "Note='"           + Note           + "', " +
                                      "Shortnote='"      + Shortnote      + "', " +
                                      "Info='"           + Info           + "', " +
                                      "Biller_id='"      + Biller_id      + "' WHERE id='" + vect[0] + "';";
          if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));
          sqlite3_close(pdb);
		}
	  }

	  if(id) *id = vect[0];                         // Annetaan paluuarvona vanha tai uusi, juuri luotu, id jos pyydetty (id != NULL)
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_16"), err, errmsg);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

int DbSqlite::paivitaWorkPlace(ItemData_workplace *pid, int num_cols, ...)
{ // Päivitetään annetut kentät WorkPlace-tauluun, kentät annettu sarake/tieto-pareina, num_cols ilmoittaaa parien määrän
    int i, s;
    ItemData id;
    sqlite3 *pdb = NULL;
	CString col, val, sql, name;
    vector <CString> col_data, vect;

    va_list args;                                    // alusta variable arguments
    va_start(args, num_cols);
    while(num_cols-- > 0)                            // Haetaan sarake/tieto-parit vektoriin (päivitettävät tiedot)
	{
      col_data.push_back((col = va_arg(args, LPCSTR)));	// sarake
      col_data.push_back((val = va_arg(args, LPCSTR)));	// tieto
      if(col == WORKPLACE_NAME) name = val;
	}
    va_end(args);                                    // asetetaan variable arguments NULL-arvoon

    escape_vc(&col_data);                            // escapointi

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      // Aukaistaan tietokanta
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      if(!(s = col_data.size())) return RETURN_NOACTION;	// sarake/data-parit SET-osaan

      // Tarkistetaan ensin onko sama nimi jo olemassa
	  if(name != "")
	  {
		sql = "SELECT id FROM WorkPlace WHERE Name='" + name + "' AND Region_id=" + CString(pid->Region_id) + " AND id<>" + pid->id;
		if((sqlite3_exec(pdb, sql, callback, 0, NULL)) != SQLITE_OK)
			throw(RETURN_EXISTS);                            // Oli olemassa -> ei voi muokata
	  }

      // Voi muokata, muutetaan annetut kentät
      sql = "UPDATE WorkPlace SET ";
      for(i=0; i<s; i+=2)
	  {
        sql += col_data[i];                          // sarake
        sql += "='" + col_data[i + 1] + "'";         // data
        if(i + 2 < s) sql += ", ";                   // jos ei ollut viimeinen col/data-pari
	  }
      sql += " WHERE id=" + pid->id + ";";

      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sqlite3_close(pdb);
	}
    catch(int err)
	{
      if(err != RETURN_EXISTS)
	  {
        CString errmsg;

        if(pdb) errmsg = dbErrMsg(pdb);
        sql.Format(Props::i().lang("DBSQLITE_17"), err, errmsg);
        MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Region-tauluun kohdistuvat funktiot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbSqlite::lisaaRegion(CString Name, CString *id)
{  // Lisää tauluun uuden asiakasryhmän (region), palauttaa sen yksilöllisen id:n
	CString sql, position;
    sqlite3 *pdb = NULL;
    vector <CString> vect;

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      escape_c(&Name);                               // escapointi

      // Haetaan id - jos ei löydy on kyseessä uusi
      vect = haeTaulusta("Region", "id", 1, "", 1, "", "Name", "=", Name);
      if(vect.size() == 0)
	  {
        // Haetaan järjestysnumero
        vect = haeTaulusta("Region", "max(position)", 1, "", 0);
        position.Format("%d", atoi(vect[0]) + 1);

        // Aukaistaan tietokanta
        if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

        // Lisätään uusi region
        sql = "INSERT INTO Region(Name, position) VALUES('";
        sql += Name + "', '" + position + "');";
        if((sqlite3_exec(pdb, sql, NULL, 0, NULL)) != SQLITE_OK) throw(sqlite3_errcode(pdb));

        sqlite3_close(pdb);

        // Haetaan uusi id
        vect = haeTaulusta("Region", "id", 1, "", 1, "", "Name", "=", Name);
	  }

	  if(id) *id = vect[0];                         // Annetaan paluuarvona vanha tai uusi, juuri luotu, id jos pyydetty (id != NULL)
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_18"), err, errmsg);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WorkType-tauluun kohdistuvat funktiot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbSqlite::lisaaWorkType(CString Name, CString ProductNumber, CString Type, CString Unit, CString PurchasePrice, CString SellPrice, CString Alv, CString ProductGroup_id, CString pos_field, CString *id, int update)
{  // Lisää tauluun uuden työtyypin, palauttaa sen yksilöllisen id:n
    DlgPaivita dlg;
	CString sql, position;
    sqlite3 *pdb = NULL;
    vector <CString> vect;

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      escape_c(&Name);                               // escapointi
      escape_c(&ProductNumber);
      escape_c(&Type);
      escape_c(&Unit);
      escape_c(&PurchasePrice);
      escape_c(&SellPrice);
      escape_c(&Alv);
      //escape_c(&ProductGroup_id);
      escape_c(&pos_field);

      vect = haeTaulusta("WorkType", "id, Name, ProductNumber, Type, Unit, PurchasePrice, SellPrice, Alv", 8, "", 2, "", "Name", "=", Name, "AND", "Type", "=", Type);
      if(vect.size() == 0)                                    // Lisätään uusi
	  {
        // Haetaan järjestysnumero - huomioidaan tuoteryhmä, tuotteilla järjestys ryhmittäin mutta työtyypit eivät ole missään ryhmässä!!!
        if(ProductGroup_id == "")
          vect = haeTaulusta("WorkType", "max(" + pos_field + ")", 1, "", 0);
		else
          vect = haeTaulusta("WorkType", "max(" + pos_field + ")", 1, "", 1, "", "ProductGroup_id", "=", ProductGroup_id);
        position.Format("%d", atoi(vect[0]) + 1);

        // Aukaistaan tietokanta
        if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

        // Lisätään uusi työkohde
        sql = "INSERT INTO WorkType(Name, ProductNumber, Type, Unit, PurchasePrice, SellPrice, Alv, " + pos_field + ", ProductGroup_id) VALUES('";
        sql += Name + "', '" + ProductNumber + "', '" + Type + "', '" + Unit + "', '" + PurchasePrice + "', '" + SellPrice + "', '" + Alv + "', '" + position + "', '" + ProductGroup_id + "');";
        if((sqlite3_exec(pdb, sql, NULL, 0, NULL)) != SQLITE_OK) throw(sqlite3_errcode(pdb));
        // Suljetaan tietokanta
        sqlite3_close(pdb);
        // Haetaan uusi id
        vect = haeTaulusta("WorkType", "id", 1, "", 2, "", "Name", "=", Name, "AND", "ProductNumber", "=", ProductNumber);
	  }
      else if(update == WT_JUSTADD && vect.size() != 0)
		  return RETURN_EXISTS;
      else if(update == WT_UPDATE && Props::e().m_yanc_wt != R_NOTA)	// Päivitä vanha ja ei valittu aiemmin 'No to All'?
	  {
        if(Props::e().m_yanc_wt != R_YESTA)									// Kysytään toiminto, jos ei valittu aiemmin 'Yes to All'
		{
          dlg.m_vect_v.push_back(vect[1]); dlg.m_vect_v.push_back(vect[2]);      //
          dlg.m_vect_v.push_back(vect[4]); dlg.m_vect_v.push_back(vect[5]);
		  dlg.m_vect_v.push_back(vect[6]); dlg.m_vect_v.push_back(vect[7]);
          dlg.m_vect_u.push_back(Name); dlg.m_vect_u.push_back(ProductNumber);
          dlg.m_vect_u.push_back(Unit); dlg.m_vect_u.push_back(PurchasePrice);
		  dlg.m_vect_u.push_back(SellPrice); dlg.m_vect_u.push_back(Alv);
		  if(vect[3] == WORK)                                                    //
            dlg.m_mode = UPDATE_TYOTYYPPI;
		  else if(vect[3] == PRODUCT)
            dlg.m_mode = UPDATE_TUOTE;
          Props::e().m_yanc_wt = dlg.DoModal();
		}
        if(Props::e().m_yanc_wt == R_YES || Props::e().m_yanc_wt == R_YESTA)     //
		{
          if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));
          sql  = "UPDATE WorkType SET Name='" + Name + "', " + "ProductNumber='" + ProductNumber + "', " + "Type='" + Type + "', " + "Unit='" + Unit + "', " + "PurchasePrice='" + PurchasePrice + "', " + "SellPrice='" + SellPrice + "', " + "Alv='" + Alv + "' WHERE id='" + vect[0] + "';";
          if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));
          sqlite3_close(pdb);
		}
	  }

	  if(id) *id = vect[0];                         // Annetaan paluuarvona vanha tai uusi, juuri luotu, id jos pyydetty (id != NULL)
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_19"), err, errmsg);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

int DbSqlite::paivitaWorkType(ItemData_type *pid, int num_cols, ...)
{ // Päivitetään annetut kentät WorkType-tauluun, kentät annettu sarake/tieto-pareina, num_cols ilmoittaaa parien määrän
    int i, s;
    ItemData id;
    sqlite3 *pdb = NULL;
	CString col, val, sql, name;
    vector <CString> col_data, vect;

    va_list args;                                    // alusta variable arguments
    va_start(args, num_cols);
    while(num_cols-- > 0)                            // Haetaan sarake/tieto-parit vektoriin (päivitettävät tiedot)
	{
      col_data.push_back((col = va_arg(args, LPCSTR)));	// sarake
      col_data.push_back((val = va_arg(args, LPCSTR)));	// tieto
      if(col == WORKTYPE_NAME) name = val;
	}
    va_end(args);                                    // asetetaan variable arguments NULL-arvoon

    escape_vc(&col_data);                            // escapointi

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      // Aukaistaan tietokanta
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      if(!(s = col_data.size())) return RETURN_NOACTION;	// sarake/data-parit SET-osaan

      // Tarkistetaan ensin onko sama nimi jo olemassa
	  if(name != "")
	  {
		sql = "SELECT id FROM WorkType WHERE Name='" + name + "' AND type='" + pid->Type + "' AND id<>" + pid->id;
		if((sqlite3_exec(pdb, sql, callback, 0, NULL)) != SQLITE_OK)
			throw(RETURN_EXISTS);                            // Oli olemassa -> ei voi muokata
	  }

      // Voi muokata, muutetaan annetut kentät
      sql = "UPDATE WorkType SET ";
      for(i=0; i<s; i+=2)
	  {
        sql += col_data[i];                          // sarake
        sql += "='" + col_data[i + 1] + "'";         // data
        if(i + 2 < s) sql += ", ";                   // jos ei ollut viimeinen col/data-pari
	  }
      sql += " WHERE id=" + pid->id + ";";

      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sqlite3_close(pdb);
	}
    catch(int err)
	{
      if(err != RETURN_EXISTS)
	  {
        CString errmsg;

        if(pdb) errmsg = dbErrMsg(pdb);
		sql.Format(Props::i().lang("DBSQLITE_20"), err, errmsg, (pid->Type == WORK ? Props::i().lang("DBSQLITE_21") : Props::i().lang("DBSQLITE_22")));
        MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Worker-tauluun kohdistuvat funktiot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbSqlite::lisaaWorker(CString Name, CString *id)
{  // Lisää tauluun uuden työntekijän, palauttaa sen yksilöllisen id:n
	CString sql;
    sqlite3 *pdb = NULL;
    vector <CString> vect;

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      escape_c(&Name);                               // escapointi

      // Haetaan id - jos ei löydy on kyseessä uusi laskuttaja
      vect = haeTaulusta("Worker", "id", 1, "", 1, "", "Name", "=", Name);
      if(vect.size() == 0)
	  {
        // Aukaistaan tietokanta
        if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

        // Lisätään uusi työkohde
        sql = "INSERT INTO Worker(Name) VALUES('" + Name + "');";
        if((sqlite3_exec(pdb, sql, NULL, 0, NULL)) != SQLITE_OK) throw(sqlite3_errcode(pdb));

        sqlite3_close(pdb);

        // Haetaan uusi id
        vect = haeTaulusta("Worker", "id", 1, "", 1, "", "Name", "=", Name);
	  }

	  if(id) *id = vect[0];                         // Annetaan paluuarvona vanha tai uusi, juuri luotu, id jos pyydetty (id != NULL)
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_23"), err, errmsg);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TravelUnit-tauluun kohdistuvat funktiot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbSqlite::lisaaTravelUnit(vector<CString> *pvect, CString WorkerName, CString ReportName, CString ReportDate, CString BillerName)
{
	float sd, ed;
    Paivays paivays;
    sqlite3 *pdb = NULL;
    vector <CString> vect;
    CString StartMeter, EndMeter, StartDate, StartTime, EndDate, EndTime, StartPlace, EndPlace, Private, Purpose, sql;

    escape_vc(pvect);                                // escapointi
    escape_c(&WorkerName);
    escape_c(&ReportName);
    escape_c(&ReportDate);
    escape_c(&BillerName);

    if(Props::e().m_db_path == "") { eiDB(0); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      StartMeter = pvect->at(0); EndMeter = pvect->at(1);
      StartTime = pvect->at(2); EndTime = pvect->at(3); Private = pvect->at(4);
      StartPlace = pvect->at(6); 
	  EndPlace = pvect->at(7); 
	  Purpose = pvect->at(8);
      StartDate = paivays.formatDateTime(StartTime, FORMAT_DATE);
      StartTime = paivays.formatDateTime(StartTime, FORMAT_TIME);
      EndDate = paivays.formatDateTime(EndTime, FORMAT_DATE);
      EndTime = paivays.formatDateTime(EndTime, FORMAT_TIME);
      ReportDate = paivays.formatDateTime(ReportDate, FORMAT_DATE);

      // Haetaan työntekijän id. Jos työntekijää ei ole, lisätään se.
      lisaaWorker(WorkerName, &WorkerName);

      // Tarkistetaan onko laskuttaja jo tietokannassa, lisätään jos ei ole
      lisaaBiller(BillerName, "", &BillerName, B_NOUPDATE);

	  // Testataan onko samalle ajalle jo työ jo taulukossa -> pois, ei lisätä jos on
      sd = atof(StartDate) + atof(StartTime) / 1440.0f;
      ed = atof(EndDate) + atof(EndTime) / 1440.0f;
      sql.Format(TU_DATES_CHECK, sd, sd, ed, ed, sd, ed);
      if((sqlite3_exec(pdb, "SELECT id FROM TravelUnit WHERE " + sql + " AND Worker_id=" + WorkerName, callback, 0, NULL)) != SQLITE_OK) throw(RETURN_EXISTS);

      // Lisätään työmatka tietokantaan
      sql = "INSERT INTO TravelUnit(StartMeter, EndMeter, StartDate, StartTime, EndDate, EndTime, StartPlace, EndPlace, Purpose, Private, Worker_id, ReportName, ReportDate, Biller_id) VALUES('";
      sql += StartMeter + "', '";
      sql += EndMeter + "', '";
      sql += StartDate + "', '";
      sql += StartTime + "', '";
      sql += EndDate + "', '";
      sql += EndTime + "', '";
	  sql += StartPlace + "', '";
      sql += EndPlace + "', '";
      sql += Purpose + "', '";
      sql += Private + "', '";
      sql += WorkerName + "', '";
      sql += ReportName + "', '";
      sql += ReportDate + "', '";
      sql += BillerName + "');";
      if((sqlite3_exec(pdb, sql, NULL, 0, NULL)) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sqlite3_close(pdb);

      // Haetaan lisätyn TravelUnitin id ja laitetaan se paluuarvoksi vektoriin
      pvect->clear();
      vect = haeTaulusta("TravelUnit", "id", 1, "", 14,  "",    "StartMeter", "=", StartMeter,
                                                         "AND", "EndMeter",   "=", EndMeter,
                                                         "AND", "StartDate",  "=", StartDate,
                                                         "AND", "StartTime",  "=", StartTime,
                                                         "AND", "EndDate",    "=", EndDate,
                                                         "AND", "EndTime",    "=", EndTime,
                                                         "AND", "StartPlace", "=", StartPlace,
                                                         "AND", "EndPlace",   "=", EndPlace,
                                                         "AND", "Purpose",    "=", Purpose,
                                                         "AND", "Private",    "=", Private,
                                                         "AND", "Worker_id",  "=", WorkerName,
                                                         "AND", "ReportName", "=", ReportName,
                                                         "AND", "ReportDate", "=", ReportDate,
                                                         "AND", "Biller_id",  "=", BillerName);
      if(vect.size() > 0) pvect->push_back(vect[0]);
	}
    catch(int err)
	{
      if(err != RETURN_OK && err != RETURN_EXISTS)
	  {
        CString errmsg;

        if(pdb) errmsg = dbErrMsg(pdb);
        sql.Format(Props::i().lang("DBSQLITE_24"), err, errmsg);
        MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

int DbSqlite::paivitaTravelUnit(ItemData_travel *pid, int num_cols, ...)
{ // Päivitetään annetut kentät TravelUnit-tauluun, kentät annettu sarake/tieto-pareina, num_cols ilmoittaaa parien määrän
    ItemData id;
	CString sql, cs;
	BOOL bDate = FALSE;
    sqlite3 *pdb = NULL;
    int i, s, ds;
	float sd, ed;
    vector <CString> col_data, vect;

	i = 0; ds = -1;
    va_list args;                                    // alusta variable arguments
    va_start(args, num_cols);
    while(num_cols-- > 0)                            // Haetaan sarake/tieto-parit vektoriin (päivitettävät tiedot), otetaan ylös indeksi päiväyksen alkuun
	{
      cs = va_arg(args, LPCSTR);
	  if(cs == TRAVELUNIT_STARTDATE) ds = i;
      col_data.push_back(cs);                            // sarake
      col_data.push_back(va_arg(args, LPCSTR));          // tieto
	  i += 2;
	}
    va_end(args);                                    // asetetaan variable arguments NULL-arvoon

    escape_vc(&col_data);                            // escapointi

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      // Aukaistaan tietokanta
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      if(!(s = col_data.size())) return RETURN_NOACTION; // sarake/data-parit SET-osaan

      // Tarkistetaan ensin onko työajo olemassa, eli tietty työntekijä saa samaan aikaan tehdä vain yhtä työmatkaa.
	  // TRAVELUNIT_STARTDATE, TRAVELUNIT_STARTTIME, TRAVELUNIT_ENDDATE ja TRAVELUNIT_ENDTIME tulevat peräkkäisinä pareina aina tässä järjestyksessä - niitä ei voi siten päivittää yksitellen tai muussa järjestyksessä!!!
	  if(ds != -1)
	  {
		sd = atof(col_data[ds + 1]) + atof(col_data[ds + 3]) / 1440.0f;
		ed = atof(col_data[ds + 5]) + atof(col_data[ds + 7]) / 1440.0f;
		sql.Format(TU_DATES_CHECK, sd, sd, ed, ed, sd, ed);
		if((sqlite3_exec(pdb, "SELECT id FROM TravelUnit WHERE " + sql + " AND id<>" + pid->id + " AND Worker_id=" + pid->Worker_id, callback, 0, NULL)) != SQLITE_OK)
			throw(RETURN_EXISTS);                            // Oli olemassa -> ei voi muokata
	  }

      // Voi muokata, muutetaan annetut kentät
      sql = "UPDATE TravelUnit SET ";
      for(i=0; i<s; i+=2)
	  {
        sql += col_data[i];                          // sarake
        sql += "='" + col_data[i + 1] + "'";         // data
        if(i + 2 < s) sql += ", ";                   // jos ei ollut viimeinen col/data-pari
	  }
      sql += " WHERE id=" + pid->id + ";";

      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sqlite3_close(pdb);
	}
    catch(int err)
	{
      if(err != RETURN_EXISTS)
	  {
        CString errmsg;

        if(pdb) errmsg = dbErrMsg(pdb);
        sql.Format(Props::i().lang("DBSQLITE_25"), err, errmsg);
        MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

vector <CString> DbSqlite::suodataTravelUnit(vector <CString> tyontekijat, CString startdate, CString enddate, CString order)
{ // Hae tietyt työmatkat, joita tietyt työntekijät ovat tehneet, tietyllä aikavälillä
    int i, s;
    sqlite3 *pdb = NULL;
    sqlite3_stmt *pstmt = NULL;
    const char *pzTail;
    const unsigned char *pCol;
    CString sql;
    vector<CString > vect;

    if(Props::e().m_db_path == "") { eiDB(1); return vect; }  // Tietokanta määrittämättä -> poistu
    try
	{
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      escape_vc(&tyontekijat);                       // escapointi

      sql = "SELECT * FROM TravelUnit WHERE";

      if(!(s = tyontekijat.size())) return vect;     // Haetut työntekijat hakuehtoihin, työntekijöitä täytyy olla valittuna!!!
      sql += " (Worker_id=";
      for(i=0; i<s; i++)
	  {
        sql += "'" + tyontekijat[i] + "'";
        if(i + 1 < s) sql += " OR Worker_id=";
	  }
      sql += ")";
                                                     // Aikaväliltä startdate - enddate
      sql += " AND (StartDate BETWEEN " + startdate + " AND " + enddate + ")";
         
      sql += " ORDER BY StartDate " + order + ", StartTime " + order + ";";  // SQL-lause loppuu, aikajärjestys

      pzTail = sql; pzTail += sql.GetLength();       // Asetaan osoittaamaan SQL-lauseen loppuun
      if(sqlite3_prepare(pdb, sql, sql.GetLength(), &pstmt, &pzTail) != SQLITE_OK) throw(sqlite3_errcode(pdb)); // Valmistellaan tulosjoukko

      while(1)
	  {
        i = sqlite3_step(pstmt);                     // Otetaan rivi tulosjoukosta
        if(i == SQLITE_DONE) break;
        else if(i == SQLITE_ERROR) throw(0);

        for(i=0; i<TRAVELUNIT_COLS; i++)
		{
          pCol = sqlite3_column_text(pstmt, i);      // id, StartMeter, EndMeter, StartDate, StartTime, EndDate, EndTime, StartPlace, EndPlace, Purpose, Private, Worker_id, ReportName, ReportDate, Biller_id
          vect.push_back(pCol);
		}
	  }
	}
    catch(...)
	{}

    if(pstmt) sqlite3_finalize(pstmt);
    if(pdb != 0) sqlite3_close(pdb);

    return vect;
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Units-tauluun kohdistuvat funktiot 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbSqlite::lisaaBiller(CString Name, CString Email, CString *id, int update)
{
    DlgPaivita dlg;
	CString sql, pos;
    sqlite3 *pdb = NULL;
    vector <CString> vect;

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      escape_c(&Name);                               // escapointi
      escape_c(&Email);

      vect = haeTaulusta("Biller", "id, Name, Email", 3, "", 1, "", "Name", "=", Name);
      if(vect.size() == 0)                                   // Lisää uusi
	  {
        // Aukaistaan tietokanta
        if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

		// Haetaan jrjestysnumero
        if((vect = haeTaulusta("Biller", "max(position)", 1, "", 0)).size() == 0)
			pos = "1";
		else
			pos.Format("%d", atoi(vect[0]) + 1);
		
		// Lisätään uusi laskuttaja
        sql = "INSERT INTO Biller(Name, Email, position) VALUES('" + Name + "', '" + Email + "', '" + pos + "');";
        if((sqlite3_exec(pdb, sql, NULL, 0, NULL)) != SQLITE_OK) throw(sqlite3_errcode(pdb));

        // Tietokanta kiinni
        sqlite3_close(pdb);
        // Haetaan uusi id
        vect = haeTaulusta("Biller", "id", 1, "", 2, "", "Name", "=", Name, "AND", "Email", "=", Email);
	  }
      else if(update == B_JUSTADD && vect.size() != 0)
		  return RETURN_EXISTS;
      else if(update == B_UPDATE && Props::e().m_yanc_b != R_NOTA)		// Päivitä vanha ja ei valittu aiemmin 'No to All'?
	  {
        if(Props::e().m_yanc_b != R_YESTA)									// Kysytään toiminto, jos ei valittu aiemmin 'Yes to All'
		{
          dlg.m_vect_v.push_back(vect[1]); dlg.m_vect_v.push_back(vect[2]);      //
          dlg.m_vect_u.push_back(Name);      dlg.m_vect_u.push_back(Email);
          dlg.m_mode = UPDATE_LASKUTTAJA;                                        //
          Props::e().m_yanc_b = dlg.DoModal();
		}
        if(Props::e().m_yanc_b == R_YES || Props::e().m_yanc_b == R_YESTA)       //
		{
          if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));
          sql  = "UPDATE Biller SET Name='" + Name + "', " + "Email='" + Email + "' WHERE id='" + vect[0] + "';";
          if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));
          sqlite3_close(pdb);
		}
	  }

	  if(id) *id = vect[0];                         // Annetaan paluuarvona vanha tai uusi, juuri luotu, id jos pyydetty (id != NULL)
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_26"), err, errmsg);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

int DbSqlite::paivitaBiller(ItemData_biller *pid, int num_cols, ...)
{ // Päivitetään annetut kentät Biller-tauluun, kentät annettu sarake/tieto-pareina, num_cols ilmoittaaa parien määrän
    int i, s;
    ItemData id;
    sqlite3 *pdb = NULL;
	CString col, val, sql, name;
    vector <CString> col_data, vect;

    va_list args;                                    // alusta variable arguments
    va_start(args, num_cols);
    while(num_cols-- > 0)                            // Haetaan sarake/tieto-parit vektoriin (päivitettävät tiedot)
	{
      col_data.push_back((col = va_arg(args, LPCSTR)));	// sarake
      col_data.push_back((val = va_arg(args, LPCSTR)));	// tieto
      if(col == BILLER_NAME) name = val;
	}
    va_end(args);                                    // asetetaan variable arguments NULL-arvoon

    escape_vc(&col_data);                            // escapointi

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{
      // Aukaistaan tietokanta
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      if(!(s = col_data.size())) return RETURN_NOACTION;	// sarake/data-parit SET-osaan

      // Tarkistetaan ensin onko sama nimi jo olemassa
	  if(name != "")
	  {
		sql = "SELECT id FROM Biller WHERE Name='" + name + "' AND id<>" + pid->id;
		if((sqlite3_exec(pdb, sql, callback, 0, NULL)) != SQLITE_OK)
			throw(RETURN_EXISTS);                            // Oli olemassa -> ei voi muokata
	  }

      // Voi muokata, muutetaan annetut kentät
      sql = "UPDATE Biller SET ";
      for(i=0; i<s; i+=2)
	  {
        sql += col_data[i];                          // sarake
        sql += "='" + col_data[i + 1] + "'";         // data
        if(i + 2 < s) sql += ", ";                   // jos ei ollut viimeinen col/data-pari
	  }
      sql += " WHERE id=" + pid->id + ";";

      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      sqlite3_close(pdb);
	}
    catch(int err)
	{
      if(err != RETURN_EXISTS)
	  {
        CString errmsg;

        if(pdb) errmsg = dbErrMsg(pdb);
		sql.Format(Props::i().lang("DBSQLITE_27"), err, errmsg);
        MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Units-tauluun kohdistuvat funktiot 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbSqlite::lisaaUnit(CString Unit)
{  // Lisätään suure Units-tauluun
    sqlite3 *pdb = NULL;
    CString dbpath, sql;
    vector <CString> vect;

    if(Unit == _UNSET_) return RETURN_OK;

    escape_c(&Unit);                                 // escapointi

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{ // Lisää jos ei löydy annettua suuretta
      vect = haeTaulusta("Units", "Unit", 1, "", 1, "", "Unit", "=", Unit);
      if(vect.size() == 0)
	  {
        if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));
        sql = "INSERT INTO Units(Unit) VALUES('" + Unit + "');";
        if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));
	  }
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      dbpath.Format(Props::i().lang("DBSQLITE_28"), err, errmsg);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), dbpath, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != 0) sqlite3_close(pdb);
      return err;
	}

    if(pdb != 0) sqlite3_close(pdb);
    return RETURN_OK;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProductGroup-tauluun kohdistuvat funktiot 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DbSqlite::lisaaProductGroup(CString ProductGroupName, CString *id)
{  // Lisätään suure Units-tauluun
    sqlite3 *pdb = NULL;
    CString dbpath, sql, pos;
    vector <CString> vect;

    escape_c(&ProductGroupName);    // escapointi

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; } // Tietokanta määrittämättä -> poistu
    try
	{ // Lisää jos ei löydy annettua suuretta
      if((vect = haeTaulusta("ProductGroup", "Name", 1, "", 1, "", "Name", "=", ProductGroupName)).size() == 0)
	  {
		// Haetaan järjestysnumero
        if((vect = haeTaulusta("ProductGroup", "max(position)", 1, "", 0)).size() == 0)
			pos = "0";
		else
			pos.Format("%d", atoi(vect[0]) + 1);

		// Talletetaan uusi tuoteryhmä
        if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));
        sql = "INSERT INTO ProductGroup(Name, position) VALUES('" + ProductGroupName + "', '" + pos + "');";
        if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));
	  }

      // haetaan uusi/vanha id
	  if(id != NULL)
	  {
        vect = haeTaulusta("ProductGroup", "id", 1, "", 1, "", "Name", "=", ProductGroupName);
        *id = vect[0];
	  }
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      dbpath.Format(Props::i().lang("DBSQLITE_29"), err, errmsg);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), dbpath, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != 0) sqlite3_close(pdb);
      return err;
	}

    if(pdb != 0) sqlite3_close(pdb);
    return RETURN_OK;
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProductGroup-tauluun kohdistuvat funktiot 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CString> DbSqlite::freeQuery(CString sql, int num_cols)
{
	int i;
	CString errmsg;
    const char *pzTail;
    sqlite3 *pdb = NULL;
    sqlite3_stmt *pstmt = NULL;
    const unsigned char *pCol;
    vector <CString> vect;

    if(Props::e().m_db_path == "") { eiDB(1); return vect; } // Tietokanta määrittämättä -> poistu

    try
	{
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      pzTail = sql; pzTail += sql.GetLength();       // Asetaan osoittaamaan SQL-lauseen loppuun
      if(sqlite3_prepare(pdb, sql, sql.GetLength(), &pstmt, &pzTail) != SQLITE_OK) throw(sqlite3_errcode(pdb)); // Valmistellaan tulosjoukko

      while(1)
	  {
        i = sqlite3_step(pstmt);                     // Otetaan rivi tulosjoukosta
        if(i == SQLITE_DONE) break;
        else if(i == SQLITE_ERROR) throw(0);

		for(i=0; i<num_cols; i++)
		{
          pCol = sqlite3_column_text(pstmt, i);      // id, StartMeter, EndMeter, StartDate, StartTime, EndDate, EndTime, StartPlace, EndPlace, Purpose, Private, Worker_id, ReportName, ReportDate, Biller_id
          vect.push_back(pCol);
		}
	  }
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      errmsg.Format(Props::i().lang("DBSQLITE_30"), err, errmsg);
      MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), errmsg, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != 0) sqlite3_close(pdb);
	  vect.clear();
      return vect;
	}

    if(pdb != 0) sqlite3_close(pdb);

	return vect;
}




BOOL DbSqlite::freeSQLStatement(CString sql, BOOL verbose)
{ // Täysin vapaa SQL-lauseen suoritus
    sqlite3 *pdb = NULL;
    vector <CString> col_data, vect;

    if(Props::e().m_db_path == "") { eiDB(1); return NODB; }          // Tietokanta määrittämättä -> poistu

    try
	{
      if(sqlite3_open(_2UTF8(Props::e().m_db_path), &pdb) != SQLITE_OK) throw(sqlite3_errcode(pdb));

      if(sqlite3_exec(pdb, sql, NULL, 0, NULL) != SQLITE_OK) throw(sqlite3_errcode(pdb));
      sqlite3_close(pdb);
	}
    catch(int err)
	{
      CString errmsg;

      if(pdb) errmsg = dbErrMsg(pdb);
      sql.Format(Props::i().lang("DBSQLITE_31"), err, errmsg);
      if(verbose) MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), sql, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);

      if(pdb != NULL) sqlite3_close(pdb);
      return err;
	}

    return RETURN_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Yhteiset tietokantoihin liittyvät funktiot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DbSqlite::findCBItem(BOOL find, CComboBox *pCB, CString table, CString name, CString id)
{ // asetetaan comboboxiin valittu
	int f;
	CString cs;

	if(find)
	{
		if((f = pCB->FindStringExact(-1, id)) == CB_ERR)
			f = 0;
	}
	else
	{
		if(id == "")
			f = 0;
		else
		{
			if((cs = haeArvoID(table, name, id)) == "")
				f = 0;
			else
			{
				if((f = pCB->FindStringExact(-1, cs)) == CB_ERR)
					f = 0;
			}
		}
	}

	pCB->SetCurSel(f);
}

CString DbSqlite::haeArvoID(CString table, CString name, CString id)
{
	vector <CString> vec;

	vec = haeTaulusta(table, name, 1, "", 1, "", "id", "=", id);
	return (vec.size() == 0 ? "" : vec[0]);
}

CString DbSqlite::fixFloat(CString str, BOOL bForce)
{ // Varmista, että (liuku)luku on matkapuhelinohjelman hyväksymässä muodossa. Muuta vain numeroformaattit, jos ei pakotettu muuttamaan.
	if(StringHelper::isNumeric((LPCSTR)str) || bForce)
	{
	    str.Replace(",", ".");
		str.Format("%.2f", atof(str));
	}

    return str;
}
