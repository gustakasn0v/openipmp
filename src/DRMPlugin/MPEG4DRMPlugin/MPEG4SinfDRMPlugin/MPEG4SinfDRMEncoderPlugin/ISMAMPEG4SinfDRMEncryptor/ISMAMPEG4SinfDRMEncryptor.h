/**	\file ISMAMPEG4SinfDRMEncryptor.h

	ISMA MPEG4 DRM encryptor plugin with Sinf signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (ISMAMPEG4SINFDRMENCRYPTOR_H)
#define ISMAMPEG4SINFDRMENCRYPTOR_H

#include "IISMADRMEncManager.h"
#include "IISMAMPEG4SinfDRMEncryptor.h"
#include "MPEG4DRMPluginException.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined ISMAMPEG4SINFDRMENCRYPTOR_EXPORTS
#define ISMAMPEG4SINFDRMENCRYPTOR_EXPORT __declspec(dllexport)
#else
#define ISMAMPEG4SINFDRMENCRYPTOR_EXPORT __declspec(dllimport)
#endif // ISMAMPEG4SINFDRMENCRYPTOR_EXPORTS
#elif defined (LINUX)
#define ISMAMPEG4SINFDRMENCRYPTOR_EXPORT
#else
#define ISMAMPEG4SINFDRMENCRYPTOR_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG4SinfDRMPlugin namespace. All MPEG4 Sinf DRM plugin code resides in it.
namespace MPEG4SinfDRMPlugin {

/*! \brief  Encrypts MP4 data using AES128ICM encryptor according to ISMA
            specifications with Sinf signalling.

    Encrypts samples and adds information for decryption to MP4 stream.
*/
class AES128ICMISMAMPEG4SinfDRMEncryptor: public IISMAMPEG4SinfDRMEncryptor {
public:
  /*! \brief  Constructor.

      Mandatory tags in the XML file are:
       - ROOT.RightsHostURL

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <RightsHostURL>localhost:8080</RightsHostURL>
      </ROOT>

      \endverbatim

      \param      drm             input, DRM manager.
      \param      conID           input-output, content identifier.
      \param      xmlDoc          input, XML document.
      \param      logger          input-output, message logger.

      If constructor fails, it throws MPEG4DRMPluginException.
  */
  ISMAMPEG4SINFDRMENCRYPTOR_EXPORT AES128ICMISMAMPEG4SinfDRMEncryptor(
      IISMADRMEncManager* drm, std::string& conID, IXMLElement* xmlDoc,
      DRMLogger& logger);

  virtual ISMAMPEG4SINFDRMENCRYPTOR_EXPORT ~AES128ICMISMAMPEG4SinfDRMEncryptor();

  /*! \brief  Encrypt sample sampleBuffer.
  
      Returns encrypted sample in encSampleData.

      \param    sampleBuffer      input, sample to be encrypted.
      \param    sampleSize        input, size of input sample.
      \param    encSampleData     output, encrypted sample.
      \param    encSampleLen      output, size of encrypted sample.

      \return Boolean indicating success or failure.
  */
  virtual ISMAMPEG4SINFDRMENCRYPTOR_EXPORT bool EncryptSample(ByteT* sampleBuffer,
    UInt32T sampleSize, ByteT** encSampleData, UInt32T* encSampleLen);

  /*! \brief  Add drm information into sinf atom.
  
      Caller must take care that given sinf atom really coresponds to sample
      description atom which refers to encrypted samples.

      \param    originalFormat  input, 4CC code of the original data format.
      \param    sinf            input-output, sinf atom where to add drm information.

      \return Boolean indicating success or failure.
  */
  virtual ISMAMPEG4SINFDRMENCRYPTOR_EXPORT bool Finish(UInt32T originalFormat,
    IMP4SinfAtom* sinf);

private:
  AES128ICMEncryptor* encryptor;
  std::string contentID;
  std::string rightsHost;
  DRMLogger& encLogger;
};

} // namespace MPEG4SinfDRMPlugin

} // namespace DRMPlugin

#endif // !defined (ISMAMPEG4SINFDRMENCRYPTOR_H)
