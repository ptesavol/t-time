/////////////////////////////////////////////////////////////////
//  BdeDatabase.cpp -- Implementation of the CBdeDatabase class
// 	This class provides access to the Borland Database Engine
//  For this to work, the BDE directory must be in the computers PATH statement
//	Link with Idapi32m.lib, 



#include "stdafx.h"
#include "BdeDatabase.h"
#include "BdeException.h"

BOOL CBdeDatabase::m_bInitialized = FALSE;

///////////////////////////////////////////////////////////////////
// CBdeDatabase Construction/Destruction

CBdeDatabase::CBdeDatabase()
{
	m_hDb = NULL;
	m_hCursor = NULL;
  m_szTableName[0] = '\0';
	m_szDatabaseName[0] = '\0';
	m_szPrivateDir[0] = '\0';
	m_pEditRecordBuffer = NULL;
	m_nEditMode = 0;
	m_nTableType = -1;
}


CBdeDatabase::~CBdeDatabase()
{
	// perform any cleanup here
	CloseDatabase();
}





////////////////////////////////////////////////////////////////////
// CBdeDatabase Operations

/*BOOL CBdeDatabase::OpenDatabase(LPCTSTR szAlias, BOOL bReadOnly, BOOL bExclusive)
{


}	*/


// function to open a database given the full path and table name in a single string
// Table type is determined by file extension
BOOL CBdeDatabase::OpenDatabase(LPCTSTR szFullPath, 
	BOOL bReadOnly, BOOL bExclusive, LPCTSTR szPrivateDir)
{
	// split the file name into it's different parts
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char fname[_MAX_FNAME];
  char ext[_MAX_EXT];
  _splitpath(szFullPath, drive, dir, fname, ext );

	// use the file extension to determine the file type
	int nTableType;
	if (_stricmp(ext, ".txt") == 0) nTableType = TABLETYPE_TEXT;
	else if (_stricmp(ext, ".csv") == 0) nTableType = TABLETYPE_TEXT;
	else if (_stricmp(ext, ".dbf") == 0) nTableType = TABLETYPE_DBASE;
	else nTableType = TABLETYPE_PARADOX;

	CString strPath;
	strPath.Format("%s%s", drive, dir);

	return OpenDatabase(strPath, fname, nTableType, bReadOnly, bExclusive, szPrivateDir);
}


// function to open a database given a separate path and table name
BOOL CBdeDatabase::OpenDatabase(LPCTSTR szPath, LPCTSTR szTableName, int nTableType,
	BOOL bReadOnly, BOOL bExclusive, LPCTSTR szPrivateDir)
{
	if (!CheckInitialization()) return FALSE;

	// If database is active, then throw and exception
	if (m_hDb != NULL || m_hCursor != NULL)
	{
		throw new CBdeException(DBIERR_NONE, BDEEXERR_ALREADYOPEN,
			m_szTableName, m_szDatabaseName, "");
		return FALSE;
	}
	

	DBIResult dbiResult;
	CString s;
	DBIOpenMode eOpenMode;
	DBIShareMode eShareMode;

	// copy the string constants to the non-const member values
	strncpy(m_szTableName, szTableName, DBIMAXNAMELEN-1);
	strncpy(m_szDatabaseName, szPath, 254);
	if (szPrivateDir != NULL)
		strncpy(m_szPrivateDir, szPrivateDir, 254);
	else
		strncpy(m_szPrivateDir, "", 254);

	// Set read only and share mode values
	if (bReadOnly) eOpenMode = dbiREADONLY;
	else eOpenMode = dbiREADWRITE;

	if (bExclusive) eShareMode = dbiOPENEXCL;
	else eShareMode = dbiOPENSHARED;



	// Open the database
	dbiResult = DbiOpenDatabase(
    NULL,       	      // Database name - NULL for standard database
    NULL,          	      // Database type - NULL for standard database
    eOpenMode,  	      // Open mode - Read/Write or Read only

    eShareMode, 	      // Share mode - Shared or Exclusive
    NULL,          	      // Password - not needed for the STANDARD database
    NULL,          	      // Number of optional parameters
    NULL,          	      // Field Desc for optional parameters
    NULL,          	      // Values for the optional parameters
    &m_hDb);          	      // Handle to the database

	if (dbiResult != DBIERR_NONE)
	{
		s.Format("Failed to open database %s.", m_szDatabaseName);
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, s);
		return FALSE;
	}

	return OpenDatabaseHelper(nTableType, eOpenMode, eShareMode, szPrivateDir);
}


// helper function to open the database, it actually opens the tables
// after a database has been opened.  It is here to support the different
// variations on opening a database
BOOL CBdeDatabase::OpenDatabaseHelper(int nTableType,
	DBIOpenMode eOpenMode, DBIShareMode eShareMode, LPCTSTR szPrivateDir)
{
	// before entering this function, the database must have been opened
	// but not the table
	ASSERT(m_hDb != NULL);
	ASSERT(m_hCursor == NULL);
		
	// local variables
	DBIResult dbiResult;
	CString s;
  CHAR szTableType[DBIMAXNAMELEN];
	pBYTE pRecBuf = NULL;
	CURProps CurProps; // cursor properties

	// save the table type
	m_nTableType = nTableType;

	// set the table directory
  dbiResult = DbiSetDirectory(
		m_hDb, // Handle to the database which is being modified
    m_szDatabaseName);	 // The new working directory

	if (dbiResult != DBIERR_NONE)
	{
		s.Format("Failed to open database %s.", m_szDatabaseName);
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, s);
		goto l_Failure;
	}

	
	// set the private dir
	if (szPrivateDir != NULL)
	{
		dbiResult = DbiSetPrivateDir(m_szPrivateDir);
		if (dbiResult != DBIERR_NONE)
		{
			s.Format("Failed to set private directory %s.", m_szPrivateDir);
			throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, s);
			goto l_Failure;
		}
	} // end of setting private dir


	// get the table type and open the table
	// Use paradox by default
	if (nTableType == TABLETYPE_TEXT)
		strcpy(szTableType, szASCII);
	else if (nTableType == TABLETYPE_DBASE)
		strcpy(szTableType, szDBASE);
	else strcpy(szTableType, szPARADOX);

	// Open the table
	dbiResult = DbiOpenTable(                                                    // Step 7
    m_hDb, 				// Handle to the standard database
    m_szTableName,     		// Name of the table
    szTableType,     		// Type of the table - only used for local tables
    NULL,          		// Index Name - Optional
    NULL,          		// IndexTagName - Optional. Only used by dBASE
    0,             		// IndexId - 0 = Primary.

    eOpenMode,  		// Open Mode - Read/Write or Read Only
    eShareMode, 		// Shared mode - SHARED or EXCL
    xltFIELD,      		// Translate mode - Almost always xltFIELD
    FALSE, 			// Unidirectional cursor movement.
    NULL,				// Optional Parameters.
    &m_hCursor);         		// Handle to the cursor

	if (dbiResult != DBIERR_NONE)
	{
		s.Format("Failed to open table %s in database %s.", 
			m_szTableName, m_szDatabaseName);
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, s);
		goto l_Failure;
	}

	// get the cursor properties here
  dbiResult = DbiGetCursorProps(
		m_hCursor, // Handle to the cursor
    &CurProps);		// Properties of the cursor (table)

	if (dbiResult != DBIERR_NONE)
	{
		s.Format("Failed to get database cursor properties in table %s.", m_szTableName);
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, s);
		goto l_Failure;
	}

	// allocate the memory for the record buffer
	pRecBuf = (pBYTE) malloc(CurProps.iRecBufSize * sizeof(BYTE)); 
	if (pRecBuf == NULL)
	{
		s.Format("Insufficient memory to open table %s.", m_szTableName);
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, s);
		goto l_Failure;
	}
	free(pRecBuf);
	
	if (CurProps.iFields > 0) MoveFirst();

	return TRUE;


	// goto here for cleanup
	l_Failure:;
	CloseDatabase();
	return FALSE;
} // end of OpenDatabase function





// function to initialize the database
BOOL CBdeDatabase::Initialize()
{
	// make sure not already initialized
	if (m_bInitialized) return TRUE;

	// initialize the BDE
	DBIResult dbiResult = DbiInit(NULL);

	// Check error code
	if (dbiResult == DBIERR_NONE)
	{
		m_bInitialized = TRUE;
		return TRUE;
	}

	Check(dbiResult, "Failed to initialize Borland Database Engine.");
	return FALSE;
}




// function to close the database
BOOL CBdeDatabase::CloseDatabase()
{
	DBIResult dbiResult;
	CString s;

	if (m_hDb == NULL) return TRUE; // database was not open to begin with

	// cancel any pending edits
	Cancel();

	// Close the cursor
  if (m_hCursor != NULL)
	{
		dbiResult = DbiCloseCursor(&m_hCursor);
		if (dbiResult != DBIERR_NONE)
		{
			s.Format("Failed to close table %s", m_szTableName);
			Check(dbiResult, s);
			return FALSE;
		}
	}
	m_hCursor = NULL;

	// close the database	
  dbiResult = DbiCloseDatabase(&m_hDb);
	if (dbiResult != DBIERR_NONE)
	{
		s.Format("Failed to close database %s", m_szDatabaseName);
		Check(dbiResult, s);
		return FALSE;
	}

	m_hDb = NULL;	
	m_szTableName[0] = '\0';
	m_szDatabaseName[0] = '\0';
	m_nTableType = -1;
	return TRUE;
}	 



// uninitialize the database, this should be last BDE call ever
void CBdeDatabase::Uninitialize()
{
	DbiExit();			
	m_bInitialized = FALSE;
}




/////////////////////////////////////////////////////////////////////
//  Functions to GetEnabling flags

BOOL CBdeDatabase::EnableFirst(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == FALSE) return FALSE;
	if (pBdeDb->GetEditMode() == TRUE) return FALSE;
	return TRUE;
}

BOOL CBdeDatabase::EnableNext(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == FALSE) return FALSE;
	if (pBdeDb->GetEditMode() == TRUE) return FALSE;
	return TRUE;
}

BOOL CBdeDatabase::EnablePrior(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == FALSE) return FALSE;
	if (pBdeDb->GetEditMode() == TRUE) return FALSE;
	return TRUE;
}


BOOL CBdeDatabase::EnableLast(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == FALSE) return FALSE;
	if (pBdeDb->GetEditMode() == TRUE) return FALSE;
	return TRUE;
}

BOOL CBdeDatabase::EnableInsert(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == FALSE) return FALSE;
	if (pBdeDb->GetEditMode() == TRUE) return FALSE;
	return TRUE;
}

BOOL CBdeDatabase::EnableEdit(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == FALSE) return FALSE;
	if (pBdeDb->GetEditMode() == TRUE) return FALSE;
	return TRUE;
}

BOOL CBdeDatabase::EnablePost(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == FALSE) return FALSE;
	if (pBdeDb->GetEditMode() == FALSE) return FALSE;
	return TRUE;
}

BOOL CBdeDatabase::EnableCancel(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == FALSE) return FALSE;
	if (pBdeDb->GetEditMode() == FALSE) return FALSE;
	return TRUE;
}

BOOL CBdeDatabase::EnableAppend(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == FALSE) return FALSE;
	if (pBdeDb->GetEditMode() == TRUE) return FALSE;
	return TRUE;
}

BOOL CBdeDatabase::EnableDelete(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == FALSE) return FALSE;
	if (pBdeDb->GetEditMode() == TRUE) return FALSE;
	return TRUE;
}


BOOL CBdeDatabase::EnableOpen(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == TRUE) return FALSE;
	return TRUE;
}

BOOL CBdeDatabase::EnableClose(CBdeDatabase* pBdeDb)
{
	if (pBdeDb == NULL) return FALSE;
	if (CBdeDatabase::m_bInitialized == FALSE) return FALSE;
	if (pBdeDb->IsActive() == FALSE) return FALSE;
	return TRUE;
}

	  
/////////////////////////////////////////////////////////////////////
//  Validity checking functions

// function to display an error message from BDE error code
// Most of this is copied from BDE API Help
// this function is not used within the class because all errors are handled as exceptions
DBIResult CBdeDatabase::Check(DBIResult ErrorValue, LPCTSTR szMessage)
{
	char        dbi_status[DBIMAXMSGLEN * 5] = {'\0'};
	DBIMSG      dbi_string = {'\0'};
	DBIErrInfo  ErrInfo;
	CString s;

	if (ErrorValue == DBIERR_NONE) return ErrorValue;

	DbiGetErrorInfo(TRUE, &ErrInfo);

	if (ErrInfo.iError == ErrorValue)
	{
		wsprintf(dbi_status, "%s", ErrInfo.szErrCode);

		if (strcmp(ErrInfo.szContext1, ""))
			wsprintf(dbi_status, "%s\r\n    %s", dbi_status, ErrInfo.szContext1);

		if (strcmp(ErrInfo.szContext2, ""))
			wsprintf(dbi_status, "%s\r\n    %s", dbi_status, ErrInfo.szContext2);
		if (strcmp(ErrInfo.szContext3, ""))
			wsprintf(dbi_status, "%s\r\n    %s", dbi_status, ErrInfo.szContext3);
		if (strcmp(ErrInfo.szContext4, ""))
			wsprintf(dbi_status, "%s\r\n    %s", dbi_status, ErrInfo.szContext4);
	}
	else
	{
		 DbiGetErrorString(ErrorValue, dbi_string);
		 wsprintf(dbi_status, "%s", dbi_string);
	}

	if (szMessage != NULL)
	{
		s.Format("%s\n\nBorland Database Engine returned the following error:\n%s",
			szMessage, dbi_status);
	}
	else
	{
		s.Format("Borland Database Engine Error:\n%s",
			dbi_status);
	}

	AfxMessageBox(s, MB_OK | MB_ICONEXCLAMATION);
  return ErrorValue;
}




// function to make sure the BDE has been initialize before any function calls
BOOL CBdeDatabase::CheckInitialization(LPCTSTR szOperation /* = NULL */)
{
	if (m_bInitialized) return TRUE;

	// if this happens, it is not BDE's fault, it is the programmers!
	throw new CBdeException(DBIERR_NONE, BDEEXERR_NOTINITIALIZED,
		m_szTableName, m_szDatabaseName, szOperation);
	return FALSE;
}


// function throws an exception if the cursor position is not valid
// meaning a database has not been opened
BOOL CBdeDatabase::CheckValidCursor(LPCTSTR szOperation /* = NULL */)
{
	// check for initialization
	if (!CheckInitialization(szOperation)) return FALSE;

	// check the validity of the cursor
	if (m_hCursor != NULL && m_hDb != NULL) return TRUE;
	throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDCURSOR,
		m_szTableName, m_szDatabaseName, szOperation);
	return FALSE;
}

// function throws an exception if the database is NOT in edit mode
BOOL CBdeDatabase::CheckEditMode(LPCTSTR szOperation /* = NULL */)
{
	if (m_nEditMode != EDITMODE_NONE) return TRUE;
	throw new CBdeException(DBIERR_NONE, BDEEXERR_NOTINEDITMODE,
		m_szTableName, m_szDatabaseName, szOperation);
	return FALSE;
}


// function throws an exception if the database IS in edit mode
BOOL CBdeDatabase::CheckNotEditMode(LPCTSTR szOperation /* = NULL */)
{
	if (m_nEditMode == EDITMODE_NONE) return TRUE;
	throw new CBdeException(DBIERR_NONE, BDEEXERR_ALREADYINEDITMODE,
		m_szTableName, m_szDatabaseName, szOperation);
	return FALSE;
}




/////////////////////////////////////////////////////////////
//  Database Navigation Functions

void CBdeDatabase::MoveFirst()
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to move to beginning of table.")) return;
	if (!CheckNotEditMode("Failed to move to beginning of table.")) return;

  DBIResult dbiResult = DbiSetToBegin(m_hCursor);
	if (dbiResult == DBIERR_NONE || dbiResult == DBIERR_BOF)
	{
		dbiResult = DbiGetNextRecord(m_hCursor, dbiNOLOCK, NULL, NULL);
		return;
	}

	CString s;
	s.Format("Failed to move to the beginning of table %s.", m_szTableName);
	throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, s);
	dbiResult = DbiGetNextRecord(m_hCursor, dbiNOLOCK, NULL, NULL);
}


void CBdeDatabase::MoveNext()
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to move to next record.")) return;
	if (!CheckNotEditMode("Failed to move to next record.")) return;

	DBIResult dbiResult = DbiGetNextRecord(m_hCursor, dbiNOLOCK, NULL, NULL);
	if (dbiResult == DBIERR_NONE) return;
	if (dbiResult == DBIERR_EOF)
	{
		dbiResult = DbiGetPriorRecord(m_hCursor, dbiNOLOCK, NULL, NULL);
		return;
	}
	CString s;
	s.Format("Failed to move to the next record in table %s.", m_szTableName);
	throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, s);
}

void CBdeDatabase::MovePrior()
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to move to previous record.")) return;
	if (!CheckNotEditMode("Failed to move to previous record.")) return;

	DBIResult dbiResult = DbiGetPriorRecord(m_hCursor, dbiNOLOCK, NULL, NULL);
	if (dbiResult == DBIERR_NONE) return;
	if (dbiResult == DBIERR_BOF)
	{
		dbiResult = DbiGetNextRecord(m_hCursor, dbiNOLOCK, NULL, NULL);
		return;
	}
	CString s;
	s.Format("Failed to move to the previous record in table %s.", m_szTableName);
	throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, s);
}


void CBdeDatabase::MoveLast()
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to move to end of table.")) return;
	if (!CheckNotEditMode("Failed to move to end of table.")) return;

  DBIResult dbiResult = DbiSetToEnd(m_hCursor);
	if (dbiResult == DBIERR_NONE || dbiResult == DBIERR_EOF)
	{
		dbiResult = DbiGetPriorRecord(m_hCursor, dbiNOLOCK, NULL, NULL);
		return;	
	}
	CString s;
	s.Format("Failed to move to the end of table %s.", m_szTableName);
	throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, s);
}


LONG CBdeDatabase::GetRecordCount()
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to get number of records.")) return -1L;

	ASSERT(m_hCursor != NULL);
	UINT32 nRecNum;
	DBIResult dbiResult = DbiGetRecordCount(m_hCursor, &nRecNum);

	if (dbiResult == DBIERR_NONE) return (LONG)nRecNum;
	CString s;
	s.Format("Failed to determine the number of records in table %s.", m_szTableName);
	throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, s);
  return -1L;
}


BOOL CBdeDatabase::IsBOF()
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor()) return FALSE;
	if (!CheckNotEditMode()) return FALSE;

	DBIResult dbiResult;
	BOOL bRetVal;

	// Check if we are at the end of the table.
	dbiResult = DbiGetPriorRecord(m_hCursor, dbiNOLOCK, NULL, NULL);
	if (dbiResult == DBIERR_BOF) bRetVal = TRUE;
	else bRetVal = FALSE;

	// Put the cursor back to where it was before entering this function.
	DbiGetNextRecord(m_hCursor, dbiNOLOCK, NULL, NULL);

	return bRetVal;
}


BOOL CBdeDatabase::IsEOF()
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor()) return FALSE;
	if (!CheckNotEditMode()) return FALSE;

	DBIResult dbiResult; 
	BOOL bRetVal;

	// Check if we are at the end of the table.
	dbiResult = DbiGetNextRecord(m_hCursor, dbiNOLOCK, NULL, NULL);
	if (dbiResult == DBIERR_EOF) bRetVal = TRUE;
	else bRetVal = FALSE;

	// Put the cursor back to where it was before entering this function.
	DbiGetPriorRecord(m_hCursor, dbiNOLOCK, NULL, NULL);

	return bRetVal;
}








/////////////////////////////////////////////////////////////////////////////
//  Functions to read field values


CString CBdeDatabase::GetFieldAsString(UINT16 nFieldNumber, BOOL* pbBlank)
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to get field value.")) return "";
	if (!CheckNotEditMode("Failed to get field value.")) return "";

	DBIResult dbiResult = DBIERR_NONE;
	CString strValue;
	CString strError;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc = NULL; // field information
  pBYTE pRecBuf = NULL; // Record Buffer
	int nBdeExError = 0;

	
	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return "";
  }

	// make sure the field number is valid
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return "";
	}


	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return "";
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return "";
	}

		
	// save the size and type of the field
	UINT16 nSize = pFldDesc[nFieldNumber-1].iLen;
	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;
	UINT16 nFieldSubType = pFldDesc[nFieldNumber-1].iSubType;
	UINT16 nUnits = pFldDesc[nFieldNumber-1].iUnits2;

	free(pFldDesc); // clean up the field descriptor
	pFldDesc = NULL;


	// allocate the record buffer for the table
  pRecBuf = (pBYTE) malloc(curProps.iRecBufSize * sizeof(BYTE));
	if (pRecBuf == NULL)
  {
		strError.Format("Insufficient memory to get field number %d.", nFieldNumber);
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
    return "";
  }

	// fill the record buffer with information
	dbiResult = DbiGetRecord(m_hCursor, dbiNOLOCK, pRecBuf, NULL);
	if (dbiResult != DBIERR_NONE)
	{
		free(pRecBuf);
		strError.Format("Failed to get record information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
	  return "";
	}

	// allocate memory for the string buffer to recieve data
	pBYTE pDestBuf = (pBYTE)malloc(nSize*sizeof BYTE);
	memset(pDestBuf, 0, nSize*sizeof BYTE);


	if (pDestBuf == NULL)
	{
		// Throw memory exception here
		free(pRecBuf);
		strError.Format("Failed to get record information.");
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
		return "";
	}
	
	// get the actual field value

	switch (nFieldType)
	{
    case fldBYTES: // Bytes
    case fldZSTRING: // String
		{
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)pDestBuf, pbBlank);
			strValue.Format("%s", (char*)pDestBuf);
			break;
		}
		case fldFLOAT:
		{
			double f;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&f, pbBlank);
			if (*pbBlank == FALSE)
			{
				if (nFieldSubType == fldstMONEY)
				{
					strValue.Format("$%.2lf", f);
				}
				else
				{
					strValue.Format("%g", f);
				}
			}
			break;
		}
		case fldBCD:
		{
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, 
				(pBYTE)pDestBuf, pbBlank);
			if (*pbBlank == FALSE)
			{
				double lfFloat;
				DbiBcdToFloat((FMTBcd *)pDestBuf,	&lfFloat);
        strValue.Format("%.*lf", nUnits, lfFloat);
			}
			break;
		}

		case fldDATE:
		{
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, 
				(pBYTE)pDestBuf, pbBlank);
			if (*pbBlank == FALSE)
			{
				// Here is a difficult situation...
				// dates are returned as 4 bytes, but in the 32-bit world
				// the DATE type is 8 bytes.  Typcasting directly to DATE
				// does not work.  We have to type cast to 32 bit int, then
				// to 64-bit int, and then to DATE
				INT32 n32 = (*(INT32 *)pDestBuf);
				strValue = FormatDate(n32);
			}
			break;
		}
		case fldTIME:
		{
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, 
				(pBYTE)pDestBuf, pbBlank);
			if (*pbBlank == FALSE)
			{
				strValue = FormatTime(*(TIME *)pDestBuf);
			}
			break;
		}
		case fldTIMESTAMP:
		{
			// size of timestamp is 8
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, 
				(pBYTE)pDestBuf, pbBlank);
			if (*pbBlank == FALSE)
			{
				TIMESTAMP dt = *(TIMESTAMP*)pDestBuf;
				strValue = FormatTimeStamp(dt);
			}
			break;
		}
		case fldINT16:
		{
			INT16 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				strValue.Format("%d", n);
			}
			break;
		}
		case fldUINT16:
		{
			UINT16 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				strValue.Format("%d", n);
			}
			break;
		}
		case fldINT32:
		{
			INT32 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				strValue.Format("%d", n);
			}
			break;
		}
		case fldUINT32:
		{
			UINT32 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				strValue.Format("%d", n);
			}
			break;
		}
		case fldBOOL:
		{
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)pDestBuf, pbBlank);
			if (*pbBlank == FALSE)
      {
        if (*(BYTE*)pDestBuf == 0) strValue = "FALSE";
        else strValue = "TRUE";
      }
			break;
		}
		case fldBLOB:	// NOTE:  This does not work on dBase files.
		{
			if (nFieldSubType == fldstMEMO)
			{
				UINT32 ulBlobSize; // Size of the BLOB

				// Open the blob
				dbiResult = DbiOpenBlob(m_hCursor, pRecBuf, nFieldNumber, dbiREADONLY);
				if (dbiResult != DBIERR_NONE) break;

        // Determine the size of the BLOB.
				dbiResult = DbiGetBlobSize(m_hCursor, pRecBuf, nFieldNumber, &ulBlobSize);
				if (dbiResult != DBIERR_NONE) break;

				// Get the BLOB from the table.
				dbiResult = DbiGetBlob(m_hCursor, pRecBuf, nFieldNumber, 0,
					ulBlobSize, (pBYTE)pDestBuf, &ulBlobSize);
				pDestBuf[ulBlobSize + 1] = '\0';
				strValue.Format("%s", pDestBuf);

				DbiFreeBlob(m_hCursor, pRecBuf, nFieldNumber);
				
				if (dbiResult != DBIERR_NONE) break;
			}
			else
			{
				// Handle non-memo formats here
				nBdeExError = BDEEXERR_UNSUPPORTEDBLOBTYPE;
			}
			break;
		}
		default:
		{
			nBdeExError = BDEEXERR_UNSUPPORTEDFIELDTYPE;
			break;
		}
	} // end of swtich

	// process the final error codes
	if (dbiResult != DBIERR_NONE || nBdeExError != 0)
	{
		// Throw exception here
		strError.Format("Failed to retrieve data for field %d.",
			nFieldNumber);
	  free(pRecBuf);
		free(pDestBuf);
		throw new CBdeException(dbiResult, nBdeExError, m_szTableName, 
			m_szDatabaseName, strError);
		return "";
	} 

	free(pDestBuf);
  free(pRecBuf);
	return strValue;
} // end of GetFieldAsString



// function to get the field value as an integer
// throws an exception for incompatible data types
LONG CBdeDatabase::GetFieldAsInteger(UINT16 nFieldNumber, BOOL* pbBlank)
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to get field value.")) return 0L;
	if (!CheckNotEditMode("Failed to get field value.")) return 0L;

	DBIResult dbiResult = DBIERR_NONE;
	LONG nValue = 0L;
	CString strError;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc; // field information
  pBYTE pRecBuf; // Record Buffer
	int nBdeExError = 0;

	
	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return 0L;
  }

	// make sure the field number is valid
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return 0L;
	}


	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return 0L;
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return 0L;
	}

		
	// save the size and type of the field
	UINT16 nSize = pFldDesc[nFieldNumber-1].iLen;
	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;

	free(pFldDesc); // clean up the field descriptor
	pFldDesc = NULL;


	// allocate the record buffer for the table
  pRecBuf = (pBYTE) malloc(curProps.iRecBufSize * sizeof(BYTE));
	if (pRecBuf == NULL)
  {
		strError.Format("Insufficient memory to get field number %d.", nFieldNumber);
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
    return 0L;
  }

	// fill the record buffer with information
	dbiResult = DbiGetRecord(m_hCursor, dbiNOLOCK, pRecBuf, NULL);
	if (dbiResult != DBIERR_NONE)
	{
		free(pRecBuf);
		strError.Format("Failed to get record information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
	  return 0L;
	}

	// allocate memory for the string buffer to recieve data
	pBYTE pDestBuf = (pBYTE)malloc(nSize*sizeof BYTE);
	memset(pDestBuf, 0, nSize*sizeof BYTE);


	if (pDestBuf == NULL)
	{
		// Throw memory exception here
		free(pRecBuf);
		strError.Format("Failed to get record information.");
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
		return 0L;
	}
	
	// get the actual field value

	switch (nFieldType)
	{
		case fldINT16:
		{
			INT16 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				nValue = (LONG)n;
			}
			break;
		}
		case fldUINT16:
		{
			UINT16 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				nValue = (LONG)n;
			}
			break;
		}
		case fldINT32:
		{
			INT32 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				nValue = (LONG)n;
			}
			break;
		}
		case fldUINT32:
		{
			UINT32 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				nValue = (LONG)n;
			}
			break;
		}
		case fldFLOAT: // need to handl floats for dBase files
		{
			double f;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&f, pbBlank);
			if (*pbBlank == FALSE)
			{
				nValue = (LONG)f;
			}
			break;
		}
		case fldBOOL:
		{
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)pDestBuf, pbBlank);
			if (*pbBlank == FALSE)
      {
        if (*(BYTE*)pDestBuf == 0)
        {
					nValue = 0L;
        }
        else
        {
					nValue = 1L;
        }
      }
			break;
		}
		default:
		{
			nBdeExError = BDEEXERR_FIELDNOTINTEGER;
		}
	} // end of swtich

	// process the final exceptions
	if (dbiResult != DBIERR_NONE || nBdeExError != 0)
	{
		// Throw exception here
		strError.Format("Failed to retrieve data for field %d.",
			nFieldNumber);
	  free(pRecBuf);
		free(pDestBuf);
		throw new CBdeException(dbiResult, nBdeExError, m_szTableName, 
			m_szDatabaseName, strError);
		return 0L;
	} 

	free(pDestBuf);
  free(pRecBuf);
	return nValue;
} // end of GetFieldAsInteger



// function to get the field value as a float
// works on float, currency, BCD, and all integer types
double CBdeDatabase::GetFieldAsFloat(UINT16 nFieldNumber, BOOL* pbBlank)
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor()) return 0.0;
	if (!CheckNotEditMode()) return 0.0;

	DBIResult dbiResult = DBIERR_NONE;
	double fValue = 0.0;
	CString strError;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc; // field information
  pBYTE pRecBuf; // Record Buffer
	int nBdeExError = 0;

	
	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return 0.0;
  }

	// make sure the field number is valid
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return 0.0;
	}

	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return 0.0;
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return 0.0;
	}

		
	// save the size and type of the field
	UINT16 nSize = pFldDesc[nFieldNumber-1].iLen;
	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;

	free(pFldDesc); // clean up the field descriptor
	pFldDesc = NULL;


	// allocate the record buffer for the table
  pRecBuf = (pBYTE) malloc(curProps.iRecBufSize * sizeof(BYTE));
	if (pRecBuf == NULL)
  {
		strError.Format("Insufficient memory to get field number %d.", nFieldNumber);
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
    return 0.0;
  }

	// fill the record buffer with information
	dbiResult = DbiGetRecord(m_hCursor, dbiNOLOCK, pRecBuf, NULL);
	if (dbiResult != DBIERR_NONE)
	{
		free(pRecBuf);
		strError.Format("Failed to get record information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
	  return 0.0;
	}

	// allocate memory for the string buffer to recieve data
	pBYTE pDestBuf = (pBYTE)malloc(nSize*sizeof BYTE);
	memset(pDestBuf, 0, nSize*sizeof BYTE);


	if (pDestBuf == NULL)
	{
		// Throw memory exception here
		free(pRecBuf);
		strError.Format("Failed to get record information.");
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
		return 0.0;
	}
	
	// get the actual field value
	switch (nFieldType)
	{
		case fldFLOAT:
		{
			double f;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&f, pbBlank);
			if (*pbBlank == FALSE)
			{
				fValue = f;
			}
			break;
		}
		case fldBCD:
		{
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, 
				(pBYTE)pDestBuf, pbBlank);
			if (*pbBlank == FALSE)
			{
				double lfFloat;
				DbiBcdToFloat((FMTBcd *)pDestBuf,	&lfFloat);
				fValue = lfFloat;
			}
			break;
		}
		case fldINT16:
		{
			INT16 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				fValue = (double)n;
			}
			break;
		}
		case fldUINT16:
		{
			UINT16 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				fValue = (double)n;
			}
			break;
		}
		case fldINT32:
		{
			INT32 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				fValue = (double)n;
			}
			break;
		}
		case fldUINT32:
		{
			UINT32 n;
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)&n, pbBlank);
			if (*pbBlank == FALSE)
			{
				fValue = (double)n;
			}
			break;
		}
		default:
		{
			nBdeExError = BDEEXERR_FIELDNOTFLOAT;
		}
	} // end of swtich


	if (dbiResult != DBIERR_NONE || nBdeExError != 0)
	{
		// Throw exception here
		strError.Format("Failed to retrieve data for field %d.",
			nFieldNumber);
	  free(pRecBuf);
		free(pDestBuf);
		throw new CBdeException(dbiResult, nBdeExError, m_szTableName, 
			m_szDatabaseName, strError);
		return 0.0;
	} 

	free(pDestBuf);
  free(pRecBuf);
	return fValue;
} // end of GetFieldAsFloat




COleDateTime CBdeDatabase::GetFieldAsDate(UINT16 nFieldNumber, BOOL* pbBlank)
{
	DBIResult dbiResult = DBIERR_NONE;
	int nBdeExError = 0;
	CString strError;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc; // field information
  pBYTE pRecBuf; // Record Buffer
	COleDateTime dtRetVal = 0.0;
	dtRetVal.m_status = COleDateTime::null; 

	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to get field value.")) return dtRetVal;
	if (!CheckNotEditMode("Failed to get field value.")) return dtRetVal;

	
	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return dtRetVal;
  }

	// make sure the field number is valid
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return dtRetVal;
	}

	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return dtRetVal;
	}

	// get the field descriptors to get the type of the field
	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return dtRetVal;
	}

	// save the size and type of the field
	UINT16 nSize = pFldDesc[nFieldNumber-1].iLen;
	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;

	free(pFldDesc); // clean up the field descriptor
	pFldDesc = NULL;


	// allocate the record buffer for the table
  pRecBuf = (pBYTE) malloc(curProps.iRecBufSize * sizeof(BYTE));
	if (pRecBuf == NULL)
  {
		strError.Format("Insufficient memory to get field number %d.", nFieldNumber);
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
    return dtRetVal;
  }

	// fill the record buffer with information
	dbiResult = DbiGetRecord(m_hCursor, dbiNOLOCK, pRecBuf, NULL);
	if (dbiResult != DBIERR_NONE)
	{
		free(pRecBuf);
		strError.Format("Failed to get record information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
	  return dtRetVal;
	}

	// allocate memory for the string buffer to recieve data
	pBYTE pDestBuf = (pBYTE)malloc(nSize*sizeof BYTE);
	memset(pDestBuf, 0, nSize*sizeof BYTE);


	if (pDestBuf == NULL)
	{
		// Throw memory exception here
		free(pRecBuf);
		strError.Format("Failed to get record information.");
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
		return dtRetVal;
	}
	
	// get the actual field value

	switch (nFieldType)
	{
		case fldDATE:
		{
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, 
				(pBYTE)pDestBuf, pbBlank);
			if (*pbBlank == FALSE)
			{
				// Here is a difficult situation...
				// dates are returned as 4 bytes, but in the 32-bit world
				// the DATE type is 8 bytes.  Typcasting directly to DATE
				// does not work.  We have to type cast to 32 bit int, then
				// to 64-bit int, and then to DATE
				INT32 n32 = (*(INT32 *)pDestBuf);
				dtRetVal = DateToOleDateTime(n32);
			}
			break;
		}
		case fldTIME:
		{
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, 
				(pBYTE)pDestBuf, pbBlank);
			if (*pbBlank == FALSE)
			{
				dtRetVal = TimeToOleDateTime((*(TIME *)pDestBuf));
			}
			break;
		}
		case fldTIMESTAMP:
		{
			// sie of timestamp is 8
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, 
				(pBYTE)pDestBuf, pbBlank);
			if (*pbBlank == FALSE)
			{
				TIMESTAMP timestamp = *(TIMESTAMP*)pDestBuf;
				dtRetVal = TimeStampToOleDateTime(timestamp);
			}
			break;
		}
		default:
		{
			nBdeExError = BDEEXERR_FIELDNOTDATE;
		}
	} // end of swtich

	if (dbiResult != DBIERR_NONE || nBdeExError != 0)
	{
		// Throw exception here
		strError.Format("Failed to retrieve data for field %d.",
			nFieldNumber);
	  free(pRecBuf);
		free(pDestBuf);
		throw new CBdeException(dbiResult, nBdeExError, m_szTableName, 
			m_szDatabaseName, strError);
		return dtRetVal;
	} 

	free(pDestBuf);
  free(pRecBuf);
	return dtRetVal;
} // end of GetFieldAsDate





// function to get the field value as an integer
// throws an exception for incompatible data types
BOOL CBdeDatabase::GetFieldAsBoolean(UINT16 nFieldNumber, BOOL* pbBlank)
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to get field value.")) return 0L;
	if (!CheckNotEditMode("Failed to get field value.")) return 0L;

	DBIResult dbiResult = DBIERR_NONE;
	BOOL bValue = FALSE;
	CString strError;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc; // field information
  pBYTE pRecBuf; // Record Buffer
	int nBdeExError = 0;

	
	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
  }

	// make sure the field number is valid
	// TODO:  This should throw an exception
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}


	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return FALSE;
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}

		
	// save the size and type of the field
	UINT16 nSize = pFldDesc[nFieldNumber-1].iLen;
	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;

	free(pFldDesc); // clean up the field descriptor
	pFldDesc = NULL;


	// allocate the record buffer for the table
  pRecBuf = (pBYTE) malloc(curProps.iRecBufSize * sizeof(BYTE));
	if (pRecBuf == NULL)
  {
		strError.Format("Insufficient memory to get field number %d.", nFieldNumber);
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
    return FALSE;
  }

	// fill the record buffer with information
	dbiResult = DbiGetRecord(m_hCursor, dbiNOLOCK, pRecBuf, NULL);
	if (dbiResult != DBIERR_NONE)
	{
		free(pRecBuf);
		strError.Format("Failed to get record information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
	  return FALSE;
	}

	// allocate memory for the string buffer to recieve data
	pBYTE pDestBuf = (pBYTE)malloc(nSize*sizeof BYTE);
	memset(pDestBuf, 0, nSize*sizeof BYTE);


	if (pDestBuf == NULL)
	{
		// Throw memory exception here
		free(pRecBuf);
		strError.Format("Failed to get record information.");
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}
	
	// get the actual field value

	switch (nFieldType)
	{
		case fldBOOL:
		{
			dbiResult = DbiGetField(m_hCursor, nFieldNumber, pRecBuf, (pBYTE)pDestBuf, pbBlank);
			if (*pbBlank == FALSE)
      {
        if (*(BYTE*)pDestBuf == 0) bValue = FALSE;
        else bValue = TRUE;
      }
			break;
		}
		default:
		{
			nBdeExError = BDEEXERR_FIELDNOTINTEGER;
		}
	} // end of swtich

	// process the final exceptions
	if (dbiResult != DBIERR_NONE || nBdeExError != 0)
	{
		// Throw exception here
		strError.Format("Failed to retrieve data for field %d.",
			nFieldNumber);
	  free(pRecBuf);
		free(pDestBuf);
		throw new CBdeException(dbiResult, nBdeExError, m_szTableName, 
			m_szDatabaseName, strError);
		return FALSE;
	} 

	free(pDestBuf);
  free(pRecBuf);
	return bValue;
} // end of GetFieldAsBoolean




// returns the 1 based index of a field name
// returns 0 on error
int CBdeDatabase::GetFieldSize(int nFieldNumber)
{
	// Throw an exception if not in edit mode
	if (!CheckValidCursor("Failed to get field size.")) return 0;

	DBIResult dbiResult;
	CURProps CurProps;
	pFLDDesc pFldDesc;
	int nSize = -1;
	CString strError;

	dbiResult = DbiGetCursorProps(m_hCursor, &CurProps);

	if (dbiResult != DBIERR_NONE)
	{
		strError.Format("Failed to retrieve size of field %d.",
			nFieldNumber);
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return -1;
	}


	pFldDesc = (pFLDDesc)malloc(CurProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return -1;
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);

	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return -1;
	}
		
	nSize = pFldDesc[nFieldNumber-1].iLen;
	free(pFldDesc);
	return nSize;
}
	

// returns the number of fields in the current table
// returns -1 on error
int CBdeDatabase::GetFieldCount()
{
	if (!CheckValidCursor("Failed to get field count.")) return -1;

	DBIResult dbiResult;
	CURProps CurProps;
	CString strError;
	CString strRetVal;

	dbiResult = DbiGetCursorProps(m_hCursor, &CurProps);

	if (dbiResult != DBIERR_NONE)
	{
		strError.Format("Failed to cursor properties in table %s.",
			m_szTableName);
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return 0;
	}

	return CurProps.iFields;
}


// function to get the filed type
// returns 0 on error
int CBdeDatabase::GetFieldType(int nFieldNumber)
{
	// Throw an exception if not in edit mode
	if (!CheckValidCursor("Failed to get field type.")) return FALSE;
	if (!CheckEditMode("Failed to get field type.")) return FALSE;

	DBIResult dbiResult;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc; // field information
	CString strError;

	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return 0;
  }

	// make sure the field number is valid
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return 0;
	}


	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return 0;
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return 0;
	}

	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;

	free(pFldDesc); // clean up the field descriptor
	return (int)nFieldType;
}


// function to get the filed type
// returns 0 on error or not a blob
int CBdeDatabase::GetBlobType(int nFieldNumber)
{
	// Throw an exception if not in edit mode
	if (!CheckValidCursor("Failed to get field type.")) return FALSE;
	if (!CheckEditMode("Failed to get field type.")) return FALSE;

	DBIResult dbiResult;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc; // field information
	CString strError;

	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return 0;
  }

	// make sure the field number is valid
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return 0;
	}


	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return 0;
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return 0;
	}

	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;
	UINT16 nFieldSubType = pFldDesc[nFieldNumber-1].iSubType;

	free(pFldDesc); // clean up the field descriptor

	if (nFieldType != fldBLOB) return 0;
	return (int)nFieldSubType;
}



// function to get the field name from it's number
CString CBdeDatabase::GetFieldName(int nFieldNumber)
{
	if (!CheckValidCursor("Failed to get field name.")) return "";

	DBIResult dbiResult;
	CURProps CurProps;
	pFLDDesc pFldDesc;
	CString strError;
	CString strRetVal;

	dbiResult = DbiGetCursorProps(m_hCursor, &CurProps);

	if (dbiResult != DBIERR_NONE)
	{
		strError.Format("Failed to cursor properties in table %s.",
			m_szTableName);
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return "";
	}

	// make sure the number is within the proper range
	if (nFieldNumber < 1 || nFieldNumber > CurProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, CurProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return "";
	}


	// allocate memory for the field descriptor
	pFldDesc = (pFLDDesc)malloc(CurProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return "";
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);

	if (dbiResult != DBIERR_NONE)
	{
		// Throw exception here
		strError.Format("Failed to get field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		free(pFldDesc);
		return "";
	}

	strRetVal.Format("%s", pFldDesc[nFieldNumber-1].szName);
	free(pFldDesc);
	return strRetVal;
}


// returns the 1 based index of a field name
// returns 0 on error
int CBdeDatabase::FieldNumberFromName(LPCTSTR szFieldName)
{
	if (!CheckValidCursor()) return 0;

	DBIResult dbiResult;
	CURProps CurProps;
	pFLDDesc pFldDesc;
	UINT16 nField;
	BOOL bFound = FALSE;
	CString strError;
	int nRetVal = 0;

	dbiResult = DbiGetCursorProps(m_hCursor, &CurProps);

	if (dbiResult != DBIERR_NONE)
	{
		strError.Format("Failed to cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return nRetVal;
	}


	pFldDesc = (pFLDDesc)malloc(CurProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return nRetVal;
	}


	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);

	if (dbiResult != DBIERR_NONE)
	{
		// TODO:  Throw exception here
		strError.Format("Failed to get field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		free(pFldDesc);
		return nRetVal;
	}

	for (nField = 0; nField < CurProps.iFields; nField++)
	{
		if (_stricmp(pFldDesc[nField].szName, szFieldName) == 0)
		{
			bFound = TRUE;
			nRetVal = pFldDesc[nField].iFldNum;
			free(pFldDesc);
			return nRetVal;
		}
	}
	free(pFldDesc);

	// did not find the name so throw an exception
		

	return nRetVal;
}



/////////////////////////////////////////////////////////////////////////
// Data type conversion functions

CString CBdeDatabase::FormatDate(INT32 Date)
{
	DBIResult   dbiResult;       // Return Value from IDAPI
	FMTDate     fmtDate;    // Date Format
	UINT16      uDay;       // Day portion of date
	UINT16      uMonth;     // Month portion of date
	INT16       iYear;      // Year portion of date
	CString strRetVal;
            
	// Get the formatting of the Date.
	dbiResult = DbiGetDateFormat(&fmtDate);
	if (dbiResult != DBIERR_NONE) return "";


	// Decode the date.
	dbiResult = DbiDateDecode(Date, &uMonth, &uDay, &iYear);
	if (dbiResult != DBIERR_NONE) return "";

	// Determine if date should be displayed year based.
	if (!(fmtDate.bFourDigitYear) && (fmtDate.bYearBiased))
	{
		iYear = (INT16)(iYear + 1900);
	}

	if (!(fmtDate.bFourDigitYear))
	{
		iYear = (INT16)(iYear - 1900);
	}

	// Make certain the seperator is not the
	//   escape character.
	if (!strcmp(fmtDate.szDateSeparator, "\\"))
	{
		strcpy(fmtDate.szDateSeparator, "/");
	}

	// Format the date.
	switch(fmtDate.iDateMode)
	{
			// MM/DD/YY - Month, Day, Year.
			case 0:
					strRetVal.Format("%0*d%s%0*d%s%0*d",
									1 + fmtDate.bMonthLeadingZero,
									uMonth,
									fmtDate.szDateSeparator,
									1 + fmtDate.bDayLeadingZero,
									uDay,
									fmtDate.szDateSeparator,
									2,
									iYear);
					break;
			// DD/MM/YY - Day, Month, Year
			case 1:
					strRetVal.Format("%0*d%s%0*d%s%0*d",
									1 + fmtDate.bDayLeadingZero,
									uDay,
									fmtDate.szDateSeparator,
									1 + fmtDate.bMonthLeadingZero,
									uMonth,
									fmtDate.szDateSeparator,
									2,
									iYear);
					break;
			// YY/MM/DD - Year, Month, Day
			case 2:
					strRetVal.Format("%0*d%s%0*d%s%0*d",
									2,
									iYear,
									fmtDate.szDateSeparator,
									1 + fmtDate.bMonthLeadingZero,
									uMonth,
									fmtDate.szDateSeparator,
									1 + fmtDate.bDayLeadingZero,
									uDay);
					break;
	}
	return strRetVal;
}


CString CBdeDatabase::FormatTime(TIME Time)
{
	DBIResult   dbiResult;       // Return value from IDAPI functions
	FMTTime     fmtTime;    // Time format
	UINT16      uHour;      // Hour portion of the time
	UINT16      uMinute;    // Minute portion of the time
	UINT16      uMilSec;    // Second portion (in ms) of the time
	UINT16      uIsAm = 0;      // Is Time AM?
	CHAR        szTemp[10]; // Temp buffer, used for AM, PM string
	CHAR szTime[48];
	CString strRetVal;

	// Get the formatting of the Time.
	dbiResult = DbiGetTimeFormat(&fmtTime);
	if (dbiResult != DBIERR_NONE) return strRetVal;

	// Decode the time.
	dbiResult = DbiTimeDecode(Time, &uHour, &uMinute, &uMilSec);
	if (dbiResult != DBIERR_NONE) return strRetVal;

	// Make certain the seperator is not the
	//   escape character.
	if (fmtTime.cTimeSeparator == '\\')
	{
		fmtTime.cTimeSeparator  = '/';
	}

	// Check if time should be displayed in 12 or 24 hour format.
	if (fmtTime.bTwelveHour)
	{
		// Temporary variable used to determine if the time is AM or PM.
		uIsAm = uHour;
		uHour = (UINT16)(uHour % 12);
		if (uHour == 0)
		{
			uHour = 12;
		}
		// If AM, set uIsAm to TRUE, else set uIsAm to 0.
		if (uIsAm == uHour)
		{
			uIsAm = 1;
		}
		else
		{
			uIsAm = 0;
		}
	}

	// Format the hour and minute of the time.
	wsprintf(szTime, "%2u%c%02u", uHour, fmtTime.cTimeSeparator, uMinute);

	// Determine if seconds are to be displayed.
	if (fmtTime.bSeconds)
	{
		wsprintf(szTemp, "%c%02u", fmtTime.cTimeSeparator, (uMilSec / 1000));
		strcat(szTime, szTemp);

		// Determine if milliseconds are to be displayed.
		if (fmtTime.bMilSeconds)
		{
			wsprintf(szTemp, "%c%03u", fmtTime.cTimeSeparator, (uMilSec % 1000));
			strcat(szTime, szTemp);   
		}
	}

	// Add a string to the time if the time is 12-hour.
	if (fmtTime.bTwelveHour)
	{
		strcat(szTime, " ");
		if (uIsAm)
		{
			strcat(szTime, fmtTime.szAmString);
		}
		else // otherwise it's PM
		{
			strcat(szTime, fmtTime.szPmString);
		}
	}

	strRetVal.Format("%s", szTime);
	return strRetVal;
}



CString CBdeDatabase::FormatTimeStamp(TIMESTAMP TimeStamp)
{
	DBIResult   rslt;       // Return value from IDAPI functions
	TIME        Time;       // Time portion of the TimeStamp
	CString strRetVal;
	INT32 nDate32;

	// Get the date and time components
	rslt = ::DbiTimeStampDecode(TimeStamp, &nDate32, &Time);

	// Format the TimeStamp
	strRetVal.Format("%s %s", FormatDate(nDate32), FormatTime(Time));

	return strRetVal;
}


// function to convert a TIMESTAMP to a COleDateTime
COleDateTime CBdeDatabase::TimeStampToOleDateTime(TIMESTAMP TimeStamp)
{
	DBIResult dbiResult;       // Return value from IDAPI functions
	TIME Time; // Time portion of the TimeStamp, actually a LONG
	INT32 n32; // date portion of the timestamp
	UINT16 hour, min, msec, day, month;
	INT16 year;
	COleDateTime dtRetVal = 0.0;
	dtRetVal.m_status = COleDateTime::null;

	// Get the date and time components
	dbiResult = ::DbiTimeStampDecode(TimeStamp, &n32, &Time);
	if (dbiResult != DBIERR_NONE) return dtRetVal;

	dbiResult = ::DbiTimeDecode(Time, &hour, &min, &msec);
	if (dbiResult != DBIERR_NONE) return dtRetVal;

	dbiResult = DbiDateDecode(n32, &month, &day, &year);
	if (dbiResult != DBIERR_NONE) return dtRetVal;

	dtRetVal.SetDateTime(year, month, day, hour, min, msec/1000);
	return dtRetVal;	
}





COleDateTime CBdeDatabase::TimeToOleDateTime(TIME time)
{
	DBIResult dbiResult;       // Return value from IDAPI functions
	UINT16 hour, min, msec;
	COleDateTime dtRetVal = 0.0;
	dtRetVal.m_status = COleDateTime::null;

	dbiResult = ::DbiTimeDecode(time, &hour, &min, &msec);
	if (dbiResult != DBIERR_NONE) return dtRetVal;

	dtRetVal.SetTime(hour, min, msec/1000);
	return dtRetVal;	
}


COleDateTime CBdeDatabase::DateToOleDateTime(INT32 Date)
{
	DBIResult dbiResult;       // Return value from IDAPI functions
	UINT16 day, month;
	INT16 year;
	COleDateTime dtRetVal = 0.0;
	dtRetVal.m_status = COleDateTime::null;

	dbiResult = DbiDateDecode(Date, &month, &day, &year);
	if (dbiResult != DBIERR_NONE) return dtRetVal;

	dtRetVal.SetDate(year, month, day);
	return dtRetVal;	
}



DBIResult CBdeDatabase::OleDateTimeToTimeStamp(COleDateTime dt, pTIMESTAMP pTimeStamp)
{
	DBIResult dbiResult;       // Return value from IDAPI functions
	TIME Time; // Time portion of the TimeStamp, actually a LONG
	INT32 n32; // date portion of the timestamp
	UINT16 hour, min, msec, day, month;
	INT16 year;

	// Get the date and time components
	year = (INT16)dt.GetYear();
	month = (UINT16)dt.GetMonth();
	day = (UINT16)dt.GetDay();
	hour = (UINT16)dt.GetHour();
	min = (UINT16)dt.GetMinute();
	msec = (UINT16)(dt.GetSecond()*1000);

	dbiResult = ::DbiTimeEncode(hour, min, msec, &Time);
	if (dbiResult != DBIERR_NONE) return dbiResult;

	dbiResult = DbiDateEncode(month, day, year, &n32);
	if (dbiResult != DBIERR_NONE) return dbiResult;

	dbiResult = ::DbiTimeStampEncode(n32, Time, pTimeStamp);
	if (dbiResult != DBIERR_NONE) return dbiResult;

	return DBIERR_NONE;	
}


INT32 CBdeDatabase::OleDateTimeToDate(COleDateTime dt)
{
	INT32 n32 = 0;
	UINT16 day, month;
	INT16 year;

	day = (UINT16)dt.GetDay();
	month = (UINT16)dt.GetMonth();
	year = (INT16)dt.GetYear();
		
	::DbiDateEncode(month, day, year, &n32);
	return n32;	
}


TIME CBdeDatabase::OleDateTimeToTime(COleDateTime dt)
{
	UINT16 hour, min, msec;
	TIME time = 0L;

	hour = (UINT16)dt.GetHour();
	min = (UINT16)dt.GetMinute();
	msec = (UINT16)(dt.GetSecond() * 1000);

	::DbiTimeEncode(hour, min, msec, &time);
	return time;	
}




/////////////////////////////////////////////////////////////////////////////////
//  Functions to set field values


// set field as a string, pass NULL or blank to set as a blank
BOOL CBdeDatabase::SetFieldAsString(INT16 nFieldNumber, LPCTSTR szValue, 
	BOOL bBlank /* = FALSE */)
{
	// Throw an exception if not in edit mode
	if (!CheckValidCursor("Failed to set field value.")) return FALSE;
	if (!CheckEditMode("Failed to set field value.")) return FALSE;

	DBIResult dbiResult;
	int nBdeExError = 0;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc; // field information
	CString strError;

	// make sure edit mode allows editing
	// and m_pEditRecordBuffer is not NULL
	if (m_pEditRecordBuffer == NULL)
	{
		strError.Format("Failed to set field %d to value '%s'.", nFieldNumber, szValue);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_NOTINEDITMODE, m_szTableName,
			m_szDatabaseName, strError);
		return FALSE;
	}

	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
  }

	// make sure the field number is valid
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}


	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return FALSE;
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}

	UINT16 nSize = pFldDesc[nFieldNumber-1].iLen;
	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;
	UINT16 nFieldSubType = pFldDesc[nFieldNumber-1].iSubType;
	UINT16 nPrecision = pFldDesc[nFieldNumber-1].iUnits2;
	if (m_nTableType == TABLETYPE_PARADOX) nPrecision = 32;
	UINT16 nDecimals = pFldDesc[nFieldNumber-1].iUnits2;

	free(pFldDesc); // clean up the field descriptor
	pFldDesc = NULL;

	// handle the situation for a blank
	if (bBlank)
	{
		dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, NULL);
		return TRUE;
	}

	// handle the situation for a NULL buffer
	if (szValue == NULL)
	{
		dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, NULL);
		return TRUE;
	}

	// if an empty string is passed, then set the field to blank
	if (strlen(szValue) == 0)
	{
		dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, NULL);
		return TRUE;
	}

	// allocate memory for the string buffer to recieve data
	pBYTE pSourceBuf = (pBYTE)malloc(nSize*sizeof BYTE);
	memset(pSourceBuf, 0, nSize*sizeof BYTE);

	// check for memory error
	if (pSourceBuf == NULL)
	{
		// Throw memory exception here
		free(pSourceBuf);
		strError.Format("Failed to set field %d to value '%s'.", nFieldNumber, szValue);
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}
	
	// set the field value based on it's type
	switch (nFieldType)
	{
    case fldBYTES: // Bytes
    case fldZSTRING: // String
		{
			strncpy((char*)pSourceBuf, szValue, nSize);
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)pSourceBuf);
			break;
		}
		case fldFLOAT:
		{
			double f = atof(szValue);
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&f);
			break;
		}
		case fldBCD:
		{
			double f = atof(szValue);
			DbiBcdFromFloat(&f, nPrecision, nDecimals, (FMTBcd *)pSourceBuf);
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)pSourceBuf);
			break;
		}
		case fldINT16:
		{
			INT16 n16 = (INT16)atoi(szValue);
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&n16);
			break;
		}
		case fldUINT16:
		{
			UINT16 n16 = (UINT16)atoi(szValue);
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&n16);
			break;
		}
		case fldINT32:
		{
			INT32 n32 = (INT32)atoi(szValue);
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&n32);
			break;
		}
		case fldUINT32:
		{
			UINT32 n32 = (UINT32)atoi(szValue);
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&n32);
			break;
		}
		case fldBOOL:
		{
			BOOL bVal = TRUE;
			if (szValue[0] == 'F' || szValue[0] == 'f') bVal = FALSE;
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&bVal);
			break;
		}
		case fldDATE:
		{
			COleDateTime dtOle;
			INT32 n32;
			if (dtOle.ParseDateTime(szValue, VAR_DATEVALUEONLY))
			{
				n32 = OleDateTimeToDate(dtOle);
				dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&n32);
			}
			else
			{
				// set an extended exception code here
				nBdeExError = BDEEXERR_INVALIDDATETIMEFORMAT;
			}
			break;
		}
		case fldTIME:
		{
			COleDateTime dtOle;
			TIME time;
			if (dtOle.ParseDateTime(szValue, VAR_TIMEVALUEONLY))
			{
				time = OleDateTimeToTime(dtOle);
				dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&time);
			}
			else
			{
				// set an extended exception code here
				nBdeExError = BDEEXERR_INVALIDDATETIMEFORMAT;
			}
			break;
		}
		case fldTIMESTAMP:
		{
			COleDateTime dtOle;
			TIMESTAMP timestamp;
			if (dtOle.ParseDateTime(szValue, 0))
			{
				dbiResult = OleDateTimeToTimeStamp(dtOle, &timestamp);
				if (dbiResult == DBIERR_NONE)
					dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&timestamp);
			}
			else
			{
				// set an extended exception code here
				nBdeExError = BDEEXERR_INVALIDDATETIMEFORMAT;
			}
			break;			
		}
		case fldBLOB:
		{
			if (nFieldSubType == fldstMEMO)
			{
				// Open the blob
				dbiResult = DbiOpenBlob(m_hCursor, m_pEditRecordBuffer, nFieldNumber, dbiREADWRITE);
				if (dbiResult != DBIERR_NONE) break;

				// Allocate memory for the blob
				pBYTE pBlobSourceBuf = (pBYTE)malloc(strlen(szValue)*sizeof BYTE + 1);

				// Check for NULL
				if (pBlobSourceBuf == NULL)
				{
					dbiResult = DBIERR_NOMEMORY;
					DbiFreeBlob(m_hCursor, m_pEditRecordBuffer, nFieldNumber);
					break;
				}

				// initialize the blob data
				memset(pBlobSourceBuf, 0, strlen(szValue)*sizeof BYTE + 1);

				// copy the string into the blob data
				strncpy((char*)pBlobSourceBuf, szValue, strlen(szValue));

				/// copy the blob data to the table
				dbiResult = DbiPutBlob(m_hCursor, m_pEditRecordBuffer, nFieldNumber, 0,
					strlen(szValue) + 1, (pBYTE)pBlobSourceBuf);

				// free the blob data				
				free(pBlobSourceBuf);
								
				// check for errors
				if (dbiResult != DBIERR_NONE)
				{
					DbiFreeBlob(m_hCursor, m_pEditRecordBuffer, nFieldNumber); 
				}
			}
			else
			{
				// TODO: Handle situations for non-memo blobs
				nBdeExError = BDEEXERR_UNSUPPORTEDBLOBTYPE;
			}
			break;
		}		
		default:
		{
			nBdeExError = BDEEXERR_UNSUPPORTEDFIELDTYPE;		
		}
	} // end of switch

	if (dbiResult != DBIERR_NONE || nBdeExError != 0)
	{
		// Throw exception here
		strError.Format("Failed to set field %d to value '%s'.", nFieldNumber, szValue);
		free(pSourceBuf);
		throw new CBdeException(dbiResult, nBdeExError, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	} 

	free(pSourceBuf);
	return TRUE;
} // end of SetFieldAsString




BOOL CBdeDatabase::SetFieldAsInteger(INT16 nFieldNumber, int nValue, 
	BOOL bBlank /* = FALSE */)
{
	// Throw an exception if not in edit mode
	if (!CheckValidCursor("Failed to set field value.")) return FALSE;
	if (!CheckEditMode("Failed to set field value.")) return FALSE;

	DBIResult dbiResult;
	int nBdeExError = 0;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc; // field information
	CString strError;

	// make sure edit mode allows editing
	// and m_pEditRecordBuffer is not NULL
	if (m_pEditRecordBuffer == NULL)
	{
		strError.Format("Failed to set field %d to value %d.", nFieldNumber, nValue);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_NOTINEDITMODE, m_szTableName,
			m_szDatabaseName, strError);
		return FALSE;
	}

	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
  }

	// make sure the field number is valid
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}


	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return FALSE;
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}

	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;

	free(pFldDesc); // clean up the field descriptor
	pFldDesc = NULL;

	// handle the situation for a blank
	if (bBlank)
	{
		dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, NULL);
		return TRUE;
	}


	// set the field value based on it's type
	switch (nFieldType)
	{
		case fldINT16:
		{
			INT16 n16 = (INT16)nValue;
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&n16);
			break;
		}
		case fldUINT16:
		{
			UINT16 n16 = (UINT16)nValue;
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&n16);
			break;
		}
		case fldINT32:
		{
			INT32 n32 = (INT32)nValue;
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&n32);
			break;
		}
		case fldUINT32:
		{
			UINT32 n32 = (UINT32)nValue;
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&n32);
			break;
		}
		case fldFLOAT: // need to handle floats for dBase tables
		{
			double fValue = (double)nValue;
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, 
				(pBYTE)&fValue);
			break;
		}
		case fldBOOL:
		{
			BOOL bVal = (nValue == 0);
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&bVal);
			break;
		}
		default:
		{
			// Handle non-integer types here
			nBdeExError = BDEEXERR_FIELDNOTINTEGER;
		}
	} // end of switch

	if (dbiResult != DBIERR_NONE || nBdeExError != 0)
	{
		// Throw exception here
		strError.Format("Failed to set field %d to value %d.", nFieldNumber, nValue);
		throw new CBdeException(dbiResult, nBdeExError, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	} 

	return TRUE;
} // end of SetFieldAsInteger




BOOL CBdeDatabase::SetFieldAsBoolean(INT16 nFieldNumber, BOOL bValue, 
	BOOL bBlank /* = FALSE */)
{
	// Throw an exception if not in edit mode
	if (!CheckValidCursor("Failed to set field value.")) return FALSE;
	if (!CheckEditMode("Failed to set field value.")) return FALSE;

	DBIResult dbiResult;
	int nBdeExError = 0;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc; // field information
	CString strError;

	// make sure edit mode allows editing
	// and m_pEditRecordBuffer is not NULL
	if (m_pEditRecordBuffer == NULL)
	{
		strError.Format("Failed to set field %d value.", nFieldNumber);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_NOTINEDITMODE, m_szTableName,
			m_szDatabaseName, strError);
		return FALSE;
	}

	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
  }

	// make sure the field number is valid
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}

	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return FALSE;
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}

	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;

	free(pFldDesc); // clean up the field descriptor
	pFldDesc = NULL;

	// handle the situation for a blank
	if (bBlank)
	{
		dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, NULL);
		return TRUE;
	}


	// set the field value based on it's type
	switch (nFieldType)
	{
		case fldBOOL:
		{
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, 
				(pBYTE)&bValue);
			break;
		}
		default:
		{
			// Handle non-boolean types here
			nBdeExError = BDEEXERR_FIELDNOTBOOLEAN;
		}
	} // end of switch

	if (dbiResult != DBIERR_NONE || nBdeExError != 0)
	{
		// Throw exception here
		strError.Format("Failed to set field %d value.", nFieldNumber);
		throw new CBdeException(dbiResult, nBdeExError, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	} 

	return TRUE;
} // end of SetFieldAsBoolean





BOOL CBdeDatabase::SetFieldAsFloat(INT16 nFieldNumber, double fValue, 
	BOOL bBlank /* = FALSE */)
{
	// Throw an exception if not in edit mode
	if (!CheckValidCursor("Failed to set field value.")) return FALSE;
	if (!CheckEditMode("Failed to set field value.")) return FALSE;

	DBIResult dbiResult = DBIERR_NONE;
	int nBdeExError = 0;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc; // field information
	CString strError;

	// make sure edit mode allows editing
	// and m_pEditRecordBuffer is not NULL
	if (m_pEditRecordBuffer == NULL)
	{
		strError.Format("Failed to set field %d to value %g.", nFieldNumber, fValue);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_NOTINEDITMODE, m_szTableName,
			m_szDatabaseName, strError);
		return FALSE;
	}

	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
  }

	// make sure the field number is valid
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}

	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return FALSE;
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}

	UINT16 nSize = pFldDesc[nFieldNumber-1].iLen;
	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;
	UINT16 nPrecision = pFldDesc[nFieldNumber-1].iUnits1;
	if (m_nTableType == TABLETYPE_PARADOX) nPrecision = 32;
	UINT16 nDecimals = pFldDesc[nFieldNumber-1].iUnits2;

	free(pFldDesc); // clean up the field descriptor
	pFldDesc = NULL;

	// handle the situation for a blank
	if (bBlank)
	{
		dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, NULL);
		return TRUE;
	}


	// allocate memory for the string buffer to recieve data
	pBYTE pSourceBuf = (pBYTE)malloc(nSize*sizeof BYTE);
	memset(pSourceBuf, 0, nSize*sizeof BYTE);

	// check for memory error
	if (pSourceBuf == NULL)
	{
		// Throw memory exception here
		free(pSourceBuf);
		strError.Format("Failed to set field %d to value %g.", nFieldNumber, fValue);
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}
	
	// set the field value based on it's type
	switch (nFieldType)
	{
		case fldFLOAT:
		{
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, 
				(pBYTE)&fValue);
			break;
		}
		case fldBCD:
		{
			// handle precision and stuff here
			DbiBcdFromFloat(&fValue, nPrecision, nDecimals, (FMTBcd *)pSourceBuf);
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)pSourceBuf);
			break;
		}
		default:
		{
			nBdeExError = BDEEXERR_FIELDNOTFLOAT;
		}
	} // end of switch

	if (dbiResult != DBIERR_NONE || nBdeExError != 0)
	{
		// Throw exception here
		strError.Format("Failed to set field %d to value %g.", nFieldNumber, fValue);
		free(pSourceBuf);
		throw new CBdeException(dbiResult, nBdeExError, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	} 

	free(pSourceBuf);

	return TRUE;
} // end of SetFieldAsFloat






BOOL CBdeDatabase::SetFieldAsDate(INT16 nFieldNumber, COleDateTime dtValue, 
	BOOL bBlank /* = FALSE */)
{
	// Throw an exception if not in edit mode
	if (!CheckValidCursor("Failed to set field value.")) return FALSE;
	if (!CheckEditMode("Failed to set field value.")) return FALSE;

	DBIResult dbiResult = DBIERR_NONE;
	int nBdeExError = 0;
  CURProps curProps; // Table Properties
	pFLDDesc pFldDesc; // field information
	CString strError;

	// make sure edit mode allows editing
	// and m_pEditRecordBuffer is not NULL
	if (m_pEditRecordBuffer == NULL)
	{
		strError.Format("Failed to set field %d to value %s.", nFieldNumber, 
			dtValue.Format("%m/%d/%Y %H:%M:%S"));
		throw new CBdeException(DBIERR_NONE, BDEEXERR_NOTINEDITMODE, m_szTableName,
			m_szDatabaseName, strError);
		return FALSE;
	}

	// get the cursor properties for the table
  dbiResult = DbiGetCursorProps(m_hCursor, &curProps);
	if (dbiResult != DBIERR_NONE)
  {
		strError.Format("Failed to get cursor properties.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
  }

	// make sure the field number is valid
	if (nFieldNumber < 1 || nFieldNumber > curProps.iFields)
	{
		strError.Format("Invalid field index %d.  Valid numbers are between 1 and %d.", 
			nFieldNumber, curProps.iFields);
		throw new CBdeException(DBIERR_NONE, BDEEXERR_INVALIDFIELDINDEX,
			m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}

	// allocate memory for the field descriptors
	pFldDesc = (pFLDDesc)malloc(curProps.iFields * sizeof(FLDDesc));
	if (pFldDesc == NULL)
	{
		// Throw exception for DBIERR_NOMEMORY
		throw new CBdeException(DBIERR_NOMEMORY);
		return FALSE;
	}

	dbiResult = DbiGetFieldDescs(m_hCursor, pFldDesc);
	if (dbiResult != DBIERR_NONE)
	{
		free(pFldDesc);
		strError.Format("Failed to retrieve field information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	}

	UINT16 nFieldType = pFldDesc[nFieldNumber-1].iFldType;

	free(pFldDesc); // clean up the field descriptor
	pFldDesc = NULL;

	// handle the situation for a blank	or invalid date time
	if (bBlank || dtValue.m_status != COleDateTime::valid)
	{
		dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, NULL);
		return TRUE;
	}


	// set the field value based on it's type
	switch (nFieldType)
	{
		case fldDATE:
		{
			INT32 n32;
			n32 = OleDateTimeToDate(dtValue);
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&n32);
			break;
		}
		case fldTIME:
		{
			TIME time;
			time = OleDateTimeToTime(dtValue);
			dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&time);
			break;
		}
		case fldTIMESTAMP:
		{
			TIMESTAMP timestamp;
			dbiResult = OleDateTimeToTimeStamp(dtValue, &timestamp);
			if (dbiResult == DBIERR_NONE)
				dbiResult = DbiPutField(m_hCursor, nFieldNumber, m_pEditRecordBuffer, (pBYTE)&timestamp);
			break;			
		}		
		default:
		{
			// Handle non-date types here
			nBdeExError = BDEEXERR_FIELDNOTDATE;
		}
	} // end of switch

	if (dbiResult != DBIERR_NONE || nBdeExError != 0)
	{
		// Throw exception here
		strError.Format("Failed to set field %d to value %s.", nFieldNumber, 
			dtValue.Format("%m/%d/%Y %H:%M:%S"));
		throw new CBdeException(dbiResult, nBdeExError, m_szTableName, m_szDatabaseName, strError);
		return FALSE;
	} 

	return TRUE;
} // end of set field as date







//////////////////////////////////////////////////////////////////////////////////
//  Functions to edit or insert records
//
//  To edit or insert a record...
//	Call Edit or Insert or Append to set the table for editing
//	Create the record buffer
//  Fill the record buffer with the information
//  Call Post or Cancel to finalize or abort the changes
//


// function to begin editing the current record of the table
BOOL CBdeDatabase::Edit()
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to edit record.")) return FALSE;
	if (!CheckNotEditMode("Failed to edit record.")) return FALSE;

	// make sure not already in edit mode
	if (m_pEditRecordBuffer != NULL)
	{
		throw new CBdeException(DBIERR_NONE, BDEEXERR_ALREADYINEDITMODE, 
			m_szTableName, m_szDatabaseName, "Failed to edit record.");
		return FALSE;
	}

	// prepare the record buffer for editing
	if (!PrepareRecordEdit(EDITMODE_EDITINPLACE)) return FALSE;

	// set the edit mode
	m_nEditMode = EDITMODE_EDITINPLACE;
	return TRUE;
}



// function to insert a record at the current position in the table
BOOL CBdeDatabase::Insert()
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to add new record.")) return FALSE;
	if (!CheckNotEditMode("Failed to add new record.")) return FALSE;

	// make sure not already in edit mode
	if (m_pEditRecordBuffer != NULL)
	{
		throw new CBdeException(DBIERR_NONE, BDEEXERR_ALREADYINEDITMODE, 
			m_szTableName, m_szDatabaseName, "Failed to insert record.");
		return FALSE;
	}

	// prepare the record buffer for editing
	if (!PrepareRecordEdit(EDITMODE_INSERT)) return FALSE;

	// set the edit mode
	m_nEditMode = EDITMODE_INSERT;
	return TRUE;
}



// function to append a record to the end of the table
BOOL CBdeDatabase::Append()
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to add new record.")) return FALSE;
	if (!CheckNotEditMode("Failed to add new record.")) return FALSE;

	// make sure not already in edit mode
	if (m_pEditRecordBuffer != NULL)
	{
		throw new CBdeException(DBIERR_NONE, BDEEXERR_ALREADYINEDITMODE, 
			m_szTableName, m_szDatabaseName, "Failed to add record.");
		return FALSE;
	}

	// prepare the record buffer for editing
	if (!PrepareRecordEdit(EDITMODE_APPEND)) return FALSE;

	// set the edit mode
	m_nEditMode = EDITMODE_APPEND;
	return TRUE;
}



// function to prepare for editing a record
// it allocates the record buffer
// it returns FALSE on failure, in which case no record buffer is allocated
BOOL CBdeDatabase::PrepareRecordEdit(int nEditMode)
{
	DBIResult dbiResult;
  CURProps CursorProps;       // Table descriptor
	

	// get the size of the tables record
  dbiResult = DbiGetCursorProps(m_hCursor, &CursorProps);
	if (dbiResult != DBIERR_NONE)
	{
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, 
			"Failed to get cursor properties.");
		return FALSE;
	}

	// allocate the buffer for the record
  m_pEditRecordBuffer = (pBYTE)malloc(CursorProps.iRecBufSize);
  if (m_pEditRecordBuffer == NULL)
  {
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, 
			"Failed to allocate record buffer.");
		return FALSE;
  }


	// if inserting or appending then initialize the record buffer
	// otherwise, fill the record buffer with current info
	if (nEditMode == EDITMODE_EDITINPLACE)
	{
		dbiResult = DbiGetRecord(m_hCursor, dbiNOLOCK, m_pEditRecordBuffer, NULL);
		if (dbiResult != DBIERR_NONE)
		{
			free(m_pEditRecordBuffer);
			m_pEditRecordBuffer = NULL;
			throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, 
				"Failed to initialize record buffer.");
			return FALSE;
		}
	}
	else
	{
		dbiResult = DbiInitRecord(m_hCursor, m_pEditRecordBuffer);
		if (dbiResult != DBIERR_NONE)
		{
			free(m_pEditRecordBuffer);
			m_pEditRecordBuffer = NULL;
			throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, 
				"Failed to initialize record buffer.");
			return FALSE;
		}
	}
	return TRUE;
}



// function to finalize edit, append, or insert operations and update the table
// if post fails, cancel must be called to clean up the record buffer
BOOL CBdeDatabase::Post()
{
	// Throw an exception if database is in NOT in Edit mode
	if (!CheckValidCursor("Failed to accept tables changes.")) return FALSE;
	if (!CheckEditMode("Failed to accept tables changes.")) return FALSE;


	DBIResult dbiResult;

	if (m_pEditRecordBuffer == NULL)
	{
		throw new CBdeException(DBIERR_NONE, BDEEXERR_NOTINEDITMODE, 
			m_szTableName, m_szDatabaseName, "Failed to accept changes.");
		return FALSE;
	}

	switch (m_nEditMode)
	{
		case EDITMODE_EDITINPLACE:
		{
			dbiResult = DbiModifyRecord(m_hCursor, m_pEditRecordBuffer, TRUE);
			if (dbiResult != DBIERR_NONE)
			{
				throw new CBdeException(dbiResult, m_szTableName, 
					m_szDatabaseName, "Failed to accept changes.");
				return FALSE;
			}
			break;
		}
		// Note the append may only be appropriate if there are no idexes
		case EDITMODE_APPEND:
		{
			dbiResult = DbiAppendRecord(m_hCursor, m_pEditRecordBuffer);
			if (dbiResult != DBIERR_NONE)
			{
				throw new CBdeException(dbiResult, m_szTableName, 
					m_szDatabaseName, "Failed to accept changes.");
				return FALSE;
			}
			break;
		}
		case EDITMODE_INSERT:
		{
			dbiResult = DbiInsertRecord(m_hCursor, dbiNOLOCK, m_pEditRecordBuffer);
			if (dbiResult != DBIERR_NONE)
			{
				throw new CBdeException(dbiResult, m_szTableName, 
					m_szDatabaseName, "Failed to accept changes.");
				return FALSE;
			}
			break;
		}
		default:
			ASSERT(FALSE);
	}
	
	// clean up the edit record buffer
	free(m_pEditRecordBuffer);
	m_pEditRecordBuffer = NULL;

	// reset the edit mode
	m_nEditMode = 0;
	
	return TRUE;
}


// function to cancel edit, append, or insert operations
BOOL CBdeDatabase::Cancel()
{
	if (!CheckInitialization()) return FALSE;

	// this function should be safe to call even if no edit buffer
	if (m_pEditRecordBuffer == NULL)
	{
		ASSERT(m_nEditMode == 0);
		return TRUE;
	}

	// clean up the edit record buffer
	free(m_pEditRecordBuffer);
	m_pEditRecordBuffer = NULL;

	// reset the edit mode
	m_nEditMode = 0;
	return TRUE;	
}



BOOL CBdeDatabase::DeleteRecord()
{
	// Throw an exception if database is in Edit mode
	if (!CheckValidCursor("Failed to delete record.")) return FALSE;
	if (!CheckNotEditMode("Failed to delete record.")) return FALSE;

	DBIResult dbiResult;
  CURProps CursorProps;       // Table descriptor
	pBYTE pRecBuf = NULL;
	CString strError;
	
	// get the size of the tables record
  dbiResult = DbiGetCursorProps(m_hCursor, &CursorProps);
	if (dbiResult != DBIERR_NONE)
	{
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, 
			"Failed to get cursor properties.");
		return FALSE;
	}

	// get the record buffer

 	// allocate the record buffer for the table
  pRecBuf = (pBYTE) malloc(CursorProps.iRecBufSize * sizeof(BYTE));
	if (pRecBuf == NULL)
  {
		strError.Format("Insufficient memory to get record buffer.");
		throw new CBdeException(DBIERR_NOMEMORY, m_szTableName, m_szDatabaseName, strError);
    return FALSE;
  }

	// fill the record buffer with information
	dbiResult = DbiGetRecord(m_hCursor, dbiNOLOCK, pRecBuf, NULL);
	if (dbiResult != DBIERR_NONE)
	{
		free(pRecBuf);
		strError.Format("Failed to get record information.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
	  return FALSE;
	}

	dbiResult = DbiDeleteRecord(m_hCursor, pRecBuf);
	if (dbiResult != DBIERR_NONE)
	{
		free(pRecBuf);
		strError.Format("Failed to delete record.");
		throw new CBdeException(dbiResult, m_szTableName, m_szDatabaseName, strError);
	  return FALSE;
	}

	// free up the record memory
	free(pRecBuf);

	// After deletion, the cursor is on a crack, so move it to a valid record
	// Move to the next record here, or if fails, move to previous
	dbiResult = DbiGetNextRecord(m_hCursor, dbiNOLOCK, NULL, NULL);
	if (dbiResult == DBIERR_EOF)
		dbiResult = DbiGetPriorRecord(m_hCursor, dbiNOLOCK, NULL, NULL);


	// if table is dBase, you may want to pack here

	return TRUE;
} // end of DeleteRecord function