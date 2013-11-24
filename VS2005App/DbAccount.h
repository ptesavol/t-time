// DbAccount.h: interface for the DbAccount class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBACCOUNT_H__601F1F81_5EDF_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_DBACCOUNT_H__601F1F81_5EDF_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "BdeDatabase.h"

using namespace std;

class DbAccount  
{
private: 
BOOL blank;
string accountNumber;
string vatAccountNumber;
int balanceType;

public:
	DbAccount();
	virtual ~DbAccount();

	void setAccountNumber(const string& _number);
	void setVatAccountNumber(const string& number);
	void setBalanceType(int _type);
	string getAccountNumber();
	string getVatAccountNumber();
	int getBalanceType();

	string toString();
	void loadFromDb(CBdeDatabase& dbase);
	int findAndLoadFromDb(const string& number, CBdeDatabase& dbase);
};

#endif // !defined(AFX_DBACCOUNT_H__601F1F81_5EDF_11D8_80E8_0010A4DF8E4B__INCLUDED_)
