// PriceComponent.cpp: implementation of the PriceComponent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PriceComponent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PriceComponent::PriceComponent()
{
this->priceSet=false;
this->amount=0;
this->productId="";
this->totalPrice=0;
this->unit="";
this->unitPrice=0;
this->vatPercent=0;
}

PriceComponent::~PriceComponent()
{
}

void PriceComponent::clear()
	{
	this->priceSet = false;
	this->amount=0;
	this->productId="";
	this->totalPrice=0;
	this->unit="";
	this->unitPrice=0;
	this->vatPercent=0;
	}

void PriceComponent::setProductId(const string& id)
	{
	this->productId=id;
	}

void PriceComponent::setWorktypeId(const string& id)  // 22.12.2008, J.V.
	{
	this->worktypeId=id;
	}

void PriceComponent::setAmount(double amount)
	{
	this->amount=amount;
	}

void PriceComponent::setUnitPrice(double price)
	{
	this->unitPrice=price;
	this->priceSet=true;
	}

void PriceComponent::setTotalPrice(double price)
	{
	this->totalPrice=price;
	}

void PriceComponent::setVatPercent(double percent)
	{
	this->vatPercent=percent;
	}

void PriceComponent::setUnit(const string& u)
	{
	this->unit=u;
	}

string PriceComponent::getProductId()
	{
	return this->productId;
	}

string PriceComponent::getWorktypeId()  // 22.12.2008, J.V.
	{
	return this->worktypeId;
	}

double PriceComponent::getAmount()
	{
	return this->amount;
	}

double PriceComponent::getUnitPrice()
	{
	return this->unitPrice;
	}

double PriceComponent::getTotalPrice()
	{
	return this->totalPrice;
	}

double PriceComponent::getVatPercent()
	{
	return this->vatPercent;
	}

string PriceComponent::getUnit()
	{
	return this->unit;
	}

bool PriceComponent::isPriced()
	{
	return this->priceSet;
	}

void PriceComponent::setDateTime(CString startDate, CString startTime, CString endDate, CString endTime)	// 13.8.2010, J.V.
	{
	this->startDate = atoi(startDate);
	this->startTime = atoi(startTime);
	this->endDate = atoi(endDate);
	this->endTime = atoi(endTime);
	}

int PriceComponent::getStartDate()	// 14.8.2010, J.V.
	{
	return this->startDate;
	}