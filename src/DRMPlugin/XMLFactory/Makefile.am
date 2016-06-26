AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libXMLFactory.la

libXMLFactory_la_LDFLAGS = -module

libXMLFactory_la_SOURCES = XMLDocument.h XMLDocument.cpp XMLFactory.h XMLFactory.cpp

libXMLFactory_la_LIBADD = $(pkglibdir)/libxerces-depdom.so $(pkglibdir)/libxerces-c.so

INCLUDES = -I../include -I../../../ext/xerces/include

AM_CXXFLAGS = -DLINUX -DXMLFACTORY_EXPORTS
