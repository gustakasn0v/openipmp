/** \file IOMADRMDecAgent.h

    Interfaces for agent handling OMA DRM device messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (IOMADRMDECAGENT_H)
#define IOMADRMDECAGENT_H

#include "ROAPMessages.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Agent handling OMA DRM device messages.
*/
class IOMADRMDecAgent: public GC  {
public:
  /*! \brief  Handle successful rights issuer hello message.

      \param  response            input, successful rights issuer hello message.

      \returns  Registration request. If zero, failed.
  */
  virtual SPtr<RegRequest> HandleSuccessRIHello(const NZSPtr<SuccessRIHello>& response) = 0;

  /*! \brief  Handle unsuccessful rights issuer hello message.

      \param  response            input, unsuccessful rights issuer hello message.
  */
  virtual void HandleUnsuccessRIHello(const NZSPtr<UnsuccessRIHello>& response) = 0;

  /*! \brief  Handle successful registration response message.

      \param  response            input, successful registration response message.
  */
  virtual void HandleSuccessRegResponse(const NZSPtr<SuccessRegResponse>& response) = 0;

  /*! \brief  Handle unsuccessful registration response message.

      \param  response            input, unsuccessful registration response message.
  */
  virtual void HandleUnsuccessRegResponse(const NZSPtr<UnsuccessRegResponse>& response) = 0;

  /*! \brief  Handle successful 2-pass rights objects response message.

      \param  response            input, successful 2-pass rights objects response
                                  message.
  */
  virtual void HandleSuccessROResponse(const NZSPtr<SuccessTwoPassROResponse>& response) = 0;

  /*! \brief  Handle unsuccessful 2-pass rights objects response message.

      \param  response            input, unsuccessful 2-pass rights objects response
                                  message.
  */
  virtual void HandleUnsuccessROResponse(const NZSPtr<UnsuccessTwoPassROResponse>& response) = 0;

  /*! \brief  Handle 1-pass rights objects response message.

      \param  response          input, 1-pass rights objects response message.
  */
  virtual void HandleROResponse(const NZSPtr<OnePassROResponse>& response) = 0;

  /*! \brief  Handle successful join domain response message.

      \param  response          input, successful join domain response message.
  */
  virtual void HandleSuccessJoinResponse(const NZSPtr<SuccessJoinDomainResponse>& response) = 0;

  /*! \brief  Handle unsuccessful join domain response message.

      \param  response          input, unsuccessful join domain response message.
  */
  virtual void HandleUnsuccessJoinResponse(const NZSPtr<UnsuccessJoinDomainResponse>& response) = 0;

  /*! \brief  Handle successful leave domain response message.

      \param  response          input, successful leave domain response message.
  */
  virtual void HandleSuccessLeaveResponse(const NZSPtr<SuccessLeaveDomainResponse>& response) = 0;

  /*! \brief  Handle unsuccessful leave domain response message.

      \param  response          input, unsuccessful leave domain response message.
  */
  virtual void HandleUnsuccessLeaveResponse(const NZSPtr<UnsuccessLeaveDomainResponse>& response) = 0;

  /*! \brief  Handle registration trigger.

      \param  trigger           input, registration trigger.

      \returns  Device hello message. If zero, failed.
  */
  virtual SPtr<DeviceHelloRequest> HandleRegTrigger(const NZSPtr<RegRequestTrigger>& trigger) = 0;

  /*! \brief  Handle domain rights objects acuisition trigger.

      \param  trigger           input, domain rights objects acuisition trigger.

      \returns  Rights objects acquisition message. If zero, failed.
  */
  virtual SPtr<RORequest> HandleDomainROTrigger(const NZSPtr<DomainROTrigger>& trigger) = 0;

  /*! \brief  Handle non-domain rights objects acuisition trigger.

      \param  trigger           input, non-domain rights objects acuisition trigger.

      \returns  Rights objects acquisition message. If zero, failed.
  */
  virtual SPtr<RORequest> HandleNDomainROTrigger(const NZSPtr<NDomainROTrigger>& trigger) = 0;

  /*! \brief  Handle join domain trigger.

      \param  trigger           input, join domain trigger.

      \returns  Join domain request message. If zero, failed.
  */
  virtual SPtr<JoinDomainRequest> HandleJoinTrigger(const NZSPtr<JoinDomainTrigger>& trigger) = 0;

  /*! \brief  Handle leave domain trigger.

      \param  trigger           input, leave domain trigger.

      \returns  Leave domain request message. If zero, failed.
  */
  virtual SPtr<LeaveDomainRequest> HandleLeaveTrigger(const NZSPtr<LeaveDomainTrigger>& trigger) = 0;
};

} // namespace DRMPlugin

#endif // !defined (IOMADRMDECAGENT_H)
