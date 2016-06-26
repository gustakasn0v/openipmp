/**	\file CryptoProvider.h

	Interface for crypto providers.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (CRYPTOPROVIDER_H)
#define CRYPTOPROVIDER_H

#include "BasicTypes.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Hash calculator.
*/
class HashCalculator {
public:
  virtual ~HashCalculator() {
  }

  /*! \brief  Calculate hash of the input data.

      \param  in          input, data.
      \param  out         output, hash.

      \returns  Boolean indicating success or failure.
  */
  bool HashData(const ByteSeq& in, ByteSeq& out) {
    if (HashInit() == false) {
      return false;
    }
    if (HashUpdate(in) == false) {
      return false;
    }
    if (HashFinish(out) == false) {
      return false;
    }
    return true;
  }

  /*! \brief  Initialize hash calculation.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HashInit() = 0;

  /*! \brief  Update hash calculation with new data.

      \param  in          input, data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HashUpdate(const ByteSeq& in) = 0;

  /*! \brief  Finish hash calculation.

      \param  out         output, hash.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HashFinish(ByteSeq& out) = 0;
};

/*! \brief  Public key encryptor.

    Using contained public key, perform encryption.
*/
class PublicEncryptor {
public:
  virtual ~PublicEncryptor() {
  }

  /*! \brief  Encrypt data.

      \param  in          input, plain data.
      \param  out         output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encrypt(const ByteSeq& in, ByteSeq& out) = 0;
};

/*! \brief  Public key decryptor.

    Using contained public and private key, perform encryption and decryption.
*/
class PublicDecryptor: public PublicEncryptor {
public:
  virtual ~PublicDecryptor() {
  }

  /*! \brief  Decrypt data.

      \param  in          input, encrypted data.
      \param  out         output, decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Decrypt(const ByteSeq& in, ByteSeq& out) = 0;
};

/*! \brief  Public key verifier.

    Using contained public key, perform verification.
*/
class PublicVerifier {
public:
  virtual ~PublicVerifier() {
  }

  /*! \brief  Verify signature.

      \param  in          input, signature.
      \param  hash        input, hash to be verified.

      \returns  Boolean indicating success or failure.
  */
  virtual bool VerifySignature(const ByteSeq& in, const ByteSeq& hash) = 0;
};

/*! \brief  Public key signer.

    Using contained public and private key, perform verification and signing.
*/
class PublicSigner: public PublicVerifier {
public:
  virtual ~PublicSigner() {
  }

  /*! \brief  Create signature.

      \param  hash        input, hash to be signed.
      \param  out         output, signature.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateSignature(const ByteSeq& hash, ByteSeq& out) = 0;
};

/*! \brief  Symmetric key operator.

    Using contained key, perform encryption and decryption.
*/
class SymmetricOperator {
public:
  virtual ~SymmetricOperator() {
  }

  /*! \brief  Create an exact copy.

      Used in copy constructors in classes that contain a symmetric operator.

      \returns New copy of this operator.
  */
  virtual SymmetricOperator* Copy() = 0;

  /*! \brief  Encrypt data and create message authentication code (MAC).

      \param  in          input, plain data.
      \param  mac         output, message authentication code (MAC).
      \param  out         output, encrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool EncryptAuthenticate(const ByteSeq& in, ByteSeq& mac,
    ByteSeq& out) = 0;

  /*! \brief  Encrypt data and create message authentication code (MAC).

      MAC is assumed to be encrypted in the output data.

      \param  in          input, plain data.
      \param  out         output, encrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool EncryptAuthenticate(const ByteSeq& in, ByteSeq& out) = 0;

  /*! \brief  Encrypt data.

      \param  in          input, plain data.
      \param  out         output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encrypt(const ByteSeq& in, ByteSeq& out) = 0;

  /*! \brief  Create message authenticaton code (MAC).

      \param  in          input, data.
      \param  mac         output, MAC.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateMAC(const ByteSeq& in, ByteSeq& mac) = 0;

  /*! \brief  Decrypt data and check message authentication code (MAC).

      \param  in          input, encrypted data.
      \param  mac         input, message authentication code (MAC).
      \param  out         output, decrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool DecryptAuthenticate(const ByteSeq& in, const ByteSeq& mac,
    ByteSeq& out) = 0;

  /*! \brief  Decrypt data and check message authentication code (MAC).

      MAC is assumed to be encrypted in the input data.

      \param  in          input, encrypted data.
      \param  out         output, decrypted and authenticated data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool DecryptAuthenticate(const ByteSeq& in, ByteSeq& out) = 0;

  /*! \brief  Decrypt data.

      \param  in          input, encrypted data.
      \param  out         output, decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Decrypt(const ByteSeq& in, ByteSeq& out) = 0;

  /*! \brief  Check message authenticaton code (MAC).

      \param  in          input, data.
      \param  mac         input, MAC.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CheckMAC(const ByteSeq& in, const ByteSeq& mac) = 0;
};

/*! \brief  Crypto provider.
*/
class CryptoProvider {
public:
  virtual ~CryptoProvider() {
  }

  /*! \brief  Create hash calculator.

      \param  alg         input, hash algorithm.
      \param  calc        output, hash calculator.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateHashCalculator(const ByteSeq& alg, HashCalculator** calc) = 0;

  /*! \brief  Create public encryptor.

      \param  alg         input, public key algorithm.
      \param  key         input, (public) key.
      \param  enc         output, public encryptor.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreatePublicEncryptor(const ByteSeq& alg, const ByteSeq& key,
    PublicEncryptor** enc) = 0;

  /*! \brief  Create public decryptor.

      \param  alg         input, public key algorithm.
      \param  key         input, (public/private) key.
      \param  dec         output, public decryptor.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreatePublicDecryptor(const ByteSeq& alg, const ByteSeq& key,
    PublicDecryptor** dec) = 0;

  /*! \brief  Create public verifier.

      \param  alg         input, public key algorithm.
      \param  key         input, (public) key.
      \param  ver         output, public verifier.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreatePublicVerifier(const ByteSeq& alg, const ByteSeq& key,
    PublicVerifier** ver) = 0;

  /*! \brief  Create public signer.

      \param  alg         input, public key algorithm.
      \param  key         input, (public/private) key.
      \param  sig         output, public signer.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreatePublicSigner(const ByteSeq& alg, const ByteSeq& key,
    PublicSigner** sig) = 0;

  /*! \brief  Create symmetric operator.

      \param  alg         input, symmetric key algorithm.
      \param  key         input, symmetric key.
      \param  symm        output, symmetric operator.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateSymmetricOperator(const ByteSeq& alg, const ByteSeq& key,
    SymmetricOperator** symm) = 0;

  /*! \brief  Create symmetric operator which doesn't do any real
              encryption/decryption, just leaves data as it is.

      \param  symm        output, symmetric operator.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateSymmetricOperator(SymmetricOperator** symm) = 0;
};

/*! \brief  Dummy implementation of crypto provider.
*/
class DummyCryptoProvider: public CryptoProvider {
public:
  DummyCryptoProvider() {
  }

  virtual ~DummyCryptoProvider() {
  }

  /*! \brief  Create hash calculator.

      \param  alg         input, hash algorithm.
      \param  calc        output, hash calculator.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateHashCalculator(const ByteSeq& alg, HashCalculator** calc);

  /*! \brief  Create public encryptor.

      \param  alg         input, public key algorithm.
      \param  key         input, (public) key.
      \param  enc         output, public encryptor.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreatePublicEncryptor(const ByteSeq& alg, const ByteSeq& key,
    PublicEncryptor** enc);

  /*! \brief  Create public decryptor.

      \param  alg         input, public key algorithm.
      \param  key         input, (public/private) key.
      \param  dec         output, public decryptor.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreatePublicDecryptor(const ByteSeq& alg, const ByteSeq& key,
    PublicDecryptor** dec);

  /*! \brief  Create public verifier.

      \param  alg         input, public key algorithm.
      \param  key         input, (public) key.
      \param  ver         output, public verifier.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreatePublicVerifier(const ByteSeq& alg, const ByteSeq& key,
    PublicVerifier** ver);

  /*! \brief  Create public signer.

      \param  alg         input, public key algorithm.
      \param  key         input, (public/private) key.
      \param  sig         output, public signer.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreatePublicSigner(const ByteSeq& alg, const ByteSeq& key,
    PublicSigner** sig);

  /*! \brief  Create symmetric operator.

      \param  alg         input, symmetric key algorithm.
      \param  key         input, symmetric key.
      \param  symm        output, symmetric operator.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateSymmetricOperator(const ByteSeq& alg, const ByteSeq& key,
    SymmetricOperator** symm);

  /*! \brief  Create symmetric operator which doesn't do any real
              encryption/decryption, just leaves data as it is.

      \param  symm        output, symmetric operator.

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateSymmetricOperator(SymmetricOperator** symm);
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (CRYPTOPROVIDER_H)
