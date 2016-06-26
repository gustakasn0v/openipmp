# Microsoft Developer Studio Project File - Name="MPEG2IPMPXEncoderTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=MPEG2IPMPXEncoderTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MPEG2IPMPXEncoderTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MPEG2IPMPXEncoderTest.mak" CFG="MPEG2IPMPXEncoderTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MPEG2IPMPXEncoderTest - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "MPEG2IPMPXEncoderTest - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MPEG2IPMPXEncoderTest - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../../ThreadSyncFactory" /I "../../../../XMLFactory" /I "../include" /I "../../include" /I "../../../include" /I "../../../../include" /I "../../MPEG2" /I "../MPEG2IPMPXDRMEncoder" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x41a /d "NDEBUG"
# ADD RSC /l 0x41a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copying DLLs...
PostBuild_Cmds=copy ..\..\..\..\DRMEncoderPlugin\ContentInfoManagerFactory\Build\Win32\VC6\Release\ContentInfoManagerFactory.dll .\Build\Win32\VC6\Release	copy ..\..\..\..\..\..\ext\openssl\lib\win32\release\VC6\libeay32.dll .\Build\Win32\VC6\Release	copy ..\..\..\..\..\..\ext\openssl\lib\win32\release\VC6\ssleay32.dll .\Build\Win32\VC6\Release	copy ..\..\..\..\..\..\ext\xerces\win32\lib\VC6\xerces-c_2_6.dll .\Build\Win32\VC6\Release	copy ..\..\..\..\..\..\ext\xerces\win32\lib\VC6\xerces-depdom_2_6.dll .\Build\Win32\VC6\Release	copy ..\..\..\..\DRMEncoderPlugin\OpenIPMPDRMEncManagerFactory\Build\Win32\VC6\Release\OpenIPMPDRMEncManagerFactory.dll .\Build\Win32\VC6\Release	copy ..\..\..\..\XMLFactory\Build\Win32\VC6\Release\XMLFactory.dll .\Build\Win32\VC6\Release	copy ..\..\..\..\ThreadSyncFactory\Build\Win32\VC6\Release\ThreadSyncFactory.dll .\Build\Win32\VC6\Release	copy ..\..\..\..\OpenIPMPMessengerFactory\Build\Win32\VC6\Release\OpenIPMPMessengerFactory.dll .\Build\Win32\VC6\Release	copy ..\..\..\..\..\..\ext\axis-c\lib\win32\VC6\AxisClient.dll .\Build\Win32\VC6\Release	copy ..\..\..\..\..\..\ext\axis-c\lib\win32\VC6\AxisXMLParser.dll .\Build\Win32\VC6\Release	copy\
    ..\..\..\..\..\..\ext\axis-c\lib\win32\VC6\HTTPChannel.dll .\Build\Win32\VC6\Release	copy ..\..\..\..\..\..\ext\axis-c\lib\win32\VC6\HTTPTransport.dll .\Build\Win32\VC6\Release	copy ..\MPEG2IPMPXDRMEncoder\Build\Win32\VC6\Release\MPEG2IPMPXDRMEncoder.dll .\Build\Win32\VC6\Release	copy ..\OpenIPMPMPEG2IPMPXDRMEncryptor\Build\Win32\VC6\Release\OpenIPMPMPEG2IPMPXDRMEncryptor.dll .\Build\Win32\VC6\Release
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MPEG2IPMPXEncoderTest - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../../ThreadSyncFactory" /I "../../../../XMLFactory" /I "../include" /I "../../include" /I "../../../include" /I "../../../../include" /I "../../MPEG2" /I "../MPEG2IPMPXDRMEncoder" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x41a /d "_DEBUG"
# ADD RSC /l 0x41a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copying DLLs...
PostBuild_Cmds=copy ..\..\..\..\DRMEncoderPlugin\ContentInfoManagerFactory\Build\Win32\VC6\Debug\ContentInfoManagerFactory.dll .\Build\Win32\VC6\Debug	copy ..\..\..\..\..\..\ext\openssl\lib\win32\debug\VC6\libeay32.dll .\Build\Win32\VC6\Debug	copy ..\..\..\..\..\..\ext\openssl\lib\win32\debug\VC6\ssleay32.dll .\Build\Win32\VC6\Debug	copy ..\..\..\..\..\..\ext\xerces\win32\lib\VC6\xerces-c_2_6D.dll .\Build\Win32\VC6\Debug	copy ..\..\..\..\..\..\ext\xerces\win32\lib\VC6\xerces-depdom_2_6D.dll .\Build\Win32\VC6\Debug	copy ..\..\..\..\DRMEncoderPlugin\OpenIPMPDRMEncManagerFactory\Build\Win32\VC6\Debug\OpenIPMPDRMEncManagerFactory.dll .\Build\Win32\VC6\Debug	copy ..\..\..\..\XMLFactory\Build\Win32\VC6\Debug\XMLFactory.dll .\Build\Win32\VC6\Debug	copy ..\..\..\..\ThreadSyncFactory\Build\Win32\VC6\Debug\ThreadSyncFactory.dll .\Build\Win32\VC6\Debug	copy ..\..\..\..\OpenIPMPMessengerFactory\Build\Win32\VC6\Debug\OpenIPMPMessengerFactory.dll .\Build\Win32\VC6\Debug	copy ..\..\..\..\..\..\ext\axis-c\lib\win32\VC6\AxisClient_D.dll .\Build\Win32\VC6\Debug	copy ..\..\..\..\..\..\ext\axis-c\lib\win32\VC6\AxisXMLParser_D.dll .\Build\Win32\VC6\Debug	copy\
   ..\..\..\..\..\..\ext\axis-c\lib\win32\VC6\HTTPChannel_D.dll  .\Build\Win32\VC6\Debug	copy ..\..\..\..\..\..\ext\axis-c\lib\win32\VC6\HTTPTransport_D.dll .\Build\Win32\VC6\Debug	copy ..\MPEG2IPMPXDRMEncoder\Build\Win32\VC6\Debug\MPEG2IPMPXDRMEncoder.dll .\Build\Win32\VC6\Debug	copy ..\OpenIPMPMPEG2IPMPXDRMEncryptor\Build\Win32\VC6\Debug\OpenIPMPMPEG2IPMPXDRMEncryptor.dll .\Build\Win32\VC6\Debug
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "MPEG2IPMPXEncoderTest - Win32 Release"
# Name "MPEG2IPMPXEncoderTest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MPEG2IPMPXEncoder.cpp
# End Source File
# Begin Source File

SOURCE=.\MPEG2IPMPXEncoderTest.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MPEG2IPMPXEncoder.h
# End Source File
# End Group
# End Target
# End Project
