// DbDiscountGroup.h: interface for the DbDiscountGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBDISCOUNTGROUP_H__14139730_9791_4445_BD5F_08278CD1A723__INCLUDED_)
#define AFX_DBDISCOUNTGROUP_H__14139730_9791_4445_BD5F_08278CD1A723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BdeDatabase.h"
#include <string>

using namespace std;

class DbDiscountGroup  
{
private: 
	double discountPercent;
	BOOL blank;	

public:
	DbDiscountGroup();
	virtual ~DbDiscountGroup();
	

	double getDiscountPercent();
	void loadFromDb(CBdeDatabase& dbase);
	int findAndLoadFromDb(int customerGroup, int productGroup, CBdeDatabase& dbase);
};

#endif // !defined(AFX_DBDISCOUNTGROUP_H__14139730_9791_4445_BD5F_08278CD1A723__INCLUDED_)
