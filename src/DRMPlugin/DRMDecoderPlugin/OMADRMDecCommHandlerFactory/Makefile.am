AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libOMADRMDecCommHandlerFactory.la

libOMADRMDecCommHandlerFactory_la_LDFLAGS = -module

libOMADRMDecCommHandlerFactory_la_SOURCES = \
	./OMADRMDecCommHandlerFactory.cpp \
	./OMADRMWS.cpp \
	./OMADRMWSDecCommHandler.cpp \
	./WSDeviceHello.cpp \
	./WSInitialRORequest.cpp \
	./WSRegistrationRequest.cpp \
	./WSRegistrationResponse.cpp \
	./WSRIHello.cpp \
	./WSROAcquisitionTrigger.cpp \
	./WSRORequest.cpp \
	./WSROResponse.cpp \
	./OMADRMDecCommHandlerFactory.h \
	./OMADRMROAPWS.hpp \
	./OMADRMWS.hpp \
	./OMADRMWSDecCommHandler.h \
	./WSDeviceHello.hpp \
	./WSInitialRORequest.hpp \
	./WSRegistrationRequest.hpp \
	./WSRegistrationResponse.hpp \
	./WSRIHello.hpp \
	./WSROAcquisitionTrigger.hpp \
	./WSRORequest.hpp \
	./WSROResponse.hpp

libOMADRMDecCommHandlerFactory_la_LIBADD = ../../ThreadSyncFactory/libThreadSyncFactory.la ../../OMADRM/ROAPParser/libROAPParser.a ../../OMADRM/ROAP/libROAP.a ../../OMADRM/Test/OMADRMMQDecCommHandler/libOMADRMMQDecCommHandler.a ../../Base64Factory/libBase64Factory.a ../../OMADRM/Test/OMADRMServer/libOMADRMServer.a ../../OMADRM/OMADRMCommon/libOMADRMCommon.a ../../OMADRM/OMADRMCrypto/libOMADRMCrypto.a ../../PublicCryptoFactory/libPublicCryptoFactory.la $(pkglibdir)/libaxiscpp_client.so ../../XMLFactory/libXMLFactory.la ../../ThreadSyncFactory/libThreadSyncFactory.la

INCLUDES = -I../../ThreadSyncFactory -I../../XMLFactory -I../../OMADRM/ROAPParser -I ../../OMADRM/Test/OMADRMMQDecCommHandler -I ../../OMADRM/Test/OMADRMServer -I../../OMADRM/ROAP -I../../OMADRM/OMADRMCrypto -I../../OMADRM/OMADRMCommon -I../../OMADRM/include -I ../../include -I../include -I../../../../ext/axis-c/include

AM_CXXFLAGS = -DLINUX -DOMADRMDECCOMMHANDLERFACTORY_EXPORTS
