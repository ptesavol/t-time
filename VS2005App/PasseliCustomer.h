// PasseliCustomer.h: interface for the PasseliCustomer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSELICUSTOMER_H__4579D8E2_7290_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_PASSELICUSTOMER_H__4579D8E2_7290_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "PasseliFloat.h"

using namespace std;

class PasseliCustomer  
{
private: 

	unsigned int id;
	string name1;
	string name2;
	string address;
	string zipaddress;
	string country;
	
	string vatid;
	string phonenumber;
	string faxnumber;
	string defaultreference;
	string defaultform;
	unsigned short lastcontactdate1;
	unsigned short nextcontactdate1;
	string contactperson1;
	string contactphone1;
	unsigned short lastcontactdate2;
	unsigned short nextcontactdate2;
	string contactperson2;
	string contactphone2;
	unsigned short lastcontactdate3;
	unsigned short nextcontactdate3;
	string contactperson3;
	string contactphone3;
	
	unsigned char payingconditionindex;
	unsigned char pricegroupindex;
	unsigned char deliverymethodindex;
	unsigned char isnoticebills;
	unsigned char isintrestbills;

	unsigned short salesman;
	unsigned short billingid;

	unsigned char currencyindex;
	PasseliFloat creditlimit;
	PasseliFloat creditsaldo;
	
	unsigned char domesticindex;
	
public:
	PasseliCustomer();
	virtual ~PasseliCustomer();

	unsigned int getId();
	string getName1();
	string getName2();
	string getAddress();
	string getZipAddress();
	string getCountry();

	string getVatId();
	string getPhoneNumber();
	string getFaxNumber();
	string getDefaultReference();
	string getDefaultForm();
	unsigned short getLastContactDate1();
	unsigned short getNextContactDate1();
	string getContactPerson1();
	string getContactPhone1();
	unsigned short getLastContactDate2();
	unsigned short getNextContactDate2();
	string getContactPerson2();
	string getContactPhone2();
	unsigned short getLastContactDate3();
	unsigned short getNextContactDate3();
	string getContactPerson3();
	string getContactPhone3();
	unsigned char getPayingConditionIndex();
	unsigned char getPriceGroupIndex();
	unsigned char getDeliveryMethodIndex();
	unsigned char getIsNoticeBills();
	unsigned char getIsIntrestBills();
	unsigned short getSalesman();
	unsigned short getBillingId();
	unsigned char getCurrencyIndex();
	double getCreditLimit();
	double getCreditSaldo();
	unsigned char getDomesticIndex();


	int findAndLoadFromFile(const string& dbdir, unsigned int id);
	
	string toString();
};

#endif // !defined(AFX_PASSELICUSTOMER_H__4579D8E2_7290_11D8_80E8_0010A4DF8E4B__INCLUDED_)
