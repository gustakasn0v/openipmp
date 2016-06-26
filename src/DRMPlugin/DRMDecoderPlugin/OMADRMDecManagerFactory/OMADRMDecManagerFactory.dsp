# Microsoft Developer Studio Project File - Name="OMADRMDecManagerFactory" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=OMADRMDecManagerFactory - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OMADRMDecManagerFactory.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OMADRMDecManagerFactory.mak" CFG="OMADRMDecManagerFactory - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OMADRMDecManagerFactory - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OMADRMDecManagerFactory - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OMADRMDecManagerFactory - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Build\Win32\VC6\Release"
# PROP Intermediate_Dir "Build\Win32\VC6\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OMADRMDECMANAGERFACTORY_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../ThreadSyncFactory" /I "../../OpenIPMPKeyManager" /I "../../DRMMessenger" /I "../OMADRMDecCommHandlerFactory" /I "../../PublicCryptoFactory" /I "../../OMADRM/ROAPParser" /I "../../Base64Factory" /I "../../XMLFactory" /I "../../OMADRM/include" /I "../include" /I "../../include" /I "../../OMADRM/OMADRMCommon" /I "../../OMADRM/OMADRMCrypto" /I "../../OMADRM/ROAP" /I "../../CipherFactory" /I "../OMADRMDecryptor" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OMADRMDECMANAGERFACTORY_EXPORTS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41a /d "NDEBUG"
# ADD RSC /l 0x41a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 ..\..\..\..\ext\srtp\lib\win32\VC6\release\SRTPCrypto.lib ..\..\..\..\ext\Crypto++\lib\win32\VC6\release\cryptlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "OMADRMDecManagerFactory - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build\Win32\VC6\Debug"
# PROP Intermediate_Dir "Build\Win32\VC6\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OMADRMDECMANAGERFACTORY_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../ThreadSyncFactory" /I "../../OpenIPMPKeyManager" /I "../../DRMMessenger" /I "../OMADRMDecCommHandlerFactory" /I "../../PublicCryptoFactory" /I "../../OMADRM/ROAPParser" /I "../../Base64Factory" /I "../../XMLFactory" /I "../../OMADRM/include" /I "../include" /I "../../include" /I "../../OMADRM/OMADRMCommon" /I "../../OMADRM/OMADRMCrypto" /I "../../OMADRM/ROAP" /I "../../CipherFactory" /I "../OMADRMDecryptor" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OMADRMDECMANAGERFACTORY_EXPORTS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41a /d "_DEBUG"
# ADD RSC /l 0x41a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\..\ext\srtp\lib\win32\VC6\debug\SRTPCrypto.lib ..\..\..\..\ext\Crypto++\lib\win32\VC6\debug\cryptlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "OMADRMDecManagerFactory - Win32 Release"
# Name "OMADRMDecManagerFactory - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AgentBase.cpp
# End Source File
# Begin Source File

SOURCE=.\AgentROAP.cpp
# End Source File
# Begin Source File

SOURCE=.\FileOMADRMDecAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\OMADRMDecAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\OMADRMDecManager.cpp
# End Source File
# Begin Source File

SOURCE=.\OMADRMDecManagerFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\OMADRMDecryptor.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenIPMPOMADRMDecManager.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AgentBase.h
# End Source File
# Begin Source File

SOURCE=.\AgentROAP.h
# End Source File
# Begin Source File

SOURCE=.\FileOMADRMDecAgent.h
# End Source File
# Begin Source File

SOURCE=.\OMADRMDecAgent.h
# End Source File
# Begin Source File

SOURCE=.\OMADRMDecManager.h
# End Source File
# Begin Source File

SOURCE=.\OMADRMDecManagerFactory.h
# End Source File
# Begin Source File

SOURCE=.\OMADRMDecryptor.h
# End Source File
# Begin Source File

SOURCE=.\OpenIPMPOMADRMDecManager.h
# End Source File
# End Group
# End Target
# End Project
