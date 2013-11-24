// Paivays.h: interface for the Paivays class.
//
#if !defined(AFX_PAIVAYS_H__08BDCD8B_2D4C_4953_92EF_B5CBFE8698D4__INCLUDED_)
#define AFX_PAIVAYS_H__08BDCD8B_2D4C_4953_92EF_B5CBFE8698D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DbSqlite.h"
#include "defines.h"
#include "Tokenizer.h"

class Paivays  
{
public:
    Paivays();
    virtual ~Paivays();

    CString formatDateTime(CString dateTime, int type);
    vector<int > jarjestaPaivat(CString, CString, int);
    int makeDate(int year, int month, int day);
    vector<int > date2int(CString);
    CString date2string(CString);
    CString date2string(int);
    int makeTime(int hour, int minute);
    CString time2string(CString time);
    CString time2string(int time);
    CString time2filetime(CString);
    pair<CString, CString> str2pair(CString dati);
    pair<int,int> haeMinMax(vector<CString>);
    int cmprDates(CString compare, CString to);
	int cmprDates(int compare, int to);
    int caclTimeDiff(pair<CString, CString> start, pair<CString, CString> end);
	void makeTimesLogical(pair<CString, CString> &pari_s, pair<CString, CString> &pari_e);
	pair <CString, CString> calcEndTime(CString minutes, CString StartDate, CString StartTime);

};

#endif // !defined(AFX_PAIVAYS_H__08BDCD8B_2D4C_4953_92EF_B5CBFE8698D4__INCLUDED_)
