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
/**
 * @file IAttribute.h
 *
 *
 */
#ifndef IATTRIBUTE_INCLUDED
#define IATTRIBUTE_INCLUDED


/**
 *   @class IAttribute
 *   @brief interface for the IAttribute class.
 *
 *
 */
AXISC_STORAGE_CLASS_INFO void axiscDestroyIAttribute(AXISCHANDLE attribute);
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetValueIAttribute(AXISCHANDLE attribute);

/**
     * Get the URI of this attribute
     * @return The URI of this attribute
     */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetURIIAttribute(AXISCHANDLE attribute);

/**
     * Get the prefix of this attribute
     * @return The prefix of this attribute
     */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetPrefixIAttribute(AXISCHANDLE attribute);

/**
     * Get the local name of this attribute
     * @return The local name of this attribute
     */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetLocalNameIAttribute(AXISCHANDLE attribute);

/**
	 * try to set theattribute with given value
	 * @param AxisChar* the value to set the value to 
	 * @return AXIS_SUCCESS if succeeded, AXIS_Fail otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
	 */
AXISC_STORAGE_CLASS_INFO int axiscSetValueIAttribute(AXISCHANDLE attribute, const AxiscChar * value);

/**
	 * try to set the URI
	 * @param AxisChar* the value to set the URI to 
	 * @return AXIS_SUCCESS if succeeded, AXIS_Fail otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
	 */
AXISC_STORAGE_CLASS_INFO int axiscSetURIIAttribute(AXISCHANDLE attribute, const AxiscChar * uri);

/**
	 * try to set the prefix with given value
	 * @param AxisChar* the prefix to set to 
	 * @return AXIS_SUCCESS if succeeded, AXIS_Fail otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
	 */
AXISC_STORAGE_CLASS_INFO int axiscSetPrefixIAttribute(AXISCHANDLE attribute, const AxiscChar * prefix);

/**
	 * try to set the attribute with given value
	 * @param AxisChar* the value to set the local name to 
	 * @return AXIS_SUCCESS if succeeded, AXIS_Fail otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
	 */
AXISC_STORAGE_CLASS_INFO int axiscSetLocalNameIAttribute(AXISCHANDLE attribute, const AxiscChar * localname);

/**
     * Get the value of this attribute.
     * @return The value of this attribute.
     */


#endif // IATTRIBUTE_INCLUDED
