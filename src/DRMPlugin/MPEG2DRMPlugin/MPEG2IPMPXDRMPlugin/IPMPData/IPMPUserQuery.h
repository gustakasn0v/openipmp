/**	\file IPMPUserQuery.h

	User query and response messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPMPUSERQUERY_H)
#define IPMPUSERQUERY_H

#include "BasicTypes.h"
#include "IPMPData.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Display text.
*/
class DTArray {
public:
  /*! \brief  Constructor.

      \param  id        identifier.
      \param  dtext     display text.
  */
  DTArray(const Bit16T& id, const ByteSeq& dtext): identifier(id), display(dtext) {
  }

  /*! \brief  Copy constructor.

      \param  rhs       display text.
  */
  DTArray(const DTArray& rhs): identifier(rhs.identifier), display(rhs.display) {
  }

  /*! \brief  Encode as byte array.
  
      \returns  Encoded byte array.
  */
  ByteSeq MPEG2Encode() const;

  /*! \brief  Get text.

      \returns Text.
  */
  const ByteSeq& GetText() const;

private:
  Bit16T identifier;
  ByteSeq display;
};

/*! \brief  Response text.
*/
class RTArray {
public:
  /*! \brief  Constructor.

      \param  id        identifier.
      \param  sub       subidentifier.
      \param  ptext     prompt text.
  */
  RTArray(const Bit16T& id, const Bit16T& sub, const ByteSeq& ptext): identifier(id),
    subidentifier(sub), prompt(ptext) {
  }

  /*! \brief  Copy constructor.

      \param  rhs       response text.
  */
  RTArray(const RTArray& rhs): identifier(rhs.identifier),
    subidentifier(rhs.subidentifier), prompt(rhs.prompt) {
  }

  /*! \brief  Encode as byte array.
  
      \returns  Encoded byte array.
  */
  ByteSeq MPEG2Encode() const;

  /*! \brief  Get prompt.

      \returns  Prompt.
  */
  const ByteSeq& GetPrompt() const;

private:
  Bit16T identifier;
  Bit16T subidentifier;
  ByteSeq prompt;
};

/*! \brief  Query text.
*/
class QTArray {
public:
  /*! \brief  Constructor.

      \param  id        identifier.
      \param  sub       subidentifier.
      \param  hid       hidden indicator.
      \param  ptext     prompt text.
  */
  QTArray(const Bit16T& id, const Bit16T& sub, const bool& hid, const ByteSeq& ptext):
    identifier(id), subidentifier(sub), hidden(hid), prompt(ptext) {
  }

  /*! \brief  Constructor.

      \param  rhs       query text.
  */
  QTArray(const QTArray& rhs): identifier(rhs.identifier),
    subidentifier(rhs.subidentifier), hidden(rhs.hidden), prompt(rhs.prompt) {
  }

  /*! \brief  Encode as byte array.
  
      \returns  Encoded byte array.
  */
  ByteSeq MPEG2Encode() const;

  /*! \brief  Get identifier.

      \returns  Identifier.
  */
  const Bit16T& GetID() const;

  /*! \brief  Get subidentifier.

      \returns  Subidentifier.
  */
  const Bit16T& GetSubID() const;

  /*! \brief  Get prompt.

      \returns  Prompt.
  */
  const ByteSeq& GetPrompt() const;

private:
  Bit16T identifier;
  Bit16T subidentifier;
  bool hidden;
  ByteSeq prompt;
};

/*! \brief  Option text.
*/
class OptionArray {
public:
  /*! \brief  Constructor.

      \param  exc       exclusive indicator.
      \param  id        identifier.
      \param  sub       subidentifier.
      \param  ptext     prompt text.
  */
  OptionArray(const bool& exc, const Bit16T& id, const Bit16T& sub, const ByteSeq& ptext):
    exclusive(exc), identifier(id), subidentifier(sub), prompt(ptext) {
  }

  /*! \brief  Copy constructor.

      \param  rhs       option text.
  */
  OptionArray(const OptionArray& rhs): exclusive(rhs.exclusive),
    identifier(rhs.identifier), subidentifier(rhs.subidentifier), prompt(rhs.prompt) {
  }

  /*! \brief  Encode as byte array.
  
      \returns  Encoded byte array.
  */
  ByteSeq MPEG2Encode() const;

private:
  bool exclusive;
  Bit16T identifier;
  Bit16T subidentifier;
  ByteSeq prompt;
};

/*! \brief  SMIL.
*/
class SMIL {
public:
  /*! \brief  Constructor.

      \param  ref       referenced indicator.
      \param  data      SMIL data.
  */
  SMIL(const bool& ref, const ByteSeq& data): referenced(ref), smil(data) {
  }

  /*! \brief  Copy constructor.

      \param  rhs       SMIL.
  */
  SMIL(const SMIL& rhs): referenced(rhs.referenced), smil(rhs.smil) {
  }

  /*! \brief  Encode as byte array.
  
      \returns  Encoded byte array.
  */
  ByteSeq MPEG2Encode() const;

private:
  bool referenced;
  ByteSeq smil;
};

/*! \brief  User query text.
*/
class UserQueryText {
public:
  /*! \brief  Constructor.

      \param  lcode       language code.
      \param  ttext       title text.
      \param  dtexts      display texts.
      \param  qtexts      query texts.
      \param  otexts      option texts.
      \param  sm          SMIL.
  */
  UserQueryText(const Bit24T& lcode, ByteSeq* ttext, const std::vector<DTArray>& dtexts,
    const std::vector<QTArray>& qtexts, const std::vector<OptionArray>& otexts,
    SMIL* sm): language(lcode), title(ttext), displays(dtexts), queries(qtexts),
    options(otexts), smil(sm) {
  }

  /*! \brief  Copy constructor.

      \param  rhs         user query text.
  */
  UserQueryText(const UserQueryText& rhs): language(rhs.language), title(0),
      displays(rhs.displays), queries(rhs.queries), options(rhs.options), smil(0) {
    if (rhs.title != 0) {
      title = new ByteSeq(*(rhs.title));
    }
    if (rhs.smil != 0) {
      smil = new SMIL(*(rhs.smil));
    }
  }

  ~UserQueryText() {
    if (title != 0) delete title; title = 0;
    if (smil != 0) delete smil; smil = 0;
  }

  /*! \brief  Get language code.

      \returns  Language code.
  */
  const Bit24T& GetLanguageCode() const;

  /*! \brief  Get title.

      \returns  Title.
  */
  const ByteSeq* GetTitle() const;

  /*! \brief  Get displays.

      \returns  Displays.
  */
  const std::vector<DTArray>& GetDisplays() const;

  /*! \brief  Get queries.

      \returns  Queries.
  */
  const std::vector<QTArray>& GetQueries() const;

  /*! \brief  Get options.

      \returns  Options.
  */
  const std::vector<OptionArray>& GetOptions() const;

  /*! \brief  Get SMIL.

      \returns  SMIL.
  */
  const SMIL* GetSMIL() const;

private:
  Bit24T language;
  ByteSeq* title;
  std::vector<DTArray> displays;
  std::vector<QTArray> queries;
  std::vector<OptionArray> options;
  SMIL* smil;
};

/*!	\brief  User query IPMP data.
*/
class UserQueryIPMPData: public IPMPData {
public:
  /*! \brief  Dummy constructor. SHOULD NOT BE USED.
  
      Needed cause std::map needs default constructor.
  */
  UserQueryIPMPData(): IPMPData(0, 0), titleInd(false), displayInd(false),
    queryInd(false), optionInd(false), smilInd(false), qtexts() {
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
  UserQueryIPMPData(const ByteT& ver, const Bit32T& id, const bool& tind,
      const bool& dind, const bool& qind, const bool& oind, const bool& sind,
      const std::vector<UserQueryText>& texts): IPMPData(ver, id), titleInd(tind),
      displayInd(dind), queryInd(qind), optionInd(oind), smilInd(sind), qtexts(texts) {
    //  Consistency check.
    for (unsigned int i = 0; i < qtexts.size(); i++) {
      if (titleInd == true) {
        if (qtexts[i].GetTitle() == 0) {
          throw IPMPDataException();
        }
      } else {
        if (qtexts[i].GetTitle() != 0) {
          throw IPMPDataException();
        }
      }
      if (smilInd == true) {
        if (qtexts[i].GetSMIL() == 0) {
          throw IPMPDataException();
        }
      } else {
        if (qtexts[i].GetSMIL() != 0) {
          throw IPMPDataException();
        }
      }
    }
  }

  virtual ~UserQueryIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

protected:
  bool titleInd;
  bool displayInd;
  bool queryInd;
  bool optionInd;
  bool smilInd;
  std::vector<UserQueryText> qtexts;
};

/*!	\brief  User query response IPMP data.
*/
class UserQueryResponseIPMPData: public IPMPData {
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
  UserQueryResponseIPMPData(const ByteT& ver, const Bit32T& id, const bool& rind,
      const bool& oind, const Bit24T& lcode, const std::vector<RTArray>& resp, 
      const std::vector<bool>& opt): IPMPData(ver, id), respInd(rind), optionsInd(oind),
      language(lcode), responses(resp), options(opt) {
    //  Consistency check.
    if ((respInd == false) && (responses.size() > 0)) {
      throw IPMPDataException();
    }
    if ((optionsInd == false) && (options.size() > 0)) {
      throw IPMPDataException();
    }
  }

  virtual ~UserQueryResponseIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Get responses.

      \returns  Responses.
  */
  const std::vector<RTArray>& GetResponses() const;

protected:
  bool respInd;
  bool optionsInd;
  Bit24T language;
  std::vector<RTArray> responses;
  std::vector<bool> options;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (IPMPUSERQUERY_H)
