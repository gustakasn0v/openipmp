AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libOMADRMDecManagerFactory.la

libOMADRMDecManagerFactory_la_LDFLAGS = -module

libOMADRMDecManagerFactory_la_SOURCES = \
	./AgentBase.cpp \
	./AgentROAP.cpp \
	./FileOMADRMDecAgent.cpp \
	./OMADRMDecAgent.cpp \
	./OMADRMDecManager.cpp \
	./OMADRMDecManagerFactory.cpp \
	./OMADRMDecryptor.cpp \
	./OpenIPMPOMADRMDecManager.cpp \
	./AgentBase.h \
	./AgentROAP.h \
	./FileOMADRMDecAgent.h \
	./OMADRMDecAgent.h \
	./OMADRMDecManager.h \
	./OMADRMDecManagerFactory.h \
	./OMADRMDecryptor.h \
	./OpenIPMPOMADRMDecManager.h

libOMADRMDecManagerFactory_la_LIBADD = ../../OpenIPMPKeyManager/libOpenIPMPKeyManager.a ../../OpenIPMPMessengerFactory/libOpenIPMPMessengerFactory.la ../../ThreadSyncFactory/libThreadSyncFactory.la ../OMADRMDecCommHandlerFactory/libOMADRMDecCommHandlerFactory.la ../../PublicCryptoFactory/libPublicCryptoFactory.la ../../OMADRM/ROAPParser/libROAPParser.a ../../OMADRM/OMADRMCommon/libOMADRMCommon.a ../../OMADRM/OMADRMCrypto/libOMADRMCrypto.a  ../../OMADRM/ROAP/libROAP.a ../../CipherFactory/libCipherFactory.a ../../../../ext/Crypto++/lib/linux/libcryptopp.a ../../../../ext/srtp/lib/linux/libsrtp.a ../../Base64Factory/libBase64Factory.a ../../XMLFactory/libXMLFactory.la

INCLUDES = -I../../ThreadSyncFactory -I../../OpenIPMPKeyManager -I ../OMADRMDecCommHandlerFactory -I../../PublicCryptoFactory -I../../OMADRM/ROAPParser -I ../../Base64Factory -I../../XMLFactory -I../../OMADRM/include -I../include -I ../../include -I../../OMADRM/OMADRMCommon -I../../OMADRM/OMADRMCrypto -I../../OMADRM/ROAP -I ../../CipherFactory

AM_CXXFLAGS = -DLINUX -DOMADRMDECMANAGERFACTORY_EXPORTS
