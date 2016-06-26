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

#if !defined(_IWRAPPERSOAPDESERIALIZER_H____OF_AXIS_INCLUDED_)
#define _IWRAPPERSOAPDESERIALIZER_H____OF_AXIS_INCLUDED_

#include "AxisUserAPI.hpp"
#include "TypeMapping.hpp"
#include "WSDDDefines.hpp"
#include "ISoapAttachment.hpp"
/**
    @class IWrapperSoapDeSerializer
    @brief interface for the IWrapperSoapDeSerializer class.


    @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
    @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
*/

AXIS_CPP_NAMESPACE_START

class IWrapperSoapDeSerializer
{
public:
    virtual ~IWrapperSoapDeSerializer(){};

    virtual int AXISCALL checkMessageBody(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual void* AXISCALL checkForFault(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /* Method used by wrappers to get a deserialized Array of complex types */
    virtual Axis_Array AXISCALL getCmplxArray(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /* Method used by wrappers to get a deserialized Array of basic types */
    virtual Axis_Array AXISCALL getBasicArray(XSDTYPE nType, 
        const AxisChar* pName, const AxisChar* pNamespace)=0;
    /* Method used by wrappers to get a deserialized single object of 
     * complex type 
     */
    virtual void* AXISCALL getCmplxObject(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
    
    /* Methods used by wrappers to get a deserialized value of basic types */
    virtual xsd__int * AXISCALL getElementAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__boolean * AXISCALL getElementAsBoolean(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__unsignedInt * AXISCALL getElementAsUnsignedInt(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual xsd__short * AXISCALL getElementAsShort(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__unsignedShort * AXISCALL getElementAsUnsignedShort(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual xsd__byte * AXISCALL getElementAsByte(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__unsignedByte * AXISCALL getElementAsUnsignedByte(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual xsd__long * AXISCALL getElementAsLong(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__integer * AXISCALL getElementAsInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__unsignedLong * AXISCALL getElementAsUnsignedLong(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual xsd__float * AXISCALL getElementAsFloat(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__double * AXISCALL getElementAsDouble(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__decimal * AXISCALL getElementAsDecimal(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__string AXISCALL getElementAsString(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__anyURI AXISCALL getElementAsAnyURI(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__QName AXISCALL getElementAsQName(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__hexBinary * AXISCALL getElementAsHexBinary(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual xsd__base64Binary * AXISCALL getElementAsBase64Binary(const AxisChar*
        pName, const AxisChar* pNamespace)=0;
    virtual xsd__dateTime * AXISCALL getElementAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__date * AXISCALL getElementAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__time * AXISCALL getElementAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__duration * AXISCALL getElementAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;


    virtual xsd__int * AXISCALL getAttributeAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__boolean * AXISCALL getAttributeAsBoolean(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__unsignedInt * AXISCALL getAttributeAsUnsignedInt(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual xsd__short * AXISCALL getAttributeAsShort(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__unsignedShort * AXISCALL getAttributeAsUnsignedShort(const AxisChar*
        pName, const AxisChar* pNamespace)=0;
    virtual xsd__byte * AXISCALL getAttributeAsByte(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__unsignedByte * AXISCALL getAttributeAsUnsignedByte(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual xsd__long * AXISCALL getAttributeAsLong(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__integer * AXISCALL getAttributeAsInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__unsignedLong * AXISCALL getAttributeAsUnsignedLong(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual xsd__float * AXISCALL getAttributeAsFloat(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__double * AXISCALL getAttributeAsDouble(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__decimal * AXISCALL getAttributeAsDecimal(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__string AXISCALL getAttributeAsString(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__anyURI AXISCALL getAttributeAsAnyURI(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__QName AXISCALL getAttributeAsQName(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__hexBinary * AXISCALL getAttributeAsHexBinary(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual xsd__base64Binary * AXISCALL getAttributeAsBase64Binary(const 
        AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual xsd__dateTime * AXISCALL getAttributeAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__date * AXISCALL getAttributeAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__time * AXISCALL getAttributeAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__duration * AXISCALL getAttributeAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual int AXISCALL getStatus()=0;
    
    /* Externalization of deserializer API */
//    virtual int setInputStream(SOAPTransport* pInputStream)=0;
//    virtual int init()=0;
//    virtual PROVIDERTYPE getCurrentProviderType()=0;
//    virtual void setCurrentProviderType(PROVIDERTYPE nType)=0;    
    virtual AXIS_BINDING_STYLE getStyle()=0;    
    virtual void setStyle(AXIS_BINDING_STYLE nStyle)=0;
    virtual int getVersion()=0;
    virtual int getHeader()=0;    
	virtual AnyType* AXISCALL getAnyObject()=0;            
    virtual void getChardataAs(void* pValue, XSDTYPE type)=0;
	virtual ISoapAttachment* getAttachment(const char* pcAttachmentid)=0;
};

AXIS_CPP_NAMESPACE_END

#endif
