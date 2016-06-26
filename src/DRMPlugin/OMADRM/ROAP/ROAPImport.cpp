/** \file ROAPImport.cpp

    OMA DRM imported classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "ROAPImport.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string URIValue::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("URI"): (varName));
  return "<" + vName + ">" + val + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string MimeDSObject::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("Object"): (varName));
  std::string ret("<" + vName);
  if (id != 0) {
    ret = ret + " Id=\"" + id->Get() + "\"";
  }
  ret = ret + " MimeType=\"" + mime + "\"";
  if (uri != 0) {
    ret = ret + " Encoding=\"" + uri->Get() + "\"";
  }
  return ret + "></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NMimeDSObject::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("Object"): (varName));
  std::string ret("<" + vName);
  if (id != 0) {
    ret = ret + " Id=\"" + id->Get() + "\"";
  }
  if (uri != 0) {
    ret = ret + " Encoding=\"" + uri->Get() + "\"";
  }
  return ret + "></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSCryptoBinary::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("CryptoBinary"): (varName));
  return "<" + vName + ">" + val.BString() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSKeyName::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("KeyName"): (varName));
  return "<" + vName + ">" + val + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSDSAKeyValuePQ::XmlEncode() const {
  return "<P>" + p->Get().BString() + "</P>" +
    "<Q>" + q->Get().BString() + "</Q>";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSDSAKeyValueSeedCtr::XmlEncode() const {
  return "<Seed>" + seed->Get().BString() + "</Seed>" +
    "<PgenCounter>" + counter->Get().BString() + "</PgenCounter>";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSDSAKeyValue::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("KeyValue"): (varName));
  std::string ret("<" + vName + "><DSAKeyValue>");
  if (pq != 0) {
    ret = ret + pq->XmlEncode();
  }
  if (g != 0) {
    ret = ret + g->XmlEncode("G");
  }
  ret = ret + y->XmlEncode("Y");
  if (j != 0) {
    ret = ret + j->XmlEncode("J");
  }
  if (seedCtr != 0) {
    ret = ret + seedCtr->XmlEncode();
  }
  return ret + "</DSAKeyValue></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSRSAKeyValue::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("KeyValue"): (varName));
  return "<" + vName + "><RSAKeyValue><Modulus>" +
    modulus->Get().BString() + "</Modulus><Exponent>" +
    exponent->Get().BString() + "</Exponent></RSAKeyValue></" +
    vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSTransform::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("Transform"): (varName));
  return "<" + vName + " Algorithm=\"" + algorithm->Get() + "\"></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSTransforms::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("Transforms"): (varName));
  std::string ret("<" + vName + ">");
  for (unsigned int i = 0; i < transforms.size(); i++) {
    ret = ret + transforms[i]->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSRetrievalMethod::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("RetrievalMethod"): (varName));
  std::string ret("<" + vName + " URI=\"");
  ret = ret + uri->Get() + "\"";
  if (type != 0) {
    ret = ret + " Type=\"" + type->Get() + "\"";
  }
  ret = ret + ">";
  if (transformations != 0) {
    ret = ret + transformations->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSX509IssuerSerial::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("X509IssuerSerial"): (varName));
  return "<" + vName + "><X509IssuerName>" + name + "</X509IssuerName><X509Serialnumber>"
    + IntToString(serial) + "</X509Serialnumber></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSX509SKI::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("X509SKI"): (varName));
  return "<" + vName + ">" + identifier.BString() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSX509SubjectName::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("X509SubjectName"): (varName));
  return "<" + vName + ">" + name + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSX509Certificate::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("X509Certificate"): (varName));
  return "<" + vName + ">" + certificate.BString() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSX509CRL::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("X509CRL"): (varName));
  return "<" + vName + ">" + crl.BString() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSX509Data::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("X509Data"): (varName));
  std::string ret("<" + vName + ">");
  for (unsigned int i = 0; i < basics.size(); i++) {
    ret = ret + basics[i]->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string KeyPacketKeyIDDSPGPData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("PGPData"): (varName));
  return "<" + vName + "><PGPKeyID>" + identifier.BString() +
    "</PGPKeyID><PGPKeyPacket>" + packet.BString() +
    "</PGPKeyPacket></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NKeyPacketKeyIDDSPGPData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("PGPData"): (varName));
  return "<" + vName + "><PGPKeyID>" + identifier.BString() +
    "</PGPKeyID></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string KeyPacketDSPGPData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("PGPData"): (varName));
  return "<" + vName + "><PGPKeyPacket>" + packet.BString() +
    "</PGPKeyPacket></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSSPKIData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("SPKIData"): (varName));
  std::string ret("<" + vName + ">");
  for (unsigned int i = 0; i < sexps.size(); i++) {
    ret = ret + "<SPKISexp>" + sexps[i].BString() + "</SPKISexp>";
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSMgmtData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("MgmtData"): (varName));
  return "<" + vName + ">" + val + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSKeyInfo::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("KeyInfo"): (varName));
  std::string ret("<" + vName);
  if (id != 0) {
    ret = ret + " Id=\"" + id->Get() + "\"";
  }
  ret = ret + ">";
  for (unsigned int i = 0; i < basics.size(); i++) {
    ret = ret + basics[i]->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSSignatureValue::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("SignatureValue"): (varName));
  std::string ret("<" + vName);
  if (id != 0) {
    ret = ret + " Id=\"" + id->Get() + "\"";
  }
  return ret + ">" + val.BString() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSDigestValue::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("DigestValue"): (varName));
  return "<" + vName + ">" + val.BString() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSDigestMethod::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("DigestMethod"): (varName));
  return "<" + vName + " Algorithm=\"" + algorithm->Get() + "\"/>";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSReference::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("Reference"): (varName));
  std::string ret("<" + vName);
  if (id != 0) {
    ret = ret + " Id=\"" + id->Get() + "\"";
  }
  if (uri != 0) {
    ret = ret + " URI=\"" + uri->Get() + "\"";
  }
  if (type != 0) {
    ret = ret + " Type=\"" + type->Get() + "\"";
  }
  ret = ret + ">";
  if (transformations != 0) {
    ret = ret + transformations->XmlEncode();
  }
  return ret + method->XmlEncode() + value->XmlEncode() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSHMACOutputLength::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("HMACOutputLength"): (varName));
  return "<" + vName + ">" + IntToString(val) + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSSignatureMethod::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("SignatureMethod"): (varName));
  std::string ret("<" + vName + " Algorithm=\"" + algorithm->Get() + "\"");
  if (macLength != 0) {
    ret = ret + ">" + macLength->XmlEncode();
    return ret + "</" + vName + ">";
  } else {
    return ret + "/>";
  }
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSCanonicalizationMethod::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("CanonicalizationMethod"): (varName));
  return "<" + vName + " Algorithm=\"" + algorithm->Get() + "\"/>";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSSignedInfo::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("SignedInfo"): (varName));
  std::string ret("<" + vName);
  if (id != 0) {
    ret = ret + " Id=\"" + id->Get() + "\"";
  }
  ret = ret + ">";
  ret = ret + canonMethod->XmlEncode();
  ret = ret + sigMethod->XmlEncode();
  for (unsigned int i = 0; i < references.size(); i++) {
    ret = ret + references[i]->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DSSignature::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("Signature"): (varName));
  std::string ret("<" + vName);
  if (id != 0) {
    ret = ret + " Id=\"" + id->Get() + "\"";
  }
  ret = ret + ">";
  ret = ret + info->XmlEncode();
  ret = ret + value->XmlEncode();
  if (key != 0) {
    ret = ret + key->XmlEncode();
  }
  for (unsigned int i = 0; i < objects.size(); i++) {
    ret = ret + objects[i]->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string XencKeySize::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("KeySize"): (varName));
  return "<" + vName + ">" + IntToString(val) + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string OAEPXencEncryptionMethod::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("EncryptionMethod"): (varName));
  std::string ret("<" + vName + " Algorithm=\"" + algorithm->Get() + "\">");
  if (size != 0) {
    ret = ret + size->XmlEncode();
  }
  return ret + "<OAEPParams>" + oaep.BString() + "</OAEPParams></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NOAEPXencEncryptionMethod::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("EncryptionMethod"): (varName));
  std::string ret("<" + vName + " Algorithm=\"" + algorithm->Get() + "\">");
  if (size != 0) {
    ret = ret + size->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string CValueXencCipherData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("CipherData"): (varName));
  return "<" + vName + "><CipherValue>" + val.BString() + "</CipherValue></" +
    vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string XencTransforms::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("Transforms"): (varName));
  std::string ret("<" + vName + ">");
  for (unsigned int i = 0; i < transforms.size(); i++) {
    ret = ret + transforms[i]->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string XencCipherReference::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("CipherReference"): (varName));
  std::string ret("<" + vName + " URI=\"" + uri->Get() + "\">");
  if (transformations != 0) {
    ret = ret + transformations->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string CRefXencCipherData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("CipherData"): (varName));
  return "<" + vName + ">" + reference->XmlEncode() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string XencEncryptionProperty::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("EncryptionProperty"): (varName));
  std::string ret("<" + vName);
  if (uri != 0) {
    ret = ret + " Target=\"" + uri->Get() + "\"";
  }
  if (id != 0) {
    ret = ret + " Id=\"" + id->Get() + "\"";
  }
  return ret + "></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string XencEncryptionProperties::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("EncryptionProperties"): (varName));
  std::string ret("<" + vName);
  if (id != 0) {
    ret = ret + " Id=\"" + id->Get() + "\"";
  }
  ret = ret + ">";
  for (unsigned int i = 0; i < properties.size(); i++) {
    ret = ret + properties[i]->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DataXencReferenceType::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("DataReference"): (varName));
  return "<" + vName + " URI=\"" + uri->Get() + "\"></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string KeyXencReferenceType::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("KeyReference"): (varName));
  return "<" + vName + " URI=\"" + uri->Get() + "\"></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string XencReferenceList::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ReferenceList"): (varName));
  std::string ret("<" + vName  + ">");
  unsigned int i = 0;
  for (i = 0; i < dReferences.size(); i++) {
    ret = ret + dReferences[i]->XmlEncode();
  }
  for (i = 0; i < kReferences.size(); i++) {
    ret = ret + kReferences[i]->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NameXencEncryptedKeyData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("CarriedKeyName"): (varName));
  return "<" + vName + ">" + val + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string XencEncryptedKey::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("EncryptedKey"): (varName));
  std::string ret("<" + vName);
  if (id != 0) {
    ret = ret + " Id=\"" + id->Get() + "\"";
  }
  if (type != 0) {
    ret = ret + " Type=\"" + type->Get() + "\"";
  }
  if (mime != 0) {
    ret = ret + " MimeType=\"" + mime->Get() + "\"";
  }
  if (encoding != 0) {
    ret = ret + " Encoding=\"" + encoding->Get() + "\"";
  }
  if (recipient != 0) {
    ret = ret + " Recipient=\"" + recipient->Get() + "\"";
  }
  ret = ret + ">";
  if (method != 0) {
    ret = ret + method->XmlEncode();
  }
  if (key != 0) {
    ret = ret + key->XmlEncode();
  }
  ret = ret + cipher->XmlEncode();
  if (properties != 0) {
    ret = ret + properties->XmlEncode();
  }
  if (reflist != 0) {
    ret = ret + reflist->XmlEncode();
  }
  if (carried != 0) {
    ret = ret + carried->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

} // namespace DRMPlugin
