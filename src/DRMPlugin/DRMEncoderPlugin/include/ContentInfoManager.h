/**	\file ContentInfoManager.h

	Interfaces for content information manager plugin.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (CONTENTINFOMANAGER_H)
#define CONTENTINFOMANAGER_H

#include <string>
#include "IXMLDocument.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Exception used for content information manager error.
*/
class ContentInfoManagerException {
};

/*! \brief Manager for creating content information out of some basic information.
*/
class ContentInfoManager {
public:
  virtual ~ContentInfoManager() {};
  /*! \brief  Create DRM content information.
  
      Use the information provided in the given XML document.
      See the specific manager documentation for the correct format of the XML
      document.

      Generally, for all content info managers, mandatory tags in the XML file are:
       - ROOT.ContentTitle

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <ContentTitle>test30.mp4.track1</ContentTitle>
      </ROOT>

      \endverbatim

      \param    xmlDoc          XML document containing necessary information for
                                creating content info.
      \param    info            output, newly created content info.

      \return Boolean indicating success or failure.
  */
  virtual bool GetContentInfo(IXMLElement* xmlDoc, std::string& info) = 0;
};

} // namespace DRMPlugin

#endif // !defined (CONTENTINFOMANAGER_H)
