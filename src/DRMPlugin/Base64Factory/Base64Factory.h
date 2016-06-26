/**	\file Base64Factory.h

	Base64 encoding and decoding tool.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (BASE64FACTORY_H)
#define BASE64FACTORY_H

#include <string>
#include "BasicTypes.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Base64 factory. Encodes to base64 and decodes from base64.
*/
class Base64Factory {
public:
  /*! \brief  Helper routine for base64 encoding.

      \param  data        input, byte data.
      \param  b64         output, base64 encoded data.

      \returns  Boolean indicating success or failure.
  */
  static bool Encode(const ByteSeq& data, Base64StringT& b64);

  /*! \brief  Helper routine for base64 decoding.

      \param  b64         input, base64 encoded data.
      \param  data        output, byte data.

      \returns  Boolean indicating success or failure.
  */
  static bool Decode(const Base64StringT& b64, ByteSeq& data);
};
  
} // namespace DRMPlugin

#endif // !defined (BASE64FACTORY_H)
