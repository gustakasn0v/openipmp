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

#if !defined(_IWRAPPERSOAPSERIALIZER_H____OF_AXIS_INCLUDED_)
#define _IWRAPPERSOAPSERIALIZER_H____OF_AXIS_INCLUDED_

#include "AxisUserAPI.hpp"
#include "TypeMapping.hpp"
#include "WSDDDefines.hpp"
#include "ISoapAttachment.hpp"
#include <stdarg.h>
#include <cctype>

/*
 *  @class IWrapperSoapSerializer
 *  @brief interface for the IWrapperSoapSerializer class.
 *
 *
 *  @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *  @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
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

AXIS_CPP_NAMESPACE_START

class IWrapperSoapSerializer
{
public:
    virtual ~IWrapperSoapSerializer(){};

    virtual int AXISCALL createSoapMethod(const AxisChar* sLocalName, 
        const AxisChar* sURI)=0;

    virtual int AXISCALL createSoapFault(const AxisChar* sLocalName, 
        const AxisChar* sURI, const AxisChar* sFaultCode,
	const AxisChar* sFaultString)=0;
    /**
     * Returns the corrosponding namespace prefix.
     * @param pNamespace The namespace.
     * @return The corrosponding prefix.
     */
    virtual const AxisChar* AXISCALL getNamespacePrefix
        (const AxisChar* pNamespace)=0;
    /**
     * Returns the corrosponding namespace prefix. This method is 
     * called when the caller also wants to know whether this is a new 
     * namespace or not as appose to its overloaded other member.
     * @param pNamespace The namespace.
     * @param blnIsNewPrefix The boolean which behaves as 
     * an out parameter to indicate whether this is a new namespace or not.
     * @return The corrosponding prefix.
     */
    virtual const AxisChar* AXISCALL getNamespacePrefix(const AxisChar* pNamespace,
        bool& blnIsNewPrefix)=0;

    virtual void AXISCALL removeNamespacePrefix(const AxisChar* pNamespace)=0;

    /* for basic types */
    virtual int AXISCALL addOutputParam(const AxisChar* pchName, void* pValue, 
        XSDTYPE type)=0;

    /* for arrays */
    virtual int AXISCALL addOutputCmplxArrayParam(const Axis_Array* pArray, 
        void* pSZFunct, void* pDelFunct, void* pSizeFunct, 
        const AxisChar* pName, const AxisChar* pNamespace)=0;

    virtual int AXISCALL addOutputBasicArrayParam(const Axis_Array* pArray, 
        XSDTYPE nType, const AxisChar* pName)=0;

    /* for complex types */
    virtual int AXISCALL addOutputCmplxParam(void* pObject, void* pSZFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace) = 0;

    virtual int AXISCALL addFaultDetail(void* pObject, void* pSZFunct,
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace) = 0;

    /* Methods used to serialize arrays */
    virtual int AXISCALL serializeCmplxArray(const Axis_Array* pArray, 
        void* pSZFunct, void* pDelFunct, void* pSizeFunct, 
        const AxisChar* pName, const AxisChar* pNamespace)=0;

    virtual int AXISCALL serializeBasicArray
        (const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)=0;

	virtual int AXISCALL serializeBasicArray
		(const Axis_Array* pArray, const AxisChar* pNamespace, XSDTYPE nType, const AxisChar* pName)=0;

    /* Basic Type Serializing methods */
    virtual int AXISCALL serializeAsElement(const AxisChar* sName, 
        void* pValue, XSDTYPE type)=0;

    virtual int AXISCALL serializeAsElement(const AxisChar* sName, const AxisChar* pNamespace, 
        void* pValue, XSDTYPE type)=0;

    virtual int AXISCALL serializeAsAttribute(const AxisChar* sName, 
        const AxisChar* pNamespace, void* pValue, XSDTYPE type)=0;

    virtual void AXISCALL serializeVargs(int count, const char** args)=0;
    virtual void AXISCALL serialize(const char* pFirst, ...)=0;

    /* 
     * following two functions are needed by serializer 
     * functions of complex types for RPC style web services 
     */
    virtual void AXISCALL serializeStartElementOfType(const AxisChar* pName, 
        const AxisChar* pNamespace, const AxisChar* pPrefix)=0;

    virtual void AXISCALL serializeEndElementOfType(const AxisChar* pName)=0;

    /* Externalization of serializer API */

    /* Following functions need not be exposed. They are internal to the
	 * Axis Engine - Commented by Susantha 02/07/2004

    virtual int setOutputStream(SOAPTransport* pStream)=0;

    virtual void markEndOfStream()=0;    

    virtual int init()=0;    

    virtual void setStyle(AXIS_BINDING_STYLE nStyle)=0;

    virtual AXIS_BINDING_STYLE getStyle()=0;
    */

    virtual PROVIDERTYPE getCurrentProviderType()=0;

    virtual void setCurrentProviderType(PROVIDERTYPE nType)=0;    

    virtual int addOutputAnyObject(AnyType* pAnyObject)=0;

    virtual int serializeAnyObject(AnyType* pAnyObject)=0;

    virtual int serializeAsChardata(void* pValue, XSDTYPE type)=0;

    virtual void addAttachment(const AxisChar* achId, ISoapAttachment* objAttach)=0;

	virtual void addAttachmentBody(const AxisChar* achId, xsd__base64Binary* pAttchBody)=0;

	virtual void addAttachmentHeader(const AxisChar* achId, const AxisChar* achHeaderName, const AxisChar* achHeaderValue)=0;

	/**
    * creates and returns a SoapAttachment object to the caller of this methods.
	*  The user can use this object and fill in the attachment details. This
	*  method doesn't add the created SoapAttachment object to the Serializer.
	*  The user will have to add this object explictly by calling the addAttachment 
	*  method of the IWrapperSoapSerializer interface
    *     
    */
	virtual ISoapAttachment* createSoapAttachement()=0;
};

AXIS_CPP_NAMESPACE_END

#endif

