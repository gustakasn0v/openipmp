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
 
#ifndef __SOAPFAULTEXCEPTION_H_OF_AXIS_INCLUDED_
#define __SOAPFAULTEXCEPTION_H_OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <axis/AxisException.hpp>

AXIS_CPP_NAMESPACE_START

/**
 * @class SoapFaultException
 * @brief Superclass of all user-defined soap faults defined in the WSDL
 * 
 * SoapFaultException is the superclass of all user faults that are defined
 * in the WSDL. This enables a client application to catch all soap faults
 * in a single catch block. To catch a specific soap fault, a client
 * application should catch the class that represents the fault's complex
 * type. SoapFaultException is a simple class that encapsulates the fault
 * information and does not reference the SoapFault itself. This means it
 * can clean it's own storage in its destructor so the client application
 * doesn't have to.
 * 
 * @author Mark Whitlock
 */

class STORAGE_CLASS_INFO SoapFaultException :public AxisException
{
public:
	SoapFaultException();
	SoapFaultException(const AxisChar *code, const AxisChar *string, const AxisChar *actor, int exceptionCode);
	SoapFaultException(AxisException& ae);
	SoapFaultException(const SoapFaultException& copy);
	virtual SoapFaultException& operator=(SoapFaultException other);
	virtual ~SoapFaultException() throw();

	virtual const AxisChar *getFaultCode() const;
	virtual const AxisChar *getFaultString() const;
	virtual const AxisChar *getFaultActor() const;

	virtual void setFaultCode(const AxisChar *code);
	virtual void setFaultString(const AxisChar *string);
	virtual void setFaultActor(const AxisChar *actor);
	virtual void setExceptionCode(int code);

	/** @returns the fault string */
    virtual const char* what() throw();
    virtual const int getExceptionCode();
private:
	AxisChar *m_code;
	AxisChar *m_string;
	AxisChar *m_actor;
	int m_exceptionCode;
};

AXIS_CPP_NAMESPACE_END

#endif

