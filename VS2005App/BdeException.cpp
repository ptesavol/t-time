//////////////////////////////////////////////////////////////////////
// BdeException.cpp -- Implementation of Borland Database Engine exception handler



#include "stdafx.h"
#include "BdeException.h"


IMPLEMENT_DYNAMIC(CBdeException, CException);


////////////////////////////////////////////////////////////////////////
//  CBdeException construction/destruction

CBdeException::CBdeException()
{
	m_dbiResult = DBIERR_NONE;
	m_nExtendedError = 0;
}


CBdeException::CBdeException(DBIResult dbiResult)
{
	m_dbiResult = dbiResult;
	m_nExtendedError = 0;
}


CBdeException::CBdeException(DBIResult dbiResult, CString strTable,
		CString strDatabaseName, LPCTSTR szAddInfo)
{
	m_dbiResult = dbiResult;
	if (szAddInfo != NULL)
		m_strAddInfo.Format("%s", szAddInfo);
	else m_strAddInfo = "Unspecified Illegal Borland Database Operation";
	m_strTableName = strTable;
	m_strDatabaseName = strDatabaseName;
	m_nExtendedError = 0;
}

CBdeException::CBdeException(DBIResult dbiResult, UINT nExtendedError, CString strTable,
		CString strDatabaseName, LPCTSTR szAddInfo)
{
	m_dbiResult = dbiResult;
	if (szAddInfo != NULL)
		m_strAddInfo.Format("%s", szAddInfo);
	else m_strAddInfo = "Unspecified Illegal Borland Database Operation";
	m_strTableName = strTable;
	m_strDatabaseName = strDatabaseName;
	m_nExtendedError = nExtendedError;
}


// TODO:  Fix this
BOOL CBdeException::GetErrorMessage(LPTSTR lpszError, UINT nMaxError, PUINT pnHelpContext)
{
	m_strAddInfo.Empty();	 // TODO:  Remove this line
	_tcsncpy(lpszError, GetErrorMessage(FALSE), nMaxError);
	return TRUE;
}


CString CBdeException::GetErrorMessage(BOOL bVerbose /*= TRUE */)
{
	char        dbi_status[DBIMAXMSGLEN * 5] = {'\0'};
	DBIMSG      dbi_string = {'\0'};
	DBIErrInfo  ErrInfo;
	CString sFinal;
	CString strDbiError;

	DbiGetErrorInfo(TRUE, &ErrInfo);

	if (m_nExtendedError != 0)
	{
		strDbiError = GetExtendedErrorMessage(m_nExtendedError); 
	}
	else if (ErrInfo.iError == m_dbiResult)
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
		strDbiError.Format("%s", dbi_status);
	}
	else
	{
		DbiGetErrorString(m_dbiResult, dbi_string);
		wsprintf(dbi_status, "%s", dbi_string);
		strDbiError.Format("%s", dbi_status);
	}

	// if not verbose, then only send a basic error message
	if (bVerbose == FALSE)
	{
		if (m_nExtendedError != 0) sFinal = strDbiError;		
		else sFinal.Format("%s", dbi_string);
		return sFinal;
	}

	// construct an advanced message
	if (m_strTableName.IsEmpty()) m_strTableName = "Unknown";
	if (m_strDatabaseName.IsEmpty()) m_strDatabaseName = "Unknown";


	sFinal.Format("%s\n\nTable:      %s\nDatabase:    %s\n\nBorland Database Engine returned the following error:\n%s",
		m_strAddInfo, m_strTableName, m_strDatabaseName, strDbiError);

  return sFinal;
}


int CBdeException::ReportError(UINT nType, UINT nMessageID)
{
	if (nMessageID == 0)
	{
		return AfxMessageBox(GetErrorMessage(), MB_OK | MB_ICONHAND);
	}
	CString s;
	if (s.LoadString(nMessageID))
	{
		return AfxMessageBox(s + "\n\n" + GetErrorMessage(), MB_OK | MB_ICONHAND);
	}
	return AfxMessageBox(GetErrorMessage(), nType);
}



CString CBdeException::GetExtendedErrorMessage(int nError)
{
	switch (nError)
	{
		case BDEEXERR_FIELDNOTINTEGER:
			return "Incompatible data types.  Field can not be read from or written to as an integer.";
		case BDEEXERR_FIELDNOTFLOAT:
			return "Incompatible data types.  Field can not be read from or written to as a floating point value.";
		case BDEEXERR_FIELDNOTDATE:
			return "Incompatible data types.  Field can not be read from or written to as a date.";
		case BDEEXERR_FIELDNOTSTRING:
			return "Incompatible data types.  Field can not be read from or written to as a string.";
		case BDEEXERR_NOSUCHFIELD:
			return "The specified field does not exist in the current table.";
		case BDEEXERR_NOTINEDITMODE:
			return "This operation can only be performed on a table in 'Edit' mode.  The current table is not in edit mode.";
		case BDEEXERR_ALREADYINEDITMODE:
			return "This operation can not be performed on a table in 'Edit' mode.  The current table is currently in edit mode.";
		case BDEEXERR_INVALIDCURSOR:
			return "The table is closed or has not been associated with a database or table file.  This operation can not be performed on a closed table.";
		case BDEEXERR_ALREADYOPEN:
			return "The table is currently is open.  This operation can not be performed on an open table.";
		case BDEEXERR_NOTINITIALIZED:
			return "This application has not initialized the Borland Database Engine.";
		case BDEEXERR_INVALIDDATETIMEFORMAT:
			return "Unrecognized or invalid date or time format.  The application could not translate the specified value to a date or time.";
		case BDEEXERR_UNSUPPORTEDFIELDTYPE:
			return "The field is a data type that is not supported by this application,";
		case BDEEXERR_UNSUPPORTEDBLOBTYPE:
			return "The blob field contains a data type that is not supported by this application,";
		case BDEEXERR_FIELDNOTBOOLEAN:
			return "Incompatible data types.  Field can not be read from or written to as a logical (true/false) value.";
		case BDEEXERR_INVALIDFIELDINDEX:
			return "Invalid field index.  The specified field number oes not exist in the current table.";
		case BDEEXERR_INVALIDFIELDNAME:
			return "Invalid field name.  The specified field does not exist in the current table.";
	} // end of switch

	return "";
}