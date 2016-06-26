/**	\file DecoderIPMPUserQuery.cpp

	User query and response messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "DecoderIPMPUserQuery.h"

#include "BasicTypes.h"
#include "IPMPData.h"
#include "IIPMPTerminal.h"
#include "IPMPUserQuery.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief  User query IPMP data.
*/

/*!	\brief  User query response IPMP data.
*/
/*! \brief  Using terminal, present query to the user and create response.

    \param  terminal      input, IPMP terminal.
    \param  response      output

    \returns  Boolean indicating success or failure.
*/
bool DecoderUserQueryIPMPData::Query(IIPMPTerminal* terminal,
    UserQueryResponseIPMPData** response) {

  std::vector<RTArray> responses;

  for (unsigned int i = 0; i < qtexts.size(); i++) {
    if (titleInd == true) {
      if (terminal->UserText(std::string(*(qtexts[i].GetTitle()))) == false) {
        return false;
      }
    }
    if (displayInd == true) {
      const std::vector<DTArray>& displays = qtexts[i].GetDisplays();
      for (unsigned int j = 0; j < displays.size(); j++) {
        if (terminal->UserText(std::string(displays[j].GetText())) == false) {
          return false;
        }
      }
    }
    if (queryInd == true) {
      const std::vector<QTArray>& queries = qtexts[i].GetQueries();
      for (unsigned int j = 0; j < queries.size(); j++) {
        std::string query = (std::string)(queries[j].GetPrompt());
        std::string resp;
        if (terminal->UserQA(query, resp) == false) {
          return false;
        }
        ByteSeq rresp(resp);
        responses.push_back(RTArray(queries[j].GetID(), queries[j].GetSubID(),
          rresp));
      }
    }
    /*  \todo: options and SMIL. Options specifications have a bunch of errors,
        so it needs to be checked.
    */
  }

  /*  Which language code to put, since we have an array of query texts, each
      one with it's language code.
  */
  *response = new DecoderUserQueryResponseIPMPData(version, dataID, queryInd,
    false, Bit24T(), responses, std::vector<bool>());

  return true;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
