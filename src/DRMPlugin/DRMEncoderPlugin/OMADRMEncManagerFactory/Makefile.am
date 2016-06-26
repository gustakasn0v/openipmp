AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libOMADRMEncManagerFactory.la

libOMADRMEncManagerFactory_la_SOURCES = \
	./OMADRMEncAgent.cpp \
	./OMADRMEncManager.cpp \
	./OMADRMEncManagerFactory.cpp \
	./OpenIPMPOMADRMEncManager.cpp \
	./OMADRMEncAgent.h \
	./OMADRMEncManager.h \
	./OMADRMEncManagerFactory.h \
	./OpenIPMPOMADRMEncManager.h

libOMADRMEncManagerFactory_la_LIBADD = ../../ThreadSyncFactory/libThreadSyncFactory.la ../../OpenIPMPKeyManager/libOpenIPMPKeyManager.a ../OMADRMEncCommHandlerFactory/libOMADRMEncCommHandlerFactory.la ../../Base64Factory/libBase64Factory.a ../../OMADRM/ROAP/libROAP.a ../../CipherFactory/libCipherFactory.a ../../../../ext/Crypto++/lib/linux/libcryptopp.a ../../../../ext/srtp/lib/linux/libsrtp.a ../../OMADRM/OMADRMCrypto/libOMADRMCrypto.a ../../OMADRM/OMADRMCommon/libOMADRMCommon.a ../../OpenIPMPMessengerFactory/libOpenIPMPMessengerFactory.la

INCLUDES = -I../../ThreadSyncFactory -I../../OpenIPMPKeyManager -I ../OMADRMEncCommHandlerFactory -I../../Base64Factory -I../include -I../../include -I ../../OMADRM/include -I../../OMADRM/ROAP -I../../CipherFactory -I../../OMADRM/OMADRMCrypto

AM_CXXFLAGS = -DLINUX -DOMADRMENCMANAGERFACTORY_EXPORTS
