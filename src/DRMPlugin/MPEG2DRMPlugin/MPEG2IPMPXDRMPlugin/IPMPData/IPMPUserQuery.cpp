/**	\file IPMPUserQuery.cpp

	User query and response messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "BasicTypes.h"
#include "IPMPData.h"
#include "IPMPUserQuery.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Display text.
*/
/*! \brief  Encode as byte array.

    \returns  Encoded byte array.
*/
ByteSeq DTArray::MPEG2Encode() const {
  return ByteSeq(identifier) + display.MPEG2Encode();
}

/*! \brief  Get text.

    \returns Text.
*/
const ByteSeq& DTArray::GetText() const {
  return display;
}

/*! \brief  Response text.
*/
/*! \brief  Encode as byte array.

    \returns  Encoded byte array.
*/
ByteSeq RTArray::MPEG2Encode() const {
  return ByteSeq(identifier) + ByteSeq(subidentifier) + prompt.MPEG2Encode();
}

/*! \brief  Get prompt.

    \returns  Prompt.
*/
const ByteSeq& RTArray::GetPrompt() const {
  return prompt;
}

/*! \brief  Query text.
*/
/*! \brief  Encode as byte array.

    \returns  Encoded byte array.
*/
ByteSeq QTArray::MPEG2Encode() const {
  return ByteSeq(identifier) + ByteSeq(subidentifier) +
    ByteSeq((ByteT)((hidden == true)? (0x80): (0))) + prompt.MPEG2Encode();
}

/*! \brief  Get identifier.

    \returns  Identifier.
*/
const Bit16T& QTArray::GetID() const {
  return identifier;
}

/*! \brief  Get subidentifier.

    \returns  Subidentifier.
*/
const Bit16T& QTArray::GetSubID() const {
  return subidentifier;
}

/*! \brief  Get prompt.

    \returns  Prompt.
*/
const ByteSeq& QTArray::GetPrompt() const {
  return prompt;
}

/*! \brief  Option text.
*/
/*! \brief  Encode as byte array.

    \returns  Encoded byte array.
*/
ByteSeq OptionArray::MPEG2Encode() const {
  return ByteSeq((ByteT)((exclusive == true)? (0x80): (0))) + ByteSeq(identifier) +
    ByteSeq(subidentifier) + prompt.MPEG2Encode();
}

/*! \brief  SMIL.
*/
/*! \brief  Encode as byte array.

    \returns  Encoded byte array.
*/
ByteSeq SMIL::MPEG2Encode() const {
  return ByteSeq((ByteT)((referenced == true)? (0x80): (0))) + smil.MPEG2Encode();
}

/*! \brief  User query text.
*/
/*! \brief  Get language code.

    \returns  Language code.
*/
const Bit24T& UserQueryText::GetLanguageCode() const {
  return language;
}

/*! \brief  Get title.

    \returns  Title.
*/
const ByteSeq* UserQueryText::GetTitle() const {
  return title;
}

/*! \brief  Get displays.

    \returns  Displays.
*/
const std::vector<DTArray>& UserQueryText::GetDisplays() const {
  return displays;
}

/*! \brief  Get queries.

    \returns  Queries.
*/
const std::vector<QTArray>& UserQueryText::GetQueries() const {
  return queries;
}

/*! \brief  Get options.

    \returns  Options.
*/
const std::vector<OptionArray>& UserQueryText::GetOptions() const {
  return options;
}

/*! \brief  Get SMIL.

    \returns  SMIL.
*/
const SMIL* UserQueryText::GetSMIL() const {
  return smil;
}

/*!	\brief  User query IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool UserQueryIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq tmp((Bit24T)qtexts.size());
  for (unsigned int i = 0; i < qtexts.size(); i++) {
    tmp += ByteSeq(qtexts[i].GetLanguageCode());
    if (titleInd == true) {
      tmp += qtexts[i].GetTitle()->MPEG2Encode();
    }
    if (displayInd == true) {
      if (qtexts[i].GetDisplays().size() > (1 << 8)) {
        return false;
      }
      tmp += (ByteT)(qtexts[i].GetDisplays().size());
      for (unsigned int j = 0; j < qtexts[i].GetDisplays().size(); j++) {
        tmp += qtexts[i].GetDisplays()[j].MPEG2Encode();
      }
    }
    if (queryInd == true) {
      if (qtexts[i].GetQueries().size() > (1 << 8)) {
        return false;
      }
      tmp += (ByteT)(qtexts[i].GetQueries().size());
      for (unsigned int j = 0; j < qtexts[i].GetQueries().size(); j++) {
        tmp += qtexts[i].GetQueries()[j].MPEG2Encode();
      }
    }
    if (optionInd == true) {
      if (qtexts[i].GetOptions().size() > (1 << 8)) {
        return false;
      }
      tmp += (ByteT)(qtexts[i].GetOptions().size());
      for (unsigned int j = 0; j < qtexts[i].GetOptions().size(); j++) {
        tmp += qtexts[i].GetOptions()[j].MPEG2Encode();
      }
    }
    if (smilInd == true) {
      tmp += qtexts[i].GetSMIL()->MPEG2Encode();
    }
  }
  ByteT ind = 0x0;
  ind |= ((titleInd == true)? (0x80): (0x0));
  ind |= ((displayInd == true)? (0x40): (0x0));
  ind |= ((queryInd == true)? (0x20): (0x0));
  ind |= ((optionInd == true)? (0x10): (0x0));
  ind |= ((smilInd == true)? (0x08): (0x0));

  return IPMPData::MPEG2Encode(0x0e, ByteSeq(ind) + tmp, encoded);
}

/*!	\brief  User query response IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool UserQueryResponseIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteT ind = 0x0;
  ind |= ((respInd == true)? (0x80): (0x0));
  ind |= ((optionsInd == true)? (0x40): (0x0));
  ByteSeq tmp(ind);
  tmp += ByteSeq(language);

  if (respInd == true) {
    if (responses.size() > (1 << 8)) {
      return false;
    }
    tmp += (ByteT)(responses.size());
    for (unsigned int j = 0; j < responses.size(); j++) {
      tmp += responses[j].MPEG2Encode();
    }
  }
  if (optionsInd == true) {
    if (options.size() > (1 << 16)) {
      return false;
    }
    tmp += ByteSeq((Bit16T)(options.size()));
    for (unsigned int j = 0; j < options.size(); j++) {
      tmp += (ByteT)((options[j] == true)? (0x80): (0x0));
    }
  }

  return IPMPData::MPEG2Encode(0x0f, tmp, encoded);
}

/*! \brief  Get responses.

    \returns  Responses.
*/
const std::vector<RTArray>& UserQueryResponseIPMPData::GetResponses() const {
  return responses;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
