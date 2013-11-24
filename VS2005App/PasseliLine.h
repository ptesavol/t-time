// PasseliLine.h: interface for the PasseliLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSELILINE_H__2ACD6862_76C1_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_PASSELILINE_H__2ACD6862_76C1_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PasseliFloat.h"
#include <string>
using namespace std;

class PasseliLine  
{
private:

PasseliFloat tempfloat;

struct productline	
{
unsigned short taxlessrowpriceexponent;	//setTaxlessRowPrice()
unsigned int taxlessrowpricemantissa;	//setTaxlessRowPrice()
unsigned char unitvatindex;				//setUnitVatIndex()
unsigned short unitvatpercentexponent;	//setUnitVatPercecnt()
unsigned int unitvatpercentmantissa;	//setUnitVatPercent()
unsigned short salesaccountnumber;		//setSalesAccountNumber()
unsigned int unknownlong;				//-
unsigned int runningnumber;				//setRunningNumber()
unsigned short productgroup;			//setProductGroup()
unsigned char shelfcodelength;			//setShelfCode()
char shelfcode[10];						//setShelfCode()
unsigned char productnamelength;		//setProductName()
char productname[51];					//setProductName()
unsigned short orderedamountexponent;	//setOrderedAmount()
unsigned int orderedamountmantissa;		//setOrderedAmount()
unsigned short deliveredamountexponent;	//setOrderedAmount()
unsigned int deliveredamountmantissa;	//setOrderedAmount()
unsigned short missingamountexponent;	//-
unsigned int missingamountmantissa;		//-
unsigned char unitnamelength;			//setUnitName()
char unitname[3];						//setUnitName()
unsigned char unitsomething;			//-
unsigned short taxlessunitpriceexponent;	//setTaxlessUnitPrice()	
unsigned int taxlessunitpricemantissa;		//setTaxlessUnitPrice()	
unsigned short discountpercentexponent;		//setDiscountPercent()
unsigned int discountpercentmantissa;		//setDiscountPercent()
unsigned short provisionexponent;			//setProvision()
unsigned int provision;						//setProvision()
unsigned short averagepriceexponent;		//setAveragePrice()
unsigned int averagepricemantissa;			//setAveragePrice()
unsigned int unknown3;						//-
unsigned char useamountdiscount;			//useAmountDiscount()
unsigned short unitweigthexponent;			//setUnitWeight()
unsigned int unitweigthmantissa;			//setUnitWeight()
} data;


public:
	PasseliLine();
	virtual ~PasseliLine();

	void setTaxlessRowPrice(double price);
	void setUnitVatIndex(unsigned char index);
	void setUnitVatPercent(double percent);
	void setSalesAccountNumber(unsigned short number);
	void setRunningNumber(unsigned int number);
	void setProductGroup(unsigned short group);
	void setShelfCode(const string& code);
	void setProductName(const string& name);
	void setOrderedAmount(double amount);
	void setUnitName(const string& name);
	void setDiscountPercent(double percent);
	void setProvision(double provision);
	void setAveragePrice(double price);
	void useAmountDiscount(unsigned char d);
	void setUnitWeight(double weight);
	char* getData();
	unsigned int getDataSize();
};

#endif // !defined(AFX_PASSELILINE_H__2ACD6862_76C1_11D8_80E8_0010A4DF8E4B__INCLUDED_)
