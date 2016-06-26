/**	\file IMPEG2IPMPXDRMEncryptor.h

	Interfaces for MPEG2 DRM encryptor with IPMPX signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IMPEG2IPMPXDRMENCRYPTOR_H)
#define IMPEG2IPMPXDRMENCRYPTOR_H

#include "BasicTypes.h"
#include "IIPMPDescriptor.h"
#include <vector>
#include "MPEG2DRMPluginException.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  MPEG2 DRM encryptor with IPMPX signalling.

    Encryptor class that adds DRM information to MPEG2 stream, and encrypts
    stream data.
*/
class IMPEG2IPMPXDRMEncryptor {
public:
  virtual ~IMPEG2IPMPXDRMEncryptor() {};

  /*! \brief  Encrypt data.

      User of IMPEG2IPMPXDRMEncryptor must decide which data will be encrypted
      (all elementary streams, only some, etc.), and once the IMPEG2IPMPXDRMEncryptor
      is created, call this function subsequently to encrypt that data.

      \param  plainData       input, plaintext data to be encrypted.
      \param  encryptedData   output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool EncryptData(const ByteSeq& plainData, ByteSeq& encryptedData) = 0;

  /*! \brief  Add DRM information to IPMP descriptor.

      User of IMPEGIPMPX2DRMEncryptor must take care of the correct placement
      of the IPMP descriptor. If all elementary streams are protected then
      the IPMP descriptor must be put in the in the main program map loop.
      If only some elementary streams are protected then the IPMP descriptor
      must be put in the program map in the elementary stream loop for the
      protected streams.

      \param  descriptor      input-output, IPMP descriptor to be updated.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddDRMInfo(IIPMPDescriptor* descriptor) = 0;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(IMPEG2IPMPXDRMENCRYPTOR_H)
