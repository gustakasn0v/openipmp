/**	\file OMAMPEG4SinfDRMEncryptor.h

	OMA MPEG4 DRM encryptor plugin with Sinf signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OMAMPEG4SINFDRMENCRYPTOR_H)
#define OMAMPEG4SINFDRMENCRYPTOR_H

#include "IOMADRMEncManager.h"
#include "IOMAMPEG4SinfDRMEncryptor.h"
#include "MPEG4DRMPluginException.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined OMAMPEG4SINFDRMENCRYPTOR_EXPORTS
#define OMAMPEG4SINFDRMENCRYPTOR_EXPORT __declspec(dllexport)
#else
#define OMAMPEG4SINFDRMENCRYPTOR_EXPORT __declspec(dllimport)
#endif // OMAMPEG4SINFDRMENCRYPTOR_EXPORTS
#elif defined (LINUX)
#define OMAMPEG4SINFDRMENCRYPTOR_EXPORT
#else
#define OMAMPEG4SINFDRMENCRYPTOR_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG4SinfDRMPlugin namespace. All MPEG4 Sinf DRM plugin code resides in it.
namespace MPEG4SinfDRMPlugin {

/*! \brief  Encrypts MP4 data using AES128CBC encryptor according to OMA
            specifications with Sinf signalling.

    Encrypts samples and adds information for decryption to MP4 stream.
*/
class AES128CBCOMAMPEG4SinfDRMEncryptor: public IOMAMPEG4SinfDRMEncryptor {
public:
  /*! \brief  Constructor.

      Mandatory tags in the XML file are:
       - ROOT.RightsHostURL

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <RightsHostURL>localhost:8080</RightsHostURL>
       <SilentHeader>Silent:on-demand;http://www.silent.com/</SilentHeader>
       <PreviewHeader>Preview:instant;http://www.preview.com/</PreviewHeader>
       <ContentURLHeader>ContentURL:http://www.content.com/</ContentURLHeader>
       <ContentVersionHeader>ContentVersion:original-content-identifier:1.1</ContentVersionHeader>
       <ContentLocationHeader>Content-Location:http://www.content.com/</ContentLocationHeader>
      </ROOT>

      \endverbatim

      \param      drm             input, DRM manager.
      \param      conID           input-output, content identifier.
      \param      xmlDoc          input, XML document.
      \param      logger          input-output, message logger.

      If constructor fails, it throws MPEG4DRMPluginException.
  */
  OMAMPEG4SINFDRMENCRYPTOR_EXPORT AES128CBCOMAMPEG4SinfDRMEncryptor(IOMADRMEncManager*
      drm, std::string& conID, IXMLElement* xmlDoc, DRMLogger& logger);

  virtual OMAMPEG4SINFDRMENCRYPTOR_EXPORT ~AES128CBCOMAMPEG4SinfDRMEncryptor();

  /*! \brief  Encrypt sample sampleBuffer.
  
      Returns encrypted sample in encSampleData.

      \param    sampleBuffer      input, sample to be encrypted.
      \param    sampleSize        input, size of input sample.
      \param    encSampleData     output, encrypted sample.
      \param    encSampleLen      output, size of encrypted sample.

      \return Boolean indicating success or failure.
  */
  virtual OMAMPEG4SINFDRMENCRYPTOR_EXPORT bool EncryptSample(ByteT* sampleBuffer,
    UInt32T sampleSize, ByteT** encSampleData, UInt32T* encSampleLen);

  /*! \brief  Add drm information into sinf atom.
  
      Caller must take care that given sinf atom really coresponds to sample 
      description atom which refers to encrypted samples.

      \param    originalFormat  input, 4CC code of the original data format.
      \param    sinf            input-output, sinf atom where to add drm information.

      \return Boolean indicating success or failure.
  */
  virtual OMAMPEG4SINFDRMENCRYPTOR_EXPORT bool Finish(UInt32T originalFormat,
    IMP4SinfAtom* sinf);

private:
  AES128CBCEncryptor* encryptor;
  std::string contentID;
  std::string rightsHost;
  std::string silentHdr;
  std::string previewHdr;
  std::string contentURLHdr;
  std::string contentVerHdr;
  std::string contentLocHdr;
  UInt64T pTextLen;
  DRMLogger& encLogger;
};

/*! \brief  Encrypts MP4 data using AES128CTR encryptor according to OMA
            specifications with Sinf signalling.

    Encrypts samples and adds information for decryption to MP4 stream.
*/
class AES128CTROMAMPEG4SinfDRMEncryptor: public IOMAMPEG4SinfDRMEncryptor {
public:
  /*! \brief  Constructor.

      Mandatory tags in the XML file are:
       - ROOT.RightsHostURL

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <RightsHostURL>localhost:8080</RightsHostURL>
       <SilentHeader>Silent:on-demand;http://www.silent.com/</SilentHeader>
       <PreviewHeader>Preview:instant;http://www.preview.com/</PreviewHeader>
       <ContentURLHeader>ContentURL:http://www.content.com/</ContentURLHeader>
       <ContentVersionHeader>ContentVersion:original-content-identifier:1.1</ContentVersionHeader>
       <ContentLocationHeader>Content-Location:http://www.content.com/</ContentLocationHeader>
      </ROOT>

      \endverbatim

      \param      drm             input, DRM manager.
      \param      conID           input, content identifier.
      \param      xmlDoc          input, XML document.
      \param      logger          input-output, message logger.

      If constructor fails, it throws MPEG4DRMPluginException.
  */
  OMAMPEG4SINFDRMENCRYPTOR_EXPORT AES128CTROMAMPEG4SinfDRMEncryptor(IOMADRMEncManager*
      drm, std::string& conID, IXMLElement* xmlDoc, DRMLogger& logger);

  virtual OMAMPEG4SINFDRMENCRYPTOR_EXPORT ~AES128CTROMAMPEG4SinfDRMEncryptor();

  /*! \brief  Encrypt sample sampleBuffer.
  
      Returns encrypted sample in encSampleData.

      \param    sampleBuffer      input, sample to be encrypted.
      \param    sampleSize        input, size of input sample.
      \param    encSampleData     output, encrypted sample.
      \param    encSampleLen      output, size of encrypted sample.

      \return Boolean indicating success or failure.
  */
  virtual OMAMPEG4SINFDRMENCRYPTOR_EXPORT bool EncryptSample(ByteT* sampleBuffer,
    UInt32T sampleSize, ByteT** encSampleData, UInt32T* encSampleLen);

  /*! \brief  Add drm information into sinf atom.
  
      Caller must take care that given sinf atom really coresponds to sample
      description atom which refers to encrypted samples.

      \param    originalFormat  input, 4CC code of the original data format.
      \param    sinf            input-output, sinf atom where to add drm information.

      \return Boolean indicating success or failure.
  */
  virtual OMAMPEG4SINFDRMENCRYPTOR_EXPORT bool Finish(UInt32T originalFormat,
    IMP4SinfAtom* sinf);

private:
  AES128CTREncryptor* encryptor;
  std::string contentID;
  std::string rightsHost;
  std::string silentHdr;
  std::string previewHdr;
  std::string contentURLHdr;
  std::string contentVerHdr;
  std::string contentLocHdr;
  UInt64T pTextLen;
  DRMLogger& encLogger;
};

} // namespace MPEG4SinfDRMPlugin

} // namespace DRMPlugin

#endif // !defined (OMAMPEG4SINFDRMENCRYPTOR_H)
