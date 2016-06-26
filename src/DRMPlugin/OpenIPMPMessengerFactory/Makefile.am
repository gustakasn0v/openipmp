AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libOpenIPMPMessengerFactory.la

libOpenIPMPMessengerFactory_la_LDFLAGS = -module

libOpenIPMPMessengerFactory_la_SOURCES = \
	./OpenIPMPMessengerFactory.cpp \
	./OsmsCreateUserFault.cpp \
	./OsmsCreateUserRequest.cpp \
	./OsmsCreateUserResponse.cpp \
	./OsmsGetContentKeyFault.cpp \
	./OsmsGetContentKeyRequest.cpp \
	./OsmsGetContentKeyResponse.cpp \
	./OsmsLicenseFault.cpp \
	./OsmsLicenseRequest.cpp \
	./OsmsLicenseResponse.cpp \
	./OsmsOpenIPMPMessenger.cpp \
	./OsmsQueryFault.cpp \
	./OsmsQueryRequest.cpp \
	./OsmsQueryResponse.cpp \
	./OsmsRegisterContentAssignIdentifierFault.cpp \
	./OsmsRegisterContentAssignIdentifierRequest.cpp \
	./OsmsRegisterContentAssignIdentifierResponse.cpp \
	./OsmsRegisterContentExistingIdentifierFault.cpp \
	./OsmsRegisterContentExistingIdentifierRequest.cpp \
	./OsmsRegisterContentExistingIdentifierResponse.cpp \
	./OsmsRegisterDigitalItemInstanceFault.cpp \
	./OsmsRegisterDigitalItemInstanceRequest.cpp \
	./OsmsRegisterDigitalItemInstanceResponse.cpp \
	./OsmsRegisterUserFault.cpp \
	./OsmsRegisterUserRequest.cpp \
	./OsmsRegisterUserResponse.cpp \
	./OsmsRightsAuthorizationFault.cpp \
	./OsmsRightsAuthorizationRequest.cpp \
	./OsmsRightsAuthorizationResponse.cpp \
	./OsmsUserLoginFault.cpp \
	./OsmsUserLoginRequest.cpp \
	./OsmsUserLoginResponse.cpp \
	./OsmsUserLogoutFault.cpp \
	./OsmsUserLogoutRequest.cpp \
	./OsmsUserLogoutResponse.cpp \
	./OsmsWebService.cpp \
	./SquashXMLOsmsOpenIPMPMessenger.cpp \
	./WSOsmsOpenIPMPMessenger.cpp \
	./OpenIPMPMessengerFactory.h \
	./OsmsCreateUserFault.hpp \
	./OsmsCreateUserRequest.hpp \
	./OsmsCreateUserResponse.hpp \
	./OsmsGetContentKeyFault.hpp \
	./OsmsGetContentKeyRequest.hpp \
	./OsmsGetContentKeyResponse.hpp \
	./OsmsLicenseFault.hpp \
	./OsmsLicenseRequest.hpp \
	./OsmsLicenseResponse.hpp \
	./OsmsOpenIPMPMessenger.h \
	./OsmsQueryFault.hpp \
	./OsmsQueryRequest.hpp \
	./OsmsQueryResponse.hpp \
	./OsmsRegisterContentAssignIdentifierFault.hpp \
	./OsmsRegisterContentAssignIdentifierRequest.hpp \
	./OsmsRegisterContentAssignIdentifierResponse.hpp \
	./OsmsRegisterContentExistingIdentifierFault.hpp \
	./OsmsRegisterContentExistingIdentifierRequest.hpp \
	./OsmsRegisterContentExistingIdentifierResponse.hpp \
	./OsmsRegisterDigitalItemInstanceFault.hpp \
	./OsmsRegisterDigitalItemInstanceRequest.hpp \
	./OsmsRegisterDigitalItemInstanceResponse.hpp \
	./OsmsRegisterUserFault.hpp \
	./OsmsRegisterUserRequest.hpp \
	./OsmsRegisterUserResponse.hpp \
	./OsmsRightsAuthorizationFault.hpp \
	./OsmsRightsAuthorizationRequest.hpp \
	./OsmsRightsAuthorizationResponse.hpp \
	./OsmsUserLoginFault.hpp \
	./OsmsUserLoginRequest.hpp \
	./OsmsUserLoginResponse.hpp \
	./OsmsUserLogoutFault.hpp \
	./OsmsUserLogoutRequest.hpp \
	./OsmsUserLogoutResponse.hpp \
	./OsmsWebService.hpp \
	./SquashXMLOsmsOpenIPMPMessenger.h \
	./WSOsmsOpenIPMPMessenger.h

libOpenIPMPMessengerFactory_la_LIBADD = ../openIPMP/libopenIPMP.a ../squashxml/libSquashXML.a ../ThreadSyncFactory/libThreadSyncFactory.la $(pkglibdir)/libxerces-c.so $(pkglibdir)/libxerces-depdom.so ../../../ext/openssl/lib/linux/libssl.a ../../../ext/openssl/lib/linux/libcrypto.a $(pkglibdir)/libaxiscpp_client.so

INCLUDES = -I../include -I../../../ext/axis-c/include -I../ThreadSyncFactory -I ../openIPMP -I../../client/include -I../../../ext/openssl/include -I../../../ext/squashxml/include -I ../../../ext/xerces/include

AM_CXXFLAGS = -DLINUX -DOPENIPMPMESSENGERFACTORY_EXPORTS
