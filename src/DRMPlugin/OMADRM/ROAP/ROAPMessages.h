/** \file ROAPMessages.h

    OMA DRM message classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (ROAPMESSAGES_H)
#define ROAPMESSAGES_H

#include "RO.h"
#include <vector>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Version.
*/
class ROAPVersion: public XmlData {
public:
  /*! \brief  Constructor.

      \param  ver           version string.
  */
  ROAPVersion(const std::string& ver): val(ver) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Less than operator.

      \param  rhs             input, version.

      \returns  Boolean indicating if this version is less than rhs.
  */
  bool operator < (const ROAPVersion& rhs) const {
    return (val < rhs.val);
  }

  /*! \brief  Get version string.

      \returns  Version string.
  */
  const std::string& Get() const {
    return val;
  }

private:
	std::string val;
};

/*! \brief  Nonce.
*/
class ROAPNonce: public XmlData {
public:
  /*! \brief  Constructor.

      Length of non must be >= 14.

      \param  non             nonce string.

      If fails, throws ROAPException.
  */
  ROAPNonce(const Base64StringT& non): val(non) {
    if (val.GetLength() < 14) {
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

  /*! \brief  Less than operator.

      \param  rhs             input, nonce.

      \returns  Boolean indicating if this nonce is less than rhs.
  */
  bool operator < (const ROAPNonce& rhs) const {
    return (val < rhs.val);
  }

  /*! \brief  Equality operator.

      \param  rhs             input, nonce.

      \returns  Boolean indicating if this nonce is equal to rhs.
  */
  bool operator == (const ROAPNonce& rhs) const {
    return (val == rhs.val);
  }

  /*! \brief  Inequality operator.

      \param  rhs             input, nonce.

      \returns  Boolean indicating if this nonce is not equal to rhs.
  */
  bool operator != (const ROAPNonce& rhs) const {
    return (!(val == rhs.val));
  }

  /*! \brief  Get nonce string.

      \returns  Nonce string.
  */
  const Base64StringT& Get() const {
    return val;
  }

private:
	Base64StringT val;
};

/*! \brief  Base class for all ROAP requests.
*/
class ROAPRequest: public XmlData {
public:
  /*! \brief  Get trigger nonce.

      \returns  Trigger nonce.
  */
	virtual const SPtr<ROAPNonce>& GetTriggerNonce() const = 0;
};

/*! \brief  Response status.
*/
class ROAPStatus: public XmlData {
public:
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const = 0;
};

/*! \brief  Success status.
*/
class SuccessROAPStatus: public ROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "Success";
  }
};

/*! \brief  Unsuccess status.
*/
class UnsuccessROAPStatus: public ROAPStatus {
};

/*! \brief  Abort status.
*/
class AbortROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "Abort";
  }
};

/*! \brief  Not supported status.
*/
class NotSupportedROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "NotSupported";
  }
};

/*! \brief  Access denied status.
*/
class AccessDeniedROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "AccessDenied";
  }
};

/*! \brief  Not found status.
*/
class NotFoundROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "NotFound";
  }
};

/*! \brief  Malformed request status.
*/
class MalformedRequestROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "MalformedRequest";
  }
};

/*! \brief  Unknown critical extension status.
*/
class UnknownCriticalExtensionROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "UnknownCriticalExtension";
  }
};

/*! \brief  Unsupported version status.
*/
class UnsupportedVersionROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "UnsupportedVersion";
  }
};

/*! \brief  Unsupported algorithm status.
*/
class UnsupportedAlgorithmROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "UnsupportedAlgorithm";
  }
};

/*! \brief  No certificate chain status.
*/
class NoCertificateChainROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "NoCertificateChain";
  }
};

/*! \brief  Invalid certificate chain status.
*/
class InvalidCertificateChainROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "InvalidCertificateChain";
  }
};

/*! \brief  Trusted root certificate not present status.
*/
class TrustedRootCertificateNotPresentROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "TrustedRootCertificateNotPresent";
  }
};

/*! \brief  Signature error status.
*/
class SignatureErrorROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "SignatureError";
  }
};

/*! \brief  Device time error status.
*/
class DeviceTimeErrorROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "DeviceTimeError";
  }
};

/*! \brief  Not registered status.
*/
class NotRegisteredROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "NotRegistered";
  }
};

/*! \brief  Invalid DCF hash status.
*/
class InvalidDCFHashROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "InvalidDCFHash";
  }
};

/*! \brief  Invalid domain status.
*/
class InvalidDomainROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "InvalidDomain";
  }
};

/*! \brief  Domain full status.
*/
class DomainFullROAPStatus: public UnsuccessROAPStatus {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
  
  /*! \brief  Get message describing status.

      \returns  Message describing status.
  */
  virtual std::string GetMessage() const {
    return "DomainFull";
  }
};

/*! \brief  Base class for all ROAP responses.
*/
class ROAPResponse: public XmlData {
public:
  /*! \brief  Get status.

      \returns  Status.
  */
	virtual NZSPtr<ROAPStatus> GetStatus() const = 0;
};

/*! \brief  ROAP extension.
*/
class ROAPExtension: public XmlData {
public:
  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const = 0;
};

/*! \brief  No need for OCSPResponse to be sent (not critical).

	  Mainly for use in the 2-pass RO Request protocol
*/
class NoOCSPResponseExtension: public ROAPExtension {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return false;
  }
};

/*! \brief  No need for OCSPResponse to be sent (critical).

	  Mainly for use in the 2-pass RO Request protocol
*/
class CriticalNoOCSPResponseExtension: public NoOCSPResponseExtension {
public:
  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return true;
  }
};

/*! \brief  Basic key identifier.
*/
class ROAPKeyIdentifier: public XmlData {
public:
  /*! \brief  Less than operator.

      \param  rhs           input, ROAP key identifier.

      \returns  Boolean indicating if this identifier is less than rhs, by
                comparing encoded XML strings.
  */
  bool operator < (const ROAPKeyIdentifier& rhs) const {
    return (XmlEncode() < rhs.XmlEncode());
  }

  /*! \brief  Equality operator.

      \param  rhs           input, ROAP key identifier.

      \returns  Boolean indicating if this identifier is equal to rhs, by
                comparing encoded XML strings.
  */
  bool operator == (const ROAPKeyIdentifier& rhs) const {
    return (XmlEncode() == rhs.XmlEncode());
  }

  /*! \brief  Inequality operator.

      \param  rhs           input, ROAP key identifier.

      \returns  Boolean indicating if this identifier is not equal to rhs, by
                comparing encoded XML strings.
  */
  bool operator != (const ROAPKeyIdentifier& rhs) const {
    return (!((*this) == rhs));
  }
};

/*! \brief  No need for receiving party's certificate chain to be sent (not critical).

	  Mainly for use in the 2-pass RO Request protocol
*/
class PeerKeyIdExtension: public ROAPExtension {
public:
  /*! \brief  Constructor.

      \param  key             key identifier.
  */
  PeerKeyIdExtension(const SPtr<ROAPKeyIdentifier>& key): identifier(key) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return false;
  }

  /*! \brief  Get key identifier.

      \returns  Key identifier.
  */
  const SPtr<ROAPKeyIdentifier>& GetIdentifier() const {
    return identifier;
  }

protected:
	SPtr<ROAPKeyIdentifier> identifier;
};

/*! \brief  No need for receiving party's certificate chain to be sent (critical).

	  Mainly for use in the 2-pass RO Request protocol
*/
class CriticalPeerKeyIdExtension: public PeerKeyIdExtension {
public:
  /*! \brief  Constructor.

      \param  key             key identifier.
  */
  CriticalPeerKeyIdExtension(const SPtr<ROAPKeyIdentifier>& key):
    PeerKeyIdExtension(key) {
  }

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return true;
  }
};

/*! \brief  No need for inclusion of OCSP responder certificates (not critical).

	  Mainly for use in the 2-pass RO Request protocol
*/
class OCSPResponderKeyIdExtension: public ROAPExtension {
public:
  /*! \brief  Constructor.

      \param  key           key identifier.
  */
  OCSPResponderKeyIdExtension(const NZSPtr<ROAPKeyIdentifier>& key): identifier(key) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return false;
  }

  /*! \brief  Get key identifier.

      \returns  Key identifier.
  */
  const NZSPtr<ROAPKeyIdentifier>& GetIdentifier() const {
    return identifier;
  }

protected:
	NZSPtr<ROAPKeyIdentifier> identifier;
};

/*! \brief  No need for inclusion of OCSP responder certificates (not critical).

	  Mainly for use in the 2-pass RO Request protocol
*/
class CriticalOCSPResponderKeyIdExtension: public OCSPResponderKeyIdExtension {
public:
  /*! \brief  Constructor.

      \param  key           key identifier.
  */
  CriticalOCSPResponderKeyIdExtension(const NZSPtr<ROAPKeyIdentifier>& key):
    OCSPResponderKeyIdExtension(key) {
  }

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return true;
  }
};

/*! \brief  Device details data.
*/
class DeviceDetailsData: public GC {
public:
  /*! \brief  Constructor.

      \param  man           manufacturer string.
      \param  mod           model string.
      \param  ver           version string.
  */
	DeviceDetailsData(const std::string& man, const std::string& mod, const
    std::string& ver): manufacturer(man), model(mod), version(ver) {
  }

  /*! \brief  Encode as XML string.

      \returns  Encoded XML string.
  */
	std::string XmlEncode() const;

  /*! \brief  Get manufacturer.

      \returns  Manufacturer.
  */
  const std::string& GetManufacturer() const {
    return manufacturer;
  }

  /*! \brief  Get model.

      \returns  Model.
  */
  const std::string& GetModel() const {
    return model;
  }

  /*! \brief  Get version string.

      \returns  Version string.
  */
  const std::string& GetVersion() const {
    return version;
  }

private:
	std::string manufacturer;
	std::string model;
	std::string version;
};

/*! \brief  Device details (not critical).

	  Used in ROAP-RIHello and ROAP-RegistrationRequest messages.
*/
class DeviceDetailsExtension: public ROAPExtension {
public:
  /*! \brief  Constructor.

      \param  det             device details data.
  */
  DeviceDetailsExtension(const SPtr<DeviceDetailsData>& det): details(det) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return false;
  }

  /*! \brief  Get device details data.

      \returns  Device details data.
  */
  const SPtr<DeviceDetailsData>& Details() const {
    return details;
  }

protected:
	SPtr<DeviceDetailsData> details;
};

/*! \brief  Device details (critical).

	  Used in ROAP-RIHello and ROAP-RegistrationRequest messages.
*/
class CriticalDeviceDetailsExtension: public DeviceDetailsExtension {
public:
  /*! \brief  Constructor.

      \param  det             device details data.
  */
  CriticalDeviceDetailsExtension(const SPtr<DeviceDetailsData>& det):
    DeviceDetailsExtension(det) {
  }

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return true;
  }
};

/*! \brief  Transaction identifier data.
*/
class TransIdentifierData: public GC {
public:
  /*! \brief  Constructor.

      Size of idval must be 16.

      \param  conidval              content identifier.
      \param  idval                 identifier string.

      If fails, throws ROAPException.
  */
  TransIdentifierData(const NZSPtr<URIValue>& conidval, const std::string& idval):
      contentID(conidval), id(idval) {
    if (id.size() != 16) {
      throw ROAPException();
    }
  }

  /*! \brief  Encode as XML string.

      \returns  Encoded XML string.
  */
	std::string XmlEncode() const;

  /*! \brief  Get content identifier string.

      \returns  Content identifier string.
  */
  const NZSPtr<URIValue>& GetContentID() const {
    return contentID;
  }

  /*! \brief  Get identifier string.

      \returns  Identifier string.
  */
  const std::string& GetID() const {
    return id;
  }

private:
	NZSPtr<URIValue> contentID;
	std::string id;
};

/*! \brief  Loyalty program information (not critical).

	  Mainly for use in 2-pass RO Request protocol.
*/
class TransactionIdExtension: public ROAPExtension {
public:
  /*! \brief  Constructor.

      Size of transaction data vector must be >= 1.

      \param  trans           transaction data vector.

      If fails, throws ROAPException.
  */
  TransactionIdExtension(const std::vector<NZSPtr<TransIdentifierData> >& trans):
      transactions(trans) {
    if (transactions.size() < 1) {
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

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return false;
  }

  /*! \brief  Get transactions.

      \returns  Transactions.
  */
  const std::vector<NZSPtr<TransIdentifierData> >& GetTransactions() const {
    return transactions;
  }

protected:
	std::vector<NZSPtr<TransIdentifierData> > transactions;
};

/*! \brief  Loyalty program information (critical).

	  Mainly for use in 2-pass RO Request protocol.
*/
class CriticalTransactionIdExtension: public TransactionIdExtension {
public:
  /*! \brief  Constructor.

      Size of transaction data vector must be >= 1.

      \param  trans           transaction data vector.

      If fails, throws ROAPException.
  */
  CriticalTransactionIdExtension(const std::vector<NZSPtr<TransIdentifierData> >&
    trans): TransactionIdExtension(trans) {
  }
	
  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return true;
  }
};

/*! \brief  Certificate chain caching capabilities extension (not critical).

	  Device signals support of the extension, RI signals if it will store
	  the device's certificates.
*/
class CertCachingExtension: public ROAPExtension {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return false;
  }
};

/*! \brief  Certificate chain caching capabilities extension (critical).

	  Device signals support of the extension, RI signals if it will store
	  the device's certificates.
*/
class CriticalCertCachingExtension: public CertCachingExtension {
public:
  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return true;
  }
};

/*! \brief  Support for hash chains in domains (not critical).
*/
class HashChainSupportExtension: public ROAPExtension {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return false;
  }
};

/*! \brief  Support for hash chains in domains (critical).
*/
class CriticalHashChainSupportExtension: public HashChainSupportExtension {
public:
  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return true;
  }
};

/*! \brief  Device does not consider itself a member of the domain (not critical).
*/
class NotDomainMemberExtension: public ROAPExtension {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return false;
  }
};

/*! \brief  Device does not consider itself a member of the domain (critical).
*/
class CriticalNotDomainMemberExtension: public NotDomainMemberExtension {
public:
  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return true;
  }
};

/*! \brief  Domain name white list (not critical).

    Rights issuer can specify up to 5 domain names for silent/preview
    rights security.
*/
class DomainNameWhiteListExtension: public ROAPExtension {
public:
  /*! \brief  Constructor.

      Size of domain names vector must be >= 1 and <= 5.

      \param  domains         domain names vector.

      If fails, throws ROAPException.
  */
  DomainNameWhiteListExtension(const std::vector<std::string>& domains):
      names(domains) {
    if ((names.size() < 1) || (names.size() > 5)) {
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

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return false;
  }

  /*! \brief  Get domain names.
  
      \returns  Domain names.
  */
  const std::vector<std::string>& GetNames() const {
    return names;
  }

protected:
	std::vector<std::string> names;
};

/*! \brief  Domain name white list (critical).

    Rights issuer can specify up to 5 domain names for silent/preview
    rights security.
*/
class CriticalDomainNameWhiteListExtension: public DomainNameWhiteListExtension {
public:
  /*! \brief  Constructor.

      Size of domain names vector must be >= 1 and <= 5.

      \param  domains         domain names vector.

      If fails, throws ROAPException.
  */
  CriticalDomainNameWhiteListExtension(const std::vector<std::string>& domains):
    DomainNameWhiteListExtension(domains) {
  }

  /*! \brief  Get critical flag.

      \returns  Critical flag.
  */
  virtual bool IsCritical() const {
    return true;
  }
};

/*! \brief  Identifier.
*/
class ROAPIdentifier: public XmlData {
public:
  /*! \brief  Constructor.

      \param  key             key identifier.
  */
  ROAPIdentifier(const NZSPtr<ROAPKeyIdentifier>& key): keyID(key) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Less than operator.

      \param  rhs           input, identifier.

      \returns  Boolean indicating if this identifier is less then rhs.
  */
  bool operator < (const ROAPIdentifier& rhs) const {
    return ((*keyID) < (*(rhs.keyID)));
  }

  /*! \brief  Equality operator.

      \param  rhs           input, identifier.

      \returns  Boolean indicating if this identifier is equal to rhs.
  */
  bool operator == (const ROAPIdentifier& rhs) const {
    return ((*keyID) == (*(rhs.keyID)));
  }

  /*! \brief  Inequality operator.

      \param  rhs           input, identifier.

      \returns  Boolean indicating if this identifier is not equal to rhs.
  */
  bool operator != (const ROAPIdentifier& rhs) const {
    return (!((*this) == rhs));
  }

  /*! \brief  Get key identifier.

      \returns  Key identifier.
  */
  const NZSPtr<ROAPKeyIdentifier>& GetKeyID() const {
    return keyID;
  }

private:
	NZSPtr<ROAPKeyIdentifier> keyID;
};

/*! \brief  Hash of complete DER-encoded subject public key info field.

    Subject public key info field is taken from key holder's certificate.
    Default value for algorithm is http://www.w3.org/2000/09/xmldsig#sha1.
*/
class X509SPKIHash: public ROAPKeyIdentifier {
public:
  /*! \brief  Constructor.

      \param  hstring         hash string.
  */
  X509SPKIHash(const Base64StringT& hstring): hash(hstring) {
  }

  /*! \brief  Copy constructor.

      \param  rhs         hash container.
  */
  X509SPKIHash(const X509SPKIHash& rhs): hash(rhs.hash) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get hash string.

      \returns  Hash string.
  */
  const Base64StringT& GetHash() const {
    return hash;
  }

  /*! \brief  Get hash algorithm.

      \returns  Hash algorithm URI value.
  */
	NZSPtr<URIValue> GetAlgorithm() const {
    return new URIValue("http://www.w3.org/2000/09/xmldsig#sha1");
  }

private:
	Base64StringT hash;
};

/*! \brief  Domain identifier.
*/
class ROAPDomainIdentifier: public XmlData {
public:
  /*! \brief  Constructor.

      \param  idval           identifier string.
  */
  ROAPDomainIdentifier(const std::string& idval): id(idval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Less than operator.

      \param  rhs           input, domain identifier.

      \returns  Boolean indicating if this identifier is less then rhs.
  */
  bool operator < (const ROAPDomainIdentifier& rhs) const {
    return (id < rhs.id);
  }

  /*! \brief  Equality operator.

      \param  rhs           input, domain identifier.

      \returns  Boolean indicating if this identifier is equal to rhs.
  */
  bool operator == (const ROAPDomainIdentifier& rhs) const {
    return (id == rhs.id);
  }

  /*! \brief  Inequality operator.

      \param  rhs           input, domain identifier.

      \returns  Boolean indicating if this identifier is less then rhs.
  */
  bool operator != (const ROAPDomainIdentifier& rhs) const {
    return (id != rhs.id);
  }

  /*! \brief  Get identifier string.

      \returns  Identifier string.
  */
  const std::string& Get() const {
    return id;
  }

private:
	std::string id;
};

/*!	\brief Date and time.
*/
class DateTime: public XmlData {
};

/*! \brief  Explicitly defined date and time.
*/
class DefDateTime: public DateTime {
public:
  /*! \brief  Constructor.

      \param  t       UTCTime time.
  */
  DefDateTime(const UTCTime& t): time(t) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get time.

      \returns  Time.
  */
  const UTCTime& GetTime() const {
    return time;
  }

private:
  UTCTime time;
};

/*! \brief  Undefined date and time.
*/
class UndefDateTime: public DateTime {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
};

/*! \brief  Infinite date and time.
*/
class InfDateTime: public DateTime {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
};

/*! \brief  Rights object payload stateful info.
*/
class ROAPROPayloadStatefulInfo: public GC {
public:
  /*! \brief  Constructor.

      \param  flag          stateful flag.
  */
  ROAPROPayloadStatefulInfo(bool flag): stateful(flag) {
  }

  /*! \brief  Encode as XML string.

      \returns  Encoded XML string.
  */
	std::string XmlEncode() const;

  /*! \brief  Get stateful flag.

      \returns  Stateful flag.
  */
  bool GetStateful() const {
    return stateful;
  }

private:
  bool stateful;
};

/*! \brief  Rights object payload rights issuer URL info.
*/
class ROAPROPayloadRIURLInfo: public GC {
public:
  /*! \brief  Constructor.

      \param  urival              URI value.
  */
  ROAPROPayloadRIURLInfo(const NZSPtr<URIValue>& urival): riURL(urival) {
  }

  /*! \brief  Get URI value.

      \returns  URI value.
  */
  const NZSPtr<URIValue>& GetURL() const {
    return riURL;
  }

private:
  NZSPtr<URIValue> riURL;
};

/*! \brief  Rights objects payload.
*/
class ROAPROPayload: public XmlData {
public:
  /*! \brief  Constructor.

      \param  riidval                 rights issuer identifier.
      \param  rightval                rights.
      \param  timeval                 time.
      \param  enc                     encrypted key.
      \param  ver                     version.
      \param  idval                   identifier.
      \param  sinfo                   stateful info.
      \param  urlinfo                 URL info.
  */
	ROAPROPayload(const NZSPtr<ROAPIdentifier>& riidval, const NZSPtr<OEXRights>&
    rightval, const SPtr<DefDateTime>& timeval, const NZSPtr<XencEncryptedKey>& enc,
    const NZSPtr<ROAPVersion>& ver, const NZSPtr<IDValue>& idval,
    const SPtr<ROAPROPayloadStatefulInfo>& sinfo,
    const SPtr<ROAPROPayloadRIURLInfo>& urlinfo): riID(riidval), rights(rightval),
    time(timeval), key(enc), version(ver), id(idval), statefulInfo(sinfo),
    riURLInfo(urlinfo) {
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get rights.

      \returns  Rights.
  */
  const NZSPtr<OEXRights>& GetRights() const {
    return rights;
  }

  /*! \brief  Get time.

      \returns  Time.
  */
  const SPtr<DefDateTime>& GetTime() const {
    return time;
  }

  /*! \brief  Get encrypted key.

      \returns  Encrypted key.
  */
  const NZSPtr<XencEncryptedKey>& GetEncKey() const {
    return key;
  }

  /*! \brief  Get version.

      \returns  Version.
  */
  const NZSPtr<ROAPVersion>& GetVersion() const {
    return version;
  }

  /*! \brief  Get identifier.

      \returns  Identifier.
  */
  const NZSPtr<IDValue>& GetID() const {
    return id;
  }

  /*! \brief  Get stateful info.

      \returns  Stateful info.
  */
  const SPtr<ROAPROPayloadStatefulInfo>& GetStatefulInfo() const {
    return statefulInfo;
  }

  /*! \brief  Get rights issuer URL info.

      \returns  Rights issuer URL info.
  */
  const SPtr<ROAPROPayloadRIURLInfo>& GetRightsIssuerURLInfo() const {
    return riURLInfo;
  }

  /*! \brief  Get domain rights objects indicator.

      \returns  Domain rights objects indicator.
  */
  virtual bool GetDomainFlag() const = 0;

protected:
	NZSPtr<ROAPIdentifier> riID;
	NZSPtr<OEXRights> rights;
	SPtr<DefDateTime> time;
	NZSPtr<XencEncryptedKey> key;
  NZSPtr<ROAPVersion> version;
  NZSPtr<IDValue> id;
  SPtr<ROAPROPayloadStatefulInfo> statefulInfo;
  SPtr<ROAPROPayloadRIURLInfo> riURLInfo;
};

/*!	\brief  Domain rights object payload.
*/
class DomainROAPROPayload: public ROAPROPayload {
public:
  /*! \brief  Constructor.

      \param  riidval                 rights issuer identifier.
      \param  rightval                rights.
      \param  sig                     signature.
      \param  timeval                 time.
      \param  enc                     encrypted key.
      \param  ver                     version.
      \param  idval                   identifier.
      \param  sinfo                   stateful info.
      \param  urlinfo                 URL info.
  */
	DomainROAPROPayload(const NZSPtr<ROAPIdentifier>& riidval,
    const NZSPtr<OEXRights>& rightval, const NZSPtr<DSSignature>& sig,
    const SPtr<DefDateTime>& timeval, const NZSPtr<XencEncryptedKey>& enc,
    const NZSPtr<ROAPVersion>& ver, const NZSPtr<IDValue>& idval,
    const SPtr<ROAPROPayloadStatefulInfo>& sinfo,
    const SPtr<ROAPROPayloadRIURLInfo>& urlinfo): ROAPROPayload(riidval, rightval,
    timeval, enc, ver, idval, sinfo, urlinfo), signature(sig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const NZSPtr<DSSignature>& GetSignature() const {
    return signature;
  }

  /*! \brief  Get domain rights objects indicator.

      \returns  Domain rights objects indicator.
  */
  virtual bool GetDomainFlag() const {
    return true;
  }

private:
	NZSPtr<DSSignature> signature;
};

/*! \brief  Device (non-domain) rights object payload.
*/
class DeviceROAPROPayload: public ROAPROPayload {
public:
  /*! \brief  Constructor.

      \param  riidval                 rights issuer identifier.
      \param  rightval                rights.
      \param  sig                     signature.
      \param  timeval                 time.
      \param  enc                     encrypted key.
      \param  ver                     version.
      \param  idval                   identifier.
      \param  sinfo                   stateful info.
      \param  urlinfo                 URL info.
  */
	DeviceROAPROPayload(const NZSPtr<ROAPIdentifier>& riidval,
    const NZSPtr<OEXRights>& rightval, const SPtr<DSSignature>& sig,
    const SPtr<DefDateTime>& timeval, const NZSPtr<XencEncryptedKey>& enc,
    const NZSPtr<ROAPVersion>& ver, const NZSPtr<IDValue>& idval,
    const SPtr<ROAPROPayloadStatefulInfo>& sinfo,
    const SPtr<ROAPROPayloadRIURLInfo>& urlinfo): ROAPROPayload(riidval, rightval,
    timeval, enc, ver, idval, sinfo, urlinfo), signature(sig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const SPtr<DSSignature>& GetSignature() const {
    return signature;
  }

  /*! \brief  Get domain rights objects indicator.

      \returns  Domain rights objects indicator.
  */
  virtual bool GetDomainFlag() const {
    return false;
  }

private:
	SPtr<DSSignature> signature;
};

/*! \brief  Protected rights objects.
*/
class ROAPProtectedRO: public XmlData {
public:
  /*! \brief  Constructor.

      \param  ropayload             rights objects payload.
      \param  sig                   signature.
  */
  ROAPProtectedRO(const NZSPtr<ROAPROPayload>& ropayload, const NZSPtr<DSSignature>&
    sig): payload(ropayload), signature(sig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get rights objects payload.

      \returns  Rights objects payload.
  */
  const NZSPtr<ROAPROPayload>& GetROPayload() const {
    return payload;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const NZSPtr<DSSignature>& GetSignature() const {
    return signature;
  }

private:
	NZSPtr<ROAPROPayload> payload;
	NZSPtr<DSSignature> signature;
};

/*! \brief  Server info.
*/
class ROAPServerInfo: public XmlData {
public:
  /*! \brief  Constructor.

      \param  infoval             server info string.
  */
  ROAPServerInfo(const Base64StringT& infoval): val(infoval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Equality operator.

      \param  rhs             input, server info.

      \returns  Boolean indicating if this server info is equal to rhs.
  */
  bool operator == (const ROAPServerInfo& rhs) {
    return (val == rhs.val);
  }

  /*! \brief  Get server info string.

      \returns  Server info string.
  */
  const Base64StringT& Get() const {
    return val;
  }

private:
  Base64StringT val;
};

/*! \brief  Session identifier.
*/
class ROAPSessionID: public GC {
public:
  /*! \brief  Constructor.

      \param  idval             identifier string.

      If fails, throws ROAPException.
  */
//  ROAPSessionID(const Base64StringT& idval): val(idval) {
  ROAPSessionID(const std::string& idval): val(idval) {
    for (unsigned int i = 0; i < val.size(); i++) {
      if (!((('0' <= val[i]) && (val[i] <= '9')) || (('A' <= val[i]) && (val[i] <= 'F')))) {
        throw ROAPException();
      }
    }
  }

  /*! \brief  Less than operator.

      \param  rhs             input, session identifier.

      \returns  Boolean indicating if this session identifier is less than rhs.
  */
  bool operator < (const ROAPSessionID& rhs) const {
    return (val < rhs.val);
  }

  /*! \brief  Equality operator.

      \param  rhs             input, session identifier.

      \returns  Boolean indicating if this session identifier is equald to rhs.
  */
  bool operator == (const ROAPSessionID& rhs) const {
    return (val == rhs.val);
  }

  /*! \brief  Get identifier string.

      \returns  Identifier string.
  */
//  const Base64StringT& Get() const {
  const std::string& Get() const {
    return val;
  }

private:
//  Base64StringT val;
  std::string val;
};

/*! \brief  Key identifiers.
*/
class ROAPKeyIdentifiers: public XmlData {
public:
  /*! \brief  Constructor.

      \param  ids             identifiers vector.
  */
  ROAPKeyIdentifiers(const std::vector<NZSPtr<ROAPKeyIdentifier> >& ids):
    identifiers(ids) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifiers vector.

      \returns  Identifiers vector.
  */
  const std::vector<NZSPtr<ROAPKeyIdentifier> >& GetIdentifiers() const {
    return identifiers;
  }

private:
  std::vector<NZSPtr<ROAPKeyIdentifier> > identifiers;
};

/*! \brief  Certificate chain.
*/
class ROAPCertificateChain: public XmlData {
public:
  /*! \brief  Constructor.

      \param  chain         certificate chain.

      Size of chain vector must be at least 1. If fails, throws ROAPException.
  */
  ROAPCertificateChain(const std::vector<Base64StringT>& chain): certs(chain) {
    if (certs.size() == 0) {
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

  /*! \brief  Get certificates.

      \returns  Certificates.
  */
  const std::vector<Base64StringT>& GetCertificates() const {
    return certs;
  }

  /*! \brief  Equality operator.

      \param  rhs         input, certificate chain.

      \returns  Boolean indicating whether contained chains are equal.
  */
  bool operator == (const ROAPCertificateChain& rhs) const {
    if (certs.size() != rhs.GetCertificates().size()) {
      return false;
    }
    for (unsigned int i = 0; i < certs.size(); i++) {
      if (certs[i] != rhs.GetCertificates()[i]) {
        return false;
      }
    }
    return true;
	}

private:
	std::vector<Base64StringT> certs;
};

/*! \brief  Extensions for device hello message.
*/
class DeviceHelloExtensions: public XmlData {
public:
  /*! \brief  Constructor.

      \param  ccaching                  certificate caching.
  */
  DeviceHelloExtensions(const NZSPtr<CertCachingExtension>& ccaching):
    caching(ccaching) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get certificate caching.

      \returns  Certificate caching.
  */
  const NZSPtr<CertCachingExtension>& GetCertCaching() const {
    return caching;
  }

protected:
  NZSPtr<CertCachingExtension> caching;
};

/*! \brief  Device hello message.
*/
class DeviceHelloRequest: public ROAPRequest {
public:
  /*! \brief  Constructor.

      Size of device identifiers vector must be >= 1.

      \param  tnonce                  trigger nonce.
      \param  ver                     version.
      \param  idvals                  device identifiers vector.
      \param  algs                    supported algorithms.
      \param  exts                    extensions.

      If fails, throws ROAPException.
  */
	DeviceHelloRequest(const SPtr<ROAPNonce>& tnonce, const NZSPtr<ROAPVersion>& ver,
      const std::vector<NZSPtr<ROAPIdentifier> >& idvals, const
      std::vector<NZSPtr<URIValue> >& algs, const SPtr<DeviceHelloExtensions>& exts):
      nonce(tnonce), version(ver), deviceIDs(idvals), algorithms(algs),
      extensions(exts) {
    if (deviceIDs.size() == 0) {
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

  /*! \brief  Get trigger nonce.

      \returns  Trigger nonce.
  */
  const SPtr<ROAPNonce>& GetTriggerNonce() const {
    return nonce;
  }

  /*! \brief  Get version.

      \returns  Version.
  */
  const NZSPtr<ROAPVersion>& GetVersion() const {
    return version;
  }

  /*! \brief  Get device identifiers.

      \returns  Device identifiers.
  */
  const std::vector<NZSPtr<ROAPIdentifier> >& GetDeviceIDs() const {
    return deviceIDs;
  }

  /*! \brief  Get supported algorithms.

      \returns  Supported algorithms.
  */
  const std::vector<NZSPtr<URIValue> >& GetSupportedAlgs() const {
    return algorithms;
  }

  /*! \brief  Get extensions.

      \returns  Extensions.
  */
  SPtr<DeviceHelloExtensions> GetExtensions() const {
    return extensions;
  }

protected:
  SPtr<ROAPNonce> nonce;
	NZSPtr<ROAPVersion> version;
	std::vector<NZSPtr<ROAPIdentifier> > deviceIDs;
	std::vector<NZSPtr<URIValue> > algorithms;
	NZSPtr<DeviceHelloExtensions> extensions;
};

/*! \brief  Extensions for rights issuer hello message.
*/
class RIHelloExtensions: public XmlData {
public:
  /*! \brief  Constructor.

      \param  peerid                peer key identifier.
      \param  ccaching              certificate caching.
      \param  ddetails              device details.

      If fails, throws ROAPException.
  */
  RIHelloExtensions(const SPtr<PeerKeyIdExtension>& peerid, const
      SPtr<CertCachingExtension>& ccaching, const SPtr<DeviceDetailsExtension>&
      ddetails): peerKeyId(peerid), caching(ccaching), details(ddetails) {
    if ((peerKeyId == 0) && (caching == 0) && (details == 0)) {
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

  /*! \brief  Get peer key identifier.

      \returns  Peer key identifier.
  */
  const SPtr<PeerKeyIdExtension>& GetPeerKeyID() const {
    return peerKeyId;
  }

  /*! \brief  Get certificate caching.

      \returns  Certificate caching.
  */
  const SPtr<CertCachingExtension>& GetCertCaching() const {
    return caching;
  }

  /*! \brief  Get device details.

      \returns  Device details.
  */
  const SPtr<DeviceDetailsExtension>& GetDeviceDetails() const {
    return details;
  }

protected:
  SPtr<PeerKeyIdExtension> peerKeyId;
  SPtr<CertCachingExtension> caching;
  SPtr<DeviceDetailsExtension> details;
};

/*! \brief  Rights issuer hello message.
*/
class RIHelloResponse: public ROAPResponse {
};

/*! \brief  Successful rights issuer hello message.
*/
class SuccessRIHello: public RIHelloResponse {
public:
  /*! \brief  Constructor.

      \param  ver                   version.
      \param  idval                 rights issuer identifier.
      \param  algs                  selected algorithms.
      \param  nonceval              nonce.
      \param  trust                 trusted authorities.
      \param  inf                   server info.
      \param  exts                  extensions.
      \param  sessid                session identifier.
  */
	SuccessRIHello(const NZSPtr<ROAPVersion>& ver, const NZSPtr<ROAPIdentifier>& idval,
    const std::vector<NZSPtr<URIValue> >& algs, const NZSPtr<ROAPNonce>&
    nonceval, const SPtr<ROAPKeyIdentifiers>& trust, const SPtr<ROAPServerInfo>& inf,
    const SPtr<RIHelloExtensions>& exts, const NZSPtr<ROAPSessionID>& sessid):
    version(ver), riID(idval), algorithms(algs), nonce(nonceval), trusted(trust),
    info(inf), extensions(exts), sessionID(sessid) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get status.

      \returns  Status.
  */
  virtual NZSPtr<ROAPStatus> GetStatus() const {
    return new SuccessROAPStatus();
  }

  /*! \brief  Get version.

      \returns  Version.
  */
  const NZSPtr<ROAPVersion>& GetVersion() const {
    return version;
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get selected algorithms.

      \returns  Selected algorithms.
  */
  const std::vector<NZSPtr<URIValue> >& GetSelectedAlgs() const {
    return algorithms;
  }

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  const NZSPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

  /*! \brief  Get trusted authorities.

      \returns  Trusted authorities.
  */
  const	SPtr<ROAPKeyIdentifiers>& GetTrustedAuthorities() const {
    return trusted;
  }

  /*! \brief  Get server info.

      \returns  Server info.
  */
  const SPtr<ROAPServerInfo>& GetServerInfo() const {
    return info;
  }

  /*! \brief  Get extensions.

      \returns  Extensions.
  */
  SPtr<RIHelloExtensions> GetExtensions() const {
    return extensions;
  }

  /*! \brief  Get session identifier.

      \returns  Session identifier.
  */
  const NZSPtr<ROAPSessionID>& GetSessionID() const {
    return sessionID;
  }

protected:
	NZSPtr<ROAPVersion> version;
	NZSPtr<ROAPIdentifier> riID;
	std::vector<NZSPtr<URIValue> > algorithms;
	NZSPtr<ROAPNonce> nonce;
	SPtr<ROAPKeyIdentifiers> trusted;
	SPtr<ROAPServerInfo> info;
	SPtr<RIHelloExtensions> extensions;
	NZSPtr<ROAPSessionID> sessionID;
};

/*! \brief  Unsuccessful rights issuer hello message.
*/
class UnsuccessRIHello: public RIHelloResponse {
public:
  /*! \brief  Constructor.

      \param  stat              unsuccessful status.
  */
  UnsuccessRIHello(const NZSPtr<UnsuccessROAPStatus>& stat): status(stat) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get status.

      \returns  Status.
  */
  virtual NZSPtr<ROAPStatus> GetStatus() const {
    return (UnsuccessROAPStatus*)status;
  }

  /*! \brief  Get unsuccess status.

      \returns  Unsuccess status.
  */
  const NZSPtr<UnsuccessROAPStatus>& GetUnsuccessStatus() const {
    return status;
  }

protected:
  NZSPtr<UnsuccessROAPStatus> status;
};

/*! \brief  Extensions for registration request message.
*/
class RegRequestExtensions: public XmlData {
public:
  /*! \brief  Constructor.

      \param  peerid                  peer key identifier.
      \param  ddetails                device details.
      \param  noocsp                  no OCSP response.
      \param  ocspkeyid               OCSP responder key identifier.

      If fails, throws ROAPException.
  */
  RegRequestExtensions(const SPtr<PeerKeyIdExtension>& peerid,
      const SPtr<DeviceDetailsExtension>& ddetails,
      const SPtr<NoOCSPResponseExtension>& noocsp,
      const SPtr<OCSPResponderKeyIdExtension>& ocspkeyid): peerKeyId(peerid),
      details(ddetails), noOCSP(noocsp), ocspResponderKeyId(ocspkeyid) {
    if ((peerKeyId == 0) && (details == 0) && (noOCSP == 0) && (ocspResponderKeyId == 0)) {
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

  /*! \brief  Get peer key identifier.

      \returns  Peer key identifier.
  */
  const SPtr<PeerKeyIdExtension>& GetPeerKeyId() const {
    return peerKeyId;
  }

  /*! \brief  Get device details.

      \returns  Device details.
  */
  const SPtr<DeviceDetailsExtension>& GetDeviceDetails() const {
    return details;
  }

  /*! \brief  Get no OCSP response.

      \returns  No OCSP response.
  */
  const SPtr<NoOCSPResponseExtension>& GetNoOCSPResponse() const {
    return noOCSP;
  }

  /*! \brief  Get OCSP responder key identifier.

      \returns  OCSP responder key identifier.
  */
  const SPtr<OCSPResponderKeyIdExtension>& GetOCSPResponderKeyId() const {
    return ocspResponderKeyId;
  }

protected:
  SPtr<PeerKeyIdExtension> peerKeyId;
  SPtr<DeviceDetailsExtension> details;
  SPtr<NoOCSPResponseExtension> noOCSP;
  SPtr<OCSPResponderKeyIdExtension> ocspResponderKeyId;
};

/*! \brief  Registration request message.
*/
class RegRequest: public ROAPRequest {
public:
  /*! \brief  Constructor.

      \param  tnonce                  trigger nonce.
      \param  dnonce                  device nonce.
      \param  dtime                   time.
      \param  cchain                  certificate chain.
      \param  trust                   trusted authorities.
      \param  inf                     server info.
      \param  exts                    extensions.
      \param  sig                     signature.
      \param  sessid                  session identifier.
  */
	RegRequest(const SPtr<ROAPNonce>& tnonce, const NZSPtr<ROAPNonce>& dnonce,
    const NZSPtr<DateTime>& dtime, const SPtr<ROAPCertificateChain>& cchain,
    const SPtr<ROAPKeyIdentifiers>& trust, const SPtr<ROAPServerInfo>& inf,
		const SPtr<RegRequestExtensions>& exts, const Base64StringT& sig,
    const NZSPtr<ROAPSessionID>& sessid): tNonce(tnonce), dNonce(dnonce),
    time(dtime), chain(cchain), trusted(trust), info(inf), extensions(exts),
    signature(sig), sessionID(sessid) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Encode as XML string (without signature).

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string (without signature).
  */
  std::string XmlEncodeWithoutSignature(const std::string& varName = "") const;

  /*! \brief  Get trigger nonce.

      \returns  Trigger nonce.
  */
  const SPtr<ROAPNonce>& GetTriggerNonce() const {
    return tNonce;
  }

  /*! \brief  Get device nonce.

      \returns  Device nonce.
  */
  const NZSPtr<ROAPNonce>& GetDeviceNonce() const {
    return dNonce;
  }

  /*! \brief  Get time.

      \returns  Time.
  */
  const NZSPtr<DateTime>& GetTime() const {
    return time;
  }

  /*! \brief  Get certificate chain.

      \returns  Certificate chain.
  */
  const SPtr<ROAPCertificateChain>& GetCertChain() const {
    return chain;
  }

  /*! \brief  Get trusted authorities.

      \returns  Trusted authorities.
  */
  const SPtr<ROAPKeyIdentifiers>& GetTrustedAuthorities() const {
    return trusted;
  }

  /*! \brief  Get server info.

      \returns  Server info.
  */
  const SPtr<ROAPServerInfo>& GetServerInfo() const {
    return info;
  }

  /*! \brief  Get extensions.

      \returns  Extensions.
  */
  SPtr<RegRequestExtensions> GetExtensions() const {
    return extensions;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const Base64StringT& GetSignature() const {
    return signature;
  }

  /*! \brief  Get session identifier.

      \returns  Session identifier.
  */
  const NZSPtr<ROAPSessionID>& GetSessionID() const {
    return sessionID;
  }

protected:
  SPtr<ROAPNonce> tNonce;
	NZSPtr<ROAPNonce> dNonce;
	NZSPtr<DateTime> time;
	SPtr<ROAPCertificateChain> chain;
	SPtr<ROAPKeyIdentifiers> trusted;
	SPtr<ROAPServerInfo> info;
	SPtr<RegRequestExtensions> extensions;
	Base64StringT signature;
	NZSPtr<ROAPSessionID> sessionID;
};

/*! \brief  Extensions for registration response message.
*/
class RegResponseExtensions: public XmlData {
public:
  /*! \brief  Constructor.

      \param  wlist                 domain name white list.
  */
  RegResponseExtensions(const NZSPtr<DomainNameWhiteListExtension>& wlist):
    whitelist(wlist) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get domain name white list.

      \returns  Domain name white list.
  */
  const NZSPtr<DomainNameWhiteListExtension>& GetDomainNameWhiteList() const {
    return whitelist;
  }

private:
  NZSPtr<DomainNameWhiteListExtension> whitelist;
};

/*! \brief  Registration response message.
*/
class RegResponse: public ROAPResponse {
};

/*! \brief  Successful registration response message.
*/
class SuccessRegResponse: public RegResponse {
public:
  /*! \brief  Constructor.

      \param  url             rights issuer URL.
      \param  cchain          certificate chain.
      \param  ocspresp        OCSP response.
      \param  exts            extensions.
      \param  sig             signature.
      \param  sessid          session identifier.
  */
	SuccessRegResponse(const NZSPtr<URIValue>& url, const SPtr<ROAPCertificateChain>&
    cchain, const std::vector<Base64StringT>& ocspresp, const SPtr<RegResponseExtensions>&
    exts, const Base64StringT& sig, const NZSPtr<ROAPSessionID>& sessid):
    riURL(url), chain(cchain), ocsps(ocspresp), extensions(exts), signature(sig),
    sessionID(sessid) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Encode as XML string (without signature).

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string (without signature).
  */
  std::string XmlEncodeWithoutSignature(const std::string& varName = "") const;

  /*! \brief  Get status.

      \returns  Status.
  */
  virtual NZSPtr<ROAPStatus> GetStatus() const {
    return new SuccessROAPStatus();
  }

  /*! \brief  Get rights issuer URL.

      \returns  Rights issuer URL.
  */
  const NZSPtr<URIValue>& GetRightsIssuerURL() const {
    return riURL;
  }

  /*! \brief  Get certificate chain.

      \returns  Certificate chain.
  */
  const SPtr<ROAPCertificateChain>& GetCertChain() const {
    return chain;
  }

  /*! \brief  Get OCSP responses.

      \returns  OCSP responses.
  */
  const std::vector<Base64StringT>& GetOCSPResponses() const {
    return ocsps;
  }

  /*! \brief  Get extensions.

      \returns  Extensions.
  */
  SPtr<RegResponseExtensions> GetExtensions() const {
    return extensions;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const Base64StringT& GetSignature() const {
    return signature;
  }

  /*! \brief  Get session identifier.

      \returns  Session identifier.
  */
  const NZSPtr<ROAPSessionID>& GetSessionID() const {
    return sessionID;
  }

protected:
	NZSPtr<URIValue> riURL;
	SPtr<ROAPCertificateChain> chain;
	std::vector<Base64StringT> ocsps;
  SPtr<RegResponseExtensions> extensions;
	Base64StringT signature;
	NZSPtr<ROAPSessionID> sessionID;
};

/*! \brief  Unsuccessful registration response message.
*/
class UnsuccessRegResponse: public RegResponse {
public:
  /*! \brief  Constructor.

      \param  stat              unsuccessful status.
      \param  sessid            session identifier.
  */
  UnsuccessRegResponse(const NZSPtr<UnsuccessROAPStatus>& stat,
    const SPtr<ROAPSessionID>& sessid): status(stat), sessionID(sessid) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get status.

      \returns  Status.
  */
  virtual NZSPtr<ROAPStatus> GetStatus() const {
    return (UnsuccessROAPStatus*)status;
  }

  /*! \brief  Get session identifier.

      \returns  Session identifier.
  */
  const SPtr<ROAPSessionID>& GetSessionID() const {
    return sessionID;
  }

  /*! \brief  Get unsuccess status.

      \returns  Unsuccess status.
  */
  const NZSPtr<UnsuccessROAPStatus>& GetUnsuccessStatus() const {
    return status;
  }

private:
  NZSPtr<UnsuccessROAPStatus> status;
  SPtr<ROAPSessionID> sessionID;
};

/*! \brief  Hash of the DRM content.

    Algorithm is fixed to http://www.w3.org/2000/09/xmldsig#sha1.
*/
class DCFHash: public XmlData {
public:
  /*! \brief  Constructor.

      \param  hashval           hash string.
  */
  DCFHash(const Base64StringT& hashval): val(hashval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get hash string.

      \returns  Hash string.
  */
  const Base64StringT& Get() const {
    return val;
  }

  /*! \brief  Get algorithm.

      \returns  Algorithm.
  */
  NZSPtr<URIValue> GetAlgorithm() const {
    return new URIValue("http://www.w3.org/2000/09/xmldsig#sha1");
  }

private:
	Base64StringT val;
};

/*! \brief  Rights object info data.

    Pair of rights object identifier and DCF hash.
*/
class ROInfoData: public GC {
public:
  /*! \brief  Constructor.

      \param  idval           rights object identifier.
      \param  dcf             DCF hash.
  */
  ROInfoData(const NZSPtr<IDValue>& idval, const SPtr<DCFHash>& dcf): roID(idval),
    dcfHash(dcf) {
  }

  /*! \brief  Encode as XML string.

      \returns  Encoded XML string.
  */
	std::string XmlEncode() const;

  /*! \brief  Get rights object identifier.

      \returns  Rights object identifier.
  */
  const NZSPtr<IDValue>& GetROID() const {
    return roID;
  }

  /*! \brief  Get DCF hash.

      \returns  DCF hash.
  */
  const SPtr<DCFHash>& GetDCFHash() const {
    return dcfHash;
  }

private:
	NZSPtr<IDValue> roID;
	SPtr<DCFHash> dcfHash;
};

/*! \brief  Rights object info.

    Sequence of rights object info data.
*/
class ROInfo: public XmlData {
public:
  /*! \brief  Constructor.

      Size of rights object info data vector must be at least 1.

      \param  data        rights object info data sequence.

      If fails, throws ROAPException.
  */
  ROInfo(const std::vector<NZSPtr<ROInfoData> >& data): infoDatas(data) {
    if (infoDatas.size() == 0) {
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

  /*! \brief  Get rights object identifier.

      \returns  Rights object identifier.
  */
  const std::vector<NZSPtr<ROInfoData> >& GetDatas() const {
    return infoDatas;
  }

private:
	std::vector<NZSPtr<ROInfoData> > infoDatas;
};

/*! \brief  Extensions for rights object request message.
*/
class RORequestExtensions: public XmlData {
public:
  /*! \brief  Constructor.

      \param  peerid                peer key identifier.
      \param  noocsp                no OCSP response.
      \param  ocspresp              OCSP responder key identifier.
      \param  transid               transaction identifier.

      If fails, throws ROAPException.
  */
  RORequestExtensions(const SPtr<PeerKeyIdExtension>& peerid, const
      SPtr<NoOCSPResponseExtension>& noocsp, const SPtr<OCSPResponderKeyIdExtension>&
      ocspresp, const SPtr<TransactionIdExtension>& transid): peerKeyId(peerid),
      noOCSP(noocsp), ocspResponderKeyId(ocspresp), transactionId(transid) {
    if ((peerKeyId == 0) && (noOCSP == 0) && (ocspResponderKeyId == 0) && (transactionId == 0)) {
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

  /*! \brief  Get peer key identifier.

      \returns  Peer key identifier.
  */
  const SPtr<PeerKeyIdExtension>& GetPeerKeyID() const {
    return peerKeyId;
  }

  /*! \brief  Get no OCSP response.

      \returns  No OCSP response.
  */
  const SPtr<NoOCSPResponseExtension>& GetNoOCSPResponse() const {
    return noOCSP;
  }

  /*! \brief  Get OCSP responder key identifier.

      \returns  OCSP responder key identifier.
  */
  const SPtr<OCSPResponderKeyIdExtension>& GetOCSPResponderKeyID() const {
    return ocspResponderKeyId;
  }

  /*! \brief  Get transaction identifier.

      \returns  Transaction identifier.
  */
  const SPtr<TransactionIdExtension>& GetTransactionID() const {
    return transactionId;
  }

protected:
  SPtr<PeerKeyIdExtension> peerKeyId;
  SPtr<NoOCSPResponseExtension> noOCSP;
  SPtr<OCSPResponderKeyIdExtension> ocspResponderKeyId;
  SPtr<TransactionIdExtension> transactionId;
};

/*! \brief  Rights object request.
*/
class RORequest: public ROAPRequest {
public:
  /*! \brief  Constructor.

      \param  tnonce                  trigger nonce.
      \param  devid                   device identifier.
      \param  domid                   domain identifier.
      \param  riid                    rights issuer identifier.
      \param  dnonce                  device nonce.
      \param  dtime                   time.
      \param  inf                     RO info.
      \param  cchain                  certificate chain.
      \param  exts                    extensions.
      \param  sig                     signature.
  */
	RORequest(const SPtr<ROAPNonce>& tnonce, const NZSPtr<ROAPIdentifier>& devid,
    const SPtr<ROAPDomainIdentifier>& domid, const NZSPtr<ROAPIdentifier>& riid,
    const NZSPtr<ROAPNonce>& dnonce, const NZSPtr<DefDateTime>& dtime,
    const NZSPtr<ROInfo>& inf, const SPtr<ROAPCertificateChain>& cchain,
    const SPtr<RORequestExtensions>& exts, const Base64StringT& sig):
    tNonce(tnonce), deviceID(devid), domainID(domid), riID(riid), dNonce(dnonce),
    time(dtime), info(inf), chain(cchain), extensions(exts), signature(sig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Encode as XML string (without signature).

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string (without signature).
  */
  std::string XmlEncodeWithoutSignature(const std::string& varName = "") const;

  /*! \brief  Get trigger nonce.

      \returns  Trigger nonce.
  */
  const SPtr<ROAPNonce>& GetTriggerNonce() const {
    return tNonce;
  }

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetDeviceID() const {
    return deviceID;
  }

  /*! \brief  Get domain identifier.

      \returns  Domain identifier.
  */
  const SPtr<ROAPDomainIdentifier>& GetDomainID() const {
    return domainID;
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get device nonce.

      \returns  Device nonce.
  */
  const NZSPtr<ROAPNonce>& GetDeviceNonce() const {
    return dNonce;
  }

  /*! \brief  Get time.

      \returns  Time.
  */
  const NZSPtr<DefDateTime>& GetTime() const {
    return time;
  }

  /*! \brief  Get rights object info.

      \returns  Rights object info.
  */
  const NZSPtr<ROInfo>& GetInfo() const {
    return info;
  }

  /*! \brief  Get certificate chain.

      \returns  Certificate chain.
  */
  const SPtr<ROAPCertificateChain>& GetCertChain() const {
    return chain;
  }

  /*! \brief  Get extensions.

      \returns  Extensions.
  */
  const SPtr<RORequestExtensions>& GetExtensions() const {
    return extensions;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const Base64StringT& GetSignature() const {
    return signature;
  }

protected:
  SPtr<ROAPNonce> tNonce;
	NZSPtr<ROAPIdentifier> deviceID;
	SPtr<ROAPDomainIdentifier> domainID;
	NZSPtr<ROAPIdentifier> riID;
  NZSPtr<ROAPNonce> dNonce;
	NZSPtr<DefDateTime> time;
	NZSPtr<ROInfo> info;
	SPtr<ROAPCertificateChain> chain;
	SPtr<RORequestExtensions> extensions;
	Base64StringT signature;
};

/*! \brief  Extensions for rights objects response message.
*/
class ROResponseExtensions: public XmlData {
public:
  /*! \brief  Constructor.

      \param  trans                 transaction identifier.

      If fails, throws ROAPException.
  */
  ROResponseExtensions(const NZSPtr<TransactionIdExtension>& trans):
      transactionId(trans) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get transaction identifier.

      \returns  Transaction identifier.
  */
  const NZSPtr<TransactionIdExtension>& GetTransactionID() const {
    return transactionId;
  }

protected:
  NZSPtr<TransactionIdExtension> transactionId;
};

/*! \brief  2-Pass rights object response.
*/
class TwoPassROResponse: public ROAPResponse {
};

/*! \brief  Successful 2-Pass rights object response.
*/
class SuccessTwoPassROResponse: public TwoPassROResponse {
public:
  /*! \brief  Constructor.

      Size of protected rights objects vector must be >= 1.

      \param  devid                 device identifier.
      \param  riid                  rights issuer identifier.
      \param  nonceval              nonce.
      \param  pros                  protected rights objects vector.
      \param  cchain                certificate chain.
      \param  ocspresp              OCSP responses.
      \param  exts                  extensions.
      \param  sig                   signature.

      If fails, throws ROAPException.
  */
	SuccessTwoPassROResponse(const NZSPtr<ROAPIdentifier>& devid,
      const NZSPtr<ROAPIdentifier>& riid, const NZSPtr<ROAPNonce>& nonceval,
      const std::vector<NZSPtr<ROAPProtectedRO> >& pros, const
      SPtr<ROAPCertificateChain>& cchain, const std::vector<Base64StringT>& ocspresp,
      const SPtr<ROResponseExtensions>& exts, const Base64StringT& sig):
      deviceID(devid), riID(riid), nonce(nonceval), ros(pros), chain(cchain),
      ocsps(ocspresp), extensions(exts), signature(sig) {
    if (ros.size() == 0) {
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

  /*! \brief  Encode as XML string (without signature).

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string (without signature).
  */
  std::string XmlEncodeWithoutSignature(const std::string& varName = "") const;

  /*! \brief  Get status.

      \returns  Status.
  */
  virtual NZSPtr<ROAPStatus> GetStatus() const {
    return new SuccessROAPStatus();
  }

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetDeviceID() const {
    return deviceID;
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  const NZSPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

  /*! \brief  Get protected rights objects vector.

      Size of protected rights objects vector must be >= 1.

      \returns  Protected rights objects vector.
  */
  const std::vector<NZSPtr<ROAPProtectedRO> >& GetProtectedROs() const {
    return ros;
  }

  /*! \brief  Get certificate chain.

      \returns  Certificate chain.
  */
  const SPtr<ROAPCertificateChain>& GetCertChain() const {
    return chain;
  }

  /*! \brief  Get OCSP responses.

      \returns  OCSP responses.
  */
  const std::vector<Base64StringT>& GetOCSPResponses() const {
    return ocsps;
  }

  /*! \brief  Get extensions.

      \returns  Extensions.
  */
  const SPtr<ROResponseExtensions>& GetExtensions() const {
    return extensions;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const Base64StringT& GetSignature() const {
    return signature;
  }

protected:
	NZSPtr<ROAPIdentifier> deviceID;
	NZSPtr<ROAPIdentifier> riID;
	NZSPtr<ROAPNonce> nonce;
	std::vector<NZSPtr<ROAPProtectedRO> > ros;
	SPtr<ROAPCertificateChain> chain;
	std::vector<Base64StringT> ocsps;
	SPtr<ROResponseExtensions> extensions;
	Base64StringT signature;
};

/*! \brief  Unsuccessful 2-Pass rights object response.
*/
class UnsuccessTwoPassROResponse: public TwoPassROResponse {
public:
  /*! \brief  Constructor.

      \param  stat                unsuccessful status.
  */
  UnsuccessTwoPassROResponse(const NZSPtr<UnsuccessROAPStatus>& stat): status(stat) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get status.

      \returns  Status.
  */
  virtual NZSPtr<ROAPStatus> GetStatus() const {
    return (UnsuccessROAPStatus*)status;
  }

  /*! \brief  Get unsuccess status.

      \returns  Unsuccess status.
  */
  const NZSPtr<UnsuccessROAPStatus>& GetUnsuccessStatus() const {
    return status;
  }

private:
  NZSPtr<UnsuccessROAPStatus> status;
};

/*! \brief  1-Pass rights object response.
*/
class OnePassROResponse: public ROAPResponse {
public:
  /*! \brief  Constructor.

      Size of protected rights objects vector must be >= 1.

      \param  stat                  status.
      \param  devid                 device identifier.
      \param  riid                  rights issuer identifier.
      \param  pros                  protected rights objects vector.
      \param  cchain                certificate chain.
      \param  ocspresp              OCSP responses.
      \param  exts                  extensions.
      \param  sig                   signature.

      If fails, throws ROAPException.
  */
	OnePassROResponse(const NZSPtr<ROAPStatus>& stat, const NZSPtr<ROAPIdentifier>& devid,
      const NZSPtr<ROAPIdentifier>& riid, const std::vector<NZSPtr<ROAPProtectedRO> >&
      pros, const SPtr<ROAPCertificateChain>& cchain, const std::vector<Base64StringT>&
      ocspresp, const NZSPtr<ROResponseExtensions>& exts, const Base64StringT& sig):
      status(stat), deviceID(devid), riID(riid), ros(pros), chain(cchain),
      ocsps(ocspresp), extensions(exts), signature(sig) {
    if (ros.size() == 0) {
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

  /*! \brief  Encode as XML string (without signature).

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string (without signature).
  */
  std::string XmlEncodeWithoutSignature(const std::string& varName = "") const;

  /*! \brief  Get status.

      \returns  Status.
  */
  virtual NZSPtr<ROAPStatus> GetStatus() const {
    return status;
  }

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetDeviceID() const {
    return deviceID;
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get protected rights objects vector.

      Size of protected rights objects vector must be >= 1.

      \returns  Protected rights objects vector.
  */
  const std::vector<NZSPtr<ROAPProtectedRO> >& GetProtectedROs() const {
    return ros;
  }

  /*! \brief  Get certificate chain.

      \returns  Certificate chain.
  */
  const SPtr<ROAPCertificateChain>& GetCertChain() const {
    return chain;
  }

  /*! \brief  Get OCSP responses.

      \returns  OCSP responses.
  */
  const std::vector<Base64StringT>& GetOCSPResponses() const {
    return ocsps;
  }

  /*! \brief  Get extensions.

      \returns  Extensions.
  */
  const NZSPtr<ROResponseExtensions>& GetExtensions() const {
    return extensions;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const Base64StringT& GetSignature() const {
    return signature;
  }

protected:
  NZSPtr<ROAPStatus> status;
	NZSPtr<ROAPIdentifier> deviceID;
	NZSPtr<ROAPIdentifier> riID;
	std::vector<NZSPtr<ROAPProtectedRO> > ros;
	SPtr<ROAPCertificateChain> chain;
	std::vector<Base64StringT> ocsps;
	NZSPtr<ROResponseExtensions> extensions;
	Base64StringT signature;
};

/*! \brief  Domain request.
*/
class DomainRequest: public ROAPRequest {
public:
  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
	virtual const NZSPtr<ROAPIdentifier>& GetDeviceID() const = 0;

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
	virtual const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const = 0;

  /*! \brief  Get device nonce.

      \returns  Device nonce.
  */
  virtual const NZSPtr<ROAPNonce>& GetDeviceNonce() const = 0;

  /*! \brief  Get time.

      \returns  Time.
  */
  virtual const NZSPtr<DateTime>& GetTime() const = 0;

  /*! \brief  Get domain identifier.

      \returns  Domain identifier.
  */
  virtual const NZSPtr<ROAPDomainIdentifier>& GetDomainID() const = 0;

  /*! \brief  Get certificate chain.

      \returns  Certificate chain.
  */
  virtual const SPtr<ROAPCertificateChain>& GetCertChain() const = 0;

  /*! \brief  Get signature.

      \returns  Signature.
  */
  virtual const Base64StringT& GetSignature() const = 0;
};

/*! \brief  Extensions for join domain request message.
*/
class JoinDomainReqExtensions: public XmlData {
public:
  /*! \brief  Constructor.

      \param  peerid              peer key identifier.
      \param  noocsp              no OCSP response.
      \param  ocspresp            OCSP responder key identifier.
      \param  hchain              hash chain support.

      If fails, throws ROAPException.
  */
  JoinDomainReqExtensions(const SPtr<PeerKeyIdExtension>& peerid, const
    SPtr<NoOCSPResponseExtension>& noocsp, const SPtr<OCSPResponderKeyIdExtension>&
    ocspresp, const SPtr<HashChainSupportExtension>& hchain): peerKeyId(peerid),
    noOCSP(noocsp), ocspResponderKeyId(ocspresp), hashChainSupport(hchain) {
    if ((peerKeyId == 0) && (noOCSP == 0) && (ocspResponderKeyId == 0) && (hashChainSupport == 0)) {
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

  /*! \brief  Get peer key identifier.

      \returns  Peer key identifier.
  */
  const SPtr<PeerKeyIdExtension>& GetPeerKeyId() const {
    return peerKeyId;
  }

  /*! \brief  Get no OCSP response.

      \returns  No OCSP response.
  */
  const SPtr<NoOCSPResponseExtension>& GetNoOCSPResponse() const {
    return noOCSP;
  }

  /*! \brief  Get OCSP responder key identifier.

      \returns  OCSP responder key identifier.
  */
  const SPtr<OCSPResponderKeyIdExtension>& GetOCSPResponderKeyId() const {
    return ocspResponderKeyId;
  }

  /*! \brief  Get hash chain support.

      \returns  Hash chain support.
  */
  const SPtr<HashChainSupportExtension>& GetHashChainSupport() const {
    return hashChainSupport;
  }

protected:
  SPtr<PeerKeyIdExtension> peerKeyId;
  SPtr<NoOCSPResponseExtension> noOCSP;
  SPtr<OCSPResponderKeyIdExtension> ocspResponderKeyId;
  SPtr<HashChainSupportExtension> hashChainSupport;
};

/*! \brief  Join domain request.
*/
class JoinDomainRequest: public DomainRequest {
public:
  /*! \brief  Constructor.

      \param  tnonce              trigger nonce.
      \param  devid               device identifier.
      \param  riid                rights issuer identifier.
      \param  dnonce              device nonce.
      \param  dtime               time.
      \param  domid               domain identifier.
      \param  cchain              certificate chain.
      \param  exts                extensions.
      \param  sig                 signature.
  */
	JoinDomainRequest(const SPtr<ROAPNonce>& tnonce, const NZSPtr<ROAPIdentifier>&
    devid, const NZSPtr<ROAPIdentifier>& riid, const NZSPtr<ROAPNonce>& dnonce,
    const NZSPtr<DateTime>& dtime, const NZSPtr<ROAPDomainIdentifier>& domid,
		const SPtr<ROAPCertificateChain>& cchain,	const SPtr<JoinDomainReqExtensions>&
    exts, const Base64StringT& sig): tNonce(tnonce), deviceID(devid), riID(riid),
    dNonce(dnonce), time(dtime), domainID(domid), chain(cchain), extensions(exts),
    signature(sig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Encode as XML string (without signature).

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string (without signature).
  */
  std::string XmlEncodeWithoutSignature(const std::string& varName = "") const;

  /*! \brief  Get trigger nonce.

      \returns  Trigger nonce.
  */
  const SPtr<ROAPNonce>& GetTriggerNonce() const {
    return tNonce;
  }

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetDeviceID() const {
    return deviceID;
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get device nonce.

      \returns  Device nonce.
  */
  const NZSPtr<ROAPNonce>& GetDeviceNonce() const {
    return dNonce;
  }

  /*! \brief  Get time.

      \returns  Time.
  */
  const NZSPtr<DateTime>& GetTime() const {
    return time;
  }

  /*! \brief  Get domain identifier.

      \returns  Domain identifier.
  */
  const NZSPtr<ROAPDomainIdentifier>& GetDomainID() const {
    return domainID;
  }

  /*! \brief  Get certificate chain.

      \returns  Certificate chain.
  */
  const SPtr<ROAPCertificateChain>& GetCertChain() const {
    return chain;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const Base64StringT& GetSignature() const {
    return signature;
  }

  /*! \brief  Get extensions.

      \returns  Extensions.
  */
  const SPtr<JoinDomainReqExtensions>& GetExtensions() const {
    return extensions;
  }

protected:
  SPtr<ROAPNonce> tNonce;
	NZSPtr<ROAPIdentifier> deviceID;
	NZSPtr<ROAPIdentifier> riID;
  NZSPtr<ROAPNonce> dNonce;
	NZSPtr<DateTime> time;
	NZSPtr<ROAPDomainIdentifier> domainID;
	SPtr<ROAPCertificateChain> chain;
	Base64StringT signature;
	SPtr<JoinDomainReqExtensions> extensions;
};

/*! \brief  Extensions for domain response message.
*/
class DomainResponseExtensions: public XmlData {
public:
  /*! \brief  Constructor.

      \param  hchain              hash chain support.
  */
  DomainResponseExtensions(const NZSPtr<HashChainSupportExtension>& hchain):
    hashChainSupport(hchain) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get hash chain support.

      \returns  Hash chain support.
  */
  const NZSPtr<HashChainSupportExtension>& GetHashChainSupport() const {
    return hashChainSupport;
  }

protected:
  NZSPtr<HashChainSupportExtension> hashChainSupport;
};

/*! \brief  Protected domain key.
*/
class ROAPProtectedDomainKey: public XmlData {
public:
  /*! \brief  Constructor.

      \param  enc             encrypted key.
      \param  idval           rights issuer identifier.
      \param  macval          mac.
  */
	ROAPProtectedDomainKey(const NZSPtr<XencEncryptedKey>& enc, const
    NZSPtr<ROAPIdentifier>& idval, const Base64StringT& macval): key(enc),
    riID(idval), mac(macval) {
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
  const NZSPtr<XencEncryptedKey>& GetEncKey() const {
    return key;
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get mac.

      \returns  Mac.
  */
  const Base64StringT& GetMac() const {
    return mac;
  }

private:
	NZSPtr<XencEncryptedKey> key;
	NZSPtr<ROAPIdentifier> riID;
	Base64StringT mac;
};

/*! \brief  Domain info.
*/
class ROAPDomainInfo: public XmlData {
public:
  /*! \brief  Constructor.

      Size of protected domain keys vector must be >= 1.

      \param  timeval               time.
      \param  keyvec                protected domain keys vector.

      If fails, throws ROAPException.
  */
	ROAPDomainInfo(const NZSPtr<DateTime>& timeval, const std::vector<
      NZSPtr<ROAPProtectedDomainKey> >& keyvec): time(timeval), keys(keyvec) {
    if (keys.size() < 1) {
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

  /*! \brief  Get time.

      \returns  Time.
  */
  const NZSPtr<DateTime>& GetTime() const {
    return time;
  }

  /*! \brief  Get protected domain keys vector.

      \returns  Protected domain keys vector.
  */
  const std::vector<NZSPtr<ROAPProtectedDomainKey> >& GetProtectedDomainKeys() const {
    return keys;
  }

private:
	NZSPtr<DateTime> time;
	std::vector<NZSPtr<ROAPProtectedDomainKey> > keys;
};

/*! \brief  Join domain response.
*/
class JoinDomainResponse: public ROAPResponse {
};

/*! \brief  Successful join domain response.
*/
class SuccessJoinDomainResponse: public JoinDomainResponse {
public:
  /*! \brief  Constructor.

      \param  devid               device identifier.
      \param  riid                rights issuer identifier.
      \param  nonceval            nonce.
      \param  inf                 domain info.
      \param  cchain              certificate chain.
      \param  ocsp                OCSP responses.
      \param  exts                extensions.
      \param  sig                 signature.
  */
	SuccessJoinDomainResponse(const NZSPtr<ROAPIdentifier>& devid, const
    NZSPtr<ROAPIdentifier>& riid,	const NZSPtr<ROAPNonce>& nonceval, const
    NZSPtr<ROAPDomainInfo>& inf,	const SPtr<ROAPCertificateChain>& cchain,
		const std::vector<Base64StringT>& ocsp,	const SPtr<DomainResponseExtensions>&
    exts, const Base64StringT& sig): deviceID(devid), riID(riid), nonce(nonceval),
    info(inf), chain(cchain), ocsps(ocsp), extensions(exts), signature(sig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Encode as XML string (without signature).

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string (without signature).
  */
  std::string XmlEncodeWithoutSignature(const std::string& varName = "") const;

  /*! \brief  Get status.

      \returns  Status.
  */
  virtual NZSPtr<ROAPStatus> GetStatus() const {
    return new SuccessROAPStatus();
  }

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetDeviceID() const {
    return deviceID;
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  const NZSPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

  /*! \brief  Get domain info.

      \returns  Domain info.
  */
  const NZSPtr<ROAPDomainInfo>& GetDomainInfo() const {
    return info;
  }

  /*! \brief  Get certificate chain.

      \returns  Certificate chain.
  */
  const SPtr<ROAPCertificateChain>& GetCertChain() const {
    return chain;
  }

  /*! \brief  Get OCSP responses.

      \returns  OCSP responses.
  */
  const std::vector<Base64StringT>& GetOCSPResponses() const {
    return ocsps;
  }

  /*! \brief  Get extensions.

      \returns  Extensions.
  */
  const SPtr<DomainResponseExtensions>& GetExtensions() const {
    return extensions;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const Base64StringT& GetSignature() const {
    return signature;
  }

protected:
	NZSPtr<ROAPIdentifier> deviceID;
	NZSPtr<ROAPIdentifier> riID;
	NZSPtr<ROAPNonce> nonce;
	NZSPtr<ROAPDomainInfo> info;
	SPtr<ROAPCertificateChain> chain;
	std::vector<Base64StringT> ocsps;
	SPtr<DomainResponseExtensions> extensions;
	Base64StringT signature;
};

/*! \brief  Unsuccessful join domain response.
*/
class UnsuccessJoinDomainResponse: public JoinDomainResponse {
public:
  /*! \brief  Constructor.

      \param  stat                  unsuccessful status.
  */
  UnsuccessJoinDomainResponse(const NZSPtr<UnsuccessROAPStatus>& stat): status(stat) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get status.

      \returns  Status.
  */
  virtual NZSPtr<ROAPStatus> GetStatus() const {
    return (UnsuccessROAPStatus*)status;
  }

  /*! \brief  Get unsuccess status.

      \returns  Unsuccess status.
  */
  virtual const NZSPtr<UnsuccessROAPStatus>& GetUnsuccessStatus() const {
    return status;
  }

protected:
  NZSPtr<UnsuccessROAPStatus> status;
};

/*! \brief  Extension for leave domain request message.
*/
class LeaveDomainReqExtensions: public XmlData {
public:
  /*! \brief  Constructor.

      \param  nmember             not domain member.
  */
  LeaveDomainReqExtensions(const SPtr<NotDomainMemberExtension>& nmember):
    notDomainMember(nmember) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get not domain member.

      \returns  Not domain member.
  */
  const SPtr<NotDomainMemberExtension>& GetNotDomainMember() const {
    return notDomainMember;
  }

protected:
  SPtr<NotDomainMemberExtension> notDomainMember;
};

/*! \brief  Leave domain request.
*/
class LeaveDomainRequest: public DomainRequest {
public:
  /*! \brief  Constructor.

      \param  tnonce              trigger nonce.
      \param  devid               device identifier.
      \param  riid                rights issuer identifier.
      \param  dnonce              device nonce.
      \param  dtime               time.
      \param  domid               domain identifier.
      \param  cchain              certificate chain.
      \param  exts                extensions.
      \param  sig                 signature.
  */
	LeaveDomainRequest(const SPtr<ROAPNonce>& tnonce, const NZSPtr<ROAPIdentifier>&
    devid, const NZSPtr<ROAPIdentifier>& riid, const NZSPtr<ROAPNonce>& dnonce,
    const NZSPtr<DateTime>& dtime, const NZSPtr<ROAPDomainIdentifier>& domid,
		const SPtr<ROAPCertificateChain>& cchain,	const SPtr<LeaveDomainReqExtensions>&
    exts, const Base64StringT& sig): tNonce(tnonce), deviceID(devid), riID(riid),
    dNonce(dnonce), time(dtime), domainID(domid), chain(cchain), extensions(exts),
    signature(sig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Encode as XML string (without signature).

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string (without signature).
  */
  std::string XmlEncodeWithoutSignature(const std::string& varName = "") const;

  /*! \brief  Get trigger nonce.

      \returns  Trigger nonce.
  */
  const SPtr<ROAPNonce>& GetTriggerNonce() const {
    return tNonce;
  }

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetDeviceID() const {
    return deviceID;
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get device nonce.

      \returns  Device nonce.
  */
  const NZSPtr<ROAPNonce>& GetDeviceNonce() const {
    return dNonce;
  }

  /*! \brief  Get time.

      \returns  Time.
  */
  const NZSPtr<DateTime>& GetTime() const {
    return time;
  }

  /*! \brief  Get domain identifier.

      \returns  Domain identifier.
  */
  const NZSPtr<ROAPDomainIdentifier>& GetDomainID() const {
    return domainID;
  }

  /*! \brief  Get certificate chain.

      \returns  Certificate chain.
  */
  const SPtr<ROAPCertificateChain>& GetCertChain() const {
    return chain;
  }

  /*! \brief  Get extensions.

      \returns  Extensions.
  */
  const SPtr<LeaveDomainReqExtensions>& GetExtensions() const {
    return extensions;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const Base64StringT& GetSignature() const {
    return signature;
  }

protected:
  SPtr<ROAPNonce> tNonce;
	NZSPtr<ROAPIdentifier> deviceID;
	NZSPtr<ROAPIdentifier> riID;
  NZSPtr<ROAPNonce> dNonce;
	NZSPtr<DateTime> time;
	NZSPtr<ROAPDomainIdentifier> domainID;
	SPtr<ROAPCertificateChain> chain;
	SPtr<LeaveDomainReqExtensions> extensions;
	Base64StringT signature;
};

/*! \brief  Extensions for leave domain response message.
*/
class LeaveDomainResponseExtensions: public XmlData {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;
};

/*! \brief  Leave domain response.
*/
class LeaveDomainResponse: public ROAPResponse {
};

/*! \brief  Successful leave domain response.
*/
class SuccessLeaveDomainResponse: public LeaveDomainResponse {
public:
  /*! \brief  Constructor.

      \param  nonceval                nonce.
      \param  domid                   domain identifier.
      \param  exts                    extensions.
  */
	SuccessLeaveDomainResponse(const NZSPtr<ROAPNonce>& nonceval, const
    NZSPtr<ROAPDomainIdentifier>& domid, const SPtr<LeaveDomainResponseExtensions>&
    exts): nonce(nonceval), domainID(domid), extensions(exts) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get status.

      \returns  Status.
  */
  virtual NZSPtr<ROAPStatus> GetStatus() const {
    return new SuccessROAPStatus();
  }

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  const NZSPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

  /*! \brief  Get domain identifier.

      \returns  Domain identifier.
  */
  const NZSPtr<ROAPDomainIdentifier>& GetDomainID() const {
    return domainID;
  }

  /*! \brief  Get extensions.

      \returns  Extensions.
  */
  const SPtr<LeaveDomainResponseExtensions>& GetExtensions() const {
    return extensions;
  }

protected:
	NZSPtr<ROAPNonce> nonce;
	NZSPtr<ROAPDomainIdentifier> domainID;
  SPtr<LeaveDomainResponseExtensions> extensions;
};

/*! \brief  Unsuccessful leave domain response.
*/
class UnsuccessLeaveDomainResponse: public LeaveDomainResponse {
public:
  /*! \brief  Constructor.

      \param  stat                  unsuccessful status.
  */
  UnsuccessLeaveDomainResponse(const NZSPtr<UnsuccessROAPStatus>& stat): status(stat) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get status.

      \returns  Status.
  */
  virtual NZSPtr<ROAPStatus> GetStatus() const {
    return (UnsuccessROAPStatus*)status;
  }

  /*! \brief  Get unsuccess status.

      \returns  Unsuccess status.
  */
  const NZSPtr<UnsuccessROAPStatus>& GetUnsuccessStatus() const {
    return status;
  }

protected:
  NZSPtr<UnsuccessROAPStatus> status;
};

/*! \brief  Trigger proxy.
*/
class ROAPTriggerProxy: public GC {
public:
  /*! \brief  Constructor.

      \param  flag          proxy indicator.
  */
  ROAPTriggerProxy(bool flag): proxy(flag) {
  }

  /*! \brief  Encode as XML string.

      \returns  Encoded XML string.
  */
	std::string XmlEncode() const;

  /*! \brief  Get proxy indicator.

      \returns  Proxy indicator.
  */
  bool Proxy() const {
    return proxy;
  }

private:
  bool proxy;
};

/*! \brief  Trigger.
*/
class ROAPTrigger: public XmlData {
public:
  /*! \brief  Constructor.

      \param  ver             version.
      \param  proxy           trigger proxy.
  */
  ROAPTrigger(const NZSPtr<ROAPVersion>& ver, const SPtr<ROAPTriggerProxy>& proxy):
    version(ver), triggerProxy(proxy) {
  }

  /*! \brief  Get version.

      \returns  Version.
  */
  const NZSPtr<ROAPVersion>& GetVersion() const {
    return version;
  }

  /*! \brief  Get trigger proxy.

      \returns  Trigger proxy.
  */
  const SPtr<ROAPTriggerProxy>& GetTriggerProxy() const {
    return triggerProxy;
  }

protected:
  NZSPtr<ROAPVersion> version;
  SPtr<ROAPTriggerProxy> triggerProxy;
};

/*! \brief  Registration request trigger data.
*/
class RegRequestTriggerData: public XmlData {
public:
  /*! \brief  Constructor.

      \param  riidval             rights issuer identifier.
      \param  nonceval            nonce.
      \param  urival              URL.
      \param  idval               identifier.
  */
  RegRequestTriggerData(const NZSPtr<ROAPIdentifier>& riidval, const
    SPtr<ROAPNonce>& nonceval, const NZSPtr<URIValue>& urival,
    const NZSPtr<IDValue>& idval): riID(riidval), nonce(nonceval), url(urival),
    id(idval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  const SPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

  /*! \brief  Get URL.

      \returns  URL.
  */
  const NZSPtr<URIValue>& GetURL() const {
    return url;
  }

  /*! \brief  Get identifier.

      \returns  Identifier.
  */
  const NZSPtr<IDValue>& GetID() const {
    return id;
  }

private:
  NZSPtr<ROAPIdentifier> riID;
  SPtr<ROAPNonce> nonce;
  NZSPtr<URIValue> url;
  NZSPtr<IDValue> id;
};

/*! \brief  Registration request trigger.
*/
class RegRequestTrigger: public ROAPTrigger {
public:
  /*! \brief  Constructor.

      \param  tdata             trigger data.
      \param  sig               signature.
      \param  ver               version.
      \param  proxy             trigger proxy.
  */
  RegRequestTrigger(const NZSPtr<RegRequestTriggerData>& tdata, const
    SPtr<DSSignature>& sig, const NZSPtr<ROAPVersion>& ver,
    const SPtr<ROAPTriggerProxy>& proxy): ROAPTrigger(ver, proxy), data(tdata),
    signature(sig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get trigger data.

      \returns  Trigger data.
  */
  const NZSPtr<RegRequestTriggerData>& GetData() const {
    return data;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const SPtr<DSSignature>& GetSignature() const {
    return signature;
  }

private:
  NZSPtr<RegRequestTriggerData> data;
  SPtr<DSSignature> signature;
};

/*! \brief  Rights object identifier and content identifiers.
*/
class ROIDContentID: public GC {
public:
  /*! \brief  Constructor.

      Size of content identifiers vector must be >= 1.

      \param  idval             rights object identifier.
      \param  ids               content identifiers vector.

      If fails, throws ROAPException.
  */
  ROIDContentID(const NZSPtr<IDValue>& idval, const std::vector<NZSPtr<URIValue> >&
      ids): roID(idval), contentIDs(ids) {
    if (contentIDs.size() < 1) {
      throw ROAPException();
    }
  }
	
  /*! \brief  Encode as XML string.

      \returns  Encoded XML string.
  */
  std::string XmlEncode() const;

  /*! \brief  Get rights object identifier.

      \returns  Rights object identifier.
  */
  const NZSPtr<IDValue>& GetROID() const {
    return roID;
  }

  /*! \brief  Get content identifiers vector.

      \returns  Content identifiers vector.
  */
  const std::vector<NZSPtr<URIValue> >& GetContentIDs() const {
    return contentIDs;
  }

private:
  NZSPtr<IDValue> roID;
  std::vector<NZSPtr<URIValue> > contentIDs;
};

/*! \brief  Rights object acquisition trigger data.
*/
class ROAcquisitionTriggerData: public XmlData {
public:
  /*! \brief  Constructor.

      Size of rights object identifier/content identifiers vector must be >= 1.

      \param  riidval           rights issuer identifier.
      \param  nonceval          nonce.
      \param  urival            URL.
      \param  roidcids          rights object identifier/content identifiers vector.
      \param  idval             identifier.

      If fails, throws ROAPException.
  */
  ROAcquisitionTriggerData(const NZSPtr<ROAPIdentifier>& riidval, const
      SPtr<ROAPNonce>& nonceval, const NZSPtr<URIValue>& urival,
      const std::vector<NZSPtr<ROIDContentID> >& roidcids, const
      NZSPtr<IDValue>& idval): riID(riidval), nonce(nonceval), url(urival),
      roIDContentIDs(roidcids), id(idval) {
    if (roIDContentIDs.size() < 1) {
      throw ROAPException();
    }
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  const SPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

  /*! \brief  Get URL.

      \returns  URL.
  */
  const NZSPtr<URIValue>& GetURL() const {
    return url;
  }

  /*! \brief  Get rights object identifier/content identifiers vector.

      \returns  Rights object identifier/content identifiers vector.
  */
  const std::vector<NZSPtr<ROIDContentID> >& GetROIDContentIDs() const {
    return roIDContentIDs;
  }

  /*! \brief  Get identifier.

      \returns  Identifier.
  */
  const NZSPtr<IDValue>& GetID() const {
    return id;
  }

  /*! \brief  Get domain identifier.

      \returns  Domain identifier.
  */
  virtual SPtr<ROAPDomainIdentifier> GetDomainID() const = 0;

protected:
  NZSPtr<ROAPIdentifier> riID;
  SPtr<ROAPNonce> nonce;
  NZSPtr<URIValue> url;
  std::vector<NZSPtr<ROIDContentID> > roIDContentIDs;
  NZSPtr<IDValue> id;
};

/*! \brief  Domain rights object acquisition trigger data.
*/
class DomainROTriggerData: public ROAcquisitionTriggerData {
public:
  /*! \brief  Constructor.

      Size of rights object identifier/content identifiers vector must be >= 1.

      \param  riidval           rights issuer identifier.
      \param  nonceval          nonce.
      \param  urival            URL.
      \param  domidval          domain identifier.
      \param  roidcids          rights object identifier/content identifiers vector.
      \param  idval             identifier.

      If fails, throws ROAPException.
  */
  DomainROTriggerData(const NZSPtr<ROAPIdentifier>& riidval, const
      SPtr<ROAPNonce>& nonceval, const NZSPtr<URIValue>& urival, const
      NZSPtr<ROAPDomainIdentifier>& domidval, const std::vector<NZSPtr<ROIDContentID> >&
      roidcids, const NZSPtr<IDValue>& idval): ROAcquisitionTriggerData(riidval,
      nonceval, urival, roidcids, idval), domainID(domidval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get domain identifier.

      \returns  Domain identifier.
  */
  virtual SPtr<ROAPDomainIdentifier> GetDomainID() const {
    return domainID;
  }

private:
  NZSPtr<ROAPDomainIdentifier> domainID;
};

/*! \brief  Non-domain rights object acquisition trigger data.
*/
class NDomainROTriggerData: public ROAcquisitionTriggerData {
public:
  /*! \brief  Constructor.

      Size of rights object identifier/content identifiers vector must be >= 1.

      \param  riidval           rights issuer identifier.
      \param  nonceval          nonce.
      \param  urival            URL.
      \param  roidcids          rights object identifier/content identifiers vector.
      \param  idval             identifier.

      If fails, throws ROAPException.
  */
  NDomainROTriggerData(const NZSPtr<ROAPIdentifier>& riidval, const
      SPtr<ROAPNonce>& nonceval, const NZSPtr<URIValue>& urival,
      const std::vector<NZSPtr<ROIDContentID> >& roidcids, const
      NZSPtr<IDValue>& idval): ROAcquisitionTriggerData(riidval, nonceval, urival,
      roidcids, idval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get domain identifier.

      \returns  Domain identifier.
  */
  virtual SPtr<ROAPDomainIdentifier> GetDomainID() const {
    return 0;
  }
};

/*! \brief  Rights object acquisition trigger.
*/
class ROAcquisitionTrigger: public ROAPTrigger {
public:
  /*! \brief  Constructor.

      \param  ver           version.
      \param  proxy         trigger proxy.
  */
  ROAcquisitionTrigger(const NZSPtr<ROAPVersion>& ver, const SPtr<ROAPTriggerProxy>&
    proxy): ROAPTrigger(ver, proxy) {
  }

  /*! \brief  Get trigger data.

      \returns  Trigger data.
  */
  virtual const NZSPtr<ROAcquisitionTriggerData>& GetTriggerData() const = 0;

  /*! \brief  Get signature.

      \returns  Signature.
  */
  virtual const SPtr<DSSignature>& GetSignature() const = 0;
};

/*! \brief  Domain rights object acquisition trigger.
*/
class DomainROTrigger: public ROAcquisitionTrigger {
public:
  /*! \brief  Constructor.

      \param  tdata         trigger data.
      \param  sig           signature.
      \param  ver           version.
      \param  proxy         trigger proxy.
  */
  DomainROTrigger(const NZSPtr<DomainROTriggerData>& tdata, const
    SPtr<DSSignature>& sig, const NZSPtr<ROAPVersion>& ver,
    const SPtr<ROAPTriggerProxy>& proxy): ROAcquisitionTrigger(ver, proxy),
    data(tdata), signature(sig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get trigger data.

      \returns  Trigger data.
  */
  virtual const NZSPtr<ROAcquisitionTriggerData>& GetTriggerData() const {
    return data;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  virtual const SPtr<DSSignature>& GetSignature() const {
    return signature;
  }

private:
  NZSPtr<ROAcquisitionTriggerData> data;
  SPtr<DSSignature> signature;
};

/*! \brief  Non-domain rights object acquisition trigger.
*/
class NDomainROTrigger: public ROAcquisitionTrigger {
public:
  /*! \brief  Constructor.

      \param  tdata         trigger data.
      \param  sig           signature.
      \param  ver           version.
      \param  proxy         trigger proxy.
  */
  NDomainROTrigger(const NZSPtr<NDomainROTriggerData>& tdata, const
    SPtr<DSSignature>& sig, const NZSPtr<ROAPVersion>& ver,
    const SPtr<ROAPTriggerProxy>& proxy): ROAcquisitionTrigger(ver, proxy),
    data(tdata), signature(sig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get trigger data.

      \returns  Trigger data.
  */
  virtual const NZSPtr<ROAcquisitionTriggerData>& GetTriggerData() const {
    return data;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  virtual const SPtr<DSSignature>& GetSignature() const {
    return signature;
  }

private:
  NZSPtr<ROAcquisitionTriggerData> data;
  SPtr<DSSignature> signature;
};

/*! \brief  Domain trigger data.
*/
class DomainTriggerData: public XmlData {
public:
  /*! \brief  Constructor.

      \param  riidval             rights issuer identifier.
      \param  urival              URL.
      \param  domidval            domain identifier.
      \param  idval               identifier.
  */
  DomainTriggerData(const NZSPtr<ROAPIdentifier>& riidval, const NZSPtr<URIValue>&
    urival, const NZSPtr<ROAPDomainIdentifier>& domidval, const NZSPtr<IDValue>&
    idval): riID(riidval), url(urival), domainID(domidval), id(idval) {
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetRightsIssuerID() const {
    return riID;
  }

  /*! \brief  Get URL.

      \returns  URL.
  */
  const NZSPtr<URIValue>& GetURL() const {
    return url;
  }

  /*! \brief  Get domain identifier.

      \returns  Domain identifier.
  */
  const NZSPtr<ROAPDomainIdentifier>& GetDomainID() const {
    return domainID;
  }

  /*! \brief  Get identifier.

      \returns  Identifier.
  */
  const NZSPtr<IDValue>& GetID() const {
    return id;
  }

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  virtual const SPtr<ROAPNonce>& GetNonce() const = 0;

protected:
  NZSPtr<ROAPIdentifier> riID;
  NZSPtr<URIValue> url;
  NZSPtr<ROAPDomainIdentifier> domainID;
  NZSPtr<IDValue> id;
};

/*! \brief  Join domain trigger data.
*/
class JoinDomainTriggerData: public DomainTriggerData {
public:
  /*! \brief  Constructor.

      \param  riidval             rights issuer identifier.
      \param  nonceval            nonce.
      \param  urival              URL.
      \param  domidval            domain identifier.
      \param  idval               identifier.
  */
  JoinDomainTriggerData(const NZSPtr<ROAPIdentifier>& riidval, const
    SPtr<ROAPNonce>& nonceval, const NZSPtr<URIValue>& urival,
    const NZSPtr<ROAPDomainIdentifier>& domidval, const NZSPtr<IDValue>& idval):
    DomainTriggerData(riidval, urival, domidval, idval), nonce(nonceval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  virtual const SPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

private:
  SPtr<ROAPNonce> nonce;
};

/*! \brief  Leave domain trigger data.
*/
class LeaveDomainTriggerData: public DomainTriggerData {
public:
  /*! \brief  Constructor.

      \param  riidval             rights issuer identifier.
      \param  nonceval            nonce.
      \param  urival              URL.
      \param  domidval            domain identifier.
      \param  idval               identifier.
  */
  LeaveDomainTriggerData(const NZSPtr<ROAPIdentifier>& riidval, const
    NZSPtr<ROAPNonce>& nonceval, const NZSPtr<URIValue>& urival,
    const NZSPtr<ROAPDomainIdentifier>& domidval, const NZSPtr<IDValue>& idval):
    DomainTriggerData(riidval, urival, domidval, idval), nonce(nonceval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  virtual const SPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

private:
  NZSPtr<ROAPNonce> nonce;
};

/*! \brief  Domain trigger.
*/
class DomainTrigger: public ROAPTrigger {
public:
  /*! \brief  Constructor.

      \param  ver                 version.
      \param  proxy               trigger proxy.
  */
  DomainTrigger(const NZSPtr<ROAPVersion>& ver, const SPtr<ROAPTriggerProxy>&
    proxy): ROAPTrigger(ver, proxy) {
  }

  /*! \brief  Get trigger data.

      \returns  Trigger data.
  */
  virtual const NZSPtr<DomainTriggerData>& GetTriggerData() const = 0;
};

/*! \brief  Join domain trigger.
*/
class JoinDomainTrigger: public DomainTrigger {
public:
  /*! \brief  Constructor.

      \param  tdata               trigger data.
      \param  sig                 signature.
      \param  ver                 version.
      \param  proxy               trigger proxy.
  */
  JoinDomainTrigger(const NZSPtr<JoinDomainTriggerData>& tdata, const
    SPtr<DSSignature>& sig, const NZSPtr<ROAPVersion>& ver, const
    SPtr<ROAPTriggerProxy>& proxy): DomainTrigger(ver, proxy), data(tdata),
    signature(sig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get trigger data.

      \returns  Trigger data.
  */
  virtual const NZSPtr<DomainTriggerData>& GetTriggerData() const {
    return data;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const SPtr<DSSignature>& GetSignature() const {
    return signature;
  }

private:
  NZSPtr<DomainTriggerData> data;
  SPtr<DSSignature> signature;
};

/*! \brief  Leave domain trigger.
*/
class LeaveDomainTrigger: public DomainTrigger {
public:
  /*! \brief  Constructor.

      \param  tdata               trigger data.
      \param  sig                 signature.
      \param  enc                 encrypte key.
      \param  ver                 version.
      \param  proxy               trigger proxy.
  */
  LeaveDomainTrigger(const NZSPtr<LeaveDomainTriggerData>& tdata, const
    NZSPtr<DSSignature>& sig, const SPtr<XencEncryptedKey>& enc,
    const NZSPtr<ROAPVersion>& ver, const SPtr<ROAPTriggerProxy>& proxy):
    DomainTrigger(ver, proxy), data(tdata), signature(sig), key(enc) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get trigger data.

      \returns  Trigger data.
  */
  virtual const NZSPtr<DomainTriggerData>& GetTriggerData() const {
    return data;
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  const SPtr<DSSignature>& GetSignature() const {
    return signature;
  }

  /*! \brief  Get encrypted key.

      \returns  Encrypted key.
  */
  const SPtr<XencEncryptedKey>& GetEncKey() const {
    return key;
  }

private:
  NZSPtr<DomainTriggerData> data;
  NZSPtr<DSSignature> signature;
  SPtr<XencEncryptedKey> key;
};

/*! \brief  Initial content rights objects request message.

    This is not OMA DRM message, and it is used to initiate content rights
    objects acquisition protocol. Response to this message must be a trigger,
    either a registration trigger, if device is not yet registered, or a rights
    objects acquisition trigger, if device is registered and corresponding
    rights objects exist.
*/
class InitialRORequest: public XmlData {
public:
  /*! \brief  Constructor.

      Size of content identifiers vector must be >= 1.

      \param  rhs               initial rights objects request.

      If fails, throws ROAPException.
  */
  InitialRORequest(const NZSPtr<InitialRORequest>& rhs): deviceID(rhs->GetDeviceID()),
      contentIDs(rhs->GetContentIDs()) {
    if (contentIDs.size() < 1) {
      throw ROAPException();
    }
  }

  /*! \brief  Constructor.

      Size of content identifiers vector must be >= 1.

      \param  devid               device identifier.
      \param  idvals              content identifiers vector.

      If fails, throws ROAPException.
  */
  InitialRORequest(const NZSPtr<ROAPIdentifier>& devid, const
      std::vector<NZSPtr<URIValue> >& idvals): deviceID(devid), contentIDs(idvals) {
    if (contentIDs.size() < 1) {
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

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetDeviceID() const {
    return deviceID;
  }

  /*! \brief  Get content identifiers vector.

      \returns  Content identifiers vector.
  */
  const std::vector<NZSPtr<URIValue> >& GetContentIDs() const {
    return contentIDs;
  }

protected:
  NZSPtr<ROAPIdentifier> deviceID;
  std::vector<NZSPtr<URIValue> > contentIDs;
};

/*! \brief  Add content encryption key request.

    This is not OMA DRM message. It is used during content protection process.
    It is sent by encoding side to the server to add the (content, key)
    context.
*/
class AddContentKeyRequest: public XmlData {
public:
  /*! \brief  Constructor.

      \param  content         content identifier.
      \param  enckey          content encryption key.
      \param  nonceval        nonce.
  */
  AddContentKeyRequest(const NZSPtr<URIValue>& content, const Base64StringT& enckey,
    const NZSPtr<ROAPNonce>& nonceval): contentID(content), key(enckey),
    nonce(nonceval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get content identifier.

      \returns  Content identifier.
  */
  const NZSPtr<URIValue>& GetContentID() const {
    return contentID;
  }

  /*! \brief  Get content encryption key.

      \returns  Content encryption key.
  */
  const Base64StringT& GetKey() const {
    return key;
  }

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  const NZSPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

private:
  NZSPtr<URIValue> contentID;
  Base64StringT key;
  NZSPtr<ROAPNonce> nonce;
};

/*! \brief  Add content encryption key response.

    This is not OMA DRM message. It is used during content protection process.
    It is sent by the server to the encoding side as a response to
    AddContentKeyRequest message.
*/
class AddContentKeyResponse: public XmlData {
public:
  /*! \brief  Constructor.

      \param  flag          success flag.
      \param  nonceval      nonce.
  */
  AddContentKeyResponse(bool flag, const NZSPtr<ROAPNonce>& nonceval): success(flag),
    nonce(nonceval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get success flag.

      \returns  Success flag.
  */
  bool GetSuccess() const {
    return success;
  }

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  const NZSPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

private:
  bool success;
  NZSPtr<ROAPNonce> nonce;
};

/*! \brief  Add rights for device for content request.

    This is not OMA DRM message. It is used during content protection process.
    It is sent by encoding side to the server to add the (rights, device, content)
    context.
*/
class AddDeviceRightsRequest: public XmlData {
public:
  /*! \brief  Constructor.
      
      \param  rghts           rights.
      \param  device          device identifier.
      \param  content         content identifier.
      \param  nonceval        nonce.
  */
  AddDeviceRightsRequest(const NZSPtr<OEXRights>& rghts, const
    NZSPtr<ROAPIdentifier>& device, const NZSPtr<URIValue>& content, const
    NZSPtr<ROAPNonce>& nonceval): rights(rghts), deviceID(device),
    contentID(content), nonce(nonceval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get rights.

      \returns  Rights.
  */
  const NZSPtr<OEXRights>& GetRights() const {
    return rights;
  }

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetDeviceID() const {
    return deviceID;
  }

  /*! \brief  Get content identifier.

      \returns  Content identifier.
  */
  const NZSPtr<URIValue>& GetContentID() const {
    return contentID;
  }

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  const NZSPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

private:
  NZSPtr<OEXRights> rights;
  NZSPtr<ROAPIdentifier> deviceID;
  NZSPtr<URIValue> contentID;
  NZSPtr<ROAPNonce> nonce;
};

/*! \brief  Add rights for device for content response.

    This is not OMA DRM message. It is used during content protection process.
    It is sent by the server to the encoding side as a response to
    AddDeviceRightsRequest.
*/
class AddDeviceRightsResponse: public XmlData {
public:
  /*! \brief  Constructor.

      \param  flag          success flag.
      \param  nonceval      nonce.
  */
  AddDeviceRightsResponse(bool flag, const NZSPtr<ROAPNonce>& nonceval): success(flag),
    nonce(nonceval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
  virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get success flag.

      \returns  Success flag.
  */
  bool GetSuccess() const {
    return success;
  }

  /*! \brief  Get nonce.

      \returns  Nonce.
  */
  const NZSPtr<ROAPNonce>& GetNonce() const {
    return nonce;
  }

private:
  bool success;
  NZSPtr<ROAPNonce> nonce;
};

} // namespace DRMPlugin

#endif // !defined (ROAPMESSAGES_H)
