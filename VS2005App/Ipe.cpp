// Ipe.cpp: implementation of the Ipe class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "taika.h"
#include "Ipe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Ipe::Ipe()
{
    str = "";
	itemdata = ITDA_ERR;
}

Ipe::~Ipe()
{}

void Ipe::init(LPCSTR lpcstr, COleDateTime *pcodt, vector<CString> *pvect_, int cols_, CString separator_, BOOL bItemData_)
{ // Alustetaan kaikki
    str = lpcstr;
    if(pcodt)
      cOleDateTime.SetDateTime(pcodt->GetYear(), pcodt->GetMonth(), pcodt->GetDay(), pcodt->GetHour(), pcodt->GetMinute(), pcodt->GetSecond());
    pvect = pvect_;
    cols = cols_;
    separator = separator_;
    bItemData = bItemData_;

    unEdited();
}

//////////////////////////////////////////////////////////////////////
// String member functions
//////////////////////////////////////////////////////////////////////
void Ipe::setString(LPCSTR lpcstr)
{ // Asetetaan
    edited();

    str = lpcstr;
}

CString Ipe::getString()
{ // Haetaan
    return str;
}

//////////////////////////////////////////////////////////////////////
// COLEDateTime member functions
//////////////////////////////////////////////////////////////////////
void Ipe::setCOleDateTime(COleDateTime codt)
{ // Asetetaan COleDateTime
    edited();

    cOleDateTime.SetDateTime(codt.GetYear(), codt.GetMonth(), codt.GetDay(), codt.GetHour(), codt.GetMinute(), codt.GetSecond());
}

COleDateTime Ipe::getCOleDateTime()
{ // Haetaan COleDateTime
    return cOleDateTime;
}

//////////////////////////////////////////////////////////////////////
// Vector and related member functions
//////////////////////////////////////////////////////////////////////
vector<CString> *Ipe::getVector()
{
    return pvect;
}

int Ipe::getCols()
{
    return cols;
}

CString Ipe::getSeparator()
{
    return separator;
}

//////////////////////////////////////////////////////////////////////
// ItemData related member functions
//////////////////////////////////////////////////////////////////////
void Ipe::setItemData(DWORD id)
{
    itemdata = id;
}

DWORD Ipe::getItemData()
{
    return itemdata;
}

BOOL Ipe::isItemData()
{
    return bItemData;
}

//////////////////////////////////////////////////////////////////////
// Edited member functions
//////////////////////////////////////////////////////////////////////
void Ipe::unEdited()
{
    bEdited = FALSE;
	setTabbedOut(0);
}

void Ipe::edited()
{
    bEdited = TRUE;
}

BOOL Ipe::isEdited()
{
    return bEdited;
}

void Ipe::setTabbedOut(int flags)
{
	tabFlags = flags;
}

int Ipe::getTabbedOut()
{
	return tabFlags;
}