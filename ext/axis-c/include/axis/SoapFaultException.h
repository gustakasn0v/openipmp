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
#ifndef SOAPFAULTEXCEPTION_INCLUDED
#define SOAPFAULTEXCEPTION_INCLUDED


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
 */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateSoapFaultException(const AxiscChar * code, 
	const AxiscChar * string, const AxiscChar * actor, 
	int exceptionCode);
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscOperator=SoapFaultExceptionSoapFaultException(AXISCHANDLE soapFaultException, AXISCHANDLE other);
AXISC_STORAGE_CLASS_INFO void axiscDestroySoapFaultException(AXISCHANDLE soapFaultException);
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetFaultCode(AXISCHANDLE soapFaultException);
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetFaultString(AXISCHANDLE soapFaultException);
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetFaultActor(AXISCHANDLE soapFaultException);
AXISC_STORAGE_CLASS_INFO void axiscSetFaultCode(AXISCHANDLE soapFaultException, const AxiscChar * code);
AXISC_STORAGE_CLASS_INFO void axiscSetFaultString(AXISCHANDLE soapFaultException, const AxiscChar * string);
AXISC_STORAGE_CLASS_INFO void axiscSetFaultActor(AXISCHANDLE soapFaultException, const AxiscChar * actor);
AXISC_STORAGE_CLASS_INFO void axiscSetExceptionCode(AXISCHANDLE soapFaultException, int code);

/** @returns the fault string */
AXISC_STORAGE_CLASS_INFO const char * axiscWhatSoapFaultException(AXISCHANDLE soapFaultException);
AXISC_STORAGE_CLASS_INFO const int axiscGetExceptionCodeSoapFaultException(AXISCHANDLE soapFaultException);


#endif // SOAPFAULTEXCEPTION_INCLUDED
