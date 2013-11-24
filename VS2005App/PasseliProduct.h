// PasseliProduct.h: interface for the PasseliProduct class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSELIPRODUCT_H__46420002_7663_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_PASSELIPRODUCT_H__46420002_7663_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <string>
#include "PasseliFloat.h"
using namespace std;

class PasseliProduct  
{
private:

//nimiketiedosto

unsigned short productgroup;
string productname;		
PasseliFloat taxlessunitprice;
unsigned short storagecurrencyindex;
unsigned short  vatindex;
string unitname;
PasseliFloat storagesaldo;
PasseliFloat inproductionsaldo;
PasseliFloat allocatedsaldo;
unsigned short acaccount;

//muutieto-tiedosto

unsigned char useAmountDiscount;
PasseliFloat salesmanProvisionPercent;
PasseliFloat bprice;
PasseliFloat cprice;
PasseliFloat dprice;
PasseliFloat amountdiscountaprice; 
PasseliFloat amountdiscountbprice; 
PasseliFloat amountdiscountcprice; 
PasseliFloat amountdiscountdprice; 
PasseliFloat alertlimit; 
PasseliFloat weight; 
string shelfcode;

/*
ushort storageamountexponent1;
uint storageamountmantissa1;
DOSDATE storaageamountdate1;
ushort storageamountexponent2;
uint storageamountmantissa2;
DOSDATE storaageamountdate2;
ushort storageamountexponent3;
uint storageamountmantissa3;
DOSDATE storaageamountdate3;
ushort storageamountexponent4;
uint storageamountmantissa4;
DOSDATE storaageamountdate4;
ushort storageamountexponent5;
uint storageamountmantissa5;
DOSDATE storaageamountdate5;
ushort storageamountexponent6;
uint storageamountmantissa6;
DOSDATE storaageamountdate6;
ushort storageamountexponent7;
uint storageamountmantissa7;
DOSDATE storaageamountdate7;
ushort storageamountexponent8;
uint storageamountmantissa8;
DOSDATE storaageamountdate8;
ushort storageamountexponent9;
uint storageamountmantissa9;
DOSDATE storaageamountdate9;
*/
unsigned int suppliernumber;
//string productname;
//string unitname;
PasseliFloat deliveryunits;
PasseliFloat orderedamount;

//ushort someexponent;
//uint somemantissa;


unsigned short orderdate;


public:
	PasseliProduct();
	virtual ~PasseliProduct();

	
	unsigned short getProductGroup();
	string getProductName();		
	double getTaxlessUnitPrice();
	unsigned short getStorageCurrencyIndex();
	unsigned short getVatIndex();
	string getUnitName();
	double getStorageSaldo();
	double getInProductionSaldo();
	double getAllocatedSaldo();
	unsigned short getAcAccount();

//muutieto-tiedosto

    unsigned char isUseAmountDiscount();
	double  getSalesmanProvisionPercent();
	double	getBPrice();
	double  getCPrice();
	double  getDPrice();
	double  getAmountDiscountAPrice(); 
	double  getAmountDiscountBPrice(); 
	double  getAmountDiscountCPrice(); 
	double  getAmountDiscountDPrice(); 
	double  getAlertLimit(); 
	double  getWeight(); 
	string getShelfcode();
	unsigned int getSupplierNumber();

	double getDeliveryUnits();
	double getOrderedAmount();
	unsigned short getOrderDate();

	int findAndLoadFromFile(const string& dbdir, const string&  pid);
	string toString();
};

#endif // !defined(AFX_PASSELIPRODUCT_H__46420002_7663_11D8_80E8_0010A4DF8E4B__INCLUDED_)
