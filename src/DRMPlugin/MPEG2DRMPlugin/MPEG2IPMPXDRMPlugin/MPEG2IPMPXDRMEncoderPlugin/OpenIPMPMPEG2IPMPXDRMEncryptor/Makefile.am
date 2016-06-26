AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libOpenIPMPMPEG2IPMPXDRMEncryptor.la

libOpenIPMPMPEG2IPMPXDRMEncryptor_la_LDFLAGS = -module

libOpenIPMPMPEG2IPMPXDRMEncryptor_la_SOURCES = OpenIPMPMPEG2IPMPXDRMEncryptor.h OpenIPMPMPEG2IPMPXDRMEncryptor.cpp

libOpenIPMPMPEG2IPMPXDRMEncryptor_la_LIBADD = ../../IPMPControlInfo/libIPMPControlInfo.a ../../IPMPData/libIPMPData.a

INCLUDES = -I../../../../openIPMP -I../include -I../../include -I../../../include -I../../../../include -I../../IPMPControlInfo -I../../IPMPData -I../../../../DRMEncoderPlugin/include -I../../../../DRMEncoderPlugin/OpenIPMPDRMEncManagerFactory

AM_CXXFLAGS = -DLINUX -DOPENIPMPMPEG2IPMPXDRMENCRYPTOR_EXPORTS
