/**	\file SigCertContainer.h

    \ingroup drmplayer
    \ingroup drmencoder

	Test implementation of signature and certificate containers.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (SIGCERTCONTAINER_H)
#define SIGCERTCONTAINER_H

#include "BasicTypes.h"
#include <vector>

#include "ISigCertContainer.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief  Certificate container.

    Certificate container consisting of certificate type and certificate data.
*/
class CertContainer: public ICertContainer {
public:
  /*! \brief  Constructor.
  */
  CertContainer(): certType(0), certificate() {
  }

  /*! \brief  Constructor.

      \param  type      certificate type.
      \param  cert      certificate.
  */
  CertContainer(const ByteT& type, const ByteSeq& cert): certType(type),
    certificate(cert) {
  }

  virtual ~CertContainer() {
  }

  /*! \brief  Get certificate type.

      Certificate type value is assigned by registration authority.

      \returns  Number representing certificate type.
  */
  virtual const ByteT& GetCertType() const {
    return certType;
  }

  /*! \brief  Set certificate type.

      If previous certificate type existed, it must be replaced with the one given.

      \param  type     input, certificate type to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCertType(const ByteT& type) {
    certType = type;
    return true;
  }

  /*! \brief  Get certificate.

      \returns  Certificate.
  */
  virtual const ByteSeq& GetCertificate() const {
    return certificate;
  }

  /*! \brief  Set certificate.

      If previous certificate existed, it must be replaced with the one given.

      \param  cert     input, certificate to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCertificate(const ByteSeq& cert) {
    certificate = cert;
    return true;
  }

private:
  ByteT certType;
  ByteSeq certificate;
};

/*!	\brief Signature and certificate container.

    Container consisting of signature data and certificate containers.
*/
class SigCertContainer: public ISigCertContainer {
public:
  /*! \brief  Constructor.
  */
  SigCertContainer(): signature(), certificates(), verifyID() {
  }

  /*! \brief  Constructor.

      \param  sig       signature.
      \param  certs     certificate containers.
      \param  verify    verifying tool identifier.
  */
  SigCertContainer(const ByteSeq& sig, const std::vector<ICertContainer*>& certs,
    const Bit128T& verify): signature(sig), certificates(certs), verifyID(verify) {
  }

  virtual ~SigCertContainer() {
    for (unsigned int i = 0; i < certificates.size(); i++) {
      delete certificates[i];
    }
    certificates.clear();
  }

  /*! \brief  Get signature.

      \returns  Signature.
  */
  virtual const ByteSeq& GetSignature() const {
    return signature;
  }

  /*! \brief  Set signature.

      If previous signature existed, it must be replaced with the one given.

      \param  sig     input, signature to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetSignature(const ByteSeq& sig) {
    signature = sig;
    return true;
  }

  /*! \brief  Get certificate containers contained.

      \returns  Vector of certificate containers.
  */
  virtual const std::vector<ICertContainer*>& GetCertContainers() const {
    return certificates;
  }

  /*! \brief  Create new certificate container and add it to certificate
              containers contained.

      \param  container     output, newly created certificate container pointer
                            (if successful).

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateCertContainer(ICertContainer** container) {
    *container = new CertContainer();
    certificates.push_back(*container);
    return true;
  }

  /*! \brief  Get verifying tool identifier.

      Verifying tool identifier represents the tool for verification of
      certificates. Value 0 indicates the device.

      \returns  Verifying tool identifier.
  */
  virtual const Bit128T& GetVerifyingToolID() const {
    return verifyID;
  }

  /*! \brief  Set verifying tool identifier.

      If previous verifying tool identifier existed, it must be replaced with
      the one given.

      \param  verify     input, verifying tool identifier to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetVerifyingToolID(const Bit128T& verify) {
    verifyID = verify;
    return true;
  }

private:
  ByteSeq signature;
  std::vector<ICertContainer*> certificates;
  Bit128T verifyID;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(SIGCERTCONTAINER_H)
