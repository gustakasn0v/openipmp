/**	\file ROAPParser.h

	Parser for ROAP messages..

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (ROAPPARSER_H)
#define ROAPPARSER_H

#include <string>

#include "RO.h"
#include "ROAPImport.h"
#include "ROAPMessages.h"
#include "DRMLogger.h"
#include "IXMLDocument.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Exception used for ROAP parsing error.
*/
class ROAPParserException {
};

/*! \brief  Parse vector.

    Template parameter B represents basic type, to which parsed elements
    will be cast. Template parameter T represents return type of the parsing
    function parse.

    \param  elems       input, XML elements to parse.
    \param  parse       input, parsing function.
    \param  logger      input, message logger.

    \returns  Vector of parsed data.
*/
template<class B, class T> std::vector<NZSPtr<T> > ParseVector(const
    std::vector<IXMLElement*>& elems, SPtr<T> (*parse)(IXMLElement*, DRMLogger&), DRMLogger& logger) {
  std::vector<NZSPtr<B> > ret;
  for (unsigned int i = 0; i < elems.size(); i++) {
    ret.push_back((B*)(T*)(parse(elems[i], logger)));
  }
  return ret;
}

/*! \brief  ROAP parser. Parses ROAP messages from encoded XML string.
*/
class ROAPParser {
public:
  /*! \brief  Parse ODDVersion.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDVersion. If fails, throws ROAPParserException.
  */
  static SPtr<ODDVersion> ParseODDVersion(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RightsODDUID.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RightsODDUID. If fails, throws ROAPParserException.
  */
  static SPtr<RightsODDUID> ParseRightsODDUID(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse AssetODDUID.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  AssetODDUID. If fails, throws ROAPParserException.
  */
  static SPtr<AssetODDUID> ParseAssetODDUID(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse IndividualODDUID.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  IndividualODDUID. If fails, throws ROAPParserException.
  */
  static SPtr<IndividualODDUID> ParseIndividualODDUID(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse SystemODDUID.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  SystemODDUID. If fails, throws ROAPParserException.
  */
  static SPtr<SystemODDUID> ParseSystemODDUID(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse InheritODDUID.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  InheritODDUID. If fails, throws ROAPParserException.
  */
  static SPtr<InheritODDUID> ParseInheritODDUID(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RightsOEXContext.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RightsOEXContext. If fails, throws ROAPParserException.
  */
  static SPtr<RightsOEXContext> ParseRightsOEXContext(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse AssetOEXContext.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  AssetOEXContext. If fails, throws ROAPParserException.
  */
  static SPtr<AssetOEXContext> ParseAssetOEXContext(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse IndividualOEXContext.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  IndividualOEXContext. If fails, throws ROAPParserException.
  */
  static SPtr<IndividualOEXContext> ParseIndividualOEXContext(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse SystemOEXContext.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  SystemOEXContext. If fails, throws ROAPParserException.
  */
  static SPtr<SystemOEXContext> ParseSystemOEXContext(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse InheritOEXContext.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  InheritOEXContext. If fails, throws ROAPParserException.
  */
  static SPtr<InheritOEXContext> ParseInheritOEXContext(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse OEXAssetID.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  OEXAssetID. If fails, throws ROAPParserException.
  */
  static SPtr<OEXAssetID> ParseOEXAssetID(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse OEXAssetIDRef.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  OEXAssetIDRef. If fails, throws ROAPParserException.
  */
  static SPtr<OEXAssetIDRef> ParseOEXAssetIDRef(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse OEXInherit.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  OEXInherit. If fails, throws ROAPParserException.
  */
  static SPtr<OEXInherit> ParseOEXInherit(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse OEXDigest.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  OEXDigest. If fails, throws ROAPParserException.
  */
  static SPtr<OEXDigest> ParseOEXDigest(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RORetrievalMethod.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RORetrievalMethod. If fails, throws ROAPParserException.
  */
  static SPtr<RORetrievalMethod> ParseRORetrievalMethod(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROEncryptedKeyInfo.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROEncryptedKeyInfo. If fails, throws ROAPParserException.
  */
  static SPtr<ROEncryptedKeyInfo> ParseROEncryptedKeyInfo(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROXencEncryptionMethod.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROXencEncryptionMethod. If fails, throws ROAPParserException.
  */
  static SPtr<ROXencEncryptionMethod> ParseROXencEncryptionMethod(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROEncryptedKey.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROEncryptedKey. If fails, throws ROAPParserException.
  */
  static SPtr<ROEncryptedKey> ParseROEncryptedKey(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse OEXAssetKeyInfo.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  OEXAssetKeyInfo. If fails, throws ROAPParserException.
  */
  static SPtr<OEXAssetKeyInfo> ParseOEXAssetKeyInfo(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse AgreementOEXAsset.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  AgreementOEXAsset. If fails, throws ROAPParserException.
  */
  static SPtr<AgreementOEXAsset> ParseAgreementOEXAsset(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse PermissionOEXAsset.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  PermissionOEXAsset. If fails, throws ROAPParserException.
  */
  static SPtr<PermissionOEXAsset> ParsePermissionOEXAsset(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ODDCountConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDCountConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<ODDCountConstraint> ParseODDCountConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse OMADDTimedCountConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  OMADDTimedCountConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<OMADDTimedCountConstraint> ParseOMADDTimedCountConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ODDStart.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDStart. If fails, throws ROAPParserException.
  */
  static SPtr<ODDStart> ParseODDStart(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ODDEnd.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDEnd. If fails, throws ROAPParserException.
  */
  static SPtr<ODDEnd> ParseODDEnd(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ODDDatetimeConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDDatetimeConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<ODDDatetimeConstraint> ParseODDDatetimeConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ODDIntervalConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDIntervalConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<ODDIntervalConstraint> ParseODDIntervalConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ODDAccumulatedConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDAccumulatedConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<ODDAccumulatedConstraint> ParseODDAccumulatedConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ODDIndividualConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDIndividualConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<ODDIndividualConstraint> ParseODDIndividualConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse OMADDSystemConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  OMADDSystemConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<OMADDSystemConstraint> ParseOMADDSystemConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse GeneralOEXConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  GeneralOEXConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<GeneralOEXConstraint> ParseGeneralOEXConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse PlayOEXConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  PlayOEXConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<PlayOEXConstraint> ParsePlayOEXConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DisplayOEXConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DisplayOEXConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<DisplayOEXConstraint> ParseDisplayOEXConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ExecuteOEXConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ExecuteOEXConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<ExecuteOEXConstraint> ParseExecuteOEXConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse PrintOEXConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  PrintOEXConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<PrintOEXConstraint> ParsePrintOEXConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse MoveExportOEXConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  MoveExportOEXConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<MoveExportOEXConstraint> ParseMoveExportOEXConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse CopyExportOEXConstraint.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  CopyExportOEXConstraint. If fails, throws ROAPParserException.
  */
  static SPtr<CopyExportOEXConstraint> ParseCopyExportOEXConstraint(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ODDPlayPermission.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDPlayPermission. If fails, throws ROAPParserException.
  */
  static SPtr<ODDPlayPermission> ParseODDPlayPermission(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ODDDisplayPermission.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDDisplayPermission. If fails, throws ROAPParserException.
  */
  static SPtr<ODDDisplayPermission> ParseODDDisplayPermission(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ODDExecutePermission.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDExecutePermission. If fails, throws ROAPParserException.
  */
  static SPtr<ODDExecutePermission> ParseODDExecutePermission(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ODDPrintPermission.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ODDPrintPermission. If fails, throws ROAPParserException.
  */
  static SPtr<ODDPrintPermission> ParseODDPrintPermission(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse OMADDExportPermission.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  OMADDExportPermission. If fails, throws ROAPParserException.
  */
  static SPtr<OMADDExportPermission> ParseOMADDExportPermission(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse OEXPermission.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  OEXPermission. If fails, throws ROAPParserException.
  */
  static SPtr<OEXPermission> ParseOEXPermission(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse OEXAgreement.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  OEXAgreement. If fails, throws ROAPParserException.
  */
  static SPtr<OEXAgreement> ParseOEXAgreement(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse OEXRights.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  OEXRights. If fails, throws ROAPParserException.
  */
  static SPtr<OEXRights> ParseOEXRights(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse IDValue.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  IDValue. If fails, throws ROAPParserException.
  */
  static SPtr<IDValue> ParseIDValue(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse IDValue.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  IDValue. If fails, throws ROAPParserException.
  */
  static SPtr<IDValue> ParseIDValue(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse URIValue.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  URIValue. If fails, throws ROAPParserException.
  */
  static SPtr<URIValue> ParseURIValue(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse URIValue.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  URIValue. If fails, throws ROAPParserException.
  */
  static SPtr<URIValue> ParseURIValue(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse DSObject.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSObject. If fails, throws ROAPParserException.
  */
  static SPtr<DSObject> ParseDSObject(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSCryptoBinary.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSCryptoBinary. If fails, throws ROAPParserException.
  */
  static SPtr<DSCryptoBinary> ParseDSCryptoBinary(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSKeyName.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSKeyName. If fails, throws ROAPParserException.
  */
  static SPtr<DSKeyName> ParseDSKeyName(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSDSAKeyValuePQ.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSDSAKeyValuePQ. If fails, throws ROAPParserException.
  */
  static SPtr<DSDSAKeyValuePQ> ParseDSDSAKeyValuePQ(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSDSAKeyValueSeedCtr.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSDSAKeyValueSeedCtr. If fails, throws ROAPParserException.
  */
  static SPtr<DSDSAKeyValueSeedCtr> ParseDSDSAKeyValueSeedCtr(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSDSAKeyValue.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSDSAKeyValue. If fails, throws ROAPParserException.
  */
  static SPtr<DSDSAKeyValue> ParseDSDSAKeyValue(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSRSAKeyValue.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSRSAKeyValue. If fails, throws ROAPParserException.
  */
  static SPtr<DSRSAKeyValue> ParseDSRSAKeyValue(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSTransform.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSTransform. If fails, throws ROAPParserException.
  */
  static SPtr<DSTransform> ParseDSTransform(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSTransforms.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSTransforms. If fails, throws ROAPParserException.
  */
  static SPtr<DSTransforms> ParseDSTransforms(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSRetrievalMethod.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSRetrievalMethod. If fails, throws ROAPParserException.
  */
  static SPtr<DSRetrievalMethod> ParseDSRetrievalMethod(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse BasicX509Data.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  BasicX509Data. If fails, throws ROAPParserException.
  */
  static SPtr<BasicX509Data> ParseBasicX509Data(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSX509IssuerSerial.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSX509IssuerSerial. If fails, throws ROAPParserException.
  */
  static SPtr<DSX509IssuerSerial> ParseDSX509IssuerSerial(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSX509SKI.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSX509SKI. If fails, throws ROAPParserException.
  */
  static SPtr<DSX509SKI> ParseDSX509SKI(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSX509SubjectName.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSX509SubjectName. If fails, throws ROAPParserException.
  */
  static SPtr<DSX509SubjectName> ParseDSX509SubjectName(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSX509Certificate.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSX509Certificate. If fails, throws ROAPParserException.
  */
  static SPtr<DSX509Certificate> ParseDSX509Certificate(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSX509CRL.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSX509CRL. If fails, throws ROAPParserException.
  */
  static SPtr<DSX509CRL> ParseDSX509CRL(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSX509Data.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSX509Data. If fails, throws ROAPParserException.
  */
  static SPtr<DSX509Data> ParseDSX509Data(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSPGPData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSPGPData. If fails, throws ROAPParserException.
  */
  static SPtr<DSPGPData> ParseDSPGPData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSSPKIData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSSPKIData. If fails, throws ROAPParserException.
  */
  static SPtr<DSSPKIData> ParseDSSPKIData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSMgmtData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSMgmtData. If fails, throws ROAPParserException.
  */
  static SPtr<DSMgmtData> ParseDSMgmtData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse BasicKeyInfo.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  BasicKeyInfo. If fails, throws ROAPParserException.
  */
  static SPtr<BasicKeyInfo> ParseBasicKeyInfo(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSKeyInfo.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSKeyInfo. If fails, throws ROAPParserException.
  */
  static SPtr<DSKeyInfo> ParseDSKeyInfo(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSSignatureValue.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSSignatureValue. If fails, throws ROAPParserException.
  */
  static SPtr<DSSignatureValue> ParseDSSignatureValue(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSDigestValue.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSDigestValue. If fails, throws ROAPParserException.
  */
  static SPtr<DSDigestValue> ParseDSDigestValue(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSDigestMethod.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSDigestMethod. If fails, throws ROAPParserException.
  */
  static SPtr<DSDigestMethod> ParseDSDigestMethod(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSReference.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSReference. If fails, throws ROAPParserException.
  */
  static SPtr<DSReference> ParseDSReference(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSHMACOutputLength.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSHMACOutputLength. If fails, throws ROAPParserException.
  */
  static SPtr<DSHMACOutputLength> ParseDSHMACOutputLength(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSSignatureMethod.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSSignatureMethod. If fails, throws ROAPParserException.
  */
  static SPtr<DSSignatureMethod> ParseDSSignatureMethod(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSCanonicalizationMethod.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSCanonicalizationMethod. If fails, throws ROAPParserException.
  */
  static SPtr<DSCanonicalizationMethod> ParseDSCanonicalizationMethod(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSSignedInfo.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSSignedInfo. If fails, throws ROAPParserException.
  */
  static SPtr<DSSignedInfo> ParseDSSignedInfo(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DSSignature.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DSSignature. If fails, throws ROAPParserException.
  */
  static SPtr<DSSignature> ParseDSSignature(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse XencKeySize.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  XencKeySize. If fails, throws ROAPParserException.
  */
  static SPtr<XencKeySize> ParseXencKeySize(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse XencEncryptionMethod.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  XencEncryptionMethod. If fails, throws ROAPParserException.
  */
  static SPtr<XencEncryptionMethod> ParseXencEncryptionMethod(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse XencCipherData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  XencCipherData. If fails, throws ROAPParserException.
  */
  static SPtr<XencCipherData> ParseXencCipherData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse CValueXencCipherData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  CValueXencCipherData. If fails, throws ROAPParserException.
  */
  static SPtr<CValueXencCipherData> ParseCValueXencCipherData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse XencTransforms.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  XencTransforms. If fails, throws ROAPParserException.
  */
  static SPtr<XencTransforms> ParseXencTransforms(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse XencCipherReference.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  XencCipherReference. If fails, throws ROAPParserException.
  */
  static SPtr<XencCipherReference> ParseXencCipherReference(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse CRefXencCipherData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  CRefXencCipherData. If fails, throws ROAPParserException.
  */
  static SPtr<CRefXencCipherData> ParseCRefXencCipherData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse XencEncryptionProperty.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  XencEncryptionProperty. If fails, throws ROAPParserException.
  */
  static SPtr<XencEncryptionProperty> ParseXencEncryptionProperty(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse XencEncryptionProperties.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  XencEncryptionProperties. If fails, throws ROAPParserException.
  */
  static SPtr<XencEncryptionProperties> ParseXencEncryptionProperties(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse XencEncryptedTypeMime.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  XencEncryptedTypeMime. If fails, throws ROAPParserException.
  */
  static SPtr<XencEncryptedTypeMime> ParseXencEncryptedTypeMime(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse DataXencReferenceType.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DataXencReferenceType. If fails, throws ROAPParserException.
  */
  static SPtr<DataXencReferenceType> ParseDataXencReferenceType(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse KeyXencReferenceType.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  KeyXencReferenceType. If fails, throws ROAPParserException.
  */
  static SPtr<KeyXencReferenceType> ParseKeyXencReferenceType(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse XencReferenceList.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  XencReferenceList. If fails, throws ROAPParserException.
  */
  static SPtr<XencReferenceList> ParseXencReferenceList(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse NameXencEncryptedKeyData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  NameXencEncryptedKeyData. If fails, throws ROAPParserException.
  */
  static SPtr<NameXencEncryptedKeyData> ParseNameXencEncryptedKeyData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RecXencEncryptedKeyData.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  RecXencEncryptedKeyData. If fails, throws ROAPParserException.
  */
  static SPtr<RecXencEncryptedKeyData> ParseRecXencEncryptedKeyData(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse XencEncryptedKey.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  XencEncryptedKey. If fails, throws ROAPParserException.
  */
  static SPtr<XencEncryptedKey> ParseXencEncryptedKey(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPVersion.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPVersion. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPVersion> ParseROAPVersion(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPVersion.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  ROAPVersion. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPVersion> ParseROAPVersion(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPNonce.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPNonce. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPNonce> ParseROAPNonce(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPNonce.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  ROAPNonce. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPNonce> ParseROAPNonce(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPStatus.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  ROAPStatus. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPStatus> ParseROAPStatus(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse UnsuccessROAPStatus.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  UnsuccessROAPStatus. If fails, throws ROAPParserException.
  */
  static SPtr<UnsuccessROAPStatus> ParseUnsuccessROAPStatus(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse NoOCSPResponseExtension.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  NoOCSPResponseExtension. If fails, throws ROAPParserException.
  */
  static SPtr<NoOCSPResponseExtension> ParseNoOCSPResponseExtension(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPKeyIdentifier.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPKeyIdentifier. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPKeyIdentifier> ParseROAPKeyIdentifier(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse PeerKeyIdExtension.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  PeerKeyIdExtension. If fails, throws ROAPParserException.
  */
  static SPtr<PeerKeyIdExtension> ParsePeerKeyIdExtension(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse OCSPResponderKeyIdExtension.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  OCSPResponderKeyIdExtension. If fails, throws ROAPParserException.
  */
  static SPtr<OCSPResponderKeyIdExtension> ParseOCSPResponderKeyIdExtension(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DeviceDetailsData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DeviceDetailsData. If fails, throws ROAPParserException.
  */
  static SPtr<DeviceDetailsData> ParseDeviceDetailsData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DeviceDetailsExtension.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DeviceDetailsExtension. If fails, throws ROAPParserException.
  */
  static SPtr<DeviceDetailsExtension> ParseDeviceDetailsExtension(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse TransIdentifierData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  TransIdentifierData. If fails, throws ROAPParserException.
  */
  static SPtr<TransIdentifierData> ParseTransIdentifierData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse TransactionIdExtension.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  TransactionIdExtension. If fails, throws ROAPParserException.
  */
  static SPtr<TransactionIdExtension> ParseTransactionIdExtension(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse CertCachingExtension.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  CertCachingExtension. If fails, throws ROAPParserException.
  */
  static SPtr<CertCachingExtension> ParseCertCachingExtension(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse HashChainSupportExtension.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  HashChainSupportExtension. If fails, throws ROAPParserException.
  */
  static SPtr<HashChainSupportExtension> ParseHashChainSupportExtension(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse NotDomainMemberExtension.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  NotDomainMemberExtension. If fails, throws ROAPParserException.
  */
  static SPtr<NotDomainMemberExtension> ParseNotDomainMemberExtension(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DomainNameWhiteListExtension.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DomainNameWhiteListExtension. If fails, throws ROAPParserException.
  */
  static SPtr<DomainNameWhiteListExtension> ParseDomainNameWhiteListExtension(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPIdentifier.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPIdentifier. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPIdentifier> ParseROAPIdentifier(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPDomainIdentifier.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPDomainIdentifier. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPDomainIdentifier> ParseROAPDomainIdentifier(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DefDateTime.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DefDateTime. If fails, throws ROAPParserException.
  */
  static SPtr<DefDateTime> ParseDefDateTime(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DefDateTime or UndefDateTime.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DefDateTime or UndefDateTime. If fails, throws ROAPParserException.
  */
  static SPtr<DateTime> ParseDefOrUndefDateTime(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DefDateTime or InfDateTime.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DefDateTime or InfDateTime. If fails, throws ROAPParserException.
  */
  static SPtr<DateTime> ParseDefOrInfDateTime(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPROPayloadStatefulInfo.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  ROAPROPayloadStatefulInfo. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPROPayloadStatefulInfo> ParseROAPROPayloadStatefulInfo(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPROPayloadRIURLInfo.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  ROAPROPayloadRIURLInfo. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPROPayloadRIURLInfo> ParseROAPROPayloadRIURLInfo(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPROPayload.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPROPayload. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPROPayload> ParseROAPROPayload(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DomainROAPROPayload.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DomainROAPROPayload. If fails, throws ROAPParserException.
  */
  static SPtr<DomainROAPROPayload> ParseDomainROAPROPayload(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DeviceROAPROPayload.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DeviceROAPROPayload. If fails, throws ROAPParserException.
  */
  static SPtr<DeviceROAPROPayload> ParseDeviceROAPROPayload(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPProtectedRO.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPProtectedRO. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPProtectedRO> ParseROAPProtectedRO(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPServerInfo.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPServerInfo. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPServerInfo> ParseROAPServerInfo(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPSessionID.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  ROAPSessionID. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPSessionID> ParseROAPSessionID(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPKeyIdentifiers.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPKeyIdentifiers. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPKeyIdentifiers> ParseROAPKeyIdentifiers(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPCertificateChain.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPCertificateChain. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPCertificateChain> ParseROAPCertificateChain(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DeviceHelloExtensions.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DeviceHelloExtensions. If fails, throws ROAPParserException.
  */
  static SPtr<DeviceHelloExtensions> ParseDeviceHelloExtensions(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DeviceHelloRequest.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DeviceHelloRequest. If fails, throws ROAPParserException.
  */
  static SPtr<DeviceHelloRequest> ParseDeviceHelloRequest(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RIHelloExtensions.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RIHelloExtensions. If fails, throws ROAPParserException.
  */
  static SPtr<RIHelloExtensions> ParseRIHelloExtensions(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse SuccessRIHello.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  SuccessRIHello. If fails, throws ROAPParserException.
  */
  static SPtr<SuccessRIHello> ParseSuccessRIHello(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse UnsuccessRIHello.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  UnsuccessRIHello. If fails, throws ROAPParserException.
  */
  static SPtr<UnsuccessRIHello> ParseUnsuccessRIHello(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RegRequestExtensions.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RegRequestExtensions. If fails, throws ROAPParserException.
  */
  static SPtr<RegRequestExtensions> ParseRegRequestExtensions(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RegRequest.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RegRequest. If fails, throws ROAPParserException.
  */
  static SPtr<RegRequest> ParseRegRequest(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RegResponseExtensions.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RegResponseExtensions. If fails, throws ROAPParserException.
  */
  static SPtr<RegResponseExtensions> ParseRegResponseExtensions(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RegResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RegResponse. If fails, throws ROAPParserException.
  */
  static SPtr<RegResponse> ParseRegResponse(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse SuccessRegResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  SuccessRegResponse. If fails, throws ROAPParserException.
  */
  static SPtr<SuccessRegResponse> ParseSuccessRegResponse(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse UnsuccessRegResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  UnsuccessRegResponse. If fails, throws ROAPParserException.
  */
  static SPtr<UnsuccessRegResponse> ParseUnsuccessRegResponse(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DCFHash.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DCFHash. If fails, throws ROAPParserException.
  */
  static SPtr<DCFHash> ParseDCFHash(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROInfo.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROInfo. If fails, throws ROAPParserException.
  */
  static SPtr<ROInfo> ParseROInfo(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RORequestExtensions.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RORequestExtensions. If fails, throws ROAPParserException.
  */
  static SPtr<RORequestExtensions> ParseRORequestExtensions(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RORequest.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RORequest. If fails, throws ROAPParserException.
  */
  static SPtr<RORequest> ParseRORequest(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROResponseExtensions.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROResponseExtensions. If fails, throws ROAPParserException.
  */
  static SPtr<ROResponseExtensions> ParseROResponseExtensions(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse SuccessTwoPassROResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  SuccessTwoPassROResponse. If fails, throws ROAPParserException.
  */
  static SPtr<SuccessTwoPassROResponse> ParseSuccessTwoPassROResponse(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse UnsuccessTwoPassROResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  UnsuccessTwoPassROResponse. If fails, throws ROAPParserException.
  */
  static SPtr<UnsuccessTwoPassROResponse> ParseUnsuccessTwoPassROResponse(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse OnePassROResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  OnePassROResponse. If fails, throws ROAPParserException.
  */
  static SPtr<OnePassROResponse> ParseOnePassROResponse(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse JoinDomainReqExtensions.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  JoinDomainReqExtensions. If fails, throws ROAPParserException.
  */
  static SPtr<JoinDomainReqExtensions> ParseJoinDomainReqExtensions(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse JoinDomainRequest.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  JoinDomainRequest. If fails, throws ROAPParserException.
  */
  static SPtr<JoinDomainRequest> ParseJoinDomainRequest(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DomainResponseExtensions.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DomainResponseExtensions. If fails, throws ROAPParserException.
  */
  static SPtr<DomainResponseExtensions> ParseDomainResponseExtensions(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPProtectedDomainKey.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPProtectedDomainKey. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPProtectedDomainKey> ParseROAPProtectedDomainKey(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPDomainInfo.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  ROAPDomainInfo. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPDomainInfo> ParseROAPDomainInfo(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse SuccessJoinDomainResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  SuccessJoinDomainResponse. If fails, throws ROAPParserException.
  */
  static SPtr<SuccessJoinDomainResponse> ParseSuccessJoinDomainResponse(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse UnsuccessJoinDomainResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  UnsuccessJoinDomainResponse. If fails, throws ROAPParserException.
  */
  static SPtr<UnsuccessJoinDomainResponse> ParseUnsuccessJoinDomainResponse(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse LeaveDomainReqExtensions.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  LeaveDomainReqExtensions. If fails, throws ROAPParserException.
  */
  static SPtr<LeaveDomainReqExtensions> ParseLeaveDomainReqExtensions(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse LeaveDomainRequest.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  LeaveDomainRequest. If fails, throws ROAPParserException.
  */
  static SPtr<LeaveDomainRequest> ParseLeaveDomainRequest(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse LeaveDomainResponseExtensions.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  LeaveDomainResponseExtensions. If fails, throws ROAPParserException.
  */
  static SPtr<LeaveDomainResponseExtensions> ParseLeaveDomainResponseExtensions(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse SuccessLeaveDomainResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  SuccessLeaveDomainResponse. If fails, throws ROAPParserException.
  */
  static SPtr<SuccessLeaveDomainResponse> ParseSuccessLeaveDomainResponse(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse UnsuccessLeaveDomainResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  UnsuccessLeaveDomainResponse. If fails, throws ROAPParserException.
  */
  static SPtr<UnsuccessLeaveDomainResponse> ParseUnsuccessLeaveDomainResponse(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse ROAPTriggerProxy.

      \param  xml       input, XML attribute.
      \param  logger    input, message logger.

      \returns  ROAPTriggerProxy. If fails, throws ROAPParserException.
  */
  static SPtr<ROAPTriggerProxy> ParseROAPTriggerProxy(IXMLAttribute* xml, DRMLogger& logger);

  /*! \brief  Parse RegRequestTriggerData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RegRequestTriggerData. If fails, throws ROAPParserException.
  */
  static SPtr<RegRequestTriggerData> ParseRegRequestTriggerData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse RegRequestTrigger.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  RegRequestTrigger. If fails, throws ROAPParserException.
  */
  static SPtr<RegRequestTrigger> ParseRegRequestTrigger(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DomainROTriggerData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DomainROTriggerData. If fails, throws ROAPParserException.
  */
  static SPtr<DomainROTriggerData> ParseDomainROTriggerData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse NDomainROTriggerData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  NDomainROTriggerData. If fails, throws ROAPParserException.
  */
  static SPtr<NDomainROTriggerData> ParseNDomainROTriggerData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse DomainROTrigger.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  DomainROTrigger. If fails, throws ROAPParserException.
  */
  static SPtr<DomainROTrigger> ParseDomainROTrigger(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse NDomainROTrigger.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  NDomainROTrigger. If fails, throws ROAPParserException.
  */
  static SPtr<NDomainROTrigger> ParseNDomainROTrigger(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse JoinDomainTriggerData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  JoinDomainTriggerData. If fails, throws ROAPParserException.
  */
  static SPtr<JoinDomainTriggerData> ParseJoinDomainTriggerData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse LeaveDomainTriggerData.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  LeaveDomainTriggerData. If fails, throws ROAPParserException.
  */
  static SPtr<LeaveDomainTriggerData> ParseLeaveDomainTriggerData(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse JoinDomainTrigger.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  JoinDomainTrigger. If fails, throws ROAPParserException.
  */
  static SPtr<JoinDomainTrigger> ParseJoinDomainTrigger(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse LeaveDomainTrigger.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  LeaveDomainTrigger. If fails, throws ROAPParserException.
  */
  static SPtr<LeaveDomainTrigger> ParseLeaveDomainTrigger(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse InitialRORequest.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  InitialRORequest. If fails, throws ROAPParserException.
  */
  static SPtr<InitialRORequest> ParseInitialRORequest(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse AddContentKeyRequest.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  AddContentKeyRequest. If fails, throws ROAPParserException.
  */
  static SPtr<AddContentKeyRequest> ParseAddContentKeyRequest(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse AddContentKeyResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  AddContentKeyResponse. If fails, throws ROAPParserException.
  */
  static SPtr<AddContentKeyResponse> ParseAddContentKeyResponse(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse AddDeviceRightsRequest.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  AddDeviceRightsRequest. If fails, throws ROAPParserException.
  */
  static SPtr<AddDeviceRightsRequest> ParseAddDeviceRightsRequest(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Parse AddDeviceRightsResponse.

      \param  xml       input, XML element.
      \param  logger    input, message logger.

      \returns  AddDeviceRightsResponse. If fails, throws ROAPParserException.
  */
  static SPtr<AddDeviceRightsResponse> ParseAddDeviceRightsResponse(IXMLElement* xml, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (ROAPPARSER_H)
