/**   \file MPEG2IPMPXEncoder.h

      \ingroup mpeg2drmencoder

      Test implementation of MPEG2 encoder with IPMPX signalling.

      The Initial Developer of the Original Code is Mutable, Inc. <br>
      Portions created by Mutable, Inc. are <br>
      Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

      
*/

#if !defined (MPEG2IPMPXENCODER_H)
#define MPEG2IPMPXENCODER_H

#include "BasicTypes.h"
#include "IIPMPControlInfoPart.h"

#include "IPMPControlInfoPart.h"
#include "IMPEG2IPMPXEncoder.h"
#include "DRMLogger.h"
#include "IXMLDocument.h"
#include "DRMLogger.h"
#include "ICipher.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  MPEG2 transport stream encoder with IPMPX signalling.

    MPEG2 transport stream encoder is used by DRM encoder for adding DRM
    information to MPEG2 transport stream.
*/
class MPEG2IPMPXTStreamEncoder: public IMPEG2IPMPXTStreamEncoder {
public:
  /*! \brief  Constructor.

      \param  logger      message logger.
  */
  MPEG2IPMPXTStreamEncoder(DRMLogger& logger): inter(), last(0), encLogger(logger) {
  }

  virtual ~MPEG2IPMPXTStreamEncoder() {
    for (unsigned int i = 0; i < inter.size(); i++) {
      delete inter[i];
    }
    inter.clear();
    if (last != 0) delete last; last = 0;
  }

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
  virtual bool CreateInterIPMPControlInfoPart(IInterTStreamIPMPControlInfoPart** interPart);

  /*! \brief  Create new last part of the IPMP control information structure.

      The newly created last part is the last part in a row of parts constituting
      an IPMP control information structure. DRM encoder must take care of the
      correct indexing and calling of this and corresponding IPMP control
      information parts creating functions.

      \param  lastPart    output, newly created last part pointer (if successful).

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateLastIPMPControlInfoPart(ILastTStreamIPMPControlInfoPart** lastPart);

  /*! \brief  Encode file.

      Encoding order is: intermediate control info parts, last control info part,
      IPMP descriptor.

      \param  in        input, name of the input file.
      \param  out       input, name of the output file.
      \param  xml       input-output, XML document containing necessary
                        information for protecting content.
      \param  method    input, encryption method.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(std::string& in, const std::string& out, IXMLElement* xml,
    EncMethod method);

private:
  std::vector<InterTStreamIPMPControlInfoPart*> inter;
  LastTStreamIPMPControlInfoPart* last;
  DRMLogger& encLogger;
};

/*! \brief  MPEG2 program stream encoder with IPMPX signalling.

    MPEG2 program stream encoder is used by DRM encoder for adding DRM
    information to MPEG2 program stream.
*/
class MPEG2IPMPXPStreamEncoder: public IMPEG2IPMPXPStreamEncoder {
public:
  /*! \brief  Constructor.

      \param  logger      message logger.
  */
  MPEG2IPMPXPStreamEncoder(DRMLogger& logger): inter(), last(0), encLogger(logger) {
  }

  virtual ~MPEG2IPMPXPStreamEncoder() {
    for (unsigned int i = 0; i < inter.size(); i++) {
      delete inter[i];
    }
    inter.clear();
    if (last != 0) delete last; last = 0;
  }

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
  virtual bool CreateInterIPMPControlInfoPart(IInterPStreamIPMPControlInfoPart** interPart);

  /*! \brief  Create new last part of the IPMP control information structure.

      The newly created last part is the last part in a row of parts constituting
      an IPMP control information structure. DRM encoder must take care of the
      correct indexing and calling of this and corresponding IPMP control
      information parts creating functions.

      \param  lastPart    output, newly created last part pointer (if successful).

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateLastIPMPControlInfoPart(ILastPStreamIPMPControlInfoPart** lastPart);

  /*! \brief  Encode file.

      Encoding order is: intermediate control info parts, last conrol info part,
      IPMP descriptor.

      \param  in        input, name of the input file.
      \param  out       input, name of the output file.
      \param  xml       input-output, XML document containing necessary
                        information for protecting content.
      \param  method    input, encryption method.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(std::string& in, const std::string& out, IXMLElement* xml,
    EncMethod method);

private:
  std::vector<InterPStreamIPMPControlInfoPart*> inter;
  LastPStreamIPMPControlInfoPart* last;
  DRMLogger& encLogger;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(MPEG2IPMPXENCODER_H)
