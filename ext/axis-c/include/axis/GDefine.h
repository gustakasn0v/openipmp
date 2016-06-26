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
 */

#if !defined(__GDEFINE_H_OF_AXIS_INCLUDED__)
#define __GDEFINE_H_OF_AXIS_INCLUDED__

/*
 * This file contains all global definitions that are valid across whole
 * Axis C++ project.
 */

typedef enum {AXISC_SECURE, AXISC_UNSECURE} AXISC_SECURE_PROTOCOL;

typedef enum 
{ 
    AXISC_SUCCESS=0, 
    AXISC_FAIL = -1, 
    AXISC_OBJECT_ALREADY_EXISTS=1,
    AXISC_NO_SUCH_HANDLER,
    AXISC_NO_SUCH_SERVICE
} AXISC_GLOBAL_ERROR;

typedef enum 
{ 
    AXISC_PT_UNKNOWN = -1, 
    AXISC_PTHTTP1_0=0, 
    AXISC_PTHTTP1_1, 
    AXISC_PTFTP, 
    AXISC_PTSMTP, 
    AXISC_PTHTTPS, 
    AXISC_PTOTHER
} AXISC_PROTOCOL_TYPE;

typedef enum 
{
    AXISC_SOAPACTION_HEADER,
    AXISC_SERVICE_URI,
    AXISC_OPERATION_NAME,
    AXISC_SOAP_MESSAGE_LENGTH,
    AXISC_TRANSPORT_PROPERTIES,
    AXISC_SECURE_PROPERTIES,
    AXISC_DLL_NAME,
    AXISC_CHANNEL_HTTP_SSL_DLL_NAME = AXISC_DLL_NAME,
    AXISC_CHANNEL_HTTP_DLL_NAME
} AXISC_TRANSPORT_INFORMATION_TYPE;

#define AXISC_SOAPACTIONHEADER "SOAPAction"

#define AxiscChar char
#define AxiscXMLCh char

#if defined(WIN32) 
#define AXISC_STORAGE_CLASS_INFO __declspec(dllexport)
#else
#define AXISC_STORAGE_CLASS_INFO 
#endif

#if defined(__GNUC__)
#define AXISCCALL __attribute__((cdecl))
#else /* unix or win32 */
#if defined(__unix)
#define AXISCCALL
#else
#define AXISCCALL __stdcall
#endif
#endif

typedef int AxiscBool;
typedef void* AXISCHANDLE;

#endif 


