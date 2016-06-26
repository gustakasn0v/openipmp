/**	\file WSOsmsOpenIPMPMessenger.cpp

	Implementation of osms openIPMP messenger using web service.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

*/
#include <iostream>
#include <strstream>
#include <string>

#include "WSOsmsOpenIPMPMessenger.h"

#pragma warning(disable: 4786)

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Constructor.

    Use the information provided in the XML document.

    Optional tags in the XML file are:
     - ROOT.P12FilePath
     - ROOT.RandomNumberFilePath.

    If ROOT.P12FilePath tag is not present, p12 path is set to \localsecurity\.
    If ROOT.RandomNumberFilePath tag is not present, random number file path is
    set to .\entropy.dat.
    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <P12FilePath>\localsecurity\</P12FilePath>
     <RandomNumberFilePath>.\entropy.dat</RandomNumberFilePath>
    </ROOT>

    \endverbatim

    \param    xmlDoc          input, XML document.
    \param    logger          input-output, message logger.

    If constructor fails, it throws OpenIPMPMessengerException and logger
    contains error description.
*/
WSOsmsOpenIPMPMessenger::WSOsmsOpenIPMPMessenger(IXMLElement* xmlDoc, DRMLogger& logger): 
	OsmsOpenIPMPMessenger(xmlDoc, logger), ws(0) {
  try {
    ws = new OsmsWebService();
  }
  catch(AxisException& e) {
    messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::ctor: axis exception -> " + std::string(e.what()) + "...");
    throw OpenIPMPMessengerException();
  }
  catch (...) {
    messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::ctor: axis exception (unknown)...");
    throw OpenIPMPMessengerException();
  }
  ws->setTransportTimeout(3000); // http timeout
}

WSOsmsOpenIPMPMessenger::~WSOsmsOpenIPMPMessenger() {
  delete ws;
}

void WSOsmsOpenIPMPMessenger::SetServiceEndpoint(const std::string& hostIP, const int hostPort) {
/*
    std::strstream hP_string;
    hP_string << hostPort << '\0';
	std::string uri = std::string("http://") + hostIP + std::string(":") + 
        hP_string.str() + std::string("/openipmp/services/OsmsWebService");
*/
	std::string uri = std::string("http://") + hostIP + std::string(":") + 
        IntToString(hostPort) + std::string("/openipmp/services/OsmsWebService");
	ws->setServiceEndpoint(uri);
}


bool WSOsmsOpenIPMPMessenger::SetSoapHeaders(const std::string& userName, const std::string& password) {
		
	IHeaderBlock *phb;
	BasicNode* pnode;
	
	phb = ws->createSOAPHeaderBlock("userName", "http://ws.server.osms.mutable.com", "ns1");
	pnode = phb->createChild(CHARACTER_NODE);
	pnode->setValue(userName.c_str());
	phb->addChild(pnode);
	
	phb = ws->createSOAPHeaderBlock("password", "http://ws.server.osms.mutable.com", "ns1");
	pnode = phb->createChild(CHARACTER_NODE);
	pnode->setValue(password.c_str());
	phb->addChild(pnode);

	return true;
}


bool WSOsmsOpenIPMPMessenger::CleanSoapHeaders() {
	while (ws->getFirstSOAPHeaderBlock() != NULL)
		ws->deleteCurrentSOAPHeaderBlock();

	return true;
}


/*! \brief  Assign content identifier using osms message via web service.

    \param    userName          input, user's name.
    \param    password          input, user's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    request           input, content identifier request.
    \param    response          output, content identifier response.

    \returns  Boolean indicating success or failure.
*/
bool WSOsmsOpenIPMPMessenger::OsmsAssignContentID(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageRegisterContentAssignIdentifierRequest* request,
    osmsMessageRegisterContentAssignIdentifierResponse** response) {
	
	SetServiceEndpoint(hostIP, hostPort);
	CleanSoapHeaders();
	SetSoapHeaders(userName, password);

	OsmsRegisterContentAssignIdentifierRequest req;
	req.metadataType = request->getMetadataType();
	req.metadataXml = request->getMetadataXml();
	
	try {
		OsmsRegisterContentAssignIdentifierResponse* resp = ws->registerContentAssignIdentifier(&req);
		
		*response = new osmsMessageRegisterContentAssignIdentifierResponse();
		(*response)->setMetadataType(resp->metadataType);
		(*response)->setMetadataXml(resp->metadataXml);

		CleanSoapHeaders();

    if (resp->metadataType != 0) delete[] resp->metadataType;
    if (resp->metadataXml != 0) delete[] resp->metadataXml;
    delete resp;

		return true;
	}
	catch(const OsmsUserLoginFault&) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsAssignContentID: OsmsUserLoginFault");
		return false;
	}
	catch(const OsmsRegisterContentAssignIdentifierFault&) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsAssignContentID: OsmsRegisterContentAssignIdentifierFault");
		return false;
	}
	catch(AxisException& e) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsAssignContentID: axis exception -> " + std::string(e.what()) + "...");
		return false;
	}
}


/*! \brief  Register content encryption key with respect to content identifier
            using osms message via web service.

    \param    userName          input, user's name.
    \param    password          input, user's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    request           input, register content/key request.
    \param    response          output, register content/key response.

    \returns  Boolean indicating success or failure.
*/
bool WSOsmsOpenIPMPMessenger::OsmsRegisterKeyForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageRegisterDigitalItemInstanceRequest* request,
    osmsMessageRegisterDigitalItemInstanceResponse** response) {

	SetServiceEndpoint(hostIP, hostPort);
	CleanSoapHeaders();
	SetSoapHeaders(userName, password);

	OsmsRegisterDigitalItemInstanceRequest req;
	req.auxDataXml = request->getAuxDataXml();
	req.keyXml = request->getKeyXml();
	req.metadataType = request->getMetadataType();
	req.metadataXml = request->getMetadataXml();
	
	try {
		OsmsRegisterDigitalItemInstanceResponse* resp = ws->registerDigitalItemInstance(&req);
		
		*response = new osmsMessageRegisterDigitalItemInstanceResponse();
		(*response)->setAuxDataXml(resp->auxDataXml);
		(*response)->setMetadataType(resp->metadataType);
		(*response)->setMetadataXml(resp->metadataXml);
		(*response)->setSignatureXml(resp->signatureXml);

		CleanSoapHeaders();

    if (resp->auxDataXml != 0) delete[] resp->auxDataXml;
    if (resp->metadataType != 0) delete[] resp->metadataType;
    if (resp->metadataXml != 0) delete[] resp->metadataXml;
    if (resp->signatureXml != 0) delete[] resp->signatureXml;
    delete resp;

		return true;
	}
	catch(const OsmsUserLoginFault&) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsRegisterKeyForContent: OsmsUserLoginFault");
		return false;
	}
	catch(const OsmsRegisterDigitalItemInstanceFault&) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsRegisterKeyForContent: OsmsRegisterDigitalItemInstanceFault");
		return false;
	}
	catch(AxisException& e) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsRegisterKeyForContent: axis exception -> " + std::string(e.what()) + "...");
		return false;
	}
}


/*! \brief  Get content encryption key with respect to content identifier using
            osms message via web service.

    \param    userName          input, user's name.
    \param    password          input, user's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    request           input, get key request.
    \param    response          output, get key response.

    \returns  Boolean indicating success or failure.
*/
bool WSOsmsOpenIPMPMessenger::OsmsGetKeyForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageLicenseRequest* request, osmsMessageLicenseResponse** response) {

	SetServiceEndpoint(hostIP, hostPort);
	CleanSoapHeaders();
	SetSoapHeaders(userName, password);

	OsmsLicenseRequest req;
	req.contentId = request->getContentId();
	req.rightsInfo = request->getRightsInfo();

	try {
		OsmsLicenseResponse* resp = ws->license(&req);
		
		*response = new osmsMessageLicenseResponse();
		(*response)->setLicense(resp->license);

		CleanSoapHeaders();

    if (resp->license != 0) delete[] resp->license;
    delete resp;

		return true;
	}
	catch(const OsmsUserLoginFault&) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsGetKeyForContent: OsmsUserLoginFault");
		return false;
	}
	catch(const OsmsLicenseFault&) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsGetKeyForContent: OsmsLicenseFault");
		return false;
	}
	catch(AxisException& e) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsGetKeyForContent: axis exception -> " + std::string(e.what()) + "...");
		return false;
	}
}


/*! \brief  Grant license to user for the content identifier using 
            osms message via web service.

    \param    userName          input, granter's name.
    \param    password          input, granter's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    request           input, grant license request.
    \param    response          output, grant license response.

    \returns  Boolean indicating success or failure.
*/
bool WSOsmsOpenIPMPMessenger::OsmsGrantLicenseForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageRightsAuthorizationRequest* request,
    osmsMessageRightsAuthorizationResponse** response) {

	SetServiceEndpoint(hostIP, hostPort);
	CleanSoapHeaders();
	SetSoapHeaders(userName, password);

	OsmsRightsAuthorizationRequest req;
	req.contentId = request->getContentId();
	req.licenseType = request->getLicenseType();
	req.userName = request->getUserName();
    req.startDate.tm_sec = request->getStartDate()->getSeconds();
    req.startDate.tm_min = request->getStartDate()->getMinutes();
    req.startDate.tm_hour = request->getStartDate()->getHours();
    req.startDate.tm_mday = request->getStartDate()->getDay();
    req.startDate.tm_mon = request->getStartDate()->getMonth() - 1 ; // tm::tm_mon (months since January - [0,11])
    req.startDate.tm_year = request->getStartDate()->getYear() - 1900; // tm::tm_year (years since 1900)
    req.endDate.tm_sec = request->getEndDate()->getSeconds();
    req.endDate.tm_min = request->getEndDate()->getMinutes();
    req.endDate.tm_hour = request->getEndDate()->getHours();
    req.endDate.tm_mday = request->getEndDate()->getDay();
    req.endDate.tm_mon = request->getEndDate()->getMonth() - 1; // tm::tm_mon (months since January - [0,11])
    req.endDate.tm_year = request->getEndDate()->getYear() - 1900; // tm::tm_year (years since 1900)

	try {
		OsmsRightsAuthorizationResponse* resp = ws->rightsAuthorization(&req);
		
		*response = new osmsMessageRightsAuthorizationResponse();
		(*response)->setTransactionId(resp->transactionId);

		CleanSoapHeaders();

    if (resp->transactionId != 0) delete[] resp->transactionId;
    delete resp;

		return true;
	}
	catch(const OsmsUserLoginFault&) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsGrantLicenseForContent: OsmsUserLoginFault");
		return false;
	}
	catch(const OsmsRightsAuthorizationFault&) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsGrantLicenseForContent: OsmsRightsAuthorizationFault");
		return false;
	}
	catch(AxisException& e) {
		messengerLogger.UpdateLog("WSOsmsOpenIPMPMessenger::OsmsGrantLicenseForContent: axis exception -> " + std::string(e.what()) + "...");
		return false;
	}
}

} // namespace DRMPlugin
