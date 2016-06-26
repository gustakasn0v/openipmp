AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = OMADRMDeviceIDCalc

OMADRMDeviceIDCalc_SOURCES = OMADRMDeviceIDCalc.cpp

OMADRMDeviceIDCalc_LDADD = ../../PublicCryptoFactory/libPublicCryptoFactory.la ../OMADRMCrypto/libOMADRMCrypto.a ../../Base64Factory/libBase64Factory.a ../ROAP/libROAP.a

INCLUDES = -I../../PublicCryptoFactory -I../../Base64Factory -I../OMADRMCrypto -I../ROAP -I../../include

AM_CXXFLAGS = -DLINUX
