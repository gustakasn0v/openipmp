# Microsoft Developer Studio Project File - Name="OpenIPMPMessengerFactory" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=OpenIPMPMessengerFactory - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OpenIPMPMessengerFactory.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenIPMPMessengerFactory.mak" CFG="OpenIPMPMessengerFactory - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenIPMPMessengerFactory - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenIPMPMessengerFactory - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OpenIPMPMessengerFactory - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OPENIPMPMESSENGERFACTORY_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../ext/axis-c/include" /I "../ThreadSyncFactory" /I "../openIPMP" /I "../../client/include" /I "../../../ext/openssl/include" /I "../../../ext/squashxml/include" /I "../../../ext/xerces/include" /I "../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OPENIPMPMESSENGERFACTORY_EXPORTS" /FD /c
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
# ADD LINK32 ../../../ext/xerces/win32/lib/VC6/xerces-c_2.lib ../../../ext/xerces/win32/lib/VC6/xerces-depdom_2.lib ../../../ext/openssl/lib/win32/release/VC6/ssleay32.lib ../../../ext/openssl/lib/win32/release/VC6/libeay32.lib ../../../ext/axis-c/lib/win32/VC6/AxisClient.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "OpenIPMPMessengerFactory - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OPENIPMPMESSENGERFACTORY_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../ext/axis-c/include" /I "../ThreadSyncFactory" /I "../openIPMP" /I "../../client/include" /I "../../../ext/openssl/include" /I "../../../ext/squashxml/include" /I "../../../ext/xerces/include" /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OPENIPMPMESSENGERFACTORY_EXPORTS" /FD /GZ /c
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
# ADD LINK32 ../../../ext/xerces/win32/lib/VC6/xerces-c_2D.lib ../../../ext/xerces/win32/lib/VC6/xerces-depdom_2D.lib ../../../ext/openssl/lib/win32/debug/VC6/ssleay32.lib ../../../ext/openssl/lib/win32/debug/VC6/libeay32.lib ../../../ext/axis-c/lib/win32/VC6/AxisClient_D.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "OpenIPMPMessengerFactory - Win32 Release"
# Name "OpenIPMPMessengerFactory - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\OpenIPMPMessengerFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsCreateUserFault.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsCreateUserRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsCreateUserResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsGetContentKeyFault.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsGetContentKeyRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsGetContentKeyResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsLicenseFault.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsLicenseRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsLicenseResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsOpenIPMPMessenger.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsQueryFault.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsQueryRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsQueryResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentAssignIdentifierFault.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentAssignIdentifierRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentAssignIdentifierResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentExistingIdentifierFault.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentExistingIdentifierRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentExistingIdentifierResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterDigitalItemInstanceFault.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterDigitalItemInstanceRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterDigitalItemInstanceResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterUserFault.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterUserRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterUserResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRightsAuthorizationFault.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRightsAuthorizationRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRightsAuthorizationResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLoginFault.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLoginRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLoginResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLogoutFault.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLogoutRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLogoutResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\OsmsWebService.cpp
# End Source File
# Begin Source File

SOURCE=.\SquashXMLOsmsOpenIPMPMessenger.cpp
# End Source File
# Begin Source File

SOURCE=.\WSOsmsOpenIPMPMessenger.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\OpenIPMPMessengerFactory.h
# End Source File
# Begin Source File

SOURCE=.\OsmsCreateUserFault.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsCreateUserRequest.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsCreateUserResponse.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsGetContentKeyFault.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsGetContentKeyRequest.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsGetContentKeyResponse.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsLicenseFault.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsLicenseRequest.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsLicenseResponse.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsOpenIPMPMessenger.h
# End Source File
# Begin Source File

SOURCE=.\OsmsQueryFault.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsQueryRequest.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsQueryResponse.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentAssignIdentifierFault.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentAssignIdentifierRequest.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentAssignIdentifierResponse.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentExistingIdentifierFault.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentExistingIdentifierRequest.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterContentExistingIdentifierResponse.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterDigitalItemInstanceFault.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterDigitalItemInstanceRequest.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterDigitalItemInstanceResponse.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterUserFault.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterUserRequest.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRegisterUserResponse.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRightsAuthorizationFault.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRightsAuthorizationRequest.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsRightsAuthorizationResponse.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLoginFault.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLoginRequest.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLoginResponse.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLogoutFault.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLogoutRequest.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsUserLogoutResponse.hpp
# End Source File
# Begin Source File

SOURCE=.\OsmsWebService.hpp
# End Source File
# Begin Source File

SOURCE=.\SquashXMLOsmsOpenIPMPMessenger.h
# End Source File
# Begin Source File

SOURCE=.\WSOsmsOpenIPMPMessenger.h
# End Source File
# End Group
# End Target
# End Project
