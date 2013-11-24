// DbSqlite.h: interface for the dbSqlite class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_DBSQLITE_H__842A7C88_9533_4AEA_BF56_D1123B9F4FA8__INCLUDED_)
#define AFX_DBSQLITE_H__842A7C88_9533_4AEA_BF56_D1123B9F4FA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sqlite3.h"
// sqlite3.lib luonti:
//   1. sqlite3.dll ja sqlite3.def -tiedostojen tulee olla samassa kansiossa
//   2. .lib luodaan Microsoftin LIB.EXE-ohjelmalla, joka sijaitsee ../bin-hakemistossa
//      (esim. C:\Program Files\Microsoft Visual Studio\VC98\Bin)
//   3. Kirjoita komentokehoitteessa LIB /DEF:sqlite3.def /MACHINE:IX86, tämä luo
//      .lib ja .exp tiedostot.
//   4. Kopio .lib ja .dll jonnekin mistä Visual Studio löytää ne
#include "defines.h"
#include <vector>
#include "string"
using namespace std;

class DbSqlite  
{
public:
	DbSqlite();
	virtual ~DbSqlite();

public:
    int check();                                     // Tarkistetaan tietokannan tila
    int luoTaulut(CString *db_path, BOOL oletukset); // luodaan tietokanta
    CString _2UTF8(CString);                         // sqlite käyttää UTF8-merkistöä -> muunna
//    CString _2MBCS(CString);                       // windowsissa käytä MBCS/Unicode-merkistöä -> muunna
    CString formatDateTime(CString, int);            // Tiedostosta saadun ajan erottaminen päiväykseen ja kellonaikaan
    vector<int > haePaivaykset(CString, CString);    // Hakee annetusta taulusta päiväykset
    static int callback(void*, int, char**, char**); //
    CString DbSqlite::dbErrMsg(sqlite3 *pdb);
    void eiDB(BOOL verbose);
    int vacuum(CString dbpath);
    void escape_vc(vector <CString> *pvect);
    void escape_c(CString *pcs);
    vector <CString> etsi(CString table, CString ret_col, int num_cols, CString find_col, CString find_data, CString order);

    vector<CString> haeTaulusta(CString table, CString cols, int num_cols, CString order, int num_ehto, ...);

    int poistaYleinen(CString table, CString column, CString value, BOOL verbose, CString dbpath);
    int paivitaYleinen(CString table, CString column, CString vanha, CString uusi, BOOL verbose);
    int paivitaYleinen_id(CString table, CString col1, CString data1, CString col2, CString data2, CString id, BOOL exists);
    int jarjestaPosition(CString table, CString col, CString data, CString field, BOOL verbose);
    int jarjestaPosition_fast(CString table, CString pos_field, CString position, BOOL verbose, CString col, CString data);

			                               // WorkUnit-taulu
    int lisaaWorkUnit(vector<CString> *pvect, CString WorkerName, CString ReportName, CString ReportDate, CString BillerName, CString Unit, CString Uprize, CString Tprize);
    int isWorkUnit(CString check, CString *WorkPlaceName, CString *WorkTypeName, CString *WorkerName, CString Region, CString ProductNumber, CString Unit, CString *BillerName, CString Type, CString PurchasePrice, CString SellPrice, CString Alv, CString *ProductGroup, CString pos_field/*, CString sqlu*/);
    int lisaaSalesUnit(vector<CString>*, CString, CString, CString, CString);
    vector<CString > suodataWorkUnit(vector <CString>, vector <CString>, vector <CString>, CString, CString, int charged, CString type, CString order);
    int paivitaWorkUnit(ItemData *pid, int cols, ...);
                                           // TravelUnit-taulu
    int lisaaTravelUnit(vector<CString>*, CString, CString, CString, CString);
    int paivitaTravelUnit(ItemData_travel *pid, int cols, ...);
	vector<CString> suodataTravelUnit(vector <CString> tyontekijat, CString startdate, CString enddate, CString order);
                                           // WorkPlace-taulu
    int lisaaWorkPlace(CString Name, CString Region_id, CString CustomerNumber, CString Address, CString Note, CString Shortnote, CString Info, CString Biller_id, CString *id, int update);
	int paivitaWorkPlace(ItemData_workplace *pid, int num_cols, ...);
                                           // Region-taulu
    int lisaaRegion(CString Name, CString *id);
                                           // WorkType-taulu
    int lisaaWorkType(CString Name, CString ProductNumber, CString Type, CString Unit, CString PurchasePrice, CString SellPrice, CString Alv, CString ProductGroup_id, CString pos_field, CString *id, int update);
	int paivitaWorkType(ItemData_type *pid, int num_cols, ...);
                                           // Worker-taulu
    int lisaaWorker(CString Name, CString *id);
                                           // Biller-taulu
    int lisaaBiller(CString Name, CString Email, CString *id, int update);
	int paivitaBiller(ItemData_biller *pid, int num_cols, ...);
                                           // Units-taulu
    int lisaaUnit(CString);
	                                       // ProductGroup
	int lisaaProductGroup(CString name, CString *id);
                                           // Vapaa haku ja lauseen suorittaminen
	vector<CString> freeQuery(CString sql, int num_cols);
    int freeSQLStatement(CString sql, BOOL verbose);
											// Yhteiset tietokantoihin liittyvät funktiot
	void findCBItem(BOOL find, CComboBox *pCB, CString table, CString name, CString id);
	CString haeArvoID(CString table, CString name, CString id);
	CString static fixFloat(CString str, BOOL bForce);
};

#endif // !defined(AFX_DBSQLITE_H__842A7C88_9533_4AEA_BF56_D1123B9F4FA8__INCLUDED_)
