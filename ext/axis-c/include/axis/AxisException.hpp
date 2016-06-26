/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *
 *
 */

/**
 * @file AxisException.h
 *
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */
 
#ifndef __AXISEXCEPTION_H_OF_AXIS_INCLUDED_
#define __AXISEXCEPTION_H_OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <string>
#include <exception>
#include <new>
#include <typeinfo>
#include <stdexcept>

AXIS_CPP_NAMESPACE_START
using namespace std;

/*
 * The following enumeration is used to serve the Axis C++ codes for 
 * faults.
 */
#define CLIENT_FAULT_OFFSET		0x0
#define SERVER_FAULT_OFFSET		0x1000
#define SOAP_FAULT_OFFSET		0x2000
#define ENGINE_FAULT_OFFSET		0x3000
#define WSDD_FAULT_OFFSET		0x4000
#define TRANSPORT_FAULT_OFFSET	0x5000
#define CONFIG_FAULT_OFFSET		0x6000
#define AXISC_FAULT_OFFSET		0x7000

typedef enum 
{
    /*The notation used for naming these exceptions is as follows
     *CLIENT at the beginning means when this interpreted as a soap fault
     *    it's fault code is CLIENT
     *SERVER at the beginning means when this interpreted as a soap fault
     *    it's fault code is SERVER
     *SOAP that comes next to CLIENT/SERVER means this is a soap releated
     *    exception
     *ENGINE that comes next to CLIENT/SERVER means this is a axisc++ engine
     *    related exception
     *WSDD that comes next to CLIENT/SERVER means this is a wsdd releated
     *    exception
     *TRANSPORT that comes next to CLIENT/SERVER means this is a transport releated
     *    exception
     *CONFIG that comes next to CLIENT/SERVER means this is a axisc++ configuration
     *    related exception
	 *AXISC ?
     */
	/* SOAP faults */
/*0*/    SOAP_VERSION_MISMATCH, /* VersionMismatch faults */
/*1*/    SOAP_MUST_UNDERSTAND,	/* MustUnderstand faults */

    /* Client faults */
/*2*/    CLIENT_SOAP_MESSAGE_INCOMPLETE,
/*3*/    CLIENT_SOAP_SOAP_ACTION_EMTPY,
/*4*/    CLIENT_SOAP_SOAP_CONTENT_ERROR,
/*5*/    CLIENT_SOAP_NO_SOAP_METHOD,
/*6*/    CLIENT_SOAP_CONTENT_NOT_SOAP,
/*7*/    CLIENT_WSDD_SERVICE_NOT_FOUND,
/*8*/    CLIENT_WSDD_METHOD_NOT_ALLOWED,
/*9*/    CLIENT_WSDD_PARA_TYPE_MISMATCH,
/*10*/   CLIENT_ENGINE_CLIENT_HANDLER_FAILED,
/*11*/	 CLIENT_TRANSPORT_EXCEPTION,
/*12*/   CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED,
/*13*/   CLIENT_TRANSPORT_TYPE_MISMATCH,
/*14*/   CLIENT_TRANSPORT_HAS_NO_UNSECURE_TRANSPORT_LAYER,
/*15*/   CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER,
/*16*/   CLIENT_SSLCHANNEL_RECEPTION_EXCEPTION,
/*17*/   CLIENT_SSLCHANNEL_SENDING_EXCEPTION,
/*18*/   CLIENT_SSLCHANNEL_CHANNEL_INIT_ERROR,
/*19*/   CLIENT_SSLCHANNEL_SOCKET_CREATE_ERROR,
/*20*/   CLIENT_SSLCHANNEL_SOCKET_CONNECT_ERROR,
/*21*/   CLIENT_SSLCHANNEL_INVALID_SOCKET_ERROR,
/*22*/   CLIENT_SSLCHANNEL_CONTEXT_CREATE_ERROR,
/*23*/   CLIENT_SSLCHANNEL_ERROR,

    /* Server faults */
/*24*/    SERVER_ENGINE_EXCEPTION,
/*25*/    SERVER_ENGINE_COULD_NOT_LOAD_SRV,
/*26*/    SERVER_ENGINE_COULD_NOT_LOAD_HDL,
/*27*/    SERVER_ENGINE_LOADING_TRANSPORT_FAILED,
/*28*/    SERVER_ENGINE_LOADING_PARSER_FAILED,
/*29*/    SERVER_ENGINE_HANDLER_FAILED,
/*30*/    SERVER_ENGINE_WEBSERVICE_FAILED,
/*31*/    SERVER_ENGINE_HANDLER_INIT_FAILED,
/*32*/    SERVER_ENGINE_HANDLER_CREATION_FAILED,
/*33*/    SERVER_ENGINE_LIBRARY_LOADING_FAILED,
/*34*/    SERVER_ENGINE_HANDLER_NOT_LOADED,
/*35*/    SERVER_ENGINE_HANDLER_BEING_USED,
/*36*/    SERVER_ENGINE_GET_HANDLER_FAILED,
/*37*/    SERVER_ENGINE_WRONG_HANDLER_TYPE,
/*38*/    SERVER_CONFIG_EXCEPTION,
/*39*/    SERVER_CONFIG_TRANSPORT_CONF_FAILED,
/*40*/    SERVER_CONFIG_LIBRARY_PATH_EMPTY,
/*41*/    SERVER_WSDD_FILE_NOT_FOUND,
/*42*/    SERVER_WSDD_EXCEPTION,
/*43*/    SERVER_WSDD_NO_HANDLERS_CONFIGURED,
/*44*/    SERVER_SOAP_EXCEPTION,
/*45*/    SERVER_TRANSPORT_EXCEPTION,
/*46*/    SERVER_TRANSPORT_RECEPTION_EXCEPTION,
/*47*/    SERVER_TRANSPORT_SENDING_EXCEPTION,
/*48*/    SERVER_TRANSPORT_PROCESS_EXCEPTION,
/*49*/    SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE,
/*50*/    SERVER_TRANSPORT_HTTP_EXCEPTION,
/*51*/    SERVER_TRANSPORT_UNEXPECTED_STRING,
/*52*/    SERVER_TRANSPORT_CHANNEL_INIT_ERROR,
/*53*/    SERVER_TRANSPORT_SOCKET_CREATE_ERROR,
/*54*/    SERVER_TRANSPORT_SOCKET_CONNECT_ERROR,
/*55*/    SERVER_TRANSPORT_INVALID_SOCKET,
/*56*/    SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR,
/*57*/    SERVER_TRANSPORT_INPUT_STREAMING_ERROR,
/*58*/    SERVER_TRANSPORT_TIMEOUT_EXCEPTION,
/*59*/    SERVER_TRANSPORT_TIMEOUT_EXPIRED,
/*60*/    SERVER_TRANSPORT_LOADING_SSLCHANNEL_FAILED,
/*61*/	  SERVER_TRANSPORT_LOADING_CHANNEL_FAILED,
/*62*/    SERVER_TRANSPORT_BUFFER_EMPTY,
/*63*/    SERVER_PARSE_BUFFER_EMPTY,
/*64*/    SERVER_PARSE_PARSER_FAILED, 
/*65*/    SERVER_PARSE_TRANSPORT_FAILED,
/*66*/    SERVER_TEST_EXCEPTION,
/*67*/    SERVER_UNKNOWN_ERROR,
/*68*/    SERVER_CLIENT_ENGINE_MISMATCH,

    /* AXIS C faults */
    /*Following exceptions are not releated to soap faults
     */
/*60*/    AXISC_SERVICE_THROWN_EXCEPTION,
/*70*/    AXISC_UNKNOWN_ELEMENT_EXCEPTION,
/*71*/    AXISC_NODE_VALUE_MISMATCH_EXCEPTION,
/*72*/    AXISC_READ_CONF_EXCEPTION,

    /*
     * This FAULT_LAST is not used as a fault code, but instead is used 
     * internaly in the code. Developers should not use this as a fault 
     * code.
     */
/*73*/    FAULT_LAST 
} AXISC_EXCEPTIONS;

/**
 *   @class AxisException
 *   @brief Base class for Axis C++ exception hierarchy.
 *
 *   This will act as the base class for Axis C++ exception hierarchy. 
 *   This is class is derived from the std c++ exception class. Derived
 *   from this class are AxisConfigExceptin, AxisSoapExceptin, AxisWsddException,
 *   AxisEngineException, AxisTransportException and AxisParseException.
 *
 *   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 */
class STORAGE_CLASS_INFO AxisException :public exception
{

public:
    /** No parameter constructor*/
    //AxisException(){};

    /** This can be used to throw an exception with the exception code
      * which is defined in the AxisException.h file, under AXISC_EXCEPTIONS
      * type. Axis C++ exception model heavily use this.
      *
      * @param Exception code which is defined in the AxisException.h file, 
      * under AXISC_EXCEPTIONS type.
      * 
      * @example throw AxisException(AXISC_NODE_VALUE_MISMATCH_EXCEPTION);
      */
    //AxisException(const int iExceptionCode);

    /** This can be used to throw an exception with exception code which is
      * is defined in the AxisException.h file, under AXISC_EXCEPTIONS type.
      * An additional description of the exception could be appended.
      *
      * @param Exception code which is defined in the AxisException.h file,
      *  under AXISC_EXCEPTIONS type.
      * @param A char pointer that will point to an exception message.
      *
      * @example throw AxisException(AXISC_NODE_VALUE_MISMATCH_EXCEPTION, 
            "Some additional exception info");
      */
    //AxisException(const int iExceptionCode, char* pcMessage);

    /** This can be used to throw an exception with another exception as a
      * parameter. One situation in which this can be used is when we catch
      * a standard exception like std::bad_alloc
      *
      * @param An exception class derived from std::exception
      *
      * @example throw AxisException(std::bad_alloc);
      */
    //AxisException(const exception* e);

    /** This accept two parameters, both an exception code an exception object
      * derived from std::exception
      *
      * @param An exception class derived from std::exception
      * @param An exception code
      */
    //AxisException(const exception* e, const int iExceptionCode);
    
    /** This accept an exception message
      *
      * @param An exception message
      */
    //AxisException(const char* pcMessage){m_sMessage = pcMessage;};
    
    /** Destructor */
    virtual ~AxisException() throw(){};

    /** This method is defined in std::exception. AxisException and derived
      * classes will override this to print exception messages
      */
    virtual const char* what() throw() = 0;

    /** This can be called to get the exception code which is passed
      * in the constructor. This returns -1 value when the 
      * constructor does not have a exception code parameter
      * 
      * @return the exception code if the construct have a exception code
      * int parameter. Else return -1.
      *
      * @return exception message
      */
    virtual const int getExceptionCode() = 0;
};

AXIS_CPP_NAMESPACE_END

#endif

