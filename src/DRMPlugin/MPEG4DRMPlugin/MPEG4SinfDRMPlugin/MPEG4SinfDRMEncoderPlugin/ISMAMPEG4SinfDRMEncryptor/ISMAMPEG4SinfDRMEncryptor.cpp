/**	\file ISMAMPEG4SinfDRMEncryptor.cpp

	ISMA MPEG4 DRM encryptor plugin with Sinf signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "ISMAMPEG4SinfDRMEncryptor.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG4SinfDRMPlugin namespace. All MPEG4 Sinf DRM plugin code resides in it.
namespace MPEG4SinfDRMPlugin {

/*! \brief  Encrypts MP4 data using AES128ICM encryptor according to ISMA
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
    \param      conID           input-output, content identifier.
    \param      xmlDoc          input, XML document.
    \param      logger          input-output, message logger.

    If constructor fails, it throws MPEG4DRMPluginException.
*/
AES128ICMISMAMPEG4SinfDRMEncryptor::AES128ICMISMAMPEG4SinfDRMEncryptor(
    IISMADRMEncManager* drm, std::string& conID, IXMLElement* xmlDoc,
    DRMLogger& logger): encryptor(0), contentID(), rightsHost(), encLogger(logger) {
  if (xmlDoc == 0) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::ctor: zero XML file.");
    throw MPEG4DRMPluginException();
  }
  encryptor = drm->CreateAES128ICMEnc(conID, xmlDoc);
  if (encryptor == 0) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::ctor: zero encryptor.");
    throw MPEG4DRMPluginException();
  }
  contentID = conID;
  try {
    rightsHost = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    delete encryptor;
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::ctor: missing data in XML file.");
    throw MPEG4DRMPluginException();
  }
}

AES128ICMISMAMPEG4SinfDRMEncryptor::~AES128ICMISMAMPEG4SinfDRMEncryptor() {
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
bool AES128ICMISMAMPEG4SinfDRMEncryptor::EncryptSample(ByteT* sampleBuffer,
    UInt32T sampleSize, ByteT** encSampleData, UInt32T* encSampleLen) {
  int headerLength;

  ByteT* iv;
  UInt32T ivLen;
  if (encryptor->NextIV(&iv, &ivLen) == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::EncryptSample: cannot get next initialization vector...");
    return false;
  }
  //! Sanity check for iv length.
//  if (ivLen != contentInfo.GetIVLen()) {
  if (ivLen != 16) {
    if (iv != NULL) free(iv);
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::EncryptSample: invalid initialization vector size.");
    return false;
  }

  ByteT* tmp;
  UInt32T tmpLen;
  if (encryptor->Encrypt(sampleBuffer, sampleSize, &tmp, &tmpLen) == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::EncryptSample: encryption error...");
    if (iv != NULL) free(iv);
    return false;
  }

//  headerLength = contentInfo.GetKeyIndLen() + contentInfo.GetIVLen();
  headerLength = 0 + ivLen;

  *encSampleData = (ByteT *)malloc(headerLength + tmpLen);
  if (*encSampleData == NULL) {
    if (tmp != NULL) free(tmp); 
    if (iv != NULL) free(iv);
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::EncryptSample: memory allocation error.");
    return false; 
  }
  memcpy((*encSampleData) + headerLength, tmp, tmpLen);
//  memset(*encSampleData, 0, contentInfo.GetKeyIndLen());
  memset(*encSampleData, 0, 0);
//  memcpy((*encSampleData) + contentInfo.GetKeyIndLen(), iv, ivLen);
  memcpy((*encSampleData) + 0, iv, ivLen);
  *encSampleLen = headerLength + tmpLen;

  if (tmp != NULL) free(tmp); 
  if (iv != NULL) free(iv);
  
  return true;
}

/*! \brief  Add drm information into sinf atom.

    Caller must take care that given sinf atom really coresponds to sample
    description atom which refers to encrypted samples.

    \param    originalFormat  input, 4CC code of the original data format.
    \param    sinf            input-output, sinf atom where to add drm information.

    \return Boolean indicating success or failure.
*/
bool AES128ICMISMAMPEG4SinfDRMEncryptor::Finish(UInt32T originalFormat,
    IMP4SinfAtom* sinf) {
	IMP4FrmaAtom* frma = sinf->GetOriginalFormat();
  if (frma == 0) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: no original format atom.");
    return false;
  }
  if (frma->SetDataFormat(originalFormat) == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: frma->SetDataFormat() error.");
    return false;
  }

  IMP4SchmAtom* schm = sinf->CreateSchemeType();
  if (schm == 0) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: could not create scheme type atom.");
    return false;
  }
  if (schm->SetSchemeCode(('i' << 24) | ('A' << 16) | ('E' << 8) | 'C') == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: schm->SetSchemeCode() error.");
    return false;
  }
  if (schm->SetSchemeVersion(1) == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: schm->SetSchemeVersion() error.");
    return false;
  }

  IMP4SchiAtom* schi = sinf->CreateSchemeInformation();
  if (schi == 0) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: could not create scheme information atom.");
    return false;
  }

  IMP4IKMSAtom* iKMS = schi->CreateISMAKMSAtom();
  IMP4ISFMAtom* iSFM = schi->CreateISMASFMAtom();
  if ((iKMS == 0) || (iSFM == 0)) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: could not create ISMA drm atoms.");
    return false;
  }

  if (iKMS->SetKeyManagementSystemURI(rightsHost.data()) == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: iKMS->SetKeyManagementSystemURI() error.");
    return false;
  }
//  if (iSFM->SetSelectiveEncryption(((contentInfo.GetSelectiveEnc() == 0)? false: true))
  if (iSFM->SetSelectiveEncryption(false) == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: iSFM->SetSelectiveEncryption() error.");
    return false;
  }
//  if (iSFM->SetKeyIndicatorLength(contentInfo.GetKeyIndLen()) == false) {
  if (iSFM->SetKeyIndicatorLength(0) == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: iSFM->SetKeyIndicatorLength() error.");
    return false;
  }
//  if (iSFM->SetIVLength(contentInfo.GetIVLen()) == false) {
  if (iSFM->SetIVLength(16) == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: iSFM->SetIVLength() error.");
    return false;
  }

  IMP4ImifAtom* imif = sinf->CreateIPMPInfo();
  if (imif == 0) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: could not create IPMP info atom.");
    return false;
  }
  IMP4IPMPDescriptor* ipmpDesc = imif->CreateIPMPDescriptor();
  if (ipmpDesc == 0) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: could not create IPMP descriptor.");
    return false;
  }
  if (ipmpDesc->SetIPMPDescriptorIdentifier(1) == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: ipmpDesc->SetIPMPDescriptorIdentifier() error.");
    return false;
  }
  if (ipmpDesc->SetIPMPDescriptorType(0x4953) == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: ipmpDesc->SetIPMPDescriptorType() error.");
    return false;
  }
  if (ipmpDesc->SetIPMPData((ByteT*)(contentID.data()), contentID.size() + 1)
      == false) {
    encLogger.UpdateLog("AES128ICMISMAMPEG4SinfDRMEncryptor::Finish: ipmpDesc->SetIPMPData() error.");
    return false;
  }

  return true;
}

} // namespace MPEG4SinfDRMPlugin

} // namespace DRMPlugin
