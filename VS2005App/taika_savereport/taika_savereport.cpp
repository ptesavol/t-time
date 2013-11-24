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

// 9.1.2008 - Jouni Veps�l�inen
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
      // Luodaan saapuneet kansio jos sit� ei jo ole olemassa
      if(!luoSaapuneet(path, filename)) return 0;

      // Ohjelman juurikansiossa on tiedosto ordinal.dat, josta l�ytyy j�rjestysnumero tiedostoille (4 tavua, int).
      luoOrdinal(path);                              // Luodaan jos ei jo l�ydy

      // Luodaan saapuneet kansioon tallentamista varten uusi tiedostonimi.
      r = 0;
      dest_file = path + "ordinal.dat";              // Yritet��n lukea j�rjestysnumero
      if(cfs.Open(dest_file, CFile::modeReadWrite|CFile::typeBinary, NULL))
	  {
        if((r = cfs.Read(&c, 4)) == 4)                   // luetaan
		{
          c++; cfs.SeekToBegin();                        // kirjoitetaan takaisin yht� isompana seuraavaa kertaa varten
          cfs.Write(&c, 4);
		}
        cfs.Close();
	  }

      if(r != 4)                                     // Jos luku ep�onnistuu, tehd��n iso satunnaisluku
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

	  // Yritet��n viesti� p��ikkunalle (t-aika -ohjelmalle)
      type = dest_file.Right(3);                                     // otetaan tyyppi yl�s (v�litet��n t-ajalle)
      type.MakeUpper();
      if(type == "TTI") c = PARAM_TTI;
      else c = PARAM_TTA;

	  if(!(hwnd = FindWindow("taikadlgclassV2", NULL)))              // Viestinn�n edellytys on ett� l�ydet��n t-ajan luokka
	    b = FALSE;                                                     // ei pysty viestim��n
      else
        b = PostMessage(hwnd, NEW_REPORT, c, c);                       // l�het� viesti

      if(!b)                                                         // Viestint� ep�onnistui -> n�yt� kopioinnista tieto
	  {
        filename = "Raportti " + filename + " kopiotiin saapuneet kansioon nimell� " + new_name + ".";  
        MessageBox(NULL, filename, ERR_TITLE, MB_ICONINFORMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }
	}
    catch(CFileException *pcfe)
	{
      pcfe->GetErrorMessage(emsg, MAX_PATH, NULL);                   // Viesti CFileExceptionilta
      path = "Raportin kopiointi saapuneet kansioon ep�onnistui\r\n\r\n"; path += emsg; path += "\r\n\r\nYrit� poistaa virheen aiheuttaja, ja yrit� uudelleen";
      MessageBox(NULL, path, ERR_TITLE, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}
    catch(int err)
	{
      if(err == ERR_OUTOFMEMORY) path = "Raportin kopiointi saapuneet kansioon ep�onnistui\r\n\r\nLiian v�h�n muistia\r\n\r\nYrit� vapauttaa muistia (esimerkiksi sulkemalla tarpeettomia ohjelmia), ja yrit� uudelleen";
      if(err == ERR_READ) path = "Raportin kopiointi saapuneet kansioon ep�onnistui\r\n\r\nTiedoston " + path + " luku ep�onnistui";
      if(err == ERR_COPY) path = "Raportin kopiointi saapuneet kansioon ep�onnistui\r\n\r\nTiedosto " + path + " on jo olemassa\r\n\r\nTallenna ja/tai muuta tiedosto nimi, ja yrit� uudelleen";
      MessageBox(NULL, path, ERR_TITLE, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}

    if(prb) delete [] prb;                                       // Tuhotaan objektit
    if(cfs.m_hFile != CFile::hFileNull) cfs.Close();

    return 0;
}

void luoOrdinal(CString path)
{ // Luo ordinal.dat tiedosto jos sit� ei l�ydy (arvoksi 0)
    DWORD ordinal, e;
    CString filepath;
    HANDLE hfile = NULL;

    filepath = path + "ordinal.dat";

    // L�ytyyk� ennest��n? Ei luoda uutta jos ei l�ydy.
    hfile = CreateFile(filepath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    e = GetLastError();
    if(hfile != INVALID_HANDLE_VALUE) CloseHandle(hfile);            // Yritet��n sulkea

    if(e == ERROR_SUCCESS || e == ERROR_ACCESS_DENIED || e == ERROR_SHARING_VIOLATION || e == ERROR_PATH_NOT_FOUND)
      return;                                        // L�ytyi tai virheellinen polku -> ohitetaan luonti

    // Luo tiedosto -> poistutaan jos ei saa luotua
    if((hfile = CreateFile(filepath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL)) == INVALID_HANDLE_VALUE)
      return;

    // Kirjoitetaan uusi, ei v�litet� jos ei saa luotua
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
    if((hfile = FindFirstFile(dirpath, &fd)) != INVALID_HANDLE_VALUE)  // L�ytyyk� kansio
	{
      FindClose(hfile);                                                  // l�ytyi -> pois
      return TRUE;
	}

    if(GetLastError() == ERROR_PATH_NOT_FOUND)                         // Jos ei ollut jokin virhe, niin luodaan kansio
    {
      if(!CreateDirectory(dirpath, NULL))
	  {
        e = GetLastError();
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, e, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
        cs.Format("Virhekoodi: %d - %s\r\nTiedostoa '%s' ei voida kopioida kansioon 'saapuneet' koska kansiota ei ole ja sen luominen ep�onnistui.\r\n\r\nVoit yritt�� luoda kansion k�sin t-aika ohjelman juurikansioon, ja t�m�n j�lkeen yritt�� kopiointia uudelleen.", e, (LPCSTR)lpMsgBuf, filename);
        LocalFree(lpMsgBuf);
        MessageBox(NULL, cs, ERR_TITLE, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
        return FALSE;
	  }
	}

    return TRUE;
}