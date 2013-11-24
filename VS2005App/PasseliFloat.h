// PasseliFloat.h: interface for the PasseliFloat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSELIFLOAT_H__46420001_7663_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_PASSELIFLOAT_H__46420001_7663_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;

class PasseliFloat  
{
private:
	double value;
public:
	PasseliFloat();
	virtual ~PasseliFloat();
	void setValue(double v);
	void setValue(char* data);
	string toString();
	double getValue();
	void writeData(char* target);
};

#endif // !defined(AFX_PASSELIFLOAT_H__46420001_7663_11D8_80E8_0010A4DF8E4B__INCLUDED_)
