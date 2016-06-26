/**	\file ISigCertContainer.h

	Interfaces for signature and certificate containers.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (ISIGCERTCONTAINER_H)
#define ISIGCERTCONTAINER_H

#include "BasicTypes.h"
#include <vector>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief  Certificate container.

    Certificate container consisting of certificate type and certificate data.
*/
class ICertContainer {
public:
  virtual ~ICertContainer() {}

  /*! \brief  Get certificate type.

      Certificate type value is assigned by registration authority.

      \returns  Number representing certificate type.
  */
  virtual const ByteT& GetCertType() const = 0;

  /*! \brief  Set certificate type.

      If previous certificate type existed, it must be replaced with the one given.

      \param  type     input, certificate type to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCertType(const ByteT& type) = 0;

  /*! \brief  Get certificate.

      \returns  Certificate.
  */
  virtual const ByteSeq& GetCertificate() const = 0;

  /*! \brief  Set certificate.

      If previous certificate existed, it must be replaced with the one given.

      \param  cert     input, certificate to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCertificate(const ByteSeq& cert) = 0;

  /*! \brief  Encode as a byte array.

      This function is used for calculating CRC codes.

      \param  encoded     output, encoded data.

      \returns  Boolean indicating success or failure. If failed, log
                will contain error description.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const {
    encoded = ByteSeq(GetCertType()) + GetCertificate().MPEG2Encode();
    return true;
  }
};

/*!	\brief Signature and certificate container.

    Container consisting of signature data and certificate containers.
*/
class ISigCertContainer {
public:
  virtual ~ISigCertContainer() {}

  /*! \brief  Get signature.

      \returns  Signature.
  */
  virtual const ByteSeq& GetSignature() const = 0;

  /*! \brief  Set signature.

      If previous signature existed, it must be replaced with the one given.

      \param  sig     input, signature to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetSignature(const ByteSeq& sig) = 0;

  /*! \brief  Get certificate containers contained.

      \returns  Vector of certificate containers.
  */
  virtual const std::vector<ICertContainer*>& GetCertContainers() const = 0;

  /*! \brief  Create new certificate container and add it to certificate
              containers contained.

      \param  container     output, newly created certificate container pointer
                            (if successful).

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateCertContainer(ICertContainer** container) = 0;

  /*! \brief  Get verifying tool identifier.

      Verifying tool identifier represents the tool for verification of
      certificates. Value 0 indicates the device.

      \returns  Verifying tool identifier.
  */
  virtual const Bit128T& GetVerifyingToolID() const = 0;

  /*! \brief  Set verifying tool identifier.

      If previous verifying tool identifier existed, it must be replaced with
      the one given.

      \param  verify     input, verifying tool identifier to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetVerifyingToolID(const Bit128T& verify) = 0;

  /*! \brief  Encode as a byte array.

      This function is used for calculating CRC codes.

      \param  encoded     output, encoded data.

      \returns  Boolean indicating success or failure. If failed, log
                will contain error description.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const {
    if (GetCertContainers().size() >= (1 << 8)) {
      /*  This shouldn't happen. It means that we have more certificate
          containers than allowed (cause number of certificate containers
          must be packed as a byte).
      */
      return false;
    }
    ByteT nCerts = (ByteT)GetCertContainers().size();
    encoded = GetSignature().MPEG2Encode() + ByteSeq(nCerts);
    std::vector<ICertContainer*>::const_iterator iter = GetCertContainers().begin();
    while (iter != GetCertContainers().end()) {
      ByteSeq tmp;
      if ((*iter)->MPEG2Encode(tmp) == false) {
        return false;
      }
      encoded += tmp;
      iter++;
    }
    encoded += ByteSeq(GetVerifyingToolID());
    return true;
  }
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(ISIGCERTCONTAINER_H)
