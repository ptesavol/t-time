// DbCustomer.cpp: implementation of the DbCustomer class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4786)
#include "stdafx.h"
#include "BdeInserter.h"
#include "DbCustomer.h"
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

DbCustomer::DbCustomer(): blank(false)
{

}

DbCustomer::~DbCustomer()
{

}

void DbCustomer::setGroup(int _group)
	{
	this->group=_group;
	}

int DbCustomer::getGroup()
	{
	return this->group;
	} 


int DbCustomer::getCId()
	{
	return this->cId;
	}
string DbCustomer::getCName()
	{
	return this->cName;
	}
string DbCustomer::getCName2()
	{
	return this->cName2;
	}
string DbCustomer::getCAddress()
	{
	return this->cAddress;
	}
string DbCustomer::getCZipCode()
	{
	return this->cZipCode;
	}
string DbCustomer::getCZipName()
	{
	return this->cZipName;
	}
string DbCustomer::getCCountry()
	{
	return this->cCountry;
	}

void DbCustomer::setCId(int _id)
	{
	this->cId=_id;
	}
void DbCustomer::setCName(const string& _name)
	{
	this->cName=_name;
	}
void DbCustomer::setCName2(const string& _name)
	{
	this->cName2=_name;
	}
void DbCustomer::setCAddress(const string& _address)
	{
	this->cAddress=_address;
	}
void DbCustomer::setCZipCode(const string& _code)
	{
	this->cZipCode=_code;
	}
void DbCustomer::setCZipName(const string& _name)
	{
	this->cZipName=_name;
	}
void DbCustomer::setCCountry(const string& _country)
	{
	this->cCountry=_country;
	}


string DbCustomer::getCContactPerson()
	{
	return this->cContactPerson;
	}

void DbCustomer::setCContactPerson(const string& _person)
	{
	this->cContactPerson=_person;
	}

void DbCustomer::setDiscount(double _discount)
	{
	this->discount=_discount;
	}

void DbCustomer::setPayingCondition(const string& _condition)
	{
	this->payingcondition=_condition;
	}

double DbCustomer::getDiscount()
	{
	return this->discount;
	}

string DbCustomer::getPayingCondition()
	{
	return this->payingcondition;
	}

void DbCustomer::setCustomerNumber(const string& _number)
	{
	this->customernumber=_number;
	}

string DbCustomer::getCustomerNumber()
	{
	return this->customernumber;
	}


void DbCustomer::loadFromDb(CBdeDatabase& dbase)
	{
	group = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("Ryhma"),&blank);
	cId = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("Tunnus"),&blank);	
	cName = dbase.GetFieldAsString(dbase.FieldNumberFromName("Nimi"),&blank);
	cName2 = dbase.GetFieldAsString(dbase.FieldNumberFromName("Nimi2"),&blank);
	cAddress = dbase.GetFieldAsString(dbase.FieldNumberFromName("KatuOs"),&blank);
	cZipCode = dbase.GetFieldAsString(dbase.FieldNumberFromName("PostiNro"),&blank);	
	cZipName = dbase.GetFieldAsString(dbase.FieldNumberFromName("PosOs"),&blank);	
	cCountry = dbase.GetFieldAsString(dbase.FieldNumberFromName("Valtio"),&blank);
	payingcondition = dbase.GetFieldAsString(dbase.FieldNumberFromName("MyyntiMaksuehto"),&blank);
	discount = dbase.GetFieldAsFloat(dbase.FieldNumberFromName("RiviAlennus"),&blank);
	cContactPerson = dbase.GetFieldAsString(dbase.FieldNumberFromName("YhtHlo"),&blank);
	customernumber = dbase.GetFieldAsString(dbase.FieldNumberFromName("AsNro"),&blank);
	}



string DbCustomer::toString()
	{
	string ret;
	ret+="Tunnus: ";
	ret+=st(cId);
	ret+="\r\n";
	ret+="Nimi: ";
	ret+=cName;
	ret+="\r\n";
	ret+="Nimi2: ";
	ret+=cName2;
	ret+="\r\n";
	ret+="KatuOs: ";
	ret+=cAddress;
	ret+="\r\n";
	ret+="PostiNro: ";
	ret+=cZipCode;
	ret+="\r\n";
	ret+="PosOs: ";
	ret+=cZipName;
	ret+="\r\n";
	ret+="YhtHlo: ";
	ret+=cContactPerson;
	ret+="\r\n";
	ret+="Valtio: ";
	ret+=cCountry;
	ret+="\r\n";
	ret+="Rivialennus: ";
	ret+=st(discount);
	ret+="\r\n";
	ret+="MyyntiMaksuehto: ";
	ret+=payingcondition;
	ret+="\r\n";
	ret+="AsNro: ";
	ret+=customernumber;
	return ret;
	}

int DbCustomer::findAndLoadFromDb(int id, CBdeDatabase& dbase)
	{
	if (dbase.GetRecordCount()==0)
		return 1;
	dbase.MoveFirst();
	int tempid;
	for (int i=0; i<dbase.GetRecordCount(); i++)
		{
		tempid=dbase.GetFieldAsInteger(dbase.FieldNumberFromName("Tunnus"),&blank );
		if (tempid==id)
			{
			loadFromDb(dbase);
			return 0;
			}
		dbase.MoveNext();
		}		
	return 1;
	}