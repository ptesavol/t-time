// PasseliBill.cpp: implementation of the PasseliBill class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BdeInserter.h"
#include "PasseliBill.h"
#include "stringhelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PasseliBill::PasseliBill()
	{
	char* cpointer=reinterpret_cast<char*>(&data);

	for (int i=0; i<sizeof(data); i++)
		*cpointer=0;
	}

PasseliBill::~PasseliBill()
{

}

void PasseliBill::setCustomerNumber(int customernumber)
	{
	data.billCustomerNumber=customernumber;
	data.deliveryCustomerNumber=customernumber;
	}
	
void PasseliBill::setCurrencyIndex(unsigned char index)
	{
	data.currencyindex=index;
	data.currencyindex2=index;
	}

void PasseliBill::setCurrencyValue(double value)
	{
	this->tempfloat.setValue(value);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.currencyinmarksexponent));
	}

void PasseliBill::setCurrencyName(const string& name)
	{
	data.currencyLength=name.length();
	for(int i=0; i<name.length(); i++)
		data.currency[i]=name[i];
	}	

void PasseliBill::setBillSum(double sum)
	{
	this->tempfloat.setValue(sum);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.billsumexponent));
	}	

void PasseliBill::setSalesmanNumber(unsigned short number)
	{
	data.salesmannumber=number;
	}	

void PasseliBill::setCustomerName(const string& name)
	{
	data.billCustomerNameLength=name.length();
	for(int i=0; i<name.length(); i++)
		data.billCustomerName[i]=name[i];
	
	data.deliveryCustomerNameLength=name.length();
	for(int j=0; j<name.length(); j++)
		data.deliveryCustomerName[j]=name[j];
	}	

void PasseliBill::setCustormerName2(const string& name)
	{
	data.billCustomerName2Length=name.length();
	for(int i=0; i<name.length(); i++)
		data.billCustomerName2[i]=name[i];
	
	data.deliveryCustomerName2Length=name.length();
	for(int j=0; j<name.length(); j++)
		data.deliveryCustomerName2[j]=name[j];
	}	

void PasseliBill::setCustomerAddress(const string& address)
	{
	data.billCustomerAddressLength=address.length();
	for(int i=0; i<address.length(); i++)
		data.billCustomerAddress[i]=address[i];
	
	data.deliveryCustomerAddressLength=address.length();
	for(int j=0; j<address.length(); j++)
		data.deliveryCustomerAddress[j]=address[j];
	}
	
void PasseliBill::setCustomerZip(const string& zip)
	{
	data.billCustomerZipLength=zip.length();
	for(int i=0; i<zip.length(); i++)
		data.billCustomerZip[i]=zip[i];
	
	data.deliveryCustomerZipLength=zip.length();
	for(int j=0; j<zip.length(); j++)
		data.deliveryCustomerZip[j]=zip[j];
	}	

void PasseliBill::setCustomerCountry(const string& country)
	{
	data.billCustomerCountryLength=country.length();
	for(int i=0; i<country.length(); i++)
		data.billCustomerCountry[i]=country[i];
	
	data.deliveryCustomerCountryLength=country.length();
	for(int j=0; j<country.length(); j++)
		data.deliveryCustomerCountry[j]=country[j];
	}	

void PasseliBill::setSalesman(const string& salesman)
	{
	data.salesmanLength=salesman.length();
	for(int i=0; i<salesman.length(); i++)
		data.salesman[i]=salesman[i];
	}
	
void PasseliBill::setYourReference(const string& reference)
	{
	data.yourReferenceLength=reference.length();
	for(int i=0; i<reference.length(); i++)
		data.yourReference[i]=reference[i];
	}	

void PasseliBill::setOurReference(const string& reference)
	{
	data.ourReferenceLength=reference.length();
	for(int i=0; i<reference.length(); i++)
		data.ourReference[i]=reference[i];
	}	

void PasseliBill::setPayingCondition(const string& condition)
	{
	data.payingConditionLength=condition.length();
	for(int i=0; i<condition.length(); i++)
		data.payingCondition[i]=condition[i];
	}	

void PasseliBill::setPayingConditionCode(unsigned short code)
	{
	data.payingConditionCode=code;
	}	

void PasseliBill::setPayingConditionDiscountedDays(unsigned short days)
	{
	data.payingConditionDays=days;
	}
void PasseliBill::setPayingConditionDiscountPercent(unsigned short percent)
	{
	data.payingConditionPercent=percent;
	}
void PasseliBill::setPayingConditionNettoDays(unsigned short days)
	{
	data.payingConditionAlternateDays=days;
	}

void PasseliBill::setSheet(const string& sheet)
	{
	data.sheetLength=sheet.length();
	for(int i=0; i<sheet.length(); i++)
		data.sheet[i]=sheet[i];
	}	

void PasseliBill::setDelayIntrest(unsigned short intrest)
	{
	data.delayIntrest=intrest;
	}

void PasseliBill::setOrderNumber(const string& ordernumber)
	{
	data.orderNumberLength=ordernumber.length();
	for(int i=0; i<ordernumber.length(); i++)
		data.ordernumber[i]=ordernumber[i];
	}	

void PasseliBill::addBillLine(const PasseliLine& row)
	{
	linevec.push_back(row);
	}	

void PasseliBill::setDAccountNumber(unsigned short number)
	{
	data.daccountnumber=number;
	}
	
void PasseliBill::setPriceGroupIndex(unsigned char index)
	{
	data.pricegroupindex=index;
	}	

void PasseliBill::setBruttoWritedown(unsigned char val)
	{
	data.isbruttowritedown=val;
	}	

void PasseliBill::setNumberOfTaxlessRows(unsigned char num)
	{
	data.numberoftaxlessrows=num;
	}	

void PasseliBill::setTaxlessPrice(double price)
	{
	this->tempfloat.setValue(price);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.taxedpriceexponent));
	}	

void PasseliBill::setVat(double vat)
	{
	this->tempfloat.setValue(vat);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.vatexponent));
	}
	
void PasseliBill::setTotalUnits(double units)
	{
	this->tempfloat.setValue(units);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.totalunitsexponent));
	}	



void PasseliBill::setVatPercent2(double percent)
	{
	this->tempfloat.setValue(percent);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.vatpercent2exponent));
	}	

void PasseliBill::setVatSum(double vatsum)
	{
	this->tempfloat.setValue(vatsum);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.vatsumexponent));
	}	

void PasseliBill::setTotalWeight(double weight)
	{
	this->tempfloat.setValue(weight);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.totalweightexponent));
	}

void PasseliBill::setCreatedDate(unsigned short date)
	{
	data.createdDate=date;
	}

void PasseliBill::setDueDate(unsigned short date)
	{
	data.dueDate=date;
	}

void PasseliBill::setPayingConditionDate(unsigned short date)
	{
	data.payingConditionDate=date;
	}

void PasseliBill::writeToFile(const string& dbdir)
	{
	//etsitään suurin laskunumero, ja lisätään siihen 1

	string target=dbdir;
	target+="\\Laskut\\*.ls-";
	int tint=0;
	int biggest=0;
	string temp;

	WIN32_FIND_DATA result;
	HANDLE iter=FindFirstFile(target.c_str(),&result);
	
	if (iter!=INVALID_HANDLE_VALUE)
		{
		temp=result.cFileName;
		temp=temp.substr(0,temp.size()-4);
		temp=temp.substr(temp.rfind("\\")+1);
		tint=atoi(temp.c_str());
		if (tint>biggest)
			biggest=tint;
		}	
	while ((FindNextFile(iter,&result) )!= 0)
		{
		temp=result.cFileName;
		temp=temp.substr(0,temp.size()-4);
		temp=temp.substr(temp.rfind("\\")+1);
		tint=atoi(temp.c_str());
		if (tint>biggest)
			biggest=tint;
		}
	
	FindClose(iter);
	
	//construct filename
	biggest++;

	this->setBillNumber(biggest);
	string billfilename=dbdir;
	billfilename+="\\Laskut\\";
	billfilename+=st(biggest);
	billfilename+=".ls-";
	
	FILE* billfile=fopen(billfilename.c_str(),"w");
	
	fwrite(&data, 1, sizeof(data), billfile);
	
	fflush(billfile);
	fclose(billfile);
	}

void PasseliBill::setBillNumber(unsigned int number)
	{
	data.billNumber=number;
	}
	