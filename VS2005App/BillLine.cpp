// BillLine.cpp: implementation of the BillLine class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4786)
#include "stdafx.h"
#include "BdeInserter.h"
#include "BillLine.h"
#include "stringhelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BillLine::BillLine(): blank(FALSE), lineNumber(0), reversedVat(0)
{

}

BillLine::BillLine(const BillLine& b)
	{
	blank=b.blank;
	billNumber=b.billNumber;
	lineNumber=b.lineNumber;
	lineType=b.lineType;
	accountCode=b.accountCode;
	productId=b.productId;
	productName=b.productName;
	amount=b.amount;
	unit=b.unit;
	unitPrice=b.unitPrice;
	taxCode=b.taxCode;
	discountPercent=b.discountPercent;
	taxlessPrice=b.taxlessPrice;
	taxedPrice=b.taxedPrice;
	vatAccount=b.vatAccount;
	vatPrice=b.vatPrice;
	vatPercent=b.vatPercent;
	balanceType=b.balanceType;
	targetNumber=b.targetNumber;
	happeningType=b.happeningType;
	ac=b.ac;
	deliveryDate=b.deliveryDate;
	reversedVat=b.reversedVat;
	}

BillLine& BillLine::operator= (const BillLine& b)
	{
	if (this==&b)
		return *this;

	blank=b.blank;
	billNumber=b.billNumber;
	lineNumber=b.lineNumber;
	lineType=b.lineType;
	accountCode=b.accountCode;
	productId=b.productId;
	productName=b.productName;
	amount=b.amount;
	unit=b.unit;
	unitPrice=b.unitPrice;
	taxCode=b.taxCode;
	discountPercent=b.discountPercent;
	taxlessPrice=b.taxlessPrice;
	taxedPrice=b.taxedPrice;
	vatAccount=b.vatAccount;
	vatPrice=b.vatPrice;
	vatPercent=b.vatPercent;
	balanceType=b.balanceType;
	targetNumber=b.targetNumber;
	happeningType=b.happeningType;
	ac=b.ac;
	deliveryDate=b.deliveryDate;
	reversedVat=b.reversedVat;

	return *this;
	}

BillLine::~BillLine()
{

}


int BillLine::getBillNumber()
	{
	return this->billNumber;
	}

int BillLine::getLineNumber()
	{
	return this->lineNumber;
	}
int BillLine::getLineType()
	{
	return this->lineType;
	}
string BillLine::getAccountCode()
	{
	return this->accountCode;
	}
string BillLine::getProductId()
	{
	return this->productId;
	}
string BillLine::getProductName()
	{
	return this->productName;
	}
double BillLine::getAmount()
	{
	return this->amount;
	}
string BillLine::getUnit()
	{
	return this->unit;
	}
double BillLine::getUnitPrice()
	{
	return this->unitPrice;
	}
int BillLine::getTaxCode()
	{
	return this->taxCode;
	}
int BillLine::getRevesedVat()
	{
	return this->reversedVat;
	}
double BillLine::getDiscountPercent()
	{
	return this->discountPercent;
	}
double BillLine::getTaxlessPrice()
	{
	return this->taxlessPrice;
	}
double BillLine::getTaxedPrice()
	{
	return this->taxedPrice;
	}
string BillLine::getVatAccount()
	{
	return this->vatAccount;
	}
double BillLine::getVatPrice()
	{
	return this->vatPrice;
	}
string BillLine::getVatPercent()
	{
	return this->vatPercent;
	}
int BillLine::getBalanceType()
	{
	return this->balanceType;
	}
int BillLine::getTargetNumber()
	{
	return this->targetNumber;
	}
int BillLine::getHappeningType()
	{
	return this->happeningType;
	}
string BillLine::getAc()
	{
	return this->ac;
	}
COleDateTime BillLine::getDeliveryDate()
	{
	return this->deliveryDate;
	}

void BillLine::setBillNumber(int _number)
	{
	this->billNumber=_number;
	}
void BillLine::setLineNumber(int _number)
	{
	this->lineNumber=_number;
	}
void BillLine::setLineType(int _type)
	{
	this->lineType=_type;
	}
void BillLine::setAccountCode(const string& _code)
	{
	this->accountCode=_code;
	}
void BillLine::setProductId(const string& _id)
	{
	this->productId=_id;
	}
void BillLine::setProductName(const string& _name)
	{
	this->productName=_name;
	}
void BillLine::setAmount(double _amount)
	{
	this->amount=_amount;
	}
void BillLine::setUnit(const string& _unit)
	{
	this->unit=_unit;
	}
void BillLine::setUnitPrice(double _price)
	{
	this->unitPrice=_price;
	}
void BillLine::setTaxCode(int _code)
	{
	this->taxCode=_code;
	}
void BillLine::setRevesedVat(int _mode)
	{
	this->reversedVat=_mode;
	}
void BillLine::setDiscountPercent(double _percent)
	{
	this->discountPercent=_percent;
	}
void BillLine::setTaxlessPrice(double _price)
	{
	this->taxlessPrice=_price;
	}
void BillLine::setTaxedPrice(double _price)
	{
	this->taxedPrice=_price;
	}
void BillLine::setVatAccount(const string& _account)
	{
	this->vatAccount=_account;
	}
void BillLine::setVatPrice(double _price)
	{
	this->vatPrice=_price;
	}
void BillLine::setVatPercent(const string& _percent)
	{
	this->vatPercent=_percent;
	}
void BillLine::setBalanceType(int _type)
	{
	this->balanceType=_type;
	}
void BillLine::setTargetNumber(int _number)
	{
	this->targetNumber=_number;
	}
void BillLine::setHappeningType(int _type)
	{
	this->happeningType=_type;
	}
void BillLine::setAc(const string& _ac)
	{
	this->ac=_ac;
	}
void BillLine::setDeliveryDate(const COleDateTime& _date)
	{
	this->deliveryDate=_date;
	}

void BillLine::saveToDb(CBdeDatabase& dbase)
	{
	
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("LaskuNro"), billNumber);
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("RiviNro"),lineNumber );

	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("RiviTyyppi"), lineType);
	dbase.SetFieldAsString(dbase.FieldNumberFromName("TiliNro"), accountCode.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("TuoteTunnus"),productId.c_str());
	dbase.SetFieldAsString(dbase.FieldNumberFromName("TuoteNimi"),productName.c_str());

	dbase.SetFieldAsFloat(dbase.FieldNumberFromName("Maara"),amount);
	dbase.SetFieldAsString(dbase.FieldNumberFromName("Yksikko"),unit.c_str());
	dbase.SetFieldAsFloat(dbase.FieldNumberFromName("AHinta"),unitPrice);
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("VerollisuusKoodi"),taxCode);
	dbase.SetFieldAsFloat(dbase.FieldNumberFromName("AlennusProsentti"),discountPercent );
	dbase.SetFieldAsFloat(dbase.FieldNumberFromName("VerotonSumma"),taxlessPrice);
	dbase.SetFieldAsFloat(dbase.FieldNumberFromName("VerollinenSumma"),taxedPrice );
	dbase.SetFieldAsString(dbase.FieldNumberFromName("ALVTili"),vatAccount.c_str());
	dbase.SetFieldAsFloat(dbase.FieldNumberFromName("ALVSumma"), vatPrice );
	dbase.SetFieldAsString(dbase.FieldNumberFromName("ALVProsentti"), vatPercent.c_str());
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("TaseRyhma"), balanceType);
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("KohdeNumero"), targetNumber);
	dbase.SetFieldAsInteger(dbase.FieldNumberFromName("Tapahtumatyyppi"), happeningType);
	dbase.SetFieldAsString(dbase.FieldNumberFromName("Kp"),ac.c_str());
	dbase.SetFieldAsDate(dbase.FieldNumberFromName("ToimPvm"),deliveryDate);
	if(dbase.FieldNumberFromName("kaannettyVeroV") != 0)
		dbase.SetFieldAsInteger(dbase.FieldNumberFromName("kaannettyVeroV"),reversedVat);
	}

void BillLine::loadFromDb(CBdeDatabase& dbase)
	{
	billNumber = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("LaskuNro"),&blank );

	lineNumber = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("RiviNro"),&blank );

	lineType = dbase.GetFieldAsInteger(dbase.FieldNumberFromName("RiviTyyppi"),&blank );
	accountCode = dbase.GetFieldAsString(dbase.FieldNumberFromName("TiliNro"),&blank );
	productId = dbase.GetFieldAsString(dbase.FieldNumberFromName("TuoteTunnus"),&blank );
	productName = dbase.GetFieldAsString(dbase.FieldNumberFromName("TuoteNimi"),&blank );
	amount=dbase.GetFieldAsFloat(dbase.FieldNumberFromName("Maara"),&blank );
	unit=dbase.GetFieldAsString(dbase.FieldNumberFromName("Yksikko"),&blank );
	unitPrice=dbase.GetFieldAsFloat(dbase.FieldNumberFromName("AHinta"),&blank );
	taxCode= dbase.GetFieldAsInteger(dbase.FieldNumberFromName("VerollisuusKoodi"),&blank );
	discountPercent=dbase.GetFieldAsFloat(dbase.FieldNumberFromName("AlennusProsentti"),&blank );
	taxlessPrice=dbase.GetFieldAsFloat(dbase.FieldNumberFromName("VerotonSumma"),&blank );
	taxedPrice=dbase.GetFieldAsFloat(dbase.FieldNumberFromName("VerollinenSumma"),&blank );
	vatAccount=dbase.GetFieldAsString(dbase.FieldNumberFromName("ALVTili"),&blank );
	vatPrice=dbase.GetFieldAsFloat(dbase.FieldNumberFromName("ALVSumma"),&blank );
	vatPercent=dbase.GetFieldAsString(dbase.FieldNumberFromName("ALVProsentti"),&blank );
	balanceType= dbase.GetFieldAsInteger(dbase.FieldNumberFromName("TaseRyhma"),&blank );
	targetNumber= dbase.GetFieldAsInteger(dbase.FieldNumberFromName("KohdeNumero"),&blank );
	happeningType= dbase.GetFieldAsInteger(dbase.FieldNumberFromName("Tapahtumatyyppi"),&blank );
	ac=dbase.GetFieldAsString(dbase.FieldNumberFromName("Kp"),&blank );
	deliveryDate= dbase.GetFieldAsDate(dbase.FieldNumberFromName("ToimPvm"),&blank );
	if(dbase.FieldNumberFromName("kaannettyVeroV") != 0)
		dbase.GetFieldAsInteger(dbase.FieldNumberFromName("kaannettyVeroV"),&blank);
	}

string BillLine::toString()
	{
	string ret;
	
	ret+="LaskuNro: ";
	ret+=st(billNumber);
	ret+="\r\n";
	ret+="RiviNro: ";
	ret+=hex(lineNumber);
	ret+="\r\n";
	ret+="RiviTyyppi: ";
	ret+=st(lineType);
	ret+="\r\n";
	ret+="TiliNro: ";
	ret+=accountCode;
	ret+="\r\n";
	ret+="TuoteTunnus: ";
	ret+=productId;
	ret+="\r\n";
	ret+="TuoteNimi: ";
	ret+=productName;
	ret+="\r\n";
	ret+="Maara: ";
	ret+=st(amount);
	ret+="\r\n";
	ret+="Yksikko: ";
	ret+=unit;
	ret+="\r\n";
	ret+="AHinta: ";
	ret+=st(unitPrice);
	ret+="\r\n";
	ret+="VerollisuusKoodi: ";	
	ret+=st(taxCode);
	ret+="\r\n";
	ret+="AlennusProsentti: ";	
	ret+=st(discountPercent);
	ret+="\r\n";
	ret+="VerotonSumma: ";	
	ret+=st(taxlessPrice);
	ret+="\r\n";
	ret+="VerollinenSumma: ";	
	ret+=st(taxedPrice);
	ret+="\r\n";
	ret+="ALVTili: ";
	ret+=vatAccount;
	ret+="\r\n";
	ret+="ALVSumma: ";
	ret+=st(vatPrice);
	ret+="\r\n";
	ret+="ALVProsentti: ";
	ret+=vatPercent;
	ret+="\r\n";
	ret+="K‰‰nteinen verovelvollisuus: ";
	ret+=st(reversedVat);
	ret+="\r\n";
	ret+="TaseRyhma: ";	
	ret+=st(balanceType);
	ret+="\r\n";
	ret+="KohdeNumero: ";	
	ret+=st(targetNumber);
	ret+="\r\n";
	ret+="Tapahtumatyyppi: ";	
	ret+=st(happeningType);
	ret+="\r\n";
	ret+="Kp: ";
	ret+=ac;
	ret+="\r\n";
	ret+="ToimPvm: ";
	ret+=deliveryDate;
	ret+="\r\n";
	
	return ret;
	}
