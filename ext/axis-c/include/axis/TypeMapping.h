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
#ifndef TYPEMAPPING_INCLUDED
#define TYPEMAPPING_INCLUDED

typedef enum XSDTYPETag 
{ XSD_UNKNOWN=1, XSD_INT, XSD_FLOAT, XSD_STRING, XSD_LONG, XSD_SHORT, \
                XSD_BYTE, XSD_UNSIGNEDLONG, \
                XSD_BOOLEAN, XSD_UNSIGNEDINT, XSD_UNSIGNEDSHORT, \
                XSD_UNSIGNEDBYTE, \
                XSD_DOUBLE, XSD_DECIMAL, XSD_DURATION, \
                XSD_DATETIME, XSD_TIME, XSD_DATE, \
                XSD_YEARMONTH, XSD_YEAR, XSD_MONTHDAY, XSD_DAY, \
                XSD_MONTH, XSD_HEXBINARY, \
                XSD_BASE64BINARY, XSD_ANYURI, XSD_QNAME,  XSD_NOTATION, \
                XSD_INTEGER, \
                XSD_ARRAY, USER_TYPE,  XSD_NMTOKEN, XSD_ANY
} AXISC_XSDTYPE;

/**
 * REMOVED from XSDTYPETag-> ACCESSOR, XSD_NCNAME,
 */
/**
 *  @class TypeMapping
 *  @brief interface for the TypeMapping class.
 *
 *
 */
AXISC_STORAGE_CLASS_INFO AXISC_XSDTYPE axiscMap(const AxiscXMLCh * sType);
AXISC_STORAGE_CLASS_INFO void axiscInitializeTypeMapping();
AXISC_STORAGE_CLASS_INFO void axiscUninitialize();


AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateTypeMapping();
AXISC_STORAGE_CLASS_INFO void axiscDestroyTypeMapping(AXISCHANDLE typeMapping);


#endif // TYPEMAPPING_INCLUDED
