// PasseliTax.h: interface for the PasseliTax class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSELITAX_H__D0483201_80C3_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_PASSELITAX_H__D0483201_80C3_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PasseliFloat.h"
#include <string>

using namespace std;

class PasseliTax  
{
private:


PasseliFloat percent;
string description;
 

public:
	PasseliTax();
	virtual ~PasseliTax();
	double getPercent();
	string getDescription();
	int findAndLoadFromFile(const string& dbdir, unsigned short id);

};

#endif // !defined(AFX_PASSELITAX_H__D0483201_80C3_11D8_80E8_0010A4DF8E4B__INCLUDED_)
