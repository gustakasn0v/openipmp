/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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

/*
 * @author Nithyakala Thangarajah (nithya@opensource.lk)
 * @author Rangika Mendis (rangika@opensource.lk) 
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshan@jkcsworld.com)
 *
 */

// ISoapAttachment.h: interface for the ISoapAttachment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISOAPATTACHMENT_H__8B3A65FD_40A6_45B2_A8C5_295DE4222952__INCLUDED_)
#define AFX_ISOAPATTACHMENT_H__8B3A65FD_40A6_45B2_A8C5_295DE4222952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <axis/AxisUserAPI.hpp>

AXIS_CPP_NAMESPACE_START

typedef enum 
{ 
    AXIS_BASE64=0, 
    AXIS_BINARY = 1
} AXIS_ATTACHMENT_ENCODING_TYPE;


class STORAGE_CLASS_INFO ISoapAttachment  
{
public:

	/**
	  * Allows the user to add the Attachment Body
	  */
	virtual void addBody(xsd__base64Binary* objBody)=0;	

	/**
	  * Allows the user to add the Attachment Headers
	  */
	virtual void addHeader(const char* pchName, const char* pchValue)=0;

	/**
	  * Allows the user to get the Attachment Body
	  */
	virtual xsd__base64Binary* getBody()=0;	

	/**
	  * Allows the user to get the required Attachment Header
	  *
	  * @param pchName The name of the required Attachement Header
	  */
	virtual const char* getHeader(const char* pchName)=0;

	virtual ~ISoapAttachment() {};

};

AXIS_CPP_NAMESPACE_END

#endif // !defined(AFX_ISOAPATTACHMENT_H__8B3A65FD_40A6_45B2_A8C5_295DE4222952__INCLUDED_)

