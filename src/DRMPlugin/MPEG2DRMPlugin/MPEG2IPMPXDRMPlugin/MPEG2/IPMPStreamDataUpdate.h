/**	\file IPMPStreamDataUpdate.h

    \ingroup drmplayer
    \ingroup drmencoder

	Test implementation of IPMP stream data update message.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPMPSTREAMDATAUPDATE_H)
#define IPMPSTREAMDATAUPDATE_H

#include "BasicTypes.h"
#include "IIPMPStreamDataUpdate.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Update message from IPMP stream.

    IPMP stream data update is a message from IPMP stream, carrying additional
    IPMP data messages for IPMP tool.
*/
class IPMPStreamDataUpdate: public IIPMPStreamDataUpdate {
public:
  /*! \brief  Constructor.
  */
  IPMPStreamDataUpdate(): ipmpDescriptorID(0), ipmpData() {
  }

  /*! \brief  Constructor.
      
      \param  id        IPMP descriptor identifier.
      \param  data      IPMP data (encoded).
  */
  IPMPStreamDataUpdate(const Bit32T& id, const ByteSeq& data):
    ipmpDescriptorID(id), ipmpData(data) {
  }

  virtual ~IPMPStreamDataUpdate() {
  }

  /*! \brief  Get IPMP descriptor identifier.

      \returns IPMP descriptor identifier.
  */
  virtual const Bit32T& GetIPMPDescriptorID() const {
    return ipmpDescriptorID;
  }

  /*! \brief  Set IPMP descriptor identifier.

      If previous IPMP descriptor identifier existed, it must be replaced
      with the provided one.

      \param  id          input, IPMP descriptor identifier to be set.

      \returns Boolean indicating success or failure.
  */
  virtual bool SetIPMPDescriptorID(const Bit32T& id) {
    ipmpDescriptorID = id;
    return true;
  }

  /*! \brief  Get IPMP data.

      \returns IPMP data.
  */
  virtual const ByteSeq& GetIPMPData() const {
    return ipmpData;
  }

  /*! \brief  Set IPMP data.

      If previous IPMP data existed, it must be replaced with the provided one.

      \param  ipmp          input, IPMP data to be set.

      \returns Boolean indicating success or failure.
  */
  virtual bool SetIPMPData(const ByteSeq& ipmp) {
    ipmpData = ipmp;
    return true;
  }

  /*! \brief  Encode.

      \param  encoded       output, encoded data.

      \returns Boolean indicating success or failure.
  */
  bool Encode(ByteSeq& encoded) {
    encoded = ByteSeq(ipmpDescriptorID) + ipmpData;
  }

private:
  Bit32T ipmpDescriptorID;
  ByteSeq ipmpData;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(IPMPSTREAMDATAUPDATE_H)
