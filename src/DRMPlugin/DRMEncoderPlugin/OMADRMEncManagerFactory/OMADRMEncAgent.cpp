/**	\file OMADRMEncAgent.cpp

	OMA DRM agent and manager used in encoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OMADRMEncAgent.h"
#include "CipherFactory.h"
#include "Base64Factory.h"
#include "IDRMEncManager.h"
#include "ThreadSyncFactory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Constructor.

    \param  xml         XML document.
    \param  logger      message logger.

    If fails, throws DRMEncManagerException.
*/
OMADRMEncAgent::OMADRMEncAgent(IXMLElement* xml, DRMLogger& logger):
    exitFlag(false), mutex(ThreadSyncFactory::GetMutex(logger)), nonceToWait(),
    noncer(new OMADRMNonceCreator()), nonceToExit(), agentLogger(logger) {
  if (mutex == 0) {
    throw DRMEncManagerException();
  }
}

OMADRMEncAgent::~OMADRMEncAgent() {
  mutex->Lock();
  //  Here we depend on the fact that all communication handlers pointing
  //  on this agent are destroyed, and cannot call this agent's handle routines.
  exitFlag = true;
  std::map<NZSPtr<ROAPNonce>, IEvent*>::iterator iter = nonceToWait.begin();
  while (iter != nonceToWait.begin()) {
    iter->second->Set();
    iter++;
  }
  std::vector<IEvent*> exs;
  iter = nonceToExit.begin();
  while (iter != nonceToExit.end()) {
    exs.push_back(iter->second);
    iter++;
  }
  mutex->Release();
  WaitForEvents(exs);
  //  This should happen immediately.
  mutex->Lock();
  for (unsigned int i = 0; i < exs.size(); i++) {
    delete exs[i];
  }
  mutex->Release();
  delete mutex;
}

/*! \brief  Add license for content.

    Use the information provided in the given XML document.

    Optional tags in the XML file are:
     - ROOT.License

    Mandatory tags in the XML file are:
     - ROOT.RightsHostURL

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <License>dG2IhDioBnMdX1faxsuX0MCCmaQ=;2006-01-02T00:00:00Z;2006-12-31T00:00:00Z</License>
     <RightsHostURL>localhost:8080</RightsHostURL>
    </ROOT>

    \endverbatim

    \param    comm            input, communication handler.
    \param    contentID       string uniquely identifying the content.
    \param    xmlDoc          XML document.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMEncAgent::AddLicense(IOMADRMEncCommHandler* comm, std::string& contentID,
    IXMLElement* xmlDoc) {
  std::string serverURL;
  try {
    serverURL = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    agentLogger.UpdateLog("OMADRMEncAgent::AddLicense: missing server URL in XML file...");
    return false;
  }

  NZSPtr<URIValue> url(new URIValue(serverURL));
  NZSPtr<URIValue> content(new URIValue(contentID));

  std::vector<IXMLElement*> license = xmlDoc->GetChildElementsByName("License");
  for (unsigned int i = 0; i < license.size(); i++) {
    agentLogger.UpdateLog("OMADRMEncAgent::AddLicense:...");

    std::string licenseData;
    try {
      licenseData = license[i]->GetStrValue();
    }
    catch (XMLException) {
      continue;
    }
    SPtr<ODDStart> oddStart;
    SPtr<ODDEnd> oddEnd;
    std::string deviceID;
    if (ParseLicense(licenseData, deviceID, oddStart, oddEnd) == false) {
      agentLogger.UpdateLog("OMADRMEncAgent::AddLicense: unrecognized license " + licenseData + "...");
      continue;
    }

    NZSPtr<ODDPlayPermission> permission = new ODDPlayPermission(
      new PlayOEXConstraint(0, 0, new StartEndODDDatetimeConstraint(oddStart, oddEnd),
      0, 0, 0, std::vector<NZSPtr<OMADDSystemConstraint> >()));
//    NZSPtr<ODDDisplayPermission> permission = new ODDDisplayPermission(
//      new DisplayOEXConstraint(0, 0, new StartEndODDDatetimeConstraint(oddStart, oddEnd),
//      0, 0, 0, std::vector<NZSPtr<OMADDSystemConstraint> >()));
//    NZSPtr<ODDExecutePermission> permission = new ODDExecutePermission(
//      new ExecuteOEXConstraint(0, 0, new StartEndODDDatetimeConstraint(oddStart, oddEnd),
//      0, 0, 0));
//    NZSPtr<ODDPrintPermission> permission = new ODDPrintPermission(
//      new PrintOEXConstraint(0, new StartEndODDDatetimeConstraint(oddStart, oddEnd),
//      0, 0, 0));
//    NZSPtr<OMADDExportPermission> permission = new MoveOMADDExportPermission(
//      new MoveExportOEXConstraint(new StartEndODDDatetimeConstraint(oddStart, oddEnd),
//      std::vector<NZSPtr<OMADDSystemConstraint> >(1,
//      new OMADDSystemConstraint(new SystemOEXContext(
//      0, std::vector<NZSPtr<SystemODDUID> >())))));

    NZSPtr<OEXRights> rights = new OEXRights(new RightsOEXContext(0, 0),
      new OEXAgreement(std::vector<NZSPtr<AgreementOEXAsset> >(1,
      new AgreementOEXAsset(0, 0, 0, 0, 0)),
      std::vector<NZSPtr<OEXPermission> >(1, new OEXPermission(0,
      std::vector<NZSPtr<PermissionOEXAsset> >(), permission, 0, 0, 0, 0))));
//      std::vector<NZSPtr<PermissionOEXAsset> >(), 0, permission, 0, 0, 0))));
//      std::vector<NZSPtr<PermissionOEXAsset> >(), 0, 0, permission, 0, 0))));
//      std::vector<NZSPtr<PermissionOEXAsset> >(), 0, 0, 0, permission, 0))));
//      std::vector<NZSPtr<PermissionOEXAsset> >(), 0, 0, 0, 0, permission))));

    NZSPtr<ROAPKeyIdentifier> devKeyID = new X509SPKIHash(deviceID);
    NZSPtr<ROAPIdentifier> devID = new ROAPIdentifier(devKeyID);

    NZSPtr<ROAPNonce> nonce = noncer->CreateNonce();

    NZSPtr<AddDeviceRightsRequest> request(new AddDeviceRightsRequest(rights, devID,
      content, nonce));

    //  Set waiting event for server response.
    IEvent* waiter = ThreadSyncFactory::GetEvent(agentLogger);
    IEvent* exiter = ThreadSyncFactory::GetEvent(agentLogger);
    if ((waiter == 0) || (exiter == 0)) {
      if (waiter != 0) delete waiter;
      if (exiter != 0) delete exiter;
      agentLogger.UpdateLog("OMADRMEncAgent::AddLicense: event creation error...");
      return false;
    }
    if (mutex->Lock() == false) {
      if (waiter != 0) delete waiter;
      if (exiter != 0) delete exiter;
      agentLogger.UpdateLog("OMADRMEncAgent::AddLicense: cannot lock mutex...");
      return false;
    }
    nonceToWait[nonce] = waiter;
    nonceToExit[nonce] = exiter;
    if (mutex->Release() == false) {
      if (waiter != 0) delete waiter;
      if (exiter != 0) delete exiter;
      agentLogger.UpdateLog("OMADRMEncAgent::AddLicense: cannot release mutex...");
      return false;
    }

    //  Send the request.
    comm->SendAddDeviceRightsRequest(request, url);

    //  Get into waiting loop for the server response.
    bool ret = waiter->Wait(EVENT_WAIT_TIME);
    if (ret == false) {
      agentLogger.UpdateLog("OMADRMEncAgent::AddLicense: event wait timeout...");
    }
    if (mutex->Lock() == false) {
      agentLogger.UpdateLog("OMADRMEncAgent::AddLicense: cannot lock mutex...");
      return false;
    }
    delete nonceToWait[nonce];
    nonceToWait.erase(nonce);
    if (exitFlag == false) {
      delete nonceToExit[nonce];
    }
    nonceToExit.erase(nonce);
    if (mutex->Release() == false) {
      agentLogger.UpdateLog("OMADRMEncAgent::AddLicense: cannot release mutex...");
      return false;
    }

    if (ret && (!exitFlag)) {
      agentLogger.UpdateLog("OMADRMEncAgent::AddLicense: ok...");
    } else {
      agentLogger.UpdateLog("OMADRMEncAgent::AddLicense: failed...");
      return false;
    }
  }

  return true;
}

/*! \brief  Handle add content encryption key response.

    \param  response          input, add content encryption key response.
*/
void OMADRMEncAgent::HandleAddContentKeyResponse(const NZSPtr<AddContentKeyResponse>&
    response) {
  if (mutex->Lock() == false) {
    agentLogger.UpdateLog("OMADRMEncAgent::HandleAddContentKeyResponse: cannot lock sync mutex...");
    return;
  }
  if (response->GetSuccess() == true) {
    agentLogger.UpdateLog("OMADRMEncAgent::HandleAddContentKeyResponse: success response...");
    if (nonceToWait.find(response->GetNonce()) != nonceToWait.end()) {
      nonceToWait[response->GetNonce()]->Set();
    }
  } else {
    agentLogger.UpdateLog("OMADRMEncAgent::HandleAddContentKeyResponse: unsuccess response...");
  }
  if (mutex->Release() == false) {
    agentLogger.UpdateLog("OMADRMEncAgent::HandleAddContentKeyResponse: cannot release sync mutex...");
  }
}

/*! \brief  Handle add rights for device for content response.

    \param  response          input, add rights for device for content response.
*/
void OMADRMEncAgent::HandleAddDeviceRightsResponse(const NZSPtr<AddDeviceRightsResponse>&
    response) {
  if (mutex->Lock() == false) {
    agentLogger.UpdateLog("OMADRMEncAgent::HandleAddDeviceRightsResponse: cannot lock sync mutex...");
    return;
  }
  if (response->GetSuccess() == true) {
    agentLogger.UpdateLog("OMADRMEncAgent::HandleAddDeviceRightsResponse: success response...");
    if (nonceToWait.find(response->GetNonce()) != nonceToWait.end()) {
      nonceToWait[response->GetNonce()]->Set();
    }
  } else {
    agentLogger.UpdateLog("OMADRMEncAgent::HandleAddDeviceRightsResponse: unsuccess response...");
  }
  if (mutex->Release() == false) {
    agentLogger.UpdateLog("OMADRMEncAgent::HandleAddDeviceRightsResponse: cannot release sync mutex...");
  }
}

/*! \brief  Create content encryption key and store it with respect to content ID.

    Mandatory tags in the XML file are:
     - ROOT.RightsHostURL

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RightsHostURL>localhost:8080</RightsHostURL>
    </ROOT>

    \endverbatim

    \param    comm            input, communication handler.
    \param    contentID       input-output, (possibly updated) content identifier.
    \param    xmlDoc          input, XML document.
    \param    key             output, newly created key.
    \param    keySize         input, requested key size.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMEncAgent::CreateAndStoreKey(IOMADRMEncCommHandler* comm, std::string&
    contentID, IXMLElement* xmlDoc, ByteT** key, UInt32T keySize) {

  agentLogger.UpdateLog("OMADRMEncAgent::CreateAndStoreKey:...");

  //  Generate a new random key.
  if (CipherFactory::RndGenerate(key, keySize) == false) {
    agentLogger.UpdateLog("OMADRMEncAgent::CreateAndStoreKey: random generate error...");
    return false; 
  }

  //  Inform the server about new content encryption key.
  //  Create request.
  NZSPtr<URIValue> content(new URIValue(contentID));
  Base64StringT enckey;
  if (EncodeKey(*key, keySize, enckey) == false) {
    free(*key);
    return false;
  }
  NZSPtr<ROAPNonce> nonce = noncer->CreateNonce();
  NZSPtr<AddContentKeyRequest> request(new AddContentKeyRequest(content, enckey, nonce));
  //  Server URL should be taken from XML document.
  std::string serverURL;
  try {
    serverURL = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    agentLogger.UpdateLog("OMADRMEncAgent::CreateAndStoreKey: missing rights host URL in XML file...");
    free(*key);
    return false;
  }
  NZSPtr<URIValue> url(new URIValue(serverURL));

  //  Set waiting event for server response.
  IEvent* waiter = ThreadSyncFactory::GetEvent(agentLogger);
  IEvent* exiter = ThreadSyncFactory::GetEvent(agentLogger);
  if ((waiter == 0) || (exiter == 0)) {
    free(*key);
    if (waiter != 0) delete waiter;
    if (exiter != 0) delete exiter;
    agentLogger.UpdateLog("OMADRMEncAgent::CreateAndStoreKey: event creation error...");
    return false;
  }
  mutex->Lock();
  nonceToWait[nonce] = waiter;
  nonceToExit[nonce] = exiter;
  mutex->Release();

  //  Send the request.
  comm->SendAddContentKeyRequest(request, url);

  //  Get into waiting loop for the server response.
  bool ret = waiter->Wait(EVENT_WAIT_TIME);
  if (ret == false) agentLogger.UpdateLog("OMADRMEncAgent::CreateAndStoreKey: event wait timeout...");

  mutex->Lock();
  delete nonceToWait[nonce];
  nonceToWait.erase(nonce);
  if (exitFlag == false) {
    delete nonceToExit[nonce];
  }
  nonceToExit.erase(nonce);
  ret = (ret && (!exitFlag));
  mutex->Release();
  if (!ret) {
    free(*key);
  } else {
    agentLogger.UpdateLog("OMADRMEncAgent::CreateAndStoreKey: ok...");
  }
  return ret;
}

/*! \brief  Encode encryption key as a base64 string.

    \param  key         input, encryption key.
    \param  len         input, encryption key length.
    \param  enc         output, base64 encoded encryption key.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMEncAgent::EncodeKey(const ByteT* key, const UInt32T len, Base64StringT& enc) {
  return Base64Factory::Encode(ByteSeq(key, (unsigned int)len), enc);
}

/*! \brief  Parse license.

    \param  license         input, license string.
    \param  deviceID        output, device identifier.
    \param  oddStart        output, start date.
    \param  oddEnd          output, end date.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMEncAgent::ParseLicense(const std::string& license, std::string& deviceID,
    SPtr<ODDStart>& oddStart, SPtr<ODDEnd>& oddEnd) {
  char *semi1, *semi2;

  semi1 = strchr(license.data(), ';');
  if (semi1 == NULL) {
    return false;
  }
  deviceID = std::string(license.begin(), std::string::const_iterator(semi1));

  semi2 = strchr(++semi1, ';');
  if (semi2 == NULL) {
    return false;
  }
  std::string start = std::string(std::string::iterator(semi1), std::string::iterator(semi2));
  std::string end = std::string(std::string::const_iterator(++semi2), license.end());

  try {
    oddStart = new ODDStart(UTCTime(start));
  }
  catch (UTCTimeException) {
    agentLogger.UpdateLog("OMADRMEncAgent::ParseLicense: invalid start date " + start + "...");
    return false;
  }
  try {
    oddEnd = new ODDEnd(UTCTime(end));
  }
  catch (UTCTimeException) {
    agentLogger.UpdateLog("OMADRMEncAgent::ParseLicense: invalid end date " + end + "...");
    return false;
  }

  return true;
}

} // namespace DRMPlugin
