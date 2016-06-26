/**	\file OMAMPEG4SinfDRMEncryptor.cpp

	OMA MPEG4 DRM encryptor plugin with Sinf signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "MPEG4DRMPluginException.h"
#include "OMAMPEG4SinfDRMEncryptor.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG4SinfDRMPlugin namespace. All MPEG4 Sinf DRM plugin code resides in it.
namespace MPEG4SinfDRMPlugin {

/*! \brief  Encrypts MP4 data using AES128CBC encryptor according to OMA
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
     <SilentHeader>Silent:on-demand;http://www.silent.com/</SilentHeader>
     <PreviewHeader>Preview:instant;http://www.preview.com/</PreviewHeader>
     <ContentURLHeader>ContentURL:http://www.content.com/</ContentURLHeader>
     <ContentVersionHeader>ContentVersion:original-content-identifier:1.1</ContentVersionHeader>
     <ContentLocationHeader>Content-Location:http://www.content.com/</ContentLocationHeader>
    </ROOT>

    \endverbatim

    \param      drm             input, DRM manager.
    \param      conID           input-output, content identifier.
    \param      xmlDoc          input, XML document.
    \param      logger          input-output, message logger.

    If constructor fails, it throws MPEG4DRMPluginException.
*/
AES128CBCOMAMPEG4SinfDRMEncryptor::AES128CBCOMAMPEG4SinfDRMEncryptor(IOMADRMEncManager*
    drm, std::string& conID, IXMLElement* xmlDoc, DRMLogger& logger):
    encryptor(0), contentID(), rightsHost(), silentHdr(), previewHdr(),
    contentURLHdr(), contentVerHdr(), contentLocHdr(), pTextLen(0), encLogger(logger) {
  if (xmlDoc == 0) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::ctor: zero XML file.");
    throw MPEG4DRMPluginException();
  }
  encryptor = drm->CreateAES128CBCEnc(conID, xmlDoc);
  if (encryptor == 0) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::ctor: zero encryptor.");
    throw MPEG4DRMPluginException();
  }
  contentID = conID;
  try {
    rightsHost = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    delete encryptor;
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::ctor: missing data in XML file.");
    throw MPEG4DRMPluginException();
  }
  try {
    silentHdr = xmlDoc->GetChildStrValue("SilentHeader");
  }
  catch (XMLException) {
  }
  try {
    previewHdr = xmlDoc->GetChildStrValue("PreviewHeader");
  }
  catch (XMLException) {
  }
  try {
    contentURLHdr = xmlDoc->GetChildStrValue("ContentURLHeader");
  }
  catch (XMLException) {
  }
  try {
    contentVerHdr = xmlDoc->GetChildStrValue("ContentVersionHeader");
  }
  catch (XMLException) {
  }
  try {
    contentLocHdr = xmlDoc->GetChildStrValue("ContentLocationHeader");
  }
  catch (XMLException) {
  }
}

AES128CBCOMAMPEG4SinfDRMEncryptor::~AES128CBCOMAMPEG4SinfDRMEncryptor() {
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
bool AES128CBCOMAMPEG4SinfDRMEncryptor::EncryptSample(ByteT* sampleBuffer,
    UInt32T sampleSize, ByteT** encSampleData, UInt32T* encSampleLen) {
  //  Get next IV.
  ByteT* iv;
  UInt32T ivLen;
  if (encryptor->NextIV(&iv, &ivLen) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::EncryptSample: cannot get next initialization vector...");
    return false;
  }
  //  Encrypt sample.
  ByteT* enc;
  UInt32T encLen;
  //  Encrypt sample.
  if (encryptor->Encrypt(sampleBuffer, sampleSize, &enc, &encLen) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::EncryptSample: encryption error...");
    if (iv != NULL) {
      free(iv);
    }
    return false;
  }

  /*  Allocate memory (1 byte for selective encryption + 1 for iv length +
      1 for counter length + size of the IV + size of the encrypted block).
  */
  *encSampleData = (ByteT*)malloc(3 + ivLen + encLen);
  if (*encSampleData == NULL) {
    if (iv != NULL) {
      free(iv);
    }
    if (enc != NULL) {
      free(enc);
    }
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::EncryptSample: memory allocation error.");
    return false;
  }
  *encSampleLen = 3 + ivLen + encLen;
  ByteT* tmp = *encSampleData;
  //  Add AU header.
  //  Selective encryption indicator.
//  *tmp++ = (contentInfo.GetSelectiveEncryption() == true? 0x80: 0);
  *tmp++ = 0x80;
  //  Counter length.
  *tmp++ = 0;
  //  IV length.
  *tmp++ = (ByteT)ivLen;
  memcpy(tmp, iv, ivLen);
  tmp += ivLen;
  memcpy(tmp, enc, encLen);
  if (iv != NULL) {
    free(iv);
  }
  if (enc != NULL) {
    free(enc);
  }
  pTextLen += sampleSize;

  return true;
}

/*! \brief  Add drm information into sinf atom.

    Caller must take care that given sinf atom really coresponds to sample
    description atom which refers to encrypted samples.

    \param    originalFormat  input, 4CC code of the original data format.
    \param    sinf            input-output, sinf atom where to add drm information.

    \return Boolean indicating success or failure.
*/
bool AES128CBCOMAMPEG4SinfDRMEncryptor::Finish(UInt32T originalFormat,
    IMP4SinfAtom* sinf) {
	IMP4FrmaAtom* frma = sinf->GetOriginalFormat();
  if (frma == 0) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: no original format atom.");
    return false;
  }
  if (frma->SetDataFormat(originalFormat) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: frma->SetDataFormat() error.");
    return false;
  }

  IMP4SchmAtom* schm = sinf->CreateSchemeType();
  if (schm == 0) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: could not create scheme type atom.");
    return false;
  }
  if (schm->SetSchemeCode(('o' << 24) | ('d' << 16) | ('k' << 8) | 'm') == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: schm->SetSchemeCode() error.");
    return false;
  }
  if (schm->SetSchemeVersion(0x0200) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: schm->SetSchemeVersion() error.");
    return false;
  }

  IMP4SchiAtom* schi = sinf->CreateSchemeInformation();
  if (schi == 0) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: could not create scheme information atom.");
    return false;
  }

  IMP4OdkmAtom* odkm = schi->CreateOMADRMAtom();
  if (odkm == 0) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: could not create OMA drm atom.");
    return false;
  }

  IMP4OhdrAtom* ohdr = odkm->GetOMADRMHeaders();
  if (ohdr == 0) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: could not create OMA drm headers atom.");
    return false;
  }

  if (ohdr->SetAtomVersion(0) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetAtomVersion() error.");
    return false;
  }
  if (ohdr->SetAtomFlags(0) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetAtomFlags() error.");
    return false;
  }
  if (ohdr->SetEncryptionMethod(1) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetEncryptionMethod() error.");
    return false;
  }
  if (ohdr->SetEncryptionPadding(1) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetEncryptionPadding() error.");
    return false;
  }
  if (ohdr->SetPlaintextLength(pTextLen) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetPlaintextLength() error.");
    return false;
  }
  if (ohdr->SetContentIdentifier(contentID.data()) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetContentIdentifier() error.");
    return false;
  }
  if (ohdr->SetRightsIssuerURL(rightsHost.data()) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetRightsIssuerURL() error.");
    return false;
  }

  unsigned int len = 0;
  unsigned int tmpLen;
  tmpLen = silentHdr.size();
  len += (tmpLen > 0? tmpLen + 1: 0);
  tmpLen = previewHdr.size();
  len += (tmpLen > 0? tmpLen + 1: 0);
  tmpLen = contentURLHdr.size();
  len += (tmpLen > 0? tmpLen + 1: 0);
  tmpLen = contentVerHdr.size();
  len += (tmpLen > 0? tmpLen + 1: 0);
  tmpLen = contentLocHdr.size();
  len += (tmpLen > 0? tmpLen + 1: 0);

  ByteT* pValue = (ByteT*)malloc(len);
  if (pValue == NULL) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: memory allocation error.");
    return false;
  }
  unsigned int pos = 0;
  tmpLen = silentHdr.size();
  if (tmpLen > 0) {
    memcpy(pValue + pos, silentHdr.data(), tmpLen + 1);
    pos += (tmpLen + 1);
  }
  tmpLen = previewHdr.size();
  if (tmpLen > 0) {
    memcpy(pValue + pos, previewHdr.data(), tmpLen + 1);
    pos += (tmpLen + 1);
  }
  tmpLen = contentURLHdr.size();
  if (tmpLen > 0) {
    memcpy(pValue + pos, contentURLHdr.data(), tmpLen + 1);
    pos += (tmpLen + 1);
  }
  tmpLen = contentVerHdr.size();
  if (tmpLen > 0) {
    memcpy(pValue + pos, contentVerHdr.data(), tmpLen + 1);
    pos += (tmpLen + 1);
  }
  tmpLen = contentLocHdr.size();
  if (tmpLen > 0) {
    memcpy(pValue + pos, contentLocHdr.data(), tmpLen + 1);
    pos += (tmpLen + 1);
  }
  if (ohdr->SetTextualHeaders(pValue, len) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetTextualHeaders() error.");
    return false;
  }
  if (pValue != 0) {
    free(pValue);
  }

  if (odkm->SetAtomVersion(0) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: odkm->SetAtomVersion() error.");
    return false;
  }
  if (odkm->SetAtomFlags(0) == false) {
    encLogger.UpdateLog("AES128CBCOMAMPEG4SinfDRMEncryptor::Finish: odkm->SetAtomFlags() error.");
    return false;
  }

  return true;
}

/*! \brief  Encrypts MP4 data using AES128CTR encryptor according to OMA
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
     <SilentHeader>Silent:on-demand;http://www.silent.com/</SilentHeader>
     <PreviewHeader>Preview:instant;http://www.preview.com/</PreviewHeader>
     <ContentURLHeader>ContentURL:http://www.content.com/</ContentURLHeader>
     <ContentVersionHeader>ContentVersion:original-content-identifier:1.1</ContentVersionHeader>
     <ContentLocationHeader>Content-Location:http://www.content.com/</ContentLocationHeader>
    </ROOT>

    \endverbatim

    \param      drm             input, DRM manager.
    \param      conID           input, content identifier.
    \param      xmlDoc          input, XML document.
    \param      logger          input-output, message logger.

    If constructor fails, it throws MPEG4DRMPluginException.
*/
AES128CTROMAMPEG4SinfDRMEncryptor::AES128CTROMAMPEG4SinfDRMEncryptor(IOMADRMEncManager*
    drm, std::string& conID, IXMLElement* xmlDoc, DRMLogger& logger):
    encryptor(0), contentID(), rightsHost(), silentHdr(), previewHdr(),
    contentURLHdr(), contentVerHdr(), contentLocHdr(), pTextLen(0), encLogger(logger) {
  if (xmlDoc == 0) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::ctor: zero XML file.");
    throw MPEG4DRMPluginException();
  }
  encryptor = drm->CreateAES128CTREnc(conID, xmlDoc);
  if (encryptor == 0) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::ctor: zero encryptor.");
    throw MPEG4DRMPluginException();
  }
  contentID = conID;
  try {
    rightsHost = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    delete encryptor;
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::ctor: missing data in XML file.");
    throw MPEG4DRMPluginException();
  }
  try {
    silentHdr = xmlDoc->GetChildStrValue("SilentHeader");
  }
  catch (XMLException) {
  }
  try {
    previewHdr = xmlDoc->GetChildStrValue("PreviewHeader");
  }
  catch (XMLException) {
  }
  try {
    contentURLHdr = xmlDoc->GetChildStrValue("ContentURLHeader");
  }
  catch (XMLException) {
  }
  try {
    contentVerHdr = xmlDoc->GetChildStrValue("ContentVersionHeader");
  }
  catch (XMLException) {
  }
  try {
    contentLocHdr = xmlDoc->GetChildStrValue("ContentLocationHeader");
  }
  catch (XMLException) {
  }
}

AES128CTROMAMPEG4SinfDRMEncryptor::~AES128CTROMAMPEG4SinfDRMEncryptor() {
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
bool AES128CTROMAMPEG4SinfDRMEncryptor::EncryptSample(ByteT* sampleBuffer,
    UInt32T sampleSize, ByteT** encSampleData, UInt32T* encSampleLen) {
  //  Get next counter.
  ByteT* ctr;
  UInt32T ctrLen;
  if (encryptor->NextCtr(&ctr, &ctrLen) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::EncryptSample: cannot get next counter...");
    return false;
  }
  //  Encrypt sample.
  ByteT* enc;
  UInt32T encLen;
  //  Encrypt sample.
  if (encryptor->Encrypt(sampleBuffer, sampleSize, &enc, &encLen) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::EncryptSample: encryption error...");
    if (ctr != NULL) {
      free(ctr);
    }
    return false;
  }

  /*  Allocate memory (1 byte for selective encryption + 1 for iv length +
      1 for counter length + size of the counter + size of the encrypted block).
  */
  *encSampleData = (ByteT*)malloc(3 + ctrLen + encLen);
  if (*encSampleData == NULL) {
    if (ctr != NULL) {
      free(ctr);
    }
    if (enc != NULL) {
      free(enc);
    }
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::EncryptSample: memory allocation error.");
    return false;
  }
  *encSampleLen = 3 + ctrLen + encLen;
  ByteT* tmp = *encSampleData;
  //  Add AU header.
  //  Selective encryption indicator.
//  *tmp++ = (contentInfo.GetSelectiveEncryption() == true? 0x80: 0);
  *tmp++ = 0x80;
  //  Counter length.
  *tmp++ = (ByteT)ctrLen;
  //  IV length.
  *tmp++ = 0;
  memcpy(tmp, ctr, ctrLen);
  tmp += ctrLen;
  memcpy(tmp, enc, encLen);
  if (ctr != NULL) {
    free(ctr);
  }
  if (enc != NULL) {
    free(enc);
  }
  pTextLen += sampleSize;

  return true;
}

/*! \brief  Add drm information into sinf atom.

    Caller must take care that given sinf atom really coresponds to sample
    description atom which refers to encrypted samples.

    \param    originalFormat  input, 4CC code of the original data format.
    \param    sinf            input-output, sinf atom where to add drm information.

    \return Boolean indicating success or failure.
*/
bool AES128CTROMAMPEG4SinfDRMEncryptor::Finish(UInt32T originalFormat,
    IMP4SinfAtom* sinf) {
	IMP4FrmaAtom* frma = sinf->GetOriginalFormat();
  if (frma == 0) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: no original format atom.");
    return false;
  }
  if (frma->SetDataFormat(originalFormat) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: frma->SetDataFormat() error.");
    return false;
  }

  IMP4SchmAtom* schm = sinf->CreateSchemeType();
  if (schm == 0) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: could not create scheme type atom.");
    return false;
  }
  if (schm->SetSchemeCode(('o' << 24) | ('d' << 16) | ('k' << 8) | 'm') == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: schm->SetSchemeCode() error.");
    return false;
  }
  if (schm->SetSchemeVersion(0x0200) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: schm->SetSchemeVersion() error.");
    return false;
  }

  IMP4SchiAtom* schi = sinf->CreateSchemeInformation();
  if (schi == 0) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: could not create scheme information atom.");
    return false;
  }

  IMP4OdkmAtom* odkm = schi->CreateOMADRMAtom();
  if (odkm == 0) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: could not create OMA drm atom.");
    return false;
  }

  IMP4OhdrAtom* ohdr = odkm->GetOMADRMHeaders();
  if (ohdr == 0) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: could not create OMA drm headers atom.");
    return false;
  }

  if (ohdr->SetAtomVersion(0) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetAtomVersion() error.");
    return false;
  }
  if (ohdr->SetAtomFlags(0) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetAtomFlags() error.");
    return false;
  }
  if (ohdr->SetEncryptionMethod(2) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetEncryptionMethod() error.");
    return false;
  }
  if (ohdr->SetEncryptionPadding(0) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetEncryptionPadding() error.");
    return false;
  }
  if (ohdr->SetPlaintextLength(pTextLen) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetPlaintextLength() error.");
    return false;
  }
  if (ohdr->SetContentIdentifier(contentID.data()) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetContentIdentifier() error.");
    return false;
  }
  if (ohdr->SetRightsIssuerURL(rightsHost.data()) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetRightsIssuerURL() error.");
    return false;
  }

  unsigned int len = 0;
  unsigned int tmpLen;
  tmpLen = silentHdr.size();
  len += (tmpLen > 0? tmpLen + 1: 0);
  tmpLen = previewHdr.size();
  len += (tmpLen > 0? tmpLen + 1: 0);
  tmpLen = contentURLHdr.size();
  len += (tmpLen > 0? tmpLen + 1: 0);
  tmpLen = contentVerHdr.size();
  len += (tmpLen > 0? tmpLen + 1: 0);
  tmpLen = contentLocHdr.size();
  len += (tmpLen > 0? tmpLen + 1: 0);

  ByteT* pValue = (ByteT*)malloc(len);
  if (pValue == NULL) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: memory allocation error.");
    return false;
  }
  unsigned int pos = 0;
  tmpLen = silentHdr.size();
  if (tmpLen > 0) {
    memcpy(pValue + pos, silentHdr.data(), tmpLen + 1);
    pos += (tmpLen + 1);
  }
  tmpLen = previewHdr.size();
  if (tmpLen > 0) {
    memcpy(pValue + pos, previewHdr.data(), tmpLen + 1);
    pos += (tmpLen + 1);
  }
  tmpLen = contentURLHdr.size();
  if (tmpLen > 0) {
    memcpy(pValue + pos, contentURLHdr.data(), tmpLen + 1);
    pos += (tmpLen + 1);
  }
  tmpLen = contentVerHdr.size();
  if (tmpLen > 0) {
    memcpy(pValue + pos, contentVerHdr.data(), tmpLen + 1);
    pos += (tmpLen + 1);
  }
  tmpLen = contentLocHdr.size();
  if (tmpLen > 0) {
    memcpy(pValue + pos, contentLocHdr.data(), tmpLen + 1);
    pos += (tmpLen + 1);
  }
  if (ohdr->SetTextualHeaders(pValue, len) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: ohdr->SetTextualHeaders() error.");
    return false;
  }
  if (pValue != 0) {
    free(pValue);
  }

  if (odkm->SetAtomVersion(0) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: odkm->SetAtomVersion() error.");
    return false;
  }
  if (odkm->SetAtomFlags(0) == false) {
    encLogger.UpdateLog("AES128CTROMAMPEG4SinfDRMEncryptor::Finish: odkm->SetAtomFlags() error.");
    return false;
  }

  return true;
}

} // namespace MPEG4SinfDRMPlugin

} // namespace DRMPlugin
