// Parse.h: interface for the Parse class.
//
#if !defined(AFX_PARSE_H__B5C66BE5_2E9D_4B0F_BE1F_5109E1941EF4__INCLUDED_)
#define AFX_PARSE_H__B5C66BE5_2E9D_4B0F_BE1F_5109E1941EF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "defines.h"
#include "DbSqlite.h"
#include "Tokenizer.h"
#include "DlgParseInfo.h"

class Parse  
{
public:
	Parse();
	virtual ~Parse();

    void parseSaapuneet(int tila);                        // Parsitaan saapuneet kansion tiedostot
    friend UINT CALLBACK OFNHookProc_Raportti(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    friend UINT CALLBACK OFNHookProc_Listat(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    friend UINT CALLBACK OFNHookProc_Tyomatkat(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);

    BOOL parseTTI(CString, CString, int, DlgParseInfo*); // Parsitaan eri tiedosto-formaatit
    BOOL parseTTA(CString, CString, int, DlgParseInfo*);

    BOOL avaaTTI(HWND hwnd);                             // Tiedosto-operaatiot
    BOOL avaaTTA(HWND hwnd);
    BOOL talletaTTI(HWND hwnd, int mode);
    BOOL talletaTTI_tyomatkat(HWND hwnd, vector <ItemData_travel*> id_vect);
    BOOL talletaTTA(HWND hwnd, CString par_filepath, UINT par_asiakkaat, UINT par_laskuttajat, UINT par_tyotyypit, UINT par_tuotteet, int mode);
    int fileExists(CString filepath, CString samat, DWORD disp);
	CString safe(CString value);

    BOOL cmFile(CString, CString, int);                  // Parsitut raportit siirret‰‰n tai kopiodaan raportit kansioon

    // Tiedosto-operatioille
    int m_mode;
    CString m_laskuttaja;
    CString m_tyontekija;
    UINT m_asiakkaat;
    UINT m_laskuttajat;
    UINT m_tyotyypit;
    UINT m_tuotteet;
};

#endif // !defined(AFX_PARSE_H__B5C66BE5_2E9D_4B0F_BE1F_5109E1941EF4__INCLUDED_)
