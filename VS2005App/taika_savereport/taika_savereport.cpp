// taika_savereport.cpp : Defines the entry point for the application.
//
#define WINVER 0x0400
#define WIN32_LEAN_AND_MEAN
#include <io.h>
#include <afxwin.h>
#include <string>
using namespace std;

#define ERR_OUTOFMEMORY                    1                         // Virheet
#define ERR_READ                           2
#define ERR_COPY                           3

#define NEW_REPORT                         (WM_USER + 1001)          // t-aika -ohjelmalla samat
#define PARAM_TTI                          0
#define PARAM_TTA                          1

#define ERR_TITLE                          "t-aika savereport"

    void luoOrdinal(CString path);
    BOOL luoSaapuneet(CString path, CString filename);

// 9.1.2008 - Jouni Vepsäläinen
// Ohjelma jolla talletetaan saapuvat t-aika -ohjelman raporttitiedostot ../saapuneet -kansioon

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    BOOL b;
    int c, r;
    HWND hwnd;
    char *prb = NULL;
    CFile cfs;
    CFileException cfe;
    TCHAR emsg[MAX_PATH];
    char getpath[MAX_PATH];
    CString path, filename(lpCmdLine), srce_file, dest_file, type, new_name;

	if(lpCmdLine == 0) return 0;
	if(filename.GetAt(0) == '\"') filename = filename.Right(filename.GetLength() - 1);
	if(filename.GetAt(filename.GetLength() - 1) == '\"') filename = filename.Left(filename.GetLength() - 1);
    srce_file = filename;

    // polku raportin tallennukseen
    GetModuleFileName(hInstance, getpath, MAX_PATH);
    path = getpath; c = path.GetLength() - 1;
    while(path[c] != '\\') c--;
    path = path.Left(c + 1);

    // Haetaan argumentista tiedoston nimi
    c = filename.GetLength() - 1;
	while(filename[c] != '\\')
	{ if(c > 0) c--; else break; }
	if(c > 0) filename = filename.Right(filename.GetLength() - c - 1);

    try
	{
      // Luodaan saapuneet kansio jos sitä ei jo ole olemassa
      if(!luoSaapuneet(path, filename)) return 0;

      // Ohjelman juurikansiossa on tiedosto ordinal.dat, josta löytyy järjestysnumero tiedostoille (4 tavua, int).
      luoOrdinal(path);                              // Luodaan jos ei jo löydy

      // Luodaan saapuneet kansioon tallentamista varten uusi tiedostonimi.
      r = 0;
      dest_file = path + "ordinal.dat";              // Yritetään lukea järjestysnumero
      if(cfs.Open(dest_file, CFile::modeReadWrite|CFile::typeBinary, NULL))
	  {
        if((r = cfs.Read(&c, 4)) == 4)                   // luetaan
		{
          c++; cfs.SeekToBegin();                        // kirjoitetaan takaisin yhtä isompana seuraavaa kertaa varten
          cfs.Write(&c, 4);
		}
        cfs.Close();
	  }

      if(r != 4)                                     // Jos luku epäonnistuu, tehdään iso satunnaisluku
	  {
        srand(GetTickCount());
		c = ((rand()%255) << 16) + ((rand()%255) << 8) + rand()%255;
	  }

      // Uusi tiedostonimi
      dest_file.Format("%d", --c);
	  new_name = dest_file + "_" + filename;
	  dest_file = path + "saapuneet\\" + new_name;

      // Kopiointi
      if(!CopyFile(srce_file, dest_file, TRUE)) throw(ERR_COPY);

	  // Yritetään viestiä pääikkunalle (t-aika -ohjelmalle)
      type = dest_file.Right(3);                                     // otetaan tyyppi ylös (välitetään t-ajalle)
      type.MakeUpper();
      if(type == "TTI") c = PARAM_TTI;
      else c = PARAM_TTA;

	  if(!(hwnd = FindWindow("taikadlgclassV2", NULL)))              // Viestinnän edellytys on että löydetään t-ajan luokka
	    b = FALSE;                                                     // ei pysty viestimään
      else
        b = PostMessage(hwnd, NEW_REPORT, c, c);                       // lähetä viesti

      if(!b)                                                         // Viestintä epäonnistui -> näytä kopioinnista tieto
	  {
        filename = "Raportti " + filename + " kopiotiin saapuneet kansioon nimellä " + new_name + ".";  
        MessageBox(NULL, filename, ERR_TITLE, MB_ICONINFORMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }
	}
    catch(CFileException *pcfe)
	{
      pcfe->GetErrorMessage(emsg, MAX_PATH, NULL);                   // Viesti CFileExceptionilta
      path = "Raportin kopiointi saapuneet kansioon epäonnistui\r\n\r\n"; path += emsg; path += "\r\n\r\nYritä poistaa virheen aiheuttaja, ja yritä uudelleen";
      MessageBox(NULL, path, ERR_TITLE, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}
    catch(int err)
	{
      if(err == ERR_OUTOFMEMORY) path = "Raportin kopiointi saapuneet kansioon epäonnistui\r\n\r\nLiian vähän muistia\r\n\r\nYritä vapauttaa muistia (esimerkiksi sulkemalla tarpeettomia ohjelmia), ja yritä uudelleen";
      if(err == ERR_READ) path = "Raportin kopiointi saapuneet kansioon epäonnistui\r\n\r\nTiedoston " + path + " luku epäonnistui";
      if(err == ERR_COPY) path = "Raportin kopiointi saapuneet kansioon epäonnistui\r\n\r\nTiedosto " + path + " on jo olemassa\r\n\r\nTallenna ja/tai muuta tiedosto nimi, ja yritä uudelleen";
      MessageBox(NULL, path, ERR_TITLE, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}

    if(prb) delete [] prb;                                       // Tuhotaan objektit
    if(cfs.m_hFile != CFile::hFileNull) cfs.Close();

    return 0;
}

void luoOrdinal(CString path)
{ // Luo ordinal.dat tiedosto jos sitä ei löydy (arvoksi 0)
    DWORD ordinal, e;
    CString filepath;
    HANDLE hfile = NULL;

    filepath = path + "ordinal.dat";

    // Löytyykö ennestään? Ei luoda uutta jos ei löydy.
    hfile = CreateFile(filepath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    e = GetLastError();
    if(hfile != INVALID_HANDLE_VALUE) CloseHandle(hfile);            // Yritetään sulkea

    if(e == ERROR_SUCCESS || e == ERROR_ACCESS_DENIED || e == ERROR_SHARING_VIOLATION || e == ERROR_PATH_NOT_FOUND)
      return;                                        // Löytyi tai virheellinen polku -> ohitetaan luonti

    // Luo tiedosto -> poistutaan jos ei saa luotua
    if((hfile = CreateFile(filepath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL)) == INVALID_HANDLE_VALUE)
      return;

    // Kirjoitetaan uusi, ei välitetä jos ei saa luotua
    ordinal = 0;
    WriteFile(hfile, &ordinal, 4, &e, NULL);
    CloseHandle(hfile); hfile = NULL;
}

BOOL luoSaapuneet(CString path, CString filename)
{
    DWORD e;
    LPVOID lpMsgBuf;
    WIN32_FIND_DATA fd;
    HANDLE hfile = NULL;
    CString dirpath, cs;

    dirpath = path + "saapuneet\\";
    if((hfile = FindFirstFile(dirpath, &fd)) != INVALID_HANDLE_VALUE)  // Löytyykö kansio
	{
      FindClose(hfile);                                                  // löytyi -> pois
      return TRUE;
	}

    if(GetLastError() == ERROR_PATH_NOT_FOUND)                         // Jos ei ollut jokin virhe, niin luodaan kansio
    {
      if(!CreateDirectory(dirpath, NULL))
	  {
        e = GetLastError();
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, e, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
        cs.Format("Virhekoodi: %d - %s\r\nTiedostoa '%s' ei voida kopioida kansioon 'saapuneet' koska kansiota ei ole ja sen luominen epäonnistui.\r\n\r\nVoit yrittää luoda kansion käsin t-aika ohjelman juurikansioon, ja tämän jälkeen yrittää kopiointia uudelleen.", e, (LPCSTR)lpMsgBuf, filename);
        LocalFree(lpMsgBuf);
        MessageBox(NULL, cs, ERR_TITLE, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
        return FALSE;
	  }
	}

    return TRUE;
}