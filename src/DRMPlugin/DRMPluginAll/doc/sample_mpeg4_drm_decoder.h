/**
    \defgroup mpeg4drmplayer mpeg4 DRM player documentation.
*/
/**     \file sample_mpeg4_drm_decoder.h

        \ingroup mpeg4drmplayer

        Example of use of DRM plugins in a mpeg4 decode case.

        The Initial Developer of the Original Code is Mutable, Inc. <br>
        Portions created by Mutable, Inc. are <br>
        Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

        
*/

/*! \brief Play protected content.

    \param    xmlDoc          XML document, containing necessary information for
                              decoding track.
    \param    logger          message logger.

    We emphasize that mandatory tags in the XML document are dependent on the DRM
    manager used.  See sample XML file <a href="../PlayerInfo.xml">PlayerInfo</a>.
    P12FilePath tag in XML configuration file must be set to the path where .p12 file
    for the user playing the content resides.  To create a new user and save his .p12
    file, go to http://localhost:8080/openipmp/jsp/login.jsp (if DRM server resides
    on some other IP address, replace localhost:8080 with its address).<br>
    RandomNumberFilePath tag in XML configuration file must be set to the path where
    entropy.dat will reside. Can be left as it is.<br>
    RegDatabasePath, RODatabasePath, CertPath, PrivateKeyPath and RootCAPath tags in
    XML configuration file are used for playing OMA DRM protected content. One must
    set these paths to registration database file path, rights database file path,
    device certificate file path, device private key file path and OMA DRM CA
    certificate file path.<br>
    Other tags in XML configuration file can be left as they are.<br>
    
    xmlDoc can be created from an input file, or however it suits a user of DRM
    plugins. A user must only take care of providing necessary tags in the XML
    document, as indicated by documentation for a specific DRM decoder manager.

    Here follows an example of the code for this function.

    \code

    #include "DecryptorHolder.h"
    #include "IXMLDocument.h"

    using namespace DRMPlugin;
    using namespace MPEG4SinfDRMPlugin;

    bool Play(IXMLElement* xmlDoc, DRMLogger& logger) {
      //  Make new decryptor holder that will create and keep decryptors.
      static DecryptorHolder decryptorHolder(xmlDoc, logger);
      
      ByteT* sample = NULL; 
      UInt32T sampleLength = 0;
      ByteT* encSample = NULL;
      UInt32T encSampleLength = 0;

      //  Read samples and call decryptor to decrypt them if they are protected.
      while (ReadSample(&encSample, &encSampleLength)) {
        //  Get "sinf" atom corresponding to the protected samples (track).
        IMP4SinfAtom* sinf = GetSinfAtom();
        try {
          IDRMDecryptor* decryptor = 0;
          //  Try to get decryptor for the protected content.
          if (decryptorHolder.GetDecryptor(sinf, &decryptor) == false) {
            if (encSample) free(encSample);
            if (sample) free(sample);
            return false;
          }
          //  If decryptor == 0, and the GetDecryptor() function returned true, it
          //  means that sample is not protected, therefore no decryption needs
          //  to be done. This could be the result of selective encryption, for
          //  example.
          if (decryptor != 0) {
            //  Try to decrypt sample.
            if (decryptor->DecryptSample(encSample, encSampleLength, &sample,
                &sampleLength) == false) {
              if (encSample) free(encSample);
              if (sample) free(sample);
              return false;
            }
            //  Render unprotected sample.
            RenderSample(sample, sampleLength);
          } else {
            //  Render unprotected sample.
            RenderSample(encSample, encSampleLength);
          }
          if (encSample) free(encSample);
          if (sample) free(sample);
        }
        catch (...) {
          if (encSample) free(encSample);
          if (sample) free(sample);
          return false;
        }
      }

      if (encSample) free(encSample);
      if (sample) free(sample);
      return true;
    }

    \endcode
*/
bool Play(IXMLElement* xmlDoc, DRMLogger& logger);
