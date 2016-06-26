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

#if !defined(_AXISUSERAPI_H____OF_AXIS_INCLUDED_)
#define _AXISUSERAPI_H____OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <time.h>
#include <string.h>

AXIS_CPP_NAMESPACE_START

 /**
  * @file AxisUserAPI.hpp
  * This file contains types defined in Axis C++. The mapping of basic xsd types
  * to the C language types.
  * 
  * The following xsd basic types are supported:
  * - <tt> anyURI, base64Binary, boolean, byte, date, dateTime, decimal, double, duration, float, hexBinary, int, integer, long, NMTOKEN, notation, QName, short, string, time, unsignedByte, unsignedInt, unsignedLong</tt> and \c unsignedShort.
  * 
  * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
  */

/**
 * @typedef xsd__string
 * Axis C++ defined type for xml basic type string
 */
typedef AxisChar * xsd__string;
/**
 * @typedef xsd__integer
 * Axis C++ defined type for xml basic type integer
 */
#ifdef WIN32
typedef __int64 xsd__integer;
#else
typedef long long xsd__integer;
#endif
/**
 * @typedef xsd__int
 * Axis C++ defined type for xml basic type int
 */
typedef int xsd__int;
/**
 * @typedef xsd__long
 * Axis C++ defined type for xml basic type long
 */
//FJP v Added
#ifdef WIN32
typedef __int64 xsd__long;
#else
typedef long long xsd__long;
#endif
//FJP ^ Added
/**
 * @typedef xsd__short
 * Axis C++ defined type for xml basic type short
 */
typedef short xsd__short;
/**
 * @typedef xsd__decimal
 * Axis C++ defined type for xml basic type decimal
 */
typedef double xsd__decimal;
/**
 * @typedef xsd__float
 * Axis C++ defined type for xml basic type float
 */
typedef float xsd__float;
/**
 * @typedef xsd__double
 * Axis C++ defined type for xml basic type double
 */
typedef double xsd__double;
/**
 * @typedef xsd__boolean
 * Axis C++ defined type for xml basic type boolean
 */
typedef enum { false_=0, true_ } xsd__boolean;
/**
 * @typedef xsd__byte
 * Axis C++ defined type for xml basic type byte
 */
typedef char xsd__byte;
/**
 * @typedef xsd__QName
 * Axis C++ defined type for xml basic type QName
 */
typedef AxisChar * xsd__QName;
/**
 * @typedef xsd__notation
 * Axis C++ defined type for xml basic type NOTATION
 */
typedef AxisChar * xsd__notation;
/**
 * @typedef xsd__NCName
 * Axis C++ defined type for xml basic type NCName
 */
//typedef AxisChar * xsd__NCName;
/**
 * @typedef xsd__dateTime
 * Axis C++ defined type for xml basic type dateTime
 */
typedef struct tm xsd__dateTime;
/**
 * @typedef xsd__date
 * Axis C++ defined type for xml basic type date
 */
typedef struct tm xsd__date;
/**
 * @typedef xsd__time
 * Axis C++ defined type for xml basic type time
 */
typedef struct tm xsd__time;
/**
 * @typedef xsd__duration
 * Axis C++ defined type for xml basic type duration
 */
typedef long xsd__duration;
/**
 * @typedef xsd__unsignedByte
 * Axis C++ defined type for xml basic type unsignedByte
 */
typedef unsigned char xsd__unsignedByte;
/**
 * @typedef xsd__unsignedInt
 * Axis C++ defined type for xml basic type unsignedInt
 */
typedef unsigned int xsd__unsignedInt;
/**
 * @typedef xsd__unsignedLong
 * Axis C++ defined type for xml basic type unsignedLong
 */
typedef unsigned long xsd__unsignedLong;
/**
 * @typedef xsd__unsignedShort
 * Axis C++ defined type for xml basic type unsignedShort
 */
typedef unsigned short xsd__unsignedShort;

/**
 * @class xsd__base64Binary
 * Axis C++ defined type for xml basic type base64Binary
 */
class STORAGE_CLASS_INFO xsd__base64Binary {
public:
    xsd__base64Binary();
    ~xsd__base64Binary();
    xsd__unsignedByte * __ptr;
    xsd__int __size;
};

/**
 * @class xsd__hexBinary
 * Axis C++ defined type for xml basic type hexBinary
 */
class STORAGE_CLASS_INFO xsd__hexBinary {
public:
    xsd__hexBinary();
    ~xsd__hexBinary();
    xsd__unsignedByte * __ptr;
    xsd__int __size;
};

/**
 * @typedef xsd__anyURI
 * Axis C++ defined type for xml basic type anyURI
 */
typedef AxisChar * xsd__anyURI;
/**
 * @typedef xsd__NMTOKEN
 * Axis C++ defined type for xml basic type anyURI
 */
typedef AxisChar * xsd__NMTOKEN;
/**
 * @enum AXIS_BINDING_STYLE
 * Enumeration for the different wsdl styles. This is used by the Axis
 * engine to identify the web service or client style.
 */
typedef enum {
    RPC_ENCODED, /*default*/
    DOC_LITERAL,
    RPC_LITERAL
} AXIS_BINDING_STYLE;

#define AXIS_DEFINED_ARRAY(type) \
    class type##_Array {\
      public:\
        type ** m_Array;\
        int m_Size;\
    };

#define AXIS_DEFINED_POINTER_ARRAY(type) \
    class type##_Array {\
      public:\
        type * m_Array;\
        int m_Size;\
    };

class Axis_Array {
  public:
    void* m_Array;
    int m_Size;
};

AXIS_DEFINED_POINTER_ARRAY(xsd__string)
AXIS_DEFINED_ARRAY(xsd__integer)
AXIS_DEFINED_ARRAY(xsd__int)
AXIS_DEFINED_ARRAY(xsd__long)
AXIS_DEFINED_ARRAY(xsd__short)
AXIS_DEFINED_ARRAY(xsd__decimal)
AXIS_DEFINED_ARRAY(xsd__float)
AXIS_DEFINED_ARRAY(xsd__double)
AXIS_DEFINED_ARRAY(xsd__boolean)
AXIS_DEFINED_POINTER_ARRAY(xsd__QName)
//AXIS_DEFINED_ARRAY(xsd__NCName)
AXIS_DEFINED_ARRAY(xsd__dateTime)
AXIS_DEFINED_ARRAY(xsd__unsignedByte)
AXIS_DEFINED_ARRAY(xsd__unsignedInt)
AXIS_DEFINED_ARRAY(xsd__unsignedLong)
AXIS_DEFINED_ARRAY(xsd__unsignedShort)
AXIS_DEFINED_ARRAY(xsd__base64Binary)
AXIS_DEFINED_ARRAY(xsd__hexBinary)
AXIS_DEFINED_POINTER_ARRAY(xsd__anyURI)
AXIS_DEFINED_POINTER_ARRAY(xsd__NMTOKEN)
 
#define AXIS_OUT_PARAM 

static const int xsd_boolean_true = 1;
static const int xsd_boolean_false = 0;

typedef enum {
    NORMAL_CHANNEL=0,
    SSL_CHANNEL
} AXIS_CHANNEL_TYPE;

/**
 * @typedef XML_String
 * Axis C++ defined type for xml encoded string. This is used only in AnyType.
 */
typedef char* XML_String;

/**
 * @class AnyType
 * Axis C++ defined type for handling xsd:any.
 */
class STORAGE_CLASS_INFO AnyType
{
public:
    AnyType();
    ~AnyType();

    /**
     * @var _array Contains an array of xml encoded strings.
     */
    XML_String* _array;

    /**
     * @var _size Contains how many xml strings are there in _array
     */
    int _size;
};

AXIS_CPP_NAMESPACE_END
#endif
