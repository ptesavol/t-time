// NeuvosProgram.h: interface for the NeuvosProgram class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEUVOSPROGRAM_H__6509C8A2_5D4B_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_NEUVOSPROGRAM_H__6509C8A2_5D4B_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)
#include "AccountingProgram.h"
#include <string>
#include <vector>
#include <map>
#include "BankAccount.h"
#include "DbCustomer.h"
#include "defines.h"

using namespace std;

class NeuvosProgram : public AccountingProgram  
{
private:

	string dbdir;

public:
	NeuvosProgram();
	virtual ~NeuvosProgram();
	
	virtual void open(const string& databasedir);
	virtual void close();
	
	// returns accounts as a list of pairs of accountname, accountnumber 
	virtual vector<pair<string,string> > getBankAccounts();
    virtual vector<string> getProductGroups();
    virtual vector<string> getProducts(BOOL bVatGroup);
    virtual vector<string> getCustomerGroups();
    virtual vector<string> getCustomers();
	virtual BOOL getAlvVect(Alv *&pAlv);				// 14.8.2010, J.V.

	virtual int createBill(const string& customerid,
							vector<PriceComponent>&, const string& bankaccount,
							const COleDateTime& duedate, const string& ourReference,
							const string& yourReference, const string& pricesFrom);

	string calculateReferenceNumber(const string& original);

	int fixedVatPercent(CBdeDatabase& productdatabase, DbCustomer& customer, CBdeDatabase& discountdatabase, CBdeDatabase& billdatabase, CBdeDatabase* accountdatabase,
		                vector<PriceComponent>& prodvec, const string& bankaccount,
						const COleDateTime& duedate, const string& ourReference,
						const string& yourReference, const string& pricesFrom);		// 13.8.2010, J.V.

	int groupVatPercent(CBdeDatabase& productdatabase, DbCustomer& customer, CBdeDatabase& discountdatabase, CBdeDatabase& billdatabase, CBdeDatabase* accountdatabase, Alv *pAlv,
		                vector<PriceComponent>& prodvec, const string& bankaccount,
						const COleDateTime& duedate, const string& ourReference,
						const string& yourReference, const string& pricesFrom);		// 13.8.2010, J.V.

	BOOL isVatGroup();																// 13.8.2010, J.V.
};

#endif // !defined(AFX_NEUVOSPROGRAM_H__6509C8A2_5D4B_11D8_80E8_0010A4DF8E4B__INCLUDED_)
