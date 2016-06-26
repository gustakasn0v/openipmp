# Microsoft Developer Studio Project File - Name="openipmp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=openipmp - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "openipmp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "openipmp.mak" CFG="openipmp - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "openipmp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "openipmp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "openipmp - Win32 Release DLL" (based on "Win32 (x86) Static Library")
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
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../ext/xerces/include" /I "./include" /I "../../ext/openssl/include" /I "../../ext/squashxml/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
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
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./include" /I "../../ext/openssl/include" /I "../../ext/squashxml/include" /I "../../ext/xerces/include" /I "../../ext/MPEGRELUpdate3/common" /I "../../ext/MPEGREL/RELLicAuthz" /I "../../ext/MPEGREL/RELLicAuthzDriver" /I "../../ext/MPEGREL/common" /I "../../ext/MSXML 4.0\inc" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /D "_WINDOWS" /D "MPEGREL_SUPPORT" /FD /I /openssl/include" /I /openssl/include" /I /openssl/include" /GZ " " " /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "openipmp - Win32 Release DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "openipmp___Win32_Release_DLL"
# PROP BASE Intermediate_Dir "openipmp___Win32_Release_DLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "openipmp___Win32_Release_DLL"
# PROP Intermediate_Dir "openipmp___Win32_Release_DLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../../ext/xerces/include" /I "./include" /I "../../ext/openssl/include" /I "../../ext/mpeg4ip/lib/SDL/include" /I "../../ext/squashxml/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../ext/xerces/include" /I "./include" /I "../../ext/openssl/include" /I "../../ext/squashxml/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
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
# Name "openipmp - Win32 Release DLL"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "busobj"

# PROP Default_Filter ""
# Begin Group "factories"

# PROP Default_Filter "*.h;*.cpp"
# Begin Source File

SOURCE=.\busobj\factories\AuxData_Factory.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\factories\AuxData_Factory.h
# End Source File
# Begin Source File

SOURCE=.\busobj\factories\DigitalSignature_Factory.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\factories\DigitalSignature_Factory.h
# End Source File
# Begin Source File

SOURCE=.\busobj\factories\DOI_Factory.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\factories\DOI_Factory.h
# End Source File
# Begin Source File

SOURCE=.\busobj\factories\IPMP_ContentId_Factory.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\factories\IPMP_ContentId_Factory.h
# End Source File
# Begin Source File

SOURCE=.\busobj\factories\KeyTransport_Factory.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\factories\KeyTransport_Factory.h
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRightsAuthorizationRequest.h
# End Source File
# Begin Source File

SOURCE=.\busobj\factories\RightsHost_Factory.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\factories\RightsHost_Factory.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\busobj\AuxData.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\AuxData.h
# End Source File
# Begin Source File

SOURCE=.\busobj\ContentIdentity.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\ContentIdentity.h
# End Source File
# Begin Source File

SOURCE=.\busobj\DigitalSignature.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\DigitalSignature.h
# End Source File
# Begin Source File

SOURCE=.\busobj\DOI.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\DOI.h
# End Source File
# Begin Source File

SOURCE=.\busobj\Exception.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\Exception.h
# End Source File
# Begin Source File

SOURCE=.\busobj\IPMP_ContentIdentity.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\IPMP_ContentIdentity.h
# End Source File
# Begin Source File

SOURCE=.\busobj\IPMP_MediaContext.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\IPMP_MediaContext.h
# End Source File
# Begin Source File

SOURCE=.\busobj\IPMP_MetaData.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\IPMP_MetaData.h
# End Source File
# Begin Source File

SOURCE=.\busobj\KeyTransport.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\KeyTransport.h
# End Source File
# Begin Source File

SOURCE=.\busobj\MPEGRELLicense.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\MPEGRELLicense.h
# End Source File
# Begin Source File

SOURCE=.\busobj\ODRLLicense.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\ODRLLicense.h
# End Source File
# Begin Source File

SOURCE=.\busobj\RightsHost.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\RightsHost.h
# End Source File
# Begin Source File

SOURCE=.\busobj\UserContext.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\UserContext.h
# End Source File
# Begin Source File

SOURCE=.\busobj\XRMLLicense.cpp
# End Source File
# Begin Source File

SOURCE=.\include\busobj\XRMLLicense.h
# End Source File
# End Group
# Begin Group "client"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\client\ClientManager.cpp
# End Source File
# Begin Source File

SOURCE=.\include\client\ClientManager.h
# End Source File
# Begin Source File

SOURCE=.\client\ContentAuthorizationManager.cpp
# End Source File
# Begin Source File

SOURCE=.\include\client\ContentAuthorizationManager.h
# End Source File
# Begin Source File

SOURCE=.\client\ContentRegistrationContext.cpp
# End Source File
# Begin Source File

SOURCE=.\include\client\ContentRegistrationContext.h
# End Source File
# Begin Source File

SOURCE=.\client\UserRegistrationManager.cpp
# End Source File
# Begin Source File

SOURCE=.\include\client\UserRegistrationManager.h
# End Source File
# End Group
# Begin Group "io"

# PROP Default_Filter ""
# Begin Group "message"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\io\message\osmsMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessage.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageAcquireUserKeyStoreRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageAcquireUserKeyStoreRequest.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageAcquireUserKeyStoreResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageAcquireUserKeyStoreResponse.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageAcquireUserKeyStoreResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageAcquireUserKeyStoreResponseError.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageCreateUserRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageCreateUserRequest.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageCreateUserResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageCreateUserResponse.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageCreateUserResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageCreateUserResponseError.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageGenericResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageGenericResponseError.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageGetContentKeyRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageGetContentKeyRequest.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageGetContentKeyResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageGetContentKeyResponse.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageGetContentKeyResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageGetContentKeyResponseError.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageLicenseRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageLicenseResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageLicenseResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageLicenseResponseError.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageQueryRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageQueryResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterContentAssignIdentifierRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterContentAssignIdentifierRequest.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterContentAssignIdentifierResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterContentAssignIdentifierResponse.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterContentAssignIdentifierResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterContentAssignIdentifierResponseError.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterContentExistingIdentifierRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterContentExistingIdentifierRequest.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterContentExistingIdentifierResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterContentExistingIdentifierResponse.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterContentExistingIdentifierResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterContentExistingIdentifierResponseError.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterDigitalItemInstanceRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterDigitalItemInstanceRequest.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterDigitalItemInstanceResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterDigitalItemInstanceResponse.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterDigitalItemInstanceResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterDigitalItemInstanceResponseError.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterUserRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterUserRequest.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterUserResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterUserResponse.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRegisterUserResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageRegisterUserResponseError.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRightsAuthorizationRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageRightsAuthorizationResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageUnknownRequestResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageUnknownRequestResponseError.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageUserLoginRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageUserLoginRequest.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageUserLoginResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageUserLoginResponse.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageUserLoginResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageUserLoginResponseError.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageUserLogoutRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageUserLogoutRequest.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageUserLogoutResponse.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageUserLogoutResponse.h
# End Source File
# Begin Source File

SOURCE=.\io\message\osmsMessageUserLogoutResponseError.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\message\osmsMessageUserLogoutResponseError.h
# End Source File
# End Group
# Begin Group "network"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\io\network\SecurityManagerProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\include\io\network\SecurityManagerProxy.h
# End Source File
# End Group
# End Group
# Begin Group "tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tools\MemMan.cpp
# End Source File
# Begin Source File

SOURCE=.\include\tools\MemMan.h
# End Source File
# End Group
# Begin Group "crypto"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\crypto\CipherContext.cpp
# End Source File
# Begin Source File

SOURCE=.\include\crypto\CipherContext.h
# End Source File
# Begin Source File

SOURCE=.\crypto\CryptoManager.cpp
# End Source File
# Begin Source File

SOURCE=.\include\crypto\CryptoManager.h
# End Source File
# Begin Source File

SOURCE=.\crypto\HashContext.cpp
# End Source File
# Begin Source File

SOURCE=.\include\crypto\HashContext.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\tools\OlCharArray.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\OlMemMan.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\OlRaw.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\busobj\License.h
# End Source File
# End Target
# End Project
