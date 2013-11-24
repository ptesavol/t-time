// DbProduct.cpp: implementation of the DbProduct class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4786)
#include "stdafx.h"
#include "BdeInserter.h"
#include "BdeException.h"
#include "DbProduct.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "stringhelper.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DbProduct::DbProduct(): blank(FALSE), pAlv(NULL), reversedVat(0)
{

}

DbProduct::DbProduct(const string& _name, const string& _code, const string& _unit, double _unitprice, double _taxpercent): blank(FALSE)
	{
	this->name=_name;
	this->id=_code;
	this->unit=_unit;
	this->unitprice=_unitprice;
	this->taxpercent=_taxpercent;
	}
DbProduct::~DbProduct()
{

}

void DbProduct::setName(const string& _name)
	{
	this->name=_name;
	}

string DbProduct::getName()
	{
	return this->name;
	} 

void DbProduct::setGroup(int _group)
	{
	this->group=_group;
	}

int DbProduct::getGroup()
	{
	return this->group;
	} 

void DbProduct::setId(const string& _code)
	{
	this->id=_code;
	}

string DbProduct::getId()
	{
	return this->id;
	} 


void DbProduct::setAcAccountNumber(const string& _number)
	{
	this->acAccountNumber=_number;
	}

string DbProduct::getAcAccountNumber()
	{
	return this->acAccountNumber;
	}

void DbProduct::setUnit(const string& _unit)
	{
	this->unit=_unit;
	}


string DbProduct::getUnit()
	{
	return this->unit;
	} 

void DbProduct::setUnitPrice(double _price)
	{
	this->unitprice=_price;
	}

double DbProduct::getUnitPrice()
	{
	return this->unitprice;
	} 

void DbProduct::setTaxPercent(double _percent)
	{
	this->taxpercent=_percent;
	}

double DbProduct::getTaxPercent()
	{
	return this->taxpercent;
	} 

void DbProduct::setVatType(const string& _type)
	{
	this->vatType=_type;
	}

string DbProduct::getVatType()
	{
	return this->vatType;
	}

void DbProduct::setTaxCode(int _code)
	{
	this->taxCode=_code;
	}

int DbProduct::getTaxCode()
	{
	return this->taxCode;
	}

void DbProduct::setRevesedVat(int _mode)
	{
	this->reversedVat=_mode;
	}

int DbProduct::getRevesedVat()
	{
	return this->reversedVat;
	}

void DbProduct::setVatVect(Alv *pAlv)
	{
	this->pAlv = pAlv;
	}

void DbProduct::loadFromDb(CBdeDatabase& dbase)
	{
	name = dbase.GetFieldAsString(dbase.FieldNumberFromName("TuoteNimi"),&blank );
	group = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("TRyhmaTunnus"),&blank );
	//AfxMessageBox(group.c_str());

	id = dbase.GetFieldAsString(dbase.FieldNumberFromName("TuoteTunnus"),&blank );
	acAccountNumber= dbase.GetFieldAsString(dbase.FieldNumberFromName("MyyntiTiliNro"),&blank ); // 23.8.2011, KpTiliNro-kenttä ei enää käytössä -> käytä MyyntiTiliNro-kenttää
	unit = dbase.GetFieldAsString(dbase.FieldNumberFromName("Yksikko"),&blank );
	unitprice = dbase.GetFieldAsFloat(dbase.FieldNumberFromName("AHinta"),&blank );

	// 12.8.2010, J.V. Vanha laskutusohjelma ei sisällä AlvRyhmaID-kenttää -> käytä ALVKanta Alv-prosenttia suoraan, muuten Alv-ryhmästä alv-prosentti
	if(pAlv == NULL)
	{
		vatType = dbase.GetFieldAsString(dbase.FieldNumberFromName("ALVKanta"),&blank );
		if (vatType=="")
			taxpercent=0;
		if (vatType=="1")
			taxpercent=22;
		if (vatType=="2")
			taxpercent=17;
		if (vatType=="3")
			taxpercent=8;
	}
	else
		taxpercent = dbase.GetFieldAsFloat(dbase.FieldNumberFromName("AlvRyhmaID"),&blank );

	taxCode=dbase.GetFieldAsInteger(dbase.FieldNumberFromName("Verollisuuskoodi"),&blank );

	if(dbase.FieldNumberFromName("KaannettyVeroV") != 0)		// reversed vat
		reversedVat=dbase.GetFieldAsInteger(dbase.FieldNumberFromName("KaannettyVeroV"),&blank );
	}


int DbProduct::findAndLoadFromDb(const string& pid, CBdeDatabase& dbase)
	{
	if (dbase.GetRecordCount()==0)
		return 1;
	dbase.MoveFirst();
	string tempid;
	for (int i=0; i<dbase.GetRecordCount(); i++)
		{
		tempid=dbase.GetFieldAsString(dbase.FieldNumberFromName("TuoteTunnus"),&blank );
		if (tempid==pid)
			{
			loadFromDb(dbase);
			return 0;
			}
		dbase.MoveNext();
		}		
	return 1;
	}

string DbProduct::toString()
	{
	string ret;
	ret+="Tuotenimi: ";
	ret+=name;
	ret+="\r\n";
	ret+="TuoteTunnus: ";
	ret+=id;
	ret+="\r\n";
	ret+="MyyntiTiliNro: ";
	ret+=acAccountNumber;
	ret+="\r\n";
	ret+="Yksikko: ";
	ret+=unit;
	ret+="\r\n";
	ret+="AHinta: ";
	ret+=st(unitprice);
	ret+="\r\n";
	ret+="ALVKanta: ";
	ret+=vatType;
	ret+="\r\n";
	ret+="Verollisuuskoodi: ";
	ret+=st(taxCode);
	ret+="\r\n";
	ret+="AlvProsentti: ";
	ret+=st(taxpercent);
	ret+="\r\n";
	ret+="Käänteinen verovelvollisuus: ";
	ret+=st(reversedVat);
	return ret;
	}
