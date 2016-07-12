/**	\file OpenIPMPDOIContentInfoManager.cpp

	DOI content information manager using openIPMP infrastructure.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OpenIPMPDOIContentInfoManager.h"
#include "busobj/factories/DOI_Factory.h"
#include "OpenIPMPMessengerFactory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Constructor.

    Use information provided in the XML document.

    \param    xmlDoc          input, XML document.
    \param    logger          input-output, message logger.

    If constructor fails, it throws ContentInfoManagerException and logger
    contains error description.
*/
OpenIPMPDOIContentInfoManager::OpenIPMPDOIContentInfoManager(IXMLElement* xmlDoc,
    DRMLogger& logger): messenger(OpenIPMPMessengerFactory::GetMessenger(xmlDoc, logger)),
    managerLogger(logger) {
  if (messenger == 0) {
    throw ContentInfoManagerException();
  }
}

OpenIPMPDOIContentInfoManager::~OpenIPMPDOIContentInfoManager() {
  if (messenger != 0) delete messenger; messenger = 0;
}

/*! \brief  Create DRM content information.

    Use information provided in the given XML document.

    Mandatory tags in the XML file are:
     - ROOT.ContentTitle
     - ROOT.UserName
     - ROOT.UserPass
     - ROOT.RightsHostURL
     - ROOT.doi:KernelMetadata.DOI
     - ROOT.doi:KernelMetadata.Titles.Title.TitleValue
     - ROOT.doi:KernelMetadata.Titles.Title.Language
     - ROOT.doi:KernelMetadata.StructuralType
     - ROOT.doi:KernelMetadata.Modes.Mode
     - ROOT.doi:KernelMetadata.PrimaryAgents.Agent.Name.NameType
     - ROOT.doi:KernelMetadata.PrimaryAgents.Agent.Name.NameValue
     - ROOT.doi:KernelMetadata.PrimaryAgents.Agent.Roles.Role
     - ROOT.doi:KernelMetadata.Assertor.Registrant.Name.NameType
     - ROOT.doi:KernelMetadata.Assertor.Registrant.Name.NameValue
     - ROOT.doi:KernelMetadata.Assertor.Registrant.Identifier.IdentifierType
     - ROOT.doi:KernelMetadata.Assertor.Registrant.Identifier.IdentifierValue
     - ROOT.doi:KernelMetadata.Assertor.Authority.Name.NameType
     - ROOT.doi:KernelMetadata.Assertor.Authority.Name.NameValue

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <ContentTitle>test30.mp4.track1</ContentTitle>
     <UserName>danijelk</UserName>
     <UserPass>ipmp</UserPass>
     <RightsHostURL>localhost:8080</RightsHostURL>
     <doi:KernelMetadata xmlns:doi="http://www.doi.org/">
      <DOI>TBD</DOI>
      <Identifiers>
       <Identifier>
        <IdentifierType>ISWC</IdentifierType>
        <IdentifierValue>T-034.524.680</IdentifierValue>
       </Identifier>
      </Identifiers>
      <Titles>
       <Title>
        <TitleValue>title</TitleValue>
        <Language>en</Language>
       </Title>
      </Titles>
      <StructuralType>visual</StructuralType>
      <Modes>
       <Mode>visual</Mode>
      </Modes>
      <PrimaryAgents>
       <Agent sequence="1">
        <Name>
         <NameType>Person</NameType>
         <NameValue>Matt Witte</NameValue>
        </Name>
        <Roles>
         <Role>Artist</Role>
        </Roles>
       </Agent>
       <Agent sequence="2">
        <Name>
         <NameType>Person</NameType>
         <NameValue>Freddy</NameValue>
        </Name>
        <Roles>
         <Role>Directory</Role>
        </Roles>
       </Agent>
      </PrimaryAgents>
      <Assertor>
       <Registrant>
        <Name>
         <NameType>Person</NameType>
         <NameValue>Persons Name Here</NameValue>
        </Name>
        <Identifier>
         <IdentifierType>PublisherCode</IdentifierType>
         <IdentifierValue>9901</IdentifierValue>
        </Identifier>
       </Registrant>
       <Authority>
        <Name>
         <NameType>Organization</NameType>
         <NameValue>Objectlab</NameValue>
        </Name>
       </Authority>
      </Assertor>
     </doi:KernelMetadata>
    </ROOT>

    \endverbatim

    \param    xmlDoc          XML document containing necessary information for
                              creating content info.
    \param    info            output, newly created content info.

    \return Boolean indicating success or failure.
*/
bool OpenIPMPDOIContentInfoManager::GetContentInfo(IXMLElement* xmlDoc, std::string& info) {
  managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo:...");

  if (xmlDoc == 0) {
    managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo: zero XML file...");
    return false;
  }
  std::string title;
  try {
    title = xmlDoc->GetChildStrValue("ContentTitle");
  }
  catch (XMLException) {
    managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo: Missing content title in the XML file...");
    return false;
  }

  IXMLElement* elem = xmlDoc->GetChildElement("doi:KernelMetadata.Titles.Title.TitleValue");
  if (elem == 0) {
    managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo: Missing doi:KernelMetadata.Titles.Title.TitleValue in the XML file...");
    return false;
  }
  if (elem->SetStrValue(title) == false) {
    managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo: Missing data in the XML file...");
    return false;
  }
  IXMLElement* doi = xmlDoc->GetChildElement("doi:KernelMetadata");
  if (doi == 0) {
    managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo: Missing doi:KernelMetadata in the XML file...");
    return false;
  }
  std::string doiStr = doi->Encode();

  std::string name, pass, infoHost;
  try {
    name = xmlDoc->GetChildStrValue("UserName");
  }
  catch (XMLException) {
    managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo: Missing user name in the XML file...");
    return false;
  }
  try {
    pass = xmlDoc->GetChildStrValue("UserPass");
  }
  catch (XMLException) {
    managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo: Missing user password in the XML file...");
    return false;
  }
  try {
    infoHost = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo: Missing openIPMP host URL in the XML file...");
    return false;
  }
  std::string hostIP;
  int hostPort;

  if (ParseHostIPPort(infoHost, hostIP, hostPort) == false) {
    managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo: could not parse host IP and port...");
    return false;
  }

  bool ret = messenger->AssignContentID(name, pass, hostIP, hostPort, doiStr, info);

  if (ret == true) {
    managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo: ok...");
  } else {
    managerLogger.UpdateLog("OpenIPMPDOIContentInfoManager::GetContentInfo: failed...");
  }

  return ret;
}

/*! \brief  Parse host IP and port from hostURL string.

    \param  hostURL     input, host URL string.
    \param  hostIP      output, host's IP address.
    \param  hostPort    output, host's port.

    \returns  Boolean indicating success or failure.
*/
bool OpenIPMPDOIContentInfoManager::ParseHostIPPort(const std::string& hostURL,
    std::string& hostIP, int& hostPort) {
  char* colon = const_cast<char*>(strchr(hostURL.data(), ':'));
  if (colon == NULL) {
    return false;
  }
  hostIP = std::string(hostURL.begin(), std::string::const_iterator(colon));
  hostPort = atoi(++colon);
  return true;
}

} // namespace DRMPlugin
