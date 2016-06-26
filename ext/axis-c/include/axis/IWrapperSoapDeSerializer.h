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
#ifndef IWRAPPERSOAPDESERIALIZER_INCLUDED
#define IWRAPPERSOAPDESERIALIZER_INCLUDED


/**
    @class IWrapperSoapDeSerializer
    @brief interface for the IWrapperSoapDeSerializer class.
*/
AXISC_STORAGE_CLASS_INFO void axiscDestroyIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer);
AXISC_STORAGE_CLASS_INFO int axiscCheckMessageBody(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO void * axiscCheckForFault(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/* Method used by wrappers to get a deserialized Array of complex types */
AXISC_STORAGE_CLASS_INFO Axisc_Array axiscGetCmplxArrayIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, void * pSizeFunct, 
	const AxiscChar * pName, const AxiscChar * pNamespace);

/* Method used by wrappers to get a deserialized Array of basic types */
AXISC_STORAGE_CLASS_INFO Axisc_Array axiscGetBasicArrayIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, AXISC_XSDTYPE nType, 
	const AxiscChar * pName, const AxiscChar * pNamespace);

/* Method used by wrappers to get a deserialized single object of 
     * complex type 
     */
AXISC_STORAGE_CLASS_INFO void * axiscGetCmplxObjectIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/* Methods used by wrappers to get a deserialized value of basic types */
AXISC_STORAGE_CLASS_INFO xsdc__int * axiscGetElementAsIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__boolean * axiscGetElementAsBooleanIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedInt * axiscGetElementAsUnsignedIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__short * axiscGetElementAsShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedShort * axiscGetElementAsUnsignedShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__byte * axiscGetElementAsByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedByte * axiscGetElementAsUnsignedByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__long * axiscGetElementAsLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__integer * axiscGetElementAsIntegerIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedLong * axiscGetElementAsUnsignedLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__float * axiscGetElementAsFloatIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__double * axiscGetElementAsDoubleIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__decimal * axiscGetElementAsDecimalIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__string axiscGetElementAsStringIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__anyURI axiscGetElementAsAnyURIIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__QName axiscGetElementAsQNameIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__hexBinary * axiscGetElementAsHexBinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__base64Binary * axiscGetElementAsBase64BinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__dateTime * axiscGetElementAsDateTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__date * axiscGetElementAsDateIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__time * axiscGetElementAsTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__duration * axiscGetElementAsDurationIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__int * axiscGetAttributeAsIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__boolean * axiscGetAttributeAsBooleanIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedInt * axiscGetAttributeAsUnsignedIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__short * axiscGetAttributeAsShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedShort * axiscGetAttributeAsUnsignedShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__byte * axiscGetAttributeAsByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedByte * axiscGetAttributeAsUnsignedByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__long * axiscGetAttributeAsLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__integer * axiscGetAttributeAsIntegerIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedLong * axiscGetAttributeAsUnsignedLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__float * axiscGetAttributeAsFloatIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__double * axiscGetAttributeAsDoubleIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__decimal * axiscGetAttributeAsDecimalIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__string axiscGetAttributeAsStringIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__anyURI axiscGetAttributeAsAnyURIIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__QName axiscGetAttributeAsQNameIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__hexBinary * axiscGetAttributeAsHexBinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__base64Binary * axiscGetAttributeAsBase64BinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__dateTime * axiscGetAttributeAsDateTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__date * axiscGetAttributeAsDateIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__time * axiscGetAttributeAsTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__duration * axiscGetAttributeAsDurationIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO int axiscGetStatusIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer);

/* Externalization of deserializer API */
//    virtual int setInputStream(SOAPTransport* pInputStream)=0;
//    virtual int init()=0;
//    virtual PROVIDERTYPE getCurrentProviderType()=0;
//    virtual void setCurrentProviderType(PROVIDERTYPE nType)=0;
AXISC_STORAGE_CLASS_INFO AXISC_BINDING_STYLE axiscGetStyle(AXISCHANDLE wrapperSoapDeSerializer);
AXISC_STORAGE_CLASS_INFO void axiscSetStyle(AXISCHANDLE wrapperSoapDeSerializer, AXISC_BINDING_STYLE nStyle);
AXISC_STORAGE_CLASS_INFO int axiscGetVersion(AXISCHANDLE wrapperSoapDeSerializer);
AXISC_STORAGE_CLASS_INFO int axiscGetHeaderIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer);
AXISC_STORAGE_CLASS_INFO AxiscAnyType * axiscGetAnyObjectIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer);
AXISC_STORAGE_CLASS_INFO void axiscGetChardataAs(AXISCHANDLE wrapperSoapDeSerializer, void * pValue, 
	AXISC_XSDTYPE type);
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetAttachmentSoapAttachment(AXISCHANDLE wrapperSoapDeSerializer, const char * pcAttachmentid);


#endif // IWRAPPERSOAPDESERIALIZER_INCLUDED
