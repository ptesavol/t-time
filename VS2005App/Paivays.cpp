// Paivays.cpp: implementation of the Paivays class.
//
#include "stdafx.h"
#include "taika.h"
#include "Paivays.h"
#include "Props.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////////////////////////////////
Paivays::Paivays()
{}

Paivays::~Paivays()
{}

//////////////////////////////////////////////////////////////////////////////////////////////////
// J�senfunktiot
//////////////////////////////////////////////////////////////////////////////////////////////////
CString Paivays::formatDateTime(CString dateTime, int type)
{  // Palautta tiedoston aikaformaatista - d.m.a h.min  - joko p�iv�yksen tai kellonajan
    CString cs;
    int day, mon, year;
    vector<string> *vect;

    Tokenizer raw(dateTime, dateTime.GetLength(), DATETIME_SEP, "\r");
    vect = raw.getNext();
    if(type == FORMAT_DATE)
	{
      cs = vect->at(0).c_str();            // otetaan dd.mm.yyyy
      Tokenizer bin(cs.GetBuffer(cs.GetLength()), cs.GetLength(), DATE_SEP, "\r");
      // muutetaan 32-bittiseksi kokonaisluvuksi - binaaripositiot: y...y|mmmmm|ddddd, eli 22-bitti� vuodelle|5-bitti� kuukaudelle|5-bitti� p�iv�lle
      vect = bin.getNext();
      day = atoi(vect->at(0).c_str());
      mon = atoi(vect->at(1).c_str());
      year = atoi(vect->at(2).c_str());
      year = makeDate(year, mon, day);         // siirret��n alkamaan oikeista binaaripositioihin ja lasketaan yhteen
      cs.Format("%d", year);                   // muunnetaan merkkijonoksi
	}
    else if(type == FORMAT_TIME)
	{
      cs = vect->at(1).c_str(); cs += "\r";
      Tokenizer bin(cs.GetBuffer(cs.GetLength()), cs.GetLength(), FILE_TIME_SEP, "\r");
      vect = bin.getNext();
      // Muunnetaan 32-bittiseksi kokonaisluvuksi - minuutteja keskiy�st�
      day = makeTime(atoi(vect->at(0).c_str()), atoi(vect->at(1).c_str()));
      cs.Format("%d", day);                    // muunnetaan merkkijonoksi
	}

    return cs;
}

vector<int > Paivays::jarjestaPaivat(CString taulu, CString sarake, int suunta)
{ // j�rjest�� tietyst� taulusta saadut p�iv�ykset nousevaan tai laskevaan j�rjestykseen
    int c, t;
    DbSqlite db;
    vector<int > vect;

    vect = db.haePaivaykset(taulu, sarake);    // Haetaan p�iv�ykset

    int o, i, count = 0, dt;

    count = vect.size();                       // voisi olla nopeampikin algoritmi paikallaan :?
    for(o=0; o<count; o++)
	{
      for(i=o+1; i<count; i++)
	  {
        c = vect[o];
        t = vect[i];

        if(c > t)
		{
          dt = vect.at(o);
          vect.at(o) = vect.at(i);
          vect.at(i) = dt;
		}
	  }
	}

    return vect;
}

int Paivays::makeDate(int year, int month, int day)
{
    return (year << 10) + (month << 5) + day;
}

vector<int > Paivays::date2int(CString date)
{ // erottelee vuoden/kuukauden/paivan annetusta kokonaisluvusta (CString:ss�) - palauttaa vektorin jossa [p�iv�, kuukausi, vuosi]
    vector<int > vect;
    int day;

    day = atoi(date);
	vect.push_back(day&0x1F);              // paiva
    vect.push_back((day>>5)&0x1F);         // kuukausi
    vect.push_back(day>>10);               // vuosi

    return vect;
}

CString Paivays::date2string(int date)
{
    CString cs;
    cs.Format("%d", date);

    return date2string(cs);
}

CString Paivays::date2string(CString date)
{ // erottelee vuoden/kuukauden/paivan annetusta kokonaisluvusta (CString:ss�) - palauttaa stringing p�iv�.kuukausi.vuosi
    int day;
    CString cs;

    day = atoi(date);
    cs.Format("%d%s%d%s%d", day&0x1F, DATE_SEP, (day>>5)&0x1F, DATE_SEP, day>>10);

    return cs;
}

int Paivays::makeTime(int hour, int minute)
{
    return hour * 60 + minute;
}

CString Paivays::time2string(CString time)
{ // muuntaa minuutteja keskiy�st� -kokonaisluvun merkkijonoksi
    int clock;
    CString cs;

    clock = atoi(time);
    cs.Format("%02d%s%02d", clock / 60, TIME_SEP, clock % 60);

    return cs;
}

CString Paivays::time2string(int time)
{ // muuntaa minuutteja keskiy�st� -kokonaisluvun merkkijonoksi
    CString cs;
    cs.Format("%02d%s%02d", time / 60, TIME_SEP, time % 60);
    return cs;
}

CString Paivays::time2filetime(CString time)
{
    int clock;
    CString cs;

    clock = atoi(time);
    cs.Format("%02d%s%02d", clock / 60, FILE_TIME_SEP, clock % 60);

    return cs;
}

pair<CString, CString> Paivays::str2pair(CString dati)
{ // Palauttaa p�iv�yksen ja kellonajan annetusta mjonosta - p�iv�s ja kellonaika tietokannan formaateissa
    CString cs;
    BOOL leap = FALSE;
    COleDateTime codt;
    pair<CString, CString> pari;
    int year, month, day;

    if(!codt.ParseDateTime(dati, LOCALE_NOUSEROVERRIDE, LOCALE_SYSTEM_DEFAULT))
	{
		cs.Format(Props::i().lang("PAIVAYS_1"), dati);
		MessageBox(Props::e().m_pMainWnd->GetSafeHwnd(), cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		pari.first = ""; pari.second = "";
	}
    else
	{
      // www.cs.helsinki.fi/u/tapasane/kurssit/OhjelmoinninPerusteet/Kevat2005/ohperat2.html
      // "Vuodesta 1753 alkaen Suomessa on noudatettu gregoriaanista kalenteria, jossa karkausvuosia ovat kaikki 400:lla jaolliset vuodet sek� lis�ksi 4:ll� jaollisista vuosista ne, jotka eiv�t ole 100:lla jaollisia."
      year = codt.GetYear(); month = codt.GetMonth(); day = codt.GetDay();
      cs.Format("%d", makeDate(year, month, day));
      pari.first = cs;
      cs.Format("%d", codt.GetHour() * 60 + codt.GetMinute());
      pari.second = cs;

      /*if(year % 400 == 0) leap = TRUE;               // estet��n karkausp�iv�n v��rink�ytt� (ParseDateTime est�� t�m�n todenn�k�isesti jo ennen t�nne p��sy�)
      else { if(year % 4 == 0 && year % 100 != 0) leap = TRUE; }
      if(!leap && day == 29 && month == 2) pari.second = "kv";*/
	}

    return pari;
}

pair<int,int> Paivays::haeMinMax(vector<CString> vect)
{  // Hakee annetusta vektorista pienimm�n ja suurimman p�iv�yksen, palauttaa parissa <min,max>
    int i, s, d;
    int min = 0x7FFFFFFF, max = 0;
    pair<int, int> pari;

    s = vect.size();
    for(i=0; i<s; i++)
	{
      d = atoi(vect[i]);

      if(d > max) max = d;
      if(d < min) min = d;
	}

    pari.first = min;
    pari.second = max;

    return pari;
}

int Paivays::cmprDates(CString compare, CString to)
{ // vertaa kahta p�iv�yst� (p�iv�yst� compare p�iv�ykseen to) - palauta: 0=yht�suuret, -1=pienempi, 1=suurempi
    int c, t;

    c = atoi(compare);
    t = atoi(to);

    if(c > t) return 1;
    else if(c < t) return -1;

    return 0;
}

int Paivays::cmprDates(int compare, int to)
{ // vertaa kahta p�iv�yst� (p�iv�yst� compare p�iv�ykseen to) - palauta: 0=yht�suuret, -1=pienempi, 1=suurempi
    if(compare > to) return 1;
    else if(compare < to) return -1;

    return 0;
}

int Paivays::caclTimeDiff(pair<CString, CString> start, pair<CString, CString> end)
{ // palauttaa aikaeron minuutteina kahden eri p�iv�yksen/kellonajan v�lill�
   COleDateTimeSpan codts;
   COleDateTime codt_s, codt_e;
   int r, day_s, day_e, time_s, time_e;

   day_s = atoi(start.first); day_e = atoi(end.first);   // asetetaan alku ja loppu p�iv�t/ajat
   time_s = atoi(start.second); time_e = atoi(end.second);
   codt_s.SetDateTime(day_s >> 10, (day_s >> 5) & 0x1F, day_s & 0x1F, time_s / 60, time_s % 60, 0);
   codt_e.SetDateTime(day_e >> 10, (day_e >> 5) & 0x1F, day_e & 0x1F, time_e / 60, time_e % 60, 0);

   codts.m_span = codt_e.m_dt - codt_s.m_dt;             // : haetaan niiden v�linen aika
   r  = codts.GetDays() * 1440;                          // : p�iv�t, 1440 minuuttia p�iv�ss�
   r += codts.GetHours() * 60;                           // : tunnit
   r += codts.GetMinutes();                              // : minuutit

   return r;
}

void Paivays::makeTimesLogical(pair<CString, CString> &pari_s, pair<CString, CString> &pari_e)
{
	CString cs;

	if(cmprDates(pari_s.first, pari_e.first) > 0)        // aloitusp�iv� lopetusp�iv� suurempi -> vaihdetaan j�rjestys
	{
		cs = pari_s.first; pari_s.first = pari_e.first; pari_e.first = cs;
		cs = pari_s.second; pari_s.second = pari_e.second; pari_e.second = cs;
	}

	if(cmprDates(pari_e.first, pari_s.first) < 0)        // lopetusp�iv� aloitusp�iv�� pienempi > vaihdetaan j�rjestys
	{
		cs = pari_s.first; pari_s.first = pari_e.first; pari_e.first = cs;
		cs = pari_s.second; pari_s.second = pari_e.second; pari_e.second = cs;
	}

	if(cmprDates(pari_s.first, pari_e.first) == 0)       // samat, vertaa kellonaikoja -> aloitusaika lopetusaikaa suurempi -> vaihdetaan j�rjestys.
	{
		if(atoi(pari_s.second) > atoi(pari_e.second))
		{ cs = pari_s.second; pari_s.second = pari_e.second; pari_e.second = cs; }
	}
}

pair<CString, CString> Paivays::calcEndTime(CString minutes, CString StartDate, CString StartTime)
{ // laske annetuista minuuteista ja aloituajasta lopetusaika
    Paivays paivays;
    COleDateTime codt;
    COleDateTimeSpan codts;
    int day, time, hour, min;
    pair <CString, CString> pari;

    day = atoi(StartDate);											 // : aseta aloitusaika
    time = atoi(StartTime);
    codt.SetDateTime(day >> 10, (day >> 5) & 0x1F, day & 0x1F, time / 60, time % 60, 0);

    min = atoi(minutes);                                             // :: ty�aika minuutteina
    day = min / 1440;
    hour = (min - day * 1440) / 60;
    min = min - day * 1440 - hour * 60;
    codts.SetDateTimeSpan(day, hour, min, 0);                        // :: ty�aika spaniin p�ivin�, tunteina ja minuutteina

    codt.m_dt += codts.m_span;                                       // : lis�� span aloitusaikaan -> uusi lopetusaika

    pari.first.Format("%d", paivays.makeDate(codt.GetYear(), codt.GetMonth(), codt.GetDay()));
    pari.second.Format("%d", paivays.makeTime(codt.GetHour(), codt.GetMinute()));

    return pari;                                                     // palauta lopetusaika
}