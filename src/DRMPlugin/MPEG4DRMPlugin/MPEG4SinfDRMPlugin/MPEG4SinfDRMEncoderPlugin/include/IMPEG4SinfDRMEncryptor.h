/**	\file IMPEG4SinfDRMEncryptor.h

	Interfaces for MPEG4 DRM encryptor plugin with Sinf signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IMPEG4SINFDRMENCRYPTOR_H)
#define IMPEG4SINFDRMENCRYPTOR_H

#include "IMPEG4DRMAtom.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG4SinfDRMPlugin namespace. All MPEG4 Sinf DRM plugin code resides in it.
namespace MPEG4SinfDRMPlugin {

/*! \brief Encrypts MP4 data with Sinf signalling.

    It is used to encrypt track samples, and add neccessary information
    for decryption.
*/
class IMPEG4SinfDRMEncryptor {
public:
  virtual ~IMPEG4SinfDRMEncryptor() {};

  /*! \brief  Encrypt sample sampleBuffer.
  
      Returns encrypted sample in encSampleData.

      \param    sampleBuffer      input, sample to be encrypted.
      \param    sampleSize        input, size of input sample.
      \param    encSampleData     output, encrypted sample.
      \param    encSampleLen      output, size of encrypted sample.

      \return Boolean indicating success or failure.
  */
  virtual bool EncryptSample(ByteT* sampleBuffer, UInt32T sampleSize,
    ByteT** encSampleData, UInt32T* encSampleLen) = 0;

  /*! \brief  Add drm information into sinf atom.
  
      Caller must take care that given sinf atom really coresponds to
      sample description atom which refers to encrypted samples.

      \param    originalFormat  input, 4CC code of the original data format.
      \param    sinf            input-output, sinf atom where to add drm information.

      \return Boolean indicating success or failure.
  */
  virtual bool Finish(UInt32T originalFormat, IMP4SinfAtom* sinf) = 0;
};

} // namespace MPEG4SinfDRMPlugin

} // namespace DRMPlugin

#endif // !defined (IMPEG4SINFDRMENCRYPTOR_H)
