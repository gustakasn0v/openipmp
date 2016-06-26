/**	\file MPEG2IPMPXDRMEncoder.h

	MPEG2 DRM encoder with IPMPX signalling.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (MPEG2IPMPXDRMENCODER_H)
#define MPEG2IPMPXDRMENCODER_H

#include "BasicTypes.h"
#include "IMPEG2IPMPXEncoder.h"
#include "MPEG2IPMPXDRMEncryptor.h"
#include <vector>
#include <string>
#include "IXMLDocument.h"
#include "ICipher.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined MPEG2IPMPXDRMENCODER_EXPORTS
#define MPEG2IPMPXDRMENCODER_EXPORT __declspec(dllexport)
#else
#define MPEG2IPMPXDRMENCODER_EXPORT __declspec(dllimport)
#endif // MPEG2IPMPXDRMENCODER_EXPORTS
#elif defined (LINUX)
#define MPEG2IPMPXDRMENCODER_EXPORT
#else
#define MPEG2IPMPXDRMENCODER_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  MPEG2 DRM encoder with IPMPX signalling.
*/
class MPEG2IPMPXDRMEncoder {
public:
  /*! \brief  Constructor.

      \param  logger      message logger.
  */
  MPEG2IPMPXDRMENCODER_EXPORT MPEG2IPMPXDRMEncoder(DRMLogger& logger);

  MPEG2IPMPXDRMENCODER_EXPORT ~MPEG2IPMPXDRMEncoder();

  /*! \brief  Create MPEG2 DRM encryptor with IPMPX signalling.

      Create new DRM encryptor that will be used by the caller to protect
      MPEG2 data.

      XML document contains necessary information for protecting the content.
    
      Mandatory tags in the XML document are:
       - ROOT.ContentTitle
       - ROOT.UserName
       - ROOT.UserPass
       - ROOT.RightsHostURL
       - ROOT.doi:KernelMetadata.DOI
       - ROOT.doi:KernelMetadata.Titles.Title.TitleValue
       - ROOT.doi:KernelMetadata.Titles.Title.Language
       - ROOT.doi:KernelMetadata.StructuralType
       - ROOT.doi:KernelMetadata.Modes.Mode
       - ROOT.doi:KernelMetadata.PrimaryAgents.Agent.Name.NameType
       - ROOT.doi:KernelMetadata.PrimaryAgents.Agent.Name.NameValue
       - ROOT.doi:KernelMetadata.PrimaryAgents.Agent.Roles.Role
       - ROOT.doi:KernelMetadata.Assertor.Registrant.Name.NameType
       - ROOT.doi:KernelMetadata.Assertor.Registrant.Name.NameValue
       - ROOT.doi:KernelMetadata.Assertor.Registrant.Identifier.IdentifierType
       - ROOT.doi:KernelMetadata.Assertor.Registrant.Identifier.IdentifierValue
       - ROOT.doi:KernelMetadata.Assertor.Authority.Name.NameType
       - ROOT.doi:KernelMetadata.Assertor.Authority.Name.NameValue

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <ContentTitle>testfile.mpg</ContentTitle>
       <UserName>danijelk</UserName>
       <UserPass>ipmp</UserPass>
       <RightsHostURL>localhost:8080</RightsHostURL>
       <doi:KernelMetadata xmlns:doi="http://www.doi.org/">
        <DOI>TBD</DOI>
        <Identifiers>
         <Identifier>
          <IdentifierType>ISWC</IdentifierType>
          <IdentifierValue>T-034.524.680</IdentifierValue>
         </Identifier>
        </Identifiers>
        <Titles>
         <Title>
          <TitleValue>title</TitleValue>
          <Language>en</Language>
         </Title>
        </Titles>
        <StructuralType>visual</StructuralType>
        <Modes>
         <Mode>visual</Mode>
        </Modes>
        <PrimaryAgents>
         <Agent sequence="1">
          <Name>
           <NameType>Person</NameType>
           <NameValue>Matt Witte</NameValue>
          </Name>
          <Roles>
           <Role>Artist</Role>
          </Roles>
         </Agent>
         <Agent sequence="2">
          <Name>
           <NameType>Person</NameType>
           <NameValue>Freddy</NameValue>
          </Name>
          <Roles>
           <Role>Directory</Role>
          </Roles>
         </Agent>
        </PrimaryAgents>
        <Assertor>
         <Registrant>
          <Name>
           <NameType>Person</NameType>
           <NameValue>Persons Name Here</NameValue>
          </Name>
          <Identifier>
           <IdentifierType>PublisherCode</IdentifierType>
           <IdentifierValue>9901</IdentifierValue>
          </Identifier>
         </Registrant>
         <Authority>
          <Name>
           <NameType>Organization</NameType>
           <NameValue>Objectlab</NameValue>
          </Name>
         </Authority>
        </Assertor>
       </doi:KernelMetadata>
      </ROOT>

      \endverbatim


      \warning  The newly created encryptor will later be used by the MPEG2
                DRM encoder, so caller MUST NOT delete it, just use it's
                functionality.

      \warning  Input content identifier must be different for each call to
                this function. Thus if protecting multiple streams with
                different encryptors, it must be different for each stream
                (e.g. file name + stream identifier).

      \param  content         input, basic content identifier.
      \param  xmlDoc          input, XML document.
      \param  eMethod         encryption method (AES128CTR or BLOWFISH).
      \param  encryptor       output, newly created encryptor (if successful).

      \returns  Boolean indicating success or failure.
  */
  bool MPEG2IPMPXDRMENCODER_EXPORT CreateMPEG2IPMPXDRMEncryptor(std::string&
    content, IXMLElement* xmlDoc, EncMethod eMethod,
    IMPEG2IPMPXDRMEncryptor** encryptor);

  /*! \brief  Add DRM information to MPEG2 transport stream.

      IMPEG2IPMPXDRMEncoder will use the functionality of the
      IMPEG2IPMPXTStreamEncoder to add DRM information.

      \param  tsEncoder       input, transport stream encoder.

      \returns  Boolean indicating success or failure.
  */
  bool MPEG2IPMPXDRMENCODER_EXPORT AddDRMInfo(IMPEG2IPMPXTStreamEncoder* tsEncoder);

  /*! \brief  Add DRM information to MPEG2 program stream.

      IMPEG2IPMPXDRMEncoder will use the functionality of the
      IMPEG2IPMPXPStreamEncoder to add DRM information.

      \param  psEncoder       input, program stream encoder.

      \returns  Boolean indicating success or failure.
  */
  bool MPEG2IPMPXDRMENCODER_EXPORT AddDRMInfo(IMPEG2IPMPXPStreamEncoder* psEncoder);

private:
  std::vector<MPEG2IPMPXDRMEncryptor*> encryptors;
  DRMLogger& drmLogger;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (MPEG2IPMPXDRMENCODER_H)
