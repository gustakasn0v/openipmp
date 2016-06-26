AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libThreadSyncFactory.la

libThreadSyncFactory_la_SOURCES = ThreadSyncFactory.h ThreadSyncFactory.cpp PThreadsThreadSync.h PThreadsThreadSync.cpp

INCLUDES = -I../include

AM_CXXFLAGS = -DLINUX -DTHREADSYNCFACTORY_EXPORTS -DPTHREADS
