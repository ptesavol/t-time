// Ipe.h: interface for the Ipe class.
//
#if !defined(AFX_IPE_H__71A6FB43_9DE4_480F_AB75_262C4AAEA314__INCLUDED_)
#define AFX_IPE_H__71A6FB43_9DE4_480F_AB75_262C4AAEA314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#define ITDA_ERR                           0xFFFFFF

class Ipe  
{
public:
	Ipe();
	virtual ~Ipe();

    void setString(LPCSTR);                // asetetaan str
    CString getString();                   // haetaan str

    void setCOleDateTime(COleDateTime);
    COleDateTime getCOleDateTime();
    vector<CString> *getVector();
    int getCols();
    CString getSeparator();
    void setItemData(DWORD);
    DWORD getItemData();
    BOOL isItemData();

    void init(LPCSTR, COleDateTime*, vector<CString>*, int, CString, BOOL);    // Aloitetaan uusi
    void unEdited();                       // Editoimaton, editoitu, hae tila
    void edited();
    BOOL isEdited();
	void setTabbedOut(int flags);
	int getTabbedOut();

    int x;                                 // kontrollin koordinaatit ja koko
    int y;                                 // x ja y ruudun koordinaatteina
    int w;
    int h;

protected:
    CString str;                           // välitetyt/välitettävät arvot
    COleDateTime cOleDateTime;
    vector<CString> *pvect;                  // useita arvoja (rivejä)
    int cols;                                // + arvolla monta sarake
    CString separator;                       // + sarakkeiden erotin
    BOOL bItemData;                          // viimeinen annettu vektorin alkio ItemDataksi (FALSE=ei, TRUE=kyllä)
    DWORD itemdata;                          // : säilö itemdatalle

    BOOL bEdited;                           // Muutettu?
	int tabFlags;							// poistuttu tabilla
};

#endif // !defined(AFX_IPE_H__71A6FB43_9DE4_480F_AB75_262C4AAEA314__INCLUDED_)