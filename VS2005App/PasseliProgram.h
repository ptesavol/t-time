// PasseliProgram.h: interface for the PasseliProgram class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSELIPROGRAM_H__4579D8E1_7290_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_PASSELIPROGRAM_H__4579D8E1_7290_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AccountingProgram.h"

class PasseliProgram : public AccountingProgram  
{
private:
	string dbdir;
public:
	PasseliProgram();
	virtual ~PasseliProgram();

	virtual void open(const string& databasedir);
	virtual void close();
	
	// returns accounts as a list of pairs of accountname, accountnumber 
	virtual vector<pair<string,string> > getBankAccounts();
    virtual vector<string> getProductGroups();
    virtual vector<string> getProducts(BOOL bVatGroup);
    virtual vector<string> getCustomerGroups();
    virtual vector<string> getCustomers();
    virtual vector<string> getVatPercents();
	virtual BOOL isVatGroup();		// 13.8.2010, J.V.
	
	virtual int createBill(const string& customerid,
							vector<PriceComponent>&, const string& bankaccount,
							const COleDateTime& duedate, const string& ourReference,
							const string& yourReference, const string& pricesFrom);

    BOOL checkFloat(double d);
};

#endif // !defined(AFX_PASSELIPROGRAM_H__4579D8E1_7290_11D8_80E8_0010A4DF8E4B__INCLUDED_)
