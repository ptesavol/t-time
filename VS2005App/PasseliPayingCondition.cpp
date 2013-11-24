// PasseliPayingCondition.cpp: implementation of the PasseliPayingCondition class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "BdeInserter.h"
#include "PasseliPayingCondition.h"
#include "stringhelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PasseliPayingCondition::PasseliPayingCondition()
{
}

PasseliPayingCondition::~PasseliPayingCondition()
{
}


unsigned short PasseliPayingCondition::getCode()
	{
	return this->code;
	}
unsigned short PasseliPayingCondition::getDiscountedDays()
	{
	return this->discounteddays;
	}
unsigned short PasseliPayingCondition::getDiscountPercent()
	{
	return this->discountpercent;
	}
unsigned short PasseliPayingCondition::getNettoDays()
	{
	return this->nettodays;
	}
string PasseliPayingCondition::getExplanation()
	{
	return this->explanation;
	}

int PasseliPayingCondition::findAndLoadFromFile(const string& dbdir, unsigned short pcode)
	{
	string conditionfilename=dbdir.substr(0,dbdir.length()-4);

	conditionfilename+="mehdot.man";
	FILE* conditionfile=fopen(conditionfilename.c_str(), "r");
	
		
	char buf[39];
			
	int i=0;
	unsigned short* uspointer;
	
	while (fread(buf,1,39, conditionfile)==39)
		{
		
		if(i ==pcode)
			{
			uspointer=reinterpret_cast<unsigned short*>(buf);
			this->discounteddays=*uspointer;
			uspointer=reinterpret_cast<unsigned short*>(buf+2);
			this->discountpercent=*uspointer;
			uspointer=reinterpret_cast<unsigned short*>(buf+4);
			this->nettodays=*uspointer;
			this->code=i;
			this->explanation=string(buf+7,0,buf[6]);
			fclose(conditionfile); 
			return 0;
			}
		i++;
		}
		
	fclose(conditionfile); 
	
	if (pcode==0)
		{
		this->discounteddays=0;
		this->discountpercent=0;
		this->nettodays=0;
		this->code=pcode;
		this->explanation="Käteinen";
		}
	
	if (pcode==1)
		{
		this->discounteddays=0;
		this->discountpercent=0;
		this->nettodays=14;
		this->code=pcode;
		this->explanation="Postiennakko";
		}
	
	if (pcode==2)
		{
		this->discounteddays=0;
		this->discountpercent=0;
		this->nettodays=14;
		this->code=pcode;
		this->explanation="14 pv netto";
		}
	
	if (pcode==3)
		{
		this->discounteddays=15;
		this->discountpercent=2;
		this->nettodays=30;
		this->code=pcode;
		this->explanation="14-2% tai 30 pv netto";
		}

	return 1;	

	}


string PasseliPayingCondition::toString()
	{
	string ret;
	ret+="code: ";
	ret+=st(code);
	ret+="\r\n";
	ret+="discounteddays: ";
	ret+=st(discounteddays);
	ret+="\r\n";
	ret+="discountedpercent: ";
	ret+=st(discountpercent);
	ret+="\r\n";
	ret+="nettodays: ";
	ret+=st(nettodays);
	ret+="\r\n";
	ret+="explanation: ";
	ret+=explanation;
	return ret;
	}
