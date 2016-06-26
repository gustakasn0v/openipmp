/** \file RO.h

    OMA DRM rights object classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (RO_H)
#define RO_H

#include "ROAPImport.h"
#include <vector>
#include "UTCTime.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Version.
*/
class ODDVersion: public XmlData {
public:
  /*! \brief  Constructor.

      \param  vs        version string.
  */
  ODDVersion(const std::string& vs): vstring(vs) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get version string.

      \returns  Version string.
  */
  const std::string& Get() const {
    return vstring;
  }

private:
	std::string vstring;
};

/*! \brief  (Unique) identifier.
*/
class ODDUID: public XmlData {
};

/*! \brief  (Unique) identifier used in rights context.
*/
class RightsODDUID: public ODDUID {
public:
  /*! \brief  Constructor.

      \param  id        identifier string.
  */
  RightsODDUID(const std::string& id): uid(id) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifier string.

      \returns  Identifier string.
  */
  const std::string& Get() const {
    return uid;
  }

private:
	std::string uid;
};

/*! \brief  (Unique) identifier used in asset context.
*/
class AssetODDUID: public ODDUID {
public:
  /*! \brief  Constructor.

      \param  id        identifier string.
  */
  AssetODDUID(const std::string& id): uid(id) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifier string.

      \returns  Identifier string.
  */
  const std::string& Get() const {
    return uid;
  }

private:
	std::string uid;
};

/*! \brief  (Unique) identifier used in individual context.
*/
class IndividualODDUID: public ODDUID {
public:
  /*! \brief  Constructor.

      \param  id        identifier string.
  */
  IndividualODDUID(const std::string& id): uid(id) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifier string.

      \returns  Identifier string.
  */
  const std::string& Get() const {
    return uid;
  }

private:
	std::string uid;
};

/*! \brief  (Unique) identifier used in system context.
*/
class SystemODDUID: public ODDUID {
public:
  /*! \brief  Constructor.

      \param  id        identifier string.
  */
  SystemODDUID(const std::string& id): uid(id) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifier string.

      \returns  Identifier string.
  */
  const std::string& Get() const {
    return uid;
  }

private:
	std::string uid;
};

/*! \brief  (Unique) identifier used in inherit context.
*/
class InheritODDUID: public ODDUID {
public:
  /*! \brief  Constructor.

      \param  id        identifier string.
  */
  InheritODDUID(const std::string& id): uid(id) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifier string.

      \returns  Identifier string.
  */
  const std::string& Get() const {
    return uid;
  }

private:
	std::string uid;
};

/*! \brief  Context.
*/
class OEXContext: public XmlData {
public:
  /*! \brief  Constructor.

      \param  ver       version.
  */
  OEXContext(const SPtr<ODDVersion>& ver): version(ver) {
  }

  /*! \brief  Get version.

      \returns  Version.
  */
  const SPtr<ODDVersion>& GetVersion() const {
    return version;
  }

protected:
	SPtr<ODDVersion> version;
};

/*! \brief  Rights context.
*/
class RightsOEXContext: public OEXContext {
public:
  /*! \brief  Constructor.

      \param  ver         version.
      \param  id          identifier.
  */
  RightsOEXContext(const SPtr<ODDVersion>& ver, const SPtr<RightsODDUID>& id):
    OEXContext(ver), uid(id) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifier.

      \returns  Identifier.
  */
  const SPtr<RightsODDUID>& GetUID() const {
    return uid;
  }

private:
  SPtr<RightsODDUID> uid;
};

/*! \brief  Asset context.
*/
class AssetOEXContext: public OEXContext {
public:
  /*! \brief  Constructor.

      \param  ver         version.
      \param  id          identifier.
  */
	AssetOEXContext(const SPtr<ODDVersion>& ver, const SPtr<AssetODDUID>& id):
    OEXContext(ver), uid(id) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifier.

      \returns  Identifier.
  */
  const SPtr<AssetODDUID>& GetUID() const {
    return uid;
  }

private:
  SPtr<AssetODDUID> uid;
};

/*! \brief  Individual context.
*/
class IndividualOEXContext: public OEXContext {
public:
  /*! \brief  Constructor.

      \param  ver         version.
      \param  ids         identifiers.
  */
	IndividualOEXContext(const SPtr<ODDVersion>& ver, const
    std::vector<NZSPtr<IndividualODDUID> >& ids): OEXContext(ver), uids(ids) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifiers.

      \returns  Identifiers.
  */
  const std::vector<NZSPtr<IndividualODDUID> >& GetUIDs() const {
    return uids;
  }

private:
  std::vector<NZSPtr<IndividualODDUID> > uids;
};

/*!	\brief  System context.
*/
class SystemOEXContext: public OEXContext {
public:
  /*! \brief  Constructor.

      \param  ver         version.
      \param  ids         identifiers.
  */
	SystemOEXContext(const SPtr<ODDVersion>& ver,
    const std::vector<NZSPtr<SystemODDUID> >& ids): OEXContext(ver), uids(ids) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifiers.

      \returns  Identifiers.
  */
  const std::vector<NZSPtr<SystemODDUID> >& GetUIDs() const {
    return uids;
  }

private:
  std::vector<NZSPtr<SystemODDUID> > uids;
};

/*! \brief  Inherit context.
*/
class InheritOEXContext: public OEXContext {
public:
  /*! \brief  Constructor.

      \param  ver         version.
      \param  id          identifier.
  */
	InheritOEXContext(const SPtr<ODDVersion>& ver, const SPtr<InheritODDUID>& id):
    OEXContext(ver), uid(id) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifier.

      \returns  Identifier.
  */
  const SPtr<InheritODDUID>& GetUID() const {
    return uid;
  }

private:
  SPtr<InheritODDUID> uid;
};

/*!	\brief  Asset.
*/
class OEXAsset: public XmlData {
};

/*! \brief  Asset identifier.
*/
class OEXAssetID: public GC {
public:
  /*! \brief  Constructor.

      \param  id          identifier value.
  */
  OEXAssetID(const NZSPtr<IDValue>& id): idval(id) {
  }

  /*! \brief  Get identifier value.

      \returns  Identifier value.
  */
  const NZSPtr<IDValue>& GetIDValue() const {
    return idval;
  }

private:
	NZSPtr<IDValue> idval;
};

/*! \brief  Asset identifier reference.
	  \todo: What exactly is type of the identifier reference?
*/
class OEXAssetIDRef: public GC {
public:
  /*! \brief  Constructor.

      \param  ref             identifier reference string.
  */
  OEXAssetIDRef(const std::string& ref): idRef(ref) {
  }

  /*! \brief  Get identifier reference string.

      \returns  Identifier reference string.
  */
  const std::string& Get() const {
    return idRef;
  }

private:
	std::string idRef;
};

/*! \brief  Inherit.
*/
class OEXInherit: public XmlData {
public:
  /*! \brief  Constructor.

      \param  ctx           inherit context.
  */
  OEXInherit(const NZSPtr<InheritOEXContext>& ctx): context(ctx) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get inherit context.

      \returns  Inherit context.
  */
  const NZSPtr<InheritOEXContext>& GetContext() const {
    return context;
  }

private:
	NZSPtr<InheritOEXContext> context;
};

/*! \brief  Digest definition.

    Digest method algorithm is fixed to http://www.w3.org/2000/09/xmldsig#sha1.
*/
class OEXDigest: public XmlData {
public:
  /*! \brief  Constructor.

      \param  dv            digest value.
  */
  OEXDigest(const NZSPtr<DSDigestValue>& dv):
    dMethod(new DSDigestMethod(new URIValue("http://www.w3.org/2000/09/xmldsig#sha1"))),
    dValue(dv) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get digest method.

      \returns  Digest method.
  */
  const NZSPtr<DSDigestMethod>& DigestMethod() const {
    return dMethod;
  }

  /*! \brief  Get digest value.

      \returns  Digest value.
  */
  const NZSPtr<DSDigestValue>& DigestValue() const {
    return dValue;
  }

private:
	NZSPtr<DSDigestMethod> dMethod;
	NZSPtr<DSDigestValue> dValue;
};

/*! \brief  Rights objects retrieval method.

	  URI value must be equal to the value given in encKey sibling to rights,
    in containing rights object payload (see ROAP messages).
*/
class RORetrievalMethod: public DSRetrievalMethod {
public:
  /*! \brief  Constructor.

      \param  ur              URI value.
  */
  RORetrievalMethod(const NZSPtr<URIValue>& ur): DSRetrievalMethod(0, ur, 0) {
  }
};

/*! \brief  Encrypted key info.
*/
class ROEncryptedKeyInfo: public DSKeyInfo {
public:
  /*! \brief  Constructor.

      \param  rm              rights objects retrieval method.
  */
  ROEncryptedKeyInfo(const NZSPtr<RORetrievalMethod>& rm):
    DSKeyInfo(std::vector<NZSPtr<BasicKeyInfo> >(1, (NZSPtr<BasicKeyInfo>)rm), 0),
    method(rm) {
  }

  /*! \brief  Get rights objects retrieval method.

      \returns  Rights objects retrieval method.
  */
  const NZSPtr<RORetrievalMethod>& GetMethod() const {
    return method;
  }

private:
  NZSPtr<RORetrievalMethod> method;
};

/*! \brief  Encryption method.

  	Algorithm is fixed: http://www.w3.org/2001/04/xmlenc#kw-aes128.
*/
class ROXencEncryptionMethod: public NOAEPXencEncryptionMethod {
public:
  /*! \brief  Constructor.
  */
  ROXencEncryptionMethod(): NOAEPXencEncryptionMethod(0,
    new URIValue("http://www.w3.org/2001/04/xmlenc#kw-aes128")) {
  }
};

/*! \brief  Encrypted key.
*/
class ROEncryptedKey: public XencEncryptedKey {
public:
  /*! \brief  Constructor.

      \param  info              encrypted key info.
      \param  meth              encryption method.
      \param  ciph              cipher data.
  */
	ROEncryptedKey(const SPtr<ROEncryptedKeyInfo>& info, const
    NZSPtr<ROXencEncryptionMethod>& meth, const NZSPtr<CValueXencCipherData>& ciph):
    XencEncryptedKey((SPtr<XencEncryptionMethod>)meth, (SPtr<DSKeyInfo>)info,
    (NZSPtr<XencCipherData>)ciph, 0, 0, 0, 0, 0, 0, 0, 0), keyInfo(info),
    encMethod(meth), cData(ciph) {
  }

  /*! \brief  Get encrypted key info.

      \returns  Encrypted key info.
  */
  const SPtr<ROEncryptedKeyInfo>& GetEncKeyInfo() const {
    return keyInfo;
  }

  /*! \brief  Get encryption method.

      \returns  Encryption method.
  */
  const NZSPtr<ROXencEncryptionMethod>& GetEncMethod() const {
    return encMethod;
  }

  /*! \brief  Get cipher data.

      \returns  Cipher data.
  */
  const NZSPtr<CValueXencCipherData>& GetCipherData() const {
    return cData;
  }

private:
	SPtr<ROEncryptedKeyInfo> keyInfo;
	NZSPtr<ROXencEncryptionMethod> encMethod;
	NZSPtr<CValueXencCipherData> cData;
};

/*! \brief  Key info contained in asset.

    \todo:  Documentation indicates that this is derived from DSKeyInfo,
            but DSKeyInfo doesn't contain encrypted key (see DSKeyInfo).
*/
class OEXAssetKeyInfo: public XmlData {
public:
  /*! \brief  Constructor.

      \param  key                 encrypted key.
  */
  OEXAssetKeyInfo(const NZSPtr<ROEncryptedKey>& key): encKey(key) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get encrypted key.

      \returns  Encrypted key.
  */
  const NZSPtr<ROEncryptedKey>& GetEncKey() const {
    return encKey;
  }

private:
	NZSPtr<ROEncryptedKey> encKey;
};

/*! \brief  Asset used in agreement.
*/
class AgreementOEXAsset: public OEXAsset {
public:
  /*! \brief  Constructor.

      \param  ctx               asset context.
      \param  inher             inherit.
      \param  dig               digest.
      \param  info              asset key info.
      \param  id                identifier.
  */
	AgreementOEXAsset(const SPtr<AssetOEXContext>& ctx, const SPtr<OEXInherit>& inher,
    const SPtr<OEXDigest>& dig, const SPtr<OEXAssetKeyInfo>& info,
    const SPtr<OEXAssetID>& id): context(ctx), inherit(inher), digest(dig),
    keyInfo(info), assetID(id) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get asset context.

      \returns  Asset context.
  */
  const SPtr<AssetOEXContext>& GetContext() const {
    return context;
  }

  /*! \brief  Get inherit.

      \returns  Inherit.
  */
  const SPtr<OEXInherit>& GetInherit() const {
    return inherit;
  }

  /*! \brief  Get digest.

      \returns  Digest.
  */
  const SPtr<OEXDigest>& GetDigest() const {
    return digest;
  }

  /*! \brief  Get asset key info.

      \returns  Asset key info.
  */
  const SPtr<OEXAssetKeyInfo>& GetKeyInfo() const {
    return keyInfo;
  }

  /*! \brief  Get asset identifier.

      \returns  Asset identifier.
  */
  const SPtr<OEXAssetID>& GetAssetID() const {
    return assetID;
  }

private:
	SPtr<AssetOEXContext> context;
	SPtr<OEXInherit> inherit; 
	SPtr<OEXDigest> digest;
	SPtr<OEXAssetKeyInfo> keyInfo;
	SPtr<OEXAssetID> assetID;
};

/*! \brief  Asset used in permission.
*/
class PermissionOEXAsset: public OEXAsset {
public:
  /*! \brief  Constructor.

      \param  ref               identifier reference.
  */
  PermissionOEXAsset(const SPtr<OEXAssetIDRef>& ref): idRef(ref) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get asset identifier reference.

      \returns  Asset identifier reference.
  */
  const SPtr<OEXAssetIDRef>& GetAssetIDRef() const {
    return idRef;
  }

private:
	SPtr<OEXAssetIDRef> idRef;
};

/*! \brief  Basic constraint.
*/
class BasicConstraint: public XmlData {
};

/*! \brief  Count constraint.
*/
class ODDCountConstraint: public BasicConstraint {
public:
  /*! \brief  Constructor.

      \param  cnt               count.
  */
  ODDCountConstraint(UInt32T cnt): count(cnt) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  bool Allow(const NZSPtr<ODDCountConstraint>& constraint) {
    return (count <= constraint->GetCount());
  }

  /*! \brief  Get count.

      \returns  Count.
  */
  UInt32T GetCount() const {
    return count;
  }

private:
	UInt32T count;
};

/*! \brief  Timed count constraint.
*/
class OMADDTimedCountConstraint: public BasicConstraint {
public:
  /*! \brief  Constructor.

      \param  cnt                 count.
  */
  OMADDTimedCountConstraint(UInt32T cnt): count(cnt) {
  }

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  bool Allow(const NZSPtr<OMADDTimedCountConstraint>& constraint) {
    return false;
  }

  /*! \brief  Get count.

      \returns  Count.
  */
  UInt32T GetCount() const {
    return count;
  }

protected:
	UInt32T count;
};

/*! \brief  Timed count constraint with timer.
*/
class TimerOMADDTimedCountConstraint: public OMADDTimedCountConstraint {
public:
  /*! \brief  Constructor.

      \param  cnt                   count.
      \param  tim                   timer.
  */
  TimerOMADDTimedCountConstraint(UInt32T cnt, UInt32T tim):
    OMADDTimedCountConstraint(cnt), timer(tim) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get timer.

      \returns  Timer.
  */
  UInt32T GetTimer() const {
    return timer;
  }

private:
	UInt32T timer;
};

/*! \brief  Timed count constraint without timer.
*/
class NTimerOMADDTimedCountConstraint: public OMADDTimedCountConstraint {
public:
  /*! \brief  Constructor.

      \param  cnt               count.
  */
  NTimerOMADDTimedCountConstraint(UInt32T cnt): OMADDTimedCountConstraint(cnt) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;
};

/*! \brief  Start time.
*/
class ODDStart: public XmlData {
public:
  /*! \brief  Constructor.

      \param  t         UTC time.
  */
  ODDStart(const UTCTime& t): time(t) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Less than operator.

      \param  rhs       input, start time.

      \returns  Boolean indicating if this time is less than rhs.
  */
  bool operator < (const ODDStart& rhs) const {
    return (time < rhs.time);
  }

  /*! \brief  Less than or equal operator.

      \param  rhs       input, start time.

      \returns  Boolean indicating if this time is less than or equal rhs.
  */
  bool operator <= (const ODDStart& rhs) const {
    return (time <= rhs.time);
  }

  /*! \brief  Get time.

      \returns  Time.
  */
  const UTCTime& GetTime() const {
    return time;
  }

private:
	UTCTime time;
};

/*! \brief  End time.
*/
class ODDEnd: public XmlData {
public:
  /*! \brief  Constructor.

      \param  t         UTC time.
  */
  ODDEnd(const UTCTime& t): time(t) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Less than operator.

      \param  rhs       input, end time.

      \returns  Boolean indicating if this time is less than rhs.
  */
  bool operator < (const ODDEnd& rhs) const {
    return (time < rhs.time);
  }

  /*! \brief  Less than or equal operator.

      \param  rhs       input, start time.

      \returns  Boolean indicating if this time is less than or equal rhs.
  */
  bool operator <= (const ODDEnd& rhs) const {
    return (time <= rhs.time);
  }

  /*! \brief  Get time.

      \returns  Time.
  */
  const UTCTime& GetTime() const {
    return time;
  }

private:
	UTCTime time;
};

/*! \brief  Exception used for ODDDatetimeConstraint error.
*/
class ODDDatetimeConstraintException {
};

/*! \brief  Datetime constraint.
*/
class ODDDatetimeConstraint: public BasicConstraint {
public:
  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  virtual bool Allow(const NZSPtr<ODDDatetimeConstraint>& constraint) = 0;

  /*! \brief  Get start time, if contains one.

      \returns  Start time, if contains one. If not, throws
                ODDDatetimeConstraintException.
  */
  virtual NZSPtr<ODDStart> GetStart() = 0;

  /*! \brief  Get end time, if contains one.

      \returns  End time, if contains one. If not, throws
                ODDDatetimeConstraintException.
  */
  virtual NZSPtr<ODDEnd> GetEnd() = 0;
};

/*! \brief  Empty datetime constraint. No start time and no end time.
*/
class EmptyODDDatetimeConstraint: public ODDDatetimeConstraint {
public:
  /*! \brief  Constructor.
  */
  EmptyODDDatetimeConstraint() {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  virtual bool Allow(const NZSPtr<ODDDatetimeConstraint>& constraint) {
    return true;
  }

  /*! \brief  Get start time, if contains one.

      \returns  Start time, if contains one. If not, throws
                ODDDatetimeConstraintException.
  */
  virtual NZSPtr<ODDStart> GetStart() {
    throw ODDDatetimeConstraintException();
  }

  /*! \brief  Get end time, if contains one.

      \returns  End time, if contains one. If not, throws
                ODDDatetimeConstraintException.
  */
  virtual NZSPtr<ODDEnd> GetEnd() {
    throw ODDDatetimeConstraintException();
  }
};

/*! \brief  Datetime constraint with start time.
*/
class StartODDDatetimeConstraint: public ODDDatetimeConstraint {
public:
  /*! \brief  Constructor.

      \param  st              start time.
  */
  StartODDDatetimeConstraint(const NZSPtr<ODDStart>& st): start(st) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  virtual bool Allow(const NZSPtr<ODDDatetimeConstraint>& constraint) {
    try {
      NZSPtr<ODDStart> cstart = constraint->GetStart();
      return ((*start) <= (*cstart));
    }
    catch (ODDDatetimeConstraintException) {
      return false;
    }
  }

  /*! \brief  Get start time, if contains one.

      \returns  Start time, if contains one. If not, throws
                ODDDatetimeConstraintException.
  */
  virtual NZSPtr<ODDStart> GetStart() {
    return start;
  }

  /*! \brief  Get end time, if contains one.

      \returns  End time, if contains one. If not, throws
                ODDDatetimeConstraintException.
  */
  virtual NZSPtr<ODDEnd> GetEnd() {
    throw ODDDatetimeConstraintException();
  }

private:
	NZSPtr<ODDStart> start;
};

/*! \brief  Datetime constraint with end time.
*/
class EndODDDatetimeConstraint: public ODDDatetimeConstraint {
public:
  /*! \brief  Constructor.

      \param  en                  end time.
  */
  EndODDDatetimeConstraint(const NZSPtr<ODDEnd>& en): end(en) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  virtual bool Allow(const NZSPtr<ODDDatetimeConstraint>& constraint) {
    try {
      NZSPtr<ODDEnd> cend = constraint->GetEnd();
      return ((*cend) <= (*end));
    }
    catch (ODDDatetimeConstraintException) {
      return false;
    }
  }

  /*! \brief  Get start time, if contains one.

      \returns  Start time, if contains one. If not, throws
                ODDDatetimeConstraintException.
  */
  virtual NZSPtr<ODDStart> GetStart() {
    throw ODDDatetimeConstraintException();
  }

  /*! \brief  Get end time, if contains one.

      \returns  End time, if contains one. If not, throws
                ODDDatetimeConstraintException.
  */
  virtual NZSPtr<ODDEnd> GetEnd() {
    return end;
  }

private:
	NZSPtr<ODDEnd> end;
};

/*! \brief  Datetime constraint with both start and end time.
*/
class StartEndODDDatetimeConstraint: public ODDDatetimeConstraint {
public:
  /*! \brief  Constructor.

      \param  st                    start time.
      \param  en                    end time.
  */
  StartEndODDDatetimeConstraint(const NZSPtr<ODDStart>& st, const NZSPtr<ODDEnd>& en):
    start(st), end(en) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  virtual bool Allow(const NZSPtr<ODDDatetimeConstraint>& constraint) {
    try {
      NZSPtr<ODDStart> cstart = constraint->GetStart();
      NZSPtr<ODDEnd> cend = constraint->GetEnd();
      return (((*start) <= (*cstart)) && ((*cend) <= (*end)));
    }
    catch (ODDDatetimeConstraintException) {
      return false;
    }
  }

  /*! \brief  Get start time, if contains one.

      \returns  Start time, if contains one. If not, throws
                ODDDatetimeConstraintException.
  */
  virtual NZSPtr<ODDStart> GetStart() {
    return start;
  }

  /*! \brief  Get end time, if contains one.

      \returns  End time, if contains one. If not, throws
                ODDDatetimeConstraintException.
  */
  virtual NZSPtr<ODDEnd> GetEnd() {
    return end;
  }

private:
	NZSPtr<ODDStart> start;
	NZSPtr<ODDEnd> end;
};

/*! \brief  Interval constraint.
*/
class ODDIntervalConstraint: public BasicConstraint {
public:
  /*! \brief  Constructor.

      \param  inter               interval string.
  */
  ODDIntervalConstraint(const std::string& inter): interval(inter) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  bool Allow(const NZSPtr<ODDIntervalConstraint>& constraint) {
    return false;
  }

  /*! \brief  Get interval string.

      \returns  Interval string.
  */
  const std::string& GetInterval() const {
    return interval;
  }

private:
	std::string interval;
};

/*! \brief  Accumulated constraint.
*/
class ODDAccumulatedConstraint: public BasicConstraint {
public:
  /*! \brief  Constructor.

      \param  inter               interval string.
  */
  ODDAccumulatedConstraint(const std::string& inter): interval(inter) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  bool Allow(const NZSPtr<ODDAccumulatedConstraint>& constraint) {
    return false;
  }

  /*! \brief  Get interval string.

      \returns  Interval string.
  */
  const std::string& GetInterval() const {
    return interval;
  }

private:
	std::string interval;
};

/*! \brief  Individual constraint.
*/
class ODDIndividualConstraint: public BasicConstraint {
public:
  /*! \brief  Constructor.

      \param  ctx               individual context.
  */
  ODDIndividualConstraint(const NZSPtr<IndividualOEXContext>& ctx): context(ctx) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  bool Allow(const NZSPtr<ODDIndividualConstraint>& constraint) {
    return false;
  }

  /*! \brief  Get individual context.

      \returns  Individual context.
  */
  const NZSPtr<IndividualOEXContext>& GetContext() const {
    return context;
  }

private:
	NZSPtr<IndividualOEXContext> context;
};

/*! \brief  System constraint.
*/
class OMADDSystemConstraint: public BasicConstraint {
public:
  /*! \brief  Constructor.

      \param  ctx                 system context.
  */
  OMADDSystemConstraint(const NZSPtr<SystemOEXContext>& ctx): context(ctx) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  bool Allow(const NZSPtr<OMADDSystemConstraint>& constraint) {
    return (GetContext()->XmlEncode() == constraint->GetContext()->XmlEncode());
  }

  /*! \brief  Get system context.

      \returns  System context.
  */
  const NZSPtr<SystemOEXContext>& GetContext() const {
    return context;
  }

private:
	NZSPtr<SystemOEXContext> context;
};

/*! \brief  Constraint.
*/
class OEXConstraint: public XmlData {
};

/*! \brief  General constraint.
*/
class GeneralOEXConstraint: public OEXConstraint {
public:
  /*! \brief  Constructor.

      \param  countc              count constraint.
      \param  timedcountc         timed count constraint.
      \param  datetimec           datetime constraint.
      \param  intervalc           interval constraint.
      \param  accumulatedc        accumulated constraint.
      \param  individualc         individual constraint.
      \param  systemc             system constraints.
  */
	GeneralOEXConstraint(const SPtr<ODDCountConstraint>& countc,
		const SPtr<OMADDTimedCountConstraint>& timedcountc,
		const SPtr<ODDDatetimeConstraint>& datetimec,
		const SPtr<ODDIntervalConstraint>& intervalc,
		const SPtr<ODDAccumulatedConstraint>& accumulatedc,
		const SPtr<ODDIndividualConstraint>& individualc,
    const std::vector<NZSPtr<OMADDSystemConstraint> >& systemc): count(countc),
    timedcount(timedcountc), datetime(datetimec), interval(intervalc),
    accumulated(accumulatedc), individual(individualc), systems(systemc) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  bool Allow(const NZSPtr<GeneralOEXConstraint>& constraint) {
    if (count != 0) {
      if (constraint->GetCountConstraint() != 0) {
        if (count->Allow(constraint->GetCountConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (timedcount != 0) {
      if (constraint->GetTimedCountConstraint() != 0) {
        if (timedcount->Allow(constraint->GetTimedCountConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (datetime != 0) {
      if (constraint->GetDatetimeConstraint() != 0) {
        if (datetime->Allow(constraint->GetDatetimeConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (interval != 0) {
      if (constraint->GetIntervalConstraint() != 0) {
        if (interval->Allow(constraint->GetIntervalConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (accumulated != 0) {
      if (constraint->GetIntervalConstraint() != 0) {
        if (accumulated->Allow(constraint->GetAccumulatedConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (individual != 0) {
      if (constraint->GetIndividualConstraint() != 0) {
        if (individual->Allow(constraint->GetIndividualConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if ((systems.size() > 0) && (constraint->GetSystemConstraints().size() == 0)) {
      return false;
    }
    unsigned int i = 0, j = 0;
    for (i = 0; i < constraint->GetSystemConstraints().size(); i++) {
      //  Check if any of our system constraints allows given system constraint.
      for (j = 0; j < systems.size(); j++) {
        if (systems[j]->Allow(constraint->GetSystemConstraints()[i]) == true) {
          break;
        }
      }
      if (j == systems.size()) {
        return false;
      }
    }
    return true;
  }

  /*! \brief  Get count constraint.

      \returns  Count constraint.
  */
  const SPtr<ODDCountConstraint>& GetCountConstraint() const {
    return count;
  }

  /*! \brief  Get timed count constraint.

      \returns  Timed count constraint.
  */
  const SPtr<OMADDTimedCountConstraint>& GetTimedCountConstraint() const {
    return timedcount;
  }

  /*! \brief  Get datetime constraint.

      \returns  Datetime constraint.
  */
  const SPtr<ODDDatetimeConstraint>& GetDatetimeConstraint() const {
    return datetime;
  }

  /*! \brief  Get interval constraint.

      \returns  Interval constraint.
  */
  const SPtr<ODDIntervalConstraint>& GetIntervalConstraint() const {
    return interval;
  }

  /*! \brief  Get accumulated constraint.

      \returns  Accumulated constraint.
  */
  const SPtr<ODDAccumulatedConstraint>& GetAccumulatedConstraint() const {
    return accumulated;
  }

  /*! \brief  Get individual constraint.

      \returns  Individual constraint.
  */
  const SPtr<ODDIndividualConstraint>& GetIndividualConstraint() const {
    return individual;
  }

  /*! \brief  Get system constraints.

      \returns  System constraints.
  */
  const std::vector<NZSPtr<OMADDSystemConstraint> >& GetSystemConstraints() const {
    return systems;
  }

private:
	SPtr<ODDCountConstraint> count;
	SPtr<OMADDTimedCountConstraint> timedcount;
	SPtr<ODDDatetimeConstraint> datetime;
	SPtr<ODDIntervalConstraint> interval;
	SPtr<ODDAccumulatedConstraint> accumulated;
	SPtr<ODDIndividualConstraint> individual;
	std::vector<NZSPtr<OMADDSystemConstraint> > systems;
};

/*! \brief  Play constraint.
*/
class PlayOEXConstraint: public OEXConstraint {
public:
  /*! \brief  Constructor.

      \param  countc              count constraint.
      \param  timedcountc         timed count constraint.
      \param  datetimec           datetime constraint.
      \param  intervalc           interval constraint.
      \param  accumulatedc        accumulated constraint.
      \param  individualc         individual constraint.
      \param  systemc             system constraints.
  */
	PlayOEXConstraint(const SPtr<ODDCountConstraint>& countc,
		const SPtr<OMADDTimedCountConstraint>& timedcountc,
		const SPtr<ODDDatetimeConstraint>& datetimec,
		const SPtr<ODDIntervalConstraint>& intervalc,
		const SPtr<ODDAccumulatedConstraint>& accumulatedc,
		const SPtr<ODDIndividualConstraint>& individualc,
    const std::vector<NZSPtr<OMADDSystemConstraint> >& systemc): count(countc),
    timedcount(timedcountc), datetime(datetimec), interval(intervalc),
    accumulated(accumulatedc), individual(individualc), systems(systemc) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  bool Allow(const NZSPtr<PlayOEXConstraint>& constraint) {
    if (count != 0) {
      if (constraint->GetCountConstraint() != 0) {
        if (count->Allow(constraint->GetCountConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (timedcount != 0) {
      if (constraint->GetTimedCountConstraint() != 0) {
        if (timedcount->Allow(constraint->GetTimedCountConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (datetime != 0) {
      if (constraint->GetDatetimeConstraint() != 0) {
        if (datetime->Allow(constraint->GetDatetimeConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (interval != 0) {
      if (constraint->GetIntervalConstraint() != 0) {
        if (interval->Allow(constraint->GetIntervalConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (accumulated != 0) {
      if (constraint->GetIntervalConstraint() != 0) {
        if (accumulated->Allow(constraint->GetAccumulatedConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (individual != 0) {
      if (constraint->GetIndividualConstraint() != 0) {
        if (individual->Allow(constraint->GetIndividualConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if ((systems.size() > 0) && (constraint->GetSystemConstraints().size() == 0)) {
      return false;
    }
    unsigned int i = 0, j = 0;
    for (i = 0; i < constraint->GetSystemConstraints().size(); i++) {
      //  Check if any of our system constraints allows given system constraint.
      for (j = 0; j < systems.size(); j++) {
        if (systems[j]->Allow(constraint->GetSystemConstraints()[i]) == true) {
          break;
        }
      }
      if (j == systems.size()) {
        return false;
      }
    }
    return true;
  }

  /*! \brief  Get count constraint.

      \returns  Count constraint.
  */
  const SPtr<ODDCountConstraint>& GetCountConstraint() const {
    return count;
  }

  /*! \brief  Get timed count constraint.

      \returns  Timed count constraint.
  */
  const SPtr<OMADDTimedCountConstraint>& GetTimedCountConstraint() const {
    return timedcount;
  }

  /*! \brief  Get datetime constraint.

      \returns  Datetime constraint.
  */
  const SPtr<ODDDatetimeConstraint>& GetDatetimeConstraint() const {
    return datetime;
  }

  /*! \brief  Get interval constraint.

      \returns  Interval constraint.
  */
  const SPtr<ODDIntervalConstraint>& GetIntervalConstraint() const {
    return interval;
  }

  /*! \brief  Get accumulated constraint.

      \returns  Accumulated constraint.
  */
  const SPtr<ODDAccumulatedConstraint>& GetAccumulatedConstraint() const {
    return accumulated;
  }

  /*! \brief  Get individual constraint.

      \returns  Individual constraint.
  */
  const SPtr<ODDIndividualConstraint>& GetIndividualConstraint() const {
    return individual;
  }

  /*! \brief  Get system constraints.

      \returns  System constraints.
  */
  const std::vector<NZSPtr<OMADDSystemConstraint> >& GetSystemConstraints() const {
    return systems;
  }

private:
	SPtr<ODDCountConstraint> count;
	SPtr<OMADDTimedCountConstraint> timedcount;
	SPtr<ODDDatetimeConstraint> datetime;
	SPtr<ODDIntervalConstraint> interval;
	SPtr<ODDAccumulatedConstraint> accumulated;
	SPtr<ODDIndividualConstraint> individual;
	std::vector<NZSPtr<OMADDSystemConstraint> > systems;
};

/*! \brief  Display constraint.
*/
class DisplayOEXConstraint: public OEXConstraint {
public:
  /*! \brief  Constructor.

      \param  countc              count constraint.
      \param  timedcountc         timed count constraint.
      \param  datetimec           datetime constraint.
      \param  intervalc           interval constraint.
      \param  accumulatedc        accumulated constraint.
      \param  individualc         individual constraint.
      \param  systemc             system constraints.
  */
	DisplayOEXConstraint(const SPtr<ODDCountConstraint>& countc,
		const SPtr<OMADDTimedCountConstraint>& timedcountc,
		const SPtr<ODDDatetimeConstraint>& datetimec,
		const SPtr<ODDIntervalConstraint>& intervalc,
		const SPtr<ODDAccumulatedConstraint>& accumulatedc,
		const SPtr<ODDIndividualConstraint>& individualc,
    const std::vector<NZSPtr<OMADDSystemConstraint> >& systemc): count(countc),
    timedcount(timedcountc), datetime(datetimec), interval(intervalc),
    accumulated(accumulatedc), individual(individualc), systems(systemc) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  bool Allow(const NZSPtr<DisplayOEXConstraint>& constraint) {
    if (count != 0) {
      if (constraint->GetCountConstraint() != 0) {
        if (count->Allow(constraint->GetCountConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (timedcount != 0) {
      if (constraint->GetTimedCountConstraint() != 0) {
        if (timedcount->Allow(constraint->GetTimedCountConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (datetime != 0) {
      if (constraint->GetDatetimeConstraint() != 0) {
        if (datetime->Allow(constraint->GetDatetimeConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (interval != 0) {
      if (constraint->GetIntervalConstraint() != 0) {
        if (interval->Allow(constraint->GetIntervalConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (accumulated != 0) {
      if (constraint->GetIntervalConstraint() != 0) {
        if (accumulated->Allow(constraint->GetAccumulatedConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (individual != 0) {
      if (constraint->GetIndividualConstraint() != 0) {
        if (individual->Allow(constraint->GetIndividualConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if ((systems.size() > 0) && (constraint->GetSystemConstraints().size() == 0)) {
      return false;
    }
    unsigned int i = 0, j = 0;
    for (i = 0; i < constraint->GetSystemConstraints().size(); i++) {
      //  Check if any of our system constraints allows given system constraint.
      for (j = 0; j < systems.size(); j++) {
        if (systems[j]->Allow(constraint->GetSystemConstraints()[i]) == true) {
          break;
        }
      }
      if (j == systems.size()) {
        return false;
      }
    }
    return true;
  }

  /*! \brief  Get count constraint.

      \returns  Count constraint.
  */
  const SPtr<ODDCountConstraint>& GetCountConstraint() const {
    return count;
  }

  /*! \brief  Get timed count constraint.

      \returns  Timed count constraint.
  */
  const SPtr<OMADDTimedCountConstraint>& GetTimedCountConstraint() const {
    return timedcount;
  }

  /*! \brief  Get datetime constraint.

      \returns  Datetime constraint.
  */
  const SPtr<ODDDatetimeConstraint>& GetDatetimeConstraint() const {
    return datetime;
  }

  /*! \brief  Get interval constraint.

      \returns  Interval constraint.
  */
  const SPtr<ODDIntervalConstraint>& GetIntervalConstraint() const {
    return interval;
  }

  /*! \brief  Get accumulated constraint.

      \returns  Accumulated constraint.
  */
  const SPtr<ODDAccumulatedConstraint>& GetAccumulatedConstraint() const {
    return accumulated;
  }

  /*! \brief  Get individual constraint.

      \returns  Individual constraint.
  */
  const SPtr<ODDIndividualConstraint>& GetIndividualConstraint() const {
    return individual;
  }

  /*! \brief  Get system constraints.

      \returns  System constraints.
  */
  const std::vector<NZSPtr<OMADDSystemConstraint> >& GetSystemConstraints() const {
    return systems;
  }

private:
	SPtr<ODDCountConstraint> count;
	SPtr<OMADDTimedCountConstraint> timedcount;
	SPtr<ODDDatetimeConstraint> datetime;
	SPtr<ODDIntervalConstraint> interval;
	SPtr<ODDAccumulatedConstraint> accumulated;
	SPtr<ODDIndividualConstraint> individual;
	std::vector<NZSPtr<OMADDSystemConstraint> > systems;
};

/*! \brief  Execute constraint.
*/
class ExecuteOEXConstraint: public OEXConstraint {
public:
  /*! \brief  Constructor.

      \param  countc              count constraint.
      \param  timedcountc         timed count constraint.
      \param  datetimec           datetime constraint.
      \param  intervalc           interval constraint.
      \param  accumulatedc        accumulated constraint.
      \param  individualc         individual constraint.
  */
	ExecuteOEXConstraint(const SPtr<ODDCountConstraint>& countc,
		const SPtr<OMADDTimedCountConstraint>& timedcountc,
		const SPtr<ODDDatetimeConstraint>& datetimec,
		const SPtr<ODDIntervalConstraint>& intervalc,
		const SPtr<ODDAccumulatedConstraint>& accumulatedc,
		const SPtr<ODDIndividualConstraint>& individualc): count(countc),
    timedcount(timedcountc), datetime(datetimec), interval(intervalc),
    accumulated(accumulatedc), individual(individualc) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  bool Allow(const NZSPtr<ExecuteOEXConstraint>& constraint) {
    if (count != 0) {
      if (constraint->GetCountConstraint() != 0) {
        if (count->Allow(constraint->GetCountConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (timedcount != 0) {
      if (constraint->GetTimedCountConstraint() != 0) {
        if (timedcount->Allow(constraint->GetTimedCountConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (datetime != 0) {
      if (constraint->GetDatetimeConstraint() != 0) {
        if (datetime->Allow(constraint->GetDatetimeConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (interval != 0) {
      if (constraint->GetIntervalConstraint() != 0) {
        if (interval->Allow(constraint->GetIntervalConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (accumulated != 0) {
      if (constraint->GetIntervalConstraint() != 0) {
        if (accumulated->Allow(constraint->GetAccumulatedConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (individual != 0) {
      if (constraint->GetIndividualConstraint() != 0) {
        if (individual->Allow(constraint->GetIndividualConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    return true;
  }

  /*! \brief  Get count constraint.

      \returns  Count constraint.
  */
  const SPtr<ODDCountConstraint>& GetCountConstraint() const {
    return count;
  }

  /*! \brief  Get timed count constraint.

      \returns  Timed count constraint.
  */
  const SPtr<OMADDTimedCountConstraint>& GetTimedCountConstraint() const {
    return timedcount;
  }

  /*! \brief  Get datetime constraint.

      \returns  Datetime constraint.
  */
  const SPtr<ODDDatetimeConstraint>& GetDatetimeConstraint() const {
    return datetime;
  }

  /*! \brief  Get interval constraint.

      \returns  Interval constraint.
  */
  const SPtr<ODDIntervalConstraint>& GetIntervalConstraint() const {
    return interval;
  }

  /*! \brief  Get accumulated constraint.

      \returns  Accumulated constraint.
  */
  const SPtr<ODDAccumulatedConstraint>& GetAccumulatedConstraint() const {
    return accumulated;
  }

  /*! \brief  Get individual constraint.

      \returns  Individual constraint.
  */
  const SPtr<ODDIndividualConstraint>& GetIndividualConstraint() const {
    return individual;
  }

private:
	SPtr<ODDCountConstraint> count;
	SPtr<OMADDTimedCountConstraint> timedcount;
	SPtr<ODDDatetimeConstraint> datetime;
	SPtr<ODDIntervalConstraint> interval;
	SPtr<ODDAccumulatedConstraint> accumulated;
	SPtr<ODDIndividualConstraint> individual;
};

/*! \brief  Print constraint.
*/
class PrintOEXConstraint: public OEXConstraint {
public:
  /*! \brief  Constructor.

      \param  countc              count constraint.
      \param  datetimec           datetime constraint.
      \param  intervalc           interval constraint.
      \param  accumulatedc        accumulated constraint.
      \param  individualc         individual constraint.
  */
	PrintOEXConstraint(const SPtr<ODDCountConstraint>& countc,
		const SPtr<ODDDatetimeConstraint>& datetimec,
		const SPtr<ODDIntervalConstraint>& intervalc,
		const SPtr<ODDAccumulatedConstraint>& accumulatedc,
		const SPtr<ODDIndividualConstraint>& individualc): count(countc),
    datetime(datetimec), interval(intervalc), accumulated(accumulatedc),
    individual(individualc) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  bool Allow(const NZSPtr<PrintOEXConstraint>& constraint) {
    if (count != 0) {
      if (constraint->GetCountConstraint() != 0) {
        if (count->Allow(constraint->GetCountConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (datetime != 0) {
      if (constraint->GetDatetimeConstraint() != 0) {
        if (datetime->Allow(constraint->GetDatetimeConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (interval != 0) {
      if (constraint->GetIntervalConstraint() != 0) {
        if (interval->Allow(constraint->GetIntervalConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (accumulated != 0) {
      if (constraint->GetIntervalConstraint() != 0) {
        if (accumulated->Allow(constraint->GetAccumulatedConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    if (individual != 0) {
      if (constraint->GetIndividualConstraint() != 0) {
        if (individual->Allow(constraint->GetIndividualConstraint()) == false) {
          return false;
        }
      } else {
        return false;
      }
    }
    return true;
  }

  /*! \brief  Get count constraint.

      \returns  Count constraint.
  */
  const SPtr<ODDCountConstraint>& GetCountConstraint() const {
    return count;
  }

  /*! \brief  Get datetime constraint.

      \returns  Datetime constraint.
  */
  const SPtr<ODDDatetimeConstraint>& GetDatetimeConstraint() const {
    return datetime;
  }

  /*! \brief  Get interval constraint.

      \returns  Interval constraint.
  */
  const SPtr<ODDIntervalConstraint>& GetIntervalConstraint() const {
    return interval;
  }

  /*! \brief  Get accumulated constraint.

      \returns  Accumulated constraint.
  */
  const SPtr<ODDAccumulatedConstraint>& GetAccumulatedConstraint() const {
    return accumulated;
  }

  /*! \brief  Get individual constraint.

      \returns  Individual constraint.
  */
  const SPtr<ODDIndividualConstraint>& GetIndividualConstraint() const {
    return individual;
  }

private:
	SPtr<ODDCountConstraint> count;
	SPtr<ODDDatetimeConstraint> datetime;
	SPtr<ODDIntervalConstraint> interval;
	SPtr<ODDAccumulatedConstraint> accumulated;
	SPtr<ODDIndividualConstraint> individual;
};

/*! \brief  Export constraint.
*/
class ExportOEXConstraint: public OEXConstraint {
public:
  /*! \brief  Get export constraint type.

      \returns  Export constraint type.
  */
  virtual std::string GetType() = 0;

  /*! \brief  Get count constraint.

      \returns  Count constraint.
  */
  virtual SPtr<ODDCountConstraint> GetCountConstraint() const = 0;

  /*! \brief  Get interval constraint.

      \returns  Interval constraint.
  */
  virtual SPtr<ODDIntervalConstraint> GetIntervalConstraint() const = 0;

  /*! \brief  Get datetime constraint.

      \returns  Datetime constraint.
  */
  virtual const SPtr<ODDDatetimeConstraint>& GetDatetimeConstraint() const = 0;

  /*! \brief  Get system constraints.

      \returns  System constraints.
  */
  virtual const std::vector<NZSPtr<OMADDSystemConstraint> >& GetSystemConstraints() const = 0;

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  virtual bool Allow(const NZSPtr<ExportOEXConstraint>& constraint) = 0;
};

/*! \brief  Move export constraint.
*/
class MoveExportOEXConstraint: public ExportOEXConstraint {
public:
  /*! \brief  Constructor.

      \param  datetimec           datetime constraint.
      \param  systemc             system constraints.

      If fails, throws ROAPException.
  */
	MoveExportOEXConstraint(const SPtr<ODDDatetimeConstraint>& datetimec,
    const std::vector<NZSPtr<OMADDSystemConstraint> >& systemc): datetime(datetimec),
    systems(systemc) {
    if (systems.size() == 0) {
      throw ROAPException();
    }
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get export constraint type.

      \returns  Export constraint type.
  */
  virtual std::string GetType() {
    return "move";
  }

  /*! \brief  Get count constraint.

      \returns  Count constraint.
  */
  virtual SPtr<ODDCountConstraint> GetCountConstraint() const {
    return 0;
  }

  /*! \brief  Get interval constraint.

      \returns  Interval constraint.
  */
  virtual SPtr<ODDIntervalConstraint> GetIntervalConstraint() const {
    return 0;
  }

  /*! \brief  Get datetime constraint.

      \returns  Datetime constraint.
  */
  virtual const SPtr<ODDDatetimeConstraint>& GetDatetimeConstraint() const {
    return datetime;
  }

  /*! \brief  Get system constraints.

      \returns  System constraints.
  */
  virtual const std::vector<NZSPtr<OMADDSystemConstraint> >& GetSystemConstraints() const {
    return systems;
  }

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  virtual bool Allow(const NZSPtr<ExportOEXConstraint>& constraint) {
    if (constraint->GetType() == "move") {
      if (datetime != 0) {
        if (constraint->GetDatetimeConstraint() != 0) {
          if (datetime->Allow(constraint->GetDatetimeConstraint()) == false) {
            return false;
          }
        } else {
          return false;
        }
      }
      if ((systems.size() > 0) && (constraint->GetSystemConstraints().size() == 0)) {
        return false;
      }
      unsigned int i = 0, j = 0;
      for (i = 0; i < constraint->GetSystemConstraints().size(); i++) {
        //  Check if any of our system constraints allows given system constraint.
        for (j = 0; j < systems.size(); j++) {
          if (systems[j]->Allow(constraint->GetSystemConstraints()[i]) == true) {
            break;
          }
        }
        if (j == systems.size()) {
          return false;
        }
      }
      return true;
    }
    return false;
  }

private:
	SPtr<ODDDatetimeConstraint> datetime;
	std::vector<NZSPtr<OMADDSystemConstraint> > systems;
};

/*! \brief  Copy export constraint.
*/
class CopyExportOEXConstraint: public ExportOEXConstraint {
public:
  /*! \brief  Constructor.

      \param  countc              count constraint.
      \param  datetimec           datetime constraint.
      \param  intervalc           interval constraint.
      \param  systemc             system constraints.

      If fails, throws ROAPException.
  */
	CopyExportOEXConstraint(const SPtr<ODDCountConstraint>& countc,
		const SPtr<ODDDatetimeConstraint>& datetimec,
		const SPtr<ODDIntervalConstraint>& intervalc,
    const std::vector<NZSPtr<OMADDSystemConstraint> >& systemc): count(countc),
    datetime(datetimec), interval(intervalc), systems(systemc) {
    if (systems.size() == 0) {
      throw ROAPException();
    }
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get export constraint type.

      \returns  Export constraint type.
  */
  virtual std::string GetType() {
    return "copy";
  }

  /*! \brief  Get count constraint.

      \returns  Count constraint.
  */
  virtual SPtr<ODDCountConstraint> GetCountConstraint() const {
    return count;
  }

  /*! \brief  Get interval constraint.

      \returns  Interval constraint.
  */
  virtual SPtr<ODDIntervalConstraint> GetIntervalConstraint() const {
    return interval;
  }

  /*! \brief  Get datetime constraint.

      \returns  Datetime constraint.
  */
  virtual const SPtr<ODDDatetimeConstraint>& GetDatetimeConstraint() const {
    return datetime;
  }

  /*! \brief  Get system constraints.

      \returns  System constraints.
  */
  virtual const std::vector<NZSPtr<OMADDSystemConstraint> >& GetSystemConstraints() const {
    return systems;
  }

  /*! \brief  Check if given constraint is not violating this constraint.

      \param  constraint      input, constraint to check.

      \returns  Boolean indicating if given constraint is not violating
                this constraint.
  */
  virtual bool Allow(const NZSPtr<ExportOEXConstraint>& constraint) {
    if (constraint->GetType() == "copy") {
      if (count != 0) {
        if (constraint->GetCountConstraint() != 0) {
          if (count->Allow(constraint->GetCountConstraint()) == false) {
            return false;
          }
        } else {
          return false;
        }
      }
      if (interval != 0) {
        if (constraint->GetIntervalConstraint() != 0) {
          if (interval->Allow(constraint->GetIntervalConstraint()) == false) {
            return false;
          }
        } else {
          return false;
        }
      }
      if (datetime != 0) {
        if (constraint->GetDatetimeConstraint() != 0) {
          if (datetime->Allow(constraint->GetDatetimeConstraint()) == false) {
            return false;
          }
        } else {
          return false;
        }
      }
      if ((systems.size() > 0) && (constraint->GetSystemConstraints().size() == 0)) {
        return false;
      }
      unsigned int i = 0, j = 0;
      for (i = 0; i < constraint->GetSystemConstraints().size(); i++) {
        //  Check if any of our system constraints allows given system constraint.
        for (j = 0; j < systems.size(); j++) {
          if (systems[j]->Allow(constraint->GetSystemConstraints()[i]) == true) {
            break;
          }
        }
        if (j == systems.size()) {
          return false;
        }
      }
      return true;
    }
    return false;
  }

private:
	SPtr<ODDCountConstraint> count;
	SPtr<ODDDatetimeConstraint> datetime;
	SPtr<ODDIntervalConstraint> interval;
	std::vector<NZSPtr<OMADDSystemConstraint> > systems;
};

/*! \brief  Basic permission.
*/
class BasicPermission: public XmlData {
};

/*! \brief  Play permission.
*/
class ODDPlayPermission: public BasicPermission {
public:
  /*! \brief  Constructor.

      \param  con                 play constraint.
  */
  ODDPlayPermission(const SPtr<PlayOEXConstraint>& con): constraint(con) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  bool Allow(const NZSPtr<ODDPlayPermission>& permission) {
    if (constraint != 0) {
      if (permission->GetConstraint() != 0) {
        return (constraint->Allow(permission->GetConstraint()));
      } else {
        return false;
      }
    }
    return true;
  }

  /*! \brief  Get play constraint.

      \returns  Play constraint.
  */
  const SPtr<PlayOEXConstraint>& GetConstraint() const {
    return constraint;
  }

private:
	SPtr<PlayOEXConstraint> constraint;
};

/*! \brief  Display permission.
*/
class ODDDisplayPermission: public BasicPermission {
public:
  /*! \brief  Constructor.

      \param  con                   display constraint.
  */
  ODDDisplayPermission(const SPtr<DisplayOEXConstraint>& con): constraint(con) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  bool Allow(const NZSPtr<ODDDisplayPermission>& permission) {
    if (constraint != 0) {
      if (permission->GetConstraint() != 0) {
        return (constraint->Allow(permission->GetConstraint()));
      } else {
        return false;
      }
    }
    return true;
  }

  /*! \brief  Get display constraint.

      \returns  Display constraint.
  */
  const SPtr<DisplayOEXConstraint>& GetConstraint() const {
    return constraint;
  }

private:
	SPtr<DisplayOEXConstraint> constraint;
};

/*! \brief  Execute permission.
*/
class ODDExecutePermission: public BasicPermission {
public:
  /*! \brief  Constructor.

      \param  con                   execute constraint.
  */
  ODDExecutePermission(const SPtr<ExecuteOEXConstraint>& con): constraint(con) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  bool Allow(const NZSPtr<ODDExecutePermission>& permission) {
    if (constraint != 0) {
      if (permission->GetConstraint() != 0) {
        return (constraint->Allow(permission->GetConstraint()));
      } else {
        return false;
      }
    }
    return true;
  }

  /*! \brief  Get execute constraint.

      \returns  Execute constraint.
  */
  const SPtr<ExecuteOEXConstraint>& GetConstraint() const {
    return constraint;
  }

private:
	SPtr<ExecuteOEXConstraint> constraint;
};

/*! \brief  Print permission.
*/
class ODDPrintPermission: public BasicPermission {
public:
  /*! \brief  Constructor.

      \param  con                   print constraint.
  */
  ODDPrintPermission(const SPtr<PrintOEXConstraint>& con): constraint(con) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  bool Allow(const NZSPtr<ODDPrintPermission>& permission) {
    if (constraint != 0) {
      if (permission->GetConstraint() != 0) {
        return (constraint->Allow(permission->GetConstraint()));
      } else {
        return false;
      }
    }
    return true;
  }

  /*! \brief  Get print constraint.

      \returns  Print constraint.
  */
  const SPtr<PrintOEXConstraint>& GetConstraint() const {
    return constraint;
  }

private:
	SPtr<PrintOEXConstraint> constraint;
};

/*! \brief  Export permission.
*/
class OMADDExportPermission: public BasicPermission {
public:
  /*! \brief  Get export constraint.

      \returns  Export constraint.
  */
  virtual NZSPtr<ExportOEXConstraint> GetConstraint() const = 0;

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  virtual bool Allow(const NZSPtr<OMADDExportPermission>& permission) = 0;
};

/*! \brief  Move export permission.
*/
class MoveOMADDExportPermission: public OMADDExportPermission {
public:
  /*! \brief  Constructor.

      \param  con                     move export constraint.
  */
  MoveOMADDExportPermission(const NZSPtr<MoveExportOEXConstraint>& con):
    constraint(con) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get export constraint.

      \returns  Export constraint.
  */
  virtual NZSPtr<ExportOEXConstraint> GetConstraint() const {
    return (ExportOEXConstraint*)constraint;
  }

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  virtual bool Allow(const NZSPtr<OMADDExportPermission>& permission) {
    return (GetConstraint()->Allow(permission->GetConstraint()));
  }

  /*! \brief  Get move export constraint.

      \returns  Move export constraint.
  */
  const NZSPtr<MoveExportOEXConstraint>& GetMoveConstraint() const {
    return constraint;
  }

private:
	NZSPtr<MoveExportOEXConstraint> constraint;
};

/*! \brief  Copy export permission.
*/
class CopyOMADDExportPermission: public OMADDExportPermission {
public:
  /*! \brief  Constructor.

      \param  con                     copy export constraint.
  */
  CopyOMADDExportPermission(const NZSPtr<CopyExportOEXConstraint>& con):
    constraint(con) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get export constraint.

      \returns  Export constraint.
  */
  virtual NZSPtr<ExportOEXConstraint> GetConstraint() const {
    return (ExportOEXConstraint*)constraint;
  }

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  virtual bool Allow(const NZSPtr<OMADDExportPermission>& permission) {
    return (GetConstraint()->Allow(permission->GetConstraint()));
  }

  /*! \brief  Get copy export constraint.

      \returns  Copy export constraint.
  */
  const NZSPtr<CopyExportOEXConstraint>& GetCopyConstraint() const {
    return constraint;
  }

private:
	NZSPtr<CopyExportOEXConstraint> constraint;
};

/*! \brief  Rights permission.
*/
class OEXPermission: public XmlData {
public:
  /*! \brief  Constructor.

      \param  generalc                  general constraint.
      \param  asset                     permission assets.
      \param  playp                     play permission.
      \param  displayp                  display permission.
      \param  executep                  execute permission.
      \param  printp                    print permission.
      \param  exportp                   export permission.
  */
	OEXPermission(const SPtr<GeneralOEXConstraint>& generalc,
		const std::vector<NZSPtr<PermissionOEXAsset> >& asset,
		const SPtr<ODDPlayPermission>& playp, const SPtr<ODDDisplayPermission>&
    displayp, const SPtr<ODDExecutePermission>& executep,
    const SPtr<ODDPrintPermission>& printp, const SPtr<OMADDExportPermission>&
    exportp): general(generalc), assets(asset), play(playp), display(displayp),
    execute(executep), print(printp), eexport(exportp) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  bool Allow(const NZSPtr<ODDPlayPermission>& permission) {
    if (play != 0) {
      return play->Allow(permission);
    }
    return false;
  }

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  bool Allow(const NZSPtr<ODDDisplayPermission>& permission) {
    if (display != 0) {
      return display->Allow(permission);
    }
    return false;
  }

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  bool Allow(const NZSPtr<ODDExecutePermission>& permission) {
    if (execute != 0) {
      return execute->Allow(permission);
    }
    return false;
  }

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  bool Allow(const NZSPtr<ODDPrintPermission>& permission) {
    if (print != 0) {
      return print->Allow(permission);
    }
    return false;
  }

  /*! \brief  Check if given permission is not violating this permission.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                this permission.
  */
  bool Allow(const NZSPtr<OMADDExportPermission>& permission) {
    if (eexport != 0) {
      return eexport->Allow(permission);
    }
    return false;
  }

  /*! \brief  Get general constraint.

      \returns  General constraint.
  */
  const SPtr<GeneralOEXConstraint>& GetGeneral() const {
    return general;
  }

  /*! \brief  Get permission assets.

      \returns  Permission assets.
  */
  const std::vector<NZSPtr<PermissionOEXAsset> >& GetAssets() const {
    return assets;
  }

  /*! \brief  Get play permission.

      \returns  Play permission.
  */
  const SPtr<ODDPlayPermission>& GetPlay() const {
    return play;
  }

  /*! \brief  Get display permission.

      \returns  Display permission.
  */
  const SPtr<ODDDisplayPermission>& GetDisplay() const {
    return display;
  }

  /*! \brief  Get execute permission.

      \returns  Execute permission.
  */
  const SPtr<ODDExecutePermission>& GetExecute() const {
    return execute;
  }

  /*! \brief  Get print permission.

      \returns  Print permission.
  */
  const SPtr<ODDPrintPermission>& GetPrint() const {
    return print;
  }

  /*! \brief  Get export permission.

      \returns  Export permission.
  */
  const SPtr<OMADDExportPermission>& GetExport() const {
    return eexport;
  }

private:
	SPtr<GeneralOEXConstraint> general;
	std::vector<NZSPtr<PermissionOEXAsset> > assets;
	SPtr<ODDPlayPermission> play;
	SPtr<ODDDisplayPermission> display;
	SPtr<ODDExecutePermission> execute;
	SPtr<ODDPrintPermission> print;
	SPtr<OMADDExportPermission> eexport;
};

/*! \brief  Rights agreement.
*/
class OEXAgreement: public XmlData {
public:
  /*! \brief  Constructor.

	    Size of asset must be > 0.

      \param  asset                   agreement assets.
      \param  perm                    permissions.

      If fails, throws ROAPException.
  */
	OEXAgreement(const std::vector<NZSPtr<AgreementOEXAsset> >& asset,
      const std::vector<NZSPtr<OEXPermission> >& perm): assets(asset),
      permissions(perm) {
    if (assets.size() == 0) {
      throw ROAPException();
    }
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Check if given permission is not violating (any of the) contained
              permissions.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                (any of the) contained permissions.
  */
  bool Allow(const NZSPtr<ODDPlayPermission>& permission) {
    for (unsigned int i = 0; i < permissions.size(); i++) {
      if (permissions[i]->Allow(permission) == true) {
        return true;
      }
    }
    return false;
  }

  /*! \brief  Check if given permission is not violating (any of the) contained
              permissions.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                (any of the) contained permissions.
  */
  bool Allow(const NZSPtr<ODDDisplayPermission>& permission) {
    for (unsigned int i = 0; i < permissions.size(); i++) {
      if (permissions[i]->Allow(permission) == true) {
        return true;
      }
    }
    return false;
  }

  /*! \brief  Check if given permission is not violating (any of the) contained
              permissions.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                (any of the) contained permissions.
  */
  bool Allow(const NZSPtr<ODDExecutePermission>& permission) {
    for (unsigned int i = 0; i < permissions.size(); i++) {
      if (permissions[i]->Allow(permission) == true) {
        return true;
      }
    }
    return false;
  }

  /*! \brief  Check if given permission is not violating (any of the) contained
              permissions.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                (any of the) contained permissions.
  */
  bool Allow(const NZSPtr<ODDPrintPermission>& permission) {
    for (unsigned int i = 0; i < permissions.size(); i++) {
      if (permissions[i]->Allow(permission) == true) {
        return true;
      }
    }
    return false;
  }

  /*! \brief  Check if given permission is not violating (any of the) contained
              permissions.

      \param  permission    input, permission to check.

      \returns  Boolean indicating if given permission is not violating
                (any of the) contained permissions.
  */
  bool Allow(const NZSPtr<OMADDExportPermission>& permission) {
    for (unsigned int i = 0; i < permissions.size(); i++) {
      if (permissions[i]->Allow(permission) == true) {
        return true;
      }
    }
    return false;
  }

  /*! \brief  Get agreement assets.

      \returns  Agreement assets.
  */
  const std::vector<NZSPtr<AgreementOEXAsset> >& GetAssets() const {
    return assets;
  }

  /*! \brief  Get permissions.

      \returns  Permissions.
  */
  const std::vector<NZSPtr<OEXPermission> >& GetPermissions() const {
    return permissions;
  }

private:
	std::vector<NZSPtr<AgreementOEXAsset> > assets;
	std::vector<NZSPtr<OEXPermission> > permissions;
};

/*! \brief  Rights.
*/
class OEXRights: public XmlData {
public:
  /*! \brief  Constructor.

      \param  ctx                       rights context.
      \param  agree                     agreement.
  */
  OEXRights(const NZSPtr<RightsOEXContext>& ctx, const NZSPtr<OEXAgreement>& agree):
    context(ctx), agreement(agree) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get rights context.

      \returns  Rights context.
  */
  const NZSPtr<RightsOEXContext>& GetContext() const {
    return context;
  }

  /*! \brief  Get agreement.

      \returns  Agreement.
  */
  const NZSPtr<OEXAgreement>& GetAgreement() const {
    return agreement;
  }

private:
	NZSPtr<RightsOEXContext> context;
	NZSPtr<OEXAgreement> agreement;
};

} // namespace DRMPlugin

#endif // !defined (RO_H)
