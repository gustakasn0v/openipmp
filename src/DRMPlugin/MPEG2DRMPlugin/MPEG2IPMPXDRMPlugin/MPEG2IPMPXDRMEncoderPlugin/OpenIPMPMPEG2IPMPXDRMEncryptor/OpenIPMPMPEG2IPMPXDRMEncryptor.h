/**	\file OpenIPMPMPEG2IPMPXDRMEncryptor.h

	OpenIPMP MPEG2 DRM encryptor with IPMPX signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENIPMPMPEG2IPMPXDRMENCRYPTOR_H)
#define OPENIPMPMPEG2IPMPXDRMENCRYPTOR_H

#include "BasicTypes.h"
#include "IIPMPDescriptor.h"
#include "MPEG2IPMPXDRMEncryptor.h"
#include <string>
#include "IXMLDocument.h"
#include "IOpenIPMPDRMEncManager.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined OPENIPMPMPEG2IPMPXDRMENCRYPTOR_EXPORTS
#define OPENIPMPMPEG2IPMPXDRMENCRYPTOR_EXPORT __declspec(dllexport)
#else
#define OPENIPMPMPEG2IPMPXDRMENCRYPTOR_EXPORT __declspec(dllimport)
#endif // OPENIPMPMPEG2IPMPXDRMENCRYPTOR_EXPORTS
#elif defined (LINUX)
#define OPENIPMPMPEG2IPMPXDRMENCRYPTOR_EXPORT
#else
#define OPENIPMPMPEG2IPMPXDRMENCRYPTOR_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  OpenIPMP MPEG2 DRM encryptor with AES128CTR encryption.

    Encryptor that will protect MPEG2 data using openIPMP specifications.
*/
class AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor: public MPEG2IPMPXDRMEncryptor {
public:
  /*! \brief Constructor.

      See the specific DRM manager documentation for the correct format
      of the XML document.

      For creating encryptor, mandatory tags in the XML file are:
       - ROOT.RightsHostURL

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <RightsHostURL>localhost:8080</RightsHostURL>
      </ROOT>

      \endverbatim

      \param    drm             DRM manager.
      \param    conID           content identifier.
      \param    xmlDoc          XML document containing necessary information for
                                creating encryptor.
      \param    logger          message logger.

      \returns  If fails, throws MPEG2DRMPluginException.
  */
  OPENIPMPMPEG2IPMPXDRMENCRYPTOR_EXPORT AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor(
    IOpenIPMPDRMEncManager* drm, std::string& conID, IXMLElement* xmlDoc,
    DRMLogger& logger);

  virtual ~AES128CTROpenIPMPMPEG2IPMPXDRMEncryptor();

  /*! \brief  Encrypt data.

      User of IMPEG2IPMPXDRMEncryptor must decide which data will be encrypted
      (all elementary streams, only some, etc.), and once the IMPEG2IPMPXDRMEncryptor
      is created, call this function subsequently to encrypt that data.

      \param  plainData       input, plaintext data to be encrypted.
      \param  encryptedData   output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool EncryptData(const ByteSeq& plainData, ByteSeq& encryptedData);

  /*! \brief  Add DRM information to IPMP descriptor.

      User of IMPEG2IPMPXDRMEncryptor must take care of the correct placement
      of the IPMP descriptor. If all elementary streams are protected then
      the IPMP descriptor must be put in the in the main program map loop.
      If only some elementary streams are protected then the IPMP descriptor
      must be put in the program map in the elementary stream loop for the
      protected streams.

      \param  descriptor      input-output, IPMP descriptor to be updated.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddDRMInfo(IIPMPDescriptor* descriptor);

  /*! \brief  Create and encode control info class.

      Control info class is this encryptor's (tool's) description, used for
      later correct initialization.

      \param  cInfo           output, encoded control info class.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateControlInfo(ByteSeq& cInfo);

private:
  AES128CTREncryptor* encryptor;
  std::string contentID;
  std::string rightsHost;
  DRMLogger& encLogger;
};

/*! \brief  OpenIPMP MPEG2 DRM encryptor with blowfish encryption.

    Encryptor that will protect MPEG2 data using openIPMP specifications.
*/
class BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor: public MPEG2IPMPXDRMEncryptor {
public:
  /*! \brief Constructor.

      See the specific DRM manager documentation for the correct format
      of the XML document.

      For creating encryptor, mandatory tags in the XML file are:
       - ROOT.RightsHostURL

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <RightsHostURL>localhost:8080</RightsHostURL>
      </ROOT>

      \endverbatim

      \param    drm             DRM manager.
      \param    conID           content identifier.
      \param    xmlDoc          XML document containing necessary information for
                                creating encryptor.
      \param    logger          message logger.

      \returns  If fails, throws MPEG2DRMPluginException.
  */
  OPENIPMPMPEG2IPMPXDRMENCRYPTOR_EXPORT BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor(
    IOpenIPMPDRMEncManager* drm, std::string& conID, IXMLElement* xmlDoc,
    DRMLogger& logger);

  virtual ~BlowfishOpenIPMPMPEG2IPMPXDRMEncryptor();

  /*! \brief  Encrypt data.

      User of IMPEG2IPMPXDRMEncryptor must decide which data will be encrypted
      (all elementary streams, only some, etc.), and once the IMPEG2IPMPXDRMEncryptor
      is created, call this function subsequently to encrypt that data.

      \param  plainData       input, plaintext data to be encrypted.
      \param  encryptedData   output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool EncryptData(const ByteSeq& plainData, ByteSeq& encryptedData);

  /*! \brief  Add DRM information to IPMP descriptor.

      User of IMPEG2IPMPXDRMEncryptor must take care of the correct placement
      of the IPMP descriptor. If all elementary streams are protected then
      the IPMP descriptor must be put in the in the main program map loop.
      If only some elementary streams are protected then the IPMP descriptor
      must be put in the program map in the elementary stream loop for the
      protected streams.

      \param  descriptor      input-output, IPMP descriptor to be updated.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddDRMInfo(IIPMPDescriptor* descriptor);

  /*! \brief  Create and encode control info class.

      Control info class is this encryptor's (tool's) description, used for
      later correct initialization.

      \param  cInfo           output, encoded control info class.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateControlInfo(ByteSeq& cInfo);

private:
  BlowfishEncryptor* encryptor;
  std::string contentID;
  std::string rightsHost;
  DRMLogger& encLogger;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (OPENIPMPMPEG2IPMPXDRMENCRYPTOR_H)
