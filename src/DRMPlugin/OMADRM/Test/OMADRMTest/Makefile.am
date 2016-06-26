AUTOMAKE_OPTIONS = foreign

noinst_PROGRAMS = OMADRMTest

OMADRMTest_SOURCES = Test.cpp

OMADRMTest_LDADD = ../../../ThreadSyncFactory/libThreadSyncFactory.la ../../../PublicCryptoFactory/libPublicCryptoFactory.la ../../../DRMDecoderPlugin/OMADRMDecManagerFactory/libOMADRMDecManagerFactory.la ../../../DRMEncoderPlugin/OMADRMEncManagerFactory/libOMADRMEncManagerFactory.la ../../../XMLFactory/libXMLFactory.la $(pkglibdir)/libxerces-depdom.so $(pkglibdir)/libxerces-c.so ../../../../../ext/openssl/lib/linux/libcrypto.a ../../../../../ext/openssl/lib/linux/libssl.a -ldl $(pkglibdir)/libaxiscpp_client.so

INCLUDES = -I../../../ThreadSyncFactory -I../../../CipherFactory -I../../../PublicCryptoFactory -I../../../DRMDecoderPlugin/OMADRMDecManagerFactory -I../../../DRMEncoderPlugin/OMADRMEncManagerFactory -I../../OMADRMCommon -I../../../Base64Factory -I../../../XMLFactory -I../../ROAPParser -I../../OMADRMCrypto -I../../ROAP -I../../../include -I../../include -I../../../DRMDecoderPlugin/include -I../../../DRMEncoderPlugin/include -I../../../../../ext/openssl/include -I../../../../../ext/xerces/include

AM_CXXFLAGS = -DLINUX
