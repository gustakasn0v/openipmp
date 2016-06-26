#
# squashxml Makefile 
# 

EXTERNALS_DIR=../../ext

# xerces include and lib paths.
XERCES_DIR=$(EXTERNALS_DIR)/xerces
XERCES_INCLUDE_DIR=$(XERCES_DIR)/include
XERCES_LIB_DIR=$(XERCES_DIR)/macosx/lib
XERCES_LIB_FLAGS= -lxerces-c -lxerces-depdom

CC=g++

CFLAGS= -g -Wall -flat_namespace -install_name /usr/local/lib/libsquashxml.dylib  -DLINUX -DMACOSX -DUNIXSTYLE -DPTHREADS -dynamiclib

CCFLAGS= -c -Wno-deprecated

LDFLAGS= -L$(XERCES_LIB_DIR) $(XERCES_LIB_FLAGS)

COMPILE= $(CC) $(CFLAGS) $(CCFLAGS) $(INCLUDE_PARM)

MAIN_INCLUDE_DIR=./include

OUTPUT_LIB_DIR=./lib

SOCKET_DIR=./src/socket
TOOLS_DIR=./src/tools
XML_DIR=./src/xml

INCLUDE_PARM= -I$(MAIN_INCLUDE_DIR) \
	      -I$(XERCES_INCLUDE_DIR)

squashxml: \
		BlockingClientSocket.o \
		BlockingSocket.o \
		HTTPTunnelClient.o \
		MessageContainer.o \
		SquashXMLServletClient.o \
		FileLogger.o \
		FileTool.o \
		HashMap.o \
		Logger.o \
		RFC1521Base64.o \
		XMLDocument.o \
		XMLMessage.o \
		XMLMessageBean.o
	$(CC) $(CFLAGS) $(INCLUDE_PARM) $(LDFLAGS) -o $(OUTPUT_LIB_DIR)/libsquashxml.dylib \
		BlockingClientSocket.o \
		BlockingSocket.o \
		HTTPTunnelClient.o \
		MessageContainer.o \
		SquashXMLServletClient.o \
		FileLogger.o \
		FileTool.o \
		HashMap.o \
		Logger.o \
		RFC1521Base64.o \
		XMLDocument.o \
		XMLMessage.o \
		XMLMessageBean.o

BlockingClientSocket.o:
	$(COMPILE) $(SOCKET_DIR)/BlockingClientSocket.cpp

BlockingSocket.o:
	$(COMPILE) $(SOCKET_DIR)/BlockingSocket.cpp

HTTPTunnelClient.o:
	$(COMPILE) $(SOCKET_DIR)/HTTPTunnelClient.cpp

MessageContainer.o:
	$(COMPILE) $(SOCKET_DIR)/MessageContainer.cpp

SquashXMLServletClient.o:
	$(COMPILE) $(SOCKET_DIR)/SquashXMLServletClient.cpp

FileLogger.o:
	$(COMPILE) $(TOOLS_DIR)/FileLogger.cpp

FileTool.o:
	$(COMPILE) $(TOOLS_DIR)/FileTool.cpp

HashMap.o:
	$(COMPILE) $(TOOLS_DIR)/HashMap.cpp

Logger.o:
	$(COMPILE) $(TOOLS_DIR)/Logger.cpp

RFC1521Base64.o:
	$(COMPILE) $(TOOLS_DIR)/RFC1521Base64.cpp

XMLDocument.o:
	$(COMPILE) $(XML_DIR)/XMLDocument.cpp

XMLMessage.o:
	$(COMPILE) $(XML_DIR)/XMLMessage.cpp

XMLMessageBean.o:
	$(COMPILE) $(XML_DIR)/XMLMessageBean.cpp

example:
	$(CC) -g  $(INCLUDE_PARM) $(LDFLAGS) -L$(OUTPUT_LIB_DIR) -lsquashxml -o example.exe ./src/example/squashxmlExample.cpp

clean:
	rm -f core $(OUTPUT_LIB_DIR)/squashxml.dylib *.o *.exe
