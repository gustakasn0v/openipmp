AUTOMAKE_OPTIONS = foreign

noinst_PROGRAMS = MPEG2IPMPXEncoderTest

MPEG2IPMPXEncoderTest_SOURCES = MPEG2IPMPXEncoder.h MPEG2IPMPXEncoder.cpp MPEG2IPMPXEncoderTest.cpp

MPEG2IPMPXEncoderTest_LDADD = ../MPEG2IPMPXDRMEncoder/libMPEG2IPMPXDRMEncoder.la ../../../../ThreadSyncFactory/libThreadSyncFactory.la ../../../../XMLFactory/libXMLFactory.la $(pkglibdir)/libxerces-c.so $(pkglibdir)/libxerces-depdom.so $(pkglibdir)/libaxiscpp_client.so -ldl

INCLUDES = -I../../../../ThreadSyncFactory -I../../../../XMLFactory -I../include -I../../include -I../../../include -I../../../../include -I../../MPEG2 -I../MPEG2IPMPXDRMEncoder

AM_CXXFLAGS = -DLINUX
