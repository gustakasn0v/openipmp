AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libOMADRMEncCommHandlerFactory.la

libOMADRMEncCommHandlerFactory_la_SOURCES = \
	./OMADRMEncCommHandlerFactory.cpp \
	./OMADRMWS.cpp \
	./OMADRMWSEncCommHandler.cpp \
	./WSAddContentKeyRequest.cpp \
	./WSAddContentKeyResponse.cpp \
	./WSAddDeviceRightsRequest.cpp \
	./WSAddDeviceRightsResponse.cpp \
	./OMADRMEncCommHandlerFactory.h \
	./OMADRMWS.hpp \
	./OMADRMWSEncCommHandler.h \
	./WSAddContentKeyRequest.hpp \
	./WSAddContentKeyResponse.hpp \
	./WSAddDeviceRightsRequest.hpp \
	./WSAddDeviceRightsResponse.hpp

libOMADRMEncCommHandlerFactory_la_LIBADD = ../../ThreadSyncFactory/libThreadSyncFactory.la ../../OMADRM/ROAPParser/libROAPParser.a ../../OMADRM/ROAP/libROAP.a ../../OMADRM/Test/OMADRMMQEncCommHandler/libOMADRMMQEncCommHandler.a ../../Base64Factory/libBase64Factory.a ../../OMADRM/Test/OMADRMServer/libOMADRMServer.a ../../OMADRM/OMADRMCommon/libOMADRMCommon.a ../../OMADRM/OMADRMCrypto/libOMADRMCrypto.a ../../PublicCryptoFactory/libPublicCryptoFactory.la $(pkglibdir)/libaxiscpp_client.so ../../XMLFactory/libXMLFactory.la ../../ThreadSyncFactory/libThreadSyncFactory.la

INCLUDES = -I../../ThreadSyncFactory -I../../XMLFactory -I../../OMADRM/ROAPParser -I../../OMADRM/include -I ../../OMADRM/ROAP -I ../../OMADRM/OMADRMCrypto -I ../../OMADRM/OMADRMCommon -I../include -I../../OMADRM/Test/OMADRMMQEncCommHandler -I../../OMADRM/Test/OMADRMServer -I../../include -I ../../../../ext/axis-c/include

AM_CXXFLAGS = -DLINUX -DOMADRMENCCOMMHANDLERFACTORY_EXPORTS
