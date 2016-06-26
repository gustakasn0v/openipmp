AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libOpenIPMPDRMDecManagerFactory.la

libOpenIPMPDRMDecManagerFactory_la_LDFLAGS = -module

libOpenIPMPDRMDecManagerFactory_la_SOURCES = OpenIPMPDRMDecManagerFactory.h OpenIPMPDRMDecManagerFactory.cpp OpenIPMPDRMDecryptor.h OpenIPMPDRMDecryptor.cpp OpenIPMPDRMDecManager.h OpenIPMPDRMDecManager.cpp

libOpenIPMPDRMDecManagerFactory_la_LIBADD = ../../OpenIPMPKeyManager/libOpenIPMPKeyManager.a ../../OpenIPMPMessengerFactory/libOpenIPMPMessengerFactory.la ../../CipherFactory/libCipherFactory.a ../../../../ext/Crypto++/lib/linux/libcryptopp.a ../../../../ext/srtp/lib/linux/libsrtp.a

INCLUDES = -I../include -I../../include -I../../OpenIPMPKeyManager -I../../openIPMP

AM_CXXFLAGS = -DLINUX -DOPENIPMPDRMDECMANAGERFACTORY_EXPORTS
