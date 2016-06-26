/**	\file MPEG2IPMPXDRMEncoder.cpp

	MPEG2 DRM encoder with IPMPX signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "MPEG2IPMPXDRMEncoder.h"
#include "OpenIPMPMPEG2IPMPXDRMEncryptor.h"
#include "CRC32Calculator.h"
#include "ContentInfoManagerFactory.h"
#include "OpenIPMPDRMEncManagerFactory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  MPEG2 DRM encoder with IPMPX signalling.
*/
/*! \brief  Constructor.

    \param  logger      message logger.
*/
MPEG2IPMPXDRMEncoder::MPEG2IPMPXDRMEncoder(DRMLogger& logger): encryptors(), drmLogger(logger) {
}

MPEG2IPMPXDRMEncoder::~MPEG2IPMPXDRMEncoder() {
  std::vector<MPEG2IPMPXDRMEncryptor*>::iterator iter = encryptors.begin();
  while (iter != encryptors.end()) {
    if (*iter != 0) {
      delete *iter;
    }
    iter++;
  }
}

/*! \brief  Create MPEG2 DRM encryptor with IPMPX signalling.

    Create new DRM encryptor that will be used by the caller to protect
    MPEG2 data.

    XML document contains necessary information for protecting the content.
    
    Mandatory tags in the XML document are:
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
     <ContentTitle>testfile.mpg</ContentTitle>
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


    \warning  The newly created encryptor will later be used by the MPEG2
              DRM encoder, so caller MUST NOT delete it, just use it's
              functionality.

    \warning  Input content identifier must be different for each call to
              this function. Thus if protecting multiple streams with
              different encryptors, it must be different for each stream
              (e.g. file name + stream identifier).

    \param  content         input, basic content identifier.
    \param  xmlDoc          input, XML document.
    \param  eMethod         encryption method (AES128CTR or BLOWFISH).
    \param  encryptor       output, newly created encryptor (if successful).

    \returns  Boolean indicating success or failure.
*/
bool MPEG2IPMPXDRMEncoder::CreateMPEG2IPMPXDRMEncryptor(std::string& content,
    IXMLElement* xmlDoc, EncMethod eMethod, IMPEG2IPMPXDRMEncryptor** encryptor) {
  ContentInfoManager* infoManager = 0;
  IOpenIPMPDRMEncManager* drmManager = 0;
  MPEG2IPMPXDRMEncryptor* enc = 0;

  try {
    if (xmlDoc == 0) {
      drmLogger.UpdateLog("MPEG2IPMPXDRMEncoder::CreateMPEG2IPMPXDRMEncryptor: Invalid XML document...");
      return false;
    }
    infoManager = ContentInfoManagerFactory::GetContentInfoManager(
      OPENIPMPDOIINFOMANAGER, xmlDoc, drmLogger);
    if (infoManager == 0) {
      return false;
    }
    DRMPlugin::IXMLElement* elem = xmlDoc->GetChildElement("ContentTitle");
    if (elem == 0) {
      delete infoManager;
      return false;
    }
    if (elem->SetStrValue(content) == false) {
      delete infoManager;
      return false;
    }

    std::string info;
    if (infoManager->GetContentInfo(xmlDoc, info) == false) {
      delete infoManager;
      return false;
    }
    delete infoManager; infoManager = 0;

    drmManager = OpenIPMPDRMEncManagerFactory::GetOpenIPMPDRMEncManager(xmlDoc,
      drmLogger);
    if (drmManager == 0) {
      return false;
    }

    if (eMethod == EncMethod(BLOWFISH)) {
      enc = new BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor(drmManager, info,
        xmlDoc, drmLogger);
    } else if (eMethod == EncMethod(AES128CTR)) {
      enc = new AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor(drmManager, info,
        xmlDoc, drmLogger);
    } else {
      delete drmManager;
      return false;
    }
    //  When and where to add license?
    drmManager->AddLicense(info, xmlDoc);
    delete drmManager; drmManager = 0;
  }
  catch (...) {
    if (infoManager != 0) delete infoManager;
    if (drmManager != 0) delete drmManager;
    if (enc != 0) delete enc;
    return false;
  }

  encryptors.push_back(enc);
  *encryptor = enc;
  return true;
}

/*! \brief  Add DRM information to MPEG2 transport stream.

    IMPEG2IPMPXDRMEncoder will use the functionality of the IMPEG2IPMPXTStreamEncoder
    to add DRM information.

    \param  tsEncoder       input, transport stream encoder.

    \returns  Boolean indicating success or failure.
*/
bool MPEG2IPMPXDRMEncoder::AddDRMInfo(IMPEG2IPMPXTStreamEncoder* tsEncoder) {
  ByteSeq cInfos;
  std::vector<MPEG2IPMPXDRMEncryptor*>::iterator iter = encryptors.begin();

  //  First we create all the IPMP control infos of all encryptors.
  while (iter != encryptors.end()) {
    ByteSeq cInfo;
    if ((*iter)->CreateControlInfo(cInfo) == false) {
      return false;
    }
    cInfos += cInfo;
    iter++;
  }
  /*  Check if 16-bit value is enough for holding the control infos. If not,
      then it's an error.
  */
  if (cInfos.GetLength() >= (1 << 16)) {
    return false;
  }

  //  Now we must create correctly sized control info parts.
  /*  First we must calculate the size of signature/certificate part, if we
      want to sign control info classes. Size is given by the following formula:
      size =  1 (signed flag) + signature size + (certificate type +
              certificate size of all certificates) + 16 (verifying tool ID).
  */
  int sigCertSize = 0;
  if (false) {
    //  We're signing control info classes.
    sigCertSize = 1 + 128 + 1024 + 16;
  } else {
    //  We're not signing control info classes.
    sigCertSize = 0;
  }
  /*  Now we need to calculate size of the control info part size without
      control info classes and signature/certificate part. Size is given by the
      following formula:
      cInfoSize = 1 (table ID) + 2 (section syntax indicator + 0 + reserved +
                  section length) + 1 (reserved + control info version + current
                  next indicator) + 1 (section number) + 1 + (last section number)
                  + 2 (control info classes total length) + 2 (control info
                  classes length in a part) + 4 (CRC size).
  */
  int cInfoSize = 14;
  //  Maximal part size.
  int maxSize = 4093;
  /*  Since we need to set last part number, we must save all the created
      parts pointers, cause we don't know the last part number till we're
      done with packing. We shall also add CRCs then, cause we cannot
      calculate them without last part number.
  */
  std::vector<IInterTStreamIPMPControlInfoPart*> interParts;
  ByteT partNumber = 0;
  UInt16T totalLen = (UInt16T)cInfos.GetLength();
  while ((maxSize - sigCertSize - cInfoSize - (long int)cInfos.GetLength()) < 0) {
    //  Add new intermediate part.
    IInterTStreamIPMPControlInfoPart* interPart;
    if (tsEncoder->CreateInterIPMPControlInfoPart(&interPart) == false) {
      return false;
    }
    if (interPart->SetTableID(0x07) == false) {
      return false;
    }
    if (interPart->SetSectionSyntaxIndicator(true) == false) {
      return false;
    }
    if (interPart->SetIPMPControlInfoVersion(0x0) == false) {
      return false;
    }
    if (interPart->SetCurrentNextIndicator(true) == false) {
      return false;
    }
    if (interPart->SetPartNumber(partNumber++) == false) {
      return false;
    }
    if (interPart->SetTotalControlInfoClassesLen(totalLen) == false) {
      return false;
    }
    ByteSeq tmp = cInfos.GetBytes(maxSize - cInfoSize);
    if (interPart->SetIPMPControlInfos(tmp) == false) {
      return false;
    }
  }
  /*  Now we only have to add last part, so we can set last part number for
      all intermediate parts, and calculate CRCs.
  */
  std::vector<IInterTStreamIPMPControlInfoPart*>::iterator interIter =
    interParts.begin();
  while (interIter != interParts.end()) {
    if ((*interIter)->SetLastPartNumber(partNumber) == false) {
      return false;
    }
    ByteSeq encoded;
    if ((*interIter)->MPEG2Encode(encoded) == false) {
      return false;
    }
    CRC32Calculator calc;
    UInt32T crc = calc.GetCRC(encoded.GetFirst(), encoded.GetLength());
    if ((*interIter)->SetCRC32Code(crc) == false) {
      return false;
    }
    interIter++;
  }
  //  Add last part.
  ILastTStreamIPMPControlInfoPart* lastPart;
  if (tsEncoder->CreateLastIPMPControlInfoPart(&lastPart) == false) {
    return false;
  }
  if (lastPart->SetTableID(0x07) == false) {
    return false;
  }
  if (lastPart->SetSectionSyntaxIndicator(true) == false) {
    return false;
  }
  if (lastPart->SetIPMPControlInfoVersion(0x0) == false) {
    return false;
  }
  if (lastPart->SetCurrentNextIndicator(true) == false) {
    return false;
  }
  if (lastPart->SetPartNumber(partNumber) == false) {
    return false;
  }
  if (lastPart->SetTotalControlInfoClassesLen(totalLen) == false) {
    return false;
  }
  if (lastPart->SetIPMPControlInfos(cInfos) == false) {
    return false;
  }
  //  Add CRC code.
  ByteSeq encoded;
  if (lastPart->MPEG2Encode(encoded) == false) {
    return false;
  }
  CRC32Calculator calc;
  UInt32T crc = calc.GetCRC(encoded.GetFirst(), encoded.GetLength());
  if (lastPart->SetCRC32Code(crc) == false) {
    return false;
  }
  return true;
}

/*! \brief  Add DRM information to MPEG2 program stream.

    IMPEG2IPMPXDRMEncoder will use the functionality of the IMPEG2IPMPXPStreamEncoder
    to add DRM information.

    \param  psEncoder       input, program stream encoder.

    \returns  Boolean indicating success or failure.
*/
bool MPEG2IPMPXDRMEncoder::AddDRMInfo(IMPEG2IPMPXPStreamEncoder* psEncoder) {
  ByteSeq cInfos;
  std::vector<MPEG2IPMPXDRMEncryptor*>::iterator iter = encryptors.begin();

  //  First we create all the IPMP control infos of all encryptors.
  while (iter != encryptors.end()) {
    ByteSeq cInfo;
    if ((*iter)->CreateControlInfo(cInfo) == false) {
      return false;
    }
    cInfos += cInfo;
    iter++;
  }

  //  Now we must create correctly sized control info parts.
  /*  First we must calculate the size of signature/certificate part, if we
      want to sign control info classes. Size is given by the following formula:
      size =  1 (signed flag) + signature size + (certificate type +
              certificate size of all certificates) + 16 (verifying tool ID).
  */
  int sigCertSize = 0;
  if (false) {
    //  We're signing control info classes.
    sigCertSize = 1 + 128 + 1024 + 16;
  } else {
    //  We're not signing control info classes.
    sigCertSize = 0;
  }
  /*  Now we need to calculate size of the control info part size without
      control info classes and signature/certificate part. Size is given by the
      following formula:
      cInfoSize = 3 (packet start code prefix) + 1 (stream id) + 2 (packet length)
                  + 2 (constant + PES extension flag) + 1 (PES header data length)
                  + 1 (constant + PES extension flag 2) + 1 (constant) + 1 (stream
                  id extension flag + stream id extension) + 1 (IPMP control info
                  version + current next indicator + reserved) + 1 (IPMP control
                  info packet number) + 1 (last packet number) + 2 (control info
                  classes length in a part) + 4 (CRC size).
  */
  int cInfoSize = 21;
  //  Maximal part size.
  int maxSize = ((1 << 16) - 1);
  /*  Since we need to set last part number, we must save all the created
      parts pointers, cause we don't know the last part number till we're
      done with packing. We shall also add CRCs then, cause we cannot
      calculate them without last part number.
  */
  std::vector<IInterPStreamIPMPControlInfoPart*> interParts;
  ByteT partNumber = 0;
  UInt16T totalLen = (UInt16T)cInfos.GetLength();
  while ((maxSize - sigCertSize - cInfoSize - (long int)cInfos.GetLength()) < 0) {
    //  Add new intermediate part.
    IInterPStreamIPMPControlInfoPart* interPart;
    if (psEncoder->CreateInterIPMPControlInfoPart(&interPart) == false) {
      return false;
    }
    if (interPart->SetPacketStartCodePrefix(0x000001) == false) {
      return false;
    }
    if (interPart->SetStreamID(0xfd) == false) {
      return false;
    }
    if (interPart->SetPESExtensionFlag(true) == false) {
      return false;
    }
    if (interPart->SetPESExtensionFlag2(true) == false) {
      return false;
    }
    if (interPart->SetStreamIDExtensionFlag(true) == false) {
      return false;
    }
    //  Check this!
    if (interPart->SetStreamIDExtension(0x0) == false) {
      return false;
    }
    if (interPart->SetIPMPControlInfoVersion(0x0) == false) {
      return false;
    }
    if (interPart->SetCurrentNextIndicator(true) == false) {
      return false;
    }
    if (interPart->SetPartNumber(partNumber++) == false) {
      return false;
    }
    ByteSeq tmp = cInfos.GetBytes(maxSize - cInfoSize);
    if (interPart->SetIPMPControlInfos(tmp) == false) {
      return false;
    }
  }
  /*  Now we only have to add last part, so we can set last part number for
      all intermediate parts, and calculate CRCs.
  */
  std::vector<IInterPStreamIPMPControlInfoPart*>::iterator interIter =
    interParts.begin();
  while (interIter != interParts.end()) {
    if ((*interIter)->SetLastPartNumber(partNumber) == false) {
      return false;
    }
    ByteSeq encoded;
    if ((*interIter)->MPEG2Encode(encoded) == false) {
      return false;
    }
    CRC32Calculator calc;
    UInt32T crc = calc.GetCRC(encoded.GetFirst(), encoded.GetLength());
    if ((*interIter)->SetCRC32Code(crc) == false) {
      return false;
    }
    interIter++;
  }
  //  Add last part.
  ILastPStreamIPMPControlInfoPart* lastPart;
  if (psEncoder->CreateLastIPMPControlInfoPart(&lastPart) == false) {
    return false;
  }
  if (lastPart->SetPacketStartCodePrefix(0x000001) == false) {
    return false;
  }
  if (lastPart->SetStreamID(0xfd) == false) {
    return false;
  }
  if (lastPart->SetPESExtensionFlag(true) == false) {
    return false;
  }
  if (lastPart->SetPESExtensionFlag2(true) == false) {
    return false;
  }
  if (lastPart->SetStreamIDExtensionFlag(true) == false) {
    return false;
  }
  //  Check this!
  if (lastPart->SetStreamIDExtension(0x0) == false) {
    return false;
  }
  if (lastPart->SetIPMPControlInfoVersion(0x0) == false) {
    return false;
  }
  if (lastPart->SetCurrentNextIndicator(true) == false) {
    return false;
  }
  if (lastPart->SetPartNumber(partNumber) == false) {
    return false;
  }
  if (lastPart->SetIPMPControlInfos(cInfos) == false) {
    return false;
  }
  //  Add CRC code.
  ByteSeq encoded;
  if (lastPart->MPEG2Encode(encoded) == false) {
    return false;
  }
  CRC32Calculator calc;
  UInt32T crc = calc.GetCRC(encoded.GetFirst(), encoded.GetLength());
  if (lastPart->SetCRC32Code(crc) == false) {
    return false;
  }
  return true;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
