// PasseliSalesman.h: interface for the PasseliSalesman class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSELISALESMAN_H__3DAE7361_7758_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_PASSELISALESMAN_H__3DAE7361_7758_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;

class PasseliSalesman  
{
private:

unsigned int id;
string name;

public:
	PasseliSalesman();
	virtual ~PasseliSalesman();
	unsigned int getId();
	string getName();
	int findAndLoadFromFile(const string& dbdir, unsigned int id);
	string toString();
};

#endif // !defined(AFX_PASSELISALESMAN_H__3DAE7361_7758_11D8_80E8_0010A4DF8E4B__INCLUDED_)
