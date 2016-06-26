AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libMessageRouter.la

libMessageRouter_la_LDFLAGS = -module

libMessageRouter_la_SOURCES = MessageRouter.h MessageRouter.cpp

libMessageRouter_la_LIBADD = ../../../../ThreadSyncFactory/libThreadSyncFactory.la

INCLUDES = -I../../../../ThreadSyncFactory -I../../../../include -I../../../include -I ../../include -I../include -I../../IPMPData -I../../IPMPCrypto -I../DecoderIPMPData

AM_CXXFLAGS = -DLINUX -DMESSAGEROUTER_EXPORTS
