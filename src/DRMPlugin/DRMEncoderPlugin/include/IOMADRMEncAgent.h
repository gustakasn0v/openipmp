/**	\file IOMADRMEncAgent.h

	OMA DRM agent used in encoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IOMADRMENCAGENT_H)
#define IOMADRMENCAGENT_H

#include "ROAPMessages.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM agent used in encoding process. Handles OMA DRM messages.
*/
class IOMADRMEncAgent: public GC {
public:
  virtual ~IOMADRMEncAgent() {
  }

  /*! \brief  Handle add content encryption key response.

      \param  response          input, add content encryption key response.
  */
  virtual void HandleAddContentKeyResponse(const NZSPtr<AddContentKeyResponse>& response) = 0;

  /*! \brief  Handle add rights for device for content response.

      \param  response          input, add rights for device for content response.
  */
  virtual void HandleAddDeviceRightsResponse(const NZSPtr<AddDeviceRightsResponse>& response) = 0;
};

} // namespace DRMPlugin

#endif // !defined (IOMADRMENCAGENT_H)
