/**
    \defgroup drmencoder DRM encoder documentation.
*/
/**	\file sample_drm_encoder.h

    \ingroup drmencoder

	Example of use of DRM plugins in an encode case.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

/*!  \brief Protect track according to OMA DRM specifications.

    Given a source track in a source file, make an encrypted copy of 
    the track in the destination file, including sample encryption, using
    OMA DRM specifications.

    \param    logger          message logger.
    \param    xmlDoc          XML document, containing necessary information for
                              encoding track.
    \param    fName           name of the source mp4 file to be protected.
    \param    srcTrackId      track ID of the source track that is to be protected.
    \param    eMethod         encryption method (AES128CBC or AES128CTR).


    We emphasize that mandatory tags in the XML document are dependent on the DRM
    and content info managers used.
    xmlDoc can be created from an input file, or however it suits a user of DRM
    plugins. A user must only take care of providing necessary tags in the XML
    document, as indicated by documentation for a specific ContentInfoManager and
    IOMADRMEncManager.

    Here follows an example of the code for this function.

    \code

    #include "ContentInfoManagerFactory.h"
    #include "OMADRMEncManagerFactory.h"
    #include "OMAMPEG4SinfDRMEncryptor.h"
    #include "IXMLDocument.h"
    #include "DRMLogger.h"
    #include "ICipher.h"
    #include <string>

    using namespace DRMPlugin;
    using namespace MPEG4SinfDRMPlugin;

    bool OMAMP4EncryptTrack(DRMLogger& logger, IXMLElement* xmlDoc,
        const std::string& fName, const unsigned int srcTrackId,
        EncMethod eMethod) {

      ContentInfoManager* infoManager = 0;
      IOMADRMEncManager* drmManager = 0;
      IOMAMPEG4SinfDRMEncryptor* encryptor = 0;

      // Create all necessary data for DRM protection.
      try {
        //  Create content info manager which will assign unique content ID to
        //  the protected content.
        infoManager = ContentInfoManagerFactory::GetContentInfoManager(
          OPENIPMPDOIINFOMANAGER, xmlDoc, logger);
        if (infoManager == 0) {
          return false;
        }

        //  Create a simple basic identifier for the track/file which is to be
        //  encrypted. A real content identifier will be created using this data.
        //  Here we just use the file name and track identifier.
        std::string title = fName + ".track" + IntToString(srcTrackId);
        DRMPlugin::IXMLElement* elem = xmlDoc->GetChildElement("ContentTitle");
        if (elem == 0) {
          delete infoManager;
          return false;
        }
        if (elem->SetStrValue(title) == false) {
          delete infoManager;
          return false;
        }

        //  Create content info with unique content ID for the protected content.
        std::string info;
        if (infoManager->GetContentInfo(xmlDoc, info, logger) == false) {
          delete infoManager;
          return false;
        }
        delete infoManager; infoManager = 0;

        //  Create DRM manager which will store encryption keys with respect to
        //  the content ID of the protected content and create DRM encryptor.
        drmManager = OMADRMEncManagerFactory::GetOMADRMEncManager(xmlDoc, logger);
        if (drmManager == 0) {
          return false;
        }

        //  Create DRM encryptor that will protect the content.
        if (eMethod == EncMethod(AES128CBC)) {
          encryptor = new AES128CBCOMAMPEG4SinfDRMEncryptor(drmManager, info,
            xmlDoc, logger);
        } else if (eMethod == EncMethod(AES128CTR)) {
          encryptor = new AES128CTROMAMPEG4SinfDRMEncryptor(drmManager, info,
            xmlDoc, logger);
        } else {
          delete drmManager;
          logger.UpdateLog("OMAMP4EncryptTrack: wrong encryption method.");
          return false;
        }

        //  Add (if any) licenses contained in the XML document.
        drmManager->AddLicense(info, xmlDoc, logger);
        delete drmManager; drmManager = 0;
      }
      catch (...) {
        if (infoManager != 0) delete infoManager;
        if (drmManager != 0) delete drmManager;
        if (encryptor != 0) delete encryptor;
        return false;
      }

      //  Create new track, including protected sample entry atoms ("enca", "encv")
      //  with "sinf" children atom, and all contained fields in it (see the
      //  description of those atoms for details).
      CreateTrack();

      ByteT* sample = NULL; 
      UInt32T sampleLength = 0;
      ByteT* encSample = NULL;
      UInt32T encSampleLength = 0;

      //  Read samples and call encryptor to encrypt them, then write encrypted samples
      //  to output file.
      while (ReadSample(&sample, &sampleLength)) {
        if (encryptor->EncryptSample(sample, sampleLength, &encSample, &encSampleLength) == false) {
          delete encryptor;
          return false;
        }
        WriteSample(encSample, encSampleLength);
        free(sample);
        free(encSample);
      }

      //  Get "sinf" atom corresponding to the protected samples (track).
      IMP4SinfAtom* sinf = GetSinfAtom();
      //  Get 4CC code corresponding to the protected samples (track). For video
      //  samples this will be (UInt32T)("mp4v"), and for audio samples
      //  (UInt32T)("mp4a").
      UInt32T otype = GetOriginalType();

      //  Add DRM information to "sinf" atom.
      if (encryptor->Finish(otype, sinf) == false) {
        delete encryptor;
        return false;
      }

      delete encryptor;

      return true;
    }

    \endcode
*/
bool OMAMP4EncryptTrack(DRMLogger& logger, IXMLElement* xmlDoc, const std::string&
  fName, const unsigned int srcTrackId, EncMethod eMethod);

/*!  \brief Protect track according to ISMA DRM specifications.

    Given a source track in a source file, make an encrypted copy of 
    the track in the destination file, including sample encryption, using
    ISMA DRM specifications.

    \param    logger          message logger.
    \param    xmlDoc          XML document, containing necessary information for
                              encoding track.
    \param    fName           name of the source mp4 file to be protected.
    \param    srcTrackId      track ID of the source track that is to be protected.
    \param    eMethod         encryption method (AES128ICM).


    We emphasize that mandatory tags in the XML document are dependent on the DRM
    and content info managers used.
    xmlDoc can be created from an input file, or however it suits a user of DRM
    plugins. A user must only take care of providing necessary tags in the XML
    document, as indicated by documentation for a specific ContentInfoManager and
    IISMADRMEncManager.

    Here follows an example of the code for this function.

    \code

    #include "ContentInfoManagerFactory.h"
    #include "ISMADRMEncManagerFactory.h"
    #include "ISMAMPEG4SinfDRMEncryptor.h"
    #include "IXMLDocument.h"
    #include "DRMLogger.h"
    #include "ICipher.h"
    #include <string>

    using namespace DRMPlugin;
    using namespace MPEG4SinfDRMPlugin;

    bool ISMAMP4EncryptTrack(DRMLogger& logger, IXMLElement* xmlDoc,
        const std::string& fName, const unsigned int srcTrackId,
        EncMethod eMethod) {

      ContentInfoManager* infoManager = 0;
      IISMADRMEncManager* drmManager = 0;
      IISMAMPEG4SinfDRMEncryptor* encryptor = 0;

      // Create all necessary data for DRM protection.
      try {
        //  Create content info manager which will assign unique content ID to
        //  the protected content.
        infoManager = ContentInfoManagerFactory::GetContentInfoManager(
          OPENIPMPDOIINFOMANAGER, xmlDoc, logger);
        if (infoManager == 0) {
          return false;
        }

        //  Create a simple basic identifier for the track/file which is to be
        //  encrypted. A real content identifier will be created using this data.
        //  Here we just use the file name and track identifier.
        std::string title = fName + ".track" + IntToString(srcTrackId);
        DRMPlugin::IXMLElement* elem = xmlDoc->GetChildElement("ContentTitle");
        if (elem == 0) {
          delete infoManager;
          return false;
        }
        if (elem->SetStrValue(title) == false) {
          delete infoManager;
          return false;
        }

        //  Create content info with unique content ID for the protected content.
        std::string info;
        if (infoManager->GetContentInfo(xmlDoc, info, logger) == false) {
          delete infoManager;
          return false;
        }
        delete infoManager; infoManager = 0;

        //  Create DRM manager which will store encryption keys with respect to
        //  the content ID of the protected content and create DRM encryptor.
        drmManager = ISMADRMEncManagerFactory::GetISMADRMEncManager(xmlDoc, logger);
        if (drmManager == 0) {
          return false;
        }

        //  Create DRM encryptor that will protect the content.
        if (eMethod == EncMethod(AES128ICM)) {
          encryptor = new AES128ICMISMAMPEG4SinfDRMEncryptor(drmManager, info,
            xmlDoc, logger);
        } else {
          delete drmManager;
          logger.UpdateLog("ISMAMP4EncryptTrack: wrong encryption method.");
          return false;
        }

        //  Add (if any) licenses contained in the XML document.
        drmManager->AddLicense(info, xmlDoc, logger);
        delete drmManager; drmManager = 0;
      }
      catch (...) {
        if (infoManager != 0) delete infoManager;
        if (drmManager != 0) delete drmManager;
        if (encryptor != 0) delete encryptor;
        return false;
      }

      //  Create new track, including protected sample entry atoms ("enca", "encv")
      //  with "sinf" children atom, and all contained fields in it (see the
      //  description of those atoms for details).
      CreateTrack();

      ByteT* sample = NULL; 
      UInt32T sampleLength = 0;
      ByteT* encSample = NULL;
      UInt32T encSampleLength = 0;

      //  Read samples and call encryptor to encrypt them, then write encrypted samples
      //  to output file.
      while (ReadSample(&sample, &sampleLength)) {
        if (encryptor->EncryptSample(sample, sampleLength, &encSample, &encSampleLength) == false) {
          delete encryptor;
          return false;
        }
        WriteSample(encSample, encSampleLength);
        free(sample);
        free(encSample);
      }

      //  Get "sinf" atom corresponding to the protected samples (track).
      IMP4SinfAtom* sinf = GetSinfAtom();
      //  Get 4CC code corresponding to the protected samples (track). For video
      //  samples this will be (UInt32T)("mp4v"), and for audio samples
      //  (UInt32T)("mp4a").
      UInt32T otype = GetOriginalType();

      //  Add DRM information to "sinf" atom.
      if (encryptor->Finish(otype, sinf) == false) {
        delete encryptor;
        return false;
      }

      delete encryptor;

      return true;
    }

    \endcode
*/
bool ISMAMP4EncryptTrack(DRMLogger& logger, IXMLElement* xmlDoc, const std::string&
  fName, const unsigned int srcTrackId, EncMethod eMethod);

/*!  \brief Protect track according to openIPMP DRM specifications.

    Given a source track in a source file, make an encrypted copy of 
    the track in the destination file, including sample encryption, using
    openIPMP DRM specifications.

    \param    logger          message logger.
    \param    xmlDoc          XML document, containing necessary information for
                              encoding track.
    \param    fName           name of the source mp4 file to be protected.
    \param    srcTrackId      track ID of the source track that is to be protected.
    \param    eMethod         encryption method (AES128CTR or BLOWFISH).


    We emphasize that mandatory tags in the XML document are dependent on the DRM
    and content info managers used.
    xmlDoc can be created from an input file, or however it suits a user of DRM
    plugins. A user must only take care of providing necessary tags in the XML
    document, as indicated by documentation for a specific ContentInfoManager and
    IOpenIPMPDRMEncManager.

    Here follows an example of the code for this function.

    \code

    #include "ContentInfoManagerFactory.h"
    #include "OpenIPMPDRMEncManagerFactory.h"
    #include "OpenIPMPMPEG4SinfDRMEncryptor.h"
    #include "IXMLDocument.h"
    #include "DRMLogger.h"
    #include "ICipher.h"
    #include <string>

    using namespace DRMPlugin;
    using namespace MPEG4SinfDRMPlugin;

    bool OpenIPMPMP4EncryptTrack(DRMLogger& logger, IXMLElement* xmlDoc,
        const std::string& fName, const unsigned int srcTrackId,
        EncMethod eMethod) {

      ContentInfoManager* infoManager = 0;
      IOpenIPMPDRMEncManager* drmManager = 0;
      IOpenIPMPMPEG4SinfDRMEncryptor* encryptor = 0;

      // Create all necessary data for DRM protection.
      try {
        //  Create content info manager which will assign unique content ID to
        //  the protected content.
        infoManager = ContentInfoManagerFactory::GetContentInfoManager(
          OPENIPMPDOIINFOMANAGER, xmlDoc, logger);
        if (infoManager == 0) {
          return false;
        }

        //  Create a simple basic identifier for the track/file which is to be
        //  encrypted. A real content identifier will be created using this data.
        //  Here we just use the file name and track identifier.
        std::string title = fName + ".track" + IntToString(srcTrackId);
        DRMPlugin::IXMLElement* elem = xmlDoc->GetChildElement("ContentTitle");
        if (elem == 0) {
          delete infoManager;
          return false;
        }
        if (elem->SetStrValue(title) == false) {
          delete infoManager;
          return false;
        }

        //  Create content info with unique content ID for the protected content.
        std::string info;
        if (infoManager->GetContentInfo(xmlDoc, info, logger) == false) {
          delete infoManager;
          return false;
        }
        delete infoManager; infoManager = 0;

        //  Create DRM manager which will store encryption keys with respect to
        //  the content ID of the protected content and create DRM encryptor.
        drmManager = OpenIPMPDRMEncManagerFactory::GetOpenIPMPDRMEncManager(xmlDoc, logger);
        if (drmManager == 0) {
          return false;
        }

        //  Create DRM encryptor that will protect the content.
        if (eMethod == EncMethod(AES128CTR)) {
          encryptor = new AES128CTROpenIPMPMPEG4SinfDRMEncryptor(drmManager, info,
            xmlDoc, logger);
        } else if (eMethod == EncMethod(BLOWFISH)) {
          encryptor = new BlowfishOpenIPMPMPEG4SinfDRMEncryptor(drmManager, info,
            xmlDoc, logger);
        } else {
          delete drmManager;
          logger.UpdateLog("OpenIPMPMP4EncryptTrack: wrong encryption method.");
          return false;
        }

        //  Add (if any) licenses contained in the XML document.
        drmManager->AddLicense(info, xmlDoc, logger);
        delete drmManager; drmManager = 0;
      }
      catch (...) {
        if (infoManager != 0) delete infoManager;
        if (drmManager != 0) delete drmManager;
        if (encryptor != 0) delete encryptor;
        return false;
      }

      //  Create new track, including protected sample entry atoms ("enca", "encv")
      //  with "sinf" children atom, and all contained fields in it (see the
      //  description of those atoms for details).
      CreateTrack();

      ByteT* sample = NULL; 
      UInt32T sampleLength = 0;
      ByteT* encSample = NULL;
      UInt32T encSampleLength = 0;

      //  Read samples and call encryptor to encrypt them, then write encrypted samples
      //  to output file.
      while (ReadSample(&sample, &sampleLength)) {
        if (encryptor->EncryptSample(sample, sampleLength, &encSample, &encSampleLength) == false) {
          delete encryptor;
          return false;
        }
        WriteSample(encSample, encSampleLength);
        free(sample);
        free(encSample);
      }

      //  Get "sinf" atom corresponding to the protected samples (track).
      IMP4SinfAtom* sinf = GetSinfAtom();
      //  Get 4CC code corresponding to the protected samples (track). For video
      //  samples this will be (UInt32T)("mp4v"), and for audio samples
      //  (UInt32T)("mp4a").
      UInt32T otype = GetOriginalType();

      //  Add DRM information to "sinf" atom.
      if (encryptor->Finish(otype, sinf) == false) {
        delete encryptor;
        return false;
      }

      delete encryptor;

      return true;
    }

    \endcode
*/
bool OpenIPMPMP4EncryptTrack(DRMLogger& logger, IXMLElement* xmlDoc, const std::string&
  fName, const unsigned int srcTrackId, EncMethod eMethod);
