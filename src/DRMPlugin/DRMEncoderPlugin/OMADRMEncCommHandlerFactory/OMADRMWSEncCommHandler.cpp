/** \file OMADRMWSEncCommHandler.cpp

    Web service implementation of OMA DRM encoding communication handler.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "OMADRMWSEncCommHandler.h"
#include "ROAPParser.h"
#include "XMLFactory.h"

#include "ThreadSyncFactory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*!  \brief  Class used for handling globals.
*/
class WSGlobalHandler {
public:
  /*!  \brief  Constructor.

      If fails, throws OMADRMCommException.
  */
  WSGlobalHandler(): aMutex(ThreadSyncFactory::GetGlobalMutex()) {
    if (aMutex == 0) {
      throw OMADRMCommException();
    }
  }

  /*!  \brief  Destructor.
  */
  ~WSGlobalHandler() {
    if (aMutex != 0) delete aMutex; aMutex = 0;
  }

  /*!  \brief  Get messenger mutex.

      \returns  Messenger mutex.
  */
  IMutex* GetMutex() {
    return aMutex;
  }

private:
  IMutex* aMutex;
};

static WSGlobalHandler wsGlobalHandler;

/*! \brief  Constructor.

    \param  logger      message logger.

    If fails, throws OMADRMCommException.
*/
OMADRMWSEncCommHandler::OMADRMWSEncCommHandler(DRMLogger& logger): agent(0), ws(0), commLogger(logger) {
  if (wsGlobalHandler.GetMutex() == 0) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::ctor: global mutex is zero...");
    throw OMADRMCommException();
  }
  if (wsGlobalHandler.GetMutex()->Lock(EVENT_WAIT_TIME) == false) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::ctor: cannot lock global mutex...");
    throw OMADRMCommException();
  }

  try {
    ws = new OMADRMWS();
  }
  catch(AxisException& e) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::ctor: axis exception -> " + std::string(e.what()) + "...");
    throw OMADRMCommException();
  }
  catch (...) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::ctor: axis exception (unknown)...");
    throw OMADRMCommException();
  }

  ws->setTransportTimeout(10000);
}

/*! \brief  Destructor.

    If fails, throws OMADRMCommException.
*/
OMADRMWSEncCommHandler::~OMADRMWSEncCommHandler() {
  if (wsGlobalHandler.GetMutex() == 0) {
    return;
  }
  if (ws != 0) delete ws; ws = 0;
  wsGlobalHandler.GetMutex()->Release();
}

/*! \brief  Send add content encryption key request.

    \param  request             input, add content encryption key request.
    \param  url                 input, URL where to send the message.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMWSEncCommHandler::SendAddContentKeyRequest(const NZSPtr<AddContentKeyRequest>&
    request, const NZSPtr<URIValue>& url) {
  if (agent == 0) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddContentKeyRequest: zero agent...");
    return false;
  }

  std::string uri = "http://"  + url->Get() + "/OMADRMWS/services/OMADRMWebService";
  ws->setEndPoint(uri.data());

  std::string encoded = request->XmlEncode();
  WSAddContentKeyRequest wsreq;
  wsreq.msg = (char*)(encoded.data());
  try {
    WSAddContentKeyResponse* wsresp = ws->addContentKey(&wsreq);
    if (wsresp == 0) {
      commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddContentKeyRequest: zero response...");
      return false;
    }
    encoded = wsresp->msg;
    if (wsresp->msg != 0) delete[] wsresp->msg;
    delete wsresp;
  }
  catch (AxisException& e) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddContentKeyRequest: axis exception -> " + std::string(e.what()) + "...");
    return false;
  }

  IXMLDocument* doc = XMLFactory::DecodeDocument(encoded, commLogger);
  if (doc == 0) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddContentKeyRequest: XML parsing response error...");
    return false;
  }
  IXMLElement* xml = doc->GetRootElement();
  if (xml == 0) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddContentKeyRequest: response root element missing...");
    delete doc;
    return false;
  }
  //  Quick check on the xml data.
  if (xml->GetName() != "addContentKeyResponse") {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddContentKeyRequest: response root element error...");
    delete doc;
    return false;
  }
  SPtr<AddContentKeyResponse> response;
  try {
    response = ROAPParser::ParseAddContentKeyResponse(xml, commLogger);
  }
  catch (ROAPParserException) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddContentKeyRequest: ROAP parsing response error ...");
    delete doc;
    return false;
  }
  delete doc;

  agent->HandleAddContentKeyResponse(response);

  return true;
}

/*! \brief  Send add rights for device for content request.

    \param  request             input, add rights for device for content request.
    \param  url                 input, URL where to send the message.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMWSEncCommHandler::SendAddDeviceRightsRequest(const NZSPtr<AddDeviceRightsRequest>&
    request, const NZSPtr<URIValue>& url) {
  if (agent == 0) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddDeviceRightsRequest: zero agent...");
    return false;
  }

  std::string uri = "http://" + url->Get() + "/OMADRMWS/services/OMADRMWebService";
  ws->setEndPoint(uri.data());

  std::string encoded = request->XmlEncode();
  WSAddDeviceRightsRequest wsreq;
  wsreq.msg = (char*)(encoded.data());
  try {
    WSAddDeviceRightsResponse* wsresp = ws->addDeviceRights(&wsreq);
    if (wsresp == 0) {
      commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddDeviceRightsRequest: zero response...");
      return false;
    }
    encoded = wsresp->msg;
    if (wsresp->msg != 0) delete[] wsresp->msg;
    delete wsresp;
  }
  catch (AxisException& e) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddDeviceRightsRequest: axis exception -> " + std::string(e.what()) + "...");
    return false;
  }

  IXMLDocument* doc = XMLFactory::DecodeDocument(encoded, commLogger);
  if (doc == 0) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddDeviceRightsRequest: XML parsing response error...");
    return false;
  }
  IXMLElement* xml = doc->GetRootElement();
  if (xml == 0) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddDeviceRightsRequest: response root element missing...");
    delete doc;
    return false;
  }
  //  Quick check on the xml data.
  if (xml->GetName() != "addDeviceRightsResponse") {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddDeviceRightsRequest: response root element error...");
    delete doc;
    return false;
  }
  SPtr<AddDeviceRightsResponse> response;
  try {
    response = ROAPParser::ParseAddDeviceRightsResponse(xml, commLogger);
  }
  catch (ROAPParserException) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::SendAddDeviceRightsRequest: ROAP parsing response error...");
    delete doc;
    return false;
  }
  delete doc;

  agent->HandleAddDeviceRightsResponse(response);

  return true;
}

/*! \brief  Set up all neccessary data and start message delivering/receiving.

    \param  omaagent          input, OMA DRM encoding agent.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMWSEncCommHandler::Run(IOMADRMEncAgent* omaagent) {
  agent = omaagent;
  if (agent == 0) {
    commLogger.UpdateLog("OMADRMWSEncCommHandler::Run: zero agent...");
    return false;
  }
  return true;
}

} // namespace DRMPlugin
