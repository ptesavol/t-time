// PasseliLine.cpp: implementation of the PasseliLine class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "BdeInserter.h"
#include "PasseliLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PasseliLine::PasseliLine()
	{
	//clear the structure
	char* cpointer=reinterpret_cast<char*>(&data);

	for (int i=0; i<sizeof(data); i++)
		*cpointer=0;
	}

PasseliLine::~PasseliLine()
	{

	}


void PasseliLine::setTaxlessRowPrice(double price)
	{
	this->tempfloat.setValue(price);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.taxlessrowpriceexponent));
	}

void PasseliLine::setUnitVatIndex(unsigned char index)
	{
	data.unitvatindex=index;
	}

void PasseliLine::setUnitVatPercent(double percent)
	{
	this->tempfloat.setValue(percent);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.unitvatpercentexponent));
	}

void PasseliLine::setSalesAccountNumber(unsigned short number)
	{
	data.salesaccountnumber=number;
	}

void PasseliLine::setRunningNumber(unsigned int number)
	{
	data.runningnumber=number;
	}

void PasseliLine::setProductGroup(unsigned short group)
	{
	data.productgroup=group;
	}

void PasseliLine::setShelfCode(const string& code)
	{
	data.shelfcodelength=code.length();
	for(int i=0; i<code.length(); i++)
		data.shelfcode[i]=code[i];
	}

void PasseliLine::setProductName(const string& name)
	{
	data.productnamelength=name.length();
	for(int i=0; i<name.length(); i++)
		data.productname[i]=name[i];
	}

void PasseliLine::setOrderedAmount(double amount)
	{
	this->tempfloat.setValue(amount);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.orderedamountexponent));
	}

void PasseliLine::setUnitName(const string& name)
	{
	data.unitnamelength=name.length();
	for(int i=0; i<name.length(); i++)
		data.unitname[i]=name[i];
	}

void PasseliLine::setDiscountPercent(double percent)
	{
	this->tempfloat.setValue(percent);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.discountpercentexponent));
	}

void PasseliLine::setProvision(double provision)
	{
	this->tempfloat.setValue(provision);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.provisionexponent));
	}

void PasseliLine::setAveragePrice(double price)
	{
	this->tempfloat.setValue(price);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.averagepriceexponent));
	}

void PasseliLine::useAmountDiscount(unsigned char d)
	{
	data.useamountdiscount=d;
	}

void PasseliLine::setUnitWeight(double weight)
	{
	this->tempfloat.setValue(weight);
	this->tempfloat.writeData(reinterpret_cast<char*>(&data.unitweigthexponent));
	}

char* PasseliLine::getData()
	{
	return reinterpret_cast<char*>(&data);
	}

unsigned int PasseliLine::getDataSize()
	{
	return sizeof(data);	
	}