// PasseliCustomer.cpp: implementation of the PasseliCustomer class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4786)
#include "stdafx.h"
#include "PasseliCustomer.h"
#include "stringhelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PasseliCustomer::PasseliCustomer()
{
}

PasseliCustomer::~PasseliCustomer()
{
}

unsigned int PasseliCustomer::getId()
	{
	return this->id;
	}

string PasseliCustomer::getName1()
	{
	return this->name1;
	}

string PasseliCustomer::getName2()
	{
	return this->name2;
	}

string PasseliCustomer::getAddress()
	{
	return this->address;
	}

string PasseliCustomer::getZipAddress()
	{
	return this->zipaddress;
	}

string PasseliCustomer::getCountry()
	{
	return this->country;
	}

string PasseliCustomer::getVatId()
	{
	return this->vatid;
	}
string PasseliCustomer::getPhoneNumber()
	{
	return this->phonenumber;
	}
string PasseliCustomer::getFaxNumber()
	{
	return this->faxnumber;
	}
string PasseliCustomer::getDefaultReference()
	{
	return this->defaultreference;
	}
string PasseliCustomer::getDefaultForm()
	{
	return this->defaultform;
	}
unsigned short PasseliCustomer::getLastContactDate1()
	{
	return this->lastcontactdate1;
	}
unsigned short PasseliCustomer::getNextContactDate1()
	{
	return this->nextcontactdate1;
	}
string PasseliCustomer::getContactPerson1()
	{
	return this->contactperson1;
	}
string PasseliCustomer::getContactPhone1()
	{
	return this->contactphone1;
	}
unsigned short PasseliCustomer::getLastContactDate2()
	{
	return this->lastcontactdate2;
	}
unsigned short PasseliCustomer::getNextContactDate2()
	{
	return this->nextcontactdate2;
	}
string PasseliCustomer::getContactPerson2()
	{
	return this->contactperson2;
	}
string PasseliCustomer::getContactPhone2()
	{
	return this->contactphone2;
	}
unsigned short PasseliCustomer::getLastContactDate3()
	{
	return this->lastcontactdate3;
	}
unsigned short PasseliCustomer::getNextContactDate3()
	{
	return this->nextcontactdate3;
	}
string PasseliCustomer::getContactPerson3()
	{
	return this->contactperson3;
	}
string PasseliCustomer::getContactPhone3()
	{
	return this->contactphone3;
	}
unsigned char PasseliCustomer::getPayingConditionIndex()
	{
	return this->payingconditionindex;
	}
unsigned char PasseliCustomer::getPriceGroupIndex()
	{
	return this->pricegroupindex;
	}
unsigned char PasseliCustomer::getDeliveryMethodIndex()
	{
	return this->deliverymethodindex;
	}
unsigned char PasseliCustomer::getIsNoticeBills()
	{
	return this->isnoticebills;
	}
unsigned char PasseliCustomer::getIsIntrestBills()
	{
	return this->isintrestbills;
	}
unsigned short PasseliCustomer::getSalesman()
	{
	return this->salesman;
	}
unsigned short PasseliCustomer::getBillingId()
	{
	return this->billingid;
	}
unsigned char PasseliCustomer::getCurrencyIndex()
	{
	return this->currencyindex;
	}
double PasseliCustomer::getCreditLimit()
	{
	return this->creditlimit.getValue();
	}
double PasseliCustomer::getCreditSaldo()
	{
	return this->creditsaldo.getValue();
	}
unsigned char PasseliCustomer::getDomesticIndex()
	{
	return this->domesticindex;
	}


int PasseliCustomer::findAndLoadFromFile(const string& dbdir, unsigned int cid)
	{
	string customerfilename=dbdir;
	customerfilename+="ASIAKAS\\nimet.asi";
	FILE* customerfile=fopen(customerfilename.c_str(), "r");
	
		
	char buf[183];
			
	int i=0;
		
	while (fread(buf,1,183, customerfile)==183 )
		{
		unsigned int* iddata=reinterpret_cast<unsigned int*>(buf+14);
		if (cid== *iddata)	
			{
			this->id=*iddata;
			this->name1=string(buf+19,0,buf[18]);
			this->name2=string(buf+52,0,buf[51]);
			this->address=string(buf+85,0,buf[84]);
			this->zipaddress=string(buf+118,0,buf[117]);
			this->country=string(buf+151,0,buf[150]);
			fclose(customerfile);		
			
			string extrafilename=dbdir;
			extrafilename+="ASIAKAS\\muutieto.asi";
			FILE* extrafile=fopen(extrafilename.c_str(), "r");
			
			char buf2[420];

			fseek(extrafile,420*i,SEEK_SET);
			fread(buf2,1,420,extrafile);
			
			this->domesticindex=buf2[1];
			
			this->vatid=string(buf2+3,0,buf[2]);
			this->phonenumber=string(buf2+20,0,buf[19]);
			this->faxnumber=string(buf2+53,0,buf[52]);
			this->defaultreference=string(buf2+86,0,buf[85]);
			this->defaultform=string(buf2+119,0,buf[118]);
			this->contactperson1=string(buf2+189,0,buf[188]);
			this->contactphone1=string(buf2+222,0,buf[221]);

			unsigned short* uspointer=reinterpret_cast<unsigned short*>(buf2+242);
			this->lastcontactdate1=*uspointer;
			uspointer=reinterpret_cast<unsigned short*>(buf2+244);
			this->nextcontactdate1=*uspointer;

			this->contactperson2=string(buf2+247,0,buf[246]);
			this->contactphone2=string(buf2+280,0,buf[279]);
			uspointer=reinterpret_cast<unsigned short*>(buf2+300);
			this->lastcontactdate2=*uspointer;
			uspointer=reinterpret_cast<unsigned short*>(buf2+302);
			this->nextcontactdate2=*uspointer;
			
			this->contactperson3=string(buf2+305,0,buf[304]);
			this->contactphone3=string(buf2+338,0,buf[337]);
			uspointer=reinterpret_cast<unsigned short*>(buf2+358);
			this->lastcontactdate3=*uspointer;
			uspointer=reinterpret_cast<unsigned short*>(buf2+360);
			this->nextcontactdate3=*uspointer;
			
			this->payingconditionindex=buf2[151];
			this->pricegroupindex=buf2[152];
			this->deliverymethodindex=buf2[153];
			this->isnoticebills=buf2[154];
			this->isintrestbills=buf2[155];
			this->currencyindex=buf2[156];

			this->creditlimit.setValue(buf2+168);
			this->creditsaldo.setValue(buf2+174);

			uspointer=reinterpret_cast<unsigned short*>(buf2+182); 
			this->salesman=*uspointer;
			uspointer=reinterpret_cast<unsigned short*>(buf2+184);
			this->billingid=*uspointer;
			
			fclose(extrafile);
			return 0;
			}	
		i++;
		//string temp(reinterpret_cast<const char*> (buf+1),0,buf[0]);
		}
		
	fclose(customerfile);
	return 1;
	}

string PasseliCustomer::toString()
	{
	string ret;
	
	ret+="id: ";
	ret+=st(id);
	ret+="\r\n";
	ret+="name1: ";
	ret+=name1;
	ret+="\r\n";
	ret+="name2: ";
	ret+=name2;
	ret+="\r\n";
	ret+="address: ";
	ret+=address;
	ret+="\r\n";
	ret+="zipaddress: ";
	ret+=zipaddress;
	ret+="\r\n";
	ret+="country: ";
	ret+=country;
	ret+="\r\n";

	ret+="vatid: ";
	ret+=vatid;
	ret+="\r\n";
	ret+="phonenumber: ";
	ret+=phonenumber;
	ret+="\r\n";
	ret+="faxnumber: ";
	ret+=faxnumber;
	ret+="\r\n";
	ret+="defaultreference: ";
	ret+=defaultreference;
	ret+="\r\n";
	ret+="defaultform: ";
	ret+=defaultform;
	ret+="\r\n";
	ret+="lastcontactdate1: ";
	ret+=st(lastcontactdate1);
	ret+="\r\n";
	ret+="nextcontactdate1: ";
	ret+=st(nextcontactdate1);
	ret+="\r\n";
	ret+="contactperson1: ";
	ret+=contactperson1;
	ret+="\r\n";
	ret+="contactphone1: ";
	ret+=contactphone1;
	ret+="\r\n";
	ret+="lastcontactdate2: ";
	ret+=st(lastcontactdate2);
	ret+="\r\n";
	ret+="nextcontactdate2: ";
	ret+=st(nextcontactdate2);
	ret+="\r\n";
	ret+="contactperson2: ";
	ret+=contactperson2;
	ret+="\r\n";
	ret+="contactphone2: ";
	ret+=contactphone2;
	ret+="\r\n";
	ret+="lastcontactdate3: ";
	ret+=st(lastcontactdate3);
	ret+="\r\n";
	ret+="nextcontactdate3: ";
	ret+=st(nextcontactdate3);
	ret+="\r\n";
	ret+="contactperson3: ";
	ret+=contactperson3;
	ret+="\r\n";
	ret+="contactphone3: ";
	ret+=contactphone3;
	ret+="\r\n";
	ret+="payingconditionindex: ";
	ret+=st((int)payingconditionindex);
	ret+="\r\n";
	
	ret+="pricegroupindex: ";
	ret+=st((int)pricegroupindex);
	ret+="\r\n";
	ret+="deliverymethodindex: ";
	ret+=st((int)deliverymethodindex);
	ret+="\r\n";
	ret+="isnoticebills: ";
	ret+=st((int)isnoticebills);
	ret+="\r\n";
	ret+="isintrestbills: ";
	ret+=st((int)isintrestbills);
	ret+="\r\n";
	ret+="salesman: ";
	ret+=st(salesman);
	ret+="\r\n";
	ret+="billingid: ";
	ret+=st(billingid);
	ret+="\r\n";
	ret+="currencyindex: ";
	ret+=st((int)currencyindex);
	ret+="\r\n";
	ret+="creditlimit: ";
	ret+=st(creditlimit.getValue());
	ret+="\r\n";
	ret+="creditsaldo: ";
	ret+=st(creditsaldo.getValue());
	ret+="\r\n";
	ret+="domesticindex: ";
	ret+=st(domesticindex);
	ret+="\r\n";
	return ret;
	}