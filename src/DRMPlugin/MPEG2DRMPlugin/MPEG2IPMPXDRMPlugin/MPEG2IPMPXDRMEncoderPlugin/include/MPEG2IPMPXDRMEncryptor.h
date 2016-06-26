/**	\file MPEG2IPMPXDRMEncryptor.h

	Additional functionality for MPEG2 DRM encryptor with IPMPX signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (MPEG2IPMPXDRMENCRYPTOR_H)
#define MPEG2IPMPXDRMENCRYPTOR_H

#include "BasicTypes.h"
#include "IMPEG2IPMPXDRMEncryptor.h"
#include <string>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  MPEG2 DRM encryptor with IPMPX signalling and additional functionality.

    Encryptor class with additional functionality of creating control info
    class, used by MPEG2 DRM encoder.
*/
class MPEG2IPMPXDRMEncryptor: public IMPEG2IPMPXDRMEncryptor {
public:
  virtual ~MPEG2IPMPXDRMEncryptor() {};

  /*! \brief  Create and encode control info class.

      Control info class is this encryptor's (tool's) description, used for
      later correct initialization.

      \param  cInfo           output, encoded control info class.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateControlInfo(ByteSeq& cInfo) = 0;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (MPEG2IPMPXDRMENCRYPTOR_H)
