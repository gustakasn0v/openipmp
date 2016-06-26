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
 
#if !defined(_IATTRIBUTE_H____OF_AXIS_INCLUDED_)
#define _IATTRIBUTE_H____OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>

AXIS_CPP_NAMESPACE_START

/**
 *   @class IAttribute
 *   @brief interface for the IAttribute class.
 *
 *   @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *
 */

class IAttribute
{
public:        

    virtual ~IAttribute() {};
    virtual const AxisChar* getValue() = 0;
    /**
     * Get the URI of this attribute
     * @return The URI of this attribute
     */
    virtual const AxisChar* getURI() = 0;
    /**
     * Get the prefix of this attribute
     * @return The prefix of this attribute
     */
    virtual const AxisChar* getPrefix() = 0;
    /**
     * Get the local name of this attribute
     * @return The local name of this attribute
     */
    virtual const AxisChar* getLocalName() = 0;

	/**
	 * try to set theattribute with given value
	 * @param AxisChar* the value to set the value to 
	 * @return AXIS_SUCCESS if succeeded, AXIS_Fail otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
	 */
    virtual int setValue(const AxisChar* value) = 0;
    
	/**
	 * try to set the URI
	 * @param AxisChar* the value to set the URI to 
	 * @return AXIS_SUCCESS if succeeded, AXIS_Fail otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
	 */
    virtual int setURI(const AxisChar* uri) = 0;
	/**
	 * try to set the prefix with given value
	 * @param AxisChar* the prefix to set to 
	 * @return AXIS_SUCCESS if succeeded, AXIS_Fail otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
	 */
    virtual int setPrefix(const AxisChar* prefix) = 0;
	/**
	 * try to set the attribute with given value
	 * @param AxisChar* the value to set the local name to 
	 * @return AXIS_SUCCESS if succeeded, AXIS_Fail otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
	 */
    virtual int setLocalName(const AxisChar* localname) = 0;    
    /**
     * Get the value of this attribute.
     * @return The value of this attribute.
     */
};

AXIS_CPP_NAMESPACE_END

#endif
