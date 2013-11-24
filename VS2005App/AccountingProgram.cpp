// AccountingProgram.cpp: implementation of the AccountingProgram class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4786)
#include "stdafx.h"
#include "AccountingProgram.h"
#include "defines.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AccountingProgram::AccountingProgram()
{

}

AccountingProgram::~AccountingProgram()
{

}

void AccountingProgram::open(const string& databasedir)
	{}

void AccountingProgram::close() {}
	
// returns accounts as a list of pairs of accountname, accountnumber 

vector<pair<string,string> > AccountingProgram::getBankAccounts() 
		{
		//return example list	

		vector<pair<string,string> > retvec;
		pair<string, string> myaccount;
		pair<string, string> myaccount2;
		
		myaccount.first="Osuuspankin tili";
		myaccount.second="12345345345";
		myaccount2.first="Säästöpankin tili";
		myaccount2.second="345657787";
		retvec.push_back(myaccount);
		retvec.push_back(myaccount2);
	
		return retvec;
		}
	
	
	 

int AccountingProgram::createBill(const string& customerid,
							vector<PriceComponent>&, const string& bankaccount,
							const COleDateTime& duedate, const string& ourReference,
							const string& yourReference, const string& pricesFrom) 
		{
		return 0;	
		}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// For "Import", 23.10.2008, J.V.
vector<string> AccountingProgram::getProductGroups()
		{
		//return example list	

		vector<string> retvec;
		retvec.push_back("1");
		retvec.push_back("Halot");

		return retvec;
		}

vector<string> AccountingProgram::getProducts(BOOL bVatGroup)
		{
		//return example list
		vector<string> retvec;
		retvec.push_back("1");
		retvec.push_back("Koivu");
		retvec.push_back("001");
		retvec.push_back("kg");
		retvec.push_back("10");
		retvec.push_back("20");
		retvec.push_back(bVatGroup ? "1" : "0");

		return retvec;
		}



vector<string> AccountingProgram::getCustomerGroups()
		{
		//return example list	

		vector<string> retvec;
		retvec.push_back("1");
		retvec.push_back("Alue 1");

		return retvec;
		}

vector<string> AccountingProgram::getCustomers()
		{
		//return example list	

		vector<string> retvec;
		retvec.push_back("1");
		retvec.push_back("Kiertotiet");
		retvec.push_back("Kiertotie 1-3");
		retvec.push_back("2");
		retvec.push_back("Kuoppainen tie");

		return retvec;
		}

BOOL AccountingProgram::getAlvVect(Alv *&pAlv)
		{
		//return example list
		pAlv = new Alv[1];
		pAlv[0].N = "0";
		pAlv[0].AlvPro = 0;
		pAlv[0].Nimi = "";
		pAlv[0].VoimassaOloAlkuPaiva = 0;
		pAlv[0].VoimassaOloAlkuAika = 0;
		pAlv[0].VoimassaOloLoppuPaiva = 0;
		pAlv[0].VoimassaOloLoppuAika = 0;
		pAlv[0].AlvRyhmaID = 0;
		pAlv[0].total = 0;
		pAlv[0].size = 1;

		return FALSE;
		}

BOOL AccountingProgram::isVatGroup()		// 13.8.2010, J.V.
{
	return FALSE;
}