// PasseliPayingCondition.h: interface for the PasseliPayingCondition class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSELIPAYINGCONDITION_H__3DAE7362_7758_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_PASSELIPAYINGCONDITION_H__3DAE7362_7758_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;

class PasseliPayingCondition  
{
private:

unsigned short code;
unsigned short discounteddays;
unsigned short discountpercent;
unsigned short nettodays;
string explanation;

public:
	PasseliPayingCondition();
	virtual ~PasseliPayingCondition();
	
	unsigned short getCode();
	unsigned short getDiscountedDays();
	unsigned short getDiscountPercent();
	unsigned short getNettoDays();
	string getExplanation();
	int findAndLoadFromFile(const string& dbdir, unsigned short code);
	string toString();
};

#endif // !defined(AFX_PASSELIPAYINGCONDITION_H__3DAE7362_7758_11D8_80E8_0010A4DF8E4B__INCLUDED_)
