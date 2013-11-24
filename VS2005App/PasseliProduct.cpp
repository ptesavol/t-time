// PasseliProduct.cpp: implementation of the PasseliProduct class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "BdeInserter.h"
#include "PasseliProduct.h"
#include "stringhelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
PasseliProduct::PasseliProduct()
{
}

PasseliProduct::~PasseliProduct()
{
}

unsigned short PasseliProduct::getProductGroup()
	{
	return this->productgroup;
	}

string PasseliProduct::getProductName()
	{
	return this->productname;
	}		

double PasseliProduct::getTaxlessUnitPrice()
	{
	return this->taxlessunitprice.getValue();
	}

unsigned short PasseliProduct::getStorageCurrencyIndex()
	{
	return this->storagecurrencyindex;
	}

unsigned short PasseliProduct::getVatIndex()
	{
	return this->vatindex;
	}

string PasseliProduct::getUnitName()
	{
	return this->unitname;
	}

double PasseliProduct::getStorageSaldo()
	{
	return this->storagesaldo.getValue();
	}

double PasseliProduct::getInProductionSaldo()
	{
	return this->inproductionsaldo.getValue();
	}

double PasseliProduct::getAllocatedSaldo()
	{
	return this->allocatedsaldo.getValue();
	}

unsigned short PasseliProduct::getAcAccount()
	{
	return this->acaccount;
	}

//muutieto-tiedosto


double	PasseliProduct::getBPrice()
	{
	return this->bprice.getValue();
	}

double  PasseliProduct::getCPrice()
	{
	return this->cprice.getValue();
	}

double  PasseliProduct::getDPrice()
	{
	return this->dprice.getValue();
	}

double  PasseliProduct::getAmountDiscountAPrice()
	{
	return this->amountdiscountaprice.getValue();
	}

double  PasseliProduct::getAmountDiscountBPrice()
	{
	return this->amountdiscountbprice.getValue();
	}
 
double  PasseliProduct::getAmountDiscountCPrice()
	{
	return this->amountdiscountcprice.getValue();
	} 

double  PasseliProduct::getAmountDiscountDPrice()
	{
	return this->amountdiscountdprice.getValue();
	}

double  PasseliProduct::getAlertLimit()
	{
	return this->alertlimit.getValue();
	}

double  PasseliProduct::getWeight()
	{
	return this->weight.getValue();
	}

string PasseliProduct::getShelfcode()
	{
	return this->shelfcode;
	}

unsigned int PasseliProduct::getSupplierNumber()
	{
	return this->suppliernumber;
	}

double PasseliProduct::getDeliveryUnits()
	{
	return this->deliveryunits.getValue();
	}

double PasseliProduct::getOrderedAmount()
	{
	return this->orderedamount.getValue();
	}

unsigned short PasseliProduct::getOrderDate()
	{
	return this->orderdate;
	}

unsigned char PasseliProduct::isUseAmountDiscount()
{
return this->useAmountDiscount;
 
}

double  PasseliProduct::getSalesmanProvisionPercent()
{
return this->salesmanProvisionPercent.getValue();
}


int PasseliProduct::findAndLoadFromFile(const string& dbdir, const string& pid)
	{
	string productfilename=dbdir;
	productfilename+="TUOTE\\nimike.tuo";
	FILE* productfile=fopen(productfilename.c_str(), "r");
	
		
	char buf[92];
			
	int i=0;
		
	while (fread(buf,1,92, productfile)==92 )
		{
		
		string tempid=string(buf+4,0,buf[3]); 
		tempid=tempid.substr(0,tempid.find("~"));

		if (pid== tempid)	
			{
			
			unsigned short* uspointer=reinterpret_cast<unsigned short*>(buf+1);
			this->productgroup=*uspointer;
			this->productname=string(buf+4,0,buf[3]); 	
			
		
		
			this->taxlessunitprice.setValue(buf+55);
			
			
			this->storagecurrencyindex=buf[61];
			this->vatindex=buf[63];
			this->unitname=string(buf+65,0,buf[64]);	
			this->storagesaldo.setValue(buf+68);
			this->inproductionsaldo.setValue(buf+74);
			this->allocatedsaldo.setValue(buf+80);
			uspointer=reinterpret_cast<unsigned short*>(buf+86);
			this->acaccount=*uspointer;
			fclose(productfile);		

			string extrafilename=dbdir;
			extrafilename+="TUOTE\\muutieto.tuo";
			FILE* extrafile=fopen(extrafilename.c_str(), "r");

			char extrabuf[221];

			fseek(extrafile,221*i,SEEK_SET);
			fread(extrabuf,1,221,extrafile);
			fclose(extrafile);

			this->useAmountDiscount=extrabuf[3];
			this->salesmanProvisionPercent.setValue(extrabuf+213);
			this->bprice.setValue(extrabuf+4);
			this->cprice.setValue(extrabuf+10);
			this->dprice.setValue(extrabuf+16);
			this->amountdiscountaprice.setValue(extrabuf+22); 
			this->amountdiscountbprice.setValue(extrabuf+28); 
			this->amountdiscountcprice.setValue(extrabuf+34); 
			this->amountdiscountdprice.setValue(extrabuf+40); 
			this->alertlimit.setValue(extrabuf+46); 
			this->weight.setValue(extrabuf+52); 
			this->shelfcode=string(extrabuf+59,0,extrabuf[58]);
			unsigned int* ulpointer=reinterpret_cast<unsigned int*>(extrabuf+141);
			this->suppliernumber=*ulpointer;
			this->deliveryunits.setValue(extrabuf+201);
			this->orderedamount.setValue(extrabuf+207);
			uspointer=reinterpret_cast<unsigned short*>(extrabuf+219);
			this->orderdate=*uspointer;
			

			return 0;
			}	
		i++;
		//string temp(reinterpret_cast<const char*> (buf+1),0,buf[0]);
		}
		
	fclose(productfile);
	return 1;
	}

string PasseliProduct::toString()
	{
	string ret="";

	//nimiketiedosto

	ret+="productgroup: ";
	ret+=st(productgroup);
	ret+="\r\n";
	ret+="productname: ";		
	ret+=productname;	
	ret+="\r\n";
	ret+="taxlessunitprice: ";
	ret+=st(taxlessunitprice.getValue());
	ret+="\r\n";
	ret+="storagecurrencyindex: ";
	ret+=st(storagecurrencyindex);
	ret+="\r\n";
	ret+="vatindex: ";
	ret+=st(vatindex);
	ret+="\r\n";
	ret+="unitname: ";
	ret+=unitname;
	ret+="\r\n";
	ret+="storagesaldo: ";
	ret+=st(storagesaldo.getValue());
	ret+="\r\n";
	ret+="inproductionsaldo: ";
	ret+=st(inproductionsaldo.getValue());
	ret+="\r\n";
	ret+="allocatedsaldo: ";
	ret+=st(allocatedsaldo.getValue());
	ret+="\r\n";
	ret+="acaccount: ";
	ret+=st(acaccount);
	ret+="\r\n";
//muutieto-tiedosto


	ret+="bprice: ";
	ret+=st(bprice.getValue());
	ret+="\r\n";
	ret+="cprice: ";
	ret+=st(cprice.getValue());
	ret+="\r\n";
	ret+="dprice: ";
	ret+=st(dprice.getValue());
	ret+="\r\n";
	ret+="amountdiscountaprice: "; 
	ret+=st(amountdiscountaprice.getValue());
	ret+="\r\n";
	ret+="amountdiscountbprice: "; 
	ret+=st(amountdiscountbprice.getValue());
	ret+="\r\n";
	ret+="amountdiscountcprice: "; 
	ret+=st(amountdiscountcprice.getValue());
	ret+="\r\n";
	ret+="amountdiscountdprice: "; 
	ret+=st(amountdiscountdprice.getValue());
	ret+="\r\n";
	ret+="alertlimit: "; 
	ret+=st(alertlimit.getValue());
	ret+="\r\n";
	ret+="weight: "; 
	ret+=st(weight.getValue());
	ret+="\r\n";
	ret+="shelfcode: ";
	ret+=shelfcode;
	ret+="\r\n";
	ret+="suppliernumber: ";
	ret+=st(suppliernumber);
	ret+="\r\n";
	ret+="deliveryunits: ";
	ret+=st(deliveryunits.getValue());
	ret+="\r\n";
	ret+="orderedamount: ";
	ret+=st(orderedamount.getValue());
	ret+="\r\n";
	ret+="orderdate: ";
	ret+=st(orderdate);
	ret+="\r\n";
	
	return ret;
	}