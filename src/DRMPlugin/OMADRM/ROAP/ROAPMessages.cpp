/** \file ROAPMessages.cpp

    OMA DRM message classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "ROAPMessages.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROAPVersion::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("version"): (varName));
  return "<" + vName + ">"  + val + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROAPNonce::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("nonce"): (varName));
  return "<" + vName + ">"  + val.BString() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string SuccessROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string AbortROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NotSupportedROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string AccessDeniedROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NotFoundROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string MalformedRequestROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string UnknownCriticalExtensionROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string UnsupportedVersionROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string UnsupportedAlgorithmROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NoCertificateChainROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string InvalidCertificateChainROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string TrustedRootCertificateNotPresentROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string SignatureErrorROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DeviceTimeErrorROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NotRegisteredROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string InvalidDCFHashROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string InvalidDomainROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DomainFullROAPStatus::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("status"): (varName));
  return "<" + vName + ">"  + GetMessage() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NoOCSPResponseExtension::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extension"): (varName));
//  return "<" + vName + " xsi:type=\"NoOCSPResponse\" critical=\"" +
//    ((IsCritical() == true)? ("true"): ("false")) + "\"></" + vName + ">";
  return "<" + vName + " critical=\"" + ((IsCritical() == true)? ("true"): ("false")) +
    "\" xsi:type=\"roap:NoOCSPResponse\"/>";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string PeerKeyIdExtension::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extension"): (varName));
//  std::string ret("<" + vName + " xsi:type=\"PeerKeyIdentifier\" critical=\""
//    + ((IsCritical() == true)? ("true"): ("false")) + "\">");
  std::string ret("<" + vName + " critical=\"" + ((IsCritical() == true)? ("true"): ("false")) +
    "\" xsi:type=\"roap:PeerKeyIdentifier\"");
  if (identifier != 0) {
    ret = ret + ">" + identifier->XmlEncode("identifier") + "</" + vName + ">";
  } else {
    ret = ret + "/>";
  }
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string OCSPResponderKeyIdExtension::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extension"): (varName));
//  return "<" + vName + " xsi:type=\"OCSPResponderKeyIdentifier\" critical=\"" +
//    ((IsCritical() == true)? ("true"): ("false")) + "\">" +
//    identifier->XmlEncode("identifier") + "</" + vName + ">";
  return "<" + vName + " critical=\"" + ((IsCritical() == true)? ("true"): ("false")) +
    "\" xsi:type=\"roap:OCSPResponderKeyIdentifier\"" +
    identifier->XmlEncode("identifier") + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \returns  Encoded XML string.
*/
std::string DeviceDetailsData::XmlEncode() const {
	return "<manufacturer>" + manufacturer + "</manufacturer>" +
    "<model>" + model + "</model>" + "<version>" + version+ "</version>";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DeviceDetailsExtension::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extension"): (varName));
//  std::string ret("<" + vName + " xsi:type=\"DeviceDetails\" critical=\""
//    + ((IsCritical() == true)? ("true"): ("false")) + "\">");
  std::string ret("<" + vName + " critical=\"" + ((IsCritical() == true)? ("true"): ("false")) +
    "\" xsi:type=\"roap:DeviceDetails\"");
  if (details != 0) {
    ret = ret + ">" + details->XmlEncode() + "</" + vName + ">";
  } else {
    ret = ret + "/>";
  }
  return ret;
}

/*! \brief  Encode as XML string.

    \returns  Encoded XML string.
*/
std::string TransIdentifierData::XmlEncode() const {
	return std::string("") + "<contentID>" + contentID->Get() + "</contentID>" + "<id>" + id + "</id>";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string TransactionIdExtension::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extension"): (varName));

  std::string ret("<" + vName + " critical=\"" + ((IsCritical() == true)? ("true"): ("false")) +
    "\" xsi:type=\"roap:TransactionIdentifier\">");
  for (unsigned int i = 0; i < transactions.size(); i++) {
    ret = ret + transactions[i]->XmlEncode();
  }
  if (transactions.size() != 0) {
    ret = ret + "</" + vName + ">";
  } else {
    ret = ret + "/>";
  }
  return ret;


//  std::string ret("<" + vName + " xsi:type=\"TransactionIdentifier\" critical=\""
//    + ((IsCritical() == true)? ("true"): ("false")) + "\">");
//  for (unsigned int i = 0; i < transactions.size(); i++) {
//    ret = ret + transactions[i]->XmlEncode();
//  }
//  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string CertCachingExtension::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extension"): (varName));
//  return "<" + vName + " xsi:type=\"CertificateCaching\" critical=\""
//    + ((IsCritical() == true)? ("true"): ("false")) + "\"></" + vName + ">";
  return "<" + vName + " critical=\"" + ((IsCritical() == true)? ("true"): ("false")) +
    "\" xsi:type=\"roap:CertificateCaching\"/>";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string HashChainSupportExtension::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extension"): (varName));
  return "<" + vName + " xsi:type=\"roap:HashChainSupport\" critical=\""
    + ((IsCritical() == true)? ("true"): ("false")) + "\"></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NotDomainMemberExtension::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extension"): (varName));
  return "<" + vName + " xsi:type=\"roap:NotDomainMember\" critical=\""
    + ((IsCritical() == true)? ("true"): ("false")) + "\"></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DomainNameWhiteListExtension::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extension"): (varName));
//  std::string ret("<" + vName + " xsi:type=\"DomainNameWhiteList\" critical=\""
//    + ((IsCritical() == true)? ("true"): ("false")) + "\">");
//  for (unsigned int i = 0; i < names.size(); i++) {
//    ret = ret + "<dn>"  + names[i] + "</dn>";
//  }
//  return ret + "</" + vName + ">";


  std::string ret("<" + vName + " critical=\"" + ((IsCritical() == true)? ("true"): ("false")) +
    "\" xsi:type=\"roap:DomainNameWhiteList\">");
  for (unsigned int i = 0; i < names.size(); i++) {
    ret = ret + "<dn>"  + names[i] + "</dn>";
  }
  if (names.size() != 0) {
    ret = ret + "</" + vName + ">";
  } else {
    ret = ret + "/>";
  }
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROAPIdentifier::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("identifier"): (varName));
  return "<" + vName + ">" + keyID->XmlEncode("keyIdentifier") + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
//! \todo: Do we need to put algorithm or not (examples suggest not)?
std::string X509SPKIHash::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("KeyIdentifier"): (varName));
  return "<" + vName + " algorithm=\"" + GetAlgorithm()->Get() +
    "\" xsi:type=\"roap:X509SPKIHash\"><hash>" + hash.BString() + "</hash>" +
    "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROAPDomainIdentifier::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("DomainIdentifier"): (varName));
  return "<" + vName + ">" + id + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DefDateTime::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("dateTime"): (varName));
  return "<" + vName + ">" + time.Get() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string UndefDateTime::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("dateTime"): (varName));
  return "<" + vName + ">Undefined</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string InfDateTime::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("dateTime"): (varName));
  return "<" + vName + ">Infinite</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \returns  Encoded XML string.
*/
std::string ROAPROPayloadStatefulInfo::XmlEncode() const {
  if (stateful) {
    return "true";
  } else {
    return "false";
  }
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DomainROAPROPayload::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ROPayload"): (varName));
  std::string ret("<" + vName);
  ret = ret + " domainRO=\"true\"";
  ret = ret + " id=\"" + id->Get() + "\"";
  if (riURLInfo != 0) {
    ret = ret + " riURL=\"" + riURLInfo->GetURL()->Get() + "\"";
  }
  if (statefulInfo != 0) {
    ret = ret + " stateful=\"" + statefulInfo->XmlEncode() + "\"";
  }
  ret = ret + " version=\"" + version->Get() + "\">";
  ret = ret + riID->XmlEncode("riID");
  ret = ret + rights->XmlEncode("rights");
  ret = ret + signature->XmlEncode("signature");
  if (time != 0) {
    ret = ret + time->XmlEncode("timeStamp");
  }
  ret = ret + key->XmlEncode("encKey");
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DeviceROAPROPayload::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ROPayload"): (varName));
  std::string ret("<" + vName);
//  ret = ret + " domainRO=\"false\"";
  ret = ret + " id=\"" + id->Get() + "\"";
  if (riURLInfo != 0) {
    ret = ret + " riURL=\"" + riURLInfo->GetURL()->Get() + "\"";
  }
  if (statefulInfo != 0) {
    ret = ret + " stateful=\"" + statefulInfo->XmlEncode() + "\"";
  }
  ret = ret + " version=\"" + version->Get() + "\">";
  ret = ret + riID->XmlEncode("riID");
  ret = ret + rights->XmlEncode("rights");
  if (signature != 0) {
    ret = ret + signature->XmlEncode("signature");
  }
  if (time != 0) {
    ret = ret + time->XmlEncode("timeStamp");
  }
  ret = ret + key->XmlEncode("encKey");
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROAPProtectedRO::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ProtectedRO"): (varName));
  return "<" + vName + ">" + payload->XmlEncode("ro") + signature->XmlEncode("mac") +
    "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROAPServerInfo::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ServerInfo"): (varName));
  return "<" + vName + ">" + val.BString() + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROAPKeyIdentifiers::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("KeyIdentifiers"): (varName));
  if (identifiers.size() == 0) {
    return "<" + vName + "/>";
  }
  std::string ret("<" + vName + ">");
  for (unsigned int i = 0; i < identifiers.size(); i++) {
    ret = ret + identifiers[i]->XmlEncode("keyIdentifier");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROAPCertificateChain::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("CertificateChain"): (varName));
  std::string ret("<" + vName + ">");
  for (unsigned int i = 0; i < certs.size(); i++) {
    ret = ret + "<certificate>" + certs[i].BString() + "</certificate>";
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DeviceHelloExtensions::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extensions"): (varName));
  std::string ret("<" + vName + ">");
  ret = ret + GetCertCaching()->XmlEncode("extension");
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DeviceHelloRequest::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("DeviceHello"): (varName));
  std::string ret("<" + vName);
  unsigned int i = 0;
  if (GetTriggerNonce() != 0) {
    ret = ret + " triggerNonce=\"" + GetTriggerNonce()->Get().BString() + "\"";
  }
  ret = ret + ">";
  ret = ret + GetVersion()->XmlEncode("version");
  for (i = 0; i < GetDeviceIDs().size(); i++) {
    ret = ret + GetDeviceIDs()[i]->XmlEncode("deviceID");
  }
  for (i = 0; i < GetSupportedAlgs().size(); i++) {
    ret = ret + GetSupportedAlgs()[i]->XmlEncode("supportedAlgorithm");
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string RIHelloExtensions::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extensions"): (varName));
  std::string ret("<" + vName + ">");
  if (GetPeerKeyID() != 0) {
    ret = ret + GetPeerKeyID()->XmlEncode("extension");
  }
  if (GetCertCaching() != 0) {
    ret = ret + GetCertCaching()->XmlEncode("extension");
  }
  if (GetDeviceDetails() != 0) {
    ret = ret + GetDeviceDetails()->XmlEncode("extension");
  }
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string SuccessRIHello::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("RIHello"): (varName));
//  std::string ret("<" + vName + " status=\"Success\" sessionId=\"" +
//    GetSessionID()->Get().BString() + "\">");
  std::string ret("<" + vName + " sessionId=\"" + GetSessionID()->Get() +
    "\" status=\"Success\">");
  ret = ret + GetVersion()->XmlEncode("selectedVersion");
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  for (unsigned int i = 0; i < GetSelectedAlgs().size(); i++) {
    ret = ret + GetSelectedAlgs()[i]->XmlEncode("selectedAlgorithm");
  }
  ret = ret + GetNonce()->XmlEncode("riNonce");
  if (GetTrustedAuthorities() != 0) {
    ret = ret + GetTrustedAuthorities()->XmlEncode("trustedAuthorities");
  }
  if (GetServerInfo() != 0) {
    ret = ret + GetServerInfo()->XmlEncode("serverInfo");
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string UnsuccessRIHello::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("RIHello"): (varName));
  return "<" + vName + " status=\"" + GetUnsuccessStatus()->GetMessage() + "\"></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string RegRequestExtensions::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extensions"): (varName));
  std::string ret("<" + vName + ">");
  if (GetPeerKeyId() != 0) {
    ret = ret + GetPeerKeyId()->XmlEncode("extension");
  }
  if (GetDeviceDetails() != 0) {
    ret = ret + GetDeviceDetails()->XmlEncode("extension");
  }
  if (GetNoOCSPResponse() != 0) {
    ret = ret + GetNoOCSPResponse()->XmlEncode("extension");
  }
  if (GetOCSPResponderKeyId() != 0) {
    ret = ret + GetOCSPResponderKeyId()->XmlEncode("extension");
  }
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string RegRequest::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("RegistrationRequest"): (varName));
  std::string ret("<" + vName);
  ret = ret + " sessionId=\"" + GetSessionID()->Get() + "\"";
  if (GetTriggerNonce() != 0) {
    ret = ret + " triggerNonce=\"" + GetTriggerNonce()->Get().BString() + "\"";
  }
//  ret = ret + " sessionId=\"" + GetSessionID()->Get() + "\">";
  ret = ret + ">" + GetDeviceNonce()->XmlEncode("nonce");
  ret = ret + GetTime()->XmlEncode("time");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  if (GetTrustedAuthorities() != 0) {
    ret = ret + GetTrustedAuthorities()->XmlEncode("trustedAuthorities");
  }
  if (GetServerInfo() != 0) {
    ret = ret + GetServerInfo()->XmlEncode("serverInfo");
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  ret = ret + "<signature>" + GetSignature().BString() + "</signature>";
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string (without signature).

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string (without signature).
*/
std::string RegRequest::XmlEncodeWithoutSignature(const std::string& varName) const {
  std::string vName = ((varName == "")? ("RegistrationRequest"): (varName));
  std::string ret("<" + vName);
  ret = ret + " sessionId=\"" + GetSessionID()->Get() + "\"";
  if (GetTriggerNonce() != 0) {
    ret = ret + " triggerNonce=\"" + GetTriggerNonce()->Get().BString() + "\"";
  }
//  ret = ret + " sessionId=\"" + GetSessionID()->Get() + "\">";
  ret = ret + ">" + GetDeviceNonce()->XmlEncode("nonce");
  ret = ret + GetTime()->XmlEncode("time");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  if (GetTrustedAuthorities() != 0) {
    ret = ret + GetTrustedAuthorities()->XmlEncode("trustedAuthorities");
  }
  if (GetServerInfo() != 0) {
    ret = ret + GetServerInfo()->XmlEncode("serverInfo");
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string RegResponseExtensions::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extensions"): (varName));
  std::string ret("<" + vName + ">");
  if (GetDomainNameWhiteList() != 0) {
    ret = ret + GetDomainNameWhiteList()->XmlEncode("extension");
  }
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string SuccessRegResponse::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("RegistrationResponse"): (varName));
  std::string ret("<" + vName + " sessionId=\"" + GetSessionID()->Get() + "\" status=\"Success\">");
  ret = ret + GetRightsIssuerURL()->XmlEncode("riURL");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  for (unsigned int i = 0; i < GetOCSPResponses().size(); i++) {
    ret = ret + "<ocspResponse>" + GetOCSPResponses()[i].BString() + "</ocspResponse>";
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  ret = ret + "<signature>" + GetSignature().BString() + "</signature>";
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string (without signature).

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string (without signature).
*/
std::string SuccessRegResponse::XmlEncodeWithoutSignature(const std::string& varName) const {
  std::string vName = ((varName == "")? ("RegistrationResponse"): (varName));
  std::string ret("<" + vName + " sessionId=\"" + GetSessionID()->Get() + "\" status=\"Success\">");
  ret = ret + GetRightsIssuerURL()->XmlEncode("riURL");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  for (unsigned int i = 0; i < GetOCSPResponses().size(); i++) {
    ret = ret + "<ocspResponse>" + GetOCSPResponses()[i].BString() + "</ocspResponse>";
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string UnsuccessRegResponse::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("RegistrationResponse"): (varName));
  std::string ret("<" + vName + " status=\"" + GetUnsuccessStatus()->GetMessage() + "\"");
  if (GetSessionID() != 0) {
    ret = ret + " sessionId=\"" + GetSessionID()->Get() + "\"";
  }
  return ret + "></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DCFHash::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("DCFHash"): (varName));
  return "<" + vName + " algorithm=" + GetAlgorithm()->Get() + "><hash>" +
    val.BString() + "</hash></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \returns  Encoded XML string.
*/
std::string ROInfoData::XmlEncode() const {
  std::string ret("<roID>" + roID->Get() + "</roID>");
  if (dcfHash != 0) {
    ret = ret + dcfHash->XmlEncode("dcfHash");
  }
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROInfo::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("roInfo"): (varName));
  std::string ret = "<" + vName + ">";
  for (unsigned int i = 0; i < infoDatas.size(); i++) {
    ret += infoDatas[i]->XmlEncode();
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string (without signature).

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string (without signature).
*/
std::string RORequest::XmlEncodeWithoutSignature(const std::string& varName) const {
  std::string vName = ((varName == "")? ("RORequest"): (varName));
  std::string ret("<" + vName);
  unsigned int i = 0;
  if (GetTriggerNonce() != 0) {
    ret = ret + " triggerNonce=\"" + GetTriggerNonce()->Get().BString() + "\"";
  }
  ret = ret + ">";
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  if (GetDomainID() != 0) {
    ret = ret + GetDomainID()->XmlEncode("domainID");
  }
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  ret = ret + GetDeviceNonce()->XmlEncode("nonce");
  ret = ret + GetTime()->XmlEncode("time");
  ret = ret + GetInfo()->XmlEncode("roInfo");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string (without signature).

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string (without signature).
*/
std::string SuccessTwoPassROResponse::XmlEncodeWithoutSignature(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ROResponse"): (varName));
  std::string ret("<" + vName + " status=\"Success\">");
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  ret = ret + GetNonce()->XmlEncode("nonce");
  unsigned int i = 0;
  for (i = 0; i < GetProtectedROs().size(); i++) {
    ret = ret + GetProtectedROs()[i]->XmlEncode("protectedRO");
  }
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  for (i = 0; i < GetOCSPResponses().size(); i++) {
    ret = ret + "<ocspResponse>" + GetOCSPResponses()[i].BString() + "</ocspResponse>";
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string (without signature).

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string (without signature).
*/
std::string OnePassROResponse::XmlEncodeWithoutSignature(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ROResponse"): (varName));
  std::string ret("<" + vName + " status=\"" + GetStatus()->GetMessage() + "\">");
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  unsigned int i = 0;
  for (i = 0; i < GetProtectedROs().size(); i++) {
    ret = ret + GetProtectedROs()[i]->XmlEncode("protectedRO");
  }
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  for (i = 0; i < GetOCSPResponses().size(); i++) {
    ret = ret + "<ocspResponse>" + GetOCSPResponses()[i].BString() + "</ocspResponse>";
  }
  ret = ret + GetExtensions()->XmlEncode("extensions");
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string JoinDomainReqExtensions::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extensions"): (varName));
  std::string ret("<" + vName + ">");
  if (GetPeerKeyId() != 0) {
    ret = ret + GetPeerKeyId()->XmlEncode("extension");
  }
  if (GetNoOCSPResponse() != 0) {
    ret = ret + GetNoOCSPResponse()->XmlEncode("extension");
  }
  if (GetOCSPResponderKeyId() != 0) {
    ret = ret + GetOCSPResponderKeyId()->XmlEncode("extension");
  }
  if (GetHashChainSupport() != 0) {
    ret = ret + GetHashChainSupport()->XmlEncode("extension");
  }
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string JoinDomainRequest::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("JoinDomainRequest"): (varName));
  std::string ret("<" + vName);
  if (GetTriggerNonce() != 0) {
    ret = ret + " triggerNonce=\"" + GetTriggerNonce()->Get().BString() + "\"";
  }
  ret = ret + ">";
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  if (GetDomainID() != 0) {
    ret = ret + GetDomainID()->XmlEncode("domainID");
  }
  ret = ret + GetDeviceNonce()->XmlEncode("nonce");
  ret = ret + GetTime()->XmlEncode("time");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  ret = ret + "<signature>" + GetSignature().BString() + "</signature>";
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string (without signature).

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string (without signature).
*/
std::string JoinDomainRequest::XmlEncodeWithoutSignature(const std::string&
    varName) const {
  std::string vName = ((varName == "")? ("JoinDomainRequest"): (varName));
  std::string ret("<" + vName);
  if (GetTriggerNonce() != 0) {
    ret = ret + " triggerNonce=\"" + GetTriggerNonce()->Get().BString() + "\"";
  }
  ret = ret + ">";
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  if (GetDomainID() != 0) {
    ret = ret + GetDomainID()->XmlEncode("domainID");
  }
  ret = ret + GetDeviceNonce()->XmlEncode("nonce");
  ret = ret + GetTime()->XmlEncode("time");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DomainResponseExtensions::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extensions"): (varName));
  std::string ret("<" + vName + ">");
  if (GetHashChainSupport() != 0) {
    ret = ret + GetHashChainSupport()->XmlEncode("extension");
  }
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROAPProtectedDomainKey::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ProtectedDomainKey"): (varName));
  return "<" + vName + ">" + key->XmlEncode("encKey") + riID->XmlEncode("riID") +
    "<mac>" + mac.BString() + "</mac>" + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROAPDomainInfo::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("DomainInfo"): (varName));
  std::string ret("<" + vName + ">");
  ret = ret + time->XmlEncode("time");
  for (unsigned int i = 0; i < keys.size(); i++) {
    ret = ret + keys[i]->XmlEncode("domainKey");
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string SuccessJoinDomainResponse::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("JoinDomainResponse"): (varName));
  std::string ret("<" + vName + " status=\"Success\">");
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  ret = ret + GetNonce()->XmlEncode("nonce");
  ret = ret + GetDomainInfo()->XmlEncode("domainInfo");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  for (unsigned int i = 0; i < GetOCSPResponses().size(); i++) {
    ret = ret + "<ocspResponse>" + GetOCSPResponses()[i].BString() + "</ocspResponse>";
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  ret = ret + "<signature>" + GetSignature().BString() + "</signature>";
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string (without signature).

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string (without signature).
*/
std::string SuccessJoinDomainResponse::XmlEncodeWithoutSignature(const
    std::string& varName) const {
  std::string vName = ((varName == "")? ("JoinDomainResponse"): (varName));
  std::string ret("<" + vName + " status=\"Success\">");
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  ret = ret + GetNonce()->XmlEncode("nonce");
  ret = ret + GetDomainInfo()->XmlEncode("domainInfo");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  for (unsigned int i = 0; i < GetOCSPResponses().size(); i++) {
    ret = ret + "<ocspResponse>" + GetOCSPResponses()[i].BString() + "</ocspResponse>";
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string UnsuccessJoinDomainResponse::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("JoinDomainResponse"): (varName));
  return "<" + vName + " status=\"" + GetUnsuccessStatus()->GetMessage() + "\"></" +
    vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string LeaveDomainReqExtensions::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extensions"): (varName));
  std::string ret("<" + vName + ">");
  if (GetNotDomainMember() != 0) {
    ret = ret + GetNotDomainMember()->XmlEncode("extension");
  }
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string LeaveDomainRequest::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("JoinDomainRequest"): (varName));
  std::string ret("<" + vName);
  if (GetTriggerNonce() != 0) {
    ret = ret + " triggerNonce=\"" + GetTriggerNonce()->Get().BString() + "\"";
  }
  ret = ret + ">";
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  if (GetDomainID() != 0) {
    ret = ret + GetDomainID()->XmlEncode("domainID");
  }
  ret = ret + GetDeviceNonce()->XmlEncode("nonce");
  ret = ret + GetTime()->XmlEncode("time");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  ret = ret + "<signature>" + GetSignature().BString() + "</signature>";
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string (without signature).

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string (without signature).
*/
std::string LeaveDomainRequest::XmlEncodeWithoutSignature(const std::string& varName) const {
  std::string vName = ((varName == "")? ("LeaveDomainRequest"): (varName));
  std::string ret("<" + vName);
  if (GetTriggerNonce() != 0) {
    ret = ret + " triggerNonce=\"" + GetTriggerNonce()->Get().BString() + "\"";
  }
  ret = ret + ">";
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  if (GetDomainID() != 0) {
    ret = ret + GetDomainID()->XmlEncode("domainID");
  }
  ret = ret + GetDeviceNonce()->XmlEncode("nonce");
  ret = ret + GetTime()->XmlEncode("time");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string LeaveDomainResponseExtensions::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extensions"): (varName));
  std::string ret("<" + vName + ">");
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string SuccessLeaveDomainResponse::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("LeaveDomainResponse"): (varName));
  std::string ret("<" + vName + " status=\"Success\">");
  ret = ret + GetNonce()->XmlEncode("nonce");
  ret = ret + GetDomainID()->XmlEncode("domainID");
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string UnsuccessLeaveDomainResponse::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("LeaveDomainResponse"): (varName));
  return "<" + vName + " status=\"" + GetUnsuccessStatus()->GetMessage() + "\"></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string RORequestExtensions::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extensions"): (varName));
  std::string ret("<" + vName + ">");
  if (GetPeerKeyID() != 0) {
    ret = ret + GetPeerKeyID()->XmlEncode("extension");
  }
  if (GetNoOCSPResponse() != 0) {
    ret = ret + GetNoOCSPResponse()->XmlEncode("extension");
  }
  if (GetOCSPResponderKeyID() != 0) {
    ret = ret + GetOCSPResponderKeyID()->XmlEncode("extension");
  }
  if (GetTransactionID() != 0) {
    ret = ret + GetTransactionID()->XmlEncode("extension");
  }
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string RORequest::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("RORequest"): (varName));
  std::string ret("<" + vName);
  unsigned int i = 0;
  if (GetTriggerNonce() != 0) {
    ret = ret + " triggerNonce=\"" + GetTriggerNonce()->Get().BString() + "\"";
  }
  ret = ret + ">";
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  if (GetDomainID() != 0) {
    ret = ret + GetDomainID()->XmlEncode("domainID");
  }
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  ret = ret + GetDeviceNonce()->XmlEncode("nonce");
  ret = ret + GetTime()->XmlEncode("time");
  ret = ret + GetInfo()->XmlEncode("roInfo");
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  ret = ret + "<signature>" + GetSignature().BString() + "</signature>";
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROResponseExtensions::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("extensions"): (varName));
  std::string ret("<" + vName + ">");
  if (GetTransactionID() != 0) {
    ret = ret + GetTransactionID()->XmlEncode("extension");
  }
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string SuccessTwoPassROResponse::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ROResponse"): (varName));
  std::string ret("<" + vName + " status=\"Success\">");
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  ret = ret + GetNonce()->XmlEncode("nonce");
  unsigned int i = 0;
  for (i = 0; i < GetProtectedROs().size(); i++) {
    ret = ret + GetProtectedROs()[i]->XmlEncode("protectedRO");
  }
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  for (i = 0; i < GetOCSPResponses().size(); i++) {
    ret = ret + "<ocspResponse>" + GetOCSPResponses()[i].BString() + "</ocspResponse>";
  }
  if (GetExtensions() != 0) {
    ret = ret + GetExtensions()->XmlEncode("extensions");
  }
  ret = ret + "<signature>" + GetSignature().BString() + "</signature>";
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string UnsuccessTwoPassROResponse::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ROResponse"): (varName));
  return "<" + vName + " status=\"" + GetUnsuccessStatus()->GetMessage() + "\"></" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string OnePassROResponse::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ROResponse"): (varName));
  std::string ret("<" + vName + " status=\"" + GetStatus()->GetMessage() + "\">");
  ret = ret + GetDeviceID()->XmlEncode("deviceID");
  ret = ret + GetRightsIssuerID()->XmlEncode("riID");
  unsigned int i = 0;
  for (i = 0; i < GetProtectedROs().size(); i++) {
    ret = ret + GetProtectedROs()[i]->XmlEncode("protectedRO");
  }
  if (GetCertChain() != 0) {
    ret = ret + GetCertChain()->XmlEncode("certificateChain");
  }
  for (i = 0; i < GetOCSPResponses().size(); i++) {
    ret = ret + "<ocspResponse>" + GetOCSPResponses()[i].BString() + "</ocspResponse>";
  }
  ret = ret + GetExtensions()->XmlEncode("extensions");
  ret = ret + "<signature>" + GetSignature().BString() + "</signature>";
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \returns  Encoded XML string.
*/
std::string ROAPTriggerProxy::XmlEncode() const {
  if (proxy) {
    return "true";
  } else {
    return "false";
  }
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string RegRequestTriggerData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("registrationRequest"): (varName));
  std::string ret("<" + vName + " id=\"" + id->Get() + "\">");
  ret = ret + riID->XmlEncode("riID");
  if (nonce != 0) {
    ret = ret + nonce->XmlEncode("nonce");
  }
  ret = ret + url->XmlEncode("roapURL") + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string RegRequestTrigger::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("roapTrigger"): (varName));
//  std::string ret("<" + vName + " version=\"" + version->Get() + "\"");
  std::string ret("<" + vName);
  if (triggerProxy != 0) {
    ret = ret + " proxy=\"" + triggerProxy->XmlEncode() + "\"";
  }
  ret = ret + " version=\"" + version->Get() + "\"";
  ret = ret + ">" + data->XmlEncode("registrationRequest");
  if (signature != 0) {
    ret = ret + signature->XmlEncode("signature");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ROIDContentID::XmlEncode() const {
  std::string ret("<roID>" + roID->Get() + "</roID>");
  for (unsigned int i = 0; i < contentIDs.size(); i++) {
    ret = ret + contentIDs[i]->XmlEncode("contentID");
  }
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DomainROTriggerData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("roAcquisition"): (varName));
  std::string ret("<" + vName + " id=\"" + id->Get() + "\">");
  ret = ret + riID->XmlEncode("riID");
  if (nonce != 0) {
    ret = ret + nonce->XmlEncode("nonce");
  }
  ret = ret + url->XmlEncode("roapURL");
  ret = ret + domainID->XmlEncode("domainID");
  for (unsigned int i = 0; i < roIDContentIDs.size(); i++) {
    ret = ret + roIDContentIDs[i]->XmlEncode();
  }
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NDomainROTriggerData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("roAcquisition"): (varName));
  std::string ret("<" + vName + " id=\"" + id->Get() + "\">");
  ret = ret + riID->XmlEncode("riID");
  if (nonce != 0) {
    ret = ret + nonce->XmlEncode("nonce");
  }
  ret = ret + url->XmlEncode("roapURL");
  for (unsigned int i = 0; i < roIDContentIDs.size(); i++) {
    ret = ret + roIDContentIDs[i]->XmlEncode();
  }
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DomainROTrigger::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("roapTrigger"): (varName));
//  std::string ret("<" + vName + " version=\"" + version->Get() + "\"");
  std::string ret("<" + vName);
  if (triggerProxy != 0) {
    ret = ret + " proxy=\"" + triggerProxy->XmlEncode() + "\"";
  }
  ret = ret + " version=\"" + version->Get() + "\"";
  ret = ret + ">" + data->XmlEncode("roAcquisition");
  if (signature != 0) {
    ret = ret + signature->XmlEncode("signature");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NDomainROTrigger::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("roapTrigger"): (varName));
//  std::string ret("<" + vName + " version=\"" + version->Get() + "\"");
  std::string ret("<" + vName);
  if (triggerProxy != 0) {
    ret = ret + " proxy=\"" + triggerProxy->XmlEncode() + "\"";
  }
  ret = ret + " version=\"" + version->Get() + "\"";
  ret = ret + ">" + data->XmlEncode("roAcquisition");
  if (signature != 0) {
    ret = ret + signature->XmlEncode("signature");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string JoinDomainTriggerData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("joinDomain"): (varName));
  std::string ret("<" + vName + " id=\"" + id->Get() + "\">");
  ret = ret + riID->XmlEncode("riID");
  if (nonce != 0) {
    ret = ret + nonce->XmlEncode("nonce");
  }
  ret = ret + url->XmlEncode("roapURL");
  ret = ret + domainID->XmlEncode("domainID");
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string LeaveDomainTriggerData::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("leaveDomain"): (varName));
  std::string ret("<" + vName + " id=\"" + id->Get() + "\">");
  ret = ret + riID->XmlEncode("riID");
  ret = ret + nonce->XmlEncode("nonce");
  ret = ret + url->XmlEncode("roapURL");
  ret = ret + domainID->XmlEncode("domainID");
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string JoinDomainTrigger::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("roapTrigger"): (varName));
//  std::string ret("<" + vName + " version=\"" + version->Get() + "\"");
  std::string ret("<" + vName);
  if (triggerProxy != 0) {
    ret = ret + " proxy=\"" + triggerProxy->XmlEncode() + "\"";
  }
  ret = ret + " version=\"" + version->Get() + "\"";
  ret = ret + ">" + data->XmlEncode("joinDomain");
  if (signature != 0) {
    ret = ret + signature->XmlEncode("signature");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string LeaveDomainTrigger::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("roapTrigger"): (varName));
  std::string ret("<" + vName);
  if (triggerProxy != 0) {
    ret = ret + " proxy=\"" + triggerProxy->XmlEncode() + "\"";
  }
  ret = ret + " version=\"" + version->Get() + "\"";
  ret = ret + ">" + data->XmlEncode("leaveDomain");
  ret = ret + signature->XmlEncode("signature");
  if (key != 0) {
    ret = ret + key->XmlEncode("encKey");
  }
  return ret + "</" + vName + ">";
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string InitialRORequest::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("initialRORequest"): (varName));
  std::string ret("<" + vName + ">");
  ret = ret + deviceID->XmlEncode("deviceID");
  for (unsigned int i = 0; i < contentIDs.size(); i++) {
    ret = ret + contentIDs[i]->XmlEncode("contentID");
  }
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string AddContentKeyRequest::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("addContentKeyRequest"): (varName));
  std::string ret("<" + vName + ">");
  ret = ret + contentID->XmlEncode("contentID");
  ret = ret + "<encryptionKey>" + key.BString() + "</encryptionKey>";
  ret = ret + nonce->XmlEncode("nonce");
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string AddContentKeyResponse::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("addContentKeyResponse"): (varName));
  std::string ret("<" + vName + ">");
  if (success == true) {
    ret = ret + "<success>true</success>";
  } else {
    ret = ret + "<success>false</success>";
  }
  ret = ret + nonce->XmlEncode("nonce");
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string AddDeviceRightsRequest::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("addDeviceRightsRequest"): (varName));
  std::string ret("<" + vName + ">");
  ret = ret + rights->XmlEncode("rights");
  ret = ret + deviceID->XmlEncode("deviceID");
  ret = ret + contentID->XmlEncode("contentID");
  ret = ret + nonce->XmlEncode("nonce");
  ret = ret + "</" + vName + ">";
  return ret;
}

/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string AddDeviceRightsResponse::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("addDeviceRightsResponse"): (varName));
  std::string ret("<" + vName + ">");
  if (success == true) {
    ret = ret + "<success>true</success>";
  } else {
    ret = ret + "<success>false</success>";
  }
  ret = ret + nonce->XmlEncode("nonce");
  ret = ret + "</" + vName + ">";
  return ret;
}

} // namespace DRMPlugin
