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
 *
 */
// ISoapAttachment.h: interface for the ISoapAttachment class.
//
//////////////////////////////////////////////////////////////////////
#ifndef ISOAPATTACHMENT_INCLUDED
#define ISOAPATTACHMENT_INCLUDED

typedef enum 
{ 
    AXISC_BASE64=0, 
    AXISC_BINARY = 1
} AXISC_AXISC_ATTACHMENT_ENCODING_TYPE;

/**
	  * Allows the user to add the Attachment Body
	  */
AXISC_STORAGE_CLASS_INFO void axiscAddBody(AXISCHANDLE soapAttachment, xsdc__base64Binary * objBody);

/**
	  * Allows the user to add the Attachment Headers
	  */
AXISC_STORAGE_CLASS_INFO void axiscAddHeader(AXISCHANDLE soapAttachment, const char * pchName, 
	const char * pchValue);

/**
	  * Allows the user to get the Attachment Body
	  */
AXISC_STORAGE_CLASS_INFO xsdc__base64Binary * axiscGetBody(AXISCHANDLE soapAttachment);

/**
	  * Allows the user to get the required Attachment Header
	  *
	  * @param pchName The name of the required Attachement Header
	  */
AXISC_STORAGE_CLASS_INFO const char * axiscGetHeaderISoapAttachment(AXISCHANDLE soapAttachment, const char * pchName);
AXISC_STORAGE_CLASS_INFO void axiscDestroyISoapAttachment(AXISCHANDLE soapAttachment);


#endif // ISOAPATTACHMENT_INCLUDED
