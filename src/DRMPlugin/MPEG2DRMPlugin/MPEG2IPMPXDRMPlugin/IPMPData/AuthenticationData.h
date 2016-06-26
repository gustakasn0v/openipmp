/**	\file AuthenticationData.h

	IPMP data authentication classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (AUTHENTICATIONDATA_H)
#define AUTHENTICATIONDATA_H

#include "BasicTypes.h"
#include <vector>
#include "CryptoProvider.h"
#include "IPMPData.h"
#include "CryptoContext.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief  Init authentication IPMP data.
*/
class InitAuthenticationIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
      \param  ipmp      input, IPMP descriptor identifier.
      \param  auth      input, authentication type.
  */
  InitAuthenticationIPMPData(const ByteT& ver, const Bit32T& id, const Bit32T&
    ipmp, const ByteT& auth): IPMPData(ver, id), ipmpDescriptorID(ipmp),
    authType(auth) {
  }

  virtual ~InitAuthenticationIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Get IPMP descriptor ID.

      \returns IPMP descriptor ID.
  */
  const Bit32T& GetIPMPDescriptorID() const;

  /*! \brief  Get authentication type.

      \returns Authentication type.
  */
  const ByteT& GetAuthType() const;

private:
  Bit32T ipmpDescriptorID;
  ByteT authType;
};

/*! \brief  Authentication codes contained in MutualAuthenticationIPMPData.
*/
class AuthCodes {
public:
  /*! \brief  Constructor.
      
      \param  ctx         public authentication context (must be != 0).
      \param  auth        authentication codes.
  */
  AuthCodes(PublicAuthContext* ctx, const ByteSeq& auth): context(ctx), codes(auth) {
  }

  virtual ~AuthCodes() {
    if (context != 0) delete context; context = 0;
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Check data using codes contained.

      \param  crypto      input, crypto provider.
      \param  in          input, data to be checked.

      \returns  Boolean indicating check success or failure.
  */
  bool Check(CryptoProvider* crypto, const ByteSeq& in);

  /*! \brief  Get public authentication context.

      \returns Public authentication context.
  */
  PublicAuthContext* GetAuthContext();

  /*! \brief  Get codes.

      \returns Codes.
  */
  const ByteSeq& GetCodes() const;

private:
  PublicAuthContext* context;
  ByteSeq codes;
};

/*!	\brief  Mutual authentication IPMP data.
*/
class MutualAuthenticationIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver         input, version.
      \param  id          input, data identifier.
      \param  failed      input, failed negotiation flag.
      \param  candidate   input, candidate algorithms.
      \param  agreed      input, agreed algorithms.
      \param  auth        input, authentication data.
      \param  codes       input, authentication codes (can be 0).
  */
  MutualAuthenticationIPMPData(const ByteT& ver, const Bit32T& id,
    const bool& failed, const std::vector<AlgorithmDescriptor*>& candidate,
    const std::vector<AlgorithmDescriptor*>& agreed, const ByteSeq& auth,
    AuthCodes* codes): IPMPData(ver, id), failedNegotiation(failed),
    candidateAlgorithms(candidate), agreedAlgorithms(agreed),
    authData(new ByteSeq(auth)), authCodes(codes) {
  }

  /*! \brief  Constructor.
      
      \param  ver         input, version.
      \param  id          input, data identifier.
      \param  failed      input, failed negotiation flag.
      \param  candidate   input, candidate algorithms.
      \param  agreed      input, agreed algorithms.
      \param  codes       input, authentication codes (can be 0).
  */
  MutualAuthenticationIPMPData(const ByteT& ver, const Bit32T& id,
    const bool& failed, const std::vector<AlgorithmDescriptor*>& candidate,
    const std::vector<AlgorithmDescriptor*>& agreed, AuthCodes* codes):
    IPMPData(ver, id), failedNegotiation(failed), candidateAlgorithms(candidate),
    agreedAlgorithms(agreed), authData(0), authCodes(codes) {
  }

  virtual ~MutualAuthenticationIPMPData() {
    std::vector<AlgorithmDescriptor*>::iterator iter;
    iter = candidateAlgorithms.begin();
    while (iter != candidateAlgorithms.end()) {
      if ((*iter) != 0) delete (*iter);
      iter++;
    }
    candidateAlgorithms.clear();
    iter = agreedAlgorithms.begin();
    while (iter != agreedAlgorithms.end()) {
      if ((*iter) != 0) delete (*iter);
      iter++;
    }
    agreedAlgorithms.clear();
    if (authData != 0) delete authData;
    if (authCodes != 0) delete authCodes;
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Encode as byte array without authentication codes.

      Encode for purpose of authenticating the message.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  bool AuthMPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Authenticate this message (add authentication).

      If authentication already exists, fails. Thus caller must verify
      if this is the case.

      \param  crypto      input, crypto provider.
      \param  context     input, private context used for authentication.

      \returns  Boolean indicating success or failure.
  */
  bool Authenticate(CryptoProvider* crypto, PrivateAuthContext* context);

  /*! \brief  Check authentication.

      If authentication codes are not present, fails. Thus caller must verify
      if this is the case.

      \param  crypto      input, crypto provider.

      \returns  Boolean indicating success or failure.
  */
  bool CheckAuthentication(CryptoProvider* crypto);

  /*! \brief  Get request negotiation flag.

      \returns Request negotiation flag.
  */
  const bool GetRequestNegotiation() const;

  /*! \brief  Get success negotiation flag.

      \returns Success negotiation flag.
  */
  const bool GetSuccessNegotiation() const;

  /*! \brief  Get failed negotiation flag.

      \returns Failed negotiation flag.
  */
  const bool GetFailedNegotiation() const;

  /*! \brief  Get candidate algorithms.

      \returns Candidate algorithms.
  */
  const std::vector<AlgorithmDescriptor*>& GetCandidateAlgorithms() const;

  /*! \brief  Get agreed algorithms.

      \returns Agreed algorithms.
  */
  const std::vector<AlgorithmDescriptor*>& GetAgreedAlgorithms() const;

  /*! \brief  Get authentication data.

      \returns Authentication data.
  */
  const ByteSeq* GetAuthenticationData() const;

  /*! \brief  Get authentication codes (can be 0).

      \returns Authentication codes.
  */
  AuthCodes* GetAuthenticationCodes();

  /*! \brief  Set authentication codes (can be 0).
  */
  void SetAuthenticationCodes(AuthCodes* codes);

private:
  bool failedNegotiation;
  std::vector<AlgorithmDescriptor*> candidateAlgorithms;
  std::vector<AlgorithmDescriptor*> agreedAlgorithms;
  ByteSeq* authData;
  AuthCodes* authCodes;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (AUTHENTICATIONDATA_H)
