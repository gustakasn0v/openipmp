/**	\file Authenticator.h

	Interface for a class that performs mutual authentication between two entities.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (AUTHENTICATOR_H)
#define AUTHENTICATOR_H

#include "BasicTypes.h"
#include <vector>
#include "CryptoProvider.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Authenticator that performs authentication between two entities.
*/
class Authenticator {
public:
  virtual ~Authenticator() {
  }

  /*! \brief  Simulated authentication steps.

      Finite automaton is defined with:
      Init + ByteSeq()    -> send ByteSeq("1"), change state to Waiting2.
      Init + ByteSeq("1") -> send ByteSeq("2"), change state to Waiting3.
      Waiting2 + ByteSeq("2") -> send ByteSeq("3"), change state to final.
      Waiting3 + ByteSeq("3") -> change state to final.
  */
  enum AuthenticationState {
    Init = 0,
    Waiting2 = 1,
    Waiting3 = 2,
    Final = 3
  };

  /*! \brief  Perform authentication step and possibly create symmetric
              operator (if authentication is done).

      If output symmetric operator is != 0, it means that authentication
      is done. In this case, if output authentication data is empty, then
      no (last) response is sent, otherwise a (last) response is sent.
      If output symmetric operator is == 0, it means that authentication
      is not yet done. In this case, if output authentication data is not
      empty, then a response is sent, otherwise it's an error.

      If in is empty, it means that authenticator must perform first step
      in the authentication protocol.

      \param  crypto    input, crypto provider.
      \param  in        input, authentication data.
      \param  out       output, authentication data.
      \param  oper      output, if authentication is done, symmetric operator.    

      \returns  Boolean indicating success or failure.
  */
  virtual bool AuthenticationStep(CryptoProvider* crypto, const ByteSeq& in,
    ByteSeq& out, SymmetricOperator** oper) = 0;
};

/*! \brief  Authenticator that performs authentication between two entities.

    Diffie-Hellman key agreement scheme.
*/
class DiffieHellmanAuthenticator: public Authenticator {
public:
  /*! \brief  Constructor.

      \param  certsA          private certificates of the first agent.
      \param  certsB          public certificates of the second agent.
  */
#if defined (WIN32)
  DiffieHellmanAuthenticator(const std::vector<ByteSeq>& certsA,
    const std::vector<ByteSeq>& certsB): certificatesA(certsA),
    certificatesB(certsB), state(AuthenticationState::Init) {
  }
#elif defined (LINUX)
  DiffieHellmanAuthenticator(const std::vector<ByteSeq>& certsA,
    const std::vector<ByteSeq>& certsB): certificatesA(certsA),
    certificatesB(certsB), state(Init) {
  }
#endif

  virtual ~DiffieHellmanAuthenticator() {
  }

  /*! \brief  Perform authentication step and possibly create symmetric
              operator (if authentication is done).

      If output symmetric operator is != 0, it means that authentication
      is done. In this case, if output authentication data is empty, then
      no (last) response is sent, otherwise a (last) response is sent.
      If output symmetric operator is == 0, it means that authentication
      is not yet done. In this case, if output authentication data is not
      empty, then a response is sent, otherwise it's an error.

      If in is empty, it means that authenticator must perform first step
      in the authentication protocol.

      \param  crypto    input, crypto provider.
      \param  in        input, authentication data.
      \param  out       output, authentication data.
      \param  oper      output, if authentication is done, symmetric operator.    

      \returns  Boolean indicating success or failure.
  */
  virtual bool AuthenticationStep(CryptoProvider* crypto, const ByteSeq& in,
    ByteSeq& out, SymmetricOperator** oper);

private:
  //! Private certificates of the first agent.
  std::vector<ByteSeq> certificatesA;
  //! Public certificates of the second agent.
  std::vector<ByteSeq> certificatesB;
  //! Current state.
  AuthenticationState state;
};

/*! \brief  Authenticator that performs authentication between two entities.

    Ephemeral Diffie-Hellman key agreement scheme.
*/
class EphemeralDiffieHellmanAuthenticator: public Authenticator {
public:
  /*! \brief  Constructor.

      \param  certsA          private certificates of the first agent.
      \param  certsB          public certificates of the second agent.
  */
#if defined (WIN32)
  EphemeralDiffieHellmanAuthenticator(const std::vector<ByteSeq>& certsA,
    const std::vector<ByteSeq>& certsB): certificatesA(certsA),
    certificatesB(certsB), state(AuthenticationState::Init) {
  }
#elif defined (LINUX)
  EphemeralDiffieHellmanAuthenticator(const std::vector<ByteSeq>& certsA,
    const std::vector<ByteSeq>& certsB): certificatesA(certsA),
    certificatesB(certsB), state(Init) {
  }
#endif

  virtual ~EphemeralDiffieHellmanAuthenticator() {
  }

  /*! \brief  Perform authentication step and possibly create symmetric
              operator (if authentication is done).

      If output symmetric operator is != 0, it means that authentication
      is done. In this case, if output authentication data is empty, then
      no (last) response is sent, otherwise a (last) response is sent.
      If output symmetric operator is == 0, it means that authentication
      is not yet done. In this case, if output authentication data is not
      empty, then a response is sent, otherwise it's an error.

      If in is empty, it means that authenticator must perform first step
      in the authentication protocol.

      \param  crypto    input, crypto provider.
      \param  in        input, authentication data.
      \param  out       output, authentication data.
      \param  oper      output, if authentication is done, symmetric operator.    

      \returns  Boolean indicating success or failure.
  */
  virtual bool AuthenticationStep(CryptoProvider* crypto, const ByteSeq& in,
    ByteSeq& out, SymmetricOperator** oper);

private:
  //! Private certificates of the first agent.
  std::vector<ByteSeq> certificatesA;
  //! Public certificates of the second agent.
  std::vector<ByteSeq> certificatesB;
  //! Current state.
  AuthenticationState state;
};

/*! \brief  Authenticator that performs authentication between two entities.

    Diffie-Hellman key agreement scheme combined with symmetric encryption.
*/
class EncDiffieHellmanAuthenticator: public Authenticator {
public:
  /*! \brief  Constructor.

      \param  certsA          private certificates of the first agent.
      \param  certsB          public certificates of the second agent.
  */
#if defined (WIN32)
  EncDiffieHellmanAuthenticator(const std::vector<ByteSeq>& certsA,
    const std::vector<ByteSeq>& certsB): certificatesA(certsA),
    certificatesB(certsB), state(AuthenticationState::Init) {
  }
#elif defined (LINUX)
  EncDiffieHellmanAuthenticator(const std::vector<ByteSeq>& certsA,
    const std::vector<ByteSeq>& certsB): certificatesA(certsA),
    certificatesB(certsB), state(Init) {
  }
#endif

  virtual ~EncDiffieHellmanAuthenticator() {
  }

  /*! \brief  Perform authentication step and possibly create symmetric
              operator (if authentication is done).

      If output symmetric operator is != 0, it means that authentication
      is done. In this case, if output authentication data is empty, then
      no (last) response is sent, otherwise a (last) response is sent.
      If output symmetric operator is == 0, it means that authentication
      is not yet done. In this case, if output authentication data is not
      empty, then a response is sent, otherwise it's an error.

      If in is empty, it means that authenticator must perform first step
      in the authentication protocol.

      \param  crypto    input, crypto provider.
      \param  in        input, authentication data.
      \param  out       output, authentication data.
      \param  oper      output, if authentication is done, symmetric operator.    

      \returns  Boolean indicating success or failure.
  */
  virtual bool AuthenticationStep(CryptoProvider* crypto, const ByteSeq& in,
    ByteSeq& out, SymmetricOperator** oper);

private:
  //! Private certificates of the first agent.
  std::vector<ByteSeq> certificatesA;
  //! Public certificates of the second agent.
  std::vector<ByteSeq> certificatesB;
  //! Current state.
  AuthenticationState state;
};

/*! \brief  Authenticator that performs authentication between two entities.

    Ephemeral Diffie-Hellman key agreement scheme combined with symmetric
    encryption.
*/
class EncEphemeralDiffieHellmanAuthenticator: public Authenticator {
public:
  /*! \brief  Constructor.

      \param  certsA          private certificates of the first agent.
      \param  certsB          public certificates of the second agent.
  */
#if defined (WIN32)
  EncEphemeralDiffieHellmanAuthenticator(const std::vector<ByteSeq>& certsA,
    const std::vector<ByteSeq>& certsB): certificatesA(certsA),
    certificatesB(certsB), state(AuthenticationState::Init) {
  }
#elif defined (LINUX)
  EncEphemeralDiffieHellmanAuthenticator(const std::vector<ByteSeq>& certsA,
    const std::vector<ByteSeq>& certsB): certificatesA(certsA),
    certificatesB(certsB), state(Init) {
  }
#endif

  virtual ~EncEphemeralDiffieHellmanAuthenticator() {
  }

  /*! \brief  Perform authentication step and possibly create symmetric
              operator (if authentication is done).

      If output symmetric operator is != 0, it means that authentication
      is done. In this case, if output authentication data is empty, then
      no (last) response is sent, otherwise a (last) response is sent.
      If output symmetric operator is == 0, it means that authentication
      is not yet done. In this case, if output authentication data is not
      empty, then a response is sent, otherwise it's an error.

      If in is empty, it means that authenticator must perform first step
      in the authentication protocol.

      \param  crypto    input, crypto provider.
      \param  in        input, authentication data.
      \param  out       output, authentication data.
      \param  oper      output, if authentication is done, symmetric operator.    

      \returns  Boolean indicating success or failure.
  */
  virtual bool AuthenticationStep(CryptoProvider* crypto, const ByteSeq& in,
    ByteSeq& out, SymmetricOperator** oper);

private:
  //! Private certificates of the first agent.
  std::vector<ByteSeq> certificatesA;
  //! Public certificates of the second agent.
  std::vector<ByteSeq> certificatesB;
  //! Current state.
  AuthenticationState state;
};

/*! \brief  Authenticator that performs authentication between two entities.

    RSA Needham-Schroeder scheme.
*/
class RSANeedhamSchroederAuthenticator: public Authenticator {
public:
  /*! \brief  Constructor.

      \param  kA          private key of the first agent.
      \param  kB          public key of the second agent.
  */
#if defined (WIN32)
  RSANeedhamSchroederAuthenticator(const ByteSeq& kA, const ByteSeq& kB):
    keyA(kA), keyB(kB), state(AuthenticationState::Init) {
  }
#elif defined (LINUX)
  RSANeedhamSchroederAuthenticator(const ByteSeq& kA, const ByteSeq& kB):
    keyA(kA), keyB(kB), state(Init) {
  }
#endif

  virtual ~RSANeedhamSchroederAuthenticator() {
  }

  /*! \brief  Perform authentication step and possibly create symmetric
              operator (if authentication is done).

      If output symmetric operator is != 0, it means that authentication
      is done. In this case, if output authentication data is empty, then
      no (last) response is sent, otherwise a (last) response is sent.
      If output symmetric operator is == 0, it means that authentication
      is not yet done. In this case, if output authentication data is not
      empty, then a response is sent, otherwise it's an error.

      If in is empty, it means that authenticator must perform first step
      in the authentication protocol.

      \param  crypto    input, crypto provider.
      \param  in        input, authentication data.
      \param  out       output, authentication data.
      \param  oper      output, if authentication is done, symmetric operator.    

      \returns  Boolean indicating success or failure.
  */
  virtual bool AuthenticationStep(CryptoProvider* crypto, const ByteSeq& in,
    ByteSeq& out, SymmetricOperator** oper);

private:
  //! Key of the first agent.
  ByteSeq keyA;
  //! Key of the second agent.
  ByteSeq keyB;
  //! Current state.
  AuthenticationState state;
};

/*! \brief  Authenticator that performs authentication between two entities.

    RSA Needham-Schroeder scheme combined with symmetric encryption.
*/
class EncRSANeedhamSchroederAuthenticator: public Authenticator {
public:
  /*! \brief  Constructor.

      \param  kA          private key of the first agent.
      \param  kB          public key of the second agent.
  */
#if defined (WIN32)
  EncRSANeedhamSchroederAuthenticator(const ByteSeq& kA, const ByteSeq& kB):
    keyA(kA), keyB(kB), state(AuthenticationState::Init) {
  }
#elif defined (LINUX)
  EncRSANeedhamSchroederAuthenticator(const ByteSeq& kA, const ByteSeq& kB):
    keyA(kA), keyB(kB), state(Init) {
  }
#endif

  virtual ~EncRSANeedhamSchroederAuthenticator() {
  }

  /*! \brief  Perform authentication step and possibly create symmetric
              operator (if authentication is done).

      If output symmetric operator is != 0, it means that authentication
      is done. In this case, if output authentication data is empty, then
      no (last) response is sent, otherwise a (last) response is sent.
      If output symmetric operator is == 0, it means that authentication
      is not yet done. In this case, if output authentication data is not
      empty, then a response is sent, otherwise it's an error.

      If in is empty, it means that authenticator must perform first step
      in the authentication protocol.

      \param  crypto    input, crypto provider.
      \param  in        input, authentication data.
      \param  out       output, authentication data.
      \param  oper      output, if authentication is done, symmetric operator.    

      \returns  Boolean indicating success or failure.
  */
  virtual bool AuthenticationStep(CryptoProvider* crypto, const ByteSeq& in,
    ByteSeq& out, SymmetricOperator** oper);

private:
  //! Private key of the first agent.
  ByteSeq keyA;
  //! Public key of the second agent.
  ByteSeq keyB;
  //! Current state.
  AuthenticationState state;
};

/*! \brief  Authenticator that performs authentication between two entities.

    Schnorr identification scheme.

    \todo What exactly does this authenticator need for it's functionality?
*/
class SchnorrAuthenticator: public Authenticator {
public:
#if defined (WIN32)
  SchnorrAuthenticator(): state(AuthenticationState::Init) {
  }
#elif defined (LINUX)
  SchnorrAuthenticator(): state(Init) {
  }
#endif

  virtual ~SchnorrAuthenticator() {
  }

  /*! \brief  Perform authentication step and possibly create symmetric
              operator (if authentication is done).

      If output symmetric operator is != 0, it means that authentication
      is done. In this case, if output authentication data is empty, then
      no (last) response is sent, otherwise a (last) response is sent.
      If output symmetric operator is == 0, it means that authentication
      is not yet done. In this case, if output authentication data is not
      empty, then a response is sent, otherwise it's an error.

      If in is empty, it means that authenticator must perform first step
      in the authentication protocol.

      \param  crypto    input, crypto provider.
      \param  in        input, authentication data.
      \param  out       output, authentication data.
      \param  oper      output, if authentication is done, symmetric operator.    

      \returns  Boolean indicating success or failure.
  */
  virtual bool AuthenticationStep(CryptoProvider* crypto, const ByteSeq& in,
    ByteSeq& out, SymmetricOperator** oper);

private:
  //! Current state.
  AuthenticationState state;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // #if !defined (AUTHENTICATOR_H)
