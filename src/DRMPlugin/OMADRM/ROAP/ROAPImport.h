/** \file ROAPImport.h

    OMA DRM imported classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (ROAPIMPORT_H)
#define ROAPIMPORT_H

#include "GC.h"
#include "BasicTypes.h"
#include <vector>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Exception used for ROAP error.
*/
class ROAPException {
};

/*! \brief  Data that is encoded as XML.
*/
class XmlData: public GC {
public:
  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const = 0;
};

/*! \brief  Identifier value.
*/
class IDValue: public GC {
public:
  /*! \brief  Constructor.

      \param  id            identifier value string.
  */
  IDValue(const std::string& id): val(id) {
  }

  /*! \brief  Less operator.

      \param  rhs           input, identifier value.

      \returns  Boolean indicating if this identifier value is less than rhs.
  */
  bool operator < (const IDValue& rhs) const {
    return (val < rhs.val);
  }

  /*! \brief  Equality operator.

      \param  rhs           input, identifier value.

      \returns  Boolean indicating if this identifier value is equal to rhs.
  */
  bool operator == (const IDValue& rhs) const {
    return (val == rhs.val);
  }

  /*! \brief  Get identifier value string.

      \returns  Identifier value string.
  */
  const std::string& Get() const {
    return val;
  }

private:
  std::string val;
};

/*! \brief  URI value.
*/
class URIValue: public XmlData {
public:
  /*! \brief  Constructor.

      \param  uri           URI value string.
  */
  URIValue(const std::string& uri): val(uri) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Less operator.

      \param  rhs           input, URI value.

      \returns  Boolean indicating if this URI value is less than rhs.
  */
  bool operator < (const URIValue& rhs) const {
    return (val < rhs.val);
  }

  /*! \brief  Equality operator.

      \param  rhs           input, URI value.

      \returns  Boolean indicating if this URI value is equal to rhs.
  */
  bool operator == (const URIValue& rhs) const {
    return (val == rhs.val);
  }

  /*! \brief  Get URI value string.

      \returns  URI value string.
  */
  const std::string& Get() const {
    return val;
  }

private:
  std::string val;
};

/*! \brief  Object.
*/
class DSObject: public XmlData {
public:
  /*! \brief  Constructor.

      \param  idval         identifier value.
      \param  urival        URI value.
  */
  DSObject(const SPtr<IDValue>& idval, const SPtr<URIValue>& urival): id(idval),
    uri(urival) {
  }

  /*! \brief  Get identifier value.

      \returns  Identifier value.
  */
  const SPtr<IDValue>& GetID() const {
    return id;
  }

  /*! \brief  Get URI value.

      \returns  URI value.
  */
  const SPtr<URIValue>& GetURI() const {
    return uri;
  }

protected:
  SPtr<IDValue> id;
  SPtr<URIValue> uri;
};

/*! \brief  Object with MIME type.
*/
class MimeDSObject: public DSObject {
public:
  /*! \brief  Constructor.

      \param  idval         identifier value.
      \param  typ           MIME type.
      \param  urival        URI value.
  */
  MimeDSObject(const SPtr<IDValue>& idval, const std::string& typ,
    const SPtr<URIValue>& urival): DSObject(idval, urival), mime(typ) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get MIME type.

      \returns  MIME type.
  */
  const std::string& GetMIMEType() const {
    return mime;
  }

private:
  std::string mime;
};

/*! \brief  DSObject without mime type.
*/
class NMimeDSObject: public DSObject {
public:
  /*! \brief  Constructor.

      \param  idval         identifier value.
      \param  urival        URI value.
  */
  NMimeDSObject(const SPtr<IDValue>& idval, const SPtr<URIValue>& urival):
    DSObject(idval, urival) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
};

/*! \brief  Crypto binary value.
*/
class DSCryptoBinary: public XmlData {
public:
  /*! \brief  Constructor.

      \param  bin           crypto binary value string.
  */
  DSCryptoBinary(const Base64StringT& bin): val(bin) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get crypto binary value string.

      \returns   Binary value string.
  */
  const Base64StringT& Get() const {
    return val;
  }

private:
  Base64StringT val;
};

/*! \brief  Basic key information.
*/
class BasicKeyInfo: public XmlData {
};

/*! \brief  Key name.
*/
class DSKeyName: public BasicKeyInfo {
public:
  /*! \brief  Constructor.

      \param  name          key name string.
  */
  DSKeyName(const std::string& name): val(name) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get key name string.

      \returns   Key name string.
  */
  const std::string& Get() const {
    return val;
  }

private:
  std::string val;
};

/*! \brief  Key value.
*/
class DSKeyValue: public BasicKeyInfo {
};

/*! \brief  DSA key value P and Q parameters.
*/
class DSDSAKeyValuePQ: public GC {
public:
  /*! \brief  Constructor.

      \param  pparam          DSA p parameter.
      \param  qparam          DSA q parameter.
  */
  DSDSAKeyValuePQ(const NZSPtr<DSCryptoBinary>& pparam, const NZSPtr<DSCryptoBinary>&
    qparam): p(pparam), q(qparam) {
  }

  /*! \brief  Encode as XML string.

      \returns  Encoded XML string.
  */
	std::string XmlEncode() const;

  /*! \brief  Get DSA p parameter.

      \returns   DSA p parameter.
  */
  const NZSPtr<DSCryptoBinary>& GetP() const {
    return p;
  }

  /*! \brief  Get DSA p parameter.

      \returns   DSA p parameter.
  */
  const NZSPtr<DSCryptoBinary>& GetQ() const {
    return q;
  }

private:
  NZSPtr<DSCryptoBinary> p;
  NZSPtr<DSCryptoBinary> q;
};

/*! \brief  DSA key value seed and counter.
*/
class DSDSAKeyValueSeedCtr: public GC {
public:
  /*! \brief  Constructor.

      \param  seedparam       DSA seed parameter.
      \param  ctrparam        DSA counter parameter.
  */
  DSDSAKeyValueSeedCtr(const NZSPtr<DSCryptoBinary>& seedparam, const
    NZSPtr<DSCryptoBinary>& ctrparam): seed(seedparam), counter(ctrparam) {
  }

  /*! \brief  Encode as XML string.

      \returns  Encoded XML string.
  */
	std::string XmlEncode() const;

  /*! \brief  Get DSA seed parameter.

      \returns   DSA seed parameter.
  */
  const NZSPtr<DSCryptoBinary>& GetSeed() const {
    return seed;
  }

  /*! \brief  Get DSA counter parameter.

      \returns   DSA counter parameter.
  */
  const NZSPtr<DSCryptoBinary>& GetCounter() const {
    return counter;
  }

private:
  NZSPtr<DSCryptoBinary> seed;
  NZSPtr<DSCryptoBinary> counter;
};

/*! \brief  DSA key value.
*/
class DSDSAKeyValue: public DSKeyValue {
public:
  /*! \brief  Constructor.

      \param  pqparam         DSA p and q parameters.
      \param  gparam          DSA g parameter.
      \param  yparam          DSA y parameter.
      \param  jparam          DSA j parameter.
      \param  seedctrparam    DSA seed and counter parameters.
  */
  DSDSAKeyValue(const SPtr<DSDSAKeyValuePQ>& pqparam, const SPtr<DSCryptoBinary>&
    gparam, const NZSPtr<DSCryptoBinary>& yparam, const SPtr<DSCryptoBinary>& jparam,
    const SPtr<DSDSAKeyValueSeedCtr>& seedctrparam): pq(pqparam), g(gparam),
    y(yparam), j(jparam), seedCtr(seedctrparam) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get DSA p and q parameters.

      \returns   DSA p and q parameters.
  */
  const SPtr<DSDSAKeyValuePQ>& GetPQ() const {
    return pq;
  }

  /*! \brief  Get DSA g parameter.

      \returns   DSA g parameter.
  */
  const SPtr<DSCryptoBinary>& GetG() const {
    return g;
  }

  /*! \brief  Get DSA y parameter.

      \returns   DSA y parameter.
  */
  const NZSPtr<DSCryptoBinary>& GetY() const {
    return y;
  }

  /*! \brief  Get DSA j parameter.

      \returns   DSA j parameter.
  */
  const SPtr<DSCryptoBinary>& GetJ() const {
    return j;
  }

  /*! \brief  Get DSA seed and counter parameters.

      \returns   DSA seed and counter parameters.
  */
  const SPtr<DSDSAKeyValueSeedCtr>& GetSeedCtr() const {
    return seedCtr;
  }

private:
  SPtr<DSDSAKeyValuePQ> pq;
  SPtr<DSCryptoBinary> g;
  NZSPtr<DSCryptoBinary> y;
  SPtr<DSCryptoBinary> j;
  SPtr<DSDSAKeyValueSeedCtr> seedCtr;
};

/*! \brief  RSA key value.
*/
class DSRSAKeyValue: public DSKeyValue {
public:
  /*! \brief  Constructor.

      \param  modparam        RSA modulus parameters.
      \param  expparam        RSA exponent parameter.
  */
  DSRSAKeyValue(const NZSPtr<DSCryptoBinary>& modparam, const NZSPtr<DSCryptoBinary>&
    expparam): modulus(modparam), exponent(expparam) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get RSA modulus parameter.

      \returns   RSA modulus parameter.
  */
  const NZSPtr<DSCryptoBinary>& Modulus() const {
    return modulus;
  }

  /*! \brief  Get RSA exponent parameter.

      \returns   RSA exponent parameter.
  */
  const NZSPtr<DSCryptoBinary>& Exponent() const {
    return exponent;
  }

private:
  NZSPtr<DSCryptoBinary> modulus;
  NZSPtr<DSCryptoBinary> exponent;
};

/*! \brief  Transformation.
*/
class DSTransform: public XmlData {
public:
  /*! \brief  Constructor.

      \param  urival          algorithm URI value.
  */
  DSTransform(const NZSPtr<URIValue>& urival): algorithm(urival) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get algorithm URI value.

      \returns   Algorithm URI value.
  */
  const NZSPtr<URIValue>& GetAlgorithm() const {
    return algorithm;
  }

private:
  NZSPtr<URIValue> algorithm;
};

/*! \brief  Transformations.
*/
class DSTransforms: public XmlData {
public:
  /*! \brief  Constructor.

      Size of transformation vector must be >= 1.

      \param  trans           transformation vector.

      If fails, throws ROAPException.
  */
  DSTransforms(const std::vector<NZSPtr<DSTransform> >& trans): transforms(trans) {
    if (transforms.size() < 1) {
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

  /*! \brief  Get transformations vector.

      \returns   Transformations vector.
  */
  const std::vector<NZSPtr<DSTransform> >& GetTransforms() const {
    return transforms;
  }

private:
  std::vector<NZSPtr<DSTransform> > transforms;
};

/*! \brief  Retrieval method.
*/
class DSRetrievalMethod: public BasicKeyInfo {
public:
  /*! \brief  Constructor.

      \param  trans           transformations.
      \param  urival          URI value.
      \param  typ             type.
  */
  DSRetrievalMethod(const SPtr<DSTransforms>& trans, const NZSPtr<URIValue>& urival,
    const SPtr<URIValue>& typ): transformations(trans), uri(urival), type(typ) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get transformations.

      \returns   Transformations.
  */
  const SPtr<DSTransforms>& GetTransformations() const {
    return transformations;
  }

  /*! \brief  Get URI value.

      \returns   URI value.
  */
  const NZSPtr<URIValue>& GetURI() const {
    return uri;
  }

  /*! \brief  Get type.

      \returns   Type.
  */
  const SPtr<URIValue>& GetType() const {
    return type;
  }

protected:
  SPtr<DSTransforms> transformations;
  NZSPtr<URIValue> uri;
  SPtr<URIValue> type;
};

/*! \brief  Basic X509 data.
*/
class BasicX509Data: public XmlData {
};

/*! \brief  X509 issuer name and serial.
*/
class DSX509IssuerSerial: public BasicX509Data {
public:
  /*! \brief  Constructor.

      \param  issuer          issuer name.
      \param  number          serial.
  */
  DSX509IssuerSerial(const std::string& issuer, UInt32T number): name(issuer),
    serial(number) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get name.

      \returns   Name.
  */
  const std::string& GetName() const {
    return name;
  }

  /*! \brief  Get serial.

      \returns   Serial.
  */
  UInt32T GetSerial() const {
    return serial;
  }

private:
  std::string name;
  UInt32T serial;
};

/*! \brief  X509 subject key identifier.
*/
class DSX509SKI: public BasicX509Data {
public:
  /*! \brief  Constructor.

      \param  id            key identifier string.
  */
  DSX509SKI(const Base64StringT& id): identifier(id) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get identifier string.

      \returns   Identifier string.
  */
  const Base64StringT& Get() const {
    return identifier;
  }

private:
  Base64StringT identifier;
};

/*! \brief  X509 subject name.
*/
class DSX509SubjectName: public BasicX509Data {
public:
  /*! \brief  Constructor.

      \param  subject           subject name string.
  */
  DSX509SubjectName(const std::string& subject): name(subject) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get name string.

      \returns   Name string.
  */
  const std::string& Get() const {
    return name;
  }

private:
  std::string name;
};

/*! \brief  X509 certificate.
*/
class DSX509Certificate: public BasicX509Data {
public:
  /*! \brief  Constructor.

      \param  cert            certificate string.
  */
  DSX509Certificate(const Base64StringT& cert): certificate(cert) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get certificate string.

      \returns   Certificate string.
  */
  const Base64StringT& Get() const {
    return certificate;
  }

private:
  Base64StringT certificate;
};

/*! \brief  X509 CRL.
*/
class DSX509CRL: public BasicX509Data {
public:
  /*! \brief  Constructor.

      \param  list            CRL string.
  */
  DSX509CRL(const Base64StringT& list): crl(list) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get CRL string.

      \returns   CRL string.
  */
  const Base64StringT& Get() const {
    return crl;
  }

private:
  Base64StringT crl;
};

/*! \brief  X509 data.
*/
class DSX509Data: public BasicKeyInfo {
public:
  /*! \brief  Constructor.

      Size of basic data must be >= 1.

      \param  data              basic data vector.

      If fails, throws ROAPException.
  */
  DSX509Data(const std::vector<NZSPtr<BasicX509Data> >& data): basics(data) {
    if (basics.size() < 1) {
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

  /*! \brief  Get basic data vector.

      \returns   Basic data vector.
  */
  const std::vector<NZSPtr<BasicX509Data> >& GetBasics() const {
    return basics;
  }

private:
  std::vector<NZSPtr<BasicX509Data> > basics;
};

/*! \brief  PGPData.
*/
class DSPGPData: public BasicKeyInfo {
};

/*! \brief  PGP data with PGP key identifier.
*/
class KeyIDDSPGPData: public DSPGPData {
public:
  /*! \brief  Constructor.

      \param  id                PGP key identifier string.
  */
  KeyIDDSPGPData(const Base64StringT& id): identifier(id) {
  }

  /*! \brief  Get PGP key identifier string.

      \returns   PGP key identifier string.
  */
  const Base64StringT& GetPGPKeyID() const {
    return identifier;
  }

protected:
  Base64StringT identifier;
};

/*! \brief  PGP data with PGP key identifier and PGP key packet.
*/
class KeyPacketKeyIDDSPGPData: public KeyIDDSPGPData {
public:
  /*! \brief  Constructor.

      \param  id                PGP key identifier string.
      \param  pack              PGP key packet string.
  */
  KeyPacketKeyIDDSPGPData(const Base64StringT& id, const Base64StringT& pack):
    KeyIDDSPGPData(id), packet(pack) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get PGP key packet string.

      \returns   PGP key packet string.
  */
  const Base64StringT& GetPGPKeyPacket() const {
    return packet;
  }

private:
  Base64StringT packet;
};

/*! \brief  PGP data with PGP key identifier and without PGP key packet.
*/
class NKeyPacketKeyIDDSPGPData: public KeyIDDSPGPData {
public:
  /*! \brief  Constructor.

      \param  id                PGP key identifier string.
  */
  NKeyPacketKeyIDDSPGPData(const Base64StringT& id): KeyIDDSPGPData(id) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
};

/*! \brief  PGP data with PGP key packet (and no PGP key identifier).
*/
class KeyPacketDSPGPData: public DSPGPData {
public:
  /*! \brief  Constructor.

      \param  pack            PGP key packet string.
  */
  KeyPacketDSPGPData(const Base64StringT& pack): packet(pack) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get PGP key packet string.

      \returns   PGP key packet string.
  */
  const Base64StringT& PGPKeyPacket() const {
    return packet;
  }

private:
  Base64StringT packet;
};

/*! \brief  SPKI data.
*/
class DSSPKIData: public BasicKeyInfo {
public:
  /*! \brief  Constructor.

      Size of SEXP vector must be >= 1.

      \param  sxp           SEXP vector.

      If fails, throws ROAPException.
  */
  DSSPKIData(const std::vector<Base64StringT>& sxp): sexps(sxp) {
    if (sexps.size() < 1) {
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

  /*! \brief  Get SEXP vector.

      \returns   SEXP vector.
  */
  const std::vector<Base64StringT>& GetSEXPs() const {
    return sexps;
  }

private:
  std::vector<Base64StringT> sexps;
};

/*! \brief  Mgmt data.
*/
class DSMgmtData: public BasicKeyInfo {
public:
  /*! \brief  Constructor.

      \param  mgmt              data string.
  */
  DSMgmtData(const std::string& mgmt): val(mgmt) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get mgmt data string.

      \returns   Mgmt data string.
  */
  const std::string& Get() const {
    return val;
  }

private:
  std::string val;
};

/*! \brief  Key info.
*/
class DSKeyInfo: public XmlData {
public:
  /*! \brief  Constructor.

      \param  infos                 basic key informations.
      \param  idval                 identifier value.
  */
  DSKeyInfo(const std::vector<NZSPtr<BasicKeyInfo> >& infos, const SPtr<IDValue>&
    idval): basics(infos), id(idval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get basic key informations.

      \returns   Basic key informations.
  */
  const std::vector<NZSPtr<BasicKeyInfo> >& GetBasics() const {
    return basics;
  }

  /*! \brief  Get identifier.

      \returns   Identifier.
  */
  const SPtr<IDValue>& GetID() const {
    return id;
  }

private:
  std::vector<NZSPtr<BasicKeyInfo> > basics;
  SPtr<IDValue> id;
};

/*! \brief  Signature value.
*/
class DSSignatureValue: public XmlData {
public:
  /*! \brief  Constructor.

      \param  sig                   signature string.
      \param  idval                 identifier value.
  */
  DSSignatureValue(const Base64StringT& sig, const SPtr<IDValue>& idval):
    val(sig), id(idval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get signature string.

      \returns   Signature string.
  */
  const Base64StringT& Get() const {
    return val;
  }

  /*! \brief  Get identifier.

      \returns   Identifier.
  */
  const SPtr<IDValue>& ID() const {
    return id;
  }

private:
  Base64StringT val;
  SPtr<IDValue> id;
};

/*! \brief  Digest value.
*/
class DSDigestValue: public XmlData {
public:
  /*! \brief  Constructor.

      \param  dig                   digest string.
  */
  DSDigestValue(const Base64StringT& dig): val(dig) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get digest string.

      \returns   Digest string.
  */
  const Base64StringT& Get() const {
    return val;
  }

private:
  Base64StringT val;
};

/*! \brief  Digest method.
*/
class DSDigestMethod: public XmlData {
public:
  /*! \brief  Constructor.

      \param  alg                   algorithm.
  */
  DSDigestMethod(const NZSPtr<URIValue>& alg): algorithm(alg) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get digest algorithm string.

      \returns   Digest algorithm string.
  */
  const NZSPtr<URIValue>& GetAlgorithm() const {
    return algorithm;
  }

protected:
  NZSPtr<URIValue> algorithm;
};

/*! \brief  Reference.
*/
class DSReference: public XmlData {
public:
  /*! \brief  Constructor.

      \param  trans                     tranformations.
      \param  meth                      digest method.
      \param  val                       digest value.
      \param  idval                     identifier value.
      \param  urival                    URI value.
      \param  typ                       type.
  */
  DSReference(const SPtr<DSTransforms>& trans, const NZSPtr<DSDigestMethod>& meth,
    const NZSPtr<DSDigestValue>& val, const SPtr<IDValue>& idval,
    const SPtr<URIValue>& urival, const SPtr<URIValue>& typ): transformations(trans),
    method(meth), value(val), id(idval), uri(urival), type(typ) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get transformations.

      \returns   Transformations.
  */
  const SPtr<DSTransforms>& GetTransformations() const {
    return transformations;
  }

  /*! \brief  Get digest method.

      \returns   Digest method.
  */
  const NZSPtr<DSDigestMethod>& GetDigestMethod() const {
    return method;
  }

  /*! \brief  Get digest value.

      \returns   Digest value.
  */
  const NZSPtr<DSDigestValue>& GetDigestValue() const {
    return value;
  }

  /*! \brief  Get identifier.

      \returns   Identifier.
  */
  const SPtr<IDValue>& GetID() const {
    return id;
  }

  /*! \brief  Get URI.

      \returns   URI.
  */
  const SPtr<URIValue>& GetURI() const {
    return uri;
  }

  /*! \brief  Get type.

      \returns   Type.
  */
  const SPtr<URIValue>& GetType() const {
    return type;
  }

private:
  SPtr<DSTransforms> transformations;
  NZSPtr<DSDigestMethod> method;
  NZSPtr<DSDigestValue> value;
  SPtr<IDValue> id;
  SPtr<URIValue> uri;
  SPtr<URIValue> type;
};

/*! \brief  MAC output length.
*/
class DSHMACOutputLength: public XmlData {
public:
  /*! \brief  Constructor.

      \param  len               length value.
  */
  DSHMACOutputLength(UInt32T len): val(len) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get length value.

      \returns   Length value.
  */
  UInt32T Get() const {
    return val;
  }

private:
  UInt32T val;
};

/*! \brief  Signature method.
*/
class DSSignatureMethod: public XmlData {
public:
  /*! \brief  Constructor.

      \param  mac               MAC length.
      \param  urival            algorithm URI value.
  */
  DSSignatureMethod(const SPtr<DSHMACOutputLength>& mac, const NZSPtr<URIValue>&
    urival): macLength(mac), algorithm(urival) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get MAC length.

      \returns   MAC length.
  */
  const SPtr<DSHMACOutputLength>& GetMacLength() const {
    return macLength;
  }

  /*! \brief  Get algorithm URI.

      \returns   Algorithm URI.
  */
  const NZSPtr<URIValue>& GetAlgorithm() const {
    return algorithm;
  }

private:
  SPtr<DSHMACOutputLength> macLength;
  NZSPtr<URIValue> algorithm;
};

/*! \brief  Canonicalization method.
*/
class DSCanonicalizationMethod: public XmlData {
public:
  /*! \brief  Constructor.

      \param  urival            algorithm URI value.
  */
  DSCanonicalizationMethod(const NZSPtr<URIValue>& urival): algorithm(urival) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get algorithm URI.

      \returns   Algorithm URI.
  */
  const NZSPtr<URIValue>& GetAlgorithm() const {
    return algorithm;
  }

private:
  NZSPtr<URIValue> algorithm;
};

/*! \brief  Signed information.
*/
class DSSignedInfo: public XmlData {
public:
  /*! \brief  Constructor.

      Size of reference vector must be >= 1.

      \param  can               canonicalization method.
      \param  sig               signature method.
      \param  refs              references.
      \param  idval             identifier.

      If fails, throws ROAPException.
  */
  DSSignedInfo(const NZSPtr<DSCanonicalizationMethod>& can, const
      NZSPtr<DSSignatureMethod>& sig, const std::vector<NZSPtr<DSReference> >& refs,
      const SPtr<IDValue>& idval): canonMethod(can), sigMethod(sig), references(refs),
      id(idval) {
    if (references.size() < 1) {
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

  /*! \brief  Get canonicalization method.

      \returns   Canonicalization method.
  */
  const NZSPtr<DSCanonicalizationMethod>& GetCanonMethod() const {
    return canonMethod;
  }

  /*! \brief  Get signature method.

      \returns   Signature method.
  */
  const NZSPtr<DSSignatureMethod>& GetSigMethod() const {
    return sigMethod;
  }

  /*! \brief  Get references.

      \returns   References.
  */
  const std::vector<NZSPtr<DSReference> >& GetReferences() const {
    return references;
  }

  /*! \brief  Get identifier.

      \returns   Identifier.
  */
  const SPtr<IDValue>& GetID() const {
    return id;
  }

private:
  NZSPtr<DSCanonicalizationMethod> canonMethod;
  NZSPtr<DSSignatureMethod> sigMethod;
  std::vector<NZSPtr<DSReference> > references;
  SPtr<IDValue> id;
};

/*! \brief  Signature.
*/
class DSSignature: public XmlData {
public:
  /*! \brief  Constructor.

      \param  inf               signed info.
      \param  val               signature value.
      \param  kinf              key information.
      \param  objs              objects vector.
      \param  idval             identifier.
  */
  DSSignature(const NZSPtr<DSSignedInfo>& inf, const NZSPtr<DSSignatureValue>& val,
    const SPtr<DSKeyInfo>& kinf, const std::vector<NZSPtr<DSObject> >& objs,
    const SPtr<IDValue>& idval): info(inf), value(val), key(kinf), objects(objs),
    id(idval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get signed info.

      \returns   Signed info.
  */
  const NZSPtr<DSSignedInfo>& GetInfo() const {
    return info;
  }

  /*! \brief  Get signature value.

      \returns   Signature value.
  */
  const NZSPtr<DSSignatureValue>& GetValue() const {
    return value;
  }

  /*! \brief  Get key info.

      \returns   Key info.
  */
  const SPtr<DSKeyInfo>& GetKeyInfo() const {
    return key;
  }

  /*! \brief  Get objects.

      \returns   Objects.
  */
  const std::vector<NZSPtr<DSObject> >& GetObjects() const {
    return objects;
  }

  /*! \brief  Get identifier.

      \returns   Identifier.
  */
  const SPtr<IDValue>& GetID() const {
    return id;
  }

private:
  NZSPtr<DSSignedInfo> info;
  NZSPtr<DSSignatureValue> value;
  SPtr<DSKeyInfo> key;
  std::vector<NZSPtr<DSObject> > objects;
  SPtr<IDValue> id;
};

/*! \brief  Encrypted key size.
*/
class XencKeySize: public XmlData {
public:
  /*! \brief  Constructor.

      \param  siz                 size value.
  */
  XencKeySize(UInt32T siz): val(siz) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get key size value.

      \returns   Key size value.
  */
  UInt32T Get() const {
    return val;
  }

private:
  UInt32T val;
};

/*! \brief  Encryption method.
*/
class XencEncryptionMethod: public XmlData {
public:
  /*! \brief  Constructor.

      \param  siz                 key size.
      \param  alg                 algorithm URI value.
  */
  XencEncryptionMethod(const SPtr<XencKeySize>& siz, const NZSPtr<URIValue>& alg):
    size(siz), algorithm(alg) {
  }

  /*! \brief  Get key size.

      \returns   Key size.
  */
  const SPtr<XencKeySize>& GetKeySize() const {
    return size;
  }

  /*! \brief  Get algorithm URI.

      \returns   Algorithm URI.
  */
  const NZSPtr<URIValue>& GetAlgorithm() const {
    return algorithm;
  }

protected:
  SPtr<XencKeySize> size;
  NZSPtr<URIValue> algorithm;
};

/*! \brief  Encryption method with OAEP parameters.
*/
class OAEPXencEncryptionMethod: public XencEncryptionMethod {
public:
  /*! \brief  Constructor.

      \param  siz                 key size.
      \param  pars                OAEP parameters string.
      \param  alg                 algorithm URI value.
  */
  OAEPXencEncryptionMethod(const SPtr<XencKeySize>& siz, const Base64StringT& pars,
    const NZSPtr<URIValue>& alg): XencEncryptionMethod(siz, alg), oaep(pars) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get OAEP parameters string.

      \returns   OAEP parameters string.
  */
  const Base64StringT& GetOAEPParams() const {
    return oaep;
  }

private:
  Base64StringT oaep;
};

/*! \brief  Encryption method without OAEP parameters.
*/
class NOAEPXencEncryptionMethod: public XencEncryptionMethod {
public:
  /*! \brief  Constructor.

      \param  siz                 key size.
      \param  alg                 algorithm URI value.
  */
  NOAEPXencEncryptionMethod(const SPtr<XencKeySize>& siz, const NZSPtr<URIValue>& alg):
    XencEncryptionMethod(siz, alg) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
};

/*! \brief  Cipher data.
*/
class XencCipherData: public XmlData {
};

/*! \brief  Cipher data with cipher value.
*/
class CValueXencCipherData: public XencCipherData {
public:
  /*! \brief  Constructor.

      \param  ciph                cipher value string.
  */
  CValueXencCipherData(const Base64StringT& ciph): val(ciph) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get value string.

      \returns   Value string.
  */
  const Base64StringT& Get() const {
    return val;
  }

private:
  Base64StringT val;
};

/*! \brief  Transformations.
*/
class XencTransforms: public XmlData {
public:
  /*! \brief  Constructor.

      Size of transforms vector must be >= 1.

      \param  trans             transforms vector.

      If fails, throws ROAPException.
  */
  XencTransforms(const std::vector<NZSPtr<DSTransform> >& trans): transforms(trans) {
    if (transforms.size() < 1) {
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

  /*! \brief  Get transforms vector.

      \returns   Transforms vector.
  */
  const std::vector<NZSPtr<DSTransform> >& GetTransforms() const {
    return transforms;
  }

private:
  std::vector<NZSPtr<DSTransform> > transforms;
};

/*! \brief  Cipher reference.
*/
class XencCipherReference: public XmlData {
public:
  /*! \brief  Constructor.

      \param  trans             transformations.
      \param  urival            URI value.
  */
  XencCipherReference(const SPtr<XencTransforms>& trans, const NZSPtr<URIValue>&
    urival): transformations(trans), uri(urival) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get transformations.

      \returns   Transformations.
  */
  const SPtr<XencTransforms>& GetTransformations() const {
    return transformations;
  }

  /*! \brief  Get URI value.

      \returns   URI value.
  */
  const NZSPtr<URIValue>& URI() const {
    return uri;
  }

private:
  SPtr<XencTransforms> transformations;
  NZSPtr<URIValue> uri;
};

/*! \brief  Cipher data with cipher reference.
*/
class CRefXencCipherData: public XencCipherData {
public:
  /*! \brief  Constructor.

      \param  ref             reference.
  */
  CRefXencCipherData(const NZSPtr<XencCipherReference>& ref): reference(ref) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get reference.

      \returns   Reference.
  */
  const NZSPtr<XencCipherReference>& CipherReference() const {
    return reference;
  }

private:
  NZSPtr<XencCipherReference> reference;
};

/*! \brief  Encryption property.
*/
class XencEncryptionProperty: public XmlData {
public:
  /*! \brief  Constructor.

      \param  urival                URI value.
      \param  idval                 identifier value.
  */
  XencEncryptionProperty(const SPtr<URIValue>& urival, const SPtr<IDValue>& idval):
    uri(urival), id(idval) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get URI value.

      \returns   URI value.
  */
  const SPtr<URIValue>& GetURI() const {
    return uri;
  }

  /*! \brief  Get identifier value.

      \returns   Identifier value.
  */
  const SPtr<IDValue>& GetID() const {
    return id;
  }

private:
  SPtr<URIValue> uri;
  SPtr<IDValue> id;
};

/*! \brief  Encryption properties.
*/
class XencEncryptionProperties: public XmlData {
public:
  /*! \brief  Constructor.

      Size of property vector must be >= 1.

      \param  prop                  property vector.
      \param  idval                 identifier value.

      If fails, throws ROAPException.
  */
  XencEncryptionProperties(const std::vector<NZSPtr<XencEncryptionProperty> >& prop,
      const SPtr<IDValue>& idval): properties(prop), id(idval) {
    if (properties.size() < 1) {
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

  /*! \brief  Get properties vector.

      \returns   Properties vector.
  */
  const std::vector<NZSPtr<XencEncryptionProperty> >& GetProperties() const {
    return properties;
  }

  /*! \brief  Get identifier value.

      \returns   Identifier value.
  */
  const SPtr<IDValue>& GetID() const {
    return id;
  }

private:
  std::vector<NZSPtr<XencEncryptionProperty> > properties;
  SPtr<IDValue> id;
};

/*! \brief  MIME type.
*/
class XencEncryptedTypeMime: public GC {
public:
  /*! \brief  Constructor.

      \param  mime                  MIME type string.
  */
  XencEncryptedTypeMime(const std::string& mime): val(mime) {
  }

  /*! \brief  Get MIME type string.

      \returns   MIME type string.
  */
  const std::string& Get() const {
    return val;
  }

private:
  std::string val;
};

/*! \brief  Encrypted.
*/
class XencEncrypted: public XmlData {
public:
  /*! \brief  Constructor.

      \param  meth                  encryption method.
      \param  info                  key information.
      \param  ciph                  cipher data.
      \param  prop                  encryption properties.
      \param  idval                 identifier value.
      \param  typ                   type.
      \param  mtyp                  MIME type.
      \param  enc                   encoding value.
  */
  XencEncrypted(const SPtr<XencEncryptionMethod>& meth,
    const SPtr<DSKeyInfo>& info, const NZSPtr<XencCipherData>& ciph,
    const SPtr<XencEncryptionProperties>& prop, const SPtr<IDValue>& idval,
    const SPtr<URIValue>& typ, const SPtr<XencEncryptedTypeMime>& mtyp,
    const SPtr<URIValue>& enc): method(meth), key(info), cipher(ciph),
    properties(prop), id(idval), type(typ), mime(mtyp), encoding(enc) {
  }

  /*! \brief  Get encryption method.

      \returns   Encryption method.
  */
  const SPtr<XencEncryptionMethod>& GetEncMethod() const {
    return method;
  }

  /*! \brief  Get key info.

      \returns   Key info.
  */
  const SPtr<DSKeyInfo>& GetKeyInfo() const {
    return key;
  }

  /*! \brief  Get cipher data.

      \returns   Cipher data.
  */
  const NZSPtr<XencCipherData>& GetCipherData() const {
    return cipher;
  }

  /*! \brief  Get properties.

      \returns   Properties.
  */
  const SPtr<XencEncryptionProperties>& GetProperties() const {
    return properties;
  }

  /*! \brief  Get identifier value.

      \returns   Identifier value.
  */
  const SPtr<IDValue>& GetID() const {
    return id;
  }

  /*! \brief  Get type URI.

      \returns   Type URI.
  */
  const SPtr<URIValue>& GetType() const {
    return type;
  }

  /*! \brief  Get MIME type.

      \returns   MIME type.
  */
  const SPtr<XencEncryptedTypeMime>& GetMIMEType() const {
    return mime;
  }

  /*! \brief  Get encoding.

      \returns   Encoding.
  */
  const SPtr<URIValue>& GetEncoding() const {
    return encoding;
  }

protected:
  SPtr<XencEncryptionMethod> method;
  SPtr<DSKeyInfo> key;
  NZSPtr<XencCipherData> cipher;
  SPtr<XencEncryptionProperties> properties;
  SPtr<IDValue> id;
  SPtr<URIValue> type;
  SPtr<XencEncryptedTypeMime> mime;
  SPtr<URIValue> encoding;
};

/*! \brief  Reference type.
*/
class XencReferenceType: public XmlData {
public:
  /*! \brief  Constructor.

      \param  urival                URI value.
  */
  XencReferenceType(const NZSPtr<URIValue>& urival): uri(urival) {
  }

  /*! \brief  Get URI value.

      \returns   URI value.
  */
  const NZSPtr<URIValue>& GetURI() const {
    return uri;
  }

protected:
  NZSPtr<URIValue> uri;
};

/*! \brief  Data reference type.
*/
class DataXencReferenceType: public XencReferenceType {
public:
  /*! \brief  Constructor.

      \param  urival                URI value.
  */
  DataXencReferenceType(const NZSPtr<URIValue>& urival): XencReferenceType(urival) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
};

/*! \brief  Key reference type.
*/
class KeyXencReferenceType: public XencReferenceType {
public:
  /*! \brief  Constructor.

      \param  urival                URI value.
  */
  KeyXencReferenceType(const NZSPtr<URIValue>& urival): XencReferenceType(urival) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;
};

/*! \brief  Reference list.
*/
class XencReferenceList: public XmlData {
public:
  /*! \brief  Constructor.

      \param  drefs                     data references.
      \param  krefs                     key references.

      Total size of data reference vector and key reference vector must be
      at least 1. If not, throws ROAPException.
  */
  XencReferenceList(const std::vector<NZSPtr<DataXencReferenceType> >& drefs,
      const std::vector<NZSPtr<KeyXencReferenceType> >& krefs): dReferences(drefs),
      kReferences(krefs) {
    if ((dReferences.size() + kReferences.size()) == 0) {
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

  /*! \brief  Get data references.

      \returns   Data references.
  */
  const std::vector<NZSPtr<DataXencReferenceType> >& GetDataReferences() const {
    return dReferences;
  }

  /*! \brief  Get key references.

      \returns   Key references.
  */
  const std::vector<NZSPtr<KeyXencReferenceType> >& GetKeyReferences() const {
    return kReferences;
  }

private:
  std::vector<NZSPtr<DataXencReferenceType> > dReferences;
  std::vector<NZSPtr<KeyXencReferenceType> > kReferences;
};

/*! \brief  Encrypted key data (carried key name).
*/
class NameXencEncryptedKeyData: public XmlData {
public:
  /*! \brief  Constructor.

      \param  data              key data string.
  */
  NameXencEncryptedKeyData(const std::string& data): val(data) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get key data string.

      \returns   Key data string.
  */
  const std::string& Get() const {
    return val;
  }

private:
  std::string val;
};

/*! \brief  Encrypted key data (recipient).
*/
class RecXencEncryptedKeyData: public GC {
public:
  /*! \brief  Constructor.

      \param  data              key data string.
  */
  RecXencEncryptedKeyData(const std::string& data): val(data) {
  }

  /*! \brief  Get key data string.

      \returns   Key data string.
  */
  const std::string& Get() const {
    return val;
  }

private:
  std::string val;
};

/*! \brief  Encrypted key.
*/
class XencEncryptedKey: public XencEncrypted {
public:
  /*! \brief  Constructor.

      \param  meth                  encryption method.
      \param  info                  key information.
      \param  ciph                  cipher data.
      \param  prop                  encryption properties.
      \param  idval                 identifier value.
      \param  typ                   type.
      \param  mtyp                  MIME type.
      \param  enc                   encoding value.
      \param  rlist                 reference list.
      \param  car                   carried key name.
      \param  rec                   recipient.
  */
  XencEncryptedKey(const SPtr<XencEncryptionMethod>& meth,
    const SPtr<DSKeyInfo>& info, const NZSPtr<XencCipherData>& ciph,
    const SPtr<XencEncryptionProperties>& prop, const SPtr<IDValue>& idval,
    const SPtr<URIValue>& typ, const SPtr<XencEncryptedTypeMime>& mtyp,
    const SPtr<URIValue>& enc, const SPtr<XencReferenceList>& rlist,
    const SPtr<NameXencEncryptedKeyData>& car, const SPtr<RecXencEncryptedKeyData>&
    rec): XencEncrypted(meth, info, ciph, prop, idval, typ, mtyp, enc),
    reflist(rlist), carried(car), recipient(rec) {
  }

  /*! \brief  Encode as XML string.

      \param  varName         input, if != "" then XML header field is set
                              to varName, otherwise the namespace is set
                              as XML header field.

      \returns  Encoded XML string.
  */
	virtual std::string XmlEncode(const std::string& varName = "") const;

  /*! \brief  Get reference list.

      \returns   Reference list.
  */
  const SPtr<XencReferenceList>& GetReferenceList() const {
    return reflist;
  }

  /*! \brief  Get carried key name.

      \returns   Carried key name.
  */
  const SPtr<NameXencEncryptedKeyData>& GetCarriedKeyName() const {
    return carried;
  }

  /*! \brief  Get carried key name.

      \returns   Carried key name.
  */
  const SPtr<RecXencEncryptedKeyData>& GetRecipient() const {
    return recipient;
  }

private:
  SPtr<XencReferenceList> reflist;
  SPtr<NameXencEncryptedKeyData> carried;
  SPtr<RecXencEncryptedKeyData> recipient;
};

} // namespace DRMPlugin

#endif // !defined (ROAPIMPORT_H)
