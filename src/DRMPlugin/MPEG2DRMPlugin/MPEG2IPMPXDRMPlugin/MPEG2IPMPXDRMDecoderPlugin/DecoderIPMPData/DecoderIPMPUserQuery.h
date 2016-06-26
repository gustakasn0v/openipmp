/**	\file DecoderIPMPUserQuery.h

	User query and response messages with additional functionality for the
  decoder.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (DECODERIPMPUSERQUERY_H)
#define DECODERIPMPUSERQUERY_H

#include "BasicTypes.h"
#include "IPMPData.h"
#include "IIPMPTerminal.h"
#include "IPMPUserQuery.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief  User query response IPMP data.
*/
class DecoderUserQueryResponseIPMPData: public UserQueryResponseIPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       version.
      \param  id        data identifier.
      \param  rind      response include indicator.
      \param  oind      options include indicator.
      \param  lcode     language code.
      \param  resp      responses.
      \param  opt       options.

      If fails, throws IPMPDataException.
  */
  DecoderUserQueryResponseIPMPData(const ByteT& ver, const Bit32T& id,
    const bool& rind, const bool& oind, const Bit24T& lcode,
    const std::vector<RTArray>& resp, const std::vector<bool>& opt):
    UserQueryResponseIPMPData(ver, id, rind, oind, lcode, resp, opt) {
  }

  virtual ~DecoderUserQueryResponseIPMPData() {
  }
};

/*!	\brief  Decoder user query IPMP data.

    Communicates with user via IPMP terminal and creates response.
*/
class DecoderUserQueryIPMPData: public UserQueryIPMPData {
public:
  /*! \brief  Dummy constructor. SHOULD NOT BE USED.
  
      Needed cause std::map needs default constructor.
  */
  DecoderUserQueryIPMPData(): UserQueryIPMPData() {
  }

  /*! \brief  Constructor.
      
      \param  ver       version.
      \param  id        data identifier.
      \param  tind      title include indicator.
      \param  dind      display include indicator.
      \param  qind      query include indicator.
      \param  oind      options include indicator.
      \param  sind      SMIL include indicator.
      \param  texts     query texts.

      If fails, throws IPMPDataException.
  */
  DecoderUserQueryIPMPData(const ByteT& ver, const Bit32T& id, const bool& tind,
    const bool& dind, const bool& qind, const bool& oind, const bool& sind,
    const std::vector<UserQueryText>& texts): UserQueryIPMPData(ver, id, tind,
    dind, qind, oind, sind, texts) {
  }

  /*! \brief  Copy constructor.
      
      \param  rhs       user query.

      If fails, throws IPMPDataException.
  */
  DecoderUserQueryIPMPData(const DecoderUserQueryIPMPData& rhs):
    UserQueryIPMPData(rhs.version, rhs.dataID, rhs.titleInd, rhs.displayInd,
    rhs.queryInd, rhs.optionInd, rhs.smilInd, rhs.qtexts) {
  }

  virtual ~DecoderUserQueryIPMPData() {
  }

  /*! \brief  Using terminal, present query to the user and create response.

      \param  terminal      input, IPMP terminal.
      \param  response      output

      \returns  Boolean indicating success or failure.
  */
  bool Query(IIPMPTerminal* terminal, UserQueryResponseIPMPData** response);
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (DECODERIPMPUSERQUERY_H)
