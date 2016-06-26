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
#ifndef IWRAPPERSOAPSERIALIZER_INCLUDED
#define IWRAPPERSOAPSERIALIZER_INCLUDED

#include <stdarg.h>

/*
 *  @class IWrapperSoapSerializer
 *  @brief interface for the IWrapperSoapSerializer class.
 *
 *
 *
 */
/*
 * Revision 1.1  2005/01/02 Roshan
 * Added addAttachmentBody
 * Added addAttachmentHeader
 */
/*
 * Revision 1.2  2005/01/07 Roshan
 * Added addAttachment
 */
AXISC_STORAGE_CLASS_INFO void axiscDestroyIWrapperSoapSerializer(AXISCHANDLE wrapperSoapSerializer);
AXISC_STORAGE_CLASS_INFO int axiscCreateSoapMethod(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sLocalName, 
	const AxiscChar * sURI);
AXISC_STORAGE_CLASS_INFO int axiscCreateSoapFault(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sLocalName, 
	const AxiscChar * sURI, const AxiscChar * sFaultCode, 
	const AxiscChar * sFaultString);

/**
     * Returns the corrosponding namespace prefix.
     * @param pNamespace The namespace.
     * @return The corrosponding prefix.
     */

/**
     * Returns the corrosponding namespace prefix. This method is 
     * called when the caller also wants to know whether this is a new 
     * namespace or not as appose to its overloaded other member.
     * @param pNamespace The namespace.
     * @param blnIsNewPrefix The boolean which behaves as 
     * an out parameter to indicate whether this is a new namespace or not.
     * @return The corrosponding prefix.
     */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetNamespacePrefixIWrapperSoapSerializer(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pNamespace, 
	AxiscBool * blnIsNewPrefix);
AXISC_STORAGE_CLASS_INFO void axiscRemoveNamespacePrefix(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pNamespace);

/* for basic types */
AXISC_STORAGE_CLASS_INFO int axiscAddOutputParam(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pchName, 
	void * pValue, AXISC_XSDTYPE type);

/* for arrays */
AXISC_STORAGE_CLASS_INFO int axiscAddOutputCmplxArrayParam(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	void * pSZFunct, void * pDelFunct, void * pSizeFunct, 
	const AxiscChar * pName, const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO int axiscAddOutputBasicArrayParam(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	AXISC_XSDTYPE nType, const AxiscChar * pName);

/* for complex types */
AXISC_STORAGE_CLASS_INFO int axiscAddOutputCmplxParam(AXISCHANDLE wrapperSoapSerializer, void * pObject, 
	void * pSZFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO int axiscAddFaultDetail(AXISCHANDLE wrapperSoapSerializer, void * pObject, 
	void * pSZFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/* Methods used to serialize arrays */
AXISC_STORAGE_CLASS_INFO int axiscSerializeCmplxArray(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	void * pSZFunct, void * pDelFunct, void * pSizeFunct, 
	const AxiscChar * pName, const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO int axiscSerializeBasicArray(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	const AxiscChar * pNamespace, AXISC_XSDTYPE nType, 
	const AxiscChar * pName);

/* Basic Type Serializing methods */
AXISC_STORAGE_CLASS_INFO int axiscSerializeAsElement(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sName, 
	const AxiscChar * pNamespace, void * pValue, AXISC_XSDTYPE type);
AXISC_STORAGE_CLASS_INFO int axiscSerializeAsAttribute(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sName, 
	const AxiscChar * pNamespace, void * pValue, AXISC_XSDTYPE type);
AXISC_STORAGE_CLASS_INFO void axiscSerializeIWrapperSoapSerializer(AXISCHANDLE wrapperSoapSerializer, const char * pFirst, 
	... );

/* 
     * following two functions are needed by serializer 
     * functions of complex types for RPC style web services 
     */
AXISC_STORAGE_CLASS_INFO void axiscSerializeStartElementOfType(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace, const AxiscChar * pPrefix);
AXISC_STORAGE_CLASS_INFO void axiscSerializeEndElementOfType(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pName);

/* Externalization of serializer API */
/* Following functions need not be exposed. They are internal to the
	 * Axis Engine - Commented by Susantha 02/07/2004
    virtual int setOutputStream(SOAPTransport* pStream)=0;
    virtual void markEndOfStream()=0;    
    virtual int init()=0;    
    virtual void setStyle(AXIS_BINDING_STYLE nStyle)=0;
    virtual AXIS_BINDING_STYLE getStyle()=0;
    */
AXISC_STORAGE_CLASS_INFO AXISC_PROVIDERTYPE axiscGetCurrentProviderType(AXISCHANDLE wrapperSoapSerializer);
AXISC_STORAGE_CLASS_INFO void axiscSetCurrentProviderType(AXISCHANDLE wrapperSoapSerializer, AXISC_PROVIDERTYPE nType);
AXISC_STORAGE_CLASS_INFO int axiscAddOutputAnyObject(AXISCHANDLE wrapperSoapSerializer, AxiscAnyType * pAnyObject);
AXISC_STORAGE_CLASS_INFO int axiscSerializeAnyObject(AXISCHANDLE wrapperSoapSerializer, AxiscAnyType * pAnyObject);
AXISC_STORAGE_CLASS_INFO int axiscSerializeAsChardata(AXISCHANDLE wrapperSoapSerializer, void * pValue, 
	AXISC_XSDTYPE type);
AXISC_STORAGE_CLASS_INFO void axiscAddAttachment(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * achId, 
	AXISCHANDLE objAttach);
AXISC_STORAGE_CLASS_INFO void axiscAddAttachmentBody(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * achId, 
	xsdc__base64Binary * pAttchBody);
AXISC_STORAGE_CLASS_INFO void axiscAddAttachmentHeader(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * achId, 
	const AxiscChar * achHeaderName, const AxiscChar * achHeaderValue);

/**
    * creates and returns a SoapAttachment object to the caller of this methods.
	*  The user can use this object and fill in the attachment details. This
	*  method doesn't add the created SoapAttachment object to the Serializer.
	*  The user will have to add this object explictly by calling the addAttachment 
	*  method of the IWrapperSoapSerializer interface
    *     
    */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateSoapAttachementSoapAttachment(AXISCHANDLE wrapperSoapSerializer);


#endif // IWRAPPERSOAPSERIALIZER_INCLUDED
