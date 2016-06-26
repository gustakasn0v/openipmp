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
 * @file INamespace.h
 *
 *
 */

/**
 *   @class INamespace
 *   @brief interface for the Namespace.
 *
 *   @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com, roshan_444@yahoo.com)
 *
 */

#if !defined(AFX_INAMESPACE_H__A4213FD6_AA6B_41BF_A72E_735167A02C69__INCLUDED_)
#define AFX_INAMESPACE_H__A4213FD6_AA6B_41BF_A72E_735167A02C69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

AXIS_CPP_NAMESPACE_START

class INamespace  
{
public:
    /**
     * Gets the prefix of this Namespace.
     * 
     * @return prefix of this namespace.
     */
	virtual const AxisChar* getPrefix()=0;
   
   /**
    * Gets the namespace uri of this Namespace.
    * 
    * @return namespace uri of this Namespace
    */
	virtual const AxisChar* getURI()=0;

    /**
      * Sets the namespace uri of this Namespace.
      *
      * @param uri The namespace uri to set in.
      * @return AXIS_SUCCESS if successful AXIS_FAIL otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
      * 
      */
	virtual int setURI(const AxisChar* achURI)=0;
    /**
     * Sets the prefix of this Namespace.
     *
     * @param prefix The prefix to set in.
     * @return AXIS_SUCCESS if successful AXIS_FAIL otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
     */
	virtual int setPrefix(const AxisChar* achPrefix)=0;
	virtual ~INamespace() {};

};

AXIS_CPP_NAMESPACE_END

#endif // !defined(AFX_INAMESPACE_H__A4213FD6_AA6B_41BF_A72E_735167A02C69__INCLUDED_)
