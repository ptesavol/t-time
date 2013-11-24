// DbCustomer.h: interface for the DbCustomer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBCUSTOMER_H__6509C8A4_5D4B_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_DBCUSTOMER_H__6509C8A4_5D4B_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "BdeDatabase.h"

using namespace std;


class DbCustomer  
{
private:

BOOL blank;
int group;
int cId;
string cName;
string cName2;
string cAddress;
string cZipCode;
string cZipName;
string cCountry;
string cContactPerson;
double discount;
string payingcondition;
string customernumber;

public:
	DbCustomer();
	virtual ~DbCustomer();
	
	void setGroup(int _group);
	int getGroup();
	int getCId();
	string getCName();
	string getCName2();
	string getCAddress();
	string getCZipCode();
	string getCZipName();
	string getCCountry();
	string getCContactPerson();
	double getDiscount();
	string getPayingCondition();
	string getCustomerNumber();

	void setCId(int _id);
	void setCName(const string& _name);
	void setCName2(const string& _name);
	void setCAddress(const string& _address);
	void setCZipCode(const string& _code);
	void setCZipName(const string& _name);
	void setCCountry(const string& _country);
	void setCContactPerson(const string& _person);
	void setDiscount(double _discount);
	void setPayingCondition(const string& _condition);
	void setCustomerNumber(const string& _number);

	void loadFromDb(CBdeDatabase& dbase);
	int findAndLoadFromDb(int id, CBdeDatabase& dbase);
	string toString();	
};

#endif // !defined(AFX_DBCUSTOMER_H__6509C8A4_5D4B_11D8_80E8_0010A4DF8E4B__INCLUDED_)
