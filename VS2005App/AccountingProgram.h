// AccountingProgram.h: interface for the AccountingProgram class.
//
//////////////////////////////////////////////////////////////////////
/*
Usage example:
  
	AccountingProgram ac;
	vector<pair<string, string> > myvec=ac.getBankAccounts();
	string temp;
	for (int j=0; j<myvec.size(); j++)
		{
		temp+=myvec.at(j).first;
		temp+=": ";
		temp+=myvec.at(j).second;
		temp+="\r\n";
		}
	AfxMessageBox(temp.c_str());
*/

#if !defined(AFX_ACCOUNTINGPROGRAM_H__94E04501_5BBA_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_ACCOUNTINGPROGRAM_H__94E04501_5BBA_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>
#include <map>
#include "PriceComponent.h"
#include "defines.h"

using namespace std;

class AccountingProgram  
{
public:
	AccountingProgram();
	virtual ~AccountingProgram();

	virtual void open(const string& databasedir);
	virtual void close();
	
	// returns accounts as a list of pairs of accountname, accountnumber 

	virtual vector<pair<string,string> > getBankAccounts();
    virtual vector<string> getProductGroups();
    virtual vector<string> getProducts(BOOL bVatGroup);
    virtual vector<string> getCustomerGroups();
    virtual vector<string> getCustomers();
	virtual BOOL getAlvVect(Alv *&pAlv);	// 14.8.2010, J.V.
	virtual BOOL isVatGroup();				// 13.8.2010, J.V.

	virtual int createBill(const string& customerid, 
							vector<PriceComponent>&, const string& bankaccount,
							const COleDateTime& duedate, const string& ourReference,
							const string& yourReference, const string& pricesFrom);

};

#endif // !defined(AFX_ACCOUNTINGPROGRAM_H__94E04501_5BBA_11D8_80E8_0010A4DF8E4B__INCLUDED_)
