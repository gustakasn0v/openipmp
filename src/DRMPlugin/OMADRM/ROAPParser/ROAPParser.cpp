/**	\file ROAPParser.cpp

	Parser for ROAP messages..

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "ROAPParser.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  ROAP parser. Parses ROAP messages from encoded XML string.
*/
/*! \brief  Parse ODDVersion.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDVersion. If fails, throws ROAPParserException.
*/
SPtr<ODDVersion> ROAPParser::ParseODDVersion(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ODDVersion(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDVersion: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDVersion: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RightsODDUID.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  RightsODDUID. If fails, throws ROAPParserException.
*/
SPtr<RightsODDUID> ROAPParser::ParseRightsODDUID(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new RightsODDUID(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRightsODDUID: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRightsODDUID: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse AssetODDUID.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  AssetODDUID. If fails, throws ROAPParserException.
*/
SPtr<AssetODDUID> ROAPParser::ParseAssetODDUID(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new AssetODDUID(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseAssetODDUID: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseAssetODDUID: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse IndividualODDUID.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  IndividualODDUID. If fails, throws ROAPParserException.
*/
SPtr<IndividualODDUID> ROAPParser::ParseIndividualODDUID(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new IndividualODDUID(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseIndividualODDUID: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseIndividualODDUID: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse SystemODDUID.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  SystemODDUID. If fails, throws ROAPParserException.
*/
SPtr<SystemODDUID> ROAPParser::ParseSystemODDUID(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new SystemODDUID(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseSystemODDUID: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseSystemODDUID: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse InheritODDUID.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  InheritODDUID. If fails, throws ROAPParserException.
*/
SPtr<InheritODDUID> ROAPParser::ParseInheritODDUID(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new InheritODDUID(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseInheritODDUID: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseInheritODDUID: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RightsOEXContext.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  RightsOEXContext. If fails, throws ROAPParserException.
*/
SPtr<RightsOEXContext> ROAPParser::ParseRightsOEXContext(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new RightsOEXContext(ParseODDVersion(xml->GetChildElement("version"), logger),
      ParseRightsODDUID(xml->GetAtMostOneChildElementByName("uid"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRightsOEXContext: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRightsOEXContext: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse AssetOEXContext.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  AssetOEXContext. If fails, throws ROAPParserException.
*/
SPtr<AssetOEXContext> ROAPParser::ParseAssetOEXContext(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new AssetOEXContext(ParseODDVersion(xml->GetChildElement("version"), logger),
      ParseAssetODDUID(xml->GetAtMostOneChildElementByName("uid"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseAssetOEXContext: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseAssetOEXContext: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse IndividualOEXContext.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  IndividualOEXContext. If fails, throws ROAPParserException.
*/
SPtr<IndividualOEXContext> ROAPParser::ParseIndividualOEXContext(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new IndividualOEXContext(ParseODDVersion(xml->GetChildElement("version"), logger),
      ParseVector<IndividualODDUID, IndividualODDUID>(
        xml->GetChildElementsByName("uid"), ParseIndividualODDUID, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseIndividualOEXContext: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseIndividualOEXContext: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse SystemOEXContext.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  SystemOEXContext. If fails, throws ROAPParserException.
*/
SPtr<SystemOEXContext> ROAPParser::ParseSystemOEXContext(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new SystemOEXContext(ParseODDVersion(xml->GetChildElement("version"), logger),
      ParseVector<SystemODDUID, SystemODDUID>(
        xml->GetChildElementsByName("uid"), ParseSystemODDUID, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseSystemOEXContext: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseSystemOEXContext: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse InheritOEXContext.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  InheritOEXContext. If fails, throws ROAPParserException.
*/
SPtr<InheritOEXContext> ROAPParser::ParseInheritOEXContext(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new InheritOEXContext(ParseODDVersion(xml->GetChildElement("version"), logger),
      ParseInheritODDUID(xml->GetAtMostOneChildElementByName("uid"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseInheritOEXContext: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseInheritOEXContext: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OEXAssetID.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  OEXAssetID. If fails, throws ROAPParserException.
*/
SPtr<OEXAssetID> ROAPParser::ParseOEXAssetID(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new OEXAssetID(ParseIDValue(xml, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOEXAssetID: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOEXAssetID: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OEXAssetIDRef.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  OEXAssetIDRef. If fails, throws ROAPParserException.
*/
SPtr<OEXAssetIDRef> ROAPParser::ParseOEXAssetIDRef(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new OEXAssetIDRef(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOEXAssetIDRef: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOEXAssetIDRef: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OEXInherit.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  OEXInherit. If fails, throws ROAPParserException.
*/
SPtr<OEXInherit> ROAPParser::ParseOEXInherit(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new OEXInherit(ParseInheritOEXContext(xml->GetChildElement("context"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOEXInherit: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOEXInherit: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OEXDigest.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  OEXDigest. If fails, throws ROAPParserException.
*/
SPtr<OEXDigest> ROAPParser::ParseOEXDigest(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new OEXDigest(ParseDSDigestValue(xml->GetChildElement("DigestValue"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOEXDigest: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOEXDigest: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RORetrievalMethod.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  RORetrievalMethod. If fails, throws ROAPParserException.
*/
SPtr<RORetrievalMethod> ROAPParser::ParseRORetrievalMethod(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new RORetrievalMethod(new URIValue(xml->GetChildAttrStrValue("", "URI")));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRORetrievalMethod: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRORetrievalMethod: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROEncryptedKeyInfo.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROEncryptedKeyInfo. If fails, throws ROAPParserException.
*/
SPtr<ROEncryptedKeyInfo> ROAPParser::ParseROEncryptedKeyInfo(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROEncryptedKeyInfo(ParseRORetrievalMethod(
      xml->GetChildElement("RetrievalMethod"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROEncryptedKeyInfo: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROEncryptedKeyInfo: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROXencEncryptionMethod.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROXencEncryptionMethod. If fails, throws ROAPParserException.
*/
SPtr<ROXencEncryptionMethod> ROAPParser::ParseROXencEncryptionMethod(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROXencEncryptionMethod();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROXencEncryptionMethod: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROXencEncryptionMethod: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROEncryptedKey.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROEncryptedKey. If fails, throws ROAPParserException.
*/
SPtr<ROEncryptedKey> ROAPParser::ParseROEncryptedKey(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROEncryptedKey(ParseROEncryptedKeyInfo(xml->GetChildElement("KeyInfo"), logger),
      ParseROXencEncryptionMethod(xml->GetChildElement("EncryptionMethod"), logger),
      ParseCValueXencCipherData(xml->GetChildElement("CipherData"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROEncryptedKey: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROEncryptedKey: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OEXAssetKeyInfo.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  OEXAssetKeyInfo. If fails, throws ROAPParserException.
*/
SPtr<OEXAssetKeyInfo> ROAPParser::ParseOEXAssetKeyInfo(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new OEXAssetKeyInfo(ParseROEncryptedKey(xml->GetChildElement("EncryptedKey"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOEXAssetKeyInfo: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOEXAssetKeyInfo: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse AgreementOEXAsset.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  AgreementOEXAsset. If fails, throws ROAPParserException.
*/
SPtr<AgreementOEXAsset> ROAPParser::ParseAgreementOEXAsset(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new AgreementOEXAsset(ParseAssetOEXContext(xml->GetChildElement("asset"), logger),
      ParseOEXInherit(xml->GetChildElement("inherit"), logger),
      ParseOEXDigest(xml->GetChildElement("digest"), logger),
      ParseOEXAssetKeyInfo(xml->GetChildElement("KeyInfo"), logger),
      ParseOEXAssetID(xml->GetChildAttribute("", "id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseAgreementOEXAsset: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseAgreementOEXAsset: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse PermissionOEXAsset.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  PermissionOEXAsset. If fails, throws ROAPParserException.
*/
SPtr<PermissionOEXAsset> ROAPParser::ParsePermissionOEXAsset(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new PermissionOEXAsset(ParseOEXAssetIDRef(xml->GetChildAttribute("", "idref"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParsePermissionOEXAsset: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParsePermissionOEXAsset: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ODDCountConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDCountConstraint. If fails, throws ROAPParserException.
*/
SPtr<ODDCountConstraint> ROAPParser::ParseODDCountConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ODDCountConstraint(xml->GetChildIntValue(""));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDCountConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDCountConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OMADDTimedCountConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  OMADDTimedCountConstraint. If fails, throws ROAPParserException.
*/
SPtr<OMADDTimedCountConstraint> ROAPParser::ParseOMADDTimedCountConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttribute("", "timer") != 0) {
      return new TimerOMADDTimedCountConstraint(xml->GetIntValue(),
        xml->GetChildAttrIntValue("", "timer"));
    } else {
      return new NTimerOMADDTimedCountConstraint(xml->GetIntValue());
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOMADDTimedCountConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOMADDTimedCountConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ODDStart.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDStart. If fails, throws ROAPParserException.
*/
SPtr<ODDStart> ROAPParser::ParseODDStart(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
//    return new ODDStart(UTCTime(xml->GetStrValue()));
    return new ODDStart(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDStart: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDStart: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ODDEnd.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDEnd. If fails, throws ROAPParserException.
*/
SPtr<ODDEnd> ROAPParser::ParseODDEnd(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
//    return new ODDEnd(UTCTime(xml->GetStrValue()));
    return new ODDEnd(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDEnd: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDEnd: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ODDDatetimeConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDDatetimeConstraint. If fails, throws ROAPParserException.
*/
SPtr<ODDDatetimeConstraint> ROAPParser::ParseODDDatetimeConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("start") != 0) {
      if (xml->GetChildElement("end") != 0) {
        return new StartEndODDDatetimeConstraint(
          ParseODDStart(xml->GetChildElement("start"), logger),
          ParseODDEnd(xml->GetChildElement("end"), logger));
      } else {
        return new StartODDDatetimeConstraint(
          ParseODDStart(xml->GetChildElement("start"), logger));
      }
    } else {
      if (xml->GetChildElement("end") != 0) {
        return new EndODDDatetimeConstraint(
          ParseODDEnd(xml->GetChildElement("end"), logger));
      } else {
        return new EmptyODDDatetimeConstraint();
      }
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDDatetimeConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDDatetimeConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ODDIntervalConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDIntervalConstraint. If fails, throws ROAPParserException.
*/
SPtr<ODDIntervalConstraint> ROAPParser::ParseODDIntervalConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ODDIntervalConstraint(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDIntervalConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDIntervalConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ODDAccumulatedConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDAccumulatedConstraint. If fails, throws ROAPParserException.
*/
SPtr<ODDAccumulatedConstraint> ROAPParser::ParseODDAccumulatedConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ODDAccumulatedConstraint(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDAccumulatedConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDAccumulatedConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ODDIndividualConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDIndividualConstraint. If fails, throws ROAPParserException.
*/
SPtr<ODDIndividualConstraint> ROAPParser::ParseODDIndividualConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ODDIndividualConstraint(ParseIndividualOEXContext(
      xml->GetChildElement("context"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDIndividualConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDIndividualConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OMADDSystemConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  OMADDSystemConstraint. If fails, throws ROAPParserException.
*/
SPtr<OMADDSystemConstraint> ROAPParser::ParseOMADDSystemConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new OMADDSystemConstraint(ParseSystemOEXContext(
      xml->GetChildElement("context"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOMADDSystemConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOMADDSystemConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse GeneralOEXConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  GeneralOEXConstraint. If fails, throws ROAPParserException.
*/
SPtr<GeneralOEXConstraint> ROAPParser::ParseGeneralOEXConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new GeneralOEXConstraint(
      ParseODDCountConstraint(xml->GetChildElement("count"), logger),
      ParseOMADDTimedCountConstraint(xml->GetChildElement("timed-count"), logger),
      ParseODDDatetimeConstraint(xml->GetChildElement("datetime"), logger),
      ParseODDIntervalConstraint(xml->GetChildElement("interval"), logger),
      ParseODDAccumulatedConstraint(xml->GetChildElement("accumulated"), logger),
      ParseODDIndividualConstraint(xml->GetChildElement("individual"), logger),
      ParseVector<OMADDSystemConstraint, OMADDSystemConstraint>(
      xml->GetChildElementsByName("system"), ParseOMADDSystemConstraint, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseGeneralOEXConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseGeneralOEXConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse PlayOEXConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  PlayOEXConstraint. If fails, throws ROAPParserException.
*/
SPtr<PlayOEXConstraint> ROAPParser::ParsePlayOEXConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new PlayOEXConstraint(
      ParseODDCountConstraint(xml->GetChildElement("count"), logger),
      ParseOMADDTimedCountConstraint(xml->GetChildElement("timed-count"), logger),
      ParseODDDatetimeConstraint(xml->GetChildElement("datetime"), logger),
      ParseODDIntervalConstraint(xml->GetChildElement("interval"), logger),
      ParseODDAccumulatedConstraint(xml->GetChildElement("accumulated"), logger),
      ParseODDIndividualConstraint(xml->GetChildElement("individual"), logger),
      ParseVector<OMADDSystemConstraint, OMADDSystemConstraint>(
      xml->GetChildElementsByName("system"), ParseOMADDSystemConstraint, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParsePlayOEXConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParsePlayOEXConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DisplayOEXConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DisplayOEXConstraint. If fails, throws ROAPParserException.
*/
SPtr<DisplayOEXConstraint> ROAPParser::ParseDisplayOEXConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DisplayOEXConstraint(
      ParseODDCountConstraint(xml->GetChildElement("count"), logger),
      ParseOMADDTimedCountConstraint(xml->GetChildElement("timed-count"), logger),
      ParseODDDatetimeConstraint(xml->GetChildElement("datetime"), logger),
      ParseODDIntervalConstraint(xml->GetChildElement("interval"), logger),
      ParseODDAccumulatedConstraint(xml->GetChildElement("accumulated"), logger),
      ParseODDIndividualConstraint(xml->GetChildElement("individual"), logger),
      ParseVector<OMADDSystemConstraint, OMADDSystemConstraint>(
      xml->GetChildElementsByName("system"), ParseOMADDSystemConstraint, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDisplayOEXConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDisplayOEXConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ExecuteOEXConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ExecuteOEXConstraint. If fails, throws ROAPParserException.
*/
SPtr<ExecuteOEXConstraint> ROAPParser::ParseExecuteOEXConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ExecuteOEXConstraint(
      ParseODDCountConstraint(xml->GetChildElement("count"), logger),
      ParseOMADDTimedCountConstraint(xml->GetChildElement("timed-count"), logger),
      ParseODDDatetimeConstraint(xml->GetChildElement("datetime"), logger),
      ParseODDIntervalConstraint(xml->GetChildElement("interval"), logger),
      ParseODDAccumulatedConstraint(xml->GetChildElement("accumulated"), logger),
      ParseODDIndividualConstraint(xml->GetChildElement("individual"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseExecuteOEXConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseExecuteOEXConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse PrintOEXConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  PrintOEXConstraint. If fails, throws ROAPParserException.
*/
SPtr<PrintOEXConstraint> ROAPParser::ParsePrintOEXConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new PrintOEXConstraint(
      ParseODDCountConstraint(xml->GetChildElement("count"), logger),
      ParseODDDatetimeConstraint(xml->GetChildElement("datetime"), logger),
      ParseODDIntervalConstraint(xml->GetChildElement("interval"), logger),
      ParseODDAccumulatedConstraint(xml->GetChildElement("accumulated"), logger),
      ParseODDIndividualConstraint(xml->GetChildElement("individual"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParsePrintOEXConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParsePrintOEXConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse MoveExportOEXConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  MoveExportOEXConstraint. If fails, throws ROAPParserException.
*/
SPtr<MoveExportOEXConstraint> ROAPParser::ParseMoveExportOEXConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new MoveExportOEXConstraint(
      ParseODDDatetimeConstraint(xml->GetChildElement("datetime"), logger),
      ParseVector<OMADDSystemConstraint, OMADDSystemConstraint>(
      xml->GetChildElementsByName("system"), ParseOMADDSystemConstraint, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseMoveExportOEXConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseMoveExportOEXConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse CopyExportOEXConstraint.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  CopyExportOEXConstraint. If fails, throws ROAPParserException.
*/
SPtr<CopyExportOEXConstraint> ROAPParser::ParseCopyExportOEXConstraint(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new CopyExportOEXConstraint(
      ParseODDCountConstraint(xml->GetChildElement("count"), logger),
      ParseODDDatetimeConstraint(xml->GetChildElement("datetime"), logger),
      ParseODDIntervalConstraint(xml->GetChildElement("interval"), logger),
      ParseVector<OMADDSystemConstraint, OMADDSystemConstraint>(
      xml->GetChildElementsByName("system"), ParseOMADDSystemConstraint, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseCopyExportOEXConstraint: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseCopyExportOEXConstraint: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ODDPlayPermission.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDPlayPermission. If fails, throws ROAPParserException.
*/
SPtr<ODDPlayPermission> ROAPParser::ParseODDPlayPermission(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ODDPlayPermission(
      ParsePlayOEXConstraint(xml->GetChildElement("constraint"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDPlayPermission: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDPlayPermission: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ODDDisplayPermission.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDDisplayPermission. If fails, throws ROAPParserException.
*/
SPtr<ODDDisplayPermission> ROAPParser::ParseODDDisplayPermission(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ODDDisplayPermission(
      ParseDisplayOEXConstraint(xml->GetChildElement("constraint"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDDisplayPermission: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDDisplayPermission: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ODDExecutePermission.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDExecutePermission. If fails, throws ROAPParserException.
*/
SPtr<ODDExecutePermission> ROAPParser::ParseODDExecutePermission(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ODDExecutePermission(
      ParseExecuteOEXConstraint(xml->GetChildElement("constraint"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDExecutePermission: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDExecutePermission: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ODDPrintPermission.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ODDPrintPermission. If fails, throws ROAPParserException.
*/
SPtr<ODDPrintPermission> ROAPParser::ParseODDPrintPermission(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ODDPrintPermission(
      ParsePrintOEXConstraint(xml->GetChildElement("constraint"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseODDPrintPermission: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseODDPrintPermission: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OMADDExportPermission.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  OMADDExportPermission. If fails, throws ROAPParserException.
*/
SPtr<OMADDExportPermission> ROAPParser::ParseOMADDExportPermission(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttrStrValue("", "mode") == "move") {
      return new MoveOMADDExportPermission(
        ParseMoveExportOEXConstraint(xml->GetChildElement("constraint"), logger));
    } else if (xml->GetChildAttrStrValue("", "mode") == "copy") {
      return new CopyOMADDExportPermission(
        ParseCopyExportOEXConstraint(xml->GetChildElement("constraint"), logger));
    } else {
      throw ROAPParserException();
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOMADDExportPermission: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOMADDExportPermission: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OEXPermission.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  OEXPermission. If fails, throws ROAPParserException.
*/
SPtr<OEXPermission> ROAPParser::ParseOEXPermission(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new OEXPermission(
      ParseGeneralOEXConstraint(xml->GetChildElement("constraint"), logger),
      ParseVector<PermissionOEXAsset, PermissionOEXAsset>(
        xml->GetChildElementsByName("asset"), ParsePermissionOEXAsset, logger),
      ParseODDPlayPermission(xml->GetChildElement("play"), logger),
      ParseODDDisplayPermission(xml->GetChildElement("display"), logger),
      ParseODDExecutePermission(xml->GetChildElement("execute"), logger),
      ParseODDPrintPermission(xml->GetChildElement("print"), logger),
      ParseOMADDExportPermission(xml->GetChildElement("export"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOEXPermission: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOEXPermission: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OEXAgreement.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  OEXAgreement. If fails, throws ROAPParserException.
*/
SPtr<OEXAgreement> ROAPParser::ParseOEXAgreement(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new OEXAgreement(
      ParseVector<AgreementOEXAsset, AgreementOEXAsset>(
        xml->GetOneOrMoreChildElementsByName("asset"), ParseAgreementOEXAsset, logger),
      ParseVector<OEXPermission, OEXPermission>(
        xml->GetChildElementsByName("permission"), ParseOEXPermission, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOEXAgreement: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOEXAgreement: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OEXRights.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  OEXRights. If fails, throws ROAPParserException.
*/
SPtr<OEXRights> ROAPParser::ParseOEXRights(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new OEXRights(ParseRightsOEXContext(xml->GetChildElement("context"), logger),
      ParseOEXAgreement(xml->GetChildElement("agreement"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOEXRights: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOEXRights: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse IDValue.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  IDValue. If fails, throws ROAPParserException.
*/
SPtr<IDValue> ROAPParser::ParseIDValue(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new IDValue(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseIDValue: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseIDValue: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse IDValue.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  IDValue. If fails, throws ROAPParserException.
*/
SPtr<IDValue> ROAPParser::ParseIDValue(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new IDValue(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseIDValue: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseIDValue: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse URIValue.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  URIValue. If fails, throws ROAPParserException.
*/
SPtr<URIValue> ROAPParser::ParseURIValue(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new URIValue(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseURIValue: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseURIValue: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse URIValue.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  URIValue. If fails, throws ROAPParserException.
*/
SPtr<URIValue> ROAPParser::ParseURIValue(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new URIValue(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseURIValue: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseURIValue: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSObject.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSObject. If fails, throws ROAPParserException.
*/
SPtr<DSObject> ROAPParser::ParseDSObject(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttribute("", "MimeType") != 0) {
      return new MimeDSObject(ParseIDValue(xml->GetChildAttribute("", "Id"), logger),
        xml->GetChildAttrStrValue("", "MimeType"),
        ParseURIValue(xml->GetChildAttribute("", "Encoding"), logger));
    } else {
      return new NMimeDSObject(ParseIDValue(xml->GetChildAttribute("", "Id"), logger),
        ParseURIValue(xml->GetChildAttribute("", "Encoding"), logger));
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSObject: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSObject: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSCryptoBinary.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSCryptoBinary. If fails, throws ROAPParserException.
*/
SPtr<DSCryptoBinary> ROAPParser::ParseDSCryptoBinary(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSCryptoBinary(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSCryptoBinary: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSCryptoBinary: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSKeyName.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSKeyName. If fails, throws ROAPParserException.
*/
SPtr<DSKeyName> ROAPParser::ParseDSKeyName(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSKeyName(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSKeyName: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSKeyName: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSDSAKeyValuePQ.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSDSAKeyValuePQ. If fails, throws ROAPParserException.
*/
SPtr<DSDSAKeyValuePQ> ROAPParser::ParseDSDSAKeyValuePQ(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  if ((xml->GetChildElement("P") == 0) || (xml->GetChildElement("Q") == 0)) {
    return 0;
  }
  try {
    return new DSDSAKeyValuePQ(ParseDSCryptoBinary(xml->GetChildElement("P"), logger),
      ParseDSCryptoBinary(xml->GetChildElement("Q"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSDSAKeyValuePQ: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSDSAKeyValuePQ: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSDSAKeyValueSeedCtr.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSDSAKeyValueSeedCtr. If fails, throws ROAPParserException.
*/
SPtr<DSDSAKeyValueSeedCtr> ROAPParser::ParseDSDSAKeyValueSeedCtr(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  if ((xml->GetChildElement("Seed") == 0) || (xml->GetChildElement("PgenCounter") == 0)) {
    return 0;
  }
  try {
    return new DSDSAKeyValueSeedCtr(ParseDSCryptoBinary(xml->GetChildElement("Seed"), logger),
      ParseDSCryptoBinary(xml->GetChildElement("PgenCounter"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSDSAKeyValueSeedCtr: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSDSAKeyValueSeedCtr: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSDSAKeyValue.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSDSAKeyValue. If fails, throws ROAPParserException.
*/
SPtr<DSDSAKeyValue> ROAPParser::ParseDSDSAKeyValue(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSDSAKeyValue(ParseDSDSAKeyValuePQ(xml, logger),
      ParseDSCryptoBinary(xml->GetChildElement("G"), logger),
      ParseDSCryptoBinary(xml->GetChildElement("Y"), logger),
      ParseDSCryptoBinary(xml->GetChildElement("J"), logger),
      ParseDSDSAKeyValueSeedCtr(xml, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSDSAKeyValue: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSDSAKeyValue: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSRSAKeyValue.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSRSAKeyValue. If fails, throws ROAPParserException.
*/
SPtr<DSRSAKeyValue> ROAPParser::ParseDSRSAKeyValue(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSRSAKeyValue(ParseDSCryptoBinary(xml->GetChildElement("Modulus"), logger),
      ParseDSCryptoBinary(xml->GetChildElement("Exponent"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSRSAKeyValue: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSRSAKeyValue: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSTransform.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSTransform. If fails, throws ROAPParserException.
*/
SPtr<DSTransform> ROAPParser::ParseDSTransform(IXMLElement* xml, DRMLogger& logger) {
  //  TODO: XPath element.
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSTransform(ParseURIValue(xml->GetChildAttribute("", "Algorithm"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSTransform: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSTransform: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSTransforms.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSTransforms. If fails, throws ROAPParserException.
*/
SPtr<DSTransforms> ROAPParser::ParseDSTransforms(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSTransforms(ParseVector<DSTransform, DSTransform>(
      xml->GetOneOrMoreChildElementsByName("Transform"), ParseDSTransform, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSTransforms: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSTransforms: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSRetrievalMethod.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSRetrievalMethod. If fails, throws ROAPParserException.
*/
SPtr<DSRetrievalMethod> ROAPParser::ParseDSRetrievalMethod(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSRetrievalMethod(ParseDSTransforms(xml->GetChildElement("Transforms"), logger),
      ParseURIValue(xml->GetChildAttribute("", "URI"), logger),
      ParseURIValue(xml->GetChildAttribute("", "Type"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSRetrievalMethod: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSRetrievalMethod: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse BasicX509Data.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  BasicX509Data. If fails, throws ROAPParserException.
*/
SPtr<BasicX509Data> ROAPParser::ParseBasicX509Data(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetName() == "X509IssuerSerial") {
      return (BasicX509Data*)(ParseDSX509IssuerSerial(xml, logger));
    } else if (xml->GetName() == "X509SKI") {
      return (BasicX509Data*)(ParseDSX509SKI(xml, logger));
    } else if (xml->GetName() == "X509SubjectName") {
      return (BasicX509Data*)(ParseDSX509SubjectName(xml, logger));
    } else if (xml->GetName() == "X509Certificate") {
      return (BasicX509Data*)(ParseDSX509Certificate(xml, logger));
    } else if (xml->GetName() == "X509CRL") {
      return (BasicX509Data*)(ParseDSX509CRL(xml, logger));
    } else {
      return 0;
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseBasicX509Data: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseBasicX509Data: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSX509IssuerSerial.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSX509IssuerSerial. If fails, throws ROAPParserException.
*/
SPtr<DSX509IssuerSerial> ROAPParser::ParseDSX509IssuerSerial(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSX509IssuerSerial(xml->GetChildStrValue("X509IssuerName"),
      xml->GetChildIntValue("X509SerialNumber"));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSX509IssuerSerial: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSX509IssuerSerial: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSX509SKI.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSX509SKI. If fails, throws ROAPParserException.
*/
SPtr<DSX509SKI> ROAPParser::ParseDSX509SKI(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSX509SKI(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSX509SKI: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSX509SKI: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSX509SubjectName.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSX509SubjectName. If fails, throws ROAPParserException.
*/
SPtr<DSX509SubjectName> ROAPParser::ParseDSX509SubjectName(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSX509SubjectName(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSX509SubjectName: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSX509SubjectName: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSX509Certificate.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSX509Certificate. If fails, throws ROAPParserException.
*/
SPtr<DSX509Certificate> ROAPParser::ParseDSX509Certificate(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSX509Certificate(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSX509Certificate: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSX509Certificate: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSX509CRL.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSX509CRL. If fails, throws ROAPParserException.
*/
SPtr<DSX509CRL> ROAPParser::ParseDSX509CRL(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSX509CRL(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSX509CRL: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSX509CRL: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSX509Data.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSX509Data. If fails, throws ROAPParserException.
*/
SPtr<DSX509Data> ROAPParser::ParseDSX509Data(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSX509Data(ParseVector<BasicX509Data, BasicX509Data>(
      xml->GetOneOrMoreChildElements(), ParseBasicX509Data, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSX509Data: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSX509Data: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSPGPData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSPGPData. If fails, throws ROAPParserException.
*/
SPtr<DSPGPData> ROAPParser::ParseDSPGPData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("PGPKeyID") != 0) {
      if (xml->GetChildElement("PGPKeyPacket") != 0) {
        return new KeyPacketKeyIDDSPGPData(
          xml->GetChildElement("PGPKeyID")->GetStrValue(),
          xml->GetChildElement("PGPKeyPacket")->GetStrValue());
      } else {
        return new NKeyPacketKeyIDDSPGPData(
          xml->GetChildElement("PGPKeyID")->GetStrValue());
      }
    } else {
      if (xml->GetChildElement("PGPKeyPacket") != 0) {
        return new KeyPacketDSPGPData(
          xml->GetChildElement("PGPKeyPacket")->GetStrValue());
      } else {
        //  Error.
        throw ROAPParserException();
      }
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSPGPData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSPGPData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSSPKIData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSSPKIData. If fails, throws ROAPParserException.
*/
SPtr<DSSPKIData> ROAPParser::ParseDSSPKIData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    std::vector<IXMLElement*> elems = xml->GetOneOrMoreChildElementsByName("SPKISexp");
    std::vector<Base64StringT> sexps;
    for (unsigned int i = 0; i < elems.size(); i++) {
      sexps.push_back(elems[i]->GetStrValue());
    }
    return new DSSPKIData(sexps);
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSSPKIData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSSPKIData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSMgmtData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSMgmtData. If fails, throws ROAPParserException.
*/
SPtr<DSMgmtData> ROAPParser::ParseDSMgmtData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSMgmtData(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSMgmtData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSMgmtData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse BasicKeyInfo.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  BasicKeyInfo. If fails, throws ROAPParserException.
*/
SPtr<BasicKeyInfo> ROAPParser::ParseBasicKeyInfo(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetName() == "KeyName") {
      return (BasicKeyInfo*)(ParseDSKeyName(xml, logger));
    } else if (xml->GetName() == "DSAKeyValue") {
      return (BasicKeyInfo*)(ParseDSDSAKeyValue(xml, logger));
    } else if (xml->GetName() == "RSAKeyValue") {
      return (BasicKeyInfo*)(ParseDSRSAKeyValue(xml, logger));
    } else if (xml->GetName() == "RetrievalMethod") {
      return (BasicKeyInfo*)(ParseDSRetrievalMethod(xml, logger));
    } else if (xml->GetName() == "X509Data") {
      return (BasicKeyInfo*)(ParseDSX509Data(xml, logger));
    } else if (xml->GetName() == "PGPData") {
      return (BasicKeyInfo*)(ParseDSPGPData(xml, logger));
    } else if (xml->GetName() == "SPKIData") {
      return (BasicKeyInfo*)(ParseDSSPKIData(xml, logger));
    } else if (xml->GetName() == "MgmtData") {
      return (BasicKeyInfo*)(ParseDSMgmtData(xml, logger));
    } else {
      //  Error.
      throw ROAPParserException();
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseBasicKeyInfo: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseBasicKeyInfo: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSKeyInfo.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSKeyInfo. If fails, throws ROAPParserException.
*/
SPtr<DSKeyInfo> ROAPParser::ParseDSKeyInfo(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSKeyInfo(ParseVector<BasicKeyInfo, BasicKeyInfo>(
      xml->GetAllChildElements(), ParseBasicKeyInfo, logger),
      ParseIDValue(xml->GetChildAttribute("", "Id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSKeyInfo: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSKeyInfo: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSSignatureValue.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSSignatureValue. If fails, throws ROAPParserException.
*/
SPtr<DSSignatureValue> ROAPParser::ParseDSSignatureValue(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSSignatureValue(xml->GetStrValue(),
      ParseIDValue(xml->GetChildAttribute("", "Id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSSignatureValue: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSSignatureValue: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSDigestValue.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSDigestValue. If fails, throws ROAPParserException.
*/
SPtr<DSDigestValue> ROAPParser::ParseDSDigestValue(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSDigestValue(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSDigestValue: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSDigestValue: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSDigestMethod.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSDigestMethod. If fails, throws ROAPParserException.
*/
SPtr<DSDigestMethod> ROAPParser::ParseDSDigestMethod(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSDigestMethod(ParseURIValue(xml->GetChildAttribute("", "Algorithm"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSDigestMethod: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSDigestMethod: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSReference.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSReference. If fails, throws ROAPParserException.
*/
SPtr<DSReference> ROAPParser::ParseDSReference(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSReference(ParseDSTransforms(xml->GetChildElement("Transforms"), logger),
      ParseDSDigestMethod(xml->GetChildElement("DigestMethod"), logger),
      ParseDSDigestValue(xml->GetChildElement("DigestValue"), logger),
      ParseIDValue(xml->GetChildAttribute("", "Id"), logger),
      ParseURIValue(xml->GetChildAttribute("", "URI"), logger),
      ParseURIValue(xml->GetChildAttribute("", "Type"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSReference: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSReference: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSHMACOutputLength.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSHMACOutputLength. If fails, throws ROAPParserException.
*/
SPtr<DSHMACOutputLength> ROAPParser::ParseDSHMACOutputLength(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSHMACOutputLength(xml->GetIntValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSHMACOutputLength: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSHMACOutputLength: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSSignatureMethod.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSSignatureMethod. If fails, throws ROAPParserException.
*/
SPtr<DSSignatureMethod> ROAPParser::ParseDSSignatureMethod(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSSignatureMethod(ParseDSHMACOutputLength(
      xml->GetChildElement("HMACOutputLength"), logger),
      ParseURIValue(xml->GetChildAttribute("", "Algorithm"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSSignatureMethod: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSSignatureMethod: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSCanonicalizationMethod.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSCanonicalizationMethod. If fails, throws ROAPParserException.
*/
SPtr<DSCanonicalizationMethod> ROAPParser::ParseDSCanonicalizationMethod(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSCanonicalizationMethod(ParseURIValue(xml->GetChildAttribute("", "Algorithm"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSCanonicalizationMethod: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSCanonicalizationMethod: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSSignedInfo.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSSignedInfo. If fails, throws ROAPParserException.
*/
SPtr<DSSignedInfo> ROAPParser::ParseDSSignedInfo(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSSignedInfo(ParseDSCanonicalizationMethod(
      xml->GetChildElement("CanonicalizationMethod"), logger),
      ParseDSSignatureMethod(xml->GetChildElement("SignatureMethod"), logger),
      ParseVector<DSReference, DSReference>(
        xml->GetOneOrMoreChildElementsByName("Reference"), ParseDSReference, logger),
      ParseIDValue(xml->GetChildAttribute("", "Id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSSignedInfo: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSSignedInfo: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DSSignature.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DSSignature. If fails, throws ROAPParserException.
*/
SPtr<DSSignature> ROAPParser::ParseDSSignature(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DSSignature(ParseDSSignedInfo(xml->GetChildElement("SignedInfo"), logger),
      ParseDSSignatureValue(xml->GetChildElement("SignatureValue"), logger),
      ParseDSKeyInfo(xml->GetChildElement("KeyInfo"), logger),
      ParseVector<DSObject, DSObject>(
        xml->GetChildElementsByName("Object"), ParseDSObject, logger),
      ParseIDValue(xml->GetChildAttribute("", "Id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDSSignature: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDSSignature: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse XencKeySize.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  XencKeySize. If fails, throws ROAPParserException.
*/
SPtr<XencKeySize> ROAPParser::ParseXencKeySize(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new XencKeySize(xml->GetIntValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseXencKeySize: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseXencKeySize: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse XencEncryptionMethod.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  XencEncryptionMethod. If fails, throws ROAPParserException.
*/
SPtr<XencEncryptionMethod> ROAPParser::ParseXencEncryptionMethod(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("OAEPparams") != 0) {
      return new OAEPXencEncryptionMethod(
        ParseXencKeySize(xml->GetChildElement("KeySize"), logger),
        xml->GetChildElement("OAEPparams")->GetStrValue(),
        ParseURIValue(xml->GetChildAttribute("", "Algorithm"), logger));
    } else {
      return new NOAEPXencEncryptionMethod(
        ParseXencKeySize(xml->GetChildElement("KeySize"), logger),
        ParseURIValue(xml->GetChildAttribute("", "Algorithm"), logger));
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseXencEncryptionMethod: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseXencEncryptionMethod: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse XencCipherData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  XencCipherData. If fails, throws ROAPParserException.
*/
SPtr<XencCipherData> ROAPParser::ParseXencCipherData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("CipherValue") != 0) {
      return (XencCipherData*)(ParseCValueXencCipherData(xml->GetChildElement("CipherValue"), logger));
    } else if (xml->GetChildElement("CipherReference") != 0) {
      return (XencCipherData*)(ParseCRefXencCipherData(xml->GetChildElement("CipherReference"), logger));
    } else {
      //  Error.
      throw ROAPParserException();
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseXencCipherData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseXencCipherData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse CValueXencCipherData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  CValueXencCipherData. If fails, throws ROAPParserException.
*/
SPtr<CValueXencCipherData> ROAPParser::ParseCValueXencCipherData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new CValueXencCipherData(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseCValueXencCipherData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseCValueXencCipherData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse XencTransforms.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  XencTransforms. If fails, throws ROAPParserException.
*/
SPtr<XencTransforms> ROAPParser::ParseXencTransforms(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new XencTransforms(ParseVector<DSTransform, DSTransform>(
      xml->GetOneOrMoreChildElementsByName("Transform"), ParseDSTransform, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseXencTransforms: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseXencTransforms: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse XencCipherReference.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  XencCipherReference. If fails, throws ROAPParserException.
*/
SPtr<XencCipherReference> ROAPParser::ParseXencCipherReference(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new XencCipherReference(ParseXencTransforms(xml->GetChildElement("Transforms"), logger),
      ParseURIValue(xml->GetChildAttribute("", "URI"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseXencCipherReference: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseXencCipherReference: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse CRefXencCipherData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  CRefXencCipherData. If fails, throws ROAPParserException.
*/
SPtr<CRefXencCipherData> ROAPParser::ParseCRefXencCipherData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new CRefXencCipherData(ParseXencCipherReference(xml, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseCRefXencCipherData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseCRefXencCipherData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse XencEncryptionProperty.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  XencEncryptionProperty. If fails, throws ROAPParserException.
*/
SPtr<XencEncryptionProperty> ROAPParser::ParseXencEncryptionProperty(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new XencEncryptionProperty(ParseURIValue(xml->GetChildAttribute("", "Target"), logger),
      ParseIDValue(xml->GetChildAttribute("", "Id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseXencEncryptionProperty: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseXencEncryptionProperty: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse XencEncryptionProperties.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  XencEncryptionProperties. If fails, throws ROAPParserException.
*/
SPtr<XencEncryptionProperties> ROAPParser::ParseXencEncryptionProperties(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new XencEncryptionProperties(ParseVector<XencEncryptionProperty, XencEncryptionProperty>(
      xml->GetOneOrMoreChildElementsByName("EncryptionProperty"), ParseXencEncryptionProperty, logger),
      ParseIDValue(xml->GetChildAttribute("", "Id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseXencEncryptionProperties: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseXencEncryptionProperties: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse XencEncryptedTypeMime.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  XencEncryptedTypeMime. If fails, throws ROAPParserException.
*/
SPtr<XencEncryptedTypeMime> ROAPParser::ParseXencEncryptedTypeMime(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new XencEncryptedTypeMime(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseXencEncryptedTypeMime: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseXencEncryptedTypeMime: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DataXencReferenceType.

    \param  xml       input, XML element.

    \returns  DataXencReferenceType. If fails, throws ROAPParserException.
*/
SPtr<DataXencReferenceType> ROAPParser::ParseDataXencReferenceType(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DataXencReferenceType(ParseURIValue(xml->GetChildAttribute("", "URI"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDataXencReferenceType: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDataXencReferenceType: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse KeyXencReferenceType.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  KeyXencReferenceType. If fails, throws ROAPParserException.
*/
SPtr<KeyXencReferenceType> ROAPParser::ParseKeyXencReferenceType(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new KeyXencReferenceType(ParseURIValue(xml->GetChildAttribute("", "URI"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseKeyXencReferenceType: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseKeyXencReferenceType: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse XencReferenceList.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  XencReferenceList. If fails, throws ROAPParserException.
*/
SPtr<XencReferenceList> ROAPParser::ParseXencReferenceList(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    std::vector<IXMLElement*> dataelems = xml->GetChildElementsByName("DataReference");
    std::vector<IXMLElement*> keyelems = xml->GetChildElementsByName("KeyReference");
    if ((dataelems.size() + keyelems.size()) == 0) {
      //  Error.
      throw ROAPParserException();
    }
    return new XencReferenceList(ParseVector<DataXencReferenceType, DataXencReferenceType>(
      dataelems, ParseDataXencReferenceType, logger),
      ParseVector<KeyXencReferenceType, KeyXencReferenceType>(keyelems,
      ParseKeyXencReferenceType, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseXencReferenceList: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseXencReferenceList: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse NameXencEncryptedKeyData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  NameXencEncryptedKeyData. If fails, throws ROAPParserException.
*/
SPtr<NameXencEncryptedKeyData> ROAPParser::ParseNameXencEncryptedKeyData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new NameXencEncryptedKeyData(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseNameXencEncryptedKeyData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseNameXencEncryptedKeyData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RecXencEncryptedKeyData.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  RecXencEncryptedKeyData. If fails, throws ROAPParserException.
*/
SPtr<RecXencEncryptedKeyData> ROAPParser::ParseRecXencEncryptedKeyData(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new RecXencEncryptedKeyData(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRecXencEncryptedKeyData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRecXencEncryptedKeyData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse XencEncryptedKey.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  XencEncryptedKey. If fails, throws ROAPParserException.
*/
SPtr<XencEncryptedKey> ROAPParser::ParseXencEncryptedKey(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new XencEncryptedKey(ParseXencEncryptionMethod(
      xml->GetChildElement("EncryptionMethod"), logger),
      ParseDSKeyInfo(xml->GetChildElement("KeyInfo"), logger),
      ParseXencCipherData(xml->GetChildElement("CipherData"), logger),
      ParseXencEncryptionProperties(xml->GetChildElement("EncryptionProperties"), logger),
      ParseIDValue(xml->GetChildAttribute("", "Id"), logger),
      ParseURIValue(xml->GetChildAttribute("", "Type"), logger),
      ParseXencEncryptedTypeMime(xml->GetChildAttribute("", "MimeType"), logger),
      ParseURIValue(xml->GetChildAttribute("", "Encoding"), logger),
      ParseXencReferenceList(xml->GetChildElement("ReferenceList"), logger),
      ParseNameXencEncryptedKeyData(xml->GetChildElement("CarriedKeyName"), logger),
      ParseRecXencEncryptedKeyData(xml->GetChildAttribute("", "Recipient"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseXencEncryptedKey: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseXencEncryptedKey: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPVersion.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROAPVersion. If fails, throws ROAPParserException.
*/
SPtr<ROAPVersion> ROAPParser::ParseROAPVersion(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPVersion(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPVersion: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPVersion: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPVersion.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  ROAPVersion. If fails, throws ROAPParserException.
*/
SPtr<ROAPVersion> ROAPParser::ParseROAPVersion(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPVersion(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPVersion: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPVersion: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPNonce.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROAPNonce. If fails, throws ROAPParserException.
*/
SPtr<ROAPNonce> ROAPParser::ParseROAPNonce(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPNonce(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPNonce: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPNonce: GC error...");
    throw ROAPParserException();
  }
  //  This is to avoid nonce length checking here.
  catch (ROAPException) {
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPNonce.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  ROAPNonce. If fails, throws ROAPParserException.
*/
SPtr<ROAPNonce> ROAPParser::ParseROAPNonce(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPNonce(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPNonce: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPNonce: GC error...");
    throw ROAPParserException();
  }
  //  This is to avoid nonce length checking here.
  catch (ROAPException) {
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPStatus.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  ROAPStatus. If fails, throws ROAPParserException.
*/
SPtr<ROAPStatus> ROAPParser::ParseROAPStatus(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetStrValue() == "Success") {
      return new SuccessROAPStatus();
    } else {
      return (ROAPStatus*)(ParseUnsuccessROAPStatus(xml, logger));
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPStatus: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPStatus: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse UnsuccessROAPStatus.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  UnsuccessROAPStatus. If fails, throws ROAPParserException.
*/
SPtr<UnsuccessROAPStatus> ROAPParser::ParseUnsuccessROAPStatus(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetStrValue() == "Abort") {
      return new AbortROAPStatus();
    } else if (xml->GetStrValue() == "NotSupported") {
      return new NotSupportedROAPStatus();
    } else if (xml->GetStrValue() == "AccessDenied") {
      return new AccessDeniedROAPStatus();
    } else if (xml->GetStrValue() == "NotFound") {
      return new NotFoundROAPStatus();
    } else if (xml->GetStrValue() == "MalformedRequest") {
      return new MalformedRequestROAPStatus();
    } else if (xml->GetStrValue() == "UnknownCriticalExtension") {
      return new UnknownCriticalExtensionROAPStatus();
    } else if (xml->GetStrValue() == "UnsupportedVersion") {
      return new UnsupportedVersionROAPStatus();
    } else if (xml->GetStrValue() == "UnsupportedAlgorithm") {
      return new UnsupportedAlgorithmROAPStatus();
    } else if (xml->GetStrValue() == "NoCertificateChain") {
      return new NoCertificateChainROAPStatus();
    } else if (xml->GetStrValue() == "InvalidCertificateChain") {
      return new InvalidCertificateChainROAPStatus();
    } else if (xml->GetStrValue() == "TrustedRootCertificateNotPresent") {
      return new TrustedRootCertificateNotPresentROAPStatus();
    } else if (xml->GetStrValue() == "SignatureError") {
      return new SignatureErrorROAPStatus();
    } else if (xml->GetStrValue() == "DeviceTimeError") {
      return new DeviceTimeErrorROAPStatus();
    } else if (xml->GetStrValue() == "InvalidDCFHash") {
      return new InvalidDCFHashROAPStatus();
    } else if (xml->GetStrValue() == "InvalidDomain") {
      return new InvalidDomainROAPStatus();
    } else if (xml->GetStrValue() == "DomainFull") {
      return new DomainFullROAPStatus();
    } else {
      //  Error.
      throw ROAPParserException();
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessROAPStatus: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessROAPStatus: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse NoOCSPResponseExtension.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  NoOCSPResponseExtension. If fails, throws ROAPParserException.
*/
SPtr<NoOCSPResponseExtension> ROAPParser::ParseNoOCSPResponseExtension(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttribute("", "xsi:type") == 0) {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrStrValue("", "xsi:type") != "roap:NoOCSPResponse") {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrBoolValue("", "critical") == true) {
      return new CriticalNoOCSPResponseExtension();
    }
    return new NoOCSPResponseExtension();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseNoOCSPResponseExtension: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseNoOCSPResponseExtension: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPKeyIdentifier.

    \param  xml       input, XML element.

    \returns  ROAPKeyIdentifier. If fails, throws ROAPParserException.
*/
SPtr<ROAPKeyIdentifier> ROAPParser::ParseROAPKeyIdentifier(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttrStrValue("", "xsi:type") == "roap:X509SPKIHash") {
      return new X509SPKIHash(xml->GetChildElement("hash")->GetStrValue());
    } else {
      //  Error.
      throw ROAPParserException();
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPKeyIdentifier: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPKeyIdentifier: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse PeerKeyIdExtension.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  PeerKeyIdExtension. If fails, throws ROAPParserException.
*/
SPtr<PeerKeyIdExtension> ROAPParser::ParsePeerKeyIdExtension(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttribute("", "xsi:type") == 0) {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrStrValue("", "xsi:type") != "roap:PeerKeyIdentifier") {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrBoolValue("", "critical") == true) {
      return new CriticalPeerKeyIdExtension(ParseROAPKeyIdentifier(
        xml->GetChildElement("identifier"), logger));
    }
    return new PeerKeyIdExtension(ParseROAPKeyIdentifier(
        xml->GetChildElement("identifier"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParsePeerKeyIdExtension: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParsePeerKeyIdExtension: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OCSPResponderKeyIdExtension.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  OCSPResponderKeyIdExtension. If fails, throws ROAPParserException.
*/
SPtr<OCSPResponderKeyIdExtension> ROAPParser::ParseOCSPResponderKeyIdExtension(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttribute("", "xsi:type") == 0) {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrStrValue("", "xsi:type") != "roap:OCSPResponderKeyIdentifier") {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrBoolValue("", "critical") == true) {
      return new CriticalOCSPResponderKeyIdExtension(ParseROAPKeyIdentifier(
        xml->GetChildElement("identifier"), logger));
    }
    return new OCSPResponderKeyIdExtension(ParseROAPKeyIdentifier(
        xml->GetChildElement("identifier"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOCSPResponderKeyIdExtension: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOCSPResponderKeyIdExtension: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DeviceDetailsData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DeviceDetailsData. If fails, throws ROAPParserException.
*/
SPtr<DeviceDetailsData> ROAPParser::ParseDeviceDetailsData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  if ((xml->GetChildElement("manufacturer") == 0) ||
      (xml->GetChildElement("model") == 0) ||
      (xml->GetChildElement("version") == 0)) {
    return 0;
  }
  try {
    return new DeviceDetailsData(xml->GetChildElement("manufacturer")->GetStrValue(),
      xml->GetChildElement("model")->GetStrValue(),
      xml->GetChildElement("version")->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDeviceDetailsData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDeviceDetailsData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DeviceDetailsExtension.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DeviceDetailsExtension. If fails, throws ROAPParserException.
*/
SPtr<DeviceDetailsExtension> ROAPParser::ParseDeviceDetailsExtension(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttribute("", "xsi:type") == 0) {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrStrValue("", "xsi:type") != "roap:DeviceDetails") {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrBoolValue("", "critical") == true) {
      return new CriticalDeviceDetailsExtension(ParseDeviceDetailsData(xml, logger));
    }
    return new DeviceDetailsExtension(ParseDeviceDetailsData(xml, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDeviceDetailsExtension: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDeviceDetailsExtension: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse TransIdentifierData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  TransIdentifierData. If fails, throws ROAPParserException.
*/
SPtr<TransIdentifierData> ROAPParser::ParseTransIdentifierData(IXMLElement* xml, DRMLogger& logger) {
  return 0;
}

/*! \brief  Parse TransactionIdExtension.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  TransactionIdExtension. If fails, throws ROAPParserException.
*/
SPtr<TransactionIdExtension> ROAPParser::ParseTransactionIdExtension(IXMLElement* xml, DRMLogger& logger) {
  return 0;
}

/*! \brief  Parse CertCachingExtension.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  CertCachingExtension. If fails, throws ROAPParserException.
*/
SPtr<CertCachingExtension> ROAPParser::ParseCertCachingExtension(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttribute("", "xsi:type") == 0) {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrStrValue("", "xsi:type") != "roap:CertificateCaching") {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrBoolValue("", "critical") == true) {
      return new CriticalCertCachingExtension();
    }
    return new CertCachingExtension();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseCertCachingExtension: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseCertCachingExtension: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse HashChainSupportExtension.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  HashChainSupportExtension. If fails, throws ROAPParserException.
*/
SPtr<HashChainSupportExtension> ROAPParser::ParseHashChainSupportExtension(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttribute("", "xsi:type") == 0) {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrStrValue("", "xsi:type") != "roap:HashChainSupport") {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrBoolValue("", "critical") == true) {
      return new CriticalHashChainSupportExtension();
    }
    return new HashChainSupportExtension();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseHashChainSupportExtension: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseHashChainSupportExtension: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse NotDomainMemberExtension.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  NotDomainMemberExtension. If fails, throws ROAPParserException.
*/
SPtr<NotDomainMemberExtension> ROAPParser::ParseNotDomainMemberExtension(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttribute("", "xsi:type") == 0) {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrStrValue("", "xsi:type") != "roap:NotDomainMember") {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrBoolValue("", "critical") == true) {
      return new CriticalNotDomainMemberExtension();
    }
    return new NotDomainMemberExtension();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseNotDomainMemberExtension: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseNotDomainMemberExtension: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DomainNameWhiteListExtension.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DomainNameWhiteListExtension. If fails, throws ROAPParserException.
*/
SPtr<DomainNameWhiteListExtension> ROAPParser::ParseDomainNameWhiteListExtension(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttribute("", "xsi:type") == 0) {
      throw ROAPParserException();
    }
    if (xml->GetChildAttrStrValue("", "xsi:type") != "roap:DomainNameWhiteList") {
      throw ROAPParserException();
    }
    std::vector<std::string> dnames;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("dn");
    if ((elems.size() == 0) || (elems.size() > 5)) {
      throw ROAPParserException();
    }
    for (unsigned int i = 0; i < elems.size(); i++) {
      dnames.push_back(elems[i]->GetStrValue());
    }
    if (xml->GetChildAttrBoolValue("", "critical") == true) {
      return new CriticalDomainNameWhiteListExtension(dnames);
    }
    return new DomainNameWhiteListExtension(dnames);
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDomainNameWhiteListExtension: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDomainNameWhiteListExtension: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPIdentifier.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROAPIdentifier. If fails, throws ROAPParserException.
*/
SPtr<ROAPIdentifier> ROAPParser::ParseROAPIdentifier(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPIdentifier(ParseROAPKeyIdentifier(xml->GetChildElement("keyIdentifier"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPIdentifier: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPIdentifier: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPDomainIdentifier.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROAPDomainIdentifier. If fails, throws ROAPParserException.
*/
SPtr<ROAPDomainIdentifier> ROAPParser::ParseROAPDomainIdentifier(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPDomainIdentifier(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPDomainIdentifier: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPDomainIdentifier: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DefDateTime.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DefDateTime. If fails, throws ROAPParserException.
*/
SPtr<DefDateTime> ROAPParser::ParseDefDateTime(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
//    return new DefDateTime(UTCTime(xml->GetStrValue()));
    return new DefDateTime(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDefDateTime: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDefDateTime: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DefDateTime or UndefDateTime.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DefDateTime or UndefDateTime. If fails, throws ROAPParserException.
*/
SPtr<DateTime> ROAPParser::ParseDefOrUndefDateTime(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetStrValue() == "Undefined") {
      return new UndefDateTime();
    }
    return (DateTime*)(ParseDefDateTime(xml, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDefOrUndefDateTime: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDefOrUndefDateTime: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DefDateTime or InfDateTime.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DefDateTime or InfDateTime. If fails, throws ROAPParserException.
*/
SPtr<DateTime> ROAPParser::ParseDefOrInfDateTime(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetStrValue() == "Infinite") {
      return new InfDateTime();
    }
    return (DateTime*)(ParseDefDateTime(xml, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDefOrInfDateTime: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDefOrInfDateTime: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPROPayloadStatefulInfo.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  ROAPROPayloadStatefulInfo. If fails, throws ROAPParserException.
*/
SPtr<ROAPROPayloadStatefulInfo> ROAPParser::ParseROAPROPayloadStatefulInfo(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPROPayloadStatefulInfo(xml->GetBoolValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPROPayloadStatefulInfo: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPROPayloadStatefulInfo: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPROPayloadRIURLInfo.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  ROAPROPayloadRIURLInfo. If fails, throws ROAPParserException.
*/
SPtr<ROAPROPayloadRIURLInfo> ROAPParser::ParseROAPROPayloadRIURLInfo(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPROPayloadRIURLInfo(ParseURIValue(xml, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPROPayloadRIURLInfo: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPROPayloadRIURLInfo: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPROPayload.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROAPROPayload. If fails, throws ROAPParserException.
*/
SPtr<ROAPROPayload> ROAPParser::ParseROAPROPayload(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildAttribute("", "domainRO") == 0) {
      return (ROAPROPayload*)(ParseDeviceROAPROPayload(xml, logger));
    }
    if (xml->GetChildAttrBoolValue("", "domainRO") == false) {
      return (ROAPROPayload*)(ParseDeviceROAPROPayload(xml, logger));
    } else {
      return (ROAPROPayload*)(ParseDomainROAPROPayload(xml, logger));
    }
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPROPayload: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPROPayload: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DomainROAPROPayload.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DomainROAPROPayload. If fails, throws ROAPParserException.
*/
SPtr<DomainROAPROPayload> ROAPParser::ParseDomainROAPROPayload(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DomainROAPROPayload(ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseOEXRights(xml->GetChildElement("rights"), logger),
      ParseDSSignature(xml->GetChildElement("signature"), logger),
      ParseDefDateTime(xml->GetChildElement("timeStamp"), logger),
      ParseXencEncryptedKey(xml->GetChildElement("encKey"), logger),
      ParseROAPVersion(xml->GetChildAttribute("", "version"), logger),
      ParseIDValue(xml->GetChildAttribute("", "id"), logger),
      ParseROAPROPayloadStatefulInfo(xml->GetChildAttribute("", "stateful"), logger),
      ParseROAPROPayloadRIURLInfo(xml->GetChildAttribute("", "riURL"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDomainROAPROPayload: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDomainROAPROPayload: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DeviceROAPROPayload.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DeviceROAPROPayload. If fails, throws ROAPParserException.
*/
SPtr<DeviceROAPROPayload> ROAPParser::ParseDeviceROAPROPayload(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DeviceROAPROPayload(ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseOEXRights(xml->GetChildElement("rights"), logger),
      ParseDSSignature(xml->GetChildElement("signature"), logger),
      ParseDefDateTime(xml->GetChildElement("timeStamp"), logger),
      ParseXencEncryptedKey(xml->GetChildElement("encKey"), logger),
      ParseROAPVersion(xml->GetChildAttribute("", "version"), logger),
      ParseIDValue(xml->GetChildAttribute("", "id"), logger),
      ParseROAPROPayloadStatefulInfo(xml->GetChildAttribute("", "stateful"), logger),
      ParseROAPROPayloadRIURLInfo(xml->GetChildAttribute("", "riURL"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDeviceROAPROPayload: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDeviceROAPROPayload: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPProtectedRO.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROAPProtectedRO. If fails, throws ROAPParserException.
*/
SPtr<ROAPProtectedRO> ROAPParser::ParseROAPProtectedRO(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPProtectedRO(ParseROAPROPayload(xml->GetChildElement("ro"), logger),
      ParseDSSignature(xml->GetChildElement("mac"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPProtectedRO: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPProtectedRO: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPServerInfo.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROAPServerInfo. If fails, throws ROAPParserException.
*/
SPtr<ROAPServerInfo> ROAPParser::ParseROAPServerInfo(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPServerInfo(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPServerInfo: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPServerInfo: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPSessionID.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  ROAPSessionID. If fails, throws ROAPParserException.
*/
SPtr<ROAPSessionID> ROAPParser::ParseROAPSessionID(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPSessionID(xml->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPSessionID: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPSessionID: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPKeyIdentifiers.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROAPKeyIdentifiers. If fails, throws ROAPParserException.
*/
SPtr<ROAPKeyIdentifiers> ROAPParser::ParseROAPKeyIdentifiers(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPKeyIdentifiers(ParseVector<ROAPKeyIdentifier, ROAPKeyIdentifier>(
      xml->GetChildElementsByName("keyIdentifier"), ParseROAPKeyIdentifier, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPKeyIdentifiers: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPKeyIdentifiers: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPCertificateChain.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROAPCertificateChain. If fails, throws ROAPParserException.
*/
SPtr<ROAPCertificateChain> ROAPParser::ParseROAPCertificateChain(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    std::vector<Base64StringT> certs;
    std::vector<IXMLElement*> elems = xml->GetOneOrMoreChildElementsByName("certificate");
    for (unsigned int i = 0; i < elems.size(); i++) {
      certs.push_back(elems[i]->GetStrValue());
    }
    return new ROAPCertificateChain(certs);
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPCertificateChain: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPCertificateChain: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DeviceHelloExtensions.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DeviceHelloExtensions. If fails, throws ROAPParserException.
*/
SPtr<DeviceHelloExtensions> ROAPParser::ParseDeviceHelloExtensions(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DeviceHelloExtensions(ParseCertCachingExtension(
      xml->GetChildElement("extension"), logger));
  }
  catch (ROAPException) {
    logger.UpdateLog("ROAPParser::ParseDeviceHelloExtensions: ROAP error...");
    throw ROAPParserException();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDeviceHelloExtensions: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDeviceHelloExtensions: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DeviceHelloRequest.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DeviceHelloRequest. If fails, throws ROAPParserException.
*/
SPtr<DeviceHelloRequest> ROAPParser::ParseDeviceHelloRequest(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DeviceHelloRequest(ParseROAPNonce(xml->GetChildAttribute("", "triggerNonce"), logger),
      ParseROAPVersion(xml->GetChildElement("version"), logger),
      ParseVector<ROAPIdentifier, ROAPIdentifier>(xml->GetChildElementsByName("deviceID"),
      ParseROAPIdentifier, logger),
      ParseVector<URIValue, URIValue>(xml->GetChildElementsByName("supportedAlgorithm"),
      ParseURIValue, logger),
      ParseDeviceHelloExtensions(xml->GetChildElement("extensions"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDeviceHelloRequest: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDeviceHelloRequest: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RIHelloExtensions.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  RIHelloExtensions. If fails, throws ROAPParserException.
*/
SPtr<RIHelloExtensions> ROAPParser::ParseRIHelloExtensions(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    SPtr<PeerKeyIdExtension> peerKeyId;
    SPtr<CertCachingExtension> caching;
    SPtr<DeviceDetailsExtension> details;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("extension");
    for (unsigned int i = 0; i < elems.size(); i++) {
      if (elems[i]->GetChildAttribute("", "xsi:type") == 0) {
        throw ROAPParserException();
      }
      if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:PeerKeyIdentifier") {
        peerKeyId = ParsePeerKeyIdExtension(elems[i], logger);
      } else if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:CertificateCaching") {
        caching = ParseCertCachingExtension(elems[i], logger);
      } else if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:DeviceDetails") {
        details = ParseDeviceDetailsExtension(elems[i], logger);
      } else {
        throw ROAPParserException();
      }
    }
    return new RIHelloExtensions(peerKeyId, caching, details);
  }
  catch (ROAPException) {
    logger.UpdateLog("ROAPParser::ParseRIHelloExtensions: ROAP error...");
    throw ROAPParserException();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRIHelloExtensions: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRIHelloExtensions: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse SuccessRIHello.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  SuccessRIHello. If fails, throws ROAPParserException.
*/
SPtr<SuccessRIHello> ROAPParser::ParseSuccessRIHello(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new SuccessRIHello(ParseROAPVersion(xml->GetChildElement("selectedVersion"), logger),
      ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseVector<URIValue, URIValue>(xml->GetChildElementsByName("selectedAlgorithm"),
      ParseURIValue, logger),
      ParseROAPNonce(xml->GetChildElement("riNonce"), logger),
      ParseROAPKeyIdentifiers(xml->GetChildElement("trustedAuthorities"), logger),
      ParseROAPServerInfo(xml->GetChildElement("serverInfo"), logger),
      ParseRIHelloExtensions(xml->GetChildElement("extensions"), logger),
      ParseROAPSessionID(xml->GetChildAttribute("", "sessionId"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseSuccessRIHello: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseSuccessRIHello: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse UnsuccessRIHello.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  UnsuccessRIHello. If fails, throws ROAPParserException.
*/
SPtr<UnsuccessRIHello> ROAPParser::ParseUnsuccessRIHello(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new UnsuccessRIHello(
      ParseUnsuccessROAPStatus(xml->GetChildAttribute("", "status"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessRIHello: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessRIHello: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RegRequestExtensions.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  RegRequestExtensions. If fails, throws ROAPParserException.
*/
SPtr<RegRequestExtensions> ROAPParser::ParseRegRequestExtensions(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    SPtr<PeerKeyIdExtension> peerKeyId;
    SPtr<DeviceDetailsExtension> details;
    SPtr<NoOCSPResponseExtension> noOCSP;
    SPtr<OCSPResponderKeyIdExtension> ocspResponderKeyId;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("extension");
    for (unsigned int i = 0; i < elems.size(); i++) {
      if (elems[i]->GetChildAttribute("", "xsi:type") == 0) {
        throw ROAPParserException();
      }
      if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:PeerKeyIdentifier") {
        peerKeyId = ParsePeerKeyIdExtension(elems[i], logger);
      } else if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:NoOCSPResponse") {
        noOCSP = ParseNoOCSPResponseExtension(elems[i], logger);
      } else if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:DeviceDetails") {
        details = ParseDeviceDetailsExtension(elems[i], logger);
      } else if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:OCSPResponderKeyIdentifier") {
        ocspResponderKeyId = ParseOCSPResponderKeyIdExtension(elems[i], logger);
      } else {
        throw ROAPParserException();
      }
    }
    return new RegRequestExtensions(peerKeyId, details, noOCSP, ocspResponderKeyId);
  }
  catch (ROAPException) {
    logger.UpdateLog("ROAPParser::ParseRegRequestExtensions: ROAP error...");
    throw ROAPParserException();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRegRequestExtensions: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRegRequestExtensions: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RegRequest.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  RegRequest. If fails, throws ROAPParserException.
*/
SPtr<RegRequest> ROAPParser::ParseRegRequest(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("signature") == 0) {
      throw ROAPParserException();
    }
    return new RegRequest(ParseROAPNonce(xml->GetChildAttribute("", "triggerNonce"), logger),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger),
      ParseDefOrUndefDateTime(xml->GetChildElement("time"), logger),
      ParseROAPCertificateChain(xml->GetChildElement("certificateChain"), logger),
      ParseROAPKeyIdentifiers(xml->GetChildElement("trustedAuthorities"), logger),
      ParseROAPServerInfo(xml->GetChildElement("serverInfo"), logger),
      ParseRegRequestExtensions(xml->GetChildElement("extensions"), logger),
      xml->GetChildElement("signature")->GetStrValue(),
      ParseROAPSessionID(xml->GetChildAttribute("", "sessionId"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRegRequest: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRegRequest: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RegResponseExtensions.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  RegResponseExtensions. If fails, throws ROAPParserException.
*/
SPtr<RegResponseExtensions> ROAPParser::ParseRegResponseExtensions(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    SPtr<DomainNameWhiteListExtension> whitelist;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("extension");
    for (unsigned int i = 0; i < elems.size(); i++) {
      if (elems[i]->GetChildAttribute("", "xsi:type") == 0) {
        throw ROAPParserException();
      }
      if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:DomainNameWhiteList") {
        whitelist = ParseDomainNameWhiteListExtension(elems[i], logger);
      } else {
        throw ROAPParserException();
      }
    }
    return new RegResponseExtensions(whitelist);
  }
  catch (ROAPException) {
    logger.UpdateLog("ROAPParser::ParseRegResponseExtensions: ROAP error...");
    throw ROAPParserException();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRegResponseExtensions: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRegResponseExtensions: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse SuccessRegResponse.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  SuccessRegResponse. If fails, throws ROAPParserException.
*/
SPtr<SuccessRegResponse> ROAPParser::ParseSuccessRegResponse(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("signature") == 0) {
      throw ROAPParserException();
    }
    std::vector<Base64StringT> ocsps;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("ocspResponse");
    for (unsigned int i = 0; i < elems.size(); i++) {
      ocsps.push_back(elems[i]->GetStrValue());
    }
    return new SuccessRegResponse(ParseURIValue(xml->GetChildElement("riURL"), logger),
      ParseROAPCertificateChain(xml->GetChildElement("certificateChain"), logger),
      ocsps,
      ParseRegResponseExtensions(xml->GetChildElement("extensions"), logger),
      xml->GetChildElement("signature")->GetStrValue(),
      ParseROAPSessionID(xml->GetChildAttribute("", "sessionId"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseSuccessRegResponse: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseSuccessRegResponse: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse UnsuccessRegResponse.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  UnsuccessRegResponse. If fails, throws ROAPParserException.
*/
SPtr<UnsuccessRegResponse> ROAPParser::ParseUnsuccessRegResponse(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new UnsuccessRegResponse(
      ParseUnsuccessROAPStatus(xml->GetChildAttribute("", "status"), logger),
      ParseROAPSessionID(xml->GetChildAttribute("", "sessionId"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessRegResponse: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessRegResponse: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DCFHash.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DCFHash. If fails, throws ROAPParserException.
*/
SPtr<DCFHash> ROAPParser::ParseDCFHash(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("hash") == 0) {
      throw ROAPParserException();
    }
    return new DCFHash(xml->GetChildElement("hash")->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDCFHash: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDCFHash: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROInfo.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROInfo. If fails, throws ROAPParserException.
*/
SPtr<ROInfo> ROAPParser::ParseROInfo(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    std::vector<NZSPtr<ROInfoData> > datas;
    IXMLElement* roid = xml->GetFirstChild();
    if (roid == 0) {
      throw ROAPParserException();
    }
    //  Must be roID.
    if (roid->GetName() != "roID") {
      throw ROAPParserException();
    }
    IXMLElement* next = roid->GetFirstSibling();
    while (next != 0) {
      if (next->GetName() == "roID") {
        datas.push_back(new ROInfoData(ParseIDValue(roid, logger), 0));
        roid = next;
        next = roid->GetFirstSibling();
      } else if (next->GetName() == "dcfHash") {
        datas.push_back(new ROInfoData(ParseIDValue(roid, logger), ParseDCFHash(next, logger)));
        roid = next->GetFirstSibling();
        if (roid != 0) {
          if (roid->GetName() != "roID") {
            throw ROAPParserException();
          }
          next = roid->GetFirstSibling();
        } else {
          next = 0;
        }
      } else {
        throw ROAPParserException();
      }
    }
    if (roid != 0) {
      datas.push_back(new ROInfoData(ParseIDValue(roid, logger), 0));
    }
    return new ROInfo(datas);
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROInfo: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROInfo: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RORequestExtensions.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  RORequestExtensions. If fails, throws ROAPParserException.
*/
SPtr<RORequestExtensions> ROAPParser::ParseRORequestExtensions(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    SPtr<PeerKeyIdExtension> peerKeyId;
    SPtr<NoOCSPResponseExtension> noOCSP;
    SPtr<OCSPResponderKeyIdExtension> ocspResponderKeyId;
    SPtr<TransactionIdExtension> transactionId;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("extension");
    for (unsigned int i = 0; i < elems.size(); i++) {
      if (elems[i]->GetChildAttribute("", "xsi:type") == 0) {
        throw ROAPParserException();
      }
      if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:PeerKeyIdentifier") {
        peerKeyId = ParsePeerKeyIdExtension(elems[i], logger);
      } else if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:NoOCSPResponse") {
        noOCSP = ParseNoOCSPResponseExtension(elems[i], logger);
      } else if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:OCSPResponderKeyIdentifier") {
        ocspResponderKeyId = ParseOCSPResponderKeyIdExtension(elems[i], logger);
      } else if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:TransactionIdentifier") {
        transactionId = ParseTransactionIdExtension(elems[i], logger);
      } else {
        throw ROAPParserException();
      }
    }
    return new RORequestExtensions(peerKeyId, noOCSP, ocspResponderKeyId, transactionId);
  }
  catch (ROAPException) {
    logger.UpdateLog("ROAPParser::ParseRORequestExtensions: ROAP error...");
    throw ROAPParserException();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRORequestExtensions: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRORequestExtensions: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RORequest.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  RORequest. If fails, throws ROAPParserException.
*/
SPtr<RORequest> ROAPParser::ParseRORequest(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("signature") == 0) {
      throw ROAPParserException();
    }
    return new RORequest(ParseROAPNonce(xml->GetChildAttribute("", "triggerNonce"), logger),
      ParseROAPIdentifier(xml->GetChildElement("deviceID"), logger),
      ParseROAPDomainIdentifier(xml->GetChildElement("domainID"), logger),
      ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger),
      ParseDefDateTime(xml->GetChildElement("time"), logger),
      ParseROInfo(xml->GetChildElement("roInfo"), logger),
      ParseROAPCertificateChain(xml->GetChildElement("certificateChain"), logger),
      ParseRORequestExtensions(xml->GetChildElement("extensions"), logger),
      xml->GetChildElement("signature")->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRORequest: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRORequest: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROResponseExtensions.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROResponseExtensions. If fails, throws ROAPParserException.
*/
SPtr<ROResponseExtensions> ROAPParser::ParseROResponseExtensions(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    SPtr<TransactionIdExtension> transactionId;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("extension");
    for (unsigned int i = 0; i < elems.size(); i++) {
      if (elems[i]->GetChildAttribute("", "xsi:type") == 0) {
        throw ROAPParserException();
      }
      if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:TransactionIdentifier") {
        transactionId = ParseTransactionIdExtension(elems[i], logger);
      } else {
        throw ROAPParserException();
      }
    }
    return new ROResponseExtensions(transactionId);
  }
  catch (ROAPException) {
    logger.UpdateLog("ROAPParser::ParseROResponseExtensions: ROAP error...");
    throw ROAPParserException();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROResponseExtensions: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROResponseExtensions: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse SuccessTwoPassROResponse.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  SuccessTwoPassROResponse. If fails, throws ROAPParserException.
*/
SPtr<SuccessTwoPassROResponse> ROAPParser::ParseSuccessTwoPassROResponse(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("signature") == 0) {
      throw ROAPParserException();
    }
    std::vector<Base64StringT> ocsps;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("ocspResponse");
    for (unsigned int i = 0; i < elems.size(); i++) {
      ocsps.push_back(elems[i]->GetStrValue());
    }
    return new SuccessTwoPassROResponse(
      ParseROAPIdentifier(xml->GetChildElement("deviceID"), logger),
      ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger),
      ParseVector<ROAPProtectedRO, ROAPProtectedRO>(
        xml->GetOneOrMoreChildElementsByName("protectedRO"), ParseROAPProtectedRO, logger),
      ParseROAPCertificateChain(xml->GetChildElement("certificateChain"), logger),
      ocsps,
      ParseROResponseExtensions(xml->GetChildElement("extensions"), logger),
      xml->GetChildElement("signature")->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseSuccessTwoPassROResponse: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseSuccessTwoPassROResponse: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse UnsuccessTwoPassROResponse.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  UnsuccessTwoPassROResponse. If fails, throws ROAPParserException.
*/
SPtr<UnsuccessTwoPassROResponse> ROAPParser::ParseUnsuccessTwoPassROResponse(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new UnsuccessTwoPassROResponse(
      ParseUnsuccessROAPStatus(xml->GetChildAttribute("", "status"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessTwoPassROResponse: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessTwoPassROResponse: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse OnePassROResponse.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  OnePassROResponse. If fails, throws ROAPParserException.
*/
SPtr<OnePassROResponse> ROAPParser::ParseOnePassROResponse(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    //  TODO: there is the option without any elements for unsuccess status.
    if (xml->GetChildElement("signature") == 0) {
      throw ROAPParserException();
    }
    std::vector<Base64StringT> ocsps;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("ocspResponse");
    for (unsigned int i = 0; i < elems.size(); i++) {
      ocsps.push_back(elems[i]->GetStrValue());
    }
    return new OnePassROResponse(
      ParseROAPStatus(xml->GetChildAttribute("", "status"), logger),
      ParseROAPIdentifier(xml->GetChildElement("deviceID"), logger),
      ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseVector<ROAPProtectedRO, ROAPProtectedRO>(
        xml->GetOneOrMoreChildElementsByName("protectedRO"), ParseROAPProtectedRO, logger),
      ParseROAPCertificateChain(xml->GetChildElement("certificateChain"), logger),
      ocsps,
      ParseROResponseExtensions(xml->GetChildElement("extensions"), logger),
      xml->GetChildElement("signature")->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseOnePassROResponse: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseOnePassROResponse: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse JoinDomainReqExtensions.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  JoinDomainReqExtensions. If fails, throws ROAPParserException.
*/
SPtr<JoinDomainReqExtensions> ROAPParser::ParseJoinDomainReqExtensions(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    SPtr<PeerKeyIdExtension> peerKeyId;
    SPtr<NoOCSPResponseExtension> noOCSP;
    SPtr<OCSPResponderKeyIdExtension> ocspResponderKeyId;
    SPtr<HashChainSupportExtension> hashChainSupport;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("extension");
    for (unsigned int i = 0; i < elems.size(); i++) {
      if (elems[i]->GetChildAttribute("", "xsi:type") == 0) {
        throw ROAPParserException();
      }
      if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:PeerKeyIdentifier") {
        peerKeyId = ParsePeerKeyIdExtension(elems[i], logger);
      } else if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:NoOCSPResponse") {
        noOCSP = ParseNoOCSPResponseExtension(elems[i], logger);
      } else if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:OCSPResponderKeyIdentifier") {
        ocspResponderKeyId = ParseOCSPResponderKeyIdExtension(elems[i], logger);
      } else if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:HashChainSupport") {
        hashChainSupport = ParseHashChainSupportExtension(elems[i], logger);
      } else {
        throw ROAPParserException();
      }
    }
    return new JoinDomainReqExtensions(peerKeyId, noOCSP, ocspResponderKeyId, hashChainSupport);
  }
  catch (ROAPException) {
    logger.UpdateLog("ROAPParser::ParseJoinDomainReqExtensions: ROAP error...");
    throw ROAPParserException();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseJoinDomainReqExtensions: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseJoinDomainReqExtensions: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse JoinDomainRequest.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  JoinDomainRequest. If fails, throws ROAPParserException.
*/
SPtr<JoinDomainRequest> ROAPParser::ParseJoinDomainRequest(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("signature") == 0) {
      throw ROAPParserException();
    }
    return new JoinDomainRequest(ParseROAPNonce(xml->GetChildAttribute("", "triggerNonce"), logger),
      ParseROAPIdentifier(xml->GetChildElement("deviceID"), logger),
      ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger),
      ParseDefOrUndefDateTime(xml->GetChildElement("time"), logger),
      ParseROAPDomainIdentifier(xml->GetChildElement("domainID"), logger),
      ParseROAPCertificateChain(xml->GetChildElement("certificateChain"), logger),
      ParseJoinDomainReqExtensions(xml->GetChildElement("extensions"), logger),
      xml->GetChildElement("signature")->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseJoinDomainRequest: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseJoinDomainRequest: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DomainResponseExtensions.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DomainResponseExtensions. If fails, throws ROAPParserException.
*/
SPtr<DomainResponseExtensions> ROAPParser::ParseDomainResponseExtensions(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    SPtr<HashChainSupportExtension> hashChainSupport;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("extension");
    for (unsigned int i = 0; i < elems.size(); i++) {
      if (elems[i]->GetChildAttribute("", "xsi:type") == 0) {
        throw ROAPParserException();
      }
      if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:HashChainSupport") {
        hashChainSupport = ParseHashChainSupportExtension(elems[i], logger);
      } else {
        throw ROAPParserException();
      }
    }
    return new DomainResponseExtensions(hashChainSupport);
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDomainResponseExtensions: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDomainResponseExtensions: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPProtectedDomainKey.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROAPProtectedDomainKey. If fails, throws ROAPParserException.
*/
SPtr<ROAPProtectedDomainKey> ROAPParser::ParseROAPProtectedDomainKey(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("mac") == 0) {
      throw ROAPParserException();
    }
    return new ROAPProtectedDomainKey(
      ParseXencEncryptedKey(xml->GetChildElement("encKey"), logger),
      ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      xml->GetChildElement("mac")->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPProtectedDomainKey: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPProtectedDomainKey: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPDomainInfo.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  ROAPDomainInfo. If fails, throws ROAPParserException.
*/
SPtr<ROAPDomainInfo> ROAPParser::ParseROAPDomainInfo(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPDomainInfo(
      ParseDefOrInfDateTime(xml->GetChildElement("notAfter"), logger),
      ParseVector<ROAPProtectedDomainKey, ROAPProtectedDomainKey>(
        xml->GetOneOrMoreChildElementsByName("domainKey"),
        ParseROAPProtectedDomainKey, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPDomainInfo: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPDomainInfo: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse SuccessJoinDomainResponse.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  SuccessJoinDomainResponse. If fails, throws ROAPParserException.
*/
SPtr<SuccessJoinDomainResponse> ROAPParser::ParseSuccessJoinDomainResponse(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("signature") == 0) {
      throw ROAPParserException();
    }
    std::vector<Base64StringT> ocsps;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("ocspResponse");
    for (unsigned int i = 0; i < elems.size(); i++) {
      ocsps.push_back(elems[i]->GetStrValue());
    }
    return new SuccessJoinDomainResponse(
      ParseROAPIdentifier(xml->GetChildElement("deviceID"), logger),
      ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger),
      ParseROAPDomainInfo(xml->GetChildElement("domainInfo"), logger),
      ParseROAPCertificateChain(xml->GetChildElement("certificateChain"), logger),
      ocsps,
      ParseDomainResponseExtensions(xml->GetChildElement("extensions"), logger),
      xml->GetChildElement("signature")->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseSuccessJoinDomainResponse: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseSuccessJoinDomainResponse: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse UnsuccessJoinDomainResponse.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  UnsuccessJoinDomainResponse. If fails, throws ROAPParserException.
*/
SPtr<UnsuccessJoinDomainResponse> ROAPParser::ParseUnsuccessJoinDomainResponse(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new UnsuccessJoinDomainResponse(
      ParseUnsuccessROAPStatus(xml->GetChildAttribute("", "status"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessJoinDomainResponse: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessJoinDomainResponse: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse LeaveDomainReqExtensions.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  LeaveDomainReqExtensions. If fails, throws ROAPParserException.
*/
SPtr<LeaveDomainReqExtensions> ROAPParser::ParseLeaveDomainReqExtensions(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    SPtr<NotDomainMemberExtension> notDomainMember;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("extension");
    for (unsigned int i = 0; i < elems.size(); i++) {
      if (elems[i]->GetChildAttribute("", "xsi:type") == 0) {
        throw ROAPParserException();
      }
      if (elems[i]->GetChildAttrStrValue("", "xsi:type") == "roap:NotDomainMember") {
        notDomainMember = ParseNotDomainMemberExtension(elems[i], logger);
      } else {
        throw ROAPParserException();
      }
    }
    return new LeaveDomainReqExtensions(notDomainMember);
  }
  catch (ROAPException) {
    logger.UpdateLog("ROAPParser::ParseLeaveDomainReqExtensions: ROAP error...");
    throw ROAPParserException();
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseLeaveDomainReqExtensions: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseLeaveDomainReqExtensions: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse LeaveDomainRequest.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  LeaveDomainRequest. If fails, throws ROAPParserException.
*/
SPtr<LeaveDomainRequest> ROAPParser::ParseLeaveDomainRequest(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("signature") == 0) {
      throw ROAPParserException();
    }
    return new LeaveDomainRequest(ParseROAPNonce(xml->GetChildAttribute("", "triggerNonce"), logger),
      ParseROAPIdentifier(xml->GetChildElement("deviceID"), logger),
      ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger),
      ParseDefOrUndefDateTime(xml->GetChildElement("time"), logger),
      ParseROAPDomainIdentifier(xml->GetChildElement("domainID"), logger),
      ParseROAPCertificateChain(xml->GetChildElement("certificateChain"), logger),
      ParseLeaveDomainReqExtensions(xml->GetChildElement("extensions"), logger),
      xml->GetChildElement("signature")->GetStrValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseLeaveDomainRequest: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseLeaveDomainRequest: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse LeaveDomainResponseExtensions.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  LeaveDomainResponseExtensions. If fails, throws ROAPParserException.
*/
SPtr<LeaveDomainResponseExtensions> ROAPParser::ParseLeaveDomainResponseExtensions(IXMLElement* xml, DRMLogger& logger) {
  return 0;
}

/*! \brief  Parse SuccessLeaveDomainResponse.

    \param  xml       input, XML element.

    \returns  SuccessLeaveDomainResponse. If fails, throws ROAPParserException.
*/
SPtr<SuccessLeaveDomainResponse> ROAPParser::ParseSuccessLeaveDomainResponse(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new SuccessLeaveDomainResponse(
      ParseROAPNonce(xml->GetChildElement("nonce"), logger),
      ParseROAPDomainIdentifier(xml->GetChildElement("domainID"), logger),
      ParseLeaveDomainResponseExtensions(xml->GetChildElement("extensions"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseSuccessLeaveDomainResponse: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseSuccessLeaveDomainResponse: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse UnsuccessLeaveDomainResponse.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  UnsuccessLeaveDomainResponse. If fails, throws ROAPParserException.
*/
SPtr<UnsuccessLeaveDomainResponse> ROAPParser::ParseUnsuccessLeaveDomainResponse(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new UnsuccessLeaveDomainResponse(
      ParseUnsuccessROAPStatus(xml->GetChildAttribute("", "status"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessLeaveDomainResponse: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseUnsuccessLeaveDomainResponse: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse ROAPTriggerProxy.

    \param  xml       input, XML attribute.
    \param  logger    input, message logger.

    \returns  ROAPTriggerProxy. If fails, throws ROAPParserException.
*/
SPtr<ROAPTriggerProxy> ROAPParser::ParseROAPTriggerProxy(IXMLAttribute* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new ROAPTriggerProxy(xml->GetBoolValue());
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseROAPTriggerProxy: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseROAPTriggerProxy: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RegRequestTriggerData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  RegRequestTriggerData. If fails, throws ROAPParserException.
*/
SPtr<RegRequestTriggerData> ROAPParser::ParseRegRequestTriggerData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new RegRequestTriggerData(
      ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger),
      ParseURIValue(xml->GetChildElement("roapURL"), logger),
      ParseIDValue(xml->GetChildAttribute("", "id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRegRequestTriggerData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRegRequestTriggerData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse RegRequestTrigger.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  RegRequestTrigger. If fails, throws ROAPParserException.
*/
SPtr<RegRequestTrigger> ROAPParser::ParseRegRequestTrigger(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new RegRequestTrigger(
      ParseRegRequestTriggerData(xml->GetChildElement("registrationRequest"), logger),
      ParseDSSignature(xml->GetChildElement("signature"), logger),
      ParseROAPVersion(xml->GetChildAttribute("", "version"), logger),
      ParseROAPTriggerProxy(xml->GetChildAttribute("", "proxy"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseRegRequestTrigger: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseRegRequestTrigger: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DomainROTriggerData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DomainROTriggerData. If fails, throws ROAPParserException.
*/
SPtr<DomainROTriggerData> ROAPParser::ParseDomainROTriggerData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    IXMLElement* next = xml->GetFirstChild();
    if (next == 0) {
      throw ROAPParserException();
    }
    if (next->GetName() != "riID") {
      throw ROAPParserException();
    }
    NZSPtr<ROAPIdentifier> riid = ParseROAPIdentifier(next, logger);
    SPtr<ROAPNonce> nonce;
    next = next->GetFirstSibling();
    if (next == 0) {
      throw ROAPParserException();
    }
    if (next->GetName() == "nonce") {
      nonce = ParseROAPNonce(next, logger);
      next = next->GetFirstSibling();
      if (next == 0) {
        throw ROAPParserException();
      }
    }
    if (next->GetName() != "roapURL") {
      throw ROAPParserException();
    }
    NZSPtr<URIValue> url = ParseURIValue(next, logger);
    next = next->GetFirstSibling();
    if (next == 0) {
      throw ROAPParserException();
    }

    if (next->GetName() != "domainID") {
      throw ROAPParserException();
    }
    NZSPtr<ROAPDomainIdentifier> domainid = ParseROAPDomainIdentifier(next, logger);
    next = next->GetFirstSibling();
    if (next == 0) {
      throw ROAPParserException();
    }

    std::vector<NZSPtr<ROIDContentID> > ids;

    while (next != 0) {
      if (next->GetName() != "roID") {
        throw ROAPParserException();
      }
      NZSPtr<IDValue> roid = ParseIDValue(next, logger);
      next = next->GetFirstSibling();
      if (next == 0) {
        throw ROAPParserException();
      }
      if (next->GetName() != "contentID") {
        throw ROAPParserException();
      }
      std::vector<NZSPtr<URIValue> > cids;
      do {
        cids.push_back(ParseURIValue(next, logger));
        next = next->GetFirstSibling();
        if (next == 0) {
          break;
        }
      } while (next->GetName() == "contentID");
      ids.push_back(new ROIDContentID(roid, cids));
    }

    return new DomainROTriggerData(riid, nonce, url, domainid, ids,
      ParseIDValue(xml->GetChildAttribute("", "id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDomainROTriggerData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDomainROTriggerData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse NDomainROTriggerData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  NDomainROTriggerData. If fails, throws ROAPParserException.
*/
SPtr<NDomainROTriggerData> ROAPParser::ParseNDomainROTriggerData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    IXMLElement* next = xml->GetFirstChild();
    if (next == 0) {
      throw ROAPParserException();
    }
    if (next->GetName() != "riID") {
      throw ROAPParserException();
    }
    NZSPtr<ROAPIdentifier> riid = ParseROAPIdentifier(next, logger);
    SPtr<ROAPNonce> nonce;
    next = next->GetFirstSibling();
    if (next == 0) {
      throw ROAPParserException();
    }
    if (next->GetName() == "nonce") {
      nonce = ParseROAPNonce(next, logger);
      next = next->GetFirstSibling();
      if (next == 0) {
        throw ROAPParserException();
      }
    }
    if (next->GetName() != "roapURL") {
      throw ROAPParserException();
    }
    NZSPtr<URIValue> url = ParseURIValue(next, logger);
    next = next->GetFirstSibling();
    if (next == 0) {
      throw ROAPParserException();
    }

    std::vector<NZSPtr<ROIDContentID> > ids;

    while (next != 0) {
      if (next->GetName() != "roID") {
        throw ROAPParserException();
      }
      NZSPtr<IDValue> roid = ParseIDValue(next, logger);
      next = next->GetFirstSibling();
      if (next == 0) {
        throw ROAPParserException();
      }
      if (next->GetName() != "contentID") {
        throw ROAPParserException();
      }
      std::vector<NZSPtr<URIValue> > cids;
      do {
        cids.push_back(ParseURIValue(next, logger));
        next = next->GetFirstSibling();
        if (next == 0) {
          break;
        }
      } while (next->GetName() == "contentID");
      ids.push_back(new ROIDContentID(roid, cids));
    }

    return new NDomainROTriggerData(riid, nonce, url, ids,
      ParseIDValue(xml->GetChildAttribute("", "id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseNDomainROTriggerData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseNDomainROTriggerData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse DomainROTrigger.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  DomainROTrigger. If fails, throws ROAPParserException.
*/
SPtr<DomainROTrigger> ROAPParser::ParseDomainROTrigger(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new DomainROTrigger(
      ParseDomainROTriggerData(xml->GetChildElement("roAcquisition"), logger),
      ParseDSSignature(xml->GetChildElement("signature"), logger),
      ParseROAPVersion(xml->GetChildAttribute("", "version"), logger),
      ParseROAPTriggerProxy(xml->GetChildAttribute("", "proxy"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseDomainROTrigger: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseDomainROTrigger: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse NDomainROTrigger.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  NDomainROTrigger. If fails, throws ROAPParserException.
*/
SPtr<NDomainROTrigger> ROAPParser::ParseNDomainROTrigger(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new NDomainROTrigger(
      ParseNDomainROTriggerData(xml->GetChildElement("roAcquisition"), logger),
      ParseDSSignature(xml->GetChildElement("signature"), logger),
      ParseROAPVersion(xml->GetChildAttribute("", "version"), logger),
      ParseROAPTriggerProxy(xml->GetChildAttribute("", "proxy"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseNDomainROTrigger: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseNDomainROTrigger: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse JoinDomainTriggerData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  JoinDomainTriggerData. If fails, throws ROAPParserException.
*/
SPtr<JoinDomainTriggerData> ROAPParser::ParseJoinDomainTriggerData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new JoinDomainTriggerData(
      ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger),
      ParseURIValue(xml->GetChildElement("roapURL"), logger),
      ParseROAPDomainIdentifier(xml->GetChildElement("domainID"), logger),
      ParseIDValue(xml->GetChildAttribute("", "id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseJoinDomainTriggerData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseJoinDomainTriggerData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse LeaveDomainTriggerData.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  LeaveDomainTriggerData. If fails, throws ROAPParserException.
*/
SPtr<LeaveDomainTriggerData> ROAPParser::ParseLeaveDomainTriggerData(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new LeaveDomainTriggerData(
      ParseROAPIdentifier(xml->GetChildElement("riID"), logger),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger),
      ParseURIValue(xml->GetChildElement("roapURL"), logger),
      ParseROAPDomainIdentifier(xml->GetChildElement("domainID"), logger),
      ParseIDValue(xml->GetChildAttribute("", "id"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseLeaveDomainTriggerData: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseLeaveDomainTriggerData: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse JoinDomainTrigger.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  JoinDomainTrigger. If fails, throws ROAPParserException.
*/
SPtr<JoinDomainTrigger> ROAPParser::ParseJoinDomainTrigger(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new JoinDomainTrigger(
      ParseJoinDomainTriggerData(xml->GetChildElement("joinDomain"), logger),
      ParseDSSignature(xml->GetChildElement("signature"), logger),
      ParseROAPVersion(xml->GetChildAttribute("", "version"), logger),
      ParseROAPTriggerProxy(xml->GetChildAttribute("", "proxy"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseJoinDomainTrigger: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseJoinDomainTrigger: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse LeaveDomainTrigger.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  LeaveDomainTrigger. If fails, throws ROAPParserException.
*/
SPtr<LeaveDomainTrigger> ROAPParser::ParseLeaveDomainTrigger(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new LeaveDomainTrigger(
      ParseLeaveDomainTriggerData(xml->GetChildElement("leaveDomain"), logger),
      ParseDSSignature(xml->GetChildElement("signature"), logger),
      ParseXencEncryptedKey(xml->GetChildElement("encKey"), logger),
      ParseROAPVersion(xml->GetChildAttribute("", "version"), logger),
      ParseROAPTriggerProxy(xml->GetChildAttribute("", "proxy"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseLeaveDomainTrigger: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseLeaveDomainTrigger: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse InitialRORequest.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  InitialRORequest. If fails, throws ROAPParserException.
*/
SPtr<InitialRORequest> ROAPParser::ParseInitialRORequest(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new InitialRORequest(ParseROAPIdentifier(xml->GetChildElement("deviceID"), logger),
      ParseVector<URIValue, URIValue>(xml->GetOneOrMoreChildElementsByName("contentID"),
        ParseURIValue, logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseInitialRORequest: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseInitialRORequest: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse AddContentKeyRequest.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  AddContentKeyRequest. If fails, throws ROAPParserException.
*/
SPtr<AddContentKeyRequest> ROAPParser::ParseAddContentKeyRequest(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("encryptionKey") == 0) {
      throw ROAPParserException();
    }
    return new AddContentKeyRequest(
      ParseURIValue(xml->GetChildElement("contentID"), logger),
      xml->GetChildElement("encryptionKey")->GetStrValue(),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseAddContentKeyRequest: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseAddContentKeyRequest: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse AddContentKeyResponse.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  AddContentKeyResponse. If fails, throws ROAPParserException.
*/
SPtr<AddContentKeyResponse> ROAPParser::ParseAddContentKeyResponse(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("success") == 0) {
      throw ROAPParserException();
    }
    return new AddContentKeyResponse(xml->GetChildElement("success")->GetBoolValue(),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseAddContentKeyResponse: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseAddContentKeyResponse: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse AddDeviceRightsRequest.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  AddDeviceRightsRequest. If fails, throws ROAPParserException.
*/
SPtr<AddDeviceRightsRequest> ROAPParser::ParseAddDeviceRightsRequest(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    return new AddDeviceRightsRequest(
      ParseOEXRights(xml->GetChildElement("rights"), logger),
      ParseROAPIdentifier(xml->GetChildElement("deviceID"), logger),
      ParseURIValue(xml->GetChildElement("contentID"), logger),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseAddDeviceRightsRequest: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseAddDeviceRightsRequest: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

/*! \brief  Parse AddDeviceRightsResponse.

    \param  xml       input, XML element.
    \param  logger    input, message logger.

    \returns  AddDeviceRightsResponse. If fails, throws ROAPParserException.
*/
SPtr<AddDeviceRightsResponse> ROAPParser::ParseAddDeviceRightsResponse(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("success") == 0) {
      throw ROAPParserException();
    }
    return new AddDeviceRightsResponse(xml->GetChildElement("success")->GetBoolValue(),
      ParseROAPNonce(xml->GetChildElement("nonce"), logger));
  }
  catch (XMLException) {
    logger.UpdateLog("ROAPParser::ParseAddDeviceRightsResponse: XML error...");
    throw ROAPParserException();
  }
  catch (GCException) {
    logger.UpdateLog("ROAPParser::ParseAddDeviceRightsResponse: GC error...");
    throw ROAPParserException();
  }
  catch (BasicException) {
    logger.UpdateLog("ROAPParser::: Basic exception...");
    throw ROAPParserException();
  }
  catch (...) {
    logger.UpdateLog("ROAPParser::: Unknown exception...");
    throw ROAPParserException();
  }
}

} // namespace DRMPlugin
