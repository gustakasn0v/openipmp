AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libMPEG2IPMPXDRMEncoder.la

libMPEG2IPMPXDRMEncoder_la_LDFLAGS = -module

libMPEG2IPMPXDRMEncoder_la_SOURCES = MPEG2IPMPXDRMEncoder.h MPEG2IPMPXDRMEncoder.cpp

libMPEG2IPMPXDRMEncoder_la_LIBADD = ../OpenIPMPMPEG2IPMPXDRMEncryptor/libOpenIPMPMPEG2IPMPXDRMEncryptor.la ../../../../DRMEncoderPlugin/ContentInfoManagerFactory/libContentInfoManagerFactory.la ../../../../DRMEncoderPlugin/OpenIPMPDRMEncManagerFactory/libOpenIPMPDRMEncManagerFactory.la

INCLUDES = -I../../../../openIPMP -I../../../../DRMEncoderPlugin/ContentInfoManagerFactory -I../../../../DRMEncoderPlugin/include -I../include -I../../include -I../../../include -I../../../../include -I../OpenIPMPMPEG2IPMPXDRMEncryptor -I../../../../DRMEncoderPlugin/OpenIPMPDRMEncManagerFactory

AM_CXXFLAGS = -DLINUX -DMPEG2IPMPXDRMENCODER_EXPORTS
