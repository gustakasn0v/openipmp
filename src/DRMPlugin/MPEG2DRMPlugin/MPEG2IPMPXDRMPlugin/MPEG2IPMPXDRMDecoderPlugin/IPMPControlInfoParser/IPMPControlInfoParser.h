/**	\file IPMPControlInfoParser.h

	IPMP control information classes parser.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPMPCONTROLINFOPARSER_H)
#define IPMPCONTROLINFOPARSER_H

#include "BasicTypes.h"
#include <string>
#include "DecoderIPMPControlInfo.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  IPMP control info parser exception.
*/
class IPMPControlInfoParserException {
};

/*! \brief  Parser of IPMP control information classes.

    Used for parsing IPMP control information classes and returning parsed
    classes to callers.
*/
class IPMPControlInfoParser {
public:
  /*!  \brief  Constructor.

      \param  logger      message logger.
  */
  IPMPControlInfoParser(DRMLogger& logger): parserLogger(logger) {
  }

  ~IPMPControlInfoParser() {
  }

  /*! \brief  Parse IPMP control information class.

      \warning  Encoded data is modified during parsing.

      \param  encoded   input, encoded data.
      \param  control   output, parsed IPMP control information class.

      \returns  Boolean indicating success or failure.
  */
  bool ParseIPMPControlInfo(ByteSeq& encoded, DecoderIPMPControlInfo** control);

protected:
  /*! \brief  Parse IPMP rights container.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPControlInfoParserException.

      \param  encoded   input, encoded message.

      \returns  IPMP rights container.
  */
  DecoderIPMPRightsContainer* ParseIPMPRightsContainer(ByteSeq& encoded);

  /*! \brief  Parse IPMP tool container.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPControlInfoParserException.

      \param  encoded   input, encoded message.

      \returns  IPMP tool container.
  */
  DecoderIPMPToolContainer* ParseIPMPToolContainer(ByteSeq& encoded);

  /*! \brief  Parse IPMP parametric description.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPControlInfoParserException.

      \param  encoded   input, encoded message.

      \returns  IPMP parametric description.
  */
  DecoderIPMPParametricDescription* ParseIPMPParametricDescription(ByteSeq& encoded);

  /*! \brief  Parse IPMP tool description.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPControlInfoParserException.

      \param  encoded   input, encoded message.

      \returns  IPMP tool description.
  */
  ToolDescription ParseToolDescription(ByteSeq& encoded);

  /*! \brief  Parse IPMP tool info.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPControlInfoParserException.

      \param  encoded   input, encoded message.

      \returns  IPMP tool info.
  */
  DecoderIPMPToolInfo* ParseIPMPToolInfo(ByteSeq& encoded);

  /*! \brief  Parse IPMP tool list.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPControlInfoParserException.

      \param  encoded     input, encoded data.

      \returns  IPMP tool list.
  */
  DecoderIPMPToolList* ParseIPMPToolList(ByteSeq& encoded);

  DRMLogger& parserLogger;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (IPMPCONTROLINFOPARSER_H)
