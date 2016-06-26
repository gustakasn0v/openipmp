AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libISMADRMEncManagerFactory.la

libISMADRMEncManagerFactory_la_SOURCES = ISMADRMEncManagerFactory.h ISMADRMEncManagerFactory.cpp OpenIPMPISMADRMEncManager.h OpenIPMPISMADRMEncManager.cpp

libISMADRMEncManagerFactory_la_LIBADD = ../../OpenIPMPKeyManager/libOpenIPMPKeyManager.a ../../OpenIPMPMessengerFactory/libOpenIPMPMessengerFactory.la ../../CipherFactory/libCipherFactory.a ../../../../ext/Crypto++/lib/linux/libcryptopp.a ../../../../ext/srtp/lib/linux/libsrtp.a

INCLUDES = -I../include -I../../include -I../../OpenIPMPKeyManager

AM_CXXFLAGS = -DLINUX -DISMADRMENCMANAGERFACTORY_EXPORTS
