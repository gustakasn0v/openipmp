AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libContentInfoManagerFactory.la

libContentInfoManagerFactory_la_SOURCES = ContentInfoManagerFactory.h ContentInfoManagerFactory.cpp OpenIPMPDOIContentInfoManager.h OpenIPMPDOIContentInfoManager.cpp

libContentInfoManagerFactory_la_LIBADD = ../../OpenIPMPMessengerFactory/libOpenIPMPMessengerFactory.la

INCLUDES = -I../../../client/include -I../../OpenIPMPMessengerFactory -I../../include -I ../include

AM_CXXFLAGS = -DLINUX -DCONTENTINFOMANAGERFACTORY_EXPORTS
