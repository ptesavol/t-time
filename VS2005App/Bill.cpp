// Bill.cpp: implementation of the Bill class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4786)
#include "stdafx.h"
#include "BdeInserter.h"
#include "Bill.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "stringhelper.h"
#include "BdeDatabase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Bill::Bill(): blank(FALSE)
{

}

Bill::~Bill()
{

}

int Bill::getBillNumber()
	{
	return this->billNumber;
	}
int Bill::getBillPhase()
	{
	return this->billPhase;
	}
int Bill::getAcPhase()
	{
	return this->acPhase;
	}
int Bill::getCId()
	{
	return this->cId;
	}
string Bill::getCName()
	{
	return this->cName;
	}
string Bill::getCName2()
	{
	return this->cName2;
	}
string Bill::getCAddress()
	{
	return this->cAddress;
	}
string Bill::getCZipCode()
	{
	return this->cZipCode;
	}
string Bill::getCZipName()
	{
	return this->cZipName;
	}
string Bill::getCCountry()
	{
	return this->cCountry;
	}
string Bill::getCContactPerson()
	{
	return this->cContactPerson;
	}
string Bill::getCNumber()
	{
	return this->cNumber;
	}
string Bill::getPayingCondition()
	{
	return this->payingCondition;
	}
COleDateTime Bill::getBillDate()
	{
	return this->billDate;
	}
COleDateTime Bill::getDeliveryDate()
	{
	return this->deliveryDate;
	}
COleDateTime Bill::getDueDate()
	{
	return this->dueDate;
	}
string Bill::getBankAccount()
	{
	return this->bankAccount;
	}
string Bill::getOurReference()
	{
	return this->ourReference;
	}
string Bill::getYourReference()
	{
	return this->yourReference;
	}
string Bill::getReferenceNumber()
	{
	return this->referenceNumber;
	}
double Bill::getBillSum()
	{
	return this->billSum;
	}
int Bill::getCurrency()
	{
	return this->currency;
	}
double Bill::getRounding()
	{
	return this->rounding;
	}
int Bill::getIncomeType()
	{
	return this->incomeType;
	}
int Bill::getOutcomeType()
	{
	return this->outcomeType;
	}
string Bill::getAcIncomeAccount()
	{
	return this->acIncomeAccount;
	}
string Bill::getAcMsAccount()
	{
	return this->acMsAccount;
	}
int Bill::getIncomeProofNumber()
	{
	return this->incomeProofNumber;
	}
string Bill::getChosen()
	{
	return this->chosen;
	}
COleDateTime Bill::getModifiedDate()
	{
	return this->modifiedDate;
	}
string Bill::getModifier()
	{
	return this->modifier;
	}
string Bill::getAc()
	{
	return this->ac;
	}

void Bill::setBillNumber(int _number)
	{
	this->billNumber=_number;
	}
void Bill::setBillPhase(int _phase)
	{
	this->billPhase=_phase;
	}
void Bill::setAcPhase(int _phase)
	{
	this->acPhase=_phase;
	}
void Bill::setCId(int _id)
	{
	this->cId=_id;
	}
void Bill::setCName(const string& _name)
	{
	this->cName=_name;
	}
void Bill::setCName2(const string& _name)
	{
	this->cName2=_name;
	}
void Bill::setCAddress(const string& _address)
	{
	this->cAddress=_address;
	}
void Bill::setCZipCode(const string& _code)
	{
	this->cZipCode=_code;
	}
void Bill::setCZipName(const string& _name)
	{
	this->cZipName=_name;
	}
void Bill::setCCountry(const string& _country)
	{
	this->cCountry=_country;
	}
void Bill::setCContactPerson(const string& _person)
	{
	this->cContactPerson=_person;
	}
void Bill::setCNumber(const string& _number)
	{
	this->cNumber=_number;
	}
void Bill::setPayingCondition(const string& _condition)
	{
	this->payingCondition=_condition;
	}
void Bill::setBillDate(const COleDateTime& _date)
	{
	this->billDate=_date;
	}
void Bill::setDeliveryDate(const COleDateTime& _date)
	{
	this->deliveryDate=_date;
	}
void Bill::setDueDate(const COleDateTime& _date)
	{
	this->dueDate=_date;
	}
void Bill::setBankAccount(const string& _account)
	{
	this->bankAccount=_account;
	}
void Bill::setOurReference(const string& _reference)
	{
	this->ourReference=_reference;
	}
void Bill::setYourReference(const string& _reference)
	{
	this->yourReference=_reference;
	}
void Bill::setReferenceNumber(const string& _number)
	{
	this->referenceNumber=_number;
	}
void Bill::setBillSum(double _sum)
	{
	this->billSum=_sum;
	}
void Bill::setCurrency(int _currency)
	{
	this->currency=_currency;
	}
void Bill::setRounding(double _rounding)
	{
	this->rounding=_rounding;
	}
void Bill::setIncomeType(int _type)
	{
	this->incomeType=_type;
	}
void Bill::setOutcomeType(int _type)
	{
	this->outcomeType=_type;
	}
void Bill::setAcIncomeAccount(const string& _account)
	{
	this->acIncomeAccount=_account;
	}
void Bill::setAcMsAccount(const string& _account)
	{
	this->acMsAccount=_account;
	}
void Bill::setIncomeProofNumber(int _number)
	{
	this->incomeProofNumber=_number;
	}
void Bill::setChosen(const string& _chosen)
	{
	this->chosen=_chosen;
	}
void Bill::setModifiedDate(const COleDateTime& _date)
	{
	this->modifiedDate=_date;
	}
void Bill::setModifier(const string& _modifier)
	{
	this->modifier=_modifier;
	}
void Bill::setAc(const string& _ac)
	{
	this->ac=_ac;
	}

void Bill::saveToDb(CBdeDatabase& dbase)
	{	
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("LaskuNro"),billNumber);
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("LaskuVaihe"),billPhase);
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("KPVaihe"),acPhase);
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("ATunnus"),cId);	
	dbase.SetFieldAsString(dbase.FieldNumberFromName("ANimi"),cName.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("ANimi2"),cName2.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("AKatuosoite"),cAddress.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("APostiNro"),cZipCode.c_str());	
	dbase.SetFieldAsString(dbase.FieldNumberFromName("APostiOsoite"),cZipName.c_str());	
	dbase.SetFieldAsString(dbase.FieldNumberFromName("AValtio"),cCountry.c_str());	
	dbase.SetFieldAsString(dbase.FieldNumberFromName("AYhteysHlo"),cContactPerson.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("AsNro"),cNumber.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("Maksuehto"),payingCondition.c_str());
	dbase.SetFieldAsDate(dbase.FieldNumberFromName("LaskunPVM"),billDate);
	dbase.SetFieldAsDate(dbase.FieldNumberFromName("ToimitusPVM"),deliveryDate);
	dbase.SetFieldAsDate(dbase.FieldNumberFromName("EraPVM"),dueDate);
	dbase.SetFieldAsString(dbase.FieldNumberFromName("Pankkitili"),bankAccount.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("Viitteemme"),ourReference.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("Viitteenne"),yourReference.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("ViiteNro"),referenceNumber.c_str());
	dbase.SetFieldAsFloat(dbase.FieldNumberFromName("LaskunSumma"),billSum);
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("Rahayksikko"),currency);
	dbase.SetFieldAsFloat(dbase.FieldNumberFromName("Pennipyoristys"),rounding);
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("TuloTLaji"),incomeType);
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("SuoritusTLaji"),outcomeType);
	dbase.SetFieldAsString(dbase.FieldNumberFromName("KpTuloTili"),acIncomeAccount.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("KpMsTili"),acMsAccount.c_str());
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("TuloTositeNro"),incomeProofNumber);
	dbase.SetFieldAsString(dbase.FieldNumberFromName("Valittu"),chosen.c_str());
	dbase.SetFieldAsDate(dbase.FieldNumberFromName("MuokkausAika"),modifiedDate);
	dbase.SetFieldAsString(dbase.FieldNumberFromName("Muokkaaja"),modifier.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("Kp"),ac.c_str());
	
	//dbase.SetFieldAsInteger(dbase.FieldNumberFromName("ToimitusVaihe"),3);
	}

void Bill::loadFromDb(CBdeDatabase& dbase)
	{
	
	billNumber = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("LaskuNro"),&blank );
	billPhase = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("LaskuVaihe"),&blank );
	acPhase = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("KPVaihe"),&blank);
	cId = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("ATunnus"),&blank);	
	cName = dbase.GetFieldAsString(dbase.FieldNumberFromName("ANimi"),&blank);
	cName2 = dbase.GetFieldAsString(dbase.FieldNumberFromName("ANimi2"),&blank);
	cAddress = dbase.GetFieldAsString(dbase.FieldNumberFromName("AKatuosoite"),&blank);
	cZipCode = dbase.GetFieldAsString(dbase.FieldNumberFromName("APostiNro"),&blank);	
	cZipName = dbase.GetFieldAsString(dbase.FieldNumberFromName("APostiOsoite"),&blank);	
	cCountry = dbase.GetFieldAsString(dbase.FieldNumberFromName("AValtio"),&blank);	
	cContactPerson = dbase.GetFieldAsString(dbase.FieldNumberFromName("AYhteysHlo"),&blank);
	cNumber = dbase.GetFieldAsString(dbase.FieldNumberFromName("AsNro"),&blank);
	payingCondition = dbase.GetFieldAsString(dbase.FieldNumberFromName("Maksuehto"),&blank);
	billDate = dbase.GetFieldAsDate(dbase.FieldNumberFromName("LaskunPVM"),&blank);
	deliveryDate = dbase.GetFieldAsDate(dbase.FieldNumberFromName("ToimitusPVM"),&blank);
	dueDate = dbase.GetFieldAsDate(dbase.FieldNumberFromName("EraPVM"),&blank);
	bankAccount = dbase.GetFieldAsString(dbase.FieldNumberFromName("Pankkitili"),&blank);
	ourReference = dbase.GetFieldAsString(dbase.FieldNumberFromName("Viitteemme"),&blank);
	yourReference = dbase.GetFieldAsString(dbase.FieldNumberFromName("Viitteenne"),&blank);
	referenceNumber = dbase.GetFieldAsString(dbase.FieldNumberFromName("ViiteNro"),&blank);
	billSum = dbase.GetFieldAsFloat(dbase.FieldNumberFromName("LaskunSumma"),&blank);
	currency = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("Rahayksikko"),&blank);
	rounding = dbase.GetFieldAsFloat(dbase.FieldNumberFromName("Pennipyoristys"),&blank);
	incomeType = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("TuloTLaji"),&blank);
	outcomeType = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("SuoritusTLaji"),&blank);
	acIncomeAccount = dbase.GetFieldAsString(dbase.FieldNumberFromName("KpTuloTili"),&blank);
	acMsAccount = dbase.GetFieldAsString(dbase.FieldNumberFromName("KpMsTili"),&blank);
	incomeProofNumber = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("TuloTositeNro"),&blank);
	chosen = dbase.GetFieldAsString(dbase.FieldNumberFromName("Valittu"),&blank);
	modifiedDate = dbase.GetFieldAsDate(dbase.FieldNumberFromName("MuokkausAika"),&blank);
	modifier = dbase.GetFieldAsString(dbase.FieldNumberFromName("Muokkaaja"),&blank);
	ac = dbase.GetFieldAsString(dbase.FieldNumberFromName("Kp"),&blank);
	
  }

string Bill::toString()
	{
	string ret;
	ret+="LaskuNro: ";
	ret+= st(billNumber);
	ret+="\r\n";
	ret+="LaskuVaihe: ";
	ret+= st(billPhase);
	ret+="\r\n";
	ret+="KPVaihe: ";
	ret+= st(acPhase);
	ret+="\r\n";
	ret+="ATunnus: ";
	ret+= st(cId);
	ret+="\r\n";
	ret+="ANimi: ";
	ret+= cName;
	ret+="\r\n";
	ret+="Animi2: ";
	ret+= cName2;
	ret+="\r\n";
	ret+="AKatuosoite: ";
	ret+= cAddress;
	ret+="\r\n";
	ret+="APostiNro: ";
	ret+= cZipCode;
	ret+="\r\n";
	ret+="APostiOsoite: ";
	ret+= cZipName;
	ret+="\r\n";
	ret+="AValtio: ";
	ret+= cCountry;
	ret+="\r\n";
	ret+="AYhteysHlo";
	ret+= cContactPerson;
	ret+="\r\n";
	ret+="AsNro: ";
	ret+= cNumber;
	ret+="\r\n";
	ret+="Maksuehto: ";
	ret+= payingCondition;
	ret+="\r\n";
	ret+="LaskunPVM: ";
	ret+= billDate;
	ret+="\r\n";
	ret+="ToimitusPVM: ";
	ret+= deliveryDate;
	ret+="\r\n";
	ret+="EraPVM: ";
	ret+= dueDate;
	ret+="\r\n";
	ret+="Pankkitili: ";
	ret+= bankAccount;
	ret+="\r\n";
	ret+="Viitteemme: ";
	ret+= ourReference;
	ret+="\r\n";
	ret+="Viitteenne: ";
	ret+= yourReference;
	ret+="\r\n";
	ret+="ViiteNro: ";
	ret+= referenceNumber;
	ret+="\r\n";
	ret+="LaskunSumma: ";
	ret+= st(billSum);
	ret+="\r\n";
	ret+="Rahayksikko: ";
	ret+= st(currency);
	ret+="\r\n";
	ret+="Pennipyoristys: ";
	ret+= st(rounding);
	ret+="\r\n";
	ret+="TuloTLaji: ";
	ret+= st(incomeType);
	ret+="\r\n";
	ret+="SuoritusTLaji: ";
	ret+= st(outcomeType);
	ret+="\r\n";
	ret+="KpTuloTili:";
	ret+= acIncomeAccount;
	ret+="\r\n";
	ret+="KpMsTili: ";
	ret+= acMsAccount;
	ret+="\r\n";
	ret+="TuloTositeNro: ";
	ret+= st(incomeProofNumber);
	ret+="\r\n";
	ret+="Valittu: ";
	ret+= chosen;
	ret+="\r\n";
	ret+="MuokkausAika: ";
	ret+= modifiedDate;
	ret+="\r\n";
	ret+="Muokkaaja: ";
	ret+= modifier;
	ret+="\r\n";
	ret+="Kp: ";
	ret+= ac;

		return ret;
	}


int Bill::getBiggestIdFromDb(CBdeDatabase& dbase)
	{
	int biggest=0;
	if (dbase.GetRecordCount()==0)
		return 0;

	dbase.MoveFirst();
	int tempint=0;

	for (int i=0; i<dbase.GetRecordCount(); i++)
		{
		tempint=dbase.GetFieldAsInteger(dbase.FieldNumberFromName("LaskuNro"),&blank );
		
		if (tempint>biggest)
			biggest=tempint;	
		
		dbase.MoveNext();
		}	

	return biggest;
	}