/**	\file IIPMPStreamDataUpdate.h

	Interface for IPMP stream data update message.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IIPMPSTREAMDATAUPDATE_H)
#define IIPMPSTREAMDATAUPDATE_H

#include "BasicTypes.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Update message from IPMP stream.

    IPMP stream data update is a message from IPMP stream, carrying additional
    IPMP data messages for IPMP tool.
*/
class IIPMPStreamDataUpdate {
public:
  virtual ~IIPMPStreamDataUpdate() {}

  /*! \brief  Get IPMP descriptor identifier.

      \returns IPMP descriptor identifier.
  */
  virtual const Bit32T& GetIPMPDescriptorID() const = 0;

  /*! \brief  Set IPMP descriptor identifier.

      If previous IPMP descriptor identifier existed, it must be replaced
      with the provided one.

      \param  id          input, IPMP descriptor identifier to be set.

      \returns Boolean indicating success or failure.
  */
  virtual bool SetIPMPDescriptorID(const Bit32T& id) = 0;

  /*! \brief  Get IPMP data.

      \returns IPMP data.
  */
  virtual const ByteSeq& GetIPMPData() const = 0;

  /*! \brief  Set IPMP data.

      If previous IPMP data existed, it must be replaced with the provided one.

      \param  ipmp          input, IPMP data to be set.

      \returns Boolean indicating success or failure.
  */
  virtual bool SetIPMPData(const ByteSeq& ipmp) = 0;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(IIPMPSTREAMDATAUPDATE_H)
