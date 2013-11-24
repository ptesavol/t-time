// PasseliSalesman.cpp: implementation of the PasseliSalesman class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "BdeInserter.h"
#include "PasseliSalesman.h"
#include "stringhelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PasseliSalesman::PasseliSalesman()
{
}

PasseliSalesman::~PasseliSalesman()
{
}

unsigned int PasseliSalesman::getId()
	{
	return this->id;
	}

string PasseliSalesman::getName()
	{
	return this->name;
	}

int PasseliSalesman::findAndLoadFromFile(const string& dbdir, unsigned int sid)
	{
	string salesmanfilename=dbdir;

	salesmanfilename+="\\myyja\\nimet.myy";
	FILE* salesmanfile=fopen(salesmanfilename.c_str(), "r");

	char buf[145];
			
	int i=0;
	unsigned int* ulpointer;
	
	while (fread(buf,1,145, salesmanfile)==145)
		{
		ulpointer=reinterpret_cast<unsigned int*>(buf+3);
		if(sid ==*ulpointer)
			{
			this->id=*ulpointer;
			this->name=string(buf+8,0,buf[7]);
			fclose(salesmanfile); 
			return 0;
			}
		}
		
	fclose(salesmanfile); 
	return 1;
	}

string PasseliSalesman::toString()
	{
	string ret;
	ret+="id: ";
	ret+=st(id);
	ret+="\r\n";
	ret+="name: ";
	ret+=name;
	return ret;
	}
