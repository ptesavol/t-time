// NeuvosProgram.cpp: implementation of the NeuvosProgram class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4786)
#include "stdafx.h"
#include "BdeInserter.h"
#include "NeuvosProgram.h"
#include "BdeDatabase.h"
#include "BdeException.h"
#include "DbCustomer.h"
#include "DbProduct.h"
#include "DbAccount.h"
#include "Bill.h"
#include "BillLine.h"
#include "stringhelper.h"
#include "Paivays.h"
#include <iostream>
#include "AccountingException.h"
#include <stdlib.h>
#include "DbDiscountGroup.h"
#include "defines.h"
#include "Props.h"

#pragma warning(disable : 4786)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NeuvosProgram::NeuvosProgram()
{

}

NeuvosProgram::~NeuvosProgram()
{

}

void NeuvosProgram::open(const string& databasedir)
	{
	CBdeDatabase::Initialize();
	this->dbdir=databasedir;
	}

void NeuvosProgram::close() {}
	
// returns accounts as a list of pairs of accountname, accountnumber 

vector<pair<string,string> > NeuvosProgram::getBankAccounts() 
		{
		CBdeDatabase database;
		BankAccount tempaccount;
		pair<string, string> temppair;
		vector<pair<string,string> > retvec;

		try		{
				string ts=dbdir;
				ts+="ptilit.db";
				database.OpenDatabase(ts.c_str());
				}
		catch (CBdeException* e)
				{
				e->ReportError();
				e->Delete();	
				database.CloseDatabase();
				return retvec;
				}
		
		if (database.GetRecordCount()==0)
			return retvec;
		database.MoveFirst();
		for (int i=0; i<database.GetRecordCount(); i++)	
			{
			tempaccount.loadFromDb(database);
			temppair.first=tempaccount.getAccountName();
			temppair.second=tempaccount.getAccountNumber();
			retvec.push_back(temppair);
			database.MoveNext();
			}
		
		database.CloseDatabase();
		return retvec;
		}
	
	
	 

int NeuvosProgram::createBill(const string& customerid,
							vector<PriceComponent>& prodvec, const string& bankaccount,
							const COleDateTime& duedate, const string& ourReference,
							const string& yourReference, const string& pricesFrom) 
	{
		CString cs;
		Alv *pAlv = NULL;								// 13.8.2010/14.8.2010, J.V.
		BOOL bvg = getAlvVect(pAlv);

		CBdeDatabase customerdatabase;

		try		{
				string ts=dbdir;
				ts+="Toi_as.db";
				customerdatabase.OpenDatabase(ts.c_str());
				}
		catch (CBdeException* )
				{
				//e->ReportError();
				//e->Delete();	
				customerdatabase.CloseDatabase();
				//return 1;
				throw;
				}	

		DbCustomer customer;

		try	{
			if ((customer.findAndLoadFromDb(atoi(customerid.c_str()),customerdatabase ))!=0)
				{
				cs.Format(Props::i().lang("NEUVOSPROGRAM_1"), customerid);
				throw AccountingException((LPCSTR)cs);
				}
				//return 2;
			}
		catch (...)
			{
			cs.Format(Props::i().lang("NEUVOSPROGRAM_2"), customerid);
			throw AccountingException((LPCSTR)cs);
			//return 3;
			}

		customerdatabase.CloseDatabase();	

		CBdeDatabase productdatabase;

		try		{
				string ts=dbdir;
				ts+="tuotteet.db";
				productdatabase.OpenDatabase(ts.c_str());
				}
		catch (CBdeException* e)
				{
				//e->ReportError();
				//e->Delete();	
				productdatabase.CloseDatabase();
				//return 4;
				throw e;
				}

		CBdeDatabase discountdatabase;

		try		{
				string ts=dbdir;
				ts+="traleryhmat.db";
				discountdatabase.OpenDatabase(ts.c_str());
				}
		catch (CBdeException* e)
				{
				//e->ReportError();
				//e->Delete();	
				discountdatabase.CloseDatabase();
				productdatabase.CloseDatabase();
				//return 4;
				throw e;
				}	

		CBdeDatabase billdatabase;

		try		{
				string ts=dbdir;
				ts+="mr_lasku.db";
				billdatabase.OpenDatabase(ts.c_str());
				}
		catch (CBdeException* e)
				{
				//e->ReportError();
				//e->Delete();	
				billdatabase.CloseDatabase();
				productdatabase.CloseDatabase();
				//return 4;
				throw e;
				}	

		CBdeDatabase* accountdatabase = new CBdeDatabase();

		try		{
				string ts=dbdir;
				ts+="tilik.db";
				accountdatabase->OpenDatabase(ts.c_str());
				}
		catch (CBdeException* e)
				{

				//e->ReportError();
				//e->Delete();	
				//accountdatabase.CloseDatabase();
				//return 4;
				//throw e;
				accountdatabase = 0;
				}

		int r;
		if(!bvg)							// 13.8.2010, J.V. vanha ja uusi alv-käsittely
			r = fixedVatPercent(productdatabase, customer, discountdatabase, billdatabase, accountdatabase,
				                   prodvec, bankaccount,
					               duedate, ourReference, yourReference, pricesFrom);
		else
			r = groupVatPercent(productdatabase, customer, discountdatabase, billdatabase, accountdatabase, pAlv,
			                    prodvec, bankaccount,
					            duedate, ourReference, yourReference, pricesFrom);
		delete [] pAlv;

		return r;
	}

int NeuvosProgram::fixedVatPercent(CBdeDatabase& productdatabase, DbCustomer& customer, CBdeDatabase& discountdatabase, CBdeDatabase& billdatabase, CBdeDatabase* accountdatabase,
								   vector<PriceComponent>& prodvec, const string& bankaccount,
								   const COleDateTime& duedate, const string& ourReference,
								   const string& yourReference, const string& pricesFrom)		// 13.8.2010, J.V.
	{
		CString cs;
		DbProduct product;
		DbAccount account;

		Bill tempbill;
		tempbill.setBillNumber(tempbill.getBiggestIdFromDb(billdatabase)+1);
	
		
		tempbill.setBillPhase(2);
		tempbill.setAcPhase(1);
		
		tempbill.setCId(customer.getCId());
		tempbill.setCName(customer.getCName());
		tempbill.setCName2(customer.getCName2());
		tempbill.setCAddress(customer.getCAddress());
		tempbill.setCZipCode(customer.getCZipCode());
		tempbill.setCZipName(customer.getCZipName());
		tempbill.setCCountry(customer.getCCountry());
		tempbill.setCContactPerson(customer.getCContactPerson());
		tempbill.setCNumber(customer.getCustomerNumber());
		tempbill.setPayingCondition(customer.getPayingCondition());
	
		tempbill.setBillDate(COleDateTime::GetCurrentTime());
		tempbill.setDeliveryDate(COleDateTime::GetCurrentTime());
		
		COleDateTime tim = COleDateTime::GetCurrentTime();

		if (customer.getPayingCondition() == "14pv-2% 30 pv netto")
			tim+=COleDateTimeSpan(30,0,0,0);
		else if (customer.getPayingCondition() == "7 päivää netto")
			tim+=COleDateTimeSpan(7,0,0,0);
		else if (customer.getPayingCondition() == "KÄTEISMAKSU")
			;	
		else
			tim+=COleDateTimeSpan(14,0,0,0);
		
		tempbill.setDueDate(tim);

		tempbill.setBankAccount(bankaccount);
		
		tempbill.setOurReference(ourReference);
		tempbill.setYourReference(yourReference);

		string sref=st(tempbill.getBillNumber());
		tempbill.setReferenceNumber(calculateReferenceNumber(sref));
		//tempbill.setBillSum(double _sum);

		tempbill.setCurrency(1);
		tempbill.setRounding(0);
		tempbill.setIncomeType(1);
		tempbill.setOutcomeType(0);

		tempbill.setAcIncomeAccount("");
		tempbill.setAcMsAccount("");

		tempbill.setIncomeProofNumber(0);
		tempbill.setChosen("");
		tempbill.setModifiedDate(COleDateTime::GetCurrentTime());
		tempbill.setModifier("t-aika");
		tempbill.setAc("");
		
		double billsum=0;	

		vector<BillLine> linevec;
		BillLine templine;

		for (int i=0; i<prodvec.size(); i++)
			{
			if ((product.findAndLoadFromDb(prodvec.at(i).getProductId(),productdatabase))!=0)
				{
				billdatabase.CloseDatabase();
				productdatabase.CloseDatabase();
				if (accountdatabase!=0)
					{
					accountdatabase->CloseDatabase();
					delete accountdatabase;
					}
				cs.Format(Props::i().lang("NEUVOSPROGRAM_3"), prodvec.at(i).getProductId());
				throw AccountingException((LPCSTR)cs);
				//return 5;
				}
			if (accountdatabase!=0)
				{
				if ((account.findAndLoadFromDb(product.getAcAccountNumber(),*accountdatabase))!=0)
					{
					billdatabase.CloseDatabase();
					productdatabase.CloseDatabase();
					if (accountdatabase!=0)
						{
						accountdatabase->CloseDatabase();
						delete accountdatabase;
						}
					cs.Format(Props::i().lang("NEUVOSPROGRAM_4"), product.getAcAccountNumber());
					throw AccountingException((LPCSTR)cs);
					//return 6;
					}
				}
			
			
			templine.setBillNumber(tempbill.getBillNumber());	//tempbillstä
			
			int bizarre=0x80000000;
			int tbz=i+1;
			tbz=tbz<<20;
			tbz=tbz&0x0ff00000;
			bizarre=bizarre|tbz;
			
			
			templine.setLineNumber(bizarre);						// i
			
			templine.setLineType(0);				//0
			
			templine.setAccountCode(product.getAcAccountNumber());	//tuotteesta
			templine.setProductId(product.getId());
			templine.setProductName(product.getName());
			
			templine.setAmount(prodvec.at(i).getAmount());	//parametrista
			
			templine.setUnit(product.getUnit());	// tuotteesta

			templine.setTaxCode(product.getTaxCode());					//!!!
			
			double pr=0;
			double vpr=0;
			double ur=0;
			double ur2=0;
			

			if(pricesFrom == HINNAT_LASKOHJ)
				{
				ur=product.getUnitPrice();
					//etsitään tuote- ja asiakastyhmäkohtainen alennusprosentti
				DbDiscountGroup discountGroup;
				if (discountGroup.findAndLoadFromDb(customer.getGroup(),product.getGroup(),discountdatabase)==0)
					ur=(ur*(100-discountGroup.getDiscountPercent()))/100;  
				ur2=ur;

				if (product.getTaxCode()==0)
					ur=(ur*(100+product.getTaxPercent()))/100;
			
				
				
				
				vpr=ur*prodvec.at(i).getAmount();
				vpr=(vpr*(100-customer.getDiscount()))/100;  
				
			


				pr=(vpr/(100+product.getTaxPercent()))*100;
				
				templine.setUnitPrice(ur2);	// tuotteesta	
				
				templine.setDiscountPercent(customer.getDiscount()); // customerista
				
				
				}
			else	
				{
				pr=prodvec.at(i).getTotalPrice();	
				if (prodvec.at(i).getVatPercent()!=0)
					vpr=pr*(1+prodvec.at(i).getVatPercent());
				else vpr=(pr*(100+product.getTaxPercent()))/100;	
				templine.setUnitPrice(pr/prodvec.at(i).getAmount());
				templine.setDiscountPercent(0); // 0
				}
			
			billsum+=vpr;

			templine.setTaxlessPrice(pr);		// lasketaan
			
		
			
			templine.setTaxedPrice(vpr);			// lasketaan
			if (accountdatabase!=0)
				templine.setVatAccount(account.getVatAccountNumber());	// tilistä
			
			templine.setVatPrice(vpr-pr);			// lasketaan
			
			templine.setVatPercent(product.getVatType()); // tuotteesta
			
			if (accountdatabase!=0)
				templine.setBalanceType(account.getBalanceType());			//tilistä
			

			templine.setTargetNumber(0);		//0?
			templine.setHappeningType(0);		//0?
			
			templine.setAc("");		//tyhjä
			templine.setDeliveryDate(COleDateTime::GetCurrentTime()); //tämä pvm
			

			linevec.push_back(templine);
			}

		productdatabase.CloseDatabase();
		discountdatabase.CloseDatabase();
		if (accountdatabase!=0)
			{
			accountdatabase->CloseDatabase();
			delete accountdatabase;
			}
		tempbill.setBillSum(billsum);
	
		// save to disk
		
		billdatabase.MoveLast();		
		billdatabase.Append();
		tempbill.saveToDb(billdatabase);
		if (billdatabase.Post() == FALSE)
			{
			billdatabase.Cancel();
			throw AccountingException((LPCSTR)Props::i().lang("NEUVOSPROGRAM_5"));
			}
		billdatabase.CloseDatabase();

		CBdeDatabase linedatabase;

		try		{
				string ts=dbdir;
				ts+="mr_laskurivit.db";
				linedatabase.OpenDatabase(ts.c_str());
				}
		catch (CBdeException* e)
				{
				//e->ReportError();
				//e->Delete();	
				linedatabase.CloseDatabase();
				//return 7;
				throw e; 
				}		

		for (int j=0; j<linevec.size(); j++)
			{
			
			linedatabase.MoveLast();
			linedatabase.Append();
			linevec.at(j).saveToDb(linedatabase);
			if (linedatabase.Post()==FALSE)
				{
				linedatabase.Cancel();
				throw AccountingException((LPCSTR)Props::i().lang("NEUVOSPROGRAM_6"));
				}
			}

		linedatabase.CloseDatabase();
		return 0;
		}

int NeuvosProgram::groupVatPercent(CBdeDatabase& productdatabase, DbCustomer& customer, CBdeDatabase& discountdatabase, CBdeDatabase& billdatabase, CBdeDatabase* accountdatabase, Alv *pAlv,
								   vector<PriceComponent>& prodvec, const string& bankaccount,
								   const COleDateTime& duedate, const string& ourReference,
								   const string& yourReference, const string& pricesFrom)		// 13.8.2010, J.V.
	{
		CString cs;
		DbProduct product;
		product.setVatVect(pAlv);
		DbAccount account;

		Bill tempbill;
		tempbill.setBillNumber(tempbill.getBiggestIdFromDb(billdatabase)+1);
		tempbill.setBillPhase(2);
		tempbill.setAcPhase(1);
		tempbill.setCId(customer.getCId());
		tempbill.setCName(customer.getCName());
		tempbill.setCName2(customer.getCName2());
		tempbill.setCAddress(customer.getCAddress());
		tempbill.setCZipCode(customer.getCZipCode());
		tempbill.setCZipName(customer.getCZipName());
		tempbill.setCCountry(customer.getCCountry());
		tempbill.setCContactPerson(customer.getCContactPerson());
		tempbill.setCNumber(customer.getCustomerNumber());
		tempbill.setPayingCondition(customer.getPayingCondition());
		tempbill.setBillDate(COleDateTime::GetCurrentTime());
		tempbill.setDeliveryDate(COleDateTime::GetCurrentTime());
		COleDateTime tim = COleDateTime::GetCurrentTime();
		if (customer.getPayingCondition() == "14pv-2% 30 pv netto")
			tim+=COleDateTimeSpan(30,0,0,0);
		else if (customer.getPayingCondition() == "7 päivää netto")
			tim+=COleDateTimeSpan(7,0,0,0);
		else if (customer.getPayingCondition() == "KÄTEISMAKSU")
			;	
		else
			tim+=COleDateTimeSpan(14,0,0,0);
		tempbill.setDueDate(tim);
		tempbill.setBankAccount(bankaccount);
		tempbill.setOurReference(ourReference);
		tempbill.setYourReference(yourReference);
		string sref=st(tempbill.getBillNumber());
		tempbill.setReferenceNumber(calculateReferenceNumber(sref));
		//tempbill.setBillSum(double _sum);
		tempbill.setCurrency(1);
		tempbill.setRounding(0);
		tempbill.setIncomeType(1);
		tempbill.setOutcomeType(0);
		tempbill.setAcIncomeAccount("");
		tempbill.setAcMsAccount("");
		tempbill.setIncomeProofNumber(0);
		tempbill.setChosen("");
		tempbill.setModifiedDate(COleDateTime::GetCurrentTime());
		tempbill.setModifier("t-aika");
		tempbill.setAc("");

		vector<BillLine> linevec;
		BillLine templine;
		double billsum=0;
		int linenum = 0, bizarre, tbz;
		double pr=0;
		double vpr=0;
		double ur=0;
		double ur2=0;
		for(int i=0; i<prodvec.size(); i++)
		{
			if ((product.findAndLoadFromDb(prodvec.at(i).getProductId(), productdatabase)) != 0)
			{
				billdatabase.CloseDatabase();
				productdatabase.CloseDatabase();
				if (accountdatabase!=0)
				{
					accountdatabase->CloseDatabase();
					delete accountdatabase;
				}
				cs.Format(Props::i().lang("NEUVOSPROGRAM_3"), prodvec.at(i).getProductId());
				throw AccountingException((LPCSTR)cs);
			}

			if (accountdatabase != 0)
			{
				if ((account.findAndLoadFromDb(product.getAcAccountNumber(), *accountdatabase))!=0)
				{
					billdatabase.CloseDatabase();
					productdatabase.CloseDatabase();
					if (accountdatabase != 0)
					{
						accountdatabase->CloseDatabase();
						delete accountdatabase;
					}
					cs.Format(Props::i().lang("NEUVOSPROGRAM_7"), product.getAcAccountNumber());
					throw AccountingException((LPCSTR)cs);
				}
			}

			if(pricesFrom == HINNAT_LASKOHJ)		// KÄYTETÄÄN LSKUTUSOHJELMAN HINTA-/VEROTIETOJA
			{
				// Etsi RyhmäId:n mukaan tuorein prosentti pVatista ja lisää tuotteen hinta totaliin -> saadaan tuotteen ostopäivän mukainen verokanta ja erotellaan verokannat eri riveille laskuun
				int ai = (int)product.getTaxPercent();
				if((ai = pAlv[0].findAlvProIndex(pAlv, ai, prodvec.at(i).getStartDate())) != -1)
					pAlv[ai].total += prodvec.at(i).getAmount();

				// Käydään läpi kaikki samat (taatusti peräkkäin vektorissa olevat) työtyypit
				if(i + 1 < prodvec.size()) {
					if(prodvec.at(i).getProductId() == prodvec.at(i + 1).getProductId()) continue; }

				// Tuotteen (mahdollisesti) eri verokannan mukaiset hinnat on nyt selvitetty -> lisätään ne nyt omille riveilleen laskuun, muistetaan nollata total-kentät Alv-vektorista seuraavaa tuotetta varten
				for(int a=0; a<pAlv[0].size; a++)
				{
					if(pAlv[a].total > 0)												// nollaa suuremmat laskutetaan
					{
						templine.setBillNumber(tempbill.getBillNumber());				// tempbillstä
						bizarre=0x80000000;												// :
						tbz = ++linenum;
						tbz=tbz<<20;
						tbz=tbz&0x0ff00000;
						bizarre=bizarre|tbz;
						templine.setLineNumber(bizarre);								// i
						templine.setLineType(0);										// 0
						templine.setAccountCode(product.getAcAccountNumber());			// tuoteesta
						templine.setProductId(product.getId());
						if(product.getRevesedVat() == 1)
							templine.setProductName(product.getName() + (LPCSTR)Props::i().lang("NEUVOSPROGRAM_8"));
						else
							templine.setProductName(product.getName());
						templine.setAmount(pAlv[a].total);								// tähän alv:iin lisättyjen tuotteiden yhteenlaskettu hinta
						templine.setUnit(product.getUnit());							// tuotteesta
						templine.setTaxCode(product.getTaxCode());						// !!!
						templine.setRevesedVat(product.getRevesedVat());

						ur=product.getUnitPrice();
						DbDiscountGroup discountGroup;									//etsitään tuote- ja asiakastyhmäkohtainen alennusprosentti
						if (discountGroup.findAndLoadFromDb(customer.getGroup(),product.getGroup(),discountdatabase)==0)
							ur=(ur*(100-discountGroup.getDiscountPercent()))/100;  
						ur2=ur;
						if (product.getTaxCode()==0)
							ur=(ur*(100+pAlv[a].AlvPro))/100;
						vpr=ur * pAlv[a].total;
						vpr=(vpr*(100-customer.getDiscount()))/100;
						pr=(vpr/(100+pAlv[a].AlvPro))*100;

						templine.setUnitPrice(ur2);										// tuotteesta	
						templine.setDiscountPercent(customer.getDiscount());			// customerista
						templine.setTaxlessPrice(pr);									// lasketaan
						templine.setTaxedPrice(vpr);									// lasketaan
						if (accountdatabase!=0)
							templine.setVatAccount(account.getVatAccountNumber());		// tilistä
						templine.setVatPrice(vpr-pr);									// lasketaan
						templine.setVatPercent((LPCSTR)pAlv[a].N);						// tuotteen alv-ryhmän avulla löydetty alv:n id
						if (accountdatabase!=0)
							templine.setBalanceType(account.getBalanceType());			// tilistä
						templine.setTargetNumber(0);									// 0?
						templine.setHappeningType(0);									// 0?
						templine.setAc("");												// tyhjä
						templine.setDeliveryDate(COleDateTime::GetCurrentTime());		// tämä pvm

						linevec.push_back(templine);
						billsum += vpr;
					}

					pAlv[a].total = 0;													// muista nollata seuraavaa kierrosta (tuotetta) varten
				}
			}
			else									// KÄYTETÄÄN MATKAPUHELIMESTA SAATUJA HINTA-/VEROTIETOJA
			{
				templine.setBillNumber(tempbill.getBillNumber());					// tempbillstä
				bizarre=0x80000000;													// :
				tbz = ++linenum;
				tbz=tbz<<20;
				tbz=tbz&0x0ff00000;
				bizarre=bizarre|tbz;
				templine.setLineNumber(bizarre);									// i
				templine.setLineType(0);											// 0
				templine.setAccountCode(product.getAcAccountNumber());				// tuotteesta
				templine.setProductId(product.getId());
				if(product.getRevesedVat() == 1)
					templine.setProductName(product.getName() + (LPCSTR)Props::i().lang("NEUVOSPROGRAM_8"));
				else
					templine.setProductName(product.getName());
				templine.setAmount(prodvec.at(i).getAmount());						// parametrista
				templine.setUnit(product.getUnit());								// tuotteesta
				templine.setTaxCode(product.getTaxCode());							// !!!
				templine.setRevesedVat(product.getRevesedVat());

				pr=prodvec.at(i).getTotalPrice();	
				if (prodvec.at(i).getVatPercent()!=0)
					vpr=pr*(1+prodvec.at(i).getVatPercent());
				else
					vpr=(pr*(100+product.getTaxPercent()))/100;	
				templine.setUnitPrice(pr/prodvec.at(i).getAmount());
				templine.setDiscountPercent(0);										// 0
				templine.setTaxlessPrice(pr);										// lasketaan
				templine.setTaxedPrice(vpr);										// lasketaan
				if (accountdatabase!=0)
					templine.setVatAccount(account.getVatAccountNumber());			// tilistä
				templine.setVatPrice(vpr-pr);										// lasketaan
				templine.setVatPercent(product.getVatType());						// tuotteen alv määrittämättä
				if (accountdatabase!=0)
					templine.setBalanceType(account.getBalanceType());				// tilistä
				templine.setTargetNumber(0);										// 0?
				templine.setHappeningType(0);										// 0?
				templine.setAc("");													// tyhjä
				templine.setDeliveryDate(COleDateTime::GetCurrentTime());			// tämä pvm

				linevec.push_back(templine);
				billsum += vpr;
			}
		}

		// Viedään rivit laskuun
		productdatabase.CloseDatabase();
		discountdatabase.CloseDatabase();
		if (accountdatabase!=0)
		{
			accountdatabase->CloseDatabase();
			delete accountdatabase;
		}

		// save to disk
		billdatabase.MoveLast();		
		billdatabase.Append();
		tempbill.setBillSum(billsum);
		tempbill.saveToDb(billdatabase);
		if (billdatabase.Post() == FALSE)
		{
			billdatabase.Cancel();
			string errs(Props::i().lang("NEUVOSPROGRAM_9"));
			throw AccountingException(errs);
		}
		billdatabase.CloseDatabase();

		CBdeDatabase linedatabase;

		try		
		{
			string ts=dbdir;
			ts+="mr_laskurivit.db";
			linedatabase.OpenDatabase(ts.c_str());
		}
		catch (CBdeException* e)
		{
			linedatabase.CloseDatabase();
			throw e; 
		}

		for (int j=0; j<linevec.size(); j++)
		{
			linedatabase.MoveLast();
			linedatabase.Append();
			linevec.at(j).saveToDb(linedatabase);
			if (linedatabase.Post()==FALSE)
			{
				linedatabase.Cancel();
				string errs(Props::i().lang("NEUVOSPROGRAM_10"));
				throw AccountingException(errs);
			}
		}

		linedatabase.CloseDatabase();
		return 0;
	}

string NeuvosProgram::calculateReferenceNumber(const string& original)
	{
	char temp='0';
	int sum=0;
	int weight=7;
	for (int i=(original.size()-1); i>-1; i--)
		{
		temp=(original[i]);
		temp=temp-'0';
		sum+=(temp*weight);

		if (weight==7)
			{
			weight=3;	
			continue;
			}
		
		if (weight==3)
			{
			weight=1;	
			continue;
			}

		if (weight==1)
			{
			weight=7;	
			continue;
			}
		}

	int result=0;

	if (sum==0 || sum%10==0)
		{
		result=0;
		}
	else
		{
		result=10-(sum%10);
		}

	if (result==10)
		result=0;
	
	string ret=original+st(result);
	return ret;
	}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
// For "Import", 23.10.2008

// returns consecutive duplets: [Tunnus, Nimi]
vector<string> NeuvosProgram::getProductGroups() 
		{
		CBdeDatabase database;
		vector<string> retvec;
        BOOL blank = FALSE;

		try		{
				string ts=dbdir;
				ts+="tuoteryhmat.db";
				database.OpenDatabase(ts.c_str());
				}
		catch (CBdeException* e)
				{
				e->ReportError();
				e->Delete();	
				database.CloseDatabase();
				return retvec;
				}
		
		if (database.GetRecordCount()==0)
			return retvec;

		database.MoveFirst();
		for (int i=0; i<database.GetRecordCount(); i++)	
			{
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("Tunnus"), &blank));
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("Nimi"), &blank));
			database.MoveNext();
			}
		
		database.CloseDatabase();
		return retvec;
		}

// returns consecutive: [TryhmaTunnus, TuoteNimi, TuoteTunnus, Yksikko, VoHinta, AHinta, ALVKanta]
vector<string> NeuvosProgram::getProducts(BOOL bVatGroup) 
	{
		CBdeDatabase database;
		vector<string> retvec;
        BOOL blank = FALSE;

		try		{
				string ts=dbdir;
				ts+="tuotteet.db";
				database.OpenDatabase(ts.c_str());
				}
		catch (CBdeException* e)
				{
				e->ReportError();
				e->Delete();	
				database.CloseDatabase();
				return retvec;
				}

		if (database.GetRecordCount()==0)
			return retvec;

		database.MoveFirst();
		for (int i=0; i<database.GetRecordCount(); i++)	
		{
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("TryhmaTunnus"), &blank));
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("TuoteNimi"), &blank));
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("TuoteTunnus"), &blank));
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("Yksikko"), &blank));
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("VoHinta"), &blank));
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("AHinta"), &blank));
			if(!bVatGroup)
				retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("ALVKanta"), &blank));
			else
				retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("AlvRyhmaID"), &blank));
			database.MoveNext();
		}
		
		database.CloseDatabase();
		return retvec;
	}

// returns consecutive: [Tunnus, Nimi]
vector<string> NeuvosProgram::getCustomerGroups()
	{
		CBdeDatabase database;
		vector<string> retvec;
        BOOL blank = FALSE;

		try		{
				string ts=dbdir;
				ts+="asryhmat.db";
				database.OpenDatabase(ts.c_str());
				}
		catch (CBdeException* e)
				{
				e->ReportError();
				e->Delete();	
				database.CloseDatabase();
				return retvec;
				}

		if (database.GetRecordCount()==0)
			return retvec;

		database.MoveFirst();
		for (int i=0; i<database.GetRecordCount(); i++)	
			{
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("Tunnus"), &blank));
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("Nimi"), &blank));
			database.MoveNext();
			}
		
		retvec.push_back("");
        retvec.push_back((LPCSTR)Props::i().lang("DEFINES_1"));

		database.CloseDatabase();
		return retvec;
	}

// returns consecutive: [Ryhma, Nimi, KatuOs, Tunnus, Lisatietoja]
vector<string> NeuvosProgram::getCustomers() 
	{
		CBdeDatabase database;
		vector<string> retvec;
        BOOL blank = FALSE;

		try		{
				string ts=dbdir;
				ts+="toi_as.db";
				database.OpenDatabase(ts.c_str());
				}
		catch (CBdeException* e)
				{
				e->ReportError();
				e->Delete();	
				database.CloseDatabase();
				return retvec;
				}
		
		if (database.GetRecordCount()==0)
			return retvec;

		database.MoveFirst();
		for (int i=0; i<database.GetRecordCount(); i++)	
			{
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("Ryhma"), &blank));
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("Nimi"), &blank));
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("KatuOs"), &blank));
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("Tunnus"), &blank));
			retvec.push_back((LPCSTR)database.GetFieldAsString(database.FieldNumberFromName("Lisatietoja"), &blank));
			database.MoveNext();
			}
		
		database.CloseDatabase();
		return retvec;
	}

BOOL  NeuvosProgram::isVatGroup()	// 13.8.2010, J.V., Onko alv-ryhmät käytössä
{
	BOOL bvg = FALSE;
	CBdeDatabase productdatabase;

	try
	{
		string ts = dbdir + "tuotteet.db";
		productdatabase.OpenDatabase(ts.c_str());
		bvg = productdatabase.FieldNumberFromName("AlvRyhmaID") == 0 ? FALSE : TRUE;
		productdatabase.CloseDatabase();
	}
	catch (CBdeException* e)
	{
	}

	productdatabase.CloseDatabase();

	return bvg;
}

BOOL NeuvosProgram::getAlvVect(Alv *&pAlv)
{
// 13.8.2010, J.V. haetaan alv-taulun sisältö, jos tuote-taulussa AlvRyhmaId-kenttä
	BOOL blank, bvg;
	Paivays paivays;
	COleDateTime codt;
	CBdeDatabase alvdatabase;
	int alvoffs = 0, vsize;
	try
	{
		bvg = isVatGroup();

		string ts = dbdir + "alv.db";
		alvdatabase.OpenDatabase(ts.c_str());
		vsize = alvdatabase.GetRecordCount();
		pAlv = new Alv[vsize];
		alvdatabase.MoveFirst();
		while(!alvdatabase.IsEOF())
		{
			pAlv[alvoffs].N = alvdatabase.GetFieldAsString(alvdatabase.FieldNumberFromName("N"), &blank);
			pAlv[alvoffs].AlvPro = alvdatabase.GetFieldAsInteger(alvdatabase.FieldNumberFromName("AlvPro"), &blank);

			if(bvg)
			{
				pAlv[alvoffs].Nimi = alvdatabase.GetFieldAsString(alvdatabase.FieldNumberFromName("Nimi"), &blank);

				if(alvdatabase.GetFieldAsString(alvdatabase.FieldNumberFromName("VoimassaOloAlku"), &blank) != "")
				{
					codt = alvdatabase.GetFieldAsDate(alvdatabase.FieldNumberFromName("VoimassaOloAlku"), &blank);
					pAlv[alvoffs].VoimassaOloAlkuPaiva = paivays.makeDate(codt.GetYear(), codt.GetMonth(), codt.GetDay());
					pAlv[alvoffs].VoimassaOloAlkuAika = paivays.makeTime(codt.GetHour(), codt.GetMinute());
				}
				else
				{
					pAlv[alvoffs].VoimassaOloAlkuPaiva = 0;
					pAlv[alvoffs].VoimassaOloAlkuAika = 0;
				}

				if(alvdatabase.GetFieldAsString(alvdatabase.FieldNumberFromName("VoimassaOloLoppu"), &blank) != "")
				{
					codt = alvdatabase.GetFieldAsDate(alvdatabase.FieldNumberFromName("VoimassaOloLoppu"), &blank);
					pAlv[alvoffs].VoimassaOloLoppuPaiva = paivays.makeDate(codt.GetYear(), codt.GetMonth(), codt.GetDay());
					pAlv[alvoffs].VoimassaOloLoppuAika = paivays.makeTime(codt.GetHour(), codt.GetMinute());
				}
				else
				{
					pAlv[alvoffs].VoimassaOloLoppuPaiva = 0;
					pAlv[alvoffs].VoimassaOloLoppuAika = 0;
				}

				pAlv[alvoffs].AlvRyhmaID = alvdatabase.GetFieldAsInteger(alvdatabase.FieldNumberFromName("AlvRyhmaID"), &blank);
				pAlv[alvoffs].total = 0;
				pAlv[alvoffs].size = vsize;

				alvoffs++;
				alvdatabase.MoveNext();
			}
		}
	}
	catch(CBdeException *pBdeE)
	{
		alvdatabase.CloseDatabase();
		throw AccountingException((LPCSTR)Props::i().lang("NEUVOSPROGRAM_11"));
	}

	alvdatabase.CloseDatabase();

	return bvg;
}