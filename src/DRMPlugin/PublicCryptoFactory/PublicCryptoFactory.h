/**	\file PublicCryptoFactory.h

	Public crypto management.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (PUBLICCRYPTOFACTORY_H)
#define PUBLICCRYPTOFACTORY_H

#include "IPublicCrypto.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined PUBLICCRYPTOFACTORY_EXPORTS
#define PUBLICCRYPTOFACTORY_EXPORT __declspec(dllexport)
#else
#define PUBLICCRYPTOFACTORY_EXPORT __declspec(dllimport)
#endif // PUBLICCRYPTOFACTORY_EXPORTS
#elif defined (LINUX)
#define PUBLICCRYPTOFACTORY_EXPORT
#else
#define PUBLICCRYPTOFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Public crypto manager.
*/
class PublicCryptoFactory {
public:
  /*! \brief  Get new MD5 hasher.

      \param  logger	input, message logger.

      \returns  New MD5 hasher. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IHasher* GetMD5Hasher(DRMLogger& logger);

  /*! \brief  Get new SHA1 hasher.

      \param  logger	input, message logger.

      \returns  New SHA1 hasher. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IHasher* GetSHA1Hasher(DRMLogger& logger);

  /*! \brief  Parse public key decryptor from key data.

      \param  data        input, data.
      \param  datalen     input, data length.
      \param  logger	input, message logger.

      \returns  New public key decryptor. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicDecryptor* ParsePublicDecryptorFromKeyData(ByteT* data, unsigned int datalen, DRMLogger& logger);

  /*! \brief  Parse public key signer from key data.

      \param  data        input, data.
      \param  datalen     input, data length.
      \param  logger	input, message logger.

      \returns  New public key signer. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicSigner* ParsePublicSignerFromKeyData(ByteT* data, unsigned int datalen, DRMLogger& logger);

  /*! \brief  Parse public key decryptor and signer from key data.

      \param  data        input, data.
      \param  datalen     input, data length.
      \param  logger	input, message logger.

      \returns  New public key decryptor and signer. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicDecryptorSigner* ParsePublicDecryptorSignerFromKeyData(ByteT* data, unsigned int datalen, DRMLogger& logger);

  /*! \brief  Parse public key decryptor from a key file.

      \param  fname       input, file name.
      \param  logger	input, message logger.

      \returns  New public key decryptor. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicDecryptor* ParsePublicDecryptorFromKeyFile(const std::string& fname, DRMLogger& logger);

  /*! \brief  Parse public key decryptor and signer from a key file.

      \param  fname       input, file name.
      \param  logger	input, message logger.

      \returns  New public key signer. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicSigner* ParsePublicSignerFromKeyFile(const std::string& fname, DRMLogger& logger);

  /*! \brief  Parse public key decryptor and signer from a key file.

      \param  fname       input, file name.
      \param  logger	input, message logger.

      \returns  New public key decryptor and signer. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicDecryptorSigner* ParsePublicDecryptorSignerFromKeyFile(const std::string& fname, DRMLogger& logger);

  /*! \brief  Get new certificate verifier.

      \param  logger	input, message logger.

      \returns  New certificate verifier. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT ICertVerifier* GetCertificateVerifier(DRMLogger& logger);

  /*! \brief  Parse public key encryptor certificate from certificate data.

      \param  data        input, data.
      \param  datalen     input, data length.
      \param  logger	input, message logger.

      \returns  New public key encryptor certificate. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicEncryptorCertificate* ParsePublicEncryptorCertificateFromData(ByteT* data, unsigned int datalen, DRMLogger& logger);

  /*! \brief  Parse public key encryptor certificate from a certificate file.

      \param  fname       input, file name.
      \param  logger	input, message logger.

      \returns  New public key encryptor certificate. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicEncryptorCertificate* ParsePublicEncryptorCertificateFromFile(const std::string& fname, DRMLogger& logger);

  /*! \brief  Parse public key verifier certificate from certificate data.

      \param  data        input, data.
      \param  datalen     input, data length.
      \param  logger	input, message logger.

      \returns  New public key verifier certificate. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicVerifierCertificate* ParsePublicVerifierCertificateFromData(ByteT* data, unsigned int datalen, DRMLogger& logger);

  /*! \brief  Parse public key verifier certificate from a certificate file.

      \param  fname       input, file name.
      \param  logger	input, message logger.

      \returns  New public key verifier certificate. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicVerifierCertificate* ParsePublicVerifierCertificateFromFile(const std::string& fname, DRMLogger& logger);

  /*! \brief  Parse public key encryptor and verifier certificate from certificate data.

      \param  data        input, data.
      \param  datalen     input, data length.
      \param  logger	input, message logger.

      \returns  New public key encryptor and verifier certificate. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicEncryptorVerifierCertificate* ParsePublicEncryptorVerifierCertificateFromData(ByteT* data, unsigned int datalen, DRMLogger& logger);

  /*! \brief  Parse public key encryptor and verifier certificate from a certificate file.

      \param  fname       input, file name.
      \param  logger	input, message logger.

      \returns  New public key encryptor and verifier certificate. If fails, 0.
  */
  static PUBLICCRYPTOFACTORY_EXPORT IPublicEncryptorVerifierCertificate* ParsePublicEncryptorVerifierCertificateFromFile(const std::string& fname, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (PUBLICCRYPTOFACTORY_H)
