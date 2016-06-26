/**	\file IOpenIPMPMPEG4SinfDRMEncryptor.h

	Interfaces for OpenIPMP MPEG4 DRM encryptor plugin with Sinf signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IOPENIPMPMPEG4SINFDRMENCRYPTOR_H)
#define IOPENIPMPMPEG4SINFDRMENCRYPTOR_H

#include "IMPEG4SinfDRMEncryptor.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG4SinfDRMPlugin namespace. All MPEG4 Sinf DRM plugin code resides in it.
namespace MPEG4SinfDRMPlugin {

/*! \brief  Encrypts MP4 data according to openIPMP specifications with
            Sinf signalling.

    Encrypts samples and adds information for decryption to MP4 stream.
*/
class IOpenIPMPMPEG4SinfDRMEncryptor: public IMPEG4SinfDRMEncryptor {
};

} // namespace MPEG4SinfDRMPlugin

} // namespace DRMPlugin

#endif // !defined (IOPENIPMPMPEG4SINFDRMENCRYPTOR_H)
