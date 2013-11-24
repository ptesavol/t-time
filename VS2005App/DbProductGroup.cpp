// DbProductGroup.cpp: implementation of the DbProductGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "parseres.h"
#include "DbProductGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DbProductGroup::DbProductGroup()
{

}

DbProductGroup::~DbProductGroup()
{

}

void DbProductGroup::setName(const string& _name)
	{
	this->name=_name;
	}

string DbProductGroup::getName()
	{
	return this->name;
	} 

void DbProductGroup::setId(const string& _code)
	{
	this->id=_code;
	}

string DbProductGroup::getId()
	{
	return this->id;
	} 
