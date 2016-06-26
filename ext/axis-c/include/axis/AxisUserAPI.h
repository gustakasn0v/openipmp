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
 */

#if !defined(_AXISUSERAPI_H_OF_AXIS_INCLUDED_)
#define _AXISUSERAPI_H_OF_AXIS_INCLUDED_

#include <axis/GDefine.h>
#include <time.h>
#include <string.h>

 /**
  * @file AxisUserAPI.h
  * This file contains types defined in Axis C++. The mapping of basic xsd types
  * to the C language types.
  * 
  * The following xsd basic types are supported:
  * - <tt> anyURI, base64Binary, boolean, byte, date, dateTime, decimal, double, duration, float, hexBinary, int, integer, long, NMTOKEN, notation, QName, short, string, time, unsignedByte, unsignedInt, unsignedLong</tt> and \c unsignedShort.
  */

/**
 * @typedef xsdc__string
 * Axis C++ defined type for xml basic type string
 */
typedef AxiscChar * xsdc__string;

/**
 * @typedef xsdc__integer
 * Axis C++ defined type for xml basic type integer
 */
#ifdef WIN32
typedef __int64 xsdc__integer;
#else
typedef long long xsdc__integer;
#endif

/**
 * @typedef xsdc__int
 * Axis C++ defined type for xml basic type int
 */
typedef int xsdc__int;

/**
 * @typedef xsdc__long
 * Axis C++ defined type for xml basic type long
 */
#ifdef WIN32
typedef __int64 xsdc__long;
#else
typedef long long xsdc__long;
#endif

/**
 * @typedef xsdc__short
 * Axis C++ defined type for xml basic type short
 */
typedef short xsdc__short;

/**
 * @typedef xsdc__decimal
 * Axis C++ defined type for xml basic type decimal
 */
typedef double xsdc__decimal;

/**
 * @typedef xsdc__float
 * Axis C++ defined type for xml basic type float
 */
typedef float xsdc__float;

/**
 * @typedef xsdc__double
 * Axis C++ defined type for xml basic type double
 */
typedef double xsdc__double;

/**
 * @typedef xsdc__boolean
 * Axis C++ defined type for xml basic type boolean
 */
typedef enum { false_=0, true_ } xsdc__boolean;
/**
 * @typedef xsdc__byte
 * Axis C++ defined type for xml basic type byte
 */
typedef char xsdc__byte;

/**
 * @typedef xsdc__QName
 * Axis C++ defined type for xml basic type QName
 */
typedef AxiscChar * xsdc__QName;

/**
 * @typedef xsdc__NCName
 * Axis C++ defined type for xml basic type NCName
 */
//typedef AxiscChar * xsdc__NCName;

/**
 * @typedef xsdc__dateTime
 * Axis C++ defined type for xml basic type dateTime
 */
typedef struct tm xsdc__dateTime;

/**
 * @typedef xsdc__date
 * Axis C++ defined type for xml basic type date
 */
typedef struct tm xsdc__date;

/**
 * @typedef xsdc__time
 * Axis C++ defined type for xml basic type time
 */
typedef struct tm xsdc__time;

/**
 * @typedef xsdc__duration
 * Axis C++ defined type for xml basic type duration
 */
typedef long xsdc__duration;

/**
 * @typedef xsdc__unsignedByte
 * Axis C++ defined type for xml basic type unsignedByte
 */
typedef unsigned char xsdc__unsignedByte;

/**
 * @typedef xsdc__unsignedInt
 * Axis C++ defined type for xml basic type unsignedInt
 */
typedef unsigned int xsdc__unsignedInt;

/**
 * @typedef xsdc__unsignedLong
 * Axis C++ defined type for xml basic type unsignedLong
 */
typedef unsigned long xsdc__unsignedLong;

/**
 * @typedef xsdc__unsignedShort
 * Axis C++ defined type for xml basic type unsignedShort
 */
typedef unsigned short xsdc__unsignedShort;

/**
 * @struct xsdc__base64Binary
 * Axis C++ defined type for xml basic type base64Binary
 */
typedef struct {
    xsdc__unsignedByte __ptr;
    xsdc__int __size;
} xsdc__base64Binary;

/**
 * @struct xsdc__hexBinary
 * Axis C++ defined type for xml basic type hexBinary
 */
typedef struct {
    xsdc__unsignedByte __ptr;
    xsdc__int __size;
} xsdc__hexBinary;
/**
 * @typedef xsdc__anyURI
 * Axis C++ defined type for xml basic type anyURI
 */
typedef AxiscChar * xsdc__anyURI;

/**
 * @typedef xsdc__NMTOKEN
 * Axis C++ defined type for xml basic type anyURI
 */
typedef AxiscChar * xsdc__NMTOKEN;

/**
 * @enum AXISC_BINDING_STYLE
 * Enumeration for the different wsdl styles. This is used by the Axis
 * engine to identify the web service or client style.
 */
typedef enum {
    AXISC_RPC_ENCODED, /*default*/
    AXISC_DOC_LITERAL,
    AXISC_RPC_LITERAL
} AXISC_BINDING_STYLE;

#define AXISC_DEFINED_ARRAY(type) \
    typedef struct {\
        type ** m_Array;\
        int m_Size;\
    } type##_Array;

#define AXISC_DEFINED_POINTER_ARRAY(type) \
    typedef struct {\
        type * m_Array;\
        int m_Size;\
    } type##_Array;

#define AXISC_DEFINED_ARRAY2(type) \
    typedef struct {\
        AXISCHANDLE m_Array;\
        int m_Size;\
    } type##_Array;

typedef struct {
    void* m_Array;
    int m_Size;
} Axisc_Array;

AXISC_DEFINED_POINTER_ARRAY(xsdc__string)
AXISC_DEFINED_ARRAY(xsdc__integer)
AXISC_DEFINED_ARRAY(xsdc__int)
AXISC_DEFINED_ARRAY(xsdc__long)
AXISC_DEFINED_ARRAY(xsdc__short)
AXISC_DEFINED_ARRAY(xsdc__decimal)
AXISC_DEFINED_ARRAY(xsdc__float)
AXISC_DEFINED_ARRAY(xsdc__double)
AXISC_DEFINED_ARRAY(xsdc__boolean)
AXISC_DEFINED_POINTER_ARRAY(xsdc__QName)
//AXISC_DEFINED_ARRAY(xsdc__NCName)
AXISC_DEFINED_ARRAY(xsdc__dateTime)
AXISC_DEFINED_ARRAY(xsdc__unsignedByte)
AXISC_DEFINED_ARRAY(xsdc__unsignedInt)
AXISC_DEFINED_ARRAY(xsdc__unsignedLong)
AXISC_DEFINED_ARRAY(xsdc__unsignedShort)
AXISC_DEFINED_ARRAY2(xsdc__base64Binary)
AXISC_DEFINED_ARRAY2(xsdc__hexBinary)
AXISC_DEFINED_POINTER_ARRAY(xsdc__anyURI)
AXISC_DEFINED_POINTER_ARRAY(xsdc__NMTOKEN)
 
static const int xsdc_boolean_true = 1;
static const int xsdc_boolean_false = 0;

typedef enum {
    AXISC_NORMAL_CHANNEL=0,
    AXISC_SSL_CHANNEL
} AXISC_CHANNEL_TYPE;

/**
 * @typedef AXISC_XML_String
 * Axis C++ defined type for xml encoded string. This is used only in AnyType.
 */
typedef char* AXISC_XML_String;

/**
 * @struct AxiscAnyType
 * Axis C++ defined type for handling xsd:any.
 */
typedef struct
{
    /**
     * @var _array Contains an array of xml encoded strings.
     */
    AXISC_XML_String* _array;

    /**
     * @var _size Contains how many xml strings are there in _array
     */
    int _size;
} AxiscAnyType;

#endif
