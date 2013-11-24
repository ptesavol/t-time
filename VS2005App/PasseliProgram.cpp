// PasseliProgram.cpp: implementation of the PasseliProgram class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4786)
#include "stdafx.h"
#include "PasseliProgram.h"
#include "PasseliLine.h"
#include "PasseliCustomer.h"
#include "PasseliBill.h"
#include "PasseliCurrency.h"
#include "PasseliSalesman.h"
#include "PasseliPayingCondition.h"
#include "PasseliProduct.h"
#include "PasseliTax.h"
#include "defines.h"
#include "Props.h"

#include <stdio.h>
#include <string>
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PasseliProgram::PasseliProgram()
{

}

PasseliProgram::~PasseliProgram()
{

}

void PasseliProgram::open(const string& databasedir)
	{
	this->dbdir=databasedir;
	}

void PasseliProgram::close() {}
	
// returns accounts as a list of pairs of accountname, accountnumber 

vector<pair<string,string> > PasseliProgram::getBankAccounts() 
		{
		vector<pair<string,string> > retvec;
		pair<string, string> temppair;

		string companyfilename=dbdir;
		companyfilename+="yritys.man";
		FILE* companyfile=fopen(companyfilename.c_str(), "r");

		fseek(companyfile,480,SEEK_SET);

		char buf[41];

		for (int i=0;i<8; i++)
			{
			fread(buf,1,41, companyfile);
			string temp(reinterpret_cast<const char*> (buf+1),0,buf[0]);
			
			if (temp.length()>0)
				{
				if (temp.find(" ")!=-1 && temp.find(" ")< (temp.length()-1))
					{
					temppair.first=temp.substr(0,temp.find(" "));
					temppair.second=temp.substr(temp.find(" ")+1);
					retvec.push_back(temppair);
					}
				}
			
			 }
		
		fclose(companyfile);
		return retvec;
		}
	
	
	 

int PasseliProgram::createBill(const string& customerid,
							vector<PriceComponent>& productvec, 
							const string& bankaccount,
							const COleDateTime& duedate, const string& ourReference,
							const string& yourReference, const string& pricesFrom) 
		{
		
		// haetaan asiakas
		
		PasseliCustomer customer;
		customer.findAndLoadFromFile(this->dbdir, atoi(customerid.c_str()));

		// t‰ytet‰‰n laskun vakiokent‰t
		
		
		PasseliBill bill;
		
		
		SYSTEMTIME sysTime;   //set createddate
		GetSystemTime(&sysTime);
		FILETIME filTime;
		SystemTimeToFileTime(&sysTime,&filTime);
		unsigned short fatDate=0;
		unsigned short fatTime=0;
		FileTimeToDosDateTime(&filTime,&fatDate,&fatTime);	
		bill.setCreatedDate(fatDate);

							//set duedate	
		duedate.GetAsSystemTime(sysTime);
		SystemTimeToFileTime(&sysTime,&filTime);
		fatDate=0;
		FileTimeToDosDateTime(&filTime,&fatDate,&fatTime);	
		bill.setDueDate(fatDate);
	
						


		bill.setCustomerNumber(atoi(customerid.c_str()));	
		PasseliCurrency curr;
		curr.findAndLoadFromFile(dbdir,customer.getCurrencyIndex());
		bill.setCurrencyName(curr.getName());
		bill.setCurrencyValue(curr.getValue());
		bill.setSalesmanNumber(customer.getSalesman());
		bill.setCustomerName(customer.getName1());
		bill.setCustormerName2(customer.getName2());
		bill.setCustomerAddress(customer.getAddress());	
		bill.setCustomerZip(customer.getZipAddress());
		bill.setCustomerCountry(customer.getCountry());
		PasseliSalesman man;
		man.findAndLoadFromFile(dbdir,customer.getSalesman());
		bill.setSalesman(man.getName());
		bill.setYourReference(yourReference);
		bill.setOurReference(ourReference);
		PasseliPayingCondition cond;
		cond.findAndLoadFromFile(dbdir,customer.getPayingConditionIndex());
		bill.setPayingCondition(cond.getExplanation());
		bill.setPayingConditionCode(customer.getPayingConditionIndex());
		bill.setPayingConditionDiscountedDays(cond.getDiscountedDays());
		bill.setPayingConditionDiscountPercent(cond.getDiscountPercent());
		bill.setPayingConditionNettoDays(cond.getNettoDays());

			//set payingconditiondate
		GetSystemTime(&sysTime);
		CTimeSpan span(cond.getNettoDays(),0,0,0);
		CTime curtime(sysTime);
		curtime+=span;
		curtime.GetAsSystemTime(sysTime);
		SystemTimeToFileTime(&sysTime,&filTime);
		fatDate=0;
		FileTimeToDosDateTime(&filTime,&fatDate,&fatTime);	
		bill.setPayingConditionDate(fatDate);


		bill.setSheet(customer.getDefaultForm());
		bill.setCurrencyIndex(customer.getCurrencyIndex());
		bill.setPriceGroupIndex(customer.getPriceGroupIndex());


		double billsum=0;
		double vatsum=0;
		double totalunits=0;
		double taxlesssum=0;
		double weightsum=0;

		for (int i=0; i<productvec.size(); i++)
			{
			totalunits+=productvec.at(i).getAmount();
			PasseliProduct product;
			PasseliLine line;
			product.findAndLoadFromFile(this->dbdir,productvec.at(i).getProductId());
			
			double tunitprice=(double)0;
			double tprice=(double)0;
			if (product.isUseAmountDiscount()==1)
				{
				if (product.getAmountDiscountBPrice() > productvec.at(i).getAmount())
					tunitprice=product.getTaxlessUnitPrice();
				
				if (product.getAmountDiscountBPrice() <= productvec.at(i).getAmount())
					tunitprice=product.getBPrice();
			
				if (product.getAmountDiscountCPrice() <= productvec.at(i).getAmount())
					tunitprice=product.getCPrice();
			
				if (product.getAmountDiscountDPrice() <= productvec.at(i).getAmount())
					tunitprice=product.getCPrice();
				}
			
			else
				{
				
				if (customer.getPriceGroupIndex()==0) 
					{
					tunitprice=product.getTaxlessUnitPrice();
					tunitprice=tunitprice*((100-product.getAmountDiscountAPrice())/100);
					}
				if (customer.getPriceGroupIndex()==1) 
					{
					tunitprice=product.getBPrice();
					tunitprice=tunitprice*((100-product.getAmountDiscountBPrice())/100);
					}
				if (customer.getPriceGroupIndex()==2) 
					{
					tunitprice=product.getCPrice();
					tunitprice=tunitprice*((100-product.getAmountDiscountCPrice())/100);
					}
				if (customer.getPriceGroupIndex()==3) 
					{
					tunitprice=product.getDPrice();
					tunitprice=tunitprice*((100-product.getAmountDiscountDPrice())/100);
					}
				}
			tprice=tunitprice*productvec.at(i).getAmount();
			line.setTaxlessRowPrice(tprice);
			
			taxlesssum+=tprice;
			
			line.setUnitVatIndex(product.getVatIndex());
			
			PasseliTax tax;
			tax.findAndLoadFromFile(this->dbdir,product.getVatIndex());
			line.setUnitVatPercent(tax.getPercent());

			billsum+=tprice*((100+tax.getPercent())/100);  
			vatsum+=tprice*((tax.getPercent())/100);  

			line.setSalesAccountNumber(product.getAcAccount());
			line.setRunningNumber(i);
			line.setProductGroup(product.getProductGroup());
			line.setShelfCode(product.getShelfcode());
			line.setProductName(product.getProductName());
			line.setOrderedAmount(productvec.at(i).getAmount());
			line.setUnitName(product.getUnitName());
			
			line.setDiscountPercent(0);
			
			line.setProvision(product.getSalesmanProvisionPercent());
			line.setAveragePrice(tprice/productvec.at(i).getAmount());
			
			line.useAmountDiscount(product.isUseAmountDiscount());
			
			line.setUnitWeight(product.getWeight()*productvec.at(i).getAmount());
			weightsum+=product.getWeight()*productvec.at(i).getAmount();
			bill.addBillLine(line);
			}
		
		bill.setTotalWeight(weightsum);
		bill.setTaxlessPrice(taxlesssum);
		bill.setVat(vatsum);
		
		bill.setTotalUnits(totalunits);
		
		bill.setVatPercent2((vatsum/billsum)*100);
		
		bill.setVatSum(vatsum);
		bill.setBillSum(billsum);

		
		bill.setDelayIntrest(10);	//??

		bill.setOrderNumber("");
		
		bill.setDAccountNumber(0);
		bill.setBruttoWritedown(0);
		bill.setNumberOfTaxlessRows(0);
		
		
		bill.writeToFile(this->dbdir);
		return 0;	
		}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// For import, 24.10.2008

// returns consecutive duplets: [Tunnus, Nimi]
vector<string> PasseliProgram::getProductGroups()
{
    int indx = 0;
	char buf[25];
    CString cnv;
    FILE* groupfile;
    vector<string> vect;
	string groupfilename = dbdir;
    
	groupfilename += "TUOTE\\ryhmat.tuo";
	groupfile = fopen(groupfilename.c_str(), "rb");

	while(fread(buf,1,25,groupfile) == 25)
	{
       cnv.Format("%d", indx++);
       vect.push_back((LPCSTR)cnv);
       vect.push_back(string(buf+1,0, buf[0]));
	}

    vect.push_back("65535");
    vect.push_back((LPCSTR)Props::i().lang("DEFINES_2"));

	fclose(groupfile);

    return vect;
}

// returns consecutive: [TryhmaTunnus, TuoteNimi, TuoteTunnus, Yksikko, VoHinta, AHinta, ALVKanta]
vector<string> PasseliProgram::getProducts(BOOL bVatGroup)
{
    CString cnv;
    string unitname;
    string productid;
    string productname;
    FILE* extrafile;
    FILE* productfile;
    vector<string> vect;
    PasseliFloat byuprice;
    PasseliFloat sellprice;
    unsigned short vatindex;
    unsigned short productgroupid;
    unsigned short* uspointer;
	char buf[92], extrabuf[256];
    string extrafilename = dbdir;
	string productfilename = dbdir;

	productfilename += "TUOTE\\nimike.tuo";
    extrafilename += "TUOTE\\muutieto.tuo";
	productfile = fopen(productfilename.c_str(), "rb");
    extrafile = fopen(extrafilename.c_str(), "rb");

	while(fread(buf,1,92,productfile) == 92)
	{
		uspointer = reinterpret_cast<unsigned short*>(buf+1);                            // TryhmaTunnus
		productgroupid = *uspointer;

		productname = string(buf+4,0,buf[3]);
        productid = productname.substr(0, productname.find("~"));                        // TuoteTunnus
        productname = productname.substr(productname.find("~") + 1, productname.size()); // TuoteNimi
	
		sellprice.setValue(buf+55);                                                      // AHinta

		vatindex = buf[63];                                                              // ALVKanta

		unitname = string(buf+65,0,buf[64]);                                             // Yksikko

		fread(extrabuf,1,256,extrafile);
		byuprice.setValue(extrabuf+232);                                                 // VoHinta


        if(productname == "" && productid == "" && unitname == "") continue;             // ei tyhji‰ rivej‰

        //
        cnv.Format("%d", productgroupid);
        vect.push_back((LPCSTR)cnv);
        vect.push_back(productname);
        vect.push_back(productid);
        vect.push_back(unitname);
        if(!checkFloat(byuprice.getValue()))
          cnv = "";
        else
          cnv.Format("%.2f", byuprice.getValue());
        vect.push_back((LPCSTR)cnv);
        if(!checkFloat(sellprice.getValue()))
          cnv = "";
        else
          cnv.Format("%.2f", sellprice.getValue());
        vect.push_back((LPCSTR)cnv);
        cnv.Format("%d", vatindex);
        vect.push_back((LPCSTR)cnv);
	}

	fclose(productfile);
    fclose(extrafile);

	return vect;
}

// returns consecutive: [Tunnus, Nimi]
vector<string> PasseliProgram::getCustomerGroups()
{
    int indx = 0;
	char buf[25];
    CString cnv;
    FILE* groupfile;
    vector<string> vect;
	string groupfilename = dbdir;
    
	groupfilename += "ASIAKAS\\ryhmat.asi";
	groupfile = fopen(groupfilename.c_str(), "rb");

	while(fread(buf,1,25,groupfile) == 25)
	{
       cnv.Format("%d", indx++);
       vect.push_back((LPCSTR)cnv);
       vect.push_back(string(buf+1,0, buf[0]));
	}

    vect.push_back("65535");
    vect.push_back((LPCSTR)Props::i().lang("DEFINES_1"));

	fclose(groupfile);

    return vect;

    return vect;
}

// returns consecutive: [Ryhma, Nimi, KatuOs, AsNro, Lisatietoja]
vector<string> PasseliProgram::getCustomers()
{
    BYTE byte;
    char buf[183];
    CString cnv;
    string name1;
    string address;
    int bit, bytepos;
    unsigned int id;
    unsigned int* iddata;
    vector<string> vect;
    FILE* customerfile;
	string customerfilename = dbdir;


	customerfilename += "ASIAKAS\\nimet.asi";
	customerfile = fopen(customerfilename.c_str(), "r");
		
	while(fread(buf,1,183,customerfile) == 183)
	{
		iddata=reinterpret_cast<unsigned int*>(buf+14);
		id = *iddata;
		name1 = string(buf+19,0,buf[18]);
		address = string(buf+85,0,buf[84]);

		if(id == 0 && name1 == "" && address == "") continue; // ei t‰ysin tyhji‰ kortteja - passeli nollaa tyhj‰t, ei poista

        bytepos = 1;
        while(bytepos < 14)
		{
          byte = buf[bytepos++];

          for(bit=0; bit<8; bit++)
		  {
            if((byte&0x01))
			{
              cnv.Format("%d", (bytepos - 2) * 8 + bit);
              vect.push_back((LPCSTR)cnv);
              vect.push_back(name1);
              vect.push_back(address);
              cnv.Format("%d", id);
              vect.push_back((LPCSTR)cnv);
              vect.push_back("");
			}

			byte >>= 1;
		  }
		}
	}
		
	fclose(customerfile);

    return vect;
}

// returns consecutive: [N, ALVPro]
vector<string> PasseliProgram::getVatPercents()
{
    vector<string> vect;

    vect.push_back("0");
    vect.push_back("");
    vect.push_back("1");
    vect.push_back("22");
    vect.push_back("2");
    vect.push_back("17");
    vect.push_back("3");
    vect.push_back("8");
    vect.push_back("4");
    vect.push_back("0");

    return vect;
}

BOOL PasseliProgram::checkFloat(double d)
{
    byte dc[8] = { 204, 204, 204, 204, 0, 0, 224, 71 }; // CCCCCCCC0000E047

    if(d == *((double*)dc)) return FALSE;

    return TRUE;
}

BOOL PasseliProgram::isVatGroup()		// 13.8.2010, J.V.
{
	return FALSE;
}