// AccountinException.h: interface for the AccountinException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCOUNTINEXCEPTION_H__64041141_5FE4_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_ACCOUNTINEXCEPTION_H__64041141_5FE4_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

using namespace std;

class AccountinException  
{
private: string reason;

public:
	AccountinException(const string& reason);
	virtual ~AccountinException();
	string getReason();
};

#endif // !defined(AFX_ACCOUNTINEXCEPTION_H__64041141_5FE4_11D8_80E8_0010A4DF8E4B__INCLUDED_)
