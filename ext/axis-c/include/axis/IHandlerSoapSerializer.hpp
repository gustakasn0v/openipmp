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

#if !defined(_IHANDLERSOAPSERIALIZER_H____OF_AXIS_INCLUDED_)
#define _IHANDLERSOAPSERIALIZER_H____OF_AXIS_INCLUDED_

#include "IWrapperSoapSerializer.hpp"
#include "SoapEnvVersions.hpp"

AXIS_CPP_NAMESPACE_START

class IHeaderBlock;
/**
  * @class IHandlerSoapSerializer
  * @brief interface for the IHandlerSoapSerializer class. This interface is
  *	exposed to a Handler Writer, to let him manipulate on the Serialzer object.
  * Example usage is given below.
  * <PRE>
  * int ESHHandler::invoke(void *pvIMsg)
  * {
  *	IMessageData *pIMsg = (IMessageData*) pvIMsg;
  *  AxisChar* pachTemp;
  *	if(pIMsg->isPastPivot()) {
  *		//this is a response
  *
  *		IHandlerSoapSerializer* pISZ;
  *		pIMsg->getSoapSerializer(&pISZ);
  *
  *		IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock();
  *
  *		pIHeaderBlock->setLocalName("echoMeStringResponse");
  * </PRE>
  * 
  * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
  */
class IHandlerSoapSerializer : public IWrapperSoapSerializer

{
public:        
    virtual ~IHandlerSoapSerializer() {};

	/**
	  * Will create a Header Block and adds it to the Serializer.
	  *
	  * @return The created Header Block pointer will be returned, which the
	  * user can manipulate on it.
	  */
    virtual IHeaderBlock* createHeaderBlock()=0;

	/**
	  * Will create a Header Block using the given local name and the namespace
	  * uri, and adds it to the Serializer.
	  *
	  * @param pachLocalName The local name of the Header Block
	  * @param pachUri The namespace uri of the Header Block.
	  * @return The created Header Block pointer will be returned, which the
	  * user can manipulate on it.
	  */
    virtual IHeaderBlock*  createHeaderBlock(const AxisChar *pachLocalName, 
		const AxisChar *pachUri)=0;    

	/**
	  * Adds the given Header Block to the Serialzer.
	  *
	  * @param pBlk The Header Block to be added.
	  * @return AXIS_SUCCESS or AXIS_FAIL to indicate success or fail.
	  */
    virtual int AXISCALL addHeaderBlock(IHeaderBlock* pBlk)=0;

	/**
	  * Sets the SOAP Version.
	  * @param eSOAP_VERSION The SOAP version to set.
	  * @return AXIS_SUCCESS to indicate success.
	  */
    virtual int setSoapVersion(SOAP_VERSION eSOAP_VERSION)=0;

	/**
	  * Gets the Header Block. After returning the Header Block pointer, it 
	  * will not be removed from the available Header Block list of the 
	  * Serializer.The caller of this method should not delete the returned 
	  * pointer object.
	  */
	/*
	 * TO DO: Have to remove this method from this api. Logged this msg on
	 *  13Jan2005.
	virtual IHeaderBlock* getHeaderBlock() = 0;
	*/

	/**
	  * Gets and returns the Header Block of the given local name and 
	  * namespace uri.After returning the Header Block pointer, it will not be
	  * removed from the available Header Block list of the Serializer.
	  * The caller of this method should not delete the returned pointer 
	  * object.
	  */
	virtual IHeaderBlock* getHeaderBlock(const AxisChar *pcName, 
											 const AxisChar *pcNamespace) = 0;
     /**
      * Used with getNextHeaderBlock, it returns the first header block,
      * or NULL if there are no headers.
      */
     virtual IHeaderBlock* getFirstHeaderBlock()=0;
 
     /**
      * Used with getFirstHeaderBlock, it returns the next header block,
      * or NULL if there are no headers.
      */
     virtual IHeaderBlock* getNextHeaderBlock()=0;

	 /**
      * Used with getFirstHeaderBlock, it returns the current header block,
      * or NULL if:
	  *  - there are no headers, 
	  *  - or if the getFirstHeaderBlock method is not called at least once.
      */
     virtual IHeaderBlock* getCurrentHeaderBlock()=0;

    /*
     * A handler may get the entire soap body and encrypt/compress 
     * it and encode to either base64Binary or hexBinary before 
     * sending to the transport. So any handler in the response message 
     * path may use following functions to get the entire soap 
     * body / set encrypted and/or compressed and then encoded soap body
     * back to the Serializer
     */

    virtual int AXISCALL setBodyAsHexBinary(xsd__hexBinary body)=0;
    virtual int AXISCALL setBodyAsBase64Binary(xsd__base64Binary body)=0;
    virtual const AxisChar* AXISCALL getBodyAsString()=0;


/**
*Used to delete a header block
*
*/

virtual int deleteHeaderBlock(const AxisChar* pName, const AxisChar* pNamespace)=0;
/**
*Used to delete all the header block
*
*/
virtual int removeSoapHeader()=0;

	/**
	  * Adds the namespace declaration to the SOAP Envelope.
	  */
	virtual void addNamespaceToEnvelope(AxisChar *pachNamespaceURI, AxisChar* pachPrefix)=0;
};

AXIS_CPP_NAMESPACE_END

#endif 

