// BankAccount.h: interface for the BankAccount class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BANKACCOUNT_H__6509C8A3_5D4B_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_BANKACCOUNT_H__6509C8A3_5D4B_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "BdeDatabase.h"

using namespace std;

class BankAccount  
{
private:
	BOOL blank;
	string accountNumber;
	string accountName;

public:
	BankAccount();
	virtual ~BankAccount();
	string getAccountName();
	string getAccountNumber();
	void setAccountName(const string& name);
	void setAccountNumber(const string& number);
	
	string toString();
	void loadFromDb(CBdeDatabase& dbase);

};

#endif // !defined(AFX_BANKACCOUNT_H__6509C8A3_5D4B_11D8_80E8_0010A4DF8E4B__INCLUDED_)
