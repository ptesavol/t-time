// BankAccount.cpp: implementation of the BankAccount class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4786)
#include "stdafx.h"
#include "BdeInserter.h"
#include "BankAccount.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BankAccount::BankAccount(): blank(FALSE)
{

}

BankAccount::~BankAccount()
{

}

string BankAccount::getAccountName()
	{
	return this->accountName;
	}

string BankAccount::getAccountNumber()
	{
	return this->accountNumber;
	}

void BankAccount::setAccountName(const string& name)
	{
	this->accountName=name;
	}

void BankAccount::setAccountNumber(const string& number)
	{
	this->accountNumber=number;
	}

void BankAccount::loadFromDb(CBdeDatabase& dbase)
	{
	accountNumber = dbase.GetFieldAsString(dbase.FieldNumberFromName("TilinNro"),&blank );
	accountName = dbase.GetFieldAsString(dbase.FieldNumberFromName("TilinNimi"),&blank );
	
	}

string BankAccount::toString()
	{
	string ret;
	ret+="TiliNimi: ";
	ret+=accountName;
	ret+="\r\n";
	ret+"TiliNro: ";
	ret+=accountNumber;
	return ret;
	}
