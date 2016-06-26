AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libOpenIPMPTool.la

libOpenIPMPTool_la_LDFLAGS = -module

libOpenIPMPTool_la_SOURCES = OpenIPMPTool.h OpenIPMPTool.cpp

libOpenIPMPTool_la_LIBADD = ../../IPMPData/libIPMPData.a ../../IPMPCrypto/libIPMPCrypto.a ../IPMPDataParser/libIPMPDataParser.a ../MessageRouter/libMessageRouter.la ../../../../XMLFactory/libXMLFactory.la ../../../../DRMDecoderPlugin/OpenIPMPDRMDecManagerFactory/libOpenIPMPDRMDecManagerFactory.la ../../../../ThreadSyncFactory/libThreadSyncFactory.la

INCLUDES = -I../../../../ThreadSyncFactory -I../../../../openIPMP -I ../../../../include -I../../../include -I../../include -I../include -I ../../IPMPData -I../MessageRouter -I../IPMPDataParser -I../../IPMPCrypto -I ../DecoderIPMPData -I../../../../XMLFactory -I../../../../DRMDecoderPlugin/include -I../../../../DRMDecoderPlugin/OpenIPMPDRMDecManagerFactory

AM_CXXFLAGS = -DLINUX -DOPENIPMPTOOL_EXPORTS
