// PasseliFloat.cpp: implementation of the PasseliFloat class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "BdeInserter.h"
#include "PasseliFloat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PasseliFloat::PasseliFloat()
{
}

PasseliFloat::~PasseliFloat()
{
}

void PasseliFloat::setValue(double v)
	{
	this->value=v;
	}

void PasseliFloat::setValue(char* data)
	{
	
	unsigned char vieritys=*data;
	vieritys=vieritys-2;
	int bias=vieritys-127;
	bias=bias+1023;
	unsigned int ylaosa=bias;
	ylaosa=ylaosa<<20;

	unsigned short* uspointer=reinterpret_cast<unsigned short*>(data+4);
	unsigned short temp;
	temp=*uspointer;

	unsigned int buffer=temp;

//etsitään etumerkki
	buffer=buffer>>15;
	buffer=buffer<<31;
	ylaosa=ylaosa|buffer;
	buffer=0;

	temp=temp<<1;
	temp=temp>>1;

	buffer=temp;
	buffer=buffer<<5;
	ylaosa=ylaosa|buffer;


	unsigned char t=*(data+3);
	t=t&0x0f;
	ylaosa=ylaosa|t;

	t=*(data+3);
	unsigned int alaosa;
	t=t>>4;
	alaosa=alaosa|t;
	uspointer=reinterpret_cast<unsigned short*>(data+1);
	temp=*uspointer;
	buffer=0;
	buffer=temp;
	buffer=buffer<<4;
	alaosa=alaosa|buffer;
	
	unsigned int dest[2];
	dest[0]=alaosa;
	dest[1]=ylaosa;

	double* ddpointer=reinterpret_cast<double*>(dest);
	this->value=*ddpointer;
	}

void PasseliFloat::writeData(char* target)
	{
	unsigned int* iipointer=(unsigned int*) (&this->value)+4;
	unsigned int epoksi=*iipointer;
	iipointer=(unsigned int*) &this->value;
	unsigned int liima=*iipointer;

	//asetetaan etumerkki mantissaan

	unsigned int mantissa=epoksi;
	mantissa=mantissa>>31;
	mantissa=mantissa<<31;


//lasketaan eksponentti ja biasoidaan se 


	int tint=epoksi;
	tint=tint<<1;
	tint=tint>>1;
	tint=tint>>20;
	tint=tint-1023;
	int kiva=tint;
	tint=tint+129;
	unsigned char bb=tint;
	unsigned char bufferbyte=tint;
	*target=bufferbyte;
	//WriteUByte(kohde,bufferbyte);	//eksponentti on hoidossa

//lasketaan mantissan alkuosan arvo

	unsigned int buf=epoksi;
	buf=buf<<12;
	buf=buf>>1;
	mantissa=mantissa|buf;


	buf=liima;
	buf=buf>>21;
	mantissa=mantissa|buf;

//mantissa on valmis
	unsigned int* iibuf=reinterpret_cast<unsigned int*>(target+2);
	(*iibuf)=mantissa;
	//WriteUInt(kohde+2,mantissa);

//kirjoitataan vähiten merkitsevä tavu
	liima=liima<<11;
	liima=liima>>24;
	bufferbyte=liima;
	*(target+1)=bufferbyte;
	//WriteUByte(kohde+1,bufferbyte);
	}

string PasseliFloat::toString()
	{
	char ccbuf[6];
	unsigned int* iipointer=(unsigned int*) (&this->value)+4;
	unsigned int epoksi=*iipointer;
	iipointer=(unsigned int*) &this->value;
	unsigned int liima=*iipointer;

	//asetetaan etumerkki mantissaan

	unsigned int mantissa=epoksi;
	mantissa=mantissa>>31;
	mantissa=mantissa<<31;


//lasketaan eksponentti ja biasoidaan se 


	int tint=epoksi;
	tint=tint<<1;
	tint=tint>>1;
	tint=tint>>20;
	tint=tint-1023;
	int kiva=tint;
	tint=tint+129;
	unsigned char bb=tint;
	unsigned char bufferbyte=tint;
	ccbuf[0]=bufferbyte;
	//WriteUByte(kohde,bufferbyte);	//eksponentti on hoidossa

//lasketaan mantissan alkuosan arvo

	unsigned int buf=epoksi;
	buf=buf<<12;
	buf=buf>>1;
	mantissa=mantissa|buf;

	buf=liima;
	buf=buf>>21;
	mantissa=mantissa|buf;

//mantissa on valmis
	unsigned int* iibuf=(unsigned int*)ccbuf+2;
	(*iibuf)=mantissa;
	//WriteUInt(kohde+2,mantissa);

//kirjoitataan vähiten merkitsevä tavu
	liima=liima<<11;
	liima=liima>>24;
	bufferbyte=liima;
	ccbuf[1]=bufferbyte;
	//WriteUByte(kohde+1,bufferbyte);
	return string(ccbuf,0,6);
	}

double PasseliFloat::getValue()
	{
	return this->value;
	}
