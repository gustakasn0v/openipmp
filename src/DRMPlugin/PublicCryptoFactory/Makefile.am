AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libPublicCryptoFactory.la

libPublicCryptoFactory_la_LDFLAGS = -module

libPublicCryptoFactory_la_SOURCES = PublicCryptoFactory.h PublicCryptoFactory.cpp OpenSSLPublicCrypto.h OpenSSLPublicCrypto.cpp

libPublicCryptoFactory_la_LIBADD = ../../../ext/openssl/lib/linux/libssl.a ../../../ext/openssl/lib/linux/libcrypto.a

INCLUDES = -I../include -I../../../ext/openssl/include

AM_CXXFLAGS = -DLINUX -DPUBLICCRYPTOFACTORY_EXPORTS
