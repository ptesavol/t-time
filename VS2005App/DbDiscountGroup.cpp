// DbDiscountGroup.cpp: implementation of the DbDiscountGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "DbDiscountGroup.h"
#include <string>
#include "stringhelper.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DbDiscountGroup::DbDiscountGroup():discountPercent(0.0)
{

}

DbDiscountGroup::~DbDiscountGroup()
{

}

double DbDiscountGroup::getDiscountPercent()
	{
	return discountPercent;
	}

void DbDiscountGroup::loadFromDb(CBdeDatabase& dbase)
	{
	discountPercent = dbase.GetFieldAsFloat(dbase.FieldNumberFromName("Alennus"),&blank );
	}

int DbDiscountGroup::findAndLoadFromDb(int customerGroup, int productGroup, CBdeDatabase& dbase)
	{
	//AfxMessageBox(st(customerGroup).c_str());
	//AfxMessageBox(st(productGroup).c_str());

	if (dbase.GetRecordCount()==0)
		return 1;
	dbase.MoveFirst();
	int tempArTunnus;
	int tempTrTunnus;


	for (int i=0; i<dbase.GetRecordCount(); i++)
		{
		tempArTunnus=dbase.GetFieldAsInteger(dbase.FieldNumberFromName("ArTunnus"),&blank );
		tempTrTunnus=dbase.GetFieldAsInteger(dbase.FieldNumberFromName("TrTunnus"),&blank );
		
		if (customerGroup==tempArTunnus && productGroup==tempTrTunnus)
			{
			loadFromDb(dbase);
			return 0;
			}
		dbase.MoveNext();
		}		
	return 1;
	}