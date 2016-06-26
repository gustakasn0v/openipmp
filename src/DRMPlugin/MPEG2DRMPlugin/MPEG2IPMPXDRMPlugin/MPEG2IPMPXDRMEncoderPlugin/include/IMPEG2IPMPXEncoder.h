/**	\file IMPEG2IPMPXEncoder.h

	Interfaces for MPEG2 encoder with IPMPX signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IMPEG2IPMPXENCODER_H)
#define IMPEG2IPMPXENCODER_H

#include "BasicTypes.h"
#include "IIPMPControlInfoPart.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  MPEG2 transport stream encoder with IPMPX signalling.

    MPEG2 transport stream encoder is used by DRM encoder for adding DRM
    information to MPEG2 transport stream.
*/
class IMPEG2IPMPXTStreamEncoder {
public:
  virtual ~IMPEG2IPMPXTStreamEncoder() {};

  /*! \brief  Create new intermediate part of the IPMP control information
              structure.

      The newly created intermediate part is the intermediate part in a row of
      parts constituting an IPMP control information structure. DRM encoder must
      take care of the correct indexing and calling of this and corresponding IPMP
      control information parts creating functions.

      \param  interPart     output, newly created intermediate part pointer
                            (if successful).

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateInterIPMPControlInfoPart(IInterTStreamIPMPControlInfoPart** interPart) = 0;

  /*! \brief  Create new last part of the IPMP control information structure.

      The newly created last part is the last part in a row of parts constituting
      an IPMP control information structure. DRM encoder must take care of the
      correct indexing and calling of this and corresponding IPMP control
      information parts creating functions.

      \param  lastPart    output, newly created last part pointer (if successful).

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateLastIPMPControlInfoPart(ILastTStreamIPMPControlInfoPart** lastPart) = 0;
};

/*! \brief  MPEG2 program stream encoder with IPMPX signalling.

    MPEG2 program stream encoder is used by DRM encoder for adding DRM
    information to MPEG2 program stream.
*/
class IMPEG2IPMPXPStreamEncoder {
public:
  virtual ~IMPEG2IPMPXPStreamEncoder() {};

  /*! \brief  Create new intermediate part of the IPMP control information
              structure.

      The newly created intermediate part is the intermediate part in a row of
      parts constituting an IPMP control information structure. DRM encoder must
      take care of the correct indexing and calling of this and corresponding IPMP
      control information parts creating functions.

      \param  interPart     output, newly created intermediate part pointer
                            (if successful).

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateInterIPMPControlInfoPart(IInterPStreamIPMPControlInfoPart** interPart) = 0;

  /*! \brief  Create new last part of the IPMP control information structure.

      The newly created last part is the last part in a row of parts constituting
      an IPMP control information structure. DRM encoder must take care of the
      correct indexing and calling of this and corresponding IPMP control
      information parts creating functions.

      \param  lastPart    output, newly created last part pointer (if successful).

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateLastIPMPControlInfoPart(ILastPStreamIPMPControlInfoPart** lastPart) = 0;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(IMPEG2IPMPXENCODER_H)
