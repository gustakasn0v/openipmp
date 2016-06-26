# Microsoft Developer Studio Project File - Name="openipmp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=openipmp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "openipmp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "openipmp.mak" CFG="openipmp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "openipmp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "openipmp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "openipmp - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "OPENSSL_SYSNAME_WIN32" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../client/include" /I "../../../ext/openssl/include" /I "../../../ext/squashxml/include" /I "../../../ext/xerces/include" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "openipmp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "openipmp___Win32_Debug"
# PROP BASE Intermediate_Dir "openipmp___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build\Win32\VC6\Debug"
# PROP Intermediate_Dir "Build\Win32\VC6\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../ThirdParty/openipmp/src/client/include" /I "../../ThirdParty/openipmp/ext/xerces/win32/include" /I "../../ThirdParty/openipmp/ext/openssl/include" /I "../../ThirdParty/openipmp/ext/mpeg4ip/lib/SDL/include" /D "OPENSSL_SYSNAME_WIN32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /I /openssl/include" /I /openssl/include" /I /openssl/include" /GZ " " " /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../client/include" /I "../../../ext/openssl/include" /I "../../../ext/squashxml/include" /I "../../../ext/xerces/include" /D "_DEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /FR /FD /I /openssl/include" /I /openssl/include" /I /openssl/include" /GZ " " " /c
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

# Name "openipmp - Win32 Release"
# Name "openipmp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "busobj"

# PROP Default_Filter ""
# Begin Group "factories"

# PROP Default_Filter "*.h,*.cpp"
# Begin Source File

SOURCE=..\..\client\busobj\factories\AuxData_Factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\factories\AuxData_Factory.h
# End Source File
# Begin Source File

SOURCE=.\DigitalSignature_Factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\factories\DigitalSignature_Factory.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\factories\DOI_Factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\factories\DOI_Factory.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\factories\IPMP_ContentId_Factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\factories\IPMP_ContentId_Factory.h
# End Source File
# Begin Source File

SOURCE=.\KeyTransport_Factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\factories\KeyTransport_Factory.h
# End Source File
# Begin Source File

SOURCE=.\OpenIPMP.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\factories\RightsHost_Factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\factories\RightsHost_Factory.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\client\busobj\AuxData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\AuxData.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\ContentIdentity.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\ContentIdentity.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\DigitalSignature.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\DigitalSignature.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\DOI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\DOI.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\Exception.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\Exception.h
# End Source File
# Begin Source File

SOURCE=.\IPMP_ContentIdentity.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\IPMP_ContentIdentity.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\IPMP_MediaContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\IPMP_MediaContext.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\IPMP_MetaData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\IPMP_MetaData.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\KeyTransport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\KeyTransport.h
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\License.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\MPEGRELLicense.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\MPEGRELLicense.h
# End Source File
# Begin Source File

SOURCE=.\ODRLLicense.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\ODRLLicense.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\RightsHost.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\RightsHost.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\UserContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\UserContext.h
# End Source File
# Begin Source File

SOURCE=..\..\client\busobj\XRMLLicense.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\busobj\XRMLLicense.h
# End Source File
# End Group
# Begin Group "client"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ContentAuthorizationManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\client\ContentAuthorizationManager.h
# End Source File
# Begin Source File

SOURCE=..\..\client\client\ContentRegistrationContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\client\ContentRegistrationContext.h
# End Source File
# End Group
# Begin Group "io"

# PROP Default_Filter ""
# Begin Group "message"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\client\io\message\osmsMessage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessage.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageAcquireUserKeyStoreRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageAcquireUserKeyStoreRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageAcquireUserKeyStoreResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageAcquireUserKeyStoreResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageAcquireUserKeyStoreResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageAcquireUserKeyStoreResponseError.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageCreateUserRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageCreateUserRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageCreateUserResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageCreateUserResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageCreateUserResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageCreateUserResponseError.h
# End Source File
# Begin Source File

SOURCE=..\..\client\io\message\osmsMessageGenericResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageGenericResponseError.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageGetContentKeyRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageGetContentKeyRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageGetContentKeyResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageGetContentKeyResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageGetContentKeyResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageGetContentKeyResponseError.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageLicenseRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageLicenseRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageLicenseResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageLicenseResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageLicenseResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageLicenseResponseError.h
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageLoginRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageLoginResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageLoginResponseError.h
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageLogout.h
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageLogoutRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageLogoutResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageLogoutResponseError.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageQueryRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageQueryRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageQueryResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageQueryResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterContentAssignIdentifierRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterContentAssignIdentifierRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterContentAssignIdentifierResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterContentAssignIdentifierResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterContentAssignIdentifierResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterContentAssignIdentifierResponseError.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterContentExistingIdentifierRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterContentExistingIdentifierRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterContentExistingIdentifierResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterContentExistingIdentifierResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterContentExistingIdentifierResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterContentExistingIdentifierResponseError.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterDigitalItemInstanceRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterDigitalItemInstanceRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterDigitalItemInstanceResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterDigitalItemInstanceResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterDigitalItemInstanceResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterDigitalItemInstanceResponseError.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterUserRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterUserRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterUserResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterUserResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRegisterUserResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRegisterUserResponseError.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRightsAuthorizationRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRightsAuthorizationRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageRightsAuthorizationResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageRightsAuthorizationResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageUnknownRequestResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageUnknownRequestResponseError.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageUserLoginRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageUserLoginRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageUserLoginResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageUserLoginResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageUserLoginResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageUserLoginResponseError.h
# End Source File
# Begin Source File

SOURCE=..\..\client\io\message\osmsMessageUserLogoutRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageUserLogoutRequest.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageUserLogoutResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageUserLogoutResponse.h
# End Source File
# Begin Source File

SOURCE=.\osmsMessageUserLogoutResponseError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\message\osmsMessageUserLogoutResponseError.h
# End Source File
# End Group
# Begin Group "network"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\client\io\network\SecurityManagerProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\io\network\SecurityManagerProxy.h
# End Source File
# End Group
# End Group
# Begin Group "tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\client\tools\MemMan.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\tools\MemMan.h
# End Source File
# Begin Source File

SOURCE=..\..\client\include\tools\OctetString.h
# End Source File
# Begin Source File

SOURCE=..\..\client\tools\OlCharArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\tools\OlCharArray.h
# End Source File
# Begin Source File

SOURCE=..\..\client\include\tools\OlDate.h
# End Source File
# Begin Source File

SOURCE=..\..\client\include\tools\OlLong.h
# End Source File
# Begin Source File

SOURCE=..\..\client\tools\OlMemMan.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\tools\OlMemMan.h
# End Source File
# Begin Source File

SOURCE=..\..\client\tools\OlRaw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\tools\OlRaw.h
# End Source File
# End Group
# Begin Group "crypto"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\client\crypto\CipherContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\crypto\CipherContext.h
# End Source File
# Begin Source File

SOURCE=.\CryptoManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\crypto\CryptoManager.h
# End Source File
# Begin Source File

SOURCE=..\..\client\crypto\HashContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\client\include\crypto\HashContext.h
# End Source File
# End Group
# End Group
# End Target
# End Project
