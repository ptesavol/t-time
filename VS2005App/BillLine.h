// BillLine.h: interface for the BillLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BILLLINE_H__39B14AE2_58A8_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_BILLLINE_H__39B14AE2_58A8_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "BdeDatabase.h"

using namespace std;

class BillLine  
{
private:
	BOOL blank;

	int billNumber;
	int lineNumber;
	int lineType;
	string accountCode;
	string productId;
	string productName;
	double amount;
	string unit;
	double unitPrice;
	int taxCode;
	double discountPercent;
	double taxlessPrice;
	double taxedPrice;
	string vatAccount;
	double vatPrice;
	string vatPercent;
	int balanceType;
	int targetNumber;
	int happeningType;
	int reversedVat;
	string ac;
	COleDateTime deliveryDate;

public:
	BillLine();
	BillLine(const BillLine& b);
	BillLine& operator= (const BillLine& b);

	virtual ~BillLine();


	int getBillNumber();
	int getLineNumber();
	int getLineType();
	string getAccountCode();
	string getProductId();
	string getProductName();
	double getAmount();
	string getUnit();
	double getUnitPrice();
	int getTaxCode();
	int getRevesedVat();
	double getDiscountPercent();
	double getTaxlessPrice();
	double getTaxedPrice();
	string getVatAccount();
	double getVatPrice();
	string getVatPercent();
	int getBalanceType();
	int getTargetNumber();
	int getHappeningType();
	string getAc();
	COleDateTime getDeliveryDate();

	void setBillNumber(int _number);
	void setLineNumber(int _number);
	void setLineType(int _type);
	void setAccountCode(const string& _code);
	void setProductId(const string& _id);
	void setProductName(const string& _name);
	void setAmount(double _amount);
	void setUnit(const string& _unit);
	void setUnitPrice(double _price);
	void setTaxCode(int _code);
	void setRevesedVat(int _mode);
	void setDiscountPercent(double _percent);
	void setTaxlessPrice(double _price);
	void setTaxedPrice(double _price);
	void setVatAccount(const string& _account);
	void setVatPrice(double _price);
	void setVatPercent(const string& _percent);
	void setBalanceType(int _type);
	void setTargetNumber(int _number);
	void setHappeningType(int _type);
	void setAc(const string& _ac);
	void setDeliveryDate(const COleDateTime& _date);

	void saveToDb(CBdeDatabase& dbase);
	void loadFromDb(CBdeDatabase& dbase);
	string toString();
};

#endif // !defined(AFX_BILLLINE_H__39B14AE2_58A8_11D8_80E8_0010A4DF8E4B__INCLUDED_)
