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
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshan@jkcs.slt.lk)
 *
 */

/* SoapEnvVersions.h:*/

#include "GDefine.hpp"

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#ifndef __SOAPENVVERSIONS_H_OF_AXIS_INCLUDED___
#define __SOAPENVVERSIONS_H_OF_AXIS_INCLUDED___

AXIS_CPP_NAMESPACE_START

/*
 * Here SKW stands for SoapKeyWord. This is a internal naming convension
 * for Axis C++.
 */
typedef enum SOAP_WORDSTag 
{
    SKW_ENVELOPE=0, /* this should always be 0 */
    SKW_HEADER,
    SKW_BODY,
    SKW_MUSTUNDERSTAND,
    SKW_ACTOR,
    SKW_ENCODING_STYLE,
    SKW_FAULT,
    SKW_FAULT_CODE,
    SKW_FAULT_STRING,
    SKW_FAULT_ACTOR,
    SKW_DETAIL,
    SKW_MULTIREF,
    
    SKW_TYPE,
    SKW_ARRAYTYPE,
    SKW_HREF,
    SKW_ID,

    SOAP_WORDS_LAST /*this should be the number of entries in this enum */
} SOAP_WORDS;

typedef enum SOAP_VERSIONTag 
{
    SOAP_VER_1_1=0,
    SOAP_VER_1_2,

    VERSION_LAST
} SOAP_VERSION;

struct SoapEnvVersionsStruct 
{    
    const AxisChar* pchNamespaceUri;
    const AxisChar* pchPrefix;
    const AxisChar* pchWords[SOAP_WORDS_LAST];
};

AXIS_CPP_NAMESPACE_END
#endif

