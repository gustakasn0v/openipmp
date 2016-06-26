/**	\file OpenIPMPMPEG4SinfDRMEncryptor.cpp

	OpenIPMP MPEG4 DRM encryptor plugin with Sinf signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "MPEG4DRMPluginException.h"
#include "OpenIPMPMPEG4SinfDRMEncryptor.h"

#include "OpenIPMP.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG4SinfDRMPlugin namespace. All MPEG4 Sinf DRM plugin code resides in it.
namespace MPEG4SinfDRMPlugin {

/*! \brief  Encrypts MP4 data using AES128CTR encryptor according to openIPMP
            specifications with Sinf signalling.

    Encrypts samples and adds information for decryption to MP4 stream.
*/
/*! \brief  Constructor.

    Mandatory tags in the XML file are:
     - ROOT.RightsHostURL

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RightsHostURL>localhost:8080</RightsHostURL>
    </ROOT>

    \endverbatim

    \param      drm             input, DRM manager.
    \param      conID           input, content identifier.
    \param      xmlDoc          input, XML document.
    \param      logger          input-output, message logger.

    If constructor fails, it throws MPEG4DRMPluginException.
*/
AES128CTROpenIPMPMPEG4SinfDRMEncryptor::AES128CTROpenIPMPMPEG4SinfDRMEncryptor(
    IOpenIPMPDRMEncManager* drm, std::string& conID, IXMLElement* xmlDoc,
    DRMLogger& logger): encryptor(0), contentID(), rightsHost(), encLogger(logger) {
  if (xmlDoc == 0) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::ctor: zero XML file.");
    throw MPEG4DRMPluginException();
  }
  encryptor = drm->CreateAES128CTREnc(conID, xmlDoc);
  if (encryptor == 0) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::ctor: zero encryptor.");
    throw MPEG4DRMPluginException();
  }
  contentID = conID;
  try {
    rightsHost = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    delete encryptor;
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::ctor: missing data in XML file.");
    throw MPEG4DRMPluginException();
  }
}

AES128CTROpenIPMPMPEG4SinfDRMEncryptor::~AES128CTROpenIPMPMPEG4SinfDRMEncryptor() {
  if (encryptor != 0) delete encryptor;
}

/*! \brief  Encrypt sample sampleBuffer.

    Returns encrypted sample in encSampleData.

    \param    sampleBuffer      input, sample to be encrypted.
    \param    sampleSize        input, size of input sample.
    \param    encSampleData     output, encrypted sample.
    \param    encSampleLen      output, size of encrypted sample.

    \return Boolean indicating success or failure.
*/
bool AES128CTROpenIPMPMPEG4SinfDRMEncryptor::EncryptSample(ByteT* sampleBuffer,
    UInt32T sampleSize, ByteT** encSampleData, UInt32T* encSampleLen) {
  //  Get next counter.
  ByteT* ctr;
  UInt32T ctrLen;
  if (encryptor->NextCtr(&ctr, &ctrLen) == false) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::EncryptSample: cannot get next counter...");
    return false;
  }
  //  Encrypt sample.
  ByteT* enc;
  UInt32T encLen;
  //  Encrypt sample.
  if (encryptor->Encrypt(sampleBuffer, sampleSize, &enc, &encLen) == false) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::EncryptSample: encryption error...");
    if (ctr != NULL) {
      free(ctr);
    }
    return false;
  }

  /*  Allocate memory (1 for counter length + size of the counter + size of the
      encrypted block).
  */
  *encSampleData = (ByteT*)malloc(1 + ctrLen + encLen);
  if (*encSampleData == NULL) {
    if (ctr != NULL) {
      free(ctr);
    }
    if (enc != NULL) {
      free(enc);
    }
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::EncryptSample: memory allocation error.");
    return false;
  }
  *encSampleLen = 1 + ctrLen + encLen;
  ByteT* tmp = *encSampleData;
  //  Add header.
  //  Counter length.
  *tmp++ = (ByteT)ctrLen;
  memcpy(tmp, ctr, ctrLen);
  tmp += ctrLen;
  memcpy(tmp, enc, encLen);
  if (ctr != NULL) {
    free(ctr);
  }
  if (enc != NULL) {
    free(enc);
  }

  return true;
}

/*! \brief  Add drm information into sinf atom.

    Caller must take care that given sinf atom really coresponds to sample
    description atom which refers to encrypted samples.

    \param    originalFormat  input, 4CC code of the original data format.
    \param    sinf            input-output, sinf atom where to add drm information.

    \return Boolean indicating success or failure.
*/
bool AES128CTROpenIPMPMPEG4SinfDRMEncryptor::Finish(UInt32T originalFormat,
    IMP4SinfAtom* sinf) {
	IMP4FrmaAtom* frma = sinf->GetOriginalFormat();
  if (frma == 0) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::Finish: no original format atom.");
    return false;
  }
  if (frma->SetDataFormat(originalFormat) == false) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::Finish: frma->SetDataFormat() error.");
    return false;
  }

  IMP4ImifAtom* imif = sinf->CreateIPMPInfo();
  if (imif == 0) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::Finish: could not create IPMP info atom.");
    return false;
  }
  IMP4IPMPDescriptor* ipmpDesc = imif->CreateIPMPDescriptor();
  if (ipmpDesc == 0) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::Finish: could not create IPMP descriptor.");
    return false;
  }
  if (ipmpDesc->SetIPMPDescriptorIdentifier(255) == false) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::Finish: ipmpDesc->SetIPMPDescriptorIdentifier() error.");
    return false;
  }
  if (ipmpDesc->SetIPMPDescriptorType(65535) == false) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::Finish: ipmpDesc->SetIPMPDescriptorType() error.");
    return false;
  }

  std::string toolID = OPENIPMP_TOOLID;
  UInt32T ipmpDataSize = 1 + toolID.size() + 1 + contentID.size() + 1 + rightsHost.size() + 1;
  ByteT* ipmpData = (ByteT*)malloc(ipmpDataSize);
  if (ipmpData == 0) {
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::Finish: memory allocation error.");
    return false;
  }
  //  Save the encryption method.
  *ipmpData = (ByteT)(AES128CTR);
  memcpy(ipmpData + 1, toolID.data(), toolID.size() + 1);
  memcpy(ipmpData + 1 + toolID.size() + 1, contentID.data(), contentID.size() + 1);
  memcpy(ipmpData + 1 + toolID.size() + 1 + contentID.size() + 1, rightsHost.data(),
    rightsHost.size() + 1);

  if (ipmpDesc->SetIPMPData(ipmpData, ipmpDataSize) == false) {
    free(ipmpData);
    encLogger.UpdateLog("AES128CTROpenIPMPMPEG4SinfDRMEncryptor::Finish: ipmpDesc->SetIPMPData() error.");
    return false;
  }
  free(ipmpData);

  return true;
}

/*! \brief  Encrypts MP4 data using blowfish encryptor according to openIPMP
            specifications with Sinf signalling.

    Encrypts samples and adds information for decryption to MP4 stream.
*/
/*! \brief  Constructor.

    Mandatory tags in the XML file are:
     - ROOT.RightsHostURL

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RightsHostURL>localhost:8080</RightsHostURL>
    </ROOT>

    \endverbatim

    \param      drm             input, DRM manager.
    \param      conID           input, content identifier.
    \param      xmlDoc          input, XML document.
    \param      logger          input-output, message logger.

    If constructor fails, it throws MPEG4DRMPluginException.
*/
BlowfishOpenIPMPMPEG4SinfDRMEncryptor::BlowfishOpenIPMPMPEG4SinfDRMEncryptor(
    IOpenIPMPDRMEncManager* drm, std::string& conID, IXMLElement* xmlDoc,
    DRMLogger& logger): encryptor(), contentID(), rightsHost(), encLogger(logger) {
  if (xmlDoc == 0) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::ctor: zero XML file.");
    throw MPEG4DRMPluginException();
  }
  encryptor = drm->CreateBlowfishEnc(conID, xmlDoc);
  if (encryptor == 0) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::ctor: zero encryptor.");
    throw MPEG4DRMPluginException();
  }
  contentID = conID;
  try {
    rightsHost = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    delete encryptor;
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::ctor: missing data in XML file.");
    throw MPEG4DRMPluginException();
  }
}

BlowfishOpenIPMPMPEG4SinfDRMEncryptor::~BlowfishOpenIPMPMPEG4SinfDRMEncryptor() {
  if (encryptor != 0) delete encryptor;
}

/*! \brief  Encrypt sample sampleBuffer.

    Returns encrypted sample in encSampleData.

    \param    sampleBuffer      input, sample to be encrypted.
    \param    sampleSize        input, size of input sample.
    \param    encSampleData     output, encrypted sample.
    \param    encSampleLen      output, size of encrypted sample.

    \return Boolean indicating success or failure.
*/
bool BlowfishOpenIPMPMPEG4SinfDRMEncryptor::EncryptSample(ByteT* sampleBuffer,
    UInt32T sampleSize, ByteT** encSampleData, UInt32T* encSampleLen) {
  bool ret = encryptor->Encrypt(sampleBuffer, sampleSize, encSampleData, encSampleLen);
  if (ret == false) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::EncryptSample: encryption error...");
  }
  return ret;
}

/*! \brief  Add drm information into sinf atom.

    Caller must take care that given sinf atom really coresponds to sample
    description atom which refers to encrypted samples.

    \param    originalFormat  input, 4CC code of the original data format.
    \param    sinf            input-output, sinf atom where to add drm information.

    \return Boolean indicating success or failure.
*/
bool BlowfishOpenIPMPMPEG4SinfDRMEncryptor::Finish(UInt32T originalFormat,
    IMP4SinfAtom* sinf) {
	IMP4FrmaAtom* frma = sinf->GetOriginalFormat();
  if (frma == 0) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::Finish: no original format atom.");
    return false;
  }
  if (frma->SetDataFormat(originalFormat) == false) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::Finish: frma->SetDataFormat() error.");
    return false;
  }

  IMP4ImifAtom* imif = sinf->CreateIPMPInfo();
  if (imif == 0) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::Finish: could not create IPMP info atom.");
    return false;
  }
  IMP4IPMPDescriptor* ipmpDesc = imif->CreateIPMPDescriptor();
  if (ipmpDesc == 0) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::Finish: could not create IPMP descriptor.");
    return false;
  }
  if (ipmpDesc->SetIPMPDescriptorIdentifier(255) == false) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::Finish: ipmpDesc->SetIPMPDescriptorIdentifier() error.");
    return false;
  }
  if (ipmpDesc->SetIPMPDescriptorType(65535) == false) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::Finish: ipmpDesc->SetIPMPDescriptorType() error.");
    return false;
  }

  std::string toolID = OPENIPMP_TOOLID;
  UInt32T ipmpDataSize = 1 + toolID.size() + 1 + contentID.size() + 1 + rightsHost.size() + 1;
  ByteT* ipmpData = (ByteT*)malloc(ipmpDataSize);
  if (ipmpData == 0) {
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::Finish: memory allocation error.");
    return false;
  }
  //  Save the encryption method.
  *ipmpData = (ByteT)(BLOWFISH);
  memcpy(ipmpData + 1, toolID.data(), toolID.size() + 1);
  memcpy(ipmpData + 1 + toolID.size() + 1, contentID.data(), contentID.size() + 1);
  memcpy(ipmpData + 1 + toolID.size() + 1 + contentID.size() + 1, rightsHost.data(),
    rightsHost.size() + 1);

  if (ipmpDesc->SetIPMPData(ipmpData, ipmpDataSize) == false) {
    free(ipmpData);
    encLogger.UpdateLog("BlowfishOpenIPMPMPEG4SinfDRMEncryptor::Finish: ipmpDesc->SetIPMPData() error.");
    return false;
  }
  free(ipmpData);

  return true;
}

} // namespace MPEG4SinfDRMPlugin

} // namespace DRMPlugin
