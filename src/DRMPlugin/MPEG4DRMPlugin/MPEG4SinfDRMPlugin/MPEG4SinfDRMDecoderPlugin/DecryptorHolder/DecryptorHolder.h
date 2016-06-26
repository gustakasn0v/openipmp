/**	\file DecryptorHolder.h

	Holder for DRM decryptors. It is used as a container for decryptors for
  different crypto/drm methods, to prevent constantly calling DRM manager
  for creating decryptors.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (DECRYPTORHOLDER_H)
#define DECRYPTORHOLDER_H

/* disabled warning
	  'identifier' : identifier was truncated to 'number' characters in
	  the debug information
*/
#pragma warning(disable: 4786)

#include <string>
#include "IXMLDocument.h"
#include "IDRMDecryptor.h"
#include "DRMLogger.h"
#include "IMPEG4DRMAtom.h"

#include <map>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG4SinfDRMPlugin namespace. All MPEG4 Sinf DRM plugin code resides in it.
namespace MPEG4SinfDRMPlugin {

/*! \brief Holder for DRM decryptors.

    It is used as a container for decryptors for different crypto/drm methods,
    to prevent constantly calling DRM manager for creating decryptors.
*/
class DecryptorHolder {
public:
  /*! \brief  Constructor.

      \param  logger      message logger.
  */
  DecryptorHolder(DRMLogger& logger): xmlDoc(0), holderLogger(logger) {
  }

  /*! \brief  Constructor.

      \param  xml         XML document.
      \param  logger      message logger.
  */
  DecryptorHolder(IXMLElement* xml, DRMLogger& logger): xmlDoc(xml), holderLogger(logger) {
  }

  ~DecryptorHolder() {
    std::map<std::string, IDRMDecryptor*>::iterator iter = id2Dec.begin();
    while (iter != id2Dec.end()) {
      delete iter->second;
      iter++;
    }
  }

  /*! \brief  Set XML document.

      \param  xml         input, XML document to be set.
  */
  void SetXML(IXMLElement* xml);

  /*! \brief  Get DRM decryptor using information in scheme information atom.

      DRM decryptor can be 0, if scheme information atom indicates that there
      is no protection.

      \param  sinf        input, scheme information atom.
      \param  decryptor   output, DRM decryptor.

      \returns  Boolean indicating success or failure.
  */
  bool GetDecryptor(IMP4SinfAtom* sinf, IDRMDecryptor** decryptor);

private:
  IXMLElement* xmlDoc;
  std::map<std::string, IDRMDecryptor*> id2Dec;
  DRMLogger& holderLogger;
};

} // namespace MPEG4SinfDRMPlugin

} // namespace DRMPlugin

#endif // !defined (DECRYPTORHOLDER_H)
