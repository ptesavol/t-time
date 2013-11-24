/////////////////////////////////////////////////////////////////
//  BdeDatabase.h -- Interface for the CBdeDatabase class
// 	This class provides access to the Borland Database Engine
//  For this to work, the BDE directory must be in the computers PATH statement
//	Link with Idapi32m.lib, 

#ifndef __BDEDATABASE_H__
#define __BDEDATABASE_H__

//#include "Ms-idapi.h" // header file for BDE API calls

// Actually, we are supposed to include Ms-idapi.h, but all it has is
// the following three lines anyway.  This allows me to keep idapi.h in the project directory  
#define	__FLAT__
#define __WIN32__
#include "idapi.h"

#define TABLETYPE_PARADOX 0
#define TABLETYPE_DBASE 1
#define TABLETYPE_TEXT 2

#define EDITMODE_NONE 0
#define EDITMODE_APPEND 1
#define EDITMODE_INSERT 2
#define EDITMODE_EDITINPLACE 3

class CBdeDatabase
{
// Construction
public:
	CBdeDatabase();
	~CBdeDatabase();

// Attributes
public:


protected:
	hDBIDb m_hDb; // Handle to the Database
	hDBICur m_hCursor; // Handle to the cursor
			
  CHAR m_szTableName[DBIMAXNAMELEN];
	CHAR m_szDatabaseName[255];
	CHAR m_szPrivateDir[255];
	pBYTE m_pEditRecordBuffer;
	UINT m_nEditMode;
	int m_nTableType;


// Operations
public:
	// functions to open and close databases
	BOOL OpenDatabase(LPCTSTR szPath, LPCTSTR szTableName, int nTableType = TABLETYPE_PARADOX,
		BOOL bReadOnly = FALSE, BOOL bExclusive = FALSE, LPCTSTR szPrivateDir = NULL);
	BOOL OpenDatabase(LPCTSTR szFullPath, 
		BOOL bReadOnly = FALSE, BOOL bExclusive = FALSE, LPCTSTR szPrivateDir = NULL);
	BOOL CloseDatabase();

	// Table navigation
	void MoveFirst();
	void MoveNext();
	void MovePrior();
	void MoveLast();
	LONG GetRecordCount();
	BOOL IsBOF();
	BOOL IsEOF();

	// Functions to get field information
	int GetFieldCount();
	CString GetFieldName(int nFieldNumber);
	int FieldNumberFromName(LPCTSTR szFieldName);
	int GetFieldSize(int nFieldNumber);
	int GetFieldType(int nFieldNumber);
	int GetBlobType(int nFieldNumber);
	
	// functions to get field values
	CString GetFieldAsString(UINT16 nFieldNumber, BOOL* pbIsBlank = NULL);
	LONG GetFieldAsInteger(UINT16 nFieldNumber, BOOL* pbBlank = NULL);
	double GetFieldAsFloat(UINT16 nFieldNumber, BOOL* pbIsBlank = NULL);
	COleDateTime GetFieldAsDate(UINT16 nFieldNumber, BOOL* pbBlank);
	BOOL GetFieldAsBoolean(UINT16 nFieldNumber, BOOL* pbBlank = NULL);

	// functions to set field values
	BOOL SetFieldAsString(INT16 nFieldNumber, LPCTSTR szValue, BOOL bBlank = FALSE);
	BOOL SetFieldAsInteger(INT16 nFieldNumber, int nValue, BOOL bBlank = FALSE);
	BOOL SetFieldAsDate(INT16 nFieldNumber, COleDateTime dtValue, BOOL bBlank = FALSE);
	BOOL SetFieldAsFloat(INT16 nFieldNumber, double fValue, BOOL bBlank = FALSE);
	BOOL SetFieldAsBoolean(INT16 nFieldNumber, int nValue, BOOL bBlank = FALSE);


	// functions for editing and posting operations
	BOOL Edit();
	BOOL Insert(); // insert and append really do the same thing
	BOOL Append();
	BOOL Post();
	BOOL Cancel();
	BOOL DeleteRecord();
		

protected:
	// Error checking routines
	BOOL CheckInitialization(LPCTSTR szOperation = NULL);
	BOOL CheckValidCursor(LPCTSTR szOperation = NULL);
	BOOL CheckEditMode(LPCTSTR szOperation = NULL);
	BOOL CheckNotEditMode(LPCTSTR szOperation = NULL);

	// Conversion routines
	CString FormatDate(INT32 Date);
	CString FormatTime(TIME Time);
	CString FormatTimeStamp (TIMESTAMP TimeStamp);
	COleDateTime TimeStampToOleDateTime(TIMESTAMP TimeStamp);
	COleDateTime DateToOleDateTime(INT32 Date);
	COleDateTime TimeToOleDateTime(TIME time);
	DBIResult OleDateTimeToTimeStamp(COleDateTime dt, pTIMESTAMP pTimeStamp);
	INT32 OleDateTimeToDate(COleDateTime dt);
	TIME OleDateTimeToTime(COleDateTime dt);


	BOOL OpenDatabaseHelper(int nTableType,
		DBIOpenMode eOpenMode, DBIShareMode eShareMode, LPCTSTR szPrivateDir);
	BOOL PrepareRecordEdit(int nEditMode);



// Inlines
public:
	inline BOOL IsActive() {
		return (m_hDb != NULL); }
	inline BOOL GetEditMode() {
		return (m_nEditMode != 0); }


protected:



// Statics
public:
	static DBIResult Check(DBIResult ErrorValue, LPCTSTR szMessage = NULL);
	static BOOL Initialize();
	static void Uninitialize();

	// Functions for enabling buttons.  These tell you whether or not to enable
	// the specified button based on the status of the database connection
	static BOOL EnableFirst(CBdeDatabase* pBdeDb);
	static BOOL EnableNext(CBdeDatabase* pBdeDb);
	static BOOL EnablePrior(CBdeDatabase* pBdeDb);
	static BOOL EnableLast(CBdeDatabase* pBdeDb);
	static BOOL EnableInsert(CBdeDatabase* pBdeDb);
	static BOOL EnableEdit(CBdeDatabase* pBdeDb);
	static BOOL EnablePost(CBdeDatabase* pBdeDb);
	static BOOL EnableCancel(CBdeDatabase* pBdeDb);
	static BOOL EnableAppend(CBdeDatabase* pBdeDb);
	static BOOL EnableDelete(CBdeDatabase* pBdeDb);
	static BOOL EnableOpen(CBdeDatabase* pBdeDb);
	static BOOL EnableClose(CBdeDatabase* pBdeDb);


protected:
	static BOOL m_bInitialized;




}; // end of class definition



#endif  // __BDEDATABASE_H__