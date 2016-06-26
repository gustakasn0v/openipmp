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

#if !defined(_IMESSAGEDATA_H___OF_AXIS_INCLUDED_)
#define _IMESSAGEDATA_H___OF_AXIS_INCLUDED_

#include "GDefine.hpp"
#include "IHandlerSoapDeSerializer.hpp"
#include "IHandlerSoapSerializer.hpp"
#include "IWrapperSoapDeSerializer.hpp"
#include "IWrapperSoapSerializer.hpp"

AXIS_CPP_NAMESPACE_START

class WSDDService;
class IAdminUtils;

/*
 *   @class IMessageData
 *   @brief interface for the IMessageData class.
 *   @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *   @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 */
class IMessageData
{
    /* Allow AxisAdminService access to the private methods */
    friend class AxisAdminServiceWrapper; 
public:
    virtual ~IMessageData(){};
private:
    virtual void getAdminUtils(IAdminUtils** pIAdminUtils)=0;
public: 
    
/**
 *  This method stores the given property value with the key, inside the 
 *  MessageData object.
 *  
 *   @param pachName is the key of the property.
 *   @param pachValue is the value of the property.
 *   @return AXIS_SUCCESS to indicate successful operation. 
 */        
    virtual int setProperty(const AxisChar* pachName, const AxisChar* pachValue)=0;

/**
 *  This method stores the given property value with the key, inside the 
 *  MessageData object.
 *
 *   @param pachName is the key of the property.
 *   @param pachValue is the value of the property.
 *   @param len is the size of value (pachValue).
 *   @return AXIS_SUCCESS to indicate successfull operation. 
*/ 
    virtual int setProperty(const AxisChar* pachName, const void* pachValue, int len)=0;

/**
 *  This method stores the given property value with the key, inside the 
 *  MessageData object. The value is a complex object.
 *
 *   @param pachName is the key of the property.
 *   @param pachValue is the value of the property.
 *   @param iObjectSize is the size of value (pachValue).
 */  
    virtual void setComplexProperty(const AxisChar* pachName, void* pachValue, int iObjectSize)=0;

/**
 *  This method returns the matching property value (to the given 
 *  corresponding key)
 *
 *  @param sName is the key of the required property.
 *  @return If it is found then matching property value is returned. If not found then it
 *      will return an empty string.
 */  
    virtual const void* getProperty(const AxisChar* sName)=0;

/**
 *  This method returns the matching property value (to the given 
 *  corresponding key)
 *
 *   @param  pachName is the key of the required property.
 *   @return If it is found then matching property value is returned.
 *      If not found NULL is returned.
 */  
    virtual void* getComplexProperty(const AxisChar* pachName)=0;

/**
 *  Returns the current operation name.
 *
 *   @return This method will return the OperationName.
 */ 
    virtual const AxisChar* AXISCALL getOperationName()=0;

/**
 *  This method will assign the current instance of SoapSerializer
 *  to the given IWrapperSoapSerializer pointer-to-pointer.By calling this
 *  method a caller will have access to the SoapSerializer.
 *
 *  @param pIWSS is a pointer to pointer used to get access to the
 *      current instance of soapSerializer.
 */ 
    virtual void AXISCALL getSoapSerializer(IWrapperSoapSerializer** pIWSS)=0;

/** 
 *  This method will assign the current instance of SoapDeSerializer
 *  to the given IWrapperSoapDeSerializer pointer-to-pointer. By calling this
 *  method a caller will have access to the SoapDeSerializer.
 *
 *   @param pIWSDS is a pointer to pointer used to store the 
 *      current instance of SoapDeSerializer.
 */ 
    virtual void AXISCALL getSoapDeSerializer
        (IWrapperSoapDeSerializer** pIWSDS)=0;

/**
 *  This method will assign the current instance of SoapSerializer
 *  to the given IHandlerSoapSerializer pointer-to-pointer. By calling this
 *  method a caller will have access to the SoapSerializer. 
 *
 *   @param  pIHandlerSoapSerializer is a pointer to pointer used to store the
 *      current instance of soapSerializer.
 */ 
    virtual void getSoapSerializer
        (IHandlerSoapSerializer** pIHandlerSoapSerializer)=0;

/**
 *  This method will assign the current instance of SoapDeSerializer
 *  to the given IHandlerSoapDeSerializer pointer-to-pointer. By calling this
 *  method a caller will have access to the SoapDeSerializer.
 *
 *   @param pIHandlerSoapDeSerializer is a pointer to pointer used to store the
 *      current instance of soapDeSerializer.
 */ 
    virtual void getSoapDeSerializer
        (IHandlerSoapDeSerializer** pIHandlerSoapDeSerializer)=0;

/**
 *   This method will store the given username inside the MessageData object.
 *
 *   @param m_sUserName is the value that is passed to be set.
 */ 
    virtual void setUserName(string& m_sUserName)=0;

/**
 * This method returns the user name.
 *
 *   @return this method will return the UserName.
 */ 
    virtual string& getUserName()=0;

/**
 *  This method will return a boolean value which will say whether at the time
 *  of calling this method has already passed the pivot point.
 * 
 *   @return Returns true if the pivot point is past. Returns false if not.
*/ 
    virtual bool isPastPivot()=0;

/**
 *   This method is used to set the pivot point status.
 *
 *  @param bState is the value of the state that should be set. Set true if 
 *      pivot point is past. Set false if pivot point is not past yet.
 *  @return will return AXIS_SUCCESS to indicate successful operation.
*/ 
    virtual int setPastPivotState(bool bState)=0;
};

AXIS_CPP_NAMESPACE_END

#endif





