/**   \file MPEG2IPMPXParser.h

      \ingroup mpeg2drmplayer

      MPEG2 test parsers with IPMPX signalling.

      The Initial Developer of the Original Code is Mutable, Inc. <br>
      Portions created by Mutable, Inc. are <br>
      Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

      
*/

#if !defined (MPEG2IPMPXPARSER_H)
#define MPEG2IPMPXPARSER_H

#include "IIPMPControlInfoPart.h"
#include "IIPMPDescriptor.h"
#include "IIPMPStreamDataUpdate.h"
#include "ISigCertContainer.h"
#include "DRMLogger.h"
#include "IPMPToolManager.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  MPEG2 parser exception.
*/
class MPEG2ParserException {
};

/*! \brief  MPEG2 parser with IPMPX signalling.

    Contains common routines for transport and program stream parsers.
*/
class MPEG2IPMPXParser {
public:
  /*! \brief  Constructor.

      \param  man         tool manager, that will handle parsed data (must be != 0).
      \param  logger      message logger.

      In case of an error, throws MPEG2ParserException.
  */
  MPEG2IPMPXParser(IPMPToolManager* man, DRMLogger& logger): manager(man), parserLogger(logger) {
  }

  virtual ~MPEG2IPMPXParser() {
    if (manager != 0) delete manager; manager = 0;
  }

  /*! \brief  Parse stream and call tool manager's handling routines.

      \warning  Input stream is modified in process.

      \param  stream        input, transport stream.

      \returns  Boolean indicating success or failure.
  */
  virtual bool ParseStream(ByteSeq& stream) = 0;

protected:
  /*! \brief Parse byte array.

      \warning  Input stream is modified in process.

      Calculate array's length and retrieve array data.
      Possibly throws ByteSeqException.

      \returns  Byte array.
  */
  ByteSeq ParseByteSeq(ByteSeq& stream);

  /*! \brief Parse IPMP descriptor.

      \warning  Input stream is modified in process.

      Possibly throws ByteSeqException.

      \returns  IPMP descriptor pointer (if 0, failed).
  */
  IIPMPDescriptor* ParseIPMPDescriptor(ByteSeq& stream);

  /*! \brief Parse signature and certificate container.

      \warning  Input stream is modified in process.

      Possibly throws ByteSeqException.

      \returns  Signature and certificate container pointer (if 0, failed).
  */
  ISigCertContainer* ParseSigCertContainer(ByteSeq& stream);

  /*! \brief Parse IPMP stream data update.

      \warning  Input stream is modified in process.

      Possibly throws ByteSeqException.

      \returns  IPMP stream data update pointer (if 0, failed).
  */
  IIPMPStreamDataUpdate* ParseIPMPStreamDataUpdate(ByteSeq& stream);

  //! Tool manager that handles parsed data.
  IPMPToolManager* manager;

  DRMLogger& parserLogger;
};

/*! \brief  MPEG2 transport stream parser with IPMPX signalling.

    Parses data and calls handling routines.
*/
class MPEG2IPMPXTStreamParser: public MPEG2IPMPXParser {
public:
  /*! \brief  Constructor.

      \param  man         tool manager, that will handle parsed data (must be != 0).
      \param  logger      message logger.

      In case of an error, throws MPEG2ParserException.
  */
  MPEG2IPMPXTStreamParser(IPMPToolManager* man, DRMLogger& logger): MPEG2IPMPXParser(man, logger) {
  }

  virtual ~MPEG2IPMPXTStreamParser() {
  }

  /*! \brief  Parse transport stream and call tool manager's handling routines.

      \warning  Input stream is modified in process.

      \param  stream        input, transport stream.

      \returns  Boolean indicating success or failure.
  */
  virtual bool ParseStream(ByteSeq& stream);
};

/*! \brief  MPEG2 program stream parser with IPMPX signalling.

    Parses data and calls handling routines.
*/
class MPEG2IPMPXPStreamParser: public MPEG2IPMPXParser {
public:
  /*! \brief  Constructor.

      \param  man         tool manager, that will handle parsed data (must be != 0).
      \param  logger      message logger.

      In case of an error, throws MPEG2ParserException.
  */
  MPEG2IPMPXPStreamParser(IPMPToolManager* man, DRMLogger& logger): MPEG2IPMPXParser(man, logger) {
  }

  virtual ~MPEG2IPMPXPStreamParser() {
  }

  /*! \brief  Parse program stream and call tool manager's handling routines.

      \warning  Input stream is modified in process.

      \param  stream        input, transport stream.

      \returns  Boolean indicating success or failure.
  */
  virtual bool ParseStream(ByteSeq& stream);
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (MPEG2IPMPXPARSER_H)
