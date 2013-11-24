// DbProduct.h: interface for the DbProduct class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_DBPRODUCT_H__39B14AE1_58A8_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_DBPRODUCT_H__39B14AE1_58A8_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "defines.h"
#include "BdeDatabase.h"
#include <string>
#include <vector>
using namespace std;


class DbProduct  
{
private:
BOOL blank;
int group;
string name;
string id;
string acAccountNumber;
string unit;
string vatType;
int taxCode;
int reversedVat;
double unitprice;
double taxpercent;

public:
	DbProduct();
	DbProduct(const string& _name, const string& _code, const string& _unit, double _unitprice, double _taxpercent);

	virtual ~DbProduct();
	
	void setName(const string& _name);
	string getName();
	
	void setGroup(const int _group);
	int getGroup();

	void setVatType(const string& _type);
	string getVatType();

	void setId(const string& _code);
	string getId();
	
	void setAcAccountNumber(const string& _number);
	string getAcAccountNumber();

	void setUnit(const string& _unit);
	string getUnit();

	void setUnitPrice(double _price);
	double getUnitPrice();
	
	void setTaxPercent(double _percent);
	double getTaxPercent();

	void setTaxCode(int _code);
	int getTaxCode();

	void setRevesedVat(int _code);
	int getRevesedVat();

	void setVatVect(Alv *pAlv);		// 13.8.2010, J.V.
	Alv *pAlv;

	void loadFromDb(CBdeDatabase& dbase);
	
	int findAndLoadFromDb(const string& pid, CBdeDatabase& dbase);
	
	string toString();

};

#endif // !defined(AFX_DBPRODUCT_H__39B14AE1_58A8_11D8_80E8_0010A4DF8E4B__INCLUDED_)
