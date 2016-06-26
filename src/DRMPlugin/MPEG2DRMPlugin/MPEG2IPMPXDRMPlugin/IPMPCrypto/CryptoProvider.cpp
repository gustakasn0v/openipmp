/**	\file CryptoProvider.cpp

	Interface for crypto providers.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "BasicTypes.h"
#include "CryptoProvider.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \todo Here we provide simple dummy implementations of the crypto classes.
*/

/*! \brief  SHA1 hash calculator.
*/
class SHA1HashCalculator: public HashCalculator {
public:
  /*! \brief  Constructor.
  */
  SHA1HashCalculator() {
  }

  virtual ~SHA1HashCalculator() {
  }

  /*! \brief  Initialize hash calculation.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HashInit() {
    return true;
  }

  /*! \brief  Update hash calculation with new data.

      \param  in          input, data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HashUpdate(const ByteSeq& in) {
    return true;
  }

  /*! \brief  Finish hash calculation.

      \param  out         output, hash.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HashFinish(ByteSeq& out) {
    return true;
  }
};

/*! \brief  RSA public key encryptor.

    Using contained public key, perform encryption.
*/
class RSAPublicEncryptor: public PublicEncryptor {
public:
  /*! \brief  Constructor.
  */
  RSAPublicEncryptor() {
  }

  virtual ~RSAPublicEncryptor() {
  }

  /*! \brief  Encrypt data.

      \param  in          input, plain data.
      \param  out         output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encrypt(const ByteSeq& in, ByteSeq& out) {
    out = in;
    return true;
  }
};

/*! \brief  RSA public key decryptor.

    Using contained public and private key, perform encryption and decryption.
*/
class RSAPublicDecryptor: public PublicDecryptor {
public:
  /*! \brief  Constructor.
  */
  RSAPublicDecryptor() {
  }

  virtual ~RSAPublicDecryptor() {
  }

  /*! \brief  Encrypt data.

      \param  in          input, plain data.
      \param  out         output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encrypt(const ByteSeq& in, ByteSeq& out) {
    out = in;
    return true;
  }

  /*! \brief  Decrypt data.

      \param  in          input, encrypted data.
      \param  out         output, decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Decrypt(const ByteSeq& in, ByteSeq& out) {
    out = in;
    return true;
  }
};

/*! \brief  DSA public key verifier.

    Using contained public key, perform verification.
*/
class DSAPublicVerifier: public PublicVerifier {
public:
  /*! \brief  Constructor.
  */
  DSAPublicVerifier() {
  }

  virtual ~DSAPublicVerifier() {
  }

  /*! \brief  Verify signature.

      \param  in          input, signature.
      \param  hash        input, hash to be verified.

      \returns  Boolean indicating success or failure.
  */
  virtual bool VerifySignature(const ByteSeq& in, const ByteSeq& hash) {
    return true;
  }
};

/*! \brief  DSA public key signer.

    Using contained public and private key, perform verification and signing.
*/
class DSAPublicSigner: public PublicSigner {
public:
  /*! \brief  Constructor.
  */
  DSAPublicSigner() {
  }

  virtual ~DSAPublicSigner() {
  }

  /*! \brief  Verify signature.

      \param  in          input, signature.
      \param  hash        input, hash to be verified.

      \returns  Boolean indicating success or failure.
  */
  virtual bool VerifySignature(const ByteSeq& in, const ByteSeq& hash) {
    return true;
  }

  /*! \brief  Create signature.

      \param  hash        input, hash to be signed.
      \param  out         output, signature.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateSignature(const ByteSeq& hash, ByteSeq& out) {
    return true;
  }
};

/*! \brief  AES128CTR symmetric key operator.

    Using contained key, perform encryption and decryption.
*/
class AES128CTRSymmetricOperator: public SymmetricOperator {
public:
  /*! \brief  Constructor.
  */
  AES128CTRSymmetricOperator() {
  }

  virtual ~AES128CTRSymmetricOperator() {
  }

  /*! \brief  Create an exact copy.

      Used in copy constructors in classes that contain a symmetric operator.

      \returns New copy of this operator.
  */
  virtual SymmetricOperator* Copy() {
    return new AES128CTRSymmetricOperator();
  }

  /*! \brief  Encrypt data and create message authentication code (MAC).

      \param  in          input, plain data.
      \param  mac         output, message authentication code (MAC).
      \param  out         output, encrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool EncryptAuthenticate(const ByteSeq& in, ByteSeq& mac,
      ByteSeq& out) {
    out = in;
    mac = ByteSeq();
    return true;
  }

  /*! \brief  Encrypt data and create message authentication code (MAC).

      MAC is assumed to be encrypted in the output data.

      \param  in          input, plain data.
      \param  out         output, encrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool EncryptAuthenticate(const ByteSeq& in, ByteSeq& out) {
    out = in;
    return true;
  }

  /*! \brief  Encrypt data.

      \param  in          input, plain data.
      \param  out         output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encrypt(const ByteSeq& in, ByteSeq& out) {
    out = in;
    return true;
  }

  /*! \brief  Create message authenticaton code (MAC).

      \param  in          input, data.
      \param  mac         output, MAC.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateMAC(const ByteSeq& in, ByteSeq& mac) {
    mac = ByteSeq();
    return true;
  }

  /*! \brief  Decrypt data and check message authentication code (MAC).

      \param  in          input, encrypted data.
      \param  mac         input, message authentication code (MAC).
      \param  out         output, decrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool DecryptAuthenticate(const ByteSeq& in, const ByteSeq& mac,
      ByteSeq& out) {
    out = in;
    return true;
  }

  /*! \brief  Decrypt data and check message authentication code (MAC).

      MAC is assumed to be encrypted in the input data.

      \param  in          input, encrypted data.
      \param  out         output, decrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool DecryptAuthenticate(const ByteSeq& in, ByteSeq& out) {
    out = in;
    return true;
  }

  /*! \brief  Decrypt data.

      \param  in          input, encrypted data.
      \param  out         output, decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Decrypt(const ByteSeq& in, ByteSeq& out) {
    out = in;
    return true;
  }

  /*! \brief  Check message authenticaton code (MAC).

      \param  in          input, data.
      \param  mac         input, MAC.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CheckMAC(const ByteSeq& in, const ByteSeq& mac) {
    return true;
  }
};

/*! \brief  Symmetric key operator which doesn't do any real
            encryption/decryption, just leaves data as it is.

    Using contained key, perform encryption and decryption.
*/
class NullSymmetricOperator: public SymmetricOperator {
public:
  /*! \brief  Constructor.
  */
  NullSymmetricOperator() {
  }

  virtual ~NullSymmetricOperator() {
  }

  /*! \brief  Create an exact copy.

      Used in copy constructors in classes that contain a symmetric operator.

      \returns New copy of this operator.
  */
  virtual SymmetricOperator* Copy() {
    return new NullSymmetricOperator();
  }

  /*! \brief  Encrypt data and create message authentication code (MAC).

      \param  in          input, plain data.
      \param  mac         output, message authentication code (MAC).
      \param  out         output, encrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool EncryptAuthenticate(const ByteSeq& in, ByteSeq& mac,
      ByteSeq& out) {
    out = in;
    mac = ByteSeq();
    return true;
  }

  /*! \brief  Encrypt data and create message authentication code (MAC).

      MAC is assumed to be encrypted in the output data.

      \param  in          input, plain data.
      \param  out         output, encrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool EncryptAuthenticate(const ByteSeq& in, ByteSeq& out) {
    out = in;
    return true;
  }

  /*! \brief  Encrypt data.

      \param  in          input, plain data.
      \param  out         output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encrypt(const ByteSeq& in, ByteSeq& out) {
    out = in;
    return true;
  }

  /*! \brief  Create message authenticaton code (MAC).

      \param  in          input, data.
      \param  mac         output, MAC.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateMAC(const ByteSeq& in, ByteSeq& mac) {
    mac = ByteSeq();
    return true;
  }

  /*! \brief  Decrypt data and check message authentication code (MAC).

      \param  in          input, encrypted data.
      \param  mac         input, message authentication code (MAC).
      \param  out         output, decrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool DecryptAuthenticate(const ByteSeq& in, const ByteSeq& mac,
      ByteSeq& out) {
    out = in;
    return true;
  }

  /*! \brief  Decrypt data and check message authentication code (MAC).

      MAC is assumed to be encrypted in the input data.

      \param  in          input, encrypted data.
      \param  out         output, decrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool DecryptAuthenticate(const ByteSeq& in, ByteSeq& out) {
    out = in;
    return true;
  }

  /*! \brief  Decrypt data.

      \param  in          input, encrypted data.
      \param  out         output, decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Decrypt(const ByteSeq& in, ByteSeq& out) {
    out = in;
    return true;
  }

  /*! \brief  Check message authenticaton code (MAC).

      \param  in          input, data.
      \param  mac         input, MAC.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CheckMAC(const ByteSeq& in, const ByteSeq& mac) {
    return true;
  }
};

/*! \brief  Dummy implementation of crypto provider.
*/
/*! \brief  Create hash calculator.

    \param  alg         input, hash algorithm.
    \param  calc        output, hash calculator.

    \returns Boolean indicating success or failure.
*/
bool DummyCryptoProvider::CreateHashCalculator(const ByteSeq& alg, HashCalculator** calc) {
  *calc = new SHA1HashCalculator();
  return true;
}

/*! \brief  Create public encryptor.

    \param  alg         input, public key algorithm.
    \param  key         input, (public) key.
    \param  enc         output, public encryptor.

    \returns Boolean indicating success or failure.
*/
bool DummyCryptoProvider::CreatePublicEncryptor(const ByteSeq& alg, const ByteSeq& key,
    PublicEncryptor** enc) {
  *enc = new RSAPublicEncryptor();
  return true;
}

/*! \brief  Create public decryptor.

    \param  alg         input, public key algorithm.
    \param  key         input, (public/private) key.
    \param  dec         output, public decryptor.

    \returns Boolean indicating success or failure.
*/
bool DummyCryptoProvider::CreatePublicDecryptor(const ByteSeq& alg, const ByteSeq& key,
    PublicDecryptor** dec) {
  *dec = new RSAPublicDecryptor();
  return true;
}

/*! \brief  Create public verifier.

    \param  alg         input, public key algorithm.
    \param  key         input, (public) key.
    \param  ver         output, public verifier.

    \returns Boolean indicating success or failure.
*/
bool DummyCryptoProvider::CreatePublicVerifier(const ByteSeq& alg, const ByteSeq& key,
    PublicVerifier** ver) {
  *ver = new DSAPublicVerifier();
  return true;
}

/*! \brief  Create public signer.

    \param  alg         input, public key algorithm.
    \param  key         input, (public/private) key.
    \param  sig         output, public signer.

    \returns Boolean indicating success or failure.
*/
bool DummyCryptoProvider::CreatePublicSigner(const ByteSeq& alg, const ByteSeq& key,
    PublicSigner** sig) {
  *sig = new DSAPublicSigner();
  return true;
}

/*! \brief  Create symmetric operator.

    \param  alg         input, symmetric key algorithm.
    \param  key         input, symmetric key.
    \param  symm        output, symmetric operator.

    \returns Boolean indicating success or failure.
*/
bool DummyCryptoProvider::CreateSymmetricOperator(const ByteSeq& alg, const ByteSeq& key,
    SymmetricOperator** symm) {
  if (ByteSeq("AES128CTR") == alg) {
    *symm = new AES128CTRSymmetricOperator();
    return true;
  }
  return false;
}

/*! \brief  Create symmetric operator which doesn't do any real
            encryption/decryption, just leaves data as it is.

    \param  symm        output, symmetric operator.

    \returns Boolean indicating success or failure.
*/
bool DummyCryptoProvider::CreateSymmetricOperator(SymmetricOperator** symm) {
  *symm = new NullSymmetricOperator();
  return true;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
