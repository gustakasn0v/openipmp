/**	\file DecryptorHolder.cpp

	Holder for DRM decryptors. It is used as a container for decryptors for
  different crypto/drm methods, to prevent constantly calling DRM manager
  for creating decryptors.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "DecryptorHolder.h"
#include "DRMInfoException.h"
#include "ISMADRMInfo.h"
#include "OMADRMInfo.h"
#include "OpenIPMPDRMInfo.h"
#include "ISMADRMDecManagerFactory.h"
#include "OMADRMDecManagerFactory.h"
#include "OpenIPMPDRMDecManagerFactory.h"
#include "DRMDecManagerException.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG4SinfDRMPlugin namespace. All MPEG4 Sinf DRM plugin code resides in it.
namespace MPEG4SinfDRMPlugin {

/*! \brief Holder for DRM decryptors.

    It is used as a container for decryptors for different crypto/drm methods,
    to prevent constantly calling DRM manager for creating decryptors.
*/
/*! \brief  Set XML document.

    \param  xml         input, XML document to be set.
*/
void DecryptorHolder::SetXML(IXMLElement* xml) {
  xmlDoc = xml;
}

/*! \brief  Get DRM decryptor using information in scheme information atom.

    DRM decryptor can be 0, if scheme information atom indicates that there
    is no protection.

    \param  sinf        input, scheme information atom.
    \param  decryptor   output, DRM decryptor.

    \returns  Boolean indicating success or failure.
*/
bool DecryptorHolder::GetDecryptor(IMP4SinfAtom* sinf, IDRMDecryptor** decryptor) {
  *decryptor = 0;
  if (sinf == 0) {
    return true;
  }

  IMP4FrmaAtom* frma = sinf->GetOriginalFormat();
  IMP4ImifAtom* imif = sinf->GetIPMPInfo();
  IMP4SchmAtom* schm = sinf->GetSchemeType();
  IMP4SchiAtom* schi = sinf->GetSchemeInformation();

  // Original format atom must be present.
  if (frma == 0) {
    holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: frma atom not present...");
    return false;
  }

  if (((schm == 0) && (schi != 0)) || ((schm != 0) && (schi == 0))) {
    // Error. Either both schm and schi are defined, or none.
    holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: either both schm and schi atoms must be present or none...");
    return false;
  } else if ((schm != 0) && (schi != 0)) {
    // Scheme type and information follows, indicating special scheme protection.
    if (schm->GetSchemeCode() == ('o'<<24 | 'd'<<16 | 'k'<<8 | 'm')) {
      // OMA DRM protection scheme.
      if (schm->GetSchemeVersion() != 0x0200) {
        // Error.
        holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: wrong OMA version...");
        return false;
      }
      IMP4OdkmAtom* odkm = schi->GetOMADRMAtom();
      if (odkm == 0) {
        // Error.
        holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: odkm atom not present...");
        return false;
      }
      IMP4OhdrAtom* ohdr = odkm->GetOMADRMHeaders();
      if (ohdr == 0) {
        // Error.
        holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: ohdr atom not present...");
        return false;
      }
      try {
        OMADRMInfo info(ohdr->GetEncryptionMethod(), ohdr->GetEncryptionPadding(),
          ohdr->GetPlaintextLength(), ohdr->GetContentIdentifier(),
          schm->GetSchemeVersion(), ohdr->GetRightsIssuerURL(),
          ohdr->GetTextualHeaders(), ohdr->GetTextualHeadersLength(), holderLogger);

        if (id2Dec.find(info.GetContentID()) != id2Dec.end()) {
          *decryptor = id2Dec[info.GetContentID()];
          return true;
        }

        IOMADRMDecManager* manager =
          OMADRMDecManagerFactory::GetOMADRMDecManager(xmlDoc, holderLogger);
        if (manager == 0) {
          return false;
        }

        *decryptor = manager->CreateDecryptor(info, xmlDoc);
        delete manager;
        if (*decryptor != 0) {
          id2Dec[info.GetContentID()] = *decryptor;
        }
        return (*decryptor != 0);
      }
      catch (DRMInfoException) {
        return false;
      }
    } else if (schm->GetSchemeCode() == ('i'<<24 | 'A'<<16 | 'E'<<8 | 'C')) {
      // ISMA DRM protection scheme.
      if (schm->GetSchemeVersion() != 1) {
        // Error.
        holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: wrong ISMA version...");
        return false;
      }
      IMP4IKMSAtom* iKMS = schi->GetISMAKMSAtom();
      IMP4ISFMAtom* iSFM = schi->GetISMASFMAtom();
      if ((iKMS == 0) || (iSFM == 0)) {
        // Error.
        holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: iKMS or iSFM atom not present...");
        return false;
      }

      /*  Currently we don't know how to encode contentID for the ISMA DRM,
          so we put it in the IPMP descriptor (similar to one defined in
          ISMA specifications for streaming).
      */
      if (imif == 0) {
        // Error.
        holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: imif atom not present...");
        return false;
      }
      if (imif->GetIPMPDescriptorCount() == 0) {
        // No IPMP descriptors.
        holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: IPMP descriptor not present in imif atom...");
        return false;
      }
      // IPMP descriptor follows, indicating IPMP protection.
      IMP4IPMPDescriptor* ipmpDesc = imif->GetIPMPDescriptor(0);
      if (ipmpDesc == 0) {
        // Error.
        holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: IPMP descriptor not present in imif atom...");
        return false;
      }
      if (ipmpDesc->GetIPMPDescriptorIdentifier() != 1) {
        // Error.
        holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: wrong IPMP descriptor identifier...");
        return false;
      }
      if (ipmpDesc->GetIPMPDescriptorType() != 0x4953) {
        // Error.
        holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: wrong IPMP descriptor type...");
        return false;
      }
      try {
        ISMADRMInfo info(ipmpDesc->GetIPMPData(), ipmpDesc->GetIPMPDataLength(),
          schm->GetSchemeVersion(), iKMS->GetKeyManagementSystemURI(),
          iSFM->GetSelectiveEncryption(), iSFM->GetKeyIndicatorLength(),
          iSFM->GetIVLength(), holderLogger);

        if (id2Dec.find(info.GetContentID()) != id2Dec.end()) {
          *decryptor = id2Dec[info.GetContentID()];
          return true;
        }

        IISMADRMDecManager* manager =
          ISMADRMDecManagerFactory::GetISMADRMDecManager(xmlDoc, holderLogger);
        if (manager == 0) {
          return false;
        }

        *decryptor = manager->CreateDecryptor(info, xmlDoc);
        delete manager;
        if (*decryptor != 0) {
          id2Dec[info.GetContentID()] = *decryptor;
        }
        return (*decryptor != 0);
      }
      catch (DRMInfoException) {
        return false;
      }
    } else {
      // Unknown protection scheme.
      return false;
    }
  } else if (imif != 0) {
    if (imif->GetIPMPDescriptorCount() == 0) {
      // No IPMP descriptors.
      holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: no IPMP descriptors...");
      return true;
    }
    // IPMP descriptor follows, indicating IPMP protection.
    IMP4IPMPDescriptor* ipmpDesc = imif->GetIPMPDescriptor(0);
    if (ipmpDesc == 0) {
      // Error.
      holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: no IPMP descriptors...");
      return false;
    }
    if (ipmpDesc->GetIPMPDescriptorIdentifier() != 255) {
      // Unrecognized IPMP protection.
      holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: unrecognized IPMP descriptor identifier (only openIPMP is supported)...");
      return false;
    }
    if (ipmpDesc->GetIPMPDescriptorType() != 65535) {
      // Unrecognized IPMP protection.
      holderLogger.UpdateLog("DecryptorHolder::GetDecryptor: unrecognized IPMP descriptor type (only openIPMP is supported)...");
      return false;
    }
    //  We recognized "openIPMP" protection.
    try {
      OpenIPMPDRMInfo info(ipmpDesc->GetIPMPData(), ipmpDesc->GetIPMPDataLength(),
        holderLogger);
      if (id2Dec.find(info.GetContentID()) != id2Dec.end()) {
        *decryptor = id2Dec[info.GetContentID()];
        return true;
      }

      IOpenIPMPDRMDecManager* manager =
        OpenIPMPDRMDecManagerFactory::GetOpenIPMPDRMDecManager(xmlDoc, holderLogger);
      if (manager == 0) {
        return false;
      }

      *decryptor = manager->CreateDecryptor(info, xmlDoc);
      delete manager;
      if (*decryptor != 0) {
        id2Dec[info.GetContentID()] = *decryptor;
      }
      return (*decryptor != 0);
    }
    catch (DRMInfoException) {
      return false;
    }
  } else {
    // No protection defined.
    return true;
  }
}

} // namespace MPEG4SinfDRMPlugin

} // namespace DRMPlugin
