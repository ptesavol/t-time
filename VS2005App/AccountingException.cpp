// AccountingException.cpp: implementation of the AccountingException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BdeInserter.h"
#include "AccountingException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AccountingException::AccountingException(const string& reason)
{
this->reason=reason;
}

AccountingException::~AccountingException()
{
}

string AccountingException::getReason()
{
return this->reason;
}