// Bill.h: interface for the Bill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BILL_H__39B14AE3_58A8_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_BILL_H__39B14AE3_58A8_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <string>
using namespace std;

class CBdeDatabase;

class Bill  
{
private:
	BOOL blank;

	int billNumber;
	int billPhase;
	int acPhase;
	int cId;
	string cName;
	string cName2;
	string cAddress;
	string cZipCode;
	string cZipName;
	string cCountry;
	string cContactPerson;
	string cNumber;
	string payingCondition;
	COleDateTime billDate;
	COleDateTime deliveryDate;
	COleDateTime dueDate;
	string bankAccount;
	string ourReference;
	string yourReference;
	string referenceNumber;
	double billSum;
	int currency;
	double rounding;
	int incomeType;
	int outcomeType;
	string acIncomeAccount;
	string acMsAccount;
	int incomeProofNumber;
	string chosen;
	COleDateTime modifiedDate;
	string modifier;
	string ac;


public:
	Bill();
	virtual ~Bill();


	int getBillNumber();	// muodosta etsimällä isoin numero ja lisäämällä 1
	
	int getBillPhase();	// 2
	int getAcPhase();	//1
	
	int getCId();		// saadaan customer-oliosta 
	string getCName();	
	string getCName2();
	string getCAddress();
	string getCZipCode();
	string getCZipName();
	string getCCountry();
	string getCContactPerson();
	string getCNumber();
	string getPayingCondition();
	
	
	COleDateTime getBillDate(); //tämä päivämäärä
	COleDateTime getDeliveryDate(); //tämä päivämäärä
	
	COleDateTime getDueDate(); //saadaan käyttöliittymästä
	string getBankAccount();	//saadaan käyttöliittymästä
	
	string getOurReference();		// tyhjä
	string getYourReference();		// saadaan käyttöliittymästä
	string getReferenceNumber();	// lasketaan laskunnumerosta
	
	double getBillSum();			// lasketaan tuoteriveistä
	
	int getCurrency();				// 1
	double getRounding();			// 0
	int getIncomeType();			// 1
	int getOutcomeType();			// 0
	string getAcIncomeAccount();	// tyhjä	
	string getAcMsAccount();		// tyhjä
	int getIncomeProofNumber();		// 0
	string getChosen();
	
	COleDateTime getModifiedDate(); //tämä päivämäärä
	
	string getModifier();		//t-aika
	string getAc();				//tyhjä

	void setBillNumber(int _number);
	void setBillPhase(int _phase);
	void setAcPhase(int _phase);
	void setCId(int _id);
	void setCName(const string& _name);
	void setCName2(const string& _name);
	void setCAddress(const string& _address);
	void setCZipCode(const string& _code);
	void setCZipName(const string& _name);
	void setCCountry(const string& _country);
	void setCContactPerson(const string& _person);
	void setCNumber(const string& _number);
	void setPayingCondition(const string& condition);
	void setBillDate(const COleDateTime& _date);
	void setDeliveryDate(const COleDateTime& _date);
	void setDueDate(const COleDateTime& _date);
	void setBankAccount(const string& _account);
	void setOurReference(const string& _reference);
	void setYourReference(const string& _reference);
	void setReferenceNumber(const string& _number);
	void setBillSum(double _sum);
	void setCurrency(int _currency);
	void setRounding(double _rounding);
	void setIncomeType(int _type);
	void setOutcomeType(int _type);
	void setAcIncomeAccount(const string& _account);
	void setAcMsAccount(const string& _account);
	void setIncomeProofNumber(int _number);
	void setChosen(const string& _chosen);
	void setModifiedDate(const COleDateTime& _date);
	void setModifier(const string& _modifier);
	void setAc(const string& _ac);
	void saveToDb(CBdeDatabase& dbase);
	
	int getBiggestIdFromDb(CBdeDatabase& dbase);

	void loadFromDb(CBdeDatabase& dbase);
	string toString();
};

#endif // !defined(AFX_BILL_H__39B14AE3_58A8_11D8_80E8_0010A4DF8E4B__INCLUDED_)
