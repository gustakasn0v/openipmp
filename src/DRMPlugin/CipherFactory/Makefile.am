AUTOMAKE_OPTIONS = foreign

noinst_LIBRARIES = libCipherFactory.a

libCipherFactory_a_SOURCES = CipherFactory.h CipherFactory.cpp BlockCipher.h BlockCipher.cpp

INCLUDES = -I../SRTPCrypto -I../../../ext/srtp/include -I../../../ext/Crypto++/include -I../include -I../../../ext/openssl/include

AM_CXXFLAGS = -DLINUX -DNDEBUG -fPIC
