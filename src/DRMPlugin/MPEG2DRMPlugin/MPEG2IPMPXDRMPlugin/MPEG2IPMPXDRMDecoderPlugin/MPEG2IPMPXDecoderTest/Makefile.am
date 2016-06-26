AUTOMAKE_OPTIONS = foreign

noinst_PROGRAMS = MPEG2IPMPXDecoderTest

MPEG2IPMPXDecoderTest_SOURCES = MPEG2IPMPXDecoderTest.cpp MPEG2IPMPXParser.h MPEG2IPMPXParser.cpp

MPEG2IPMPXDecoderTest_LDADD = ../../IPMPCrypto/libIPMPCrypto.a ../IPMPToolManager/libIPMPToolManager.a ../IPMPControlInfoParser/libIPMPControlInfoParser.a ../DecoderIPMPControlInfo/libDecoderIPMPControlInfo.a ../../IPMPControlInfo/libIPMPControlInfo.a ../OpenIPMPTool/libOpenIPMPTool.la ../IPMPDataParser/libIPMPDataParser.a ../DecoderIPMPData/libDecoderIPMPData.a ../../IPMPData/libIPMPData.a  ../MessageRouter/libMessageRouter.la ../../../../ThreadSyncFactory/libThreadSyncFactory.la $(pkglibdir)/libxerces-c.so $(pkglibdir)/libxerces-depdom.so $(pkglibdir)/libaxiscpp_client.so -ldl

INCLUDES = -I../../../../ThreadSyncFactory -I../../../../include -I../../../include -I../../include -I../include -I../../MPEG2 -I../IPMPToolManager -I ../../IPMPData -I../../IPMPCrypto -I../MessageRouter -I../OpenIPMPTool -I ../DecoderIPMPData

AM_CXXFLAGS = -DLINUX
