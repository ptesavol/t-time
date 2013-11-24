// Yleisiä määrittelyjä ja struktuureja
#define OK                                 0
#define ERR_OUTOFMEMORY                    1
#define ERR_READ                           2

#define WORKUNIT_ID                        "id"
#define WORKUNIT_WORKER_ID                 "Worker_id"
#define WORKUNIT_WORKPLACE_ID              "WorkPlace_id"
#define WORKUNIT_WORKTYPE_ID               "WorkType_id"
#define WORKUNIT_STARTDATE                 "StartDate"
#define WORKUNIT_STARTTIME                 "StartTime"
#define WORKUNIT_ENDDATE                   "EndDate"
#define WORKUNIT_ENDTIME                   "EndTime"
#define WORKUNIT_UNIT                      "Unit"
#define WORKUNIT_UNITVALUE                 "UnitValue"
#define WORKUNIT_CHARGED                   "Charged"
#define WORKUNIT_UNITPRICE                 "UnitPrice"
#define WORKUNIT_TOTALPRICE                "TotalPrice"
#define WORKUNIT_ALV                       "Alv"
#define WORKUNIT_REPORTNAME                "ReportName"
#define WORKUNIT_REPORTDATE                "ReportDate"
#define WORKUNIT_BILLER_ID                 "Biller_id"
#define WORKUNIT_TYPE                      "Type"
#define WORKUNIT_COLS                      18                        // Sarakkeiden määrä

#define TRAVELUNIT_ID                      "id"
#define TRAVELUNIT_STARTMETER              "StartMeter"
#define TRAVELUNIT_ENDMETER                "EndMeter"
#define TRAVELUNIT_STARTDATE               "StartDate"
#define TRAVELUNIT_STARTTIME               "StartTime"
#define TRAVELUNIT_ENDDATE                 "EndDate"
#define TRAVELUNIT_ENDTIME                 "EndTime"
#define TRAVELUNIT_STARTPLACE              "StartPlace"
#define TRAVELUNIT_ENDPLACE                "EndPlace"
#define TRAVELUNIT_PURPOSE                 "Purpose"
#define TRAVELUNIT_PRIVATE                 "Private"
#define TRAVELUNIT_WORKER_ID               "Worker_id"
#define TRAVELUNIT_REPORTNAME              "ReportName"
#define TRAVELUNIT_REPORTDATE              "ReportDate"
#define TRAVELUNIT_BILLER_ID               "Biller_id"
#define TRAVELUNIT_COLS                    15

#define WORKPLACE_ID                       "id"
#define WORKPLACE_NAME                     "Name"
#define WORKPLACE_CUSTOMERNUMBER           "CustomerNumber"
#define WORKPLACE_REGION_ID                "Region_id"
#define WORKPLACE_ADDRESS                  "Address"
#define WORKPLACE_NOTE                     "Note"
#define WORKPLACE_SHORTNOTE                "Shortnote"
#define WORKPLACE_INFO                     "Info"
#define WORKPLACE_BILLER_ID                "Biller_id"
#define WORKPLACE_POSITION                 "position"
#define WORKPLACE_COLS                     10

#define REGION_ID                          "id"
#define REGION_NAME                        "Name"
#define REGION_POSITION                    "position"
#define REGION_COLS                        3

#define PRODUCTGROUP_ID                    "id"
#define PRODUCTGROUP_NAME                  "Name"
#define PRODUCTGROUP_POSITION              "position"
#define PRODUCTGROUP_COLS                  3

#define WORKTYPE_ID                        "id"
#define WORKTYPE_NAME                      "Name"
#define WORKTYPE_PRODUCTNUMBER             "ProductNumber"
#define WORKTYPE_TYPE                      "Type"          // [WORK, PRODUCT]
#define WORKTYPE_UNIT                      "Unit"
#define WORKTYPE_PURCHASEPRICE             "PurchasePrice" // Ostohinta
#define WORKTYPE_SELLPRICE                 "SellPrice"     // myyntihinta
#define WORKTYPE_ALV                       "Alv"           //Alv %
#define WORKTYPE_PRODUCTGROUP_ID           "ProductGroup_id"
#define WORKTYPE_POSITION_WORK             "position_work"
#define WORKTYPE_POSITION_PRODUCT          "position_product"
#define WORKTYPE_COLS                      11

#define BILLER_ID                          "id"
#define BILLER_NAME                        "Name"
#define BILLER_EMAIL                       "Email"
#define BILLER_POSITION                    "position"
#define BILLER_COLS                        4

#define WORKUNIT                           "TYPE_WORKUNIT"           // Työtyypit
#define WORKSESSION                        "TYPE_WORKSESSION"
#define TRAVELUNIT                         "TYPE_TRAVEL"
#define SALESUNIT                          "TYPE_SALESUNIT"
#define ID_WORKUNIT                        "0"                       // > kokonaisluku id:t
#define ID_WORKSESSION                     "0"
#define ID_SALESUNIT                       "1"
#define ID_TRAVELUNIT                      "2"
#define TM_BOTH                            "TM"
#define MT_BOTH                            "MT"

#define AUTOMATIC                          "Automaattinen"           // Asiakasryhmän oletusnimi
#define ALV_TYOAIKA                        "0"                       // Oletus alv-% tyäajalle
#define _UNIT_MIN_                         "min"                     // työajan oletussuure minuutteina/tunteina
#define _UNIT_HOUR_                        "h"
#define _UNSET_                            "###"                     // oletus tunniste
#define C_FALSE                            "FALSE"                   // merkkijonot totuusarvoille
#define C_TRUE                             "TRUE"
#define C_ALL                              "ALL"
#define C_ONLY                             "ONLY"
#define _DSTNCT_                           " DISTINCT "              // haku ehto
#define TIME_SEP                           ":"                       // ajan/päiväyksen erotinmerkit
#define FILE_TIME_SEP                      "."
#define DATE_SEP                           "."
#define DATETIME_SEP                       " "
#define DATETIME_IB                        ", "
#define NOREPORTNAME                       _UNSET_                   // Ei raportin nimeä - lisätty t-aika ohjelmassa
#define _VE_                               "_VE_"                    // haun erikoistapaus
#define DFLT_BILLER                        "Oletus"
#define DFLT_WORKTYPE                      "Oletus"
#define TTA_TAIKALISTAT                    "t-aika-listat:"
#define TTA_ASIAKKAAT                      "[asiakkaat]"
#define TTA_LASKUTTAJAT                    "[laskuttajat]"
#define TTA_TYOTYYPIT                      "[työtyypit]"
#define TTA_TUOTTEET                       "[tuotteet]"
#define _IDENTIFIER_                       "(t[a]2)"                 // subject-kenttään sähköpostissa ja liitteen nimen osaksi
#define TTA_EXT                            "tta"                     // tta/tti-tiedostojen päätteet
#define DOT_TTA_EXT                        ".tta"
#define TTI_EXT                            "tti"
#define DOT_TTI_EXT                        ".tti"
#define TYOTKOHTEISSA                      "Työt kohteissa"
#define ASIAKKAAT                          "Asiakkaat"
#define TU_DATES_CHECK                     "((%f >= (StartDate + StartTime/1440.0) AND %f <= (EndDate + EndTime/1440.0)) OR (%f >= (StartDate + StartTime/1440.0) AND %f <= (EndDate + EndTime/1440.0)) OR (%f < (StartDate + StartTime/1440.0) AND %f > (EndDate + EndTime/1440.0)))"
#define WP_NOUPDATE						   0
#define WP_UPDATE						   1
#define WP_JUSTADD						   2
#define WT_NOUPDATE						   0
#define WT_UPDATE						   1
#define WT_JUSTADD						   2
#define B_NOUPDATE						   0							
#define B_UPDATE						   1
#define B_JUSTADD						   2

#define FIELD_8                            8
#define FIELD_16		                   16
#define FIELD_32                           32

#define SHOW_RAPORTIT                      0
#define SHOW_LISTAT                        1
#define SHOW_TYOMATKAT                     2

#define OPTIONS_FILENAME                   "t-aika.options"          // Asetustiedoston tiedostonimi ja avaimet
#define OPTIONS_DB_PATH                    "db_path"                 // Käytössä olevan tietokannan polku - oletuksena ohjelman polku\DEFAULT_DB_NAME
#define OPTIONS_DB_NAME                    "db_name"
#define OPTIONS_AUTOPARSE                  "auto_parse"
#define OPTIONS_LASKUTUSOHJELMA            "laskohj"                 // LAS_NONE, LAS_MAATALOUS, LAS_PASSELI
#define OPTIONS_LASKUTUSOHJELMA_POLKU      "laskohj_polku"
#define OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU "laskohj_kokopolku"
#define OPTIONS_LASKUTUSOHJELMA_YRITYS     "laskohjyritys"
#define OPTIONS_KAYNTIKERTAVELOITUS        "kayntikerta"             // C_FALSE, C_TRUE
#define OPTIONS_HINNAT                     "hinnat"                  // HINNAT_LASKOHJ, HINNAT_MATKAPUH
#define OPTIONS_LASKUTUSTILA               "lasktila"                // LTILA_KAIKKI, LTILA_LASKUTETUT, LTILA_LASKUTTAMATTOMAT
#define OPTIONS_YHDISTATAPAHTUMAT          "yhdistatapahtumat"       // C_FALSE, C_TRUE
#define OPTIONS_LASKUNMAKSUAIKA            "maksuaika"
#define OPTIONS_OPENPATH                   "openpath"                // käyttäjän suosimat hakemistot tiedosto-operaatioille
#define OPTIONS_SAVEPATH                   "savepath"
#define OPTIONS_AJAT                       "ajat"                    // minutes, hours, visits
#define OPTIONS_ALKAEN_R                   "alkaen_r"                // DATE_... raportti-näkymä
#define OPTIONS_PAATTYEN_R                 "paattyen_r"
#define OPTIONS_ALKAEN_VIIMEISIN_R         "alkaen_viimeisin_r"      // viimeksi valittu pvm
#define OPTIONS_PAATTYEN_VIIMEISIN_R       "paattyen_viimeisin_r"
#define OPTIONS_ALKAEN_T                   "alkaen_t"                // DATE_... työmatkat-näkymä
#define OPTIONS_PAATTYEN_T                 "paattyen_t"
#define OPTIONS_ALKAEN_VIIMEISIN_T         "alkaen_viimeisin_t"      // viimeksi valittu pvm
#define OPTIONS_PAATTYEN_VIIMEISIN_T       "paattyen_viimeisin_t"
#define OPTIONS_AIKAJARJESTYS_R            "aikaj_r"                 // ASCENT_S, DESCENT_S
#define OPTIONS_AIKAJARJESTYS_T            "aikaj_t"
#define OPTIONS_KMKERROIN                  "kmkerroin"
#define OPTIONS_DB_BACKUP_PATH             "db_backup_path"
#define OPTIONS_EM_RECIPIENTS              "email_recipients"        // Sähköpostin asetukset
#define OPTIONS_EM_FROM                    "email_from"
#define OPTIONS_EM_SMTP_SERVER             "email_smtp_server"
#define OPTIONS_EM_SMTP_PORT               "email_smtp_port"
#define OPTIONS_EM_SMTP_USE_AUTH           "email_smtp_use_auth"     // C_FALSE, C_TRUE
#define OPTIONS_EM_SMTP_RMBR_UN            "email_smtp_rmbr_un"      // C_FALSE, C_TRUE
#define OPTIONS_EM_SMTP_USERNAME           "email_smtp_username"
#define OPTIONS_PRNT_ASNIMI                "prnt_asnimi"             // PRNT_ASNIMINRO, PRNT_ASNIMI
#define OPTIONS_PRNT_ASALOITUSPVM          "prnt_asaloituspvm"       // PRNT_PVM_AIKA, PRNT_PVM, PRNT_EI
#define OPTIONS_PRNT_ASLOPETUSPVM          "prnt_aslopetuspvm"       // PRNT_PVM_AIKA, PRNT_PVM, PRNT_EI
#define OPTIONS_PRNT_ASTYOAIKA             "prnt_astyoajat"          // PRNT_TYOAIKA_MIN, PRNT_TYOAIKA_H, PRNT_EI
#define OPTIONS_PRNT_ASTYOTYYPIT           "prnt_astyotyypit"        // PRNT_TYOTYYPIT, PRNT_EI
#define OPTIONS_PRNT_TTALOITUSPVM          "prnt_ttaloituspvm"       //  PRNT_PVM_AIKA, PRNT_PVM, PRNT_EI
#define OPTIONS_PRNT_TTLOPETUSPVM          "prnt_ttlopetuspvm"       //  PRNT_PVM_AIKA, PRNT_PVM, PRNT_EI
#define OPTIONS_PRNT_TTTYOAIKA             "prnt_tttyoajat"          //  PRNT_TYOAIKA_MIN, PRNT_TYOAIKA_H, PRNT_EI
#define OPTIONS_PRNT_TTTYOTYYPIT           "prnt_tttyotyypit"        //  PRNT_TYOTYYPIT, PRNT_EI
#define OPTIONS_PRNT_TMPAIVAYKSET          "prnt_tmpaivaykset"       //   PRNT_PVM_AIKA_MOLEMMAT, PRNT_PVM_MOLEMMAT, PRNT_PVM_AIKA_ALOITUS, PRNT_PVM_ALOITUS, PRNT_PVM_AIKA_LOPETUS, PRNT_PVM_LOPETUS, PRNT_EI_PVM_TM
#define OPTIONS_PRNT_TMMATKA               "prnt_tmmatka"            //   PRNT_MATKAT_TARKOITUS, PRNT_MATKAT, PRNT_EI
#define OPTIONS_PRNT_TMLUKEMAT             "prnt_tmlukemat"          //   PRNT_LUKEMAT, PRNT_EI
#define OPTIONS_PRNT_TMYKSAJOA             "prnt_tmyksajoa"          //   PRNT_YKSAJOA, PRNT_EI
#define OPTIONS_PRNT_TMTYOAJOA             "prnt_tmtyoajoa"          //   PRNT_TYOAJOA, PRNT_EI
#define OPTIONS_PRNT_SIVUTUS               "prnt_sivutus"            // C_FALSE, C_TRUE
#define OPTIONS_PRNT_YLATUNNISTE_TEXT      "prnt_ylatunniste_text"   //
#define OPTIONS_PRNT_ALATUNNISTE_TEXT      "prnt_alatunniste_text"   //
#define OPTIONS_PRNT_YLATUNNISTE           "prnt_ylatunniste"        // C_FALSE, C_TRUE
#define OPTIONS_PRNT_ALATUNNISTE           "prnt_alatunniste"        // C_FALSE, C_TRUE
#define OPTIONS_PRNT_YLAPAIVAYS            "prnt_ylapaivays"         // C_FALSE, C_TRUE
#define OPTIONS_PRNT_FONTINKOKO            "prnt_fontinkoko"         // FONTSIZE_8 - FONTSIZE_14
#define OPTIONS_PRNT_FONTINNIMI            "prnt_fontinnimi"         //
#define OPTIONS_PRNT_YHTEENVETO            "prnt_yhteenveto"         // C_FALSE, C_TRUE, C_ONLY
#define OPTIONS_PRNT_KMKORVAUS             "prnt_kmkorvaus"          // C_FALSE, C_TRUE
#define OPTIONS_PRNT_YHDISTATAPAHTUMAT     "prnt_yhdistatapahtumat"  // C_FALSE, C_TRUE
#define OPTIONS_LSTHEADER_RATA             "listheader_rata"         // puolipiklkulla eroteltuna listan otsikon koot
#define OPTIONS_LSTHEADER_RAMY             "listheader_ramy"
#define OPTIONS_LSTHEADER_LIAR             "listheader_liar"
#define OPTIONS_LSTHEADER_LIAS             "listheader_lias"
#define OPTIONS_LSTHEADER_LILA             "listheader_lila"
#define OPTIONS_LSTHEADER_LITT             "listheader_litt"
#define OPTIONS_LSTHEADER_LITR             "listheader_litr"
#define OPTIONS_LSTHEADER_LITU             "listheader_litu"
#define OPTIONS_LSTHEADER_TYTY             "listheader_tyty"

#define DEFAULT_DB_NAME                    "Work.db"

#define LAS_NONE                           "none"
#define LAS_MAATALOUSNEUVOS                "maatalous"
#define LAS_PASSELI                        "passeli"

#define HINNAT_LASKOHJ                     "laskohj"
#define HINNAT_MATKAPUH                    "matkapuh"

#define LTILA_KAIKKI                       "kaikki"
#define LTILA_LASKUTETUT                   "laskutetut"
#define LTILA_LASKUTTAMATTOMAT             "laskuttamattomat"

#define DATE_VIIMEKSI_ASETETTU             "Viimeksi asetettu"
#define DATE_VANHIN_TYO                    "Vanhin tapahtuma"
#define DATE_UUSIN_TYO                     "Uusin tapahtuma"
#define DATE_NYKYINEN_PVM                  "Nykyinen pvm"
#define DATE_NYKYINEN_M1                   "Nykyinen pvm -1 vuosi"
#define DATE_NYKYINEN_M2                   "Nykyinen pvm -2 vuotta"
#define DATE_NYKYINEN_M3                   "Nykyinen pvm -3 vuotta"

#define COMO_COPY                          "copy"
#define COMO_MOVE                          "move"
#define COMO_NOCOMO                        "nocopymove"

#define PRNT_ASNIMINRO                     "0"
#define PRNT_ASNIMI                        "1"
#define PRNT_PVM_AIKA                      "0"
#define PRNT_PVM                           "1"
#define PRNT_EI_PVM                        "2"
#define PRNT_TYOAIKA_MIN                   "0"
#define PRNT_TYOAIKA_H                     "1"
#define PRNT_TYOAIKA_KERTOINA              "2"
#define PRNT_EI_TYOAIKA                    "3"
#define PRNT_TYOTYYPIT                     "0"
#define PRNT_MATKAT_TARKOITUS              "0"
#define PRNT_MATKAT                        "1"
#define PRNT_EI_MATKAT                     "2"
#define PRNT_LUKEMAT                       "0"
#define PRNT_YKSAJOA                       "0"
#define PRNT_TYOAJOA                       "0"
#define PRNT_EI                            "1"
#define PRNT_PVM_AIKA_MOLEMMAT             "0"
#define PRNT_PVM_MOLEMMAT                  "1"
#define PRNT_PVM_AIKA_ALOITUS              "2"
#define PRNT_PVM_ALOITUS                   "3"
#define PRNT_PVM_AIKA_LOPETUS              "4"
#define PRNT_PVM_LOPETUS                   "5"
#define PRNT_EI_PVM_TM                     "6"

#define FONTSIZE_8                         "8"
#define FONTSIZE_10                        "10"
#define FONTSIZE_12                        "12"
#define FONTSIZE_14                        "14"

#define DEFAULT_DB_NAME                    "Work.db"

#define WORK                               "WORK"
#define PRODUCT                            "PRODUCT"
#define PRODUCTGROUP                       "PRODUCTGROUP"
#define BILLER                             "BILLER"

#define PRODUCTLIST_ASSUMED                "Oletus"

#define UPDATE_START                       0
#define UPDATE_END                         1

#define FORMAT_DATE                        0
#define FORMAT_TIME                        1

#define MOVE_FILE                          0
#define COPY_FILE                          1
#define NOCM_FILE                          2

#define ASCENT                             0
#define DESCENT                            1
#define ASCENT_S                           "ASC"
#define DESCENT_S                          "DESC"

#define DBSPACE                            "   "

#define UNCHARGED                          0
#define CHARGED                            1
#define ALLREPORTS                         2

#define MODE_SAVE                          0
#define MODE_ATTACH                        1

#define MODE_LISAA                         0
#define MODE_POISTA                        1

#define MODE_VALITUT                       1
#define MODE_KAIKKINAYTETYT                2
#define MODE_ASIAKAANTIEDOT                4
#define MODE_ASIAKAANTIEDOT_TT             8
#define MODE_TYONTEKIJOIDENTIEDOT          16
#define MODE_TYONTEKIJANTIEDOT             32

#define TIME_MINUTES                       0
#define TIME_HOURS                         1
#define TIME_CALLS                         2

#define PARSE_SAAPUNEET                    0
#define PARSE_FILES                        1
#define PARSE_ADD_FILE                     2

#define SEPARATOR                          " - "         // sarakkeiden välille CListCtrl yms. kontrolleissa

#define O_TYOAJAT                          0             // ListctrlRaportit
#define O_MYYNNIT                          1
#define O_ASIAKASRYHMA                     2
#define O_ASIAKAS                          3
#define O_LASKUTTAJA                       4
#define O_TYOTYYPPI                        5
#define O_TUOTERYHMA                       6
#define O_TUOTE                            7
#define O_TRAVEL                           8

#define UPDATE_ASIAKAS                     0
#define UPDATE_LASKUTTAJA                  1
#define UPDATE_TYOTYYPPI                   2
#define UPDATE_TUOTE                       3

#define MODE_ASIAKKAAT                     0
#define MODE_TYOAJAT                       1
#define MODE_TYOMATKAT                     2

#define MODE_EMAIL_RAPORTIT                0
#define MODE_EMAIL_LISTAT                  1

#define PAGE_LEFT                          4
#define PAGE_RIGHT                         4
#define PAGE_TOP                           4
#define PAGE_BOTTOM                        4
#define PAGE_GAD_SPACE                     4
#define PAGE_GAD_SPACE_L                   6
#define PAGE_GAD_SPACE_T                   12

#define SYNC_ASIAKASRYHMAT                 1
#define SYNC_ASIAKKAAT                     2
#define SYNC_LASKUTTAJAT                   4
#define SYNC_TYOTYYPIT                     8
#define SYNC_TUOTERYHMAT                   16
#define SYNC_TUOTTEET                      32
#define SYNC_TYONTEKIJAT                   64
#define SYNC_FROM_RAPORTIT                 128
#define SYNC_FROM_LISTAT                   256
#define SYNC_FROM_TYOMATKAT                512
#define SYNC_ALL                           (SYNC_ASIAKASRYHMAT|SYNC_ASIAKKAAT|SYNC_LASKUTTAJAT|SYNC_TYOTYYPIT|SYNC_TUOTERYHMAT|SYNC_TUOTTEET|SYNC_TYONTEKIJAT)

#define KEY_CTRLF                          0
#define KEY_F3                             1

#define IMPORT_ASIAKKAAT                   0
#define IMPORT_TYOTYYPIT                   1
#define IMPORT_TUOTTEET                    2

#define WM_USER_NEW_REPORT                 (WM_USER + 1001)          // taika_savereport.exe viestittää uudesta raportista => täytyy olla + 1001!!!
//#define MSG_THREADEXIT                     (WM_USER + 1002)
#define WM_USER_SELECTALL                  (WM_USER + 1003)
#define WM_USER_OPEN                       (WM_USER + 1004)
#define WM_USER_SAVE                       (WM_USER + 1005)
#define WM_USER_FIND                       (WM_USER + 1006)
#define WM_USER_FINDF3                     (WM_USER + 1007)
#define WM_USER_DELETE                     (WM_USER + 1008)
#define WM_USER_NEW                        (WM_USER + 1009)
#define WM_USER_IMPORT                     (WM_USER + 1010)
#define WM_USER_TABBEDOUT                  (WM_USER + 1011)

#define PARAM_TTI                          0
#define PARAM_TTA                          1

#define INPLACEEDIT                        909808303

#define NODB								-3
#define GEN_RESET							-2
#define GEN_ERROR							-1            // Paluuarvoja 
#define RETURN_NOACTION						SQLITE_OK       // sqlite v3.5.4 kanssa yhtenevät arvot
#define RETURN_OK							SQLITE_DONE + 1 // sqlite v3.5.4 suurin paluu arvo = SQLITE_DONE. Eli vaikka SQLITE_DONE:ia käytretty se ei tarkoita, että olisi tieotkantavirhe kyseessä. SQLITE_DONE on vain base numberina!!!
#define RETURN_EXISTS						SQLITE_DONE + 2
#define RETURN_NONE							SQLITE_DONE + 3
#define ERR_IMALLOC							SQLITE_DONE + 4
#define ERR_SHGET							SQLITE_DONE + 5
#define ERR_ACCOUNT							SQLITE_DONE + 6
#define ERR_WORKTYPE						SQLITE_DONE + 7
#define ERR_CUSTOMERNUMBER					SQLITE_DONE + 8
#define ERR_MEMORYERR1						SQLITE_DONE + 9
#define ERR_SELCUSTOMER						SQLITE_DONE + 10
#define ERR_SELONE							SQLITE_DONE + 11
#define ERR_SELATLEASTONE					SQLITE_DONE + 12
#define ERR_NOWUNITS						SQLITE_DONE + 13
#define ERR_REPE							SQLITE_DONE + 14
#define R_YES								SQLITE_DONE + 15
#define R_YESTA								SQLITE_DONE + 16
#define R_NO								SQLITE_DONE + 17
#define R_NOTA								SQLITE_DONE + 18
#define ERR_ERITTELY_TT_1					SQLITE_DONE + 19
#define ERR_ERITTELY_TT_2					SQLITE_DONE + 20
#define ERR_ERITTELY_TT_3					SQLITE_DONE + 21
#define ERR_ERITTELY_TT_4					SQLITE_DONE + 22
#define ERR_ERITTELY_TT_5					SQLITE_DONE + 23
#define ERR_ERITTELY_TM_1					SQLITE_DONE + 24
#define ERR_ERITTELY_TM_2					SQLITE_DONE + 25
#define ERR_ERITTELY_TM_3					SQLITE_DONE + 26
#define ERR_ERITTELY_TM_4					SQLITE_DONE + 27
#define ERR_ERITTELY_TM_5					SQLITE_DONE + 28
#define ERR_ERITTELY_AS_1					SQLITE_DONE + 29
#define ERR_ERITTELY_AS_2					SQLITE_DONE + 30
#define ERR_ERITTELY_AS_3					SQLITE_DONE + 31
#define ERR_ERITTELY_AS_4					SQLITE_DONE + 32
#define ERR_ERITTELY_AS_5					SQLITE_DONE + 33
#define ERR_IMPORT_AS_0						SQLITE_DONE + 34
#define ERR_IMPORT_AS_1						SQLITE_DONE + 35
#define ERR_IMPORT_AS_2						SQLITE_DONE + 36
#define ERR_IMPORT_AS_3						SQLITE_DONE + 37
#define ERR_IMPORT_TT_0						SQLITE_DONE + 38
#define ERR_IMPORT_TT_3						SQLITE_DONE + 39
#define ERR_IMPORT_TU_0						SQLITE_DONE + 40
#define ERR_IMPORT_TU_2						SQLITE_DONE + 41
#define ERR_IMPORT_TU_3						SQLITE_DONE + 42
#define ERR_INFO_0							SQLITE_DONE + 43
#define ERR_INFO_1							SQLITE_DONE + 44
#define ERR_SMPTP_0							SQLITE_DONE + 45
#define ERR_SMPTP_2							SQLITE_DONE + 46
#define ERR_SMPTP_3							SQLITE_DONE + 47
#define ERR_SMPTP_4							SQLITE_DONE + 48
#define ERR_SMPTP_7							SQLITE_DONE + 49
#define ERR_SMPTP_8							SQLITE_DONE + 50
#define ERR_NEWREPORT_0                     SQLITE_DONE + 51
#define ERR_NEWREPORT_2						SQLITE_DONE + 52
#define ERR_NEWREPORT_3						SQLITE_DONE + 53
#define ERR_NEWREPORT_4						SQLITE_DONE + 54
#define ERR_NEWREPORT_5						SQLITE_DONE + 55
#define ERR_NEWREPORT_6						SQLITE_DONE + 56
#define ERR_NEWREPORT_7						SQLITE_DONE + 57
#define ERR_NEWREPORT_8						SQLITE_DONE + 58
#define ERR_NEWREPORT_9						SQLITE_DONE + 59
#define ERR_NEWREPORT_10					SQLITE_DONE + 60
#define ERR_NEWREPORT_11					SQLITE_DONE + 61
#define ERR_NEWREPORT_12					SQLITE_DONE + 62
#define ERR_NEWREPORT_13					SQLITE_DONE + 63
#define ERR_NEWREPORT_14					SQLITE_DONE + 64
#define ERR_NEWREPORT_15					SQLITE_DONE + 65
#define ERR_BACKUP_0						SQLITE_DONE + 66
#define ERR_BACKUP_1						SQLITE_DONE + 67
#define ERR_REPORTS_0						SQLITE_DONE + 68
#define ERR_REPORTS_1						SQLITE_DONE + 69
#define ERR_REPORTS_2						SQLITE_DONE + 70
#define ERR_REPORTS_4						SQLITE_DONE + 71
#define ERR_TRAVEL_0						SQLITE_DONE + 72
#define ERR_NEWTRAVEL_0						SQLITE_DONE + 73
#define ERR_NEWTRAVEL_1						SQLITE_DONE + 74
#define ERR_NEWTRAVEL_2						SQLITE_DONE + 75
#define ERR_NEWTRAVEL_3						SQLITE_DONE + 76
#define ERR_NEWTRAVEL_4						SQLITE_DONE + 77
#define ERR_NEWTRAVEL_5						SQLITE_DONE + 78
#define ERR_NEWTRAVEL_6						SQLITE_DONE + 79
#define ERR_NEWTRAVEL_7						SQLITE_DONE + 80
#define ERR_NEWTRAVEL_8						SQLITE_DONE + 81
#define ERR_NEWTRAVEL_9						SQLITE_DONE + 82
#define ERR_NEWTRAVEL_10					SQLITE_DONE + 83
#define ERR_NEWTRAVEL_11					SQLITE_DONE + 84
#define ERR_NEWWORKPLACE_0					SQLITE_DONE + 85
#define ERR_NEWWORKPLACE_1					SQLITE_DONE + 86
#define ERR_NEWWORKPLACE_2					SQLITE_DONE + 87
#define ERR_NEWWORKPLACE_3					SQLITE_DONE + 88
#define ERR_NEWWORKPLACE_4					SQLITE_DONE + 89
#define ERR_NEWWORKPLACE_5					SQLITE_DONE + 90
#define ERR_NEWWORKPLACE_6					SQLITE_DONE + 91
#define ERR_NEWWORKPLACE_7					SQLITE_DONE + 92
#define ERR_NEWPRODUCT_0					SQLITE_DONE + 93
#define ERR_NEWPRODUCT_1					SQLITE_DONE + 94
#define ERR_NEWPRODUCT_2					SQLITE_DONE + 95
#define ERR_NEWPRODUCT_3					SQLITE_DONE + 96
#define ERR_NEWPRODUCT_4					SQLITE_DONE + 97
#define ERR_NEWPRODUCT_5					SQLITE_DONE + 98
#define ERR_NEWPRODUCT_6					SQLITE_DONE + 99
#define ERR_NEWWORKTYPE_0					SQLITE_DONE + 100
#define ERR_NEWWORKTYPE_1					SQLITE_DONE + 101
#define ERR_NEWWORKTYPE_2					SQLITE_DONE + 102
#define ERR_NEWBILLER_0						SQLITE_DONE + 103
#define ERR_NEWBILLER_1						SQLITE_DONE + 104
#define ERR_NEWBILLER_2						SQLITE_DONE + 105
//

#pragma once

class Item
{
public:
    CString id;
    CString Name;
	CString position;
};

class ItemData : public Item               // Jokaiseen itemiin talletetaan tiedot raportista tietokanta-/tiedosto-operaatioden helpottamiseksi
{ // TYPE_WORKUNIT , TYPE_WORKSESSION, TYPE_SALESUNIT
public:
    CString Worker_id;
    CString WorkPlace_id;
    CString WorkType_id;
    CString StartDate;
    CString StartTime;
    CString EndDate;
    CString EndTime;
    CString Unit;
    CString UnitValue;
    CString Charged;
    CString UnitPrice;
    CString TotalPrice;
    CString Alv;
    CString ReportName;
    CString ReportDate;
    CString Biller_id;
    CString Type;                         // TYPE_WORKUNIT, TYPE_WORKSESSION, SALES_UNIT

    BOOL kasitelty;                       // käytetään seurattaessa onko tietue käsitelty (FALSE=käsittelemätön, TRUE=käsitelty)
    CString oWorkType_id;                 // käytetään laskutuksen yhteydessä merkittäessä tietokantaan työ lakutetuksi (original id). Yhdistettäessä samalla tuotenumerolla olevia töitö/tuotteita alkuperäinen id joudutaan muuttamaan ja tässä säilytetään alkuperäinen tietokantaoperaatioita varten (ks. void DlgLaskutus::teeYhdiste()).
};

struct ItemData_travel : public Item
{
public:
    CString StartMeter;
    CString EndMeter;
    CString StartDate;
    CString StartTime;
    CString EndDate;
    CString EndTime;
    CString StartPlace;
    CString EndPlace;
    CString Purpose;
    CString Private;
    CString Worker_id;
    CString ReportName;
    CString ReportDate;
    CString Biller_id;
};

class ItemData_region : public Item
{
public:
};

class ItemData_workplace : public Item
{
public:
    CString Region_id;
    CString CustomerNumber;
    CString Address;
    CString Note;
    CString Shortnote;
    CString Info;
    CString Biller_id;

    int kasitelty;                         // muokkausoperaatioille
};

class ItemData_biller : public Item
{
public:
    CString Email;
};

class ItemData_type : public Item
{
public:
    CString ProductNumber;
	CString Type;
	CString Unit;
	CString PurchasePrice;
	CString SellPrice;
	CString Alv;
    CString ProductGroup_id;
};

class ItemData_productgroup : public Item
{
public:
};

// 13.8.2010, J.V. Alv-ryhmät suonentiedon ohjelmissa
class Alv
{
public:
	CString N;						// Ai, yksilöivä tunnus
	int AlvPro;						// N, alvikannan prosentti
	CString Nimi;					// A30
	int VoimassaOloAlkuPaiva;		// D (t-aika Paivaysluokan mukainen), koska alvikanta tulee voimaan 
	int VoimassaOloAlkuAika;
	int VoimassaOloLoppuPaiva;		// D (t-aika Paivaysluokan mukainen), alvikannan voimassaolon loppupäivä
	int VoimassaOloLoppuAika;
	int AlvRyhmaID;					// I, mihinkäalviryhmään alvikanta kuuluu

	double total;					// t-aika laskee tähän kokonaisumman eri tuotteilta tietylle alv-prosentille
	int size;						// t-aika tallettaa jokaiseen vektorin alkioon vektorin koon

	int findAlvProIndex(Alv *pAlv, int ai, int sd)
	{
		for(int a=0; a<pAlv[0].size; a++)
		{
			if(ai == pAlv[a].AlvRyhmaID)
			{
				// verokantaa ei asetettu/valittu tuotteelle
				if(pAlv[a].VoimassaOloAlkuPaiva == 0 && pAlv[a].VoimassaOloLoppuPaiva == 0)
					return a;
				// verokannan loppumispäivää ei ole määritetty
				else if(pAlv[a].VoimassaOloAlkuPaiva > 0 && pAlv[a].VoimassaOloLoppuPaiva == 0)
				{
					if(sd >= pAlv[a].VoimassaOloAlkuPaiva)
						return a;
				}
				// verokannan loppumis- ja alkamispäivät on määritetty
				else
				{
					if(sd >= pAlv[a].VoimassaOloAlkuPaiva && sd <= pAlv[a].VoimassaOloLoppuPaiva)
						return a;
				}
			}
		}

		return -1;
	}
};