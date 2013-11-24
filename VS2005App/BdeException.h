//////////////////////////////////////////////////////////////////////////
//  BdeException.h -- Interface for Borland Database Engine exception handler


#ifndef __BDEEXCEPION_H__
#define __BDEEXCEPION_H__

//#include "Ms-idapi.h" // header file for BDE API calls

// Actually, we are supposed to include Ms-idapi.h, but all it has is
// the following three lines anyway.  This allows me to keep idapi.h in the project directory  
#define	__FLAT__
#define __WIN32__
#include "idapi.h"


// These are additional errors that may be generated in the 
// CBdeDatabase class
#define BDEEXERR_FIELDNOTINTEGER 1
#define BDEEXERR_FIELDNOTFLOAT 2
#define BDEEXERR_FIELDNOTDATE 3
#define BDEEXERR_FIELDNOTSTRING 4
#define BDEEXERR_NOSUCHFIELD 5
#define BDEEXERR_NOTINEDITMODE 6
#define BDEEXERR_ALREADYINEDITMODE 7
#define BDEEXERR_INVALIDCURSOR 8
#define BDEEXERR_ALREADYOPEN 9
#define BDEEXERR_NOTINITIALIZED 10
#define BDEEXERR_INVALIDDATETIMEFORMAT 11
#define BDEEXERR_UNSUPPORTEDFIELDTYPE 12
#define BDEEXERR_UNSUPPORTEDBLOBTYPE 13
#define BDEEXERR_FIELDNOTBOOLEAN 14
#define BDEEXERR_INVALIDFIELDINDEX 15
#define BDEEXERR_INVALIDFIELDNAME 16


class CBdeException : public CException
{
	DECLARE_DYNAMIC(CBdeException);

// construction/destruction
public:
	CBdeException();
	CBdeException(DBIResult dbiResult);
	CBdeException(DBIResult dbiResult, CString strTable,
		CString strDatabaseName, LPCTSTR szAddInfo);
	CBdeException(DBIResult dbiResult, UINT nExtendedError, CString strTable,
		CString strDatabaseName, LPCTSTR szAddInfo);
	
// Attributes
public:


protected:
	DBIResult m_dbiResult;
	UINT m_nExtendedError;
	CString m_strAddInfo;
	CString m_strTableName;
	CString m_strDatabaseName;

// Operations
public:
	virtual BOOL GetErrorMessage(LPTSTR lpszError, UINT nMaxError, 
		PUINT pnHelpContext = NULL);
	CString GetErrorMessage(BOOL bVerbose = TRUE);
	virtual int ReportError(UINT nType = MB_OK, UINT nMessageID = 0);
	static CString GetExtendedErrorMessage(int nError);


protected:

// inlines
public:
	inline LPCTSTR GetTableName() {
		return m_strTableName; }
	inline LPCTSTR GetAddInfo() {
		return m_strAddInfo; }
	inline LPCTSTR GetDatabaseName() {
		return m_strDatabaseName; }
	



}; // end of class definition



#endif __BDEEXCEPION_H__