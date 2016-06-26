AUTOMAKE_OPTIONS = foreign

noinst_LIBRARIES = libOMADRMServer.a

libOMADRMServer_a_SOURCES = OMADRMServer.h OMADRMServer.cpp ServerBase.h ServerBase.cpp ServerROAP.h ServerROAP.cpp

INCLUDES = -I../../../ThreadSyncFactory -I../../../PublicCryptoFactory -I../../ROAPParser -I../../../XMLFactory -I../../../Base64Factory -I../../OMADRMCommon -I../../OMADRMCrypto -I../../ROAP -I../../include -I../../../include

AM_CXXFLAGS = -DLINUX
