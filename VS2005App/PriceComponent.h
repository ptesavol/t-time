// PriceComponent.h: interface for the PriceComponent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRICECOMPONENT_H__9AD61E81_D004_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_PRICECOMPONENT_H__9AD61E81_D004_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

using namespace std;

class PriceComponent  
{
private:

	string productId;
    string worktypeId;          // 22.12.2008, J.V.
	double amount;
	double unitPrice;
	double totalPrice;
	double vatPercent;
	bool priceSet;
	string unit;
	int startDate;			// 13.8.2010, J.V.
	int startTime;
	int endDate;
	int endTime;

public:
	PriceComponent();
	virtual ~PriceComponent();

	void setProductId(const string& id);
	void setWorktypeId(const string& id);  // 22.12.2008, J.V.
	void setAmount(double amount);

	void setUnitPrice(double price);
	void setTotalPrice(double price);
	void setVatPercent(double percent);
	void setUnit(const string&  unit);
	void setDateTime(CString startDate, CString startTime, CString endDate, CString endTime);	// 13.8.2010, J.V.
	int getStartDate();
    void clear();

	string getProductId();
    string getWorktypeId(); // 22.12.2008, J.V.
	double getAmount();
	double getUnitPrice();
	double getTotalPrice();
	double getVatPercent();
	string getUnit();

	bool isPriced();
	
};

#endif // !defined(AFX_PRICECOMPONENT_H__9AD61E81_D004_11D8_80E8_0010A4DF8E4B__INCLUDED_)
