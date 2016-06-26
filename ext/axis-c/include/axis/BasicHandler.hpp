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
 *
 *
 */

/**
 * @file BasicHandler.hpp
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com) *
 */
  
#if !defined(_BASICHANDLER_H__OF_AXIS_INCLUDED_)
#define _BASICHANDLER_H__OF_AXIS_INCLUDED_

#include <axis/IMessageData.hpp>
#include "GDefine.hpp"

AXIS_CPP_NAMESPACE_START

typedef enum { NORMAL_HANDLER, WEBSERVICE_HANDLER, CHAIN_HANDLER } HANDLER_TYPE;

typedef struct 
{
    int (AXISCALL* invoke)(void* _object, void* pMsg);
    void (AXISCALL* onFault)(void* _object, void* pMsg);
    int (AXISCALL* init)(void* _object);
    int (AXISCALL* fini)(void* _object);
    int (AXISCALL* getType)(void* _object);
    AXIS_BINDING_STYLE (AXISCALL* getBindingStyle)(void* _object);
} BasicHandlerFunctions;

typedef struct 
{
    void* _object; 
    /* present only for interfaces passed from C to C++ (eg:BasicHandler) */
    BasicHandlerFunctions* _functions;
} BasicHandler;

/**
  * @class HandlerBase
  * @brief interface for the Handlers. This is the base class for:
  *        - Handler 
  *        - WrapperClassHandler
  * In the Axis Architecture there are different types of Handlers :
  *        - NORMAL_HANDLER : A Handler which is used to process SOAP Headers.
  *        - WEBSERVICE_HANDLER : A web service is also considered as a Handler.
  *        - CHAIN_HANDLER : Handler Chains are also derived from Handler.
  * Each of these handlers will inherit from this HandlerBase which serves as
  * the base point for all the different types of Handlers.
  *
  * @author Susantha Kumara (skumara@virtusa.com)
  * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
  *
  */

/*
 * Revision 1.1  2004/06/14 roshan
 * Added doxygen comments to help autobuild API docs
 */

class HandlerBase
{
public:
    /**
      * Constructor.
      */
    HandlerBase(){};

    /**
      * Destructor.
      */
    virtual ~HandlerBase(){};

    /**
      * The invoke method is automatically called by the Axis Engine when it
      * needs to execute a Handler. The main task of the handler which a
      * Handler writer expects the Handler to be performed needs to be written
      * within the invoke method of the Handler.
      *
      * A example code segment within a invoke method which is written to
      * process a SOAP Header is as following:
      * <PRE>
      * int ESHHandler::invoke(void *pvIMsg)
      * {
      * IMessageData *pIMsg = (IMessageData*) pvIMsg;
      *    AxisChar* pachTemp;
      *    if(pIMsg->isPastPivot()) {
      *        //this is a response
      *
      *        IHandlerSoapSerializer* pISZ;
      *        pIMsg->getSoapSerializer(&pISZ);
      *
      *        IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock();
      *
      *        pIHeaderBlock->setLocalName("echoMeStringResponse");
      *        pIHeaderBlock->setURI("http://soapinterop.org/echoheader/");
      *
      *        pachTemp = "EchoStringHeaderHandlerPr1.id";
      *
      *        const AxisChar* pachHeaderVal = pIMsg->getProperty(pachTemp);
      *        printf("in the ESHHandler::Invoke : %s\n",pachHeaderVal);
      *
      *        BasicNode* pBasicNode = pIHeaderBlock->createChild(CHARACTER_NODE);
      *        pBasicNode->setValue(pachHeaderVal);
      *
      *        pIHeaderBlock->addChild(pBasicNode);
      *
      * } else {
      *        //this is a request
      *
      *        IHandlerSoapDeSerializer* pIHandlerSoapDeSerializer;
      *        pIMsg->getSoapDeSerializer(&pIHandlerSoapDeSerializer);
      *
      *        IHeaderBlock* pIHeaderBlock= pIHandlerSoapDeSerializer->getHeaderBlock("echoMeString", "http://soapinterop.org/echoheader/");
      *
      *        if (pIHeaderBlock != NULL) {
      *
      *            const BasicNode* pBasicNode= pIHeaderBlock->getFirstChild();
      *
      *            const AxisChar* pachHeaderValue;
      *
      *            if (pBasicNode != NULL)
      *            {
      *                if((pBasicNode->getNodeType()) == CHARACTER_NODE) {
      *                    pachHeaderValue= pBasicNode->getValue();
      *                } else {
      *                    pachHeaderValue = "This was not the expected value Ros";
      *                }
      *            } else
      *            {
      *                pachHeaderValue = "pBascNode is NULL";
      *            }
      *
      *            AxisChar* pachTmpValue = (AxisChar*) malloc(strlen(pachHeaderValue) + 4);
      *            strcpy(pachTmpValue, pachHeaderValue);
      *
      *            pachTemp = "EchoStringHeaderHandlerPr1.id";
      *            pIMsg->setProperty(pachTemp, pachTmpValue);
      *
      *            free(pachTmpValue);
      *
      *
      *        } else {
      *            //do some thing
      *        }
      *
      *    }
      *
      *    return AXIS_SUCCESS;
      *    }
      * </PRE>
      *
      * In case of a Web Service Handler the invoke method should do what is
      * required by a web service invoke method, which is different from the
      * above shown example.
      *
      * @param pMsg The MessageData object pointer. This MessageData object is
      * passed to every handler when serving to a client request. The handler
      * writer can get access to objects such as:
      *        - IHandlerSoapDeSerializer
      *        - IHandlerSoapSerializer
      *        - The properties/data/info which are set by other handlers
      *        - The properties/data/info which is set by the Client Stub in case
      *          the Handler is a Client side Handler.
      *                                                etc.
      * @return AXIS_SUCCESS or AXIS_FAIL to indicate success or fail.
      */
    virtual int AXISCALL invoke(void* pMsg)=0;

    /**
      * Called when ever a fault is occured within the handler. The tasks which
      * needs to be persormed when ever an error occurs within a Handler has
      * to be written within this method.
      *
      * @param mMsg The MessageData object pointer. This MessageData object is
      * passed to every handler when serving to a client request. The handler
      * writer can get access to objects such as:
      *        - IHandlerSoapDeSerializer
      *        - IHandlerSoapSerializer
      *                                etc.
      * @return AXIS_SUCCESS or AXIS_FAIL to indicate success or fail.
      */
    virtual void AXISCALL onFault(void* mMsg)=0;

    /**
      * The initialization tasks which needs to be performed within a Handler
      * has to be written here. This method will be automatically called by the
      * Axis Engine when it loads a handler.
      *
      * @return AXIS_SUCCESS or AXIS_FAIL to indicate success or fail.
      */
    virtual int AXISCALL init()=0;

    /**
      * The finalization tasks which needs to be performed within a Handler
      * has to be written here. This method will be automatically called by the
      * Axis Engine when it unloads a handler.
      *
      * @return AXIS_SUCCESS or AXIS_FAIL to indicate success or fail.
      */
    virtual int AXISCALL fini()=0;

    /**
      * Gets and returns the type of the handler. The return value could be :
      *        - NORMAL_HANDLER
      *        - WEBSERVICE_HANDLER
      *        - CHAIN_HANDLER
      *
      *    @return This returns the following depending on the actual Handler
      * type:
      *        - NORMAL_HANDLER : In case of a normal Handler which is used to
      *                           process SOAP Headers.
      *        - WEBSERVICE_HANDLER : In case of a Web Service.
      *        - CHAIN_HANDLER : In case of a HandlerChain
      */
    virtual int AXISCALL getType()=0;
};

AXIS_CPP_NAMESPACE_END

#endif 


