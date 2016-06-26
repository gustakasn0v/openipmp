# Microsoft Developer Studio Project File - Name="squashxml" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=squashxml - Win32 ReleaseDLL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "squashxml.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "squashxml.mak" CFG="squashxml - Win32 ReleaseDLL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "squashxml - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "squashxml - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "squashxml - Win32 Debug_st" (based on "Win32 (x86) Static Library")
!MESSAGE "squashxml - Win32 Release_st" (based on "Win32 (x86) Static Library")
!MESSAGE "squashxml - Win32 DebugDLL" (based on "Win32 (x86) Static Library")
!MESSAGE "squashxml - Win32 ReleaseDLL" (based on "Win32 (x86) Static Library")
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
# PROP Output_Dir "obj\Release"
# PROP Intermediate_Dir "obj\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /I "../xerces/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\squashxml_dll.lib"

!ELSEIF  "$(CFG)" == "squashxml - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj\Debug"
# PROP Intermediate_Dir "obj\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "include" /I "../xerces/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\squashxmlD.lib"

!ELSEIF  "$(CFG)" == "squashxml - Win32 Debug_st"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "squashxml___Win32_Debug_st"
# PROP BASE Intermediate_Dir "squashxml___Win32_Debug_st"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj\Debug_st"
# PROP Intermediate_Dir "obj\Debug_st"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "include" /I "ext/xerces/win32/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /W3 /GX /Z7 /Od /I "include" /I "../xerces/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib\squashxml_st.lib"
# ADD LIB32 /nologo /out:"lib\squashxmlD_st.lib"

!ELSEIF  "$(CFG)" == "squashxml - Win32 Release_st"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "squashxml___Win32_Release_st"
# PROP BASE Intermediate_Dir "squashxml___Win32_Release_st"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj\Release_st"
# PROP Intermediate_Dir "obj\Release_st"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "include" /I "ext/xerces/win32/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "include" /I "../xerces/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib\squashxml_st.lib"
# ADD LIB32 /nologo /out:"lib\squashxml_st.lib"

!ELSEIF  "$(CFG)" == "squashxml - Win32 DebugDLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "squashxml___Win32_DebugDLL"
# PROP BASE Intermediate_Dir "squashxml___Win32_DebugDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj\Debug_dll"
# PROP Intermediate_Dir "obj\Debug_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "include" /I "../xerces/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib\squashxmlD.lib"
# ADD LIB32 /nologo /out:"lib\squashxmlD_dll.lib"

!ELSEIF  "$(CFG)" == "squashxml - Win32 ReleaseDLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "squashxml___Win32_ReleaseDLL"
# PROP BASE Intermediate_Dir "squashxml___Win32_ReleaseDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj\Release_dll"
# PROP Intermediate_Dir "obj\Release_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "include" /I "../xerces/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"lib\squashxmlD.lib"
# ADD LIB32 /nologo /out:"lib\squashxml_dll.lib"

!ENDIF 

# Begin Target

# Name "squashxml - Win32 Release"
# Name "squashxml - Win32 Debug"
# Name "squashxml - Win32 Debug_st"
# Name "squashxml - Win32 Release_st"
# Name "squashxml - Win32 DebugDLL"
# Name "squashxml - Win32 ReleaseDLL"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "xml"

# PROP Default_Filter ""
# Begin Group "datatype"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\squashxml\xml\datatype\DataTypeAttribute.h
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\xml\datatype\DataTypeBinaryHex.h
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\xml\datatype\DataTypeByteArray.h
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\xml\datatype\DataTypeCharArray.h
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\xml\datatype\DataTypeCodex.h
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\xml\datatype\DataTypeDate.h
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\xml\datatype\DataTypeInt.h
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\xml\datatype\DataTypeLong.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\xml\XMLDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\xml\XMLDocument.h
# End Source File
# Begin Source File

SOURCE=.\src\xml\XMLMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\xml\XMLMessage.h
# End Source File
# Begin Source File

SOURCE=.\src\xml\XMLMessageBean.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\xml\XMLMessageBean.h
# End Source File
# End Group
# Begin Group "tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\squashxml\tools\ByteArray.h
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\tools\Date.h
# End Source File
# Begin Source File

SOURCE=.\src\tools\FileLogger.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\tools\FileLogger.h
# End Source File
# Begin Source File

SOURCE=.\src\tools\FileTool.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\tools\FileTool.h
# End Source File
# Begin Source File

SOURCE=.\src\tools\HashMap.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\tools\HashMap.h
# End Source File
# Begin Source File

SOURCE=.\src\tools\Logger.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\tools\Logger.h
# End Source File
# Begin Source File

SOURCE=.\src\tools\RFC1521Base64.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\tools\RFC1521Base64.h
# End Source File
# End Group
# Begin Group "socket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\socket\BlockingClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\socket\BlockingClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\src\socket\BlockingSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\socket\BlockingSocket.h
# End Source File
# Begin Source File

SOURCE=.\src\socket\HTTPTunnelClient.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\socket\HTTPTunnelClient.h
# End Source File
# Begin Source File

SOURCE=.\src\socket\MessageContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\socket\MessageContainer.h
# End Source File
# Begin Source File

SOURCE=.\src\socket\SquashXMLServletClient.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\socket\SquashXMLServletClient.h
# End Source File
# End Group
# Begin Group "example"

# PROP Default_Filter ""
# Begin Group "xmldoc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\example\xmldoc\XMLDocDOIKernel.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\example\xmldoc\XMLDocDOIKernel.h
# End Source File
# Begin Source File

SOURCE=.\src\example\xmldoc\XMLDocLicenseODRL.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\example\xmldoc\XMLDocLicenseODRL.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\example\XMLMessageExampleBase.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\example\XMLMessageExampleBase.h
# End Source File
# Begin Source File

SOURCE=.\src\example\XMLMessageGenericError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\example\XMLMessageGenericError.h
# End Source File
# Begin Source File

SOURCE=.\src\example\XMLMessageWhatDayOfWeek.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\example\XMLMessageWhatDayOfWeek.h
# End Source File
# Begin Source File

SOURCE=.\src\example\XMLMessageWhatDayOfWeekResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\include\squashxml\example\XMLMessageWhatDayOfWeekResponse.h
# End Source File
# End Group
# End Group
# End Target
# End Project
