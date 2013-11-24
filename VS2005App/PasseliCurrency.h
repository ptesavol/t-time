// PasseliCurrency.h: interface for the PasseliCurrency class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSELICURRENCY_H__663D9B21_771D_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_PASSELICURRENCY_H__663D9B21_771D_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "PasseliFloat.h"
using namespace std;

class PasseliCurrency  
{
private:
string currencyName;
PasseliFloat currencyvalue;
PasseliFloat currencyvalueineuros;
string location;
unsigned short valuedate;

public:
	PasseliCurrency();
	virtual ~PasseliCurrency();
	
	string getName();
	double getValue();
	double getValueInEuros();	
	string getLocation();
	unsigned short getValueDate();
	int findAndLoadFromFile(const string& dbdir, unsigned int index);	
	string toString();
};

#endif // !defined(AFX_PASSELICURRENCY_H__663D9B21_771D_11D8_80E8_0010A4DF8E4B__INCLUDED_)
