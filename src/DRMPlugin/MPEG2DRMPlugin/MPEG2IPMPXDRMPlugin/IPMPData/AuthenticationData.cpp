/**	\file AuthenticationData.cpp

	IPMP authentication data classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "AuthenticationData.h"
#include "BasicTypes.h"
#include <vector>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief  Init authentication IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool InitAuthenticationIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPData::MPEG2Encode(0x0c, ByteSeq(ipmpDescriptorID) +
    ByteSeq(authType), encoded);
}

/*! \brief  Get IPMP descriptor ID.

    \returns IPMP descriptor ID.
*/
const Bit32T& InitAuthenticationIPMPData::GetIPMPDescriptorID() const {
  return ipmpDescriptorID;
}

/*! \brief  Get authentication type.

    \returns Authentication type.
*/
const ByteT& InitAuthenticationIPMPData::GetAuthType() const {
  return authType;
}

/*! \brief  Authentication codes contained in MutualAuthenticationIPMPData.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool AuthCodes::MPEG2Encode(ByteSeq& encoded) const {
  if (context->MPEG2Encode(encoded) == false) {
    return false;
  }
  encoded += codes.MPEG2Encode();
  return true;
}

/*! \brief  Check data using codes contained.

    \param  crypto      input, crypto provider.
    \param  in          input, data to be checked.

    \returns  Boolean indicating check success or failure.
*/
bool AuthCodes::Check(CryptoProvider* crypto, const ByteSeq& in) {
  //  \todo Perhaps not all checks are signature checks.
  HashCalculator* hash;
  if (context->CreateHashCalculator(crypto, &hash) == false) {
    return false;
  }
  ByteSeq out;
  if (hash->HashData(in, out) == false) {
    delete hash;
    return false;
  }
  delete hash;
  PublicVerifier* verifier;
  if (context->CreatePublicVerifier(crypto, &verifier) == false) {
    return false;
  }
  bool ret = verifier->VerifySignature(codes, out);
  delete verifier;
  return ret;
}

/*! \brief  Get public authentication context.

    \returns Public authentication context.
*/
PublicAuthContext* AuthCodes::GetAuthContext() {
  return context;
}

/*! \brief  Get codes.

    \returns Codes.
*/
const ByteSeq& AuthCodes::GetCodes() const {
  return codes;
}

/*!	\brief  Mutual authentication IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool MutualAuthenticationIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  ByteT tmp8 = 0;
  tmp8 |= (candidateAlgorithms.size() == 0)? (0x00): (0x80);
  tmp8 |= (agreedAlgorithms.size() == 0)? (0x00): (0x40);
  tmp8 |= (failedNegotiation == false)? (0x00): (0x20);
  tmp8 |= (authData == 0)? (0x00): (0x10);
  tmp8 |= (authCodes == 0)? (0x00): (0x08);
  enc = ByteSeq(tmp8);
  if (candidateAlgorithms.size() != 0) {
    if (candidateAlgorithms.size() >= (1 << 8)) {
      return false;
    }
    enc += (ByteT)(candidateAlgorithms.size());
    std::vector<AlgorithmDescriptor*>::const_iterator iter = candidateAlgorithms.begin();
    while (iter != candidateAlgorithms.end()) {
      ByteSeq tmp;
      if ((*iter)->MPEG2Encode(tmp) == false) {
        return false;
      }
      enc += tmp;
      iter++;
    }
  }
  if (agreedAlgorithms.size() != 0) {
    if (agreedAlgorithms.size() >= (1 << 8)) {
      return false;
    }
    enc += (ByteT)(agreedAlgorithms.size());
    std::vector<AlgorithmDescriptor*>::const_iterator iter = agreedAlgorithms.begin();
    while (iter != agreedAlgorithms.end()) {
      ByteSeq tmp;
      if ((*iter)->MPEG2Encode(tmp) == false) {
        return false;
      }
      enc += tmp;
      iter++;
    }
  }
  if (authData != 0) {
    enc += authData->MPEG2Encode();
  }
  if (authCodes != 0) {
    ByteSeq tmp;
    if (authCodes->MPEG2Encode(tmp) == false) {
      return false;
    }
    enc += tmp;
  }
  return IPMPData::MPEG2Encode(0x0d, enc, encoded);
}

/*! \brief  Encode as byte array without authentication codes.

    Encode for purpose of authenticating the message.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool MutualAuthenticationIPMPData::AuthMPEG2Encode(ByteSeq& encoded) const {
  ByteT tmp8 = 0;
  tmp8 |= (candidateAlgorithms.size() == 0)? (0x00): (0x80);
  tmp8 |= (agreedAlgorithms.size() == 0)? (0x00): (0x40);
  tmp8 |= (failedNegotiation == false)? (0x00): (0x20);
  tmp8 |= (authData == 0)? (0x00): (0x10);
//  tmp8 |= (authCodes == 0)? (0x00): (0x08);
  tmp8 |= 0x08;
  encoded = ByteSeq(tmp8);
  if (candidateAlgorithms.size() != 0) {
    if (candidateAlgorithms.size() >= (1 << 8)) {
      return false;
    }
    encoded += (ByteT)(candidateAlgorithms.size());
    std::vector<AlgorithmDescriptor*>::const_iterator iter = candidateAlgorithms.begin();
    while (iter != candidateAlgorithms.end()) {
      ByteSeq tmp;
      if ((*iter)->MPEG2Encode(tmp) == false) {
        return false;
      }
      encoded += tmp;
      iter++;
    }
  }
  if (agreedAlgorithms.size() != 0) {
    if (agreedAlgorithms.size() >= (1 << 8)) {
      return false;
    }
    encoded += (ByteT)(agreedAlgorithms.size());
    std::vector<AlgorithmDescriptor*>::const_iterator iter = agreedAlgorithms.begin();
    while (iter != agreedAlgorithms.end()) {
      ByteSeq tmp;
      if ((*iter)->MPEG2Encode(tmp) == false) {
        return false;
      }
      encoded += tmp;
      iter++;
    }
  }
  if (authData != 0) {
    encoded += authData->MPEG2Encode();
  }
  return true;
}

/*! \brief  Authenticate this message (add authentication).

    If authentication already exists, fails. Thus caller must verify
    if this is the case.

    \param  crypto      input, crypto provider.
    \param  context     input, private context used for authentication.

    \returns  Boolean indicating success or failure.
*/
bool MutualAuthenticationIPMPData::Authenticate(CryptoProvider* crypto,
    PrivateAuthContext* context) {
  if (authCodes != 0) {
    return false;
  }
  ByteSeq encoded;
  if (AuthMPEG2Encode(encoded) == false) {
    return false;
  }
  HashCalculator* hasher;
  if (context->CreateHashCalculator(crypto, &hasher) == false) {
    return false;
  }
  ByteSeq hashed, codes;
  if (hasher->HashData(encoded, hashed) == false) {
    delete hasher;
    return false;
  }
  delete hasher;
  PublicSigner* signer;
  if (context->CreatePublicSigner(crypto, &signer) == false) {
    return false;
  }
  if (signer->CreateSignature(hashed, codes) == false) {
    delete signer;
    return false;
  }
  delete signer;
  PublicAuthContext* pub;
  if (context->CreatePublicContext(&pub) == false) {
    return false;
  }
  authCodes = new AuthCodes(pub, codes);
  return true;
}

/*! \brief  Check authentication.

    If authentication codes are not present, fails. Thus caller must verify
    if this is the case.

    \param  crypto      input, crypto provider.

    \returns  Boolean indicating success or failure.
*/
bool MutualAuthenticationIPMPData::CheckAuthentication(CryptoProvider* crypto) {
  if (authCodes == 0) {
    return false;
  }
  ByteSeq encoded;
  if (AuthMPEG2Encode(encoded) == false) {
    return false;
  }
  return authCodes->Check(crypto, encoded);
}

/*! \brief  Get request negotiation flag.

    \returns Request negotiation flag.
*/
const bool MutualAuthenticationIPMPData::GetRequestNegotiation() const {
  return (candidateAlgorithms.size() > 0);
}

/*! \brief  Get success negotiation flag.

    \returns Success negotiation flag.
*/
const bool MutualAuthenticationIPMPData::GetSuccessNegotiation() const {
  return (agreedAlgorithms.size() > 0);
}

/*! \brief  Get failed negotiation flag.

    \returns Failed negotiation flag.
*/
const bool MutualAuthenticationIPMPData::GetFailedNegotiation() const {
  return failedNegotiation;
}

/*! \brief  Get candidate algorithms.

    \returns Candidate algorithms.
*/
const std::vector<AlgorithmDescriptor*>& MutualAuthenticationIPMPData::GetCandidateAlgorithms() const {
  return candidateAlgorithms;
}

/*! \brief  Get agreed algorithms.

    \returns Agreed algorithms.
*/
const std::vector<AlgorithmDescriptor*>& MutualAuthenticationIPMPData::GetAgreedAlgorithms() const {
  return agreedAlgorithms;
}

/*! \brief  Get authentication data.

    \returns Authentication data.
*/
const ByteSeq* MutualAuthenticationIPMPData::GetAuthenticationData() const {
  return authData;
}

/*! \brief  Get authentication codes.

    \returns Authentication codes.
*/
AuthCodes* MutualAuthenticationIPMPData::GetAuthenticationCodes() {
  return authCodes;
}

/*! \brief  Set authentication codes (can be 0).
*/
void MutualAuthenticationIPMPData::SetAuthenticationCodes(AuthCodes* codes) {
  if (authCodes != 0) delete authCodes;
  authCodes = codes;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
