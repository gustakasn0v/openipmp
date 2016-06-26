#
# OpenIPMP Makefile 
# 

EXTERNALS_DIR=../../ext

# SquashXML include and lib paths.
SQUASHXML_DIR=$(EXTERNALS_DIR)/squashxml
SQUASHXML_INCLUDE_DIR=$(SQUASHXML_DIR)/include
SQUASHXML_LIB_DIR=$(SQUASHXML_DIR)/lib
SQUASHXML_LIB_FLAGS= -lsquashxml

# OpenSSL include and lib paths.
OPENSSL_DIR=/usr
OPENSSL_INCLUDE_DIR=$(OPENSSL_DIR)/include
OPENSSL_LIB_DIR=$(EXTERNALS_DIR)/openssl/lib/macosx/static/gcc33_openssl97b
#OPENSSL_LIB_DIR=/Users/chrismollis/openssl-0.9.7b
#OPENSSL_LIB_FLAGS= -lssl -lcrypto

# xerces include and lib paths.
XERCES_DIR=$(EXTERNALS_DIR)/xerces
XERCES_INCLUDE_DIR=$(XERCES_DIR)/include
XERCES_LIB_DIR=$(XERCES_DIR)/macosx/lib
XERCES_LIB_FLAGS= -lxerces-c -lxerces-depdom

# SDL include and lib paths.
SDL_DIR=/opt/local
SDL_INCLUDE_DIR=$(SDL_DIR)/include
SDL_LIB_DIR=$(SDL_DIR)/lib
SDL_LIB_FLAGS= -lSDL

CC=g++

CFLAGS= -g -Wall -fexceptions -flat_namespace -install_name /usr/local/lib/libopenipmp.dylib -DLINUX -DMACOSX -DUNIXSTYLE -DPTHREADS -dynamiclib
#CFLAGS= -g -Wall -fexceptions -DLINUX -DMACOSX -DUNIXSTYLE -DPTHREADS

CCFLAGS= -c -Wno-deprecated

LDFLAGS= \
	-L$(OPENSSL_LIB_DIR) $(OPENSSL_LIB_FLAGS) \
	-L$(XERCES_LIB_DIR) $(XERCES_LIB_FLAGS) \
	-L$(SQUASHXML_LIB_DIR) $(SQUASHXML_LIB_FLAGS) \
	-lSystemStubs 

COMPILE= $(CC) $(CFLAGS) $(CCFLAGS) $(INCLUDE_PARM)

#SDL_INCLUDE_DIR=$(EXTERNALS_DIR)/mpeg4ip/lib/SDL/include

MAIN_INCLUDE_DIR=./include

BUSOBJ_DIR=./busobj
FACTORIES_DIR=./busobj/factories
CLIENT_DIR=./client
CRYPTO_DIR=./crypto
MESSAGE_DIR=./io/message
NETWORK_DIR=./io/network
TOOLS_DIR=./tools

INCLUDE_PARM= -I$(MAIN_INCLUDE_DIR) \
	      -I$(XERCES_INCLUDE_DIR) \
	      -I$(OPENSSL_INCLUDE_DIR) \
	      -I$(SQUASHXML_INCLUDE_DIR)

openipmp: \
		Exception.o \
		ClientManager.o \
		IPMP_MetaData.o \
		ContentIdentity.o \
		IPMP_ContentIdentity.o \
		AuxData.o \
		RightsHost.o \
		DOI.o \
		DigitalSignature.o \
		KeyTransport.o \
		ODRLLicense.o \
		XRMLLicense.o \
		MPEGRELLicense.o \
		IPMP_MediaContext.o \
		UserContext.o \
		DOI_Factory.o \
		AuxData_Factory.o \
		RightsHost_Factory.o \
		IPMP_ContentId_Factory.o \
		DigitalSignature_Factory.o \
		KeyTransport_Factory.o \
		ContentAuthorizationManager.o \
		ContentRegistrationContext.o \
		UserRegistrationManager.o \
		CryptoManager.o \
		CipherContext.o \
		HashContext.o \
		osmsMessage.o \
		osmsMessageGenericResponseError.o \
		osmsMessageUnknownRequestResponseError.o \
		osmsMessageUserLoginRequest.o \
		osmsMessageUserLoginResponse.o \
		osmsMessageUserLoginResponseError.o \
		osmsMessageLicenseRequest.o \
		osmsMessageLicenseResponse.o \
		osmsMessageLicenseResponseError.o \
		osmsMessageUserLogoutRequest.o \
		osmsMessageUserLogoutResponse.o \
		osmsMessageUserLogoutResponseError.o \
		osmsMessageCreateUserRequest.o \
		osmsMessageCreateUserResponse.o \
		osmsMessageCreateUserResponseError.o \
		osmsMessageRegisterUserRequest.o \
		osmsMessageRegisterUserResponse.o \
		osmsMessageRegisterUserResponseError.o \
		osmsMessageRegisterContentAssignIdentifierRequest.o \
		osmsMessageRegisterContentAssignIdentifierResponse.o \
		osmsMessageRegisterContentAssignIdentifierResponseError.o \
		osmsMessageRegisterContentExistingIdentifierRequest.o \
		osmsMessageRegisterContentExistingIdentifierResponse.o \
		osmsMessageRegisterContentExistingIdentifierResponseError.o \
		osmsMessageRegisterDigitalItemInstanceRequest.o \
		osmsMessageRegisterDigitalItemInstanceResponse.o \
		osmsMessageRegisterDigitalItemInstanceResponseError.o \
		osmsMessageAcquireUserKeyStoreRequest.o \
		osmsMessageAcquireUserKeyStoreResponse.o \
		osmsMessageAcquireUserKeyStoreResponseError.o \
		osmsMessageGetContentKeyRequest.o \
		osmsMessageGetContentKeyResponse.o \
		osmsMessageGetContentKeyResponseError.o \
		osmsMessageQueryRequest.o \
		osmsMessageQueryResponse.o \
		SecurityManagerProxy.o \
		osmsMessageRightsAuthorizationResponse.o \
		osmsMessageRightsAuthorizationRequest.o \
		MemMan.o \
		OlCharArray.o \
		OlMemMan.o \
		OlRaw.o
	$(CC) $(CFLAGS) $(INCLUDE_PARM) $(LDFLAGS) $(OPENSSL_LIB_DIR)/libssl.a $(OPENSSL_LIB_DIR)/libcrypto.a -o libopenipmp.dylib \
		Exception.o \
		ClientManager.o \
		UserRegistrationManager.o \
		IPMP_MetaData.o \
		ContentIdentity.o \
		IPMP_ContentIdentity.o \
		AuxData.o \
		RightsHost.o \
		DOI.o \
		DigitalSignature.o \
		KeyTransport.o \
		ODRLLicense.o \
		XRMLLicense.o \
		MPEGRELLicense.o \
		IPMP_MediaContext.o \
		UserContext.o \
		DOI_Factory.o \
		AuxData_Factory.o \
		RightsHost_Factory.o \
		DigitalSignature_Factory.o \
		KeyTransport_Factory.o \
		IPMP_ContentId_Factory.o \
		ContentAuthorizationManager.o \
		ContentRegistrationContext.o \
		CipherContext.o \
		CryptoManager.o \
		HashContext.o \
		osmsMessage.o \
		osmsMessageGenericResponseError.o \
		osmsMessageUnknownRequestResponseError.o \
		osmsMessageUserLoginRequest.o \
		osmsMessageUserLoginResponse.o \
		osmsMessageUserLoginResponseError.o \
		osmsMessageLicenseRequest.o \
		osmsMessageLicenseResponse.o \
		osmsMessageLicenseResponseError.o \
		osmsMessageAcquireUserKeyStoreRequest.o \
		osmsMessageAcquireUserKeyStoreResponse.o \
		osmsMessageAcquireUserKeyStoreResponseError.o \
		osmsMessageUserLogoutRequest.o \
		osmsMessageUserLogoutResponse.o \
		osmsMessageUserLogoutResponseError.o \
		osmsMessageCreateUserRequest.o \
		osmsMessageCreateUserResponse.o \
		osmsMessageCreateUserResponseError.o \
		osmsMessageRegisterUserRequest.o \
		osmsMessageRegisterUserResponse.o \
		osmsMessageRegisterUserResponseError.o \
		osmsMessageRegisterContentAssignIdentifierRequest.o \
		osmsMessageRegisterContentAssignIdentifierResponse.o \
		osmsMessageRegisterContentAssignIdentifierResponseError.o \
		osmsMessageRegisterContentExistingIdentifierRequest.o \
		osmsMessageRegisterContentExistingIdentifierResponse.o \
		osmsMessageRegisterContentExistingIdentifierResponseError.o \
		osmsMessageRegisterDigitalItemInstanceRequest.o \
		osmsMessageRegisterDigitalItemInstanceResponse.o \
		osmsMessageRegisterDigitalItemInstanceResponseError.o \
		osmsMessageGetContentKeyRequest.o \
		osmsMessageGetContentKeyResponse.o \
		osmsMessageGetContentKeyResponseError.o \
		osmsMessageQueryRequest.o \
		osmsMessageQueryResponse.o \
		SecurityManagerProxy.o \
		osmsMessageRightsAuthorizationResponse.o \
		osmsMessageRightsAuthorizationRequest.o \
		MemMan.o \
		OlCharArray.o \
		OlMemMan.o \
		OlRaw.o

Exception.o:
	$(COMPILE) $(BUSOBJ_DIR)/Exception.cpp

IPMP_MetaData.o:
	$(COMPILE) $(BUSOBJ_DIR)/IPMP_MetaData.cpp

ContentIdentity.o:
	$(COMPILE) $(BUSOBJ_DIR)/ContentIdentity.cpp

IPMP_ContentIdentity.o:
	$(COMPILE) $(BUSOBJ_DIR)/IPMP_ContentIdentity.cpp

AuxData.o:
	$(COMPILE) $(BUSOBJ_DIR)/AuxData.cpp

RightsHost.o:
	$(COMPILE) $(BUSOBJ_DIR)/RightsHost.cpp

DOI.o:
	$(COMPILE) $(BUSOBJ_DIR)/DOI.cpp

DigitalSignature.o:
	$(COMPILE) $(BUSOBJ_DIR)/DigitalSignature.cpp

KeyTransport.o:
	$(COMPILE) $(BUSOBJ_DIR)/KeyTransport.cpp

ODRLLicense.o:
	$(COMPILE) $(BUSOBJ_DIR)/ODRLLicense.cpp

XRMLLicense.o:
	$(COMPILE) $(BUSOBJ_DIR)/XRMLLicense.cpp

MPEGRELLicense.o:
	$(COMPILE) $(BUSOBJ_DIR)/MPEGRELLicense.cpp

IPMP_MediaContext.o:
	$(COMPILE) $(BUSOBJ_DIR)/IPMP_MediaContext.cpp

UserContext.o:
	$(COMPILE) $(BUSOBJ_DIR)/UserContext.cpp

DOI_Factory.o:
	$(COMPILE) $(FACTORIES_DIR)/DOI_Factory.cpp

AuxData_Factory.o:
	$(COMPILE) $(FACTORIES_DIR)/AuxData_Factory.cpp

RightsHost_Factory.o:
	$(COMPILE) $(FACTORIES_DIR)/RightsHost_Factory.cpp

DigitalSignature_Factory.o:
	$(COMPILE) $(FACTORIES_DIR)/DigitalSignature_Factory.cpp

KeyTransport_Factory.o:
	$(COMPILE) $(FACTORIES_DIR)/KeyTransport_Factory.cpp

IPMP_ContentId_Factory.o:
	$(COMPILE) $(FACTORIES_DIR)/IPMP_ContentId_Factory.cpp

ClientManager.o:
	$(COMPILE) $(CLIENT_DIR)/ClientManager.cpp

UserRegistrationManager.o:
	$(COMPILE) $(CLIENT_DIR)/UserRegistrationManager.cpp

ContentAuthorizationManager.o:
	$(COMPILE) $(CLIENT_DIR)/ContentAuthorizationManager.cpp

ContentRegistrationContext.o:
	$(COMPILE) $(CLIENT_DIR)/ContentRegistrationContext.cpp

CipherContext.o:
	$(COMPILE) $(CRYPTO_DIR)/CipherContext.cpp

CryptoManager.o:
	$(COMPILE) $(CRYPTO_DIR)/CryptoManager.cpp

HashContext.o:
	$(COMPILE) $(CRYPTO_DIR)/HashContext.cpp

osmsMessage.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessage.cpp

osmsMessageGenericResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageGenericResponseError.cpp

osmsMessageUnknownRequestResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageUnknownRequestResponseError.cpp

osmsMessageLicenseRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageLicenseRequest.cpp

osmsMessageLicenseResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageLicenseResponse.cpp

osmsMessageLicenseResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageLicenseResponseError.cpp

osmsMessageUserLoginRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageUserLoginRequest.cpp

osmsMessageUserLoginResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageUserLoginResponse.cpp

osmsMessageUserLoginResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageUserLoginResponseError.cpp

osmsMessageUserLogoutRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageUserLogoutRequest.cpp

osmsMessageUserLogoutResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageUserLogoutResponse.cpp

osmsMessageUserLogoutResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageUserLogoutResponseError.cpp

osmsMessageAcquireUserKeyStoreRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageAcquireUserKeyStoreRequest.cpp

osmsMessageAcquireUserKeyStoreResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageAcquireUserKeyStoreResponse.cpp

osmsMessageAcquireUserKeyStoreResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageAcquireUserKeyStoreResponseError.cpp

osmsMessageCreateUserRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageCreateUserRequest.cpp

osmsMessageCreateUserResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageCreateUserResponse.cpp

osmsMessageCreateUserResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageCreateUserResponseError.cpp

osmsMessageRegisterUserRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterUserRequest.cpp

osmsMessageRegisterUserResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterUserResponse.cpp

osmsMessageRegisterUserResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterUserResponseError.cpp

osmsMessageRegisterContentAssignIdentifierRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterContentAssignIdentifierRequest.cpp

osmsMessageRegisterContentAssignIdentifierResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterContentAssignIdentifierResponse.cpp

osmsMessageRegisterContentAssignIdentifierResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterContentAssignIdentifierResponseError.cpp

osmsMessageRegisterContentExistingIdentifierRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterContentExistingIdentifierRequest.cpp

osmsMessageRegisterContentExistingIdentifierResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterContentExistingIdentifierResponse.cpp

osmsMessageRegisterContentExistingIdentifierResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterContentExistingIdentifierResponseError.cpp

osmsMessageRegisterDigitalItemInstanceRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterDigitalItemInstanceRequest.cpp

osmsMessageRegisterDigitalItemInstanceResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterDigitalItemInstanceResponse.cpp

osmsMessageRegisterDigitalItemInstanceResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRegisterDigitalItemInstanceResponseError.cpp

osmsMessageQueryRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageQueryRequest.cpp

osmsMessageQueryResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageQueryResponse.cpp

osmsMessageRightsAuthorizationResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRightsAuthorizationResponse.cpp

osmsMessageRightsAuthorizationRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageRightsAuthorizationRequest.cpp

osmsMessageGetContentKeyRequest.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageGetContentKeyRequest.cpp

osmsMessageGetContentKeyResponse.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageGetContentKeyResponse.cpp

osmsMessageGetContentKeyResponseError.o:
	$(COMPILE) $(MESSAGE_DIR)/osmsMessageGetContentKeyResponseError.cpp

SecurityManagerProxy.o:
	$(COMPILE) $(NETWORK_DIR)/SecurityManagerProxy.cpp

MemMan.o:
	$(COMPILE) $(TOOLS_DIR)/MemMan.cpp

OlCharArray.o:
	$(COMPILE) $(TOOLS_DIR)/OlCharArray.cpp

OlMemMan.o:
	$(COMPILE) $(TOOLS_DIR)/OlMemMan.cpp

OlRaw.o:
	$(COMPILE) $(TOOLS_DIR)/OlRaw.cpp

clean:
	rm -f core libopenipmp.dylib *.o

