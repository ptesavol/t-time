// PasseliCurrency.cpp: implementation of the PasseliCurrency class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "BdeInserter.h"
#include "PasseliCurrency.h"
#include <string>
#include "stringhelper.h"

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
PasseliCurrency::PasseliCurrency()
{
}

PasseliCurrency::~PasseliCurrency()
{
}

string PasseliCurrency::getName()
	{
	return this->currencyName;
	}
double PasseliCurrency::getValue()
	{
	return this->currencyvalue.getValue();
	}
double PasseliCurrency::getValueInEuros()
	{
	return this->currencyvalueineuros.getValue();
	}	
string PasseliCurrency::getLocation()
	{
	return this->location;
	}
unsigned short PasseliCurrency::getValueDate()
	{
	return this->valuedate;
	}

int PasseliCurrency::findAndLoadFromFile(const string& dbdir, unsigned int index)
	{
	string currencyfilename=dbdir.substr(0,dbdir.length()-4);

	currencyfilename+="valuutat.man";
	FILE* currencyfile=fopen(currencyfilename.c_str(), "r");

	char buf[44];
			
	int i=0;
		
	while (fread(buf,1,44, currencyfile)==44)
		{
		if(i== index)
			{
			this->currencyName=string(buf+1,0,buf[0]);
			this->currencyvalue.setValue(buf+5);
			this->currencyvalueineuros.setValue(buf+11);
			this->location=string(buf+18,0,buf[17]);
			unsigned short* uspointer=reinterpret_cast<unsigned short*>(buf+42);
			this->valuedate=*uspointer;
			fclose(currencyfile);
			return 0;
			}
		i++;
		}
	fclose(currencyfile);
	return 1;
	}

string PasseliCurrency::toString()
	{
	string ret="";
	ret+="currencyName: ";
	ret+=currencyName;
	ret+="\r\n";
	ret+="currencyvalue: ";
	ret+=st(currencyvalue.getValue());
	ret+="\r\n";
	ret+="currencyvalueineuros: ";
	ret+=st(currencyvalueineuros.getValue());
	ret+="\r\n";
	ret+="location: ";
	ret+=location;
	ret+="\r\n";
	ret+="valuedate: ";
	ret+=st(valuedate);
	
	return ret;
	}