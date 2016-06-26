/**	\file OpenIPMPMPEG2IPMPXDRMEncryptor.cpp

	OpenIPMP MPEG2 DRM encryptor with IPMPX signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OpenIPMPMPEG2IPMPXDRMEncryptor.h"
#include "IPMPControlInfo.h"
#include "IPMPData.h"

#include "OpenIPMP.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  OpenIPMP MPEG2 DRM encryptor with AES128CTR encryption.

    Encryptor that will protect MPEG2 data using openIPMP specifications.
*/
/*! \brief Constructor.

    See the specific DRM manager documentation for the correct format
    of the XML document.

    For creating encryptor, mandatory tags in the XML file are:
     - ROOT.RightsHostURL

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RightsHostURL>localhost:8080</RightsHostURL>
    </ROOT>

    \endverbatim

    \param    drm             DRM manager.
    \param    conID           content identifier.
    \param    xmlDoc          XML document containing necessary information for
                              creating encryptor.
    \param    logger          message logger.

    \returns  If fails, throws MPEG2DRMPluginException.
*/
AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor::AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor(
    IOpenIPMPDRMEncManager* drm, std::string& conID, IXMLElement* xmlDoc,
    DRMLogger& logger): encryptor(0), contentID(), rightsHost(), encLogger(logger) {
  if (xmlDoc == 0) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor::ctor: zero XML file.");
    throw MPEG2DRMPluginException();
  }
  encryptor = drm->CreateAES128CTREnc(conID, xmlDoc);
  if (encryptor == 0) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor::ctor: zero encryptor.");
    throw MPEG2DRMPluginException();
  }
  contentID = conID;
  try {
    rightsHost = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    delete encryptor;
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor::ctor: missing data in XML file.");
    throw MPEG2DRMPluginException();
  }
}

AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor::~AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor() {
  if (encryptor != 0) delete encryptor; encryptor = 0;
}

/*! \brief  Encrypt data.

    User of IMPEG2IPMPXDRMEncryptor must decide which data will be encrypted
    (all elementary streams, only some, etc.), and once the IMPEG2IPMPXDRMEncryptor
    is created, call this function subsequently to encrypt that data.

    \param  plainData       input, plaintext data to be encrypted.
    \param  encryptedData   output, encrypted data.

    \returns  Boolean indicating success or failure.
*/
bool AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor::EncryptData(const ByteSeq& plainData,
    ByteSeq& encryptedData) {
  //  Get next counter.
  ByteT* ctr;
  UInt32T ctrLen;
  if (encryptor->NextCtr(&ctr, &ctrLen) == false) {
    return false;
  }
  //  Encrypt sample.
  ByteT* enc;
  UInt32T encLen;
  //  Encrypt sample.
  if (encryptor->Encrypt((ByteT*)(plainData.GetFirst()), plainData.GetLength(), &enc,
      &encLen) == false) {
    if (ctr != NULL) {
      free(ctr);
    }
    return false;
  }

  encryptedData = ByteSeq((ByteT)ctrLen);
  encryptedData += ByteSeq(ctr, ctrLen);
  encryptedData += ByteSeq(enc, encLen);

  if (ctr != NULL) {
    free(ctr);
  }
  if (enc != NULL) {
    free(enc);
  }

  return true;
}

/*! \brief  Add DRM information to IPMP descriptor.

    User of IMPEG2IPMPXDRMEncryptor must take care of the correct placement
    of the IPMP descriptor. If all elementary streams are protected then
    the IPMP descriptor must be put in the in the main program map loop.
    If only some elementary streams are protected then the IPMP descriptor
    must be put in the program map in the elementary stream loop for the
    protected streams.

    \param  descriptor      input-output, IPMP descriptor to be updated.

    \returns  Boolean indicating success or failure.
*/
bool AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor::AddDRMInfo(IIPMPDescriptor* descriptor) {
  if (descriptor->SetIPMPDescriptorID(0x11223344) == false) {
    return false;
  }
  if (descriptor->SetIPMPToolID(std::string("openIPMP tool ID")) == false) {
    return false;
  }
  if (descriptor->SetControlPoint(1) == false) {
    return false;
  }
  if (descriptor->SetSequenceCode(1) == false) {
    return false;
  }
  std::string toolID = OPENIPMP_TOOLID;
  ByteSeq rights((ByteT)AES128CTR);
  rights += ByteSeq((ByteT*)(toolID.data()), toolID.size() + 1);
  rights += ByteSeq((ByteT*)(contentID.data()), contentID.size() + 1);
  rights += ByteSeq((ByteT*)(rightsHost.data()), rightsHost.size() + 1);
  RightsIPMPData rightsData(0, 0, rights);
  ByteSeq encoded;
  if (rightsData.MPEG2Encode(encoded) == false) {
    return false;
  }
  if (descriptor->SetIPMPData(encoded) == false) {
    return false;
  }
  return true;
}

/*! \brief  Create and encode control info class.

    Control info class is this encryptor's (tool's) description, used for
    later correct initialization.

    \param  cInfo           output, encoded control info class.

    \returns  Boolean indicating success or failure.
*/
bool AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor::CreateControlInfo(ByteSeq& cInfo) {
  //  We create just a tool info.
  IPMPToolInfo info(Bit128T(std::string("openIPMP tool ID")), std::vector<Bit128T>(),
    0, std::vector<ByteSeq>());
  return info.MPEG2Encode(cInfo);
}

/*! \brief  OpenIPMP MPEG2 DRM encryptor with blowfish encryption.

    Encryptor that will protect MPEG2 data using openIPMP specifications.
*/
/*! \brief Constructor.

    See the specific DRM manager documentation for the correct format
    of the XML document.

    For creating encryptor, mandatory tags in the XML file are:
     - ROOT.RightsHostURL

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RightsHostURL>localhost:8080</RightsHostURL>
    </ROOT>

    \endverbatim

    \param    drm             DRM manager.
    \param    conID           content identifier.
    \param    xmlDoc          XML document containing necessary information for
                              creating encryptor.
    \param    logger          message logger.

    \returns  If fails, throws MPEG2DRMPluginException.
*/
BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor::BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor(
    IOpenIPMPDRMEncManager* drm, std::string& conID, IXMLElement* xmlDoc,
    DRMLogger& logger): encryptor(0), contentID(), rightsHost(), encLogger(logger) {
  if (xmlDoc == 0) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor::ctor: zero XML file.");
    throw MPEG2DRMPluginException();
  }
  encryptor = drm->CreateBlowfishEnc(conID, xmlDoc);
  if (encryptor == 0) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor::ctor: zero encryptor.");
    throw MPEG2DRMPluginException();
  }
  contentID = conID;
  try {
    rightsHost = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    delete encryptor;
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor::ctor: missing data in XML file.");
    throw MPEG2DRMPluginException();
  }
}

BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor::~BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor() {
  if (encryptor != 0) delete encryptor; encryptor = 0;
}

/*! \brief  Encrypt data.

    User of IMPEG2IPMPXDRMEncryptor must decide which data will be encrypted
    (all elementary streams, only some, etc.), and once the IMPEG2IPMPXDRMEncryptor
    is created, call this function subsequently to encrypt that data.

    \param  plainData       input, plaintext data to be encrypted.
    \param  encryptedData   output, encrypted data.

    \returns  Boolean indicating success or failure.
*/
bool BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor::EncryptData(const ByteSeq& plainData,
    ByteSeq& encryptedData) {
  //  Encrypt sample.
  ByteT* enc;
  UInt32T encLen;
  //  Encrypt sample.
  if (encryptor->Encrypt((ByteT*)(plainData.GetFirst()), plainData.GetLength(), &enc,
      &encLen) == false) {
    return false;
  }

  encryptedData = ByteSeq(enc, encLen);

  if (enc != NULL) {
    free(enc);
  }

  return true;
}

/*! \brief  Add DRM information to IPMP descriptor.

    User of IMPEG2IPMPXDRMEncryptor must take care of the correct placement
    of the IPMP descriptor. If all elementary streams are protected then
    the IPMP descriptor must be put in the in the main program map loop.
    If only some elementary streams are protected then the IPMP descriptor
    must be put in the program map in the elementary stream loop for the
    protected streams.

    \param  descriptor      input-output, IPMP descriptor to be updated.

    \returns  Boolean indicating success or failure.
*/
bool BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor::AddDRMInfo(IIPMPDescriptor* descriptor) {
  if (descriptor->SetIPMPDescriptorID(0x11223344) == false) {
    return false;
  }
  if (descriptor->SetIPMPToolID(std::string("openIPMP tool ID")) == false) {
    return false;
  }
  if (descriptor->SetControlPoint(1) == false) {
    return false;
  }
  if (descriptor->SetSequenceCode(1) == false) {
    return false;
  }
  std::string toolID = OPENIPMP_TOOLID;
  ByteSeq rights((ByteT)BLOWFISH);
  rights += ByteSeq((ByteT*)(toolID.data()), toolID.size() + 1);
  rights += ByteSeq((ByteT*)(contentID.data()), contentID.size() + 1);
  rights += ByteSeq((ByteT*)(rightsHost.data()), rightsHost.size() + 1);
  RightsIPMPData rightsData(0, 0, rights);
  ByteSeq encoded;
  if (rightsData.MPEG2Encode(encoded) == false) {
    return false;
  }
  if (descriptor->SetIPMPData(encoded) == false) {
    return false;
  }
  return true;
}

/*! \brief  Create and encode control info class.

    Control info class is this encryptor's (tool's) description, used for
    later correct initialization.

    \param  cInfo           output, encoded control info class.

    \returns  Boolean indicating success or failure.
*/
bool BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor::CreateControlInfo(ByteSeq& cInfo) {
  //  We create just a tool info.
  IPMPToolInfo info(Bit128T(std::string("openIPMP tool ID")), std::vector<Bit128T>(),
    0, std::vector<ByteSeq>());
  return info.MPEG2Encode(cInfo);
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
