AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libOpenIPMPDRMEncManagerFactory.la

libOpenIPMPDRMEncManagerFactory_la_SOURCES = OpenIPMPDRMEncManagerFactory.h OpenIPMPDRMEncManagerFactory.cpp OpenIPMPDRMEncManager.h OpenIPMPDRMEncManager.cpp

libOpenIPMPDRMEncManagerFactory_la_LIBADD = ../../OpenIPMPKeyManager/libOpenIPMPKeyManager.a ../../OpenIPMPMessengerFactory/libOpenIPMPMessengerFactory.la ../../CipherFactory/libCipherFactory.a ../../../../ext/Crypto++/lib/linux/libcryptopp.a ../../../../ext/srtp/lib/linux/libsrtp.a

INCLUDES = -I../include -I../../include -I../../OpenIPMPKeyManager

AM_CXXFLAGS = -DLINUX -DOPENIPMPDRMENCMANAGERFACTORY_EXPORTS
