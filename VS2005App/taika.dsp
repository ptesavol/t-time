# Microsoft Developer Studio Project File - Name="taika" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=taika - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "taika.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "taika.mak" CFG="taika - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "taika - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "taika - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "taika - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40b /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 sqlite3.lib Idapi32m.lib mpr.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "taika - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40b /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Idapi32m.lib mpr.lib sqlite3.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../Debug"

!ENDIF 

# Begin Target

# Name "taika - Win32 Release"
# Name "taika - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AccountinException.cpp
# End Source File
# Begin Source File

SOURCE=.\AccountingException.cpp
# End Source File
# Begin Source File

SOURCE=.\AccountingProgram.cpp
# End Source File
# Begin Source File

SOURCE=.\BankAccount.cpp
# End Source File
# Begin Source File

SOURCE=.\Base64Coder.cpp
# End Source File
# Begin Source File

SOURCE=.\BdeDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\BdeException.cpp
# End Source File
# Begin Source File

SOURCE=.\Bill.cpp
# End Source File
# Begin Source File

SOURCE=.\BillLine.cpp
# End Source File
# Begin Source File

SOURCE=.\Buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DbAccount.cpp
# End Source File
# Begin Source File

SOURCE=.\DbCustomer.cpp
# End Source File
# Begin Source File

SOURCE=.\DbDiscountGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\DbProduct.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSqlite.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAsetukset.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgErittely.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEtsi.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgImport.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLaskutus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLuoUusiTietokanta.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPaivita.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgParseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSiirraAsiakkaat.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSiivoaTietokanta.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSMTP.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUusiRaportti.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVarmuuskopioi.cpp
# End Source File
# Begin Source File

SOURCE=.\GenericChildDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Ipe.cpp
# End Source File
# Begin Source File

SOURCE=.\IpeDlgComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\IpeDlgComboBox2.cpp
# End Source File
# Begin Source File

SOURCE=.\IpeDlgEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\ListctrlRaportit.cpp
# End Source File
# Begin Source File

SOURCE=.\md5.cpp
# End Source File
# Begin Source File

SOURCE=.\NeuvosProgram.cpp
# End Source File
# Begin Source File

SOURCE=.\Paivays.cpp
# End Source File
# Begin Source File

SOURCE=.\Parse.cpp
# End Source File
# Begin Source File

SOURCE=.\PasseliBill.cpp
# End Source File
# Begin Source File

SOURCE=.\PasseliCurrency.cpp
# End Source File
# Begin Source File

SOURCE=.\PasseliCustomer.cpp
# End Source File
# Begin Source File

SOURCE=.\PasseliFloat.cpp
# End Source File
# Begin Source File

SOURCE=.\PasseliLine.cpp
# End Source File
# Begin Source File

SOURCE=.\PasseliPayingCondition.cpp
# End Source File
# Begin Source File

SOURCE=.\PasseliProduct.cpp
# End Source File
# Begin Source File

SOURCE=.\PasseliProgram.cpp
# End Source File
# Begin Source File

SOURCE=.\PasseliSalesman.cpp
# End Source File
# Begin Source File

SOURCE=.\PasseliTax.cpp
# End Source File
# Begin Source File

SOURCE=.\PpageListat.cpp
# End Source File
# Begin Source File

SOURCE=.\PpageRaportit.cpp
# End Source File
# Begin Source File

SOURCE=.\PpageTyomatkat.cpp
# End Source File
# Begin Source File

SOURCE=.\PriceComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\Properties.cpp
# End Source File
# Begin Source File

SOURCE=.\Smtp.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\taika.cpp
# End Source File
# Begin Source File

SOURCE=.\taikaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Tokenizer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AccountinException.h
# End Source File
# Begin Source File

SOURCE=.\AccountingException.h
# End Source File
# Begin Source File

SOURCE=.\AccountingProgram.h
# End Source File
# Begin Source File

SOURCE=.\BankAccount.h
# End Source File
# Begin Source File

SOURCE=.\BdeDatabase.h
# End Source File
# Begin Source File

SOURCE=.\BdeException.h
# End Source File
# Begin Source File

SOURCE=.\BdeInserter.h
# End Source File
# Begin Source File

SOURCE=.\Bill.h
# End Source File
# Begin Source File

SOURCE=.\BillLine.h
# End Source File
# Begin Source File

SOURCE=.\Buffer.h
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DbAccount.h
# End Source File
# Begin Source File

SOURCE=.\DbCustomer.h
# End Source File
# Begin Source File

SOURCE=.\DbDiscountGroup.h
# End Source File
# Begin Source File

SOURCE=.\DbProduct.h
# End Source File
# Begin Source File

SOURCE=.\DbSqlite.h
# End Source File
# Begin Source File

SOURCE=.\defines.h
# End Source File
# Begin Source File

SOURCE=.\DlgAsetukset.h
# End Source File
# Begin Source File

SOURCE=.\DlgErittely.h
# End Source File
# Begin Source File

SOURCE=.\DlgEtsi.h
# End Source File
# Begin Source File

SOURCE=.\DlgImport.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgLaskutus.h
# End Source File
# Begin Source File

SOURCE=.\DlgLuoUusiTietokanta.h
# End Source File
# Begin Source File

SOURCE=.\DlgPaivita.h
# End Source File
# Begin Source File

SOURCE=.\DlgParseInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgSiirraAsiakkaat.h
# End Source File
# Begin Source File

SOURCE=.\DlgSiivoaTietokanta.h
# End Source File
# Begin Source File

SOURCE=.\DlgSMTP.h
# End Source File
# Begin Source File

SOURCE=.\DlgUusiRaportti.h
# End Source File
# Begin Source File

SOURCE=.\DlgVarmuuskopioi.h
# End Source File
# Begin Source File

SOURCE=.\GenericChildDialog.h
# End Source File
# Begin Source File

SOURCE=.\idapi.h
# End Source File
# Begin Source File

SOURCE=.\Ipe.h
# End Source File
# Begin Source File

SOURCE=.\IpeDlgComboBox.h
# End Source File
# Begin Source File

SOURCE=.\IpeDlgComboBox2.h
# End Source File
# Begin Source File

SOURCE=.\IpeDlgEdit.h
# End Source File
# Begin Source File

SOURCE=.\ListctrlRaportit.h
# End Source File
# Begin Source File

SOURCE=".\Ms-idapi.h"
# End Source File
# Begin Source File

SOURCE=.\NeuvosProgram.h
# End Source File
# Begin Source File

SOURCE=.\Paivays.h
# End Source File
# Begin Source File

SOURCE=.\Parse.h
# End Source File
# Begin Source File

SOURCE=.\PasseliBill.h
# End Source File
# Begin Source File

SOURCE=.\PasseliCurrency.h
# End Source File
# Begin Source File

SOURCE=.\PasseliCustomer.h
# End Source File
# Begin Source File

SOURCE=.\PasseliFloat.h
# End Source File
# Begin Source File

SOURCE=.\PasseliLine.h
# End Source File
# Begin Source File

SOURCE=.\PasseliPayingCondition.h
# End Source File
# Begin Source File

SOURCE=.\PasseliProduct.h
# End Source File
# Begin Source File

SOURCE=.\PasseliProgram.h
# End Source File
# Begin Source File

SOURCE=.\PasseliSalesman.h
# End Source File
# Begin Source File

SOURCE=.\PasseliTax.h
# End Source File
# Begin Source File

SOURCE=.\PpageListat.h
# End Source File
# Begin Source File

SOURCE=.\PpageRaportit.h
# End Source File
# Begin Source File

SOURCE=.\PpageTyomatkat.h
# End Source File
# Begin Source File

SOURCE=.\PriceComponent.h
# End Source File
# Begin Source File

SOURCE=.\Properties.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Smtp.h
# End Source File
# Begin Source File

SOURCE=.\StringHelper_luokka.h
# End Source File
# Begin Source File

SOURCE=.\taika.h
# End Source File
# Begin Source File

SOURCE=.\taikaDlg.h
# End Source File
# Begin Source File

SOURCE=.\Tokenizer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\arrowlef.bmp
# End Source File
# Begin Source File

SOURCE=.\res\arrowleft.bmp
# End Source File
# Begin Source File

SOURCE=.\res\arrowright.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\folder.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\taika.ico
# End Source File
# Begin Source File

SOURCE=.\taika.rc
# End Source File
# Begin Source File

SOURCE=.\res\taika.rc2
# End Source File
# End Group
# End Target
# End Project
