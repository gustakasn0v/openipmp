/**	\file IIPMPTerminal.h

	IPMP terminal, used for user/IPMP tool manager communication.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IIPMPTERMINAL_H)
#define IIPMPTERMINAL_H

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  IPMP terminal.

    Used for user/IPMP tool manager communication.
*/
class IIPMPTerminal {
public:
  virtual ~IIPMPTerminal() {
  }

  /*! \brief  User text.

      \param  text          input, text to be presented to the user.
      
      \returns Boolean indicating success or failure.
  */
  virtual bool UserText(const std::string& text) = 0;

  /*! \brief  User query/response.

      \param  query         input, user query.
      \param  response      output, user response.
      
      \returns Boolean indicating success or failure.
  */
  virtual bool UserQA(const std::string& query, std::string& response) = 0;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (IIPMPTERMINAL_H)
