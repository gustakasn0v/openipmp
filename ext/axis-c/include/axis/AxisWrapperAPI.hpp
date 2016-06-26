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
 */

#if !defined(_AXISWRAPPERAPI_H____OF_AXIS_INCLUDED_)
#define _AXISWRAPPERAPI_H____OF_AXIS_INCLUDED_

#include "IWrapperSoapDeSerializer.hpp"
#include "IWrapperSoapSerializer.hpp"
#include "BasicHandler.hpp"

AXIS_CPP_NAMESPACE_START

/**
 * @file AxisWrapperAPI.hpp
 * This file contains the API functions that are implemented by the WSDL2Ws
 * tool generated code to manipulate C/C++ type for each complex type in a xml
 * schema.
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
 
/**
 * @fn AXIS_DESERIALIZE_FUNCT
 * Function that deserializes a custom type 
 */
typedef int (* AXIS_DESERIALIZE_FUNCT)(void*, void*);

/**
 * @fn AXIS_OBJECT_CREATE_FUNCT
 * Function used to create a custom type. bArray is true if array of 
 * objects to be created. Then nSize is the size of that array.
 */
typedef void* (* AXIS_OBJECT_CREATE_FUNCT)(void*, bool bArray, int nSize);

/**
 * @fn AXIS_OBJECT_DELETE_FUNCT
 * Function used to delete a custom type. bArray is true if void* is a 
 * pointer to an array. Then nSize is the size of that array.
 */
typedef void (* AXIS_OBJECT_DELETE_FUNCT)(void*, bool bArray, int nSize);

/**
 * @fn AXIS_SERIALIZE_FUNCT
 * Function that serializes a custom type. bArray indicates that the object 
 * in void is an element of an array (note that void* is not itself an array).
 */
typedef int (* AXIS_SERIALIZE_FUNCT)(void*, void*, bool bArray);

/**
 * @fn AXIS_OBJECT_SIZE_FUNCT
 * Function that is used to get the size of an object of a custom type.
 */
typedef int (* AXIS_OBJECT_SIZE_FUNCT)(void);

AXIS_CPP_NAMESPACE_END

#endif
 
