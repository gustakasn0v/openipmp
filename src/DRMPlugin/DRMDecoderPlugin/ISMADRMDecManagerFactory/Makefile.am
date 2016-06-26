AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libISMADRMDecManagerFactory.la

libISMADRMDecManagerFactory_la_LDFLAGS = -module

libISMADRMDecManagerFactory_la_SOURCES = ISMADRMDecManagerFactory.h ISMADRMDecManagerFactory.cpp ISMADRMDecryptor.h ISMADRMDecryptor.cpp OpenIPMPISMADRMDecManager.h OpenIPMPISMADRMDecManager.cpp

libISMADRMDecManagerFactory_la_LIBADD = ../../OpenIPMPKeyManager/libOpenIPMPKeyManager.a ../../OpenIPMPMessengerFactory/libOpenIPMPMessengerFactory.la ../../CipherFactory/libCipherFactory.a ../../../../ext/Crypto++/lib/linux/libcryptopp.a ../../../../ext/srtp/lib/linux/libsrtp.a

INCLUDES = -I../include -I../../include -I../../OpenIPMPKeyManager

AM_CXXFLAGS = -DLINUX -DISMADRMDECMANAGERFACTORY_EXPORTS
