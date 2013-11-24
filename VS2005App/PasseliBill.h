// PasseliBill.h: interface for the PasseliBill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSELIBILL_H__2ACD6861_76C1_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_PASSELIBILL_H__2ACD6861_76C1_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include <vector>

using namespace std;
#include "PasseliLine.h"
#include "PasseliFloat.h"


class PasseliBill  
{

private:

vector<PasseliLine> linevec;

PasseliFloat tempfloat;

struct billdata
{
char something;							//57
unsigned short createdDate;				//setCreatedDate()
unsigned int billNumber;				//setBillNumber()
char something2;
unsigned short dueDate;					//setDueDate()
unsigned int billCustomerNumber;		//setCustomerNumber()
unsigned int deliveryCustomerNumber;	//setCustomerNumber()
char currencyindex;						//setCurrencyIndex()
char currencyLength;					//setCurrencyName()
char currency[4];						//setCurrencyName()
unsigned short currencyinmarksexponent;	//setCurrencyValue()	
unsigned int currencyinmarksmantissa;	//setCurrencyValue()
unsigned short billsumexponent;			//setBillSum()
unsigned int billsummantissa;			//setBillSum()
char something4[9];						//-
unsigned short salesmannumber;			//setSalesmanNumber()
char billCustomerNameLength;			//setCustomerName()
char billCustomerName[32];				//setCustomerName()
char billCustomerName2Length;			//setCustomerName2()
char billCustomerName2[32];				//setCustomerName2()
char billCustomerAddressLength;			//setCustomerAddress()
char billCustomerAddress[32];			//setCustomerAddress()
char billCustomerZipLength;				//setCustomerZip()
char billCustomerZip[32];				//setCustomerZip()
char billCustomerCountryLength;			//setCustomerCountry()
char billCustomerCountry[32];			//setCustomerCountry()
char deliveryCustomerNameLength;		//setCustomerName()	
char deliveryCustomerName[32];			//setCustomerName()
char deliveryCustomerName2Length;		//setCustomerName2()	
char deliveryCustomerName2[32];			//setCustomerName2()
char deliveryCustomerAddressLength;		//setCustomerAddress()
char deliveryCustomerAddress[32];		//setCustomerAddress()	
char deliveryCustomerZipLength;			//setCustomerZip()
char deliveryCustomerZip[32];			//setCustomerZip()
char deliveryCustomerCountryLength;		//setCustomerCountry()
char deliveryCustomerCountry[32];		//setCustomerCountry()
char billCustomerPhoneLength;			//setCustomerPhone()
char billCustomerPhone[32];				//setCustomerPhone()
char deliveryCustomerPhoneLength;		//setCustomerPhone()
char deliveryCustomerPhone[32];			//setCustomerPhone()
char salesmanLength;					//setSalesman()
char salesman[32];						//setSalesman()
char noticeTimeLength;					//-
char noticeTime[16];					//-
char deliveryTimeLength;				//-
char deliveryTime[32];					//-
char deliveryMethodLength;				//-
char deliveryMethod[32];				//-
char yourReferenceLength;				//setYourReference()
char yourReference[32];					//setYourReference()
char ourReferenceLength;				//setOurReference()	
char ourReference[32];					//setOurReference()
char payingConditionLength;				//setPayingCondition()
char payingCondition[32];				//setPayingCondition()
unsigned short payingConditionCode;		//setPayingConditionCode()
unsigned short payingConditionDate;		//setPayingConditionDate()
unsigned short payingConditionDays;		//setPayingConditionDiscountedDays()	
unsigned short payingConditionPercent;	//setPayingConditionDiscountPercent()
unsigned short payingConditionAlternateDays;	//setPayingConditionNettoDays()
char sheetLength;						//setSheet()
char sheet[32];							//setSheet()
unsigned short delayIntrest;			//setDelayIntrest()
char something5[8];						//-
unsigned char orderNumberLength;		//setOrderNumber()
char ordernumber[32];					//setOrderNumber()
char something6[10];					//-
unsigned short salesmanprovisionexponent;	//setSalesmanProvision()
unsigned int salesmanprovisionmantissa;		//setSalesmanProvision()	
char something7[8];						//-
unsigned short billrowcount;			//addBillRow()
unsigned char isafterdeliverycolumn;	//-
unsigned char isdiscountcolumn;			//-
unsigned char isvatpercentcolumn;		//-
unsigned char isacaccountcolumn;		//-
unsigned char zero;						//-
unsigned short daccountnumber;			//setDAccountNumber
unsigned short totalweightexponent;		//setTotalWeight()
unsigned int totalweightmantissa;		//setTotalWeight()
unsigned char pricegroupindex;			//setPriceGroupIndex()
unsigned char isbruttowritedown;		//setBruttoWritedown()
unsigned char numberoftaxlessrows;		//setNumberOfTaxlessRows
unsigned char zeero;					//-
unsigned short taxlesspriceexponent;	//setTaxlessPrice()
unsigned int taxlesspricemantissa;		//setTaxlessPrice()
unsigned short vatexponent;				//setVat()
unsigned int vatmantissa;				//setVat()
unsigned short taxedpriceexponent;		//setTaxedPrice()
unsigned int taxedpricemantissa;		//setTaxedPrice()	
unsigned short totalunitsexponent;		//setTotalUnits()
unsigned int totalunitsmantissa;		//setTotalUnits()
char currencyindex2;						//setCurrencyIndex()
unsigned short currenryinmarks2exponent;	//setCurrencyValue()
unsigned int currencyinmarks2mantissa;		//setCurrencyValue()
char something8[100];					//-

unsigned short vatpercent2exponent;	//setVatPercent2() 
unsigned int vatpercent2mantissa;	//setVatPercent2()
unsigned short taxlessprice2exponent; //setTaxlessPrice()
unsigned int taxlessprice2mantissa;	//setTaxlessPrice()	
unsigned short vatsumexponent;		//setVatSum()
unsigned int vatsummantissa;		//setVatSum()
char something9[144];				//-
} data;




string noticetext;



public:
	PasseliBill();
	virtual ~PasseliBill();
	void writeToFile(const string& dbdir);
	void setBillNumber(unsigned int number);
	void setCreatedDate(unsigned short date);
	void setDueDate(unsigned short date);

	void setCustomerNumber(int customernumber);	
	
	void setCurrencyName(const string& name);
	void setCurrencyValue(double value);
	void setBillSum(double sum);
	void setSalesmanNumber(unsigned short number);
	void setCustomerName(const string& name);
	void setCustormerName2(const string& name);
	void setCustomerAddress(const string& address);	
	void setCustomerZip(const string& zip);
	void setCustomerCountry(const string& country);
	void setSalesman(const string& salesman);
	void setYourReference(const string& reference);
	void setOurReference(const string& reference);
	void setPayingCondition(const string& condition);
	void setPayingConditionCode(unsigned short code);

	void setPayingConditionDiscountedDays(unsigned short days);
	void setPayingConditionDiscountPercent(unsigned short percent);
	void setPayingConditionNettoDays(unsigned short days);

	void setSheet(const string& sheet);
	void setDelayIntrest(unsigned short intrest);
	void setOrderNumber(const string& ordernumber);
	void addBillLine(const PasseliLine& row);
	void setDAccountNumber(unsigned short number);
	void setPriceGroupIndex(unsigned char index);
	void setBruttoWritedown(unsigned char val);
	void setNumberOfTaxlessRows(unsigned char num);
	void setTaxlessPrice(double price);
	void setVat(double vat);
	void setTotalUnits(double units);
	void setCurrencyIndex(unsigned char index);
	void setVatPercent2(double percent);
	void setVatSum(double vatsum);
	void setTotalWeight(double weight);
	void setPayingConditionDate(unsigned short date);
};

#endif // !defined(AFX_PASSELIBILL_H__2ACD6861_76C1_11D8_80E8_0010A4DF8E4B__INCLUDED_)
