/** \file OMADRMWSDecCommHandler.cpp

    Web service implementation of OMA DRM decoding communication handler.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "OMADRMWSDecCommHandler.h"
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
OMADRMWSDecCommHandler::OMADRMWSDecCommHandler(DRMLogger& logger): agent(0), ws(0), commLogger(logger) {
  if (wsGlobalHandler.GetMutex() == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::ctor: global mutex is zero...");
    throw OMADRMCommException();
  }
  if (wsGlobalHandler.GetMutex()->Lock(EVENT_WAIT_TIME) == false) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::ctor: cannot lock global mutex...");
    throw OMADRMCommException();
  }

  try {
    ws = new OMADRMWS();
  }
  catch(AxisException& e) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::ctor: axis exception -> " + std::string(e.what()) + "...");
    wsGlobalHandler.GetMutex()->Release();
    throw OMADRMCommException();
  }
  catch (...) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::ctor: axis exception (unknown)...");
    wsGlobalHandler.GetMutex()->Release();
    throw OMADRMCommException();
  }
  ws->setTransportTimeout(10000);
}

/*! \brief  Destructor.

    If fails, throws OMADRMCommException.
*/
OMADRMWSDecCommHandler::~OMADRMWSDecCommHandler() {
  if (wsGlobalHandler.GetMutex() == 0) {
    return;
  }
  if (ws != 0) delete ws; ws = 0;
  wsGlobalHandler.GetMutex()->Release();
}

/*! \brief  Send initial content rights objects request.

    \param  request             input, content rights objects request.
    \param  url                 input, URL where to send the message.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMWSDecCommHandler::SendInitialRORequest(const NZSPtr<InitialRORequest>&
    request, const NZSPtr<URIValue>& url) {
  if (agent == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: zero agent...");
    return false;
  }
  std::string uri = "http://"  + url->Get() + "/OMADRMWS/services/OMADRMWebService";
  ws->setEndPoint(uri.data());

  IXMLDocument* doc = 0;
  IXMLElement* xml = 0;
  std::string encoded = request->XmlEncode();
  WSInitialRORequest wsinitreq;
  wsinitreq.msg = (char*)(encoded.data());
  try {
    WSROAcquisitionTrigger* wsrotrigger = ws->initialRO(&wsinitreq);
    if (wsrotrigger == 0) {
      commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: received zero trigger...");
      return false;
    }
    encoded = wsrotrigger->msg;
    if (wsrotrigger->msg != 0) delete[] wsrotrigger->msg;
    delete wsrotrigger;
  }
  catch (AxisException& e) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: axis exception -> " + std::string(e.what()) + "...");
    return false;
  }
  catch (...) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: unknown exception...");
    return false;
  }

  doc = XMLFactory::DecodeDocument(encoded, commLogger);
  if (doc == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: trigger XML parsing error...");
    return false;
  }
  xml = doc->GetRootElement();
  if (xml == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: trigger root element missing...");
    delete doc;
    return false;
  }
  //  Quick check on the xml data.
  if (xml->GetName() != "roapTrigger") {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: trigger root element error...");
    delete doc;
    return false;
  }
  if (xml->GetChildElement("roAcquisition") == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: trigger root element error...");
    delete doc;
    return false;
  }
  SPtr<RORequest> roreq;
  try {
    if (xml->GetChildElement("roAcquisition")->GetChildElement("domainID") != 0) {
      SPtr<DomainROTrigger> rotrigger = ROAPParser::ParseDomainROTrigger(xml, commLogger);
      roreq = agent->HandleDomainROTrigger(rotrigger);
    } else {
      SPtr<NDomainROTrigger> rotrigger = ROAPParser::ParseNDomainROTrigger(xml, commLogger);
      roreq = agent->HandleNDomainROTrigger(rotrigger);
    }
  }
  catch (ROAPParserException) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: trigger ROAP parsing error...");
    delete doc;
    return false;
  }
  delete doc;
  if (roreq == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: zero rights objects request...");
    return false;
  }
  encoded = roreq->XmlEncode();
  WSRORequest wsroreq;
  wsroreq.msg = (char*)(encoded.data());
  try {
    WSROResponse* wsroresponse = ws->roAcquisition(&wsroreq);
    if (wsroresponse == 0) {
      commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: zero rights objects response...");
      return false;
    }
    encoded = wsroresponse->msg;
    if (wsroresponse->msg != 0) delete[] wsroresponse->msg;
    delete wsroresponse;
  }
  catch (AxisException& e) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: axis exception -> " + std::string(e.what()) + "...");
    return false;
  }
  catch (...) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: unknown exception...");
    return false;
  }

  doc = XMLFactory::DecodeDocument(encoded, commLogger);
  if (doc == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: rights objects response XML parsing error...");
    return false;
  }
  xml = doc->GetRootElement();
  if (xml == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: rights objects response root element missing...");
    delete doc;
    return false;
  }
  //  Quick check on the xml data.
  if (xml->GetName() != "ROResponse") {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: rights objects response root element error...");
    delete doc;
    return false;
  }
  if (xml->GetChildAttribute("", "status") == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: rights objects response root element error...");
    delete doc;
    return false;
  }
  try {
    if (xml->GetChildAttribute("", "status")->GetStrValue() == "Success") {
      SPtr<SuccessTwoPassROResponse> roresponse = ROAPParser::ParseSuccessTwoPassROResponse(xml, commLogger);
      agent->HandleSuccessROResponse(roresponse);
    } else {
      SPtr<UnsuccessTwoPassROResponse> roresponse = ROAPParser::ParseUnsuccessTwoPassROResponse(xml, commLogger);
      agent->HandleUnsuccessROResponse(roresponse);
    }
  }
  catch (ROAPParserException) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendInitialRORequest: rights objects response ROAP parsing error...");
    delete doc;
    return false;
  }
  delete doc;

  return true;
}

/*! \brief  Send device hello message to the server.

    \param  request             input, device hello message.
    \param  url                 input, URL where to send the message.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMWSDecCommHandler::SendDeviceHello(const NZSPtr<DeviceHelloRequest>& request,
    const NZSPtr<URIValue>& url) {
  if (agent == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: zero agent...");
    return false;
  }
  std::string uri = "http://"  + url->Get() + "/OMADRMWS/services/OMADRMWebService";
  ws->setEndPoint(uri.data());

  IXMLDocument* doc = 0;
  IXMLElement* xml = 0;
  std::string encoded = request->XmlEncode();
  WSDeviceHello wsdevhello;
  wsdevhello.msg = (char*)(encoded.data());
  try {
    WSRIHello* wsrihello = ws->hello(&wsdevhello);
    if (wsrihello == 0) {
      commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: received zero rights issuer hello...");
      return false;
    }
    encoded = wsrihello->msg;
    if (wsrihello->msg != 0) delete[] wsrihello->msg;
    delete wsrihello;
  }
  catch (AxisException& e) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: axis exception -> " + std::string(e.what()) + "...");
    return false;
  }
  catch (...) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: unknown exception...");
    return false;
  }

  doc = XMLFactory::DecodeDocument(encoded, commLogger);
  if (doc == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: rights issuer hello XML parsing error...");
    return false;
  }
  xml = doc->GetRootElement();
  if (xml == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: rights issuer hello root element missing...");
    delete doc;
    return false;
  }
  //  Quick check on the xml data.
  if (xml->GetName() != "RIHello") {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: rights issuer hello root element error...");
    delete doc;
    return false;
  }
  if (xml->GetChildAttribute("", "status") == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: rights issuer hello root element error...");
    delete doc;
    return false;
  }
  SPtr<RegRequest> regreq;
  try {
    if (xml->GetChildAttribute("", "status")->GetStrValue() == "Success") {
      SPtr<SuccessRIHello> rihello = ROAPParser::ParseSuccessRIHello(xml, commLogger);
      regreq = agent->HandleSuccessRIHello(rihello);
    } else {
      SPtr<UnsuccessRIHello> rihello = ROAPParser::ParseUnsuccessRIHello(xml, commLogger);
      agent->HandleUnsuccessRIHello(rihello);
    }
  }
  catch (ROAPParserException) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: rights issuer hello ROAP parsing error...");
    delete doc;
    return false;
  }
  delete doc;
  if (regreq == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: zero registration request...");
    return false;
  }
  encoded = regreq->XmlEncode();
  WSRegistrationRequest wsregreq;
  wsregreq.msg = (char*)(encoded.data());
  try {
    WSRegistrationResponse* wsregresp = ws->registration(&wsregreq);
    if (wsregresp == 0) {
      commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: received zero registration response...");
      return false;
    }
    encoded = wsregresp->msg;
    if (wsregresp->msg != 0) delete[] wsregresp->msg;
    delete wsregresp;
  }
  catch (AxisException& e) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: axis exception -> " + std::string(e.what()) + "...");
    return false;
  }
  catch (...) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: unknown exception...");
    return false;
  }

  doc = XMLFactory::DecodeDocument(encoded, commLogger);
  if (doc == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: registration response XML parsing error...");
    return false;
  }
  xml = doc->GetRootElement();
  if (xml == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: registration response root element missing...");
    delete doc;
    return false;
  }
  //  Quick check on the xml data.
  if (xml->GetName() != "RegistrationResponse") {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: registration response root element error...");
    delete doc;
    return false;
  }
  if (xml->GetChildAttribute("", "status") == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: registration response root element error...");
    delete doc;
    return false;
  }
  try {
    if (xml->GetChildAttribute("", "status")->GetStrValue() == "Success") {
      SPtr<SuccessRegResponse> regresp = ROAPParser::ParseSuccessRegResponse(xml, commLogger);
      agent->HandleSuccessRegResponse(regresp);
    } else {
      SPtr<UnsuccessRegResponse> regresp = ROAPParser::ParseUnsuccessRegResponse(xml, commLogger);
      agent->HandleUnsuccessRegResponse(regresp);
    }
  }
  catch (ROAPParserException) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::SendDeviceHello: registration response ROAP parsing error...");
    delete doc;
    return false;
  }
  delete doc;

  return true;
}

/*! \brief  Send registration request message to the server.

    \param  request             input, registration request message.
    \param  url                 input, URL where to send the message.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMWSDecCommHandler::SendRegRequest(const NZSPtr<RegRequest>& request,
    const NZSPtr<URIValue>& url) {
  return true;
}

/*! \brief  Send rights objects request message to the server.

    \param  request             input, rights objects request message.
    \param  url                 input, URL where to send the message.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMWSDecCommHandler::SendRORequest(const NZSPtr<RORequest>& request,
    const NZSPtr<URIValue>& url) {
  return true;
}

/*! \brief  Send join domain request message to the server.

    \param  request             input, join domain request message.
    \param  url                 input, URL where to send the message.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMWSDecCommHandler::SendJoinDomainRequest(const NZSPtr<JoinDomainRequest>&
    request, const NZSPtr<URIValue>& url) {
  return true;
}

/*! \brief  Send leave domain request message to the server.

    \param  request             input, leave domain request message.
    \param  url                 input, URL where to send the message.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMWSDecCommHandler::SendLeaveDomainRequest(const NZSPtr<LeaveDomainRequest>&
    request, const NZSPtr<URIValue>& url) {
  return true;
}

/*! \brief  Set up all neccessary data and start message delivering/receiving.

    \param  omaagent          input, OMA DRM agent.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMWSDecCommHandler::Run(IOMADRMDecAgent* omaagent) {
  agent = omaagent;
  if (agent == 0) {
    commLogger.UpdateLog("OMADRMWSDecCommHandler::Run: zero agent...");
    return false;
  }
  return true;
}

} // namespace DRMPlugin
