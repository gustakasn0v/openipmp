/**	\file IPMPDataParser.h

	IPMP data parser.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPMPDATAPARSER_H)
#define IPMPDATAPARSER_H

#include "BasicTypes.h"
#include "IPMPAgent.h"
#include <string>
#include "AuthenticationData.h"
#include "CryptoContext.h"
#include "IPMPData.h"
#include "SecureContainerData.h"
#include "DecoderIPMPUserQuery.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  IPMP data parser exception.
*/
class IPMPDataParserException {
};

/*! \brief  Parser of IPMP data messages.

    Used for parsing IPMP data messages and returning parsed messages to callers.
*/
class IPMPDataParser {
public:
  /*!  \brief  Constructor.

      \param  logger      message logger.
  */
  IPMPDataParser(DRMLogger& logger): parserLogger(logger) {
  }

  ~IPMPDataParser() {
  }

  /*! \brief  Parse IPMP data message, call handling function and return it's
              response.

      \warning  Encoded data is modified during parsing.
      \warning  Response can be empty, depending on whether any response is
                needed and whether an error occured during the processing.

      \param  sender    input, sender's code.
      \param  encoded   input, encoded message.
      \param  agent     input, IPMP agent which will handle parsed message.
      \param  resp      output, response message data.

      \returns  Boolean indicating success or failure.
  */
  bool ParseMessage(const Bit32T& sender, ByteSeq& encoded, IPMPAgent* agent,
    ByteSeq& resp);

protected:
  /*! \brief  Parse user query IPMP data message.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPDataException.

      \param  encoded   input, encoded message.

      \returns  User query IPMP data message.
  */
  DecoderUserQueryIPMPData* ParseUserQueryData(ByteSeq& encoded);

  /*! \brief  Parse user response IPMP data message.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPDataException.

      \param  encoded   input, encoded message.

      \returns  User response IPMP data message.
  */
  DecoderUserQueryResponseIPMPData* ParseUserQueryResponseData(ByteSeq& encoded);

  /*! \brief  Parse opaque IPMP data message.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPDataException.

      \param  encoded   input, encoded message.

      \returns  Opaque IPMP data message.
  */
  OpaqueIPMPData* ParseOpaqueData(ByteSeq& encoded);

  /*! \brief  Parse IPMP rights data message.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPDataException.

      \param  encoded   input, encoded message.

      \returns  IPMP rights data message.
  */
  RightsIPMPData* ParseRightsData(ByteSeq& encoded);

  /*! \brief  Parse IPMP secure container message.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPDataException.

      \param  encoded   input, encoded message.

      \returns  IPMP secure container message.
  */
  SecureContainerIPMPData* ParseSecureContainer(ByteSeq& encoded);

  /*! \brief  Parse IPMP init authentication message.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPDataException.

      \param  encoded   input, encoded message.

      \returns  IPMP init authentication message.
  */
  InitAuthenticationIPMPData* ParseInitAuthentication(ByteSeq& encoded);

  /*! \brief  Parse IPMP mutual authentication message.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPDataException.

      \param  encoded   input, encoded message.

      \returns  IPMP mutual authentication message.
  */
  MutualAuthenticationIPMPData* ParseMutualAuthentication(ByteSeq& encoded);

  /*! \brief  Parse IPMP can process message.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPDataException.

      \param  encoded   input, encoded message.

      \returns  IPMP can process message.
  */
  CanProcessIPMPData* ParseCanProcess(ByteSeq& encoded);

  /*! \brief  Parse algorithm descriptor.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPDataException.

      \param  encoded     input, encoded data.

      \returns  Algorithm descriptor.
  */
  AlgorithmDescriptor* ParseAlgorithmDescriptor(ByteSeq& encoded);

  /*! \brief  Parse key descriptor.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPDataException.

      \param  encoded     input, encoded data.

      \returns  Key descriptor.
  */
  KeyDescriptor ParseKeyDescriptor(ByteSeq& encoded);

  /*! \brief  Parse trust security metadata.

      \warning  Encoded data is modified during parsing.
      \warning  In case of an error, throws either ByteSeqException or
                IPMPDataException.

      \param  encoded     input, encoded data.

      \returns  Trust security metadata.
  */
  TrustSecurityMetadataIPMPData* ParseTrustSecurityMetadata(ByteSeq& encoded);

  /*! \brief  Clear vector (used in case of an error).

      \param  vec       input-output, vector to be cleared.
  */
  void ClearVector(std::vector<AlgorithmDescriptor*>& vec);

private:
  DRMLogger& parserLogger;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (IPMPDATAPARSER_H)
