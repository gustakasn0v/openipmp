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
 * @file ISoapFault.h
 *
 *
 */
#ifndef ISOAPFAULT_INCLUDED
#define ISOAPFAULT_INCLUDED


/**
 *  @class ISoapFault
 *  @brief Interface to represent SoapFault
 *
 *
 */
AXISC_STORAGE_CLASS_INFO void axiscDestroyISoapFault(AXISCHANDLE soapFault);

/** When a complex fault arrives this method can be used to
      * get the name of that fault. This is useful because once 
      * we have the fault name we can pass the information necessary
      * to deserialize it, back to the SoapFault class.
      * 
      * @return name of the complex fault
      */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetCmplxFaultObjectName(AXISCHANDLE soapFault);

/** Once we know the complex fault name we can pass the information such as the
      * knowledge to deserialize the complex fault by calling this method.
      *
      * @param deserialize callback function pointer
      * @param create callback function
      * @param delete callback function
      * @param name
      * @param url
      */
AXISC_STORAGE_CLASS_INFO void * axiscGetCmplxFaultObject(AXISCHANDLE soapFault, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/** To retrive a simple fault detail string
      *
      * @return Simple fault detail
      */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetSimpleFaultDetail(AXISCHANDLE soapFault);

/** To retrive the soap fault code
      *
      * @return fault code
      */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetFaultcode(AXISCHANDLE soapFault);

/** To retrive the soap fault string
      *
      * @return fault string
      */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetFaultstring(AXISCHANDLE soapFault);

/** To retrive the soap fault actor
      *
      * @return fault actor
      */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetFaultactor(AXISCHANDLE soapFault);
AXISC_STORAGE_CLASS_INFO int axiscSetFaultcode(AXISCHANDLE soapFault, const AxiscChar * sFaultcode);
AXISC_STORAGE_CLASS_INFO int axiscSetFaultstring(AXISCHANDLE soapFault, const AxiscChar * sFaultstring);
AXISC_STORAGE_CLASS_INFO int axiscSetFaultactor(AXISCHANDLE soapFault, const AxiscChar * sFaultactor);
AXISC_STORAGE_CLASS_INFO int axiscSetFaultDetailISoapFault(AXISCHANDLE soapFault, const AxiscChar * sFaultdetail);
AXISC_STORAGE_CLASS_INFO int axiscSetCmplxFaultObject(AXISCHANDLE soapFault, const void * pCmplxFaultObject);


#endif // ISOAPFAULT_INCLUDED
