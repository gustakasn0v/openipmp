/**	\file Authenticator.cpp

	Interface for a class that performs mutual authentication between two entities.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "Authenticator.h"

#include "BasicTypes.h"
#include <vector>
#include "CryptoProvider.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Authenticator that performs authentication between two entities.

    Diffie-Hellman key agreement scheme.
*/
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
bool DiffieHellmanAuthenticator::AuthenticationStep(CryptoProvider* crypto,
    const ByteSeq& in, ByteSeq& out, SymmetricOperator** oper) {
/*
    Init + ByteSeq()    -> send ByteSeq("1"), change state to Waiting2.
    Init + ByteSeq("1") -> send ByteSeq("2"), change state to Waiting3.
    Waiting2 + ByteSeq("2") -> send ByteSeq("3"), change state to final.
    Waiting3 + ByteSeq("3") -> change state to final;
*/
  switch (state) {
#if defined (WIN32)
    case AuthenticationState::Init:
#elif defined (LINUX)
    case Init:
#endif
      if (in == ByteSeq()) {
        out = ByteSeq("1");
#if defined (WIN32)
        state = AuthenticationState::Waiting2;
#elif defined (LINUX)
        state = Waiting2;
#endif
        break;
      }
      if (in == ByteSeq("1")) {
        out = ByteSeq("2");
#if defined (WIN32)
        state = AuthenticationState::Waiting3;
#elif defined (LINUX)
        state = Waiting3;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting2:
#elif defined (LINUX)
    case Waiting2:
#endif
      if (in == ByteSeq("2")) {
        out = ByteSeq("3");
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting3:
#elif defined (LINUX)
    case Waiting3:
#endif
      if (in == ByteSeq("3")) {
        out = ByteSeq();
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
    default:
      return false;
  }

#if defined (WIN32)
  if (state == AuthenticationState::Final) {
#elif defined (LINUX)
  if (state == Final) {
#endif
    return crypto->CreateSymmetricOperator(ByteSeq("AES128CTR"), ByteSeq(), oper);
  }

  return false;
}

/*! \brief  Authenticator that performs authentication between two entities.

    Ephemeral Diffie-Hellman key agreement scheme.
*/
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
bool EphemeralDiffieHellmanAuthenticator::AuthenticationStep(CryptoProvider* crypto,
    const ByteSeq& in, ByteSeq& out, SymmetricOperator** oper) {
/*
    Init + ByteSeq()    -> send ByteSeq("1"), change state to Waiting2.
    Init + ByteSeq("1") -> send ByteSeq("2"), change state to Waiting3.
    Waiting2 + ByteSeq("2") -> send ByteSeq("3"), change state to final.
    Waiting3 + ByteSeq("3") -> change state to final;
*/
  switch (state) {
#if defined (WIN32)
    case AuthenticationState::Init:
#elif defined (LINUX)
    case Init:
#endif
      if (in == ByteSeq()) {
        out = ByteSeq("1");
#if defined (WIN32)
        state = AuthenticationState::Waiting2;
#elif defined (LINUX)
        state = Waiting2;
#endif
        break;
      }
      if (in == ByteSeq("1")) {
        out = ByteSeq("2");
#if defined (WIN32)
        state = AuthenticationState::Waiting3;
#elif defined (LINUX)
        state = Waiting3;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting2:
#elif defined (LINUX)
    case Waiting2:
#endif
      if (in == ByteSeq("2")) {
        out = ByteSeq("3");
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting3:
#elif defined (LINUX)
    case Waiting3:
#endif
      if (in == ByteSeq("3")) {
        out = ByteSeq();
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
    default:
      return false;
  }

#if defined (WIN32)
  if (state == AuthenticationState::Final) {
#elif defined (LINUX)
  if (state == Final) {
#endif
    return crypto->CreateSymmetricOperator(ByteSeq("AES128CTR"), ByteSeq(), oper);
  }

  return false;
}

/*! \brief  Authenticator that performs authentication between two entities.

    Diffie-Hellman key agreement scheme combined with symmetric encryption.
*/
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
bool EncDiffieHellmanAuthenticator::AuthenticationStep(CryptoProvider* crypto,
    const ByteSeq& in, ByteSeq& out, SymmetricOperator** oper) {
/*
    Init + ByteSeq()    -> send ByteSeq("1"), change state to Waiting2.
    Init + ByteSeq("1") -> send ByteSeq("2"), change state to Waiting3.
    Waiting2 + ByteSeq("2") -> send ByteSeq("3"), change state to final.
    Waiting3 + ByteSeq("3") -> change state to final;
*/
  switch (state) {
#if defined (WIN32)
    case AuthenticationState::Init:
#elif defined (LINUX)
    case Init:
#endif
      if (in == ByteSeq()) {
        out = ByteSeq("1");
#if defined (WIN32)
        state = AuthenticationState::Waiting2;
#elif defined (LINUX)
        state = Waiting2;
#endif
        break;
      }
      if (in == ByteSeq("1")) {
        out = ByteSeq("2");
#if defined (WIN32)
        state = AuthenticationState::Waiting3;
#elif defined (LINUX)
        state = Waiting3;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting2:
#elif defined (LINUX)
    case Waiting2:
#endif
      if (in == ByteSeq("2")) {
        out = ByteSeq("3");
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting3:
#elif defined (LINUX)
    case Waiting3:
#endif
      if (in == ByteSeq("3")) {
        out = ByteSeq();
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
    default:
      return false;
  }

#if defined (WIN32)
  if (state == AuthenticationState::Final) {
#elif defined (LINUX)
  if (state == Final) {
#endif
    return crypto->CreateSymmetricOperator(ByteSeq("AES128CTR"), ByteSeq(), oper);
  }

  return false;
}

/*! \brief  Authenticator that performs authentication between two entities.

    Ephemeral Diffie-Hellman key agreement scheme combined with symmetric
    encryption.
*/
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
bool EncEphemeralDiffieHellmanAuthenticator::AuthenticationStep(CryptoProvider* crypto,
    const ByteSeq& in, ByteSeq& out, SymmetricOperator** oper) {
/*
    Init + ByteSeq()    -> send ByteSeq("1"), change state to Waiting2.
    Init + ByteSeq("1") -> send ByteSeq("2"), change state to Waiting3.
    Waiting2 + ByteSeq("2") -> send ByteSeq("3"), change state to final.
    Waiting3 + ByteSeq("3") -> change state to final;
*/
  switch (state) {
#if defined (WIN32)
    case AuthenticationState::Init:
#elif defined (LINUX)
    case Init:
#endif
      if (in == ByteSeq()) {
        out = ByteSeq("1");
#if defined (WIN32)
        state = AuthenticationState::Waiting2;
#elif defined (LINUX)
        state = Waiting2;
#endif
        break;
      }
      if (in == ByteSeq("1")) {
        out = ByteSeq("2");
#if defined (WIN32)
        state = AuthenticationState::Waiting3;
#elif defined (LINUX)
        state = Waiting3;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting2:
#elif defined (LINUX)
    case Waiting2:
#endif
      if (in == ByteSeq("2")) {
        out = ByteSeq("3");
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting3:
#elif defined (LINUX)
    case Waiting3:
#endif
      if (in == ByteSeq("3")) {
        out = ByteSeq();
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
    default:
      return false;
  }

#if defined (WIN32)
  if (state == AuthenticationState::Final) {
#elif defined (LINUX)
  if (state == Final) {
#endif
    return crypto->CreateSymmetricOperator(ByteSeq("AES128CTR"), ByteSeq(), oper);
  }

  return false;
}

/*! \brief  Authenticator that performs authentication between two entities.

    RSA Needham-Schroeder scheme.
*/
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
bool RSANeedhamSchroederAuthenticator::AuthenticationStep(CryptoProvider* crypto,
    const ByteSeq& in, ByteSeq& out, SymmetricOperator** oper) {
/*
    Init + ByteSeq()    -> send ByteSeq("1"), change state to Waiting2.
    Init + ByteSeq("1") -> send ByteSeq("2"), change state to Waiting3.
    Waiting2 + ByteSeq("2") -> send ByteSeq("3"), change state to final.
    Waiting3 + ByteSeq("3") -> change state to final;
*/
  switch (state) {
#if defined (WIN32)
    case AuthenticationState::Init:
#elif defined (LINUX)
    case Init:
#endif
      if (in == ByteSeq()) {
        out = ByteSeq("1");
#if defined (WIN32)
        state = AuthenticationState::Waiting2;
#elif defined (LINUX)
        state = Waiting2;
#endif
        break;
      }
      if (in == ByteSeq("1")) {
        out = ByteSeq("2");
#if defined (WIN32)
        state = AuthenticationState::Waiting3;
#elif defined (LINUX)
        state = Waiting3;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting2:
#elif defined (LINUX)
    case Waiting2:
#endif
      if (in == ByteSeq("2")) {
        out = ByteSeq("3");
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting3:
#elif defined (LINUX)
    case Waiting3:
#endif
      if (in == ByteSeq("3")) {
        out = ByteSeq();
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
    default:
      return false;
  }

#if defined (WIN32)
  if (state == AuthenticationState::Final) {
#elif defined (LINUX)
  if (state == Final) {
#endif
    return crypto->CreateSymmetricOperator(ByteSeq("AES128CTR"), ByteSeq(), oper);
  }

  return true;
}

/*! \brief  Authenticator that performs authentication between two entities.

    RSA Needham-Schroeder scheme combined with symmetric encryption.
*/
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
bool EncRSANeedhamSchroederAuthenticator::AuthenticationStep(CryptoProvider* crypto,
    const ByteSeq& in, ByteSeq& out, SymmetricOperator** oper) {
/*
    Init + ByteSeq()    -> send ByteSeq("1"), change state to Waiting2.
    Init + ByteSeq("1") -> send ByteSeq("2"), change state to Waiting3.
    Waiting2 + ByteSeq("2") -> send ByteSeq("3"), change state to final.
    Waiting3 + ByteSeq("3") -> change state to final;
*/
  switch (state) {
#if defined (WIN32)
    case AuthenticationState::Init:
#elif defined (LINUX)
    case Init:
#endif
      if (in == ByteSeq()) {
        out = ByteSeq("1");
#if defined (WIN32)
        state = AuthenticationState::Waiting2;
#elif defined (LINUX)
        state = Waiting2;
#endif
        break;
      }
      if (in == ByteSeq("1")) {
        out = ByteSeq("2");
#if defined (WIN32)
        state = AuthenticationState::Waiting3;
#elif defined (LINUX)
        state = Waiting3;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting2:
#elif defined (LINUX)
    case Waiting2:
#endif
      if (in == ByteSeq("2")) {
        out = ByteSeq("3");
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting3:
#elif defined (LINUX)
    case Waiting3:
#endif
      if (in == ByteSeq("3")) {
        out = ByteSeq();
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
    default:
      return false;
  }

#if defined (WIN32)
  if (state == AuthenticationState::Final) {
#elif defined (LINUX)
  if (state == Final) {
#endif
    return crypto->CreateSymmetricOperator(ByteSeq("AES128CTR"), ByteSeq(), oper);
  }

  return false;
}

/*! \brief  Authenticator that performs authentication between two entities.

    Schnorr identification scheme.

    \todo What exactly does this authenticator need for it's functionality?
*/
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
bool SchnorrAuthenticator::AuthenticationStep(CryptoProvider* crypto,
    const ByteSeq& in, ByteSeq& out, SymmetricOperator** oper) {
/*
    Init + ByteSeq()    -> send ByteSeq("1"), change state to Waiting2.
    Init + ByteSeq("1") -> send ByteSeq("2"), change state to Waiting3.
    Waiting2 + ByteSeq("2") -> send ByteSeq("3"), change state to final.
    Waiting3 + ByteSeq("3") -> change state to final;
*/
  switch (state) {
#if defined (WIN32)
    case AuthenticationState::Init:
#elif defined (LINUX)
    case Init:
#endif
      if (in == ByteSeq()) {
        out = ByteSeq("1");
#if defined (WIN32)
        state = AuthenticationState::Waiting2;
#elif defined (LINUX)
        state = Waiting2;
#endif
        break;
      }
      if (in == ByteSeq("1")) {
        out = ByteSeq("2");
#if defined (WIN32)
        state = AuthenticationState::Waiting3;
#elif defined (LINUX)
        state = Waiting3;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting2:
#elif defined (LINUX)
    case Waiting2:
#endif
      if (in == ByteSeq("2")) {
        out = ByteSeq("3");
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
#if defined (WIN32)
    case AuthenticationState::Waiting3:
#elif defined (LINUX)
    case Waiting3:
#endif
      if (in == ByteSeq("3")) {
        out = ByteSeq();
#if defined (WIN32)
        state = AuthenticationState::Final;
#elif defined (LINUX)
        state = Final;
#endif
        break;
      }
      return false;
    default:
      return false;
  }

#if defined (WIN32)
  if (state == AuthenticationState::Final) {
#elif defined (LINUX)
  if (state == Final) {
#endif
    return crypto->CreateSymmetricOperator(ByteSeq("AES128CTR"), ByteSeq(), oper);
  }

  return false;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
