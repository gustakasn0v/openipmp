/**	\file IPMPDataParser.cpp

	IPMP data parser.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "IPMPDataParser.h"

#include "BasicTypes.h"
#include "IPMPAgent.h"
#include <string>
#include "IPMPData.h"
#include "SecureContainerData.h"
#include "IPMPUserQuery.h"
#include "AuthenticationData.h"
#include "CryptoContext.h"
#include "IPMPMessage.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Parser of IPMP data messages.

    Used for parsing IPMP data messages and returning parsed messages to callers.
*/
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
bool IPMPDataParser::ParseMessage(const Bit32T& sender, ByteSeq& encoded,
    IPMPAgent* agent, ByteSeq& resp) {
  try {
    ByteT tag = encoded.GetByte();
    ByteSeq data(encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0xfffffff))));
    switch (tag) {
    case 0x01:
      //  Opaque data.
      if (agent->HandleOpaqueIPMPData(sender, ParseOpaqueData(data), resp) == false) {
        return false;
      }
      break;
    case 0x08:
      //  Rights data.
      if (agent->HandleRightsIPMPData(sender, ParseRightsData(data), resp) == false) {
        return false;
      }
      break;
    case 0x09:
      //  Secure container.
      if (agent->HandleSecureContainerIPMPData(sender, ParseSecureContainer(data), resp) == false) {
        return false;
      }
      break;
    case 0x0c:
      //  Init authentication.
      if (agent->HandleInitAuthenticationIPMPData(sender, ParseInitAuthentication(data), resp) == false) {
        return false;
      }
      break;
    case 0x0d:
      //  Mutual authentication.
      if (agent->HandleMutualAuthenticationIPMPData(sender, ParseMutualAuthentication(data), resp) == false) {
        return false;
      }
      break;
    case 0x17:
      //  Can process.
      if (agent->HandleCanProcessIPMPData(sender, ParseCanProcess(data), resp) == false) {
        return false;
      }
      break;
    case 0x0e:
      //  User query.
      if (agent->HandleUserQueryIPMPData(sender, ParseUserQueryData(data), resp) == false) {
        return false;
      }
      break;
    case 0x0f:
      //  User response.
      if (agent->HandleUserQueryResponseIPMPData(sender, ParseUserQueryResponseData(data), resp) == false) {
        return false;
      }
      break;
    default:
      return false;
    }
    return true;
  }
  catch (ByteSeqException) {
    return false;
  }
  catch (IPMPDataException) {
    return false;
  }
  catch (IPMPDataParserException) {
    return false;
  }
//  catch (...) {
//    return false;
//  }
}

/*! \brief  Parse user query IPMP data message.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPDataException.

    \param  encoded   input, encoded message.

    \returns  User query IPMP data message.
*/
DecoderUserQueryIPMPData* IPMPDataParser::ParseUserQueryData(ByteSeq& encoded) {
  //  Get version.
  ByteT version = encoded.GetByte();
  //  Get data identifier.
  Bit32T dataID = encoded.GetBit32();
  ByteT tmp = encoded.GetByte();
  bool titleInd = ((tmp & 0x80) == 0)? (false): (true);
  bool displayInd = ((tmp & 0x40) == 0)? (false): (true);
  bool queryInd = ((tmp & 0x20) == 0)? (false): (true);
  bool optionInd = ((tmp & 0x10) == 0)? (false): (true);
  bool smilInd = ((tmp & 0x08) == 0)? (false): (true);
  if ((tmp & 0x7) != 0) {
    throw IPMPDataParserException();
  }
  Bit24T numAlt = encoded.GetBit24();
  std::vector<UserQueryText> qtexts;
  for (unsigned int i = 0; i < (UInt32T)numAlt; i++) {
    Bit24T language = encoded.GetBit24();
    ByteSeq* title = 0;
    std::vector<DTArray> displays;
    std::vector<QTArray> queries;
    std::vector<OptionArray> options;
    SMIL* smil = 0;
    if (titleInd == true) {
      title = new ByteSeq(encoded.GetBytes((UInt32T)encoded.GetSizeOfInstance(0)));
    }
    if (displayInd == true) {
      tmp = encoded.GetByte();
      while (tmp > 0) {
        //  Parse display.
        Bit16T identifier = encoded.GetBit16();
        ByteSeq display(encoded.GetBytes((UInt32T)encoded.GetSizeOfInstance(0)));
        displays.push_back(DTArray(identifier, display));
        tmp--;
      }
    }
    if (queryInd == true) {
      tmp = encoded.GetByte();
      while (tmp > 0) {
        //  Parse query.
        Bit16T identifier = encoded.GetBit16();
        Bit16T subidentifier = encoded.GetBit16();
        bool hidden = ((encoded.GetByte() & 0x80) == 0)? (false): (true);
        ByteSeq prompt(encoded.GetBytes((UInt32T)encoded.GetSizeOfInstance(0)));
        queries.push_back(QTArray(identifier, subidentifier, hidden, prompt));
        tmp--;
      }
    }
    if (optionInd == true) {
      tmp = encoded.GetByte();
      while (tmp > 0) {
        //  Parse option.
        bool exclusive = ((encoded.GetByte() & 0x80) == 0)? (false): (true);
        Bit16T identifier = encoded.GetBit16();
        Bit16T subidentifier = encoded.GetBit16();
        ByteSeq prompt(encoded.GetBytes((UInt32T)encoded.GetSizeOfInstance(0)));
        options.push_back(OptionArray(exclusive, identifier, subidentifier, prompt));
        tmp--;
      }
    }
    if (smilInd == true) {
      //  Parse SMIL.
      bool referenced = ((encoded.GetByte() & 0x80) == 0)? (false): (true);
      ByteSeq data(encoded.GetBytes((UInt32T)encoded.GetSizeOfInstance(0)));
      smil = new SMIL(referenced, data);
      tmp--;
    }

    //  Save new user query text.
    qtexts.push_back(UserQueryText(language, title, displays, queries, options, smil));
    if (title != 0) delete title;
    if (smil != 0) delete smil;
  }

  return new DecoderUserQueryIPMPData(version, dataID, titleInd, displayInd,
    queryInd, optionInd, smilInd, qtexts);
}

/*! \brief  Parse user response IPMP data message.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPDataException.

    \param  encoded   input, encoded message.

    \returns  User response IPMP data message.
*/
DecoderUserQueryResponseIPMPData* IPMPDataParser::ParseUserQueryResponseData(ByteSeq& encoded) {
  //  Get version.
  ByteT version = encoded.GetByte();
  //  Get data identifier.
  Bit32T dataID = encoded.GetBit32();
  ByteT tmp = encoded.GetByte();
  bool respInd = ((tmp & 0x80) == 0)? (false): (true);
  bool optionInd = ((tmp & 0x40) == 0)? (false): (true);
  if ((tmp & 0x3f) != 0) {
    throw IPMPDataParserException();
  }
  Bit24T language = encoded.GetBit24();
  std::vector<RTArray> responses;
  std::vector<bool> options;

  if (respInd == true) {
    tmp = encoded.GetByte();
    while (tmp > 0) {
      //  Parse response.
      Bit16T identifier = encoded.GetBit16();
      Bit16T subidentifier = encoded.GetBit16();
      ByteSeq prompt(encoded.GetBytes((UInt32T)encoded.GetSizeOfInstance(0)));
      responses.push_back(RTArray(identifier, subidentifier, prompt));
      tmp--;
    }
  }
  if (optionInd == true) {
    Bit16T tmp16 = encoded.GetBit16();
    while (tmp16 > 0) {
      //  Parse option.
      options.push_back(((encoded.GetByte() & 0x80) == 0)? (false): (true));
      tmp16--;
    }
  }

  return new DecoderUserQueryResponseIPMPData(version, dataID, respInd, optionInd,
    language, responses, options);
}

/*! \brief  Parse opaque IPMP data message.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPDataException.

    \param  encoded   input, encoded message.

    \returns  Opaque IPMP data message.
*/
OpaqueIPMPData* IPMPDataParser::ParseOpaqueData(ByteSeq& encoded) {
  //  Get version.
  ByteT version = encoded.GetByte();
  //  Get data identifier.
  Bit32T dataID = encoded.GetBit32();
  //  Get opaque data.
  ByteSeq opaque = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
  return new OpaqueIPMPData(version, dataID, opaque);
}

/*! \brief  Parse IPMP rights data message.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPDataException.

    \param  encoded   input, encoded message.

    \returns  IPMP rights data message.
*/
RightsIPMPData* IPMPDataParser::ParseRightsData(ByteSeq& encoded) {
  //  Get version.
  ByteT version = encoded.GetByte();
  //  Get data identifier.
  Bit32T dataID = encoded.GetBit32();
  //  Get rights data.
  ByteSeq rights = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
  return new RightsIPMPData(version, dataID, rights);
}

/*! \brief  Parse IPMP secure container message.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPDataException.

    \param  encoded   input, encoded message.

    \returns  IPMP secure container message.
*/
SecureContainerIPMPData* IPMPDataParser::ParseSecureContainer(ByteSeq& encoded) {
  //  Get version.
  ByteT version = encoded.GetByte();
  //  Get data identifier.
  Bit32T dataID = encoded.GetBit32();
  //  Get flags.
  ByteT tmp = encoded.GetByte();
  bool hasEncryption = ((tmp & 0x80) == 0)? (false): (true);
  bool hasMAC = ((tmp & 0x40) == 0)? (false): (true);
  bool isMACEncrypted = ((tmp & 0x20) == 0)? (false): (true);
  //  Sanity check.
  if ((!hasMAC && isMACEncrypted) || (!hasEncryption && isMACEncrypted)) {
    throw IPMPDataParserException();
  }
  if (hasEncryption) {
    ByteSeq encrypted = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
    if (hasMAC && !isMACEncrypted) {
      ByteSeq mac = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
      return new MACEncSecureContainerIPMPData(version, dataID, encrypted, mac, parserLogger);
    } else if (!hasMAC) {
      return new NMACEncSecureContainerIPMPData(version, dataID, encrypted, parserLogger);
    } else { // if (isMACEncrypted)
      return new EncMACEncSecureContainerIPMPData(version, dataID, encrypted, parserLogger);
    }
  } else {
    ByteSeq plain = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
    if (hasMAC) {
      ByteSeq mac = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
      return new MACNEncSecureContainerIPMPData(version, dataID, plain, mac, parserLogger);
    } else {
      return new NMACNEncSecureContainerIPMPData(version, dataID, plain, parserLogger);
    }
  }
}

/*! \brief  Parse IPMP init authentication message.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPDataException.

    \param  encoded   input, encoded message.

    \returns  IPMP init authentication message.
*/
InitAuthenticationIPMPData* IPMPDataParser::ParseInitAuthentication(ByteSeq& encoded) {
  //  Get version.
  ByteT version = encoded.GetByte();
  //  Get data identifier.
  Bit32T dataID = encoded.GetBit32();
  //  Get IPMP descriptor identifier.
  Bit32T ipmpDescriptorID = encoded.GetBit32();
  //  Get authentication type.
  ByteT authType = encoded.GetByte();
  return new InitAuthenticationIPMPData(version, dataID, ipmpDescriptorID, authType);
}

/*! \brief  Parse IPMP mutual authentication message.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPDataException.

    \param  encoded   input, encoded message.

    \returns  IPMP mutual authentication message.
*/
MutualAuthenticationIPMPData* IPMPDataParser::ParseMutualAuthentication(ByteSeq& encoded) {
  //  Get version.
  ByteT version = encoded.GetByte();
  //  Get data identifier.
  Bit32T dataID = encoded.GetBit32();
  //  Get flags.
  ByteT tmp = encoded.GetByte();

  bool requestNegotiation = ((tmp & 0x80) == 0)? (false): (true);
  bool successNegotiation =  ((tmp & 0x40) == 0)? (false): (true);
  bool failedNegotiation =  ((tmp & 0x20) == 0)? (false): (true);
  bool inclAuthenticationData =  ((tmp & 0x10) == 0)? (false): (true);
  bool inclAuthCodes =  ((tmp & 0x08) == 0)? (false): (true);

  ByteSeq tmpArray;
  std::vector<AlgorithmDescriptor*> candidate;
  std::vector<AlgorithmDescriptor*> agreed;
  ByteSeq authenticationData;
  AuthCodes* codes = 0;
  try {
    if (requestNegotiation) {
      //  Get number of candidate algorithms.
      tmp = encoded.GetByte();
      while (tmp > 0) {
        //  Get encoded algorithm descriptor data.
        if (encoded.GetByte() != 0x01) {
          throw IPMPDataParserException();
        }
        tmpArray = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0xfffffff)));
        candidate.push_back(ParseAlgorithmDescriptor(tmpArray));
        tmp--;
      }
    }
    if (successNegotiation) {
      //  Get number of agreed algorithms.
      tmp = encoded.GetByte();
      while (tmp > 0) {
        //  Get encoded algorithm descriptor data.
        if (encoded.GetByte() != 0x01) {
          throw IPMPDataParserException();
        }
        tmpArray = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0xfffffff)));
        agreed.push_back(ParseAlgorithmDescriptor(tmpArray));
        tmp--;
      }
    }
    if (inclAuthenticationData) {
      authenticationData = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
    }
    if (inclAuthCodes) {
      tmp = encoded.GetByte();
      if (tmp == 0x01) {
        //  Parse certificates.
        ByteT nCert = encoded.GetByte();
        ByteT certType = encoded.GetByte();
        std::vector<ByteSeq> certs;
        while (nCert > 0) {
          certs.push_back(encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0))));
          nCert--;
        }
        //  Parse trust security metadata.
        if (encoded.GetByte() != 0x18) {
          throw IPMPDataParserException();
        }
        tmpArray = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0xfffffff)));
        TrustSecurityMetadataIPMPData* trustData = ParseTrustSecurityMetadata(tmpArray);
        tmpArray = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
        PublicAuthContext* context = new CertPublicAuthContext(
          std::vector<AlgorithmDescriptor*>(),trustData, certType, certs);
        codes = new AuthCodes(context, tmpArray);
      } else if (tmp == 0x02) {
        if (encoded.GetByte() != 0x02) {
          throw IPMPDataParserException();
        }
        tmpArray = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0xfffffff)));
        KeyDescriptor descriptor = ParseKeyDescriptor(tmpArray);
        //  Parse trust security metadata.
        if (encoded.GetByte() != 0x18) {
          throw IPMPDataParserException();
        }
        tmpArray = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0xfffffff)));
        TrustSecurityMetadataIPMPData* trustData = ParseTrustSecurityMetadata(tmpArray);
        tmpArray = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
        PublicAuthContext* context = new KeyPublicAuthContext(
          std::vector<AlgorithmDescriptor*>(), trustData, descriptor);
        codes = new AuthCodes(context, tmpArray);
      } else if (tmp = 0xfe) {
        //  Parse opaque.
        ByteSeq opaque = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
        //  Parse trust security metadata.
        if (encoded.GetByte() != 0x18) {
          throw IPMPDataParserException();
        }
        tmpArray = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0xfffffff)));
        TrustSecurityMetadataIPMPData* trustData = ParseTrustSecurityMetadata(tmpArray);
        tmpArray = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
        PublicAuthContext* context = new OpaquePublicAuthContext(
          std::vector<AlgorithmDescriptor*>(), trustData, opaque);
        codes = new AuthCodes(context, tmpArray);
      } else {
        throw IPMPDataParserException();
      }
    }
  }
  catch (ByteSeqException) {
    ClearVector(candidate);
    ClearVector(agreed);
    if (codes != 0) delete codes;
    throw ByteSeqException();
  }
  catch (IPMPDataParserException) {
    ClearVector(candidate);
    ClearVector(agreed);
    if (codes != 0) delete codes;
    throw IPMPDataParserException();
  }

  if (authenticationData.GetLength() > 0) {
    return new MutualAuthenticationIPMPData(version, dataID, failedNegotiation,
      candidate, agreed, authenticationData, codes);
  } else {
    return new MutualAuthenticationIPMPData(version, dataID, failedNegotiation,
      candidate, agreed, codes);
  }
}

/*! \brief  Parse IPMP can process message.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPDataException.

    \param  encoded   input, encoded message.

    \returns  IPMP can process message.
*/
CanProcessIPMPData* IPMPDataParser::ParseCanProcess(ByteSeq& encoded) {
  //  Get version.
  ByteT version = encoded.GetByte();
  //  Get data identifier.
  Bit32T dataID = encoded.GetBit32();
  //  Get process flag.
  ByteT process = encoded.GetByte();
  return new CanProcessIPMPData(version, dataID, ((process & 0x80) == 0)? (false): (true));
}

/*! \brief  Parse algorithm descriptor.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPDataException.

    \param  encoded     input, encoded data.

    \returns  Algorithm descriptor.
*/
AlgorithmDescriptor* IPMPDataParser::ParseAlgorithmDescriptor(ByteSeq& encoded) {
  //  Get registered flag.
  ByteT tmp = encoded.GetByte();
  bool isRegistered = ((tmp & 0x80) == 0)? (false): (true);
  if (isRegistered) {
    //  Get registered algorithm identifier.
    Bit16T regAlgoID = encoded.GetBit16();
    //  Get opaque data.
    ByteSeq opaque = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
    return new RegAlgorithmDescriptor(opaque, regAlgoID);
  } else {
    //  Get special algorithm identifier.
    ByteSeq specAlgoID = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
    //  Get opaque data.
    ByteSeq opaque = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
    return new NRegAlgorithmDescriptor(opaque, specAlgoID);
  }
}

/*! \brief  Parse key descriptor.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPDataException.

    \param  encoded     input, encoded data.

    \returns  Key descriptor.
*/
KeyDescriptor IPMPDataParser::ParseKeyDescriptor(ByteSeq& encoded) {
  ByteSeq keyBody = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
  return KeyDescriptor(keyBody);
}

/*! \brief  Parse trust security metadata.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPDataException.

    \param  encoded     input, encoded data.

    \returns  Trust security metadata.
*/
TrustSecurityMetadataIPMPData* IPMPDataParser::ParseTrustSecurityMetadata(ByteSeq&
    encoded) {
  //  Get version.
  ByteT version = encoded.GetByte();
  //  Get data identifier.
  Bit32T dataID = encoded.GetBit32();
  //  Currently we do not parse full trust security metadata.
  return new TrustSecurityMetadataIPMPData(version, dataID);
}

/*! \brief  Clear vector (used in case of an error).

    \param  vec       input-output, vector to be cleared.
*/
void IPMPDataParser::ClearVector(std::vector<AlgorithmDescriptor*>& vec) {
  for (unsigned int i = 0; i < vec.size(); i++) {
    if (vec[i] != 0) delete vec[i];
  }
  vec.clear();
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
