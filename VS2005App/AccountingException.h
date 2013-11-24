// AccountingException.h: interface for the AccountingException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCOUNTINGEXCEPTION_H__64041142_5FE4_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_ACCOUNTINGEXCEPTION_H__64041142_5FE4_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "AccountingException.h"

using namespace std;

class AccountingException  
{
private:
string reason;

public:
	AccountingException(const string& reason);
	virtual ~AccountingException();
	string getReason();
};

#endif // !defined(AFX_ACCOUNTINGEXCEPTION_H__64041142_5FE4_11D8_80E8_0010A4DF8E4B__INCLUDED_)
