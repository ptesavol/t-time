// DbAccount.cpp: implementation of the DbAccount class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BdeInserter.h"
#include "DbAccount.h"
#include "BdeDatabase.h"
#include "stringhelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DbAccount::DbAccount()
{

}

DbAccount::~DbAccount()
{

}


void DbAccount::setAccountNumber(const string& _number)
	{
	this->accountNumber=_number;
	}

void DbAccount::setVatAccountNumber(const string& _number)
	{
	this->vatAccountNumber=_number;
	}

void DbAccount::setBalanceType(int _type)
	{
	this->balanceType=_type;
	}

string DbAccount::getAccountNumber()
	{
	return this->accountNumber;
	}

string DbAccount::getVatAccountNumber()
	{
	return this->vatAccountNumber;
	}

int DbAccount::getBalanceType()
	{
	return this->balanceType;
	}

void DbAccount::loadFromDb(CBdeDatabase& dbase)
	{
	accountNumber = dbase.GetFieldAsString(dbase.FieldNumberFromName("TiliNro"),&blank);	
	vatAccountNumber = dbase.GetFieldAsString(dbase.FieldNumberFromName("ALVTili"),&blank);	
	balanceType = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("TaseR"),&blank);
	}



string DbAccount::toString()
	{
	string ret;
	ret+="TiliNro: ";
	ret+=accountNumber;
	ret+="\r\n";
	ret+="ALVTili: ";
	ret+=vatAccountNumber;
	ret+="\r\n";
	ret+="TaseR: ";
	ret+=st(balanceType);
	return ret;
	}

int DbAccount::findAndLoadFromDb(const string& id, CBdeDatabase& dbase)
	{
	if (dbase.GetRecordCount()==0)
		return 1;
	dbase.MoveFirst();
	string tempid;
	for (int i=0; i<dbase.GetRecordCount(); i++)
		{
		tempid=dbase.GetFieldAsString(dbase.FieldNumberFromName("TiliNro"),&blank );
		if (tempid==id)
			{
			loadFromDb(dbase);
			return 0;
			}
		dbase.MoveNext();
		}		
	return 1;
	}