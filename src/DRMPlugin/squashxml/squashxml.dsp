# Microsoft Developer Studio Project File - Name="squashxml" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=squashxml - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "squashxml.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "squashxml.mak" CFG="squashxml - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "squashxml - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "squashxml - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "squashxml - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Build\Win32\VC6\Release"
# PROP Intermediate_Dir "Build\Win32\VC6\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../ext/squashxml/include" /I "../../../ext/xerces/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "squashxml - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build\Win32\VC6\Debug"
# PROP Intermediate_Dir "Build\Win32\VC6\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../ext/squashxml/include" /I "../../../ext/xerces/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "squashxml - Win32 Release"
# Name "squashxml - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "xml"

# PROP Default_Filter ""
# Begin Group "datatype"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\xml\datatype\DataTypeAttribute.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\xml\datatype\DataTypeBinaryHex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\xml\datatype\DataTypeByteArray.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\xml\datatype\DataTypeCharArray.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\xml\datatype\DataTypeCodex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\xml\datatype\DataTypeDate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\xml\datatype\DataTypeInt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\xml\datatype\DataTypeLong.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\XMLDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\xml\XMLDocument.h
# End Source File
# Begin Source File

SOURCE=.\XMLMessage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\xml\XMLMessage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\src\xml\XMLMessageBean.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\xml\XMLMessageBean.h
# End Source File
# End Group
# Begin Group "tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\tools\ByteArray.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\tools\Date.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\src\tools\FileLogger.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\tools\FileLogger.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\src\tools\FileTool.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\tools\FileTool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\src\tools\HashMap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\tools\HashMap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\src\tools\Logger.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\tools\Logger.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\src\tools\RFC1521Base64.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\tools\RFC1521Base64.h
# End Source File
# End Group
# Begin Group "socket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\ext\squashxml\src\socket\BlockingClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\socket\BlockingClientSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\src\socket\BlockingSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\socket\BlockingSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\src\socket\HTTPTunnelClient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\socket\HTTPTunnelClient.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\src\socket\MessageContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\socket\MessageContainer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\src\socket\SquashXMLServletClient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ext\squashxml\include\squashxml\socket\SquashXMLServletClient.h
# End Source File
# End Group
# End Group
# End Target
# End Project
