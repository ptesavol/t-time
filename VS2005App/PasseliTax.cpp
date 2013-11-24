// PasseliTax.cpp: implementation of the PasseliTax class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "BdeInserter.h"
#include "PasseliTax.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PasseliTax::PasseliTax()
{
}

PasseliTax::~PasseliTax()
{
}

double PasseliTax::getPercent()
	{
	return this->percent.getValue();
	}

string PasseliTax::getDescription()
	{
	return this->description;
	}

int PasseliTax::findAndLoadFromFile(const string& dbdir, unsigned short tid)
	{
	string taxfilename=dbdir.substr(0,dbdir.length()-4);
	taxfilename+="alv.man";
	FILE* taxfile=fopen(taxfilename.c_str(), "r");

	char buf[35];
	int i=0;

	while (fread(buf,1,35, taxfile)==35)
		{
		if(tid==i)
			{
			this->percent.setValue(buf);
			this->description=string(buf+7,0,buf[6]);
			fclose(taxfile); 
			return 0;
			}
		}
	
	if (tid==0)
		{
		this->percent.setValue((double)0);
		this->description="";
		}

	if (tid==1)
		{
		this->percent.setValue((double)22);
		this->description="Alv 22%";
		}
	if (tid==2)
		{
		this->percent.setValue((double)17);
		this->description="Alv 17%";
		}
	if (tid==3)
		{
		this->percent.setValue((double)8);
		this->description="Alv 8%";
		}
	if (tid==4)
		{
		this->percent.setValue((double)0);
		this->description="Alv 0%";
		}
	
	fclose(taxfile); 
	return 1;
	}