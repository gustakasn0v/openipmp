/**	\file IMPEG4DRMAtom.h

  Interfaces for MP4 atoms used for DRM.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IMPEG4DRMATOM_H)
#define IMPEG4DRMATOM_H

#include "BasicTypes.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG4SinfDRMPlugin namespace. All MPEG4 Sinf DRM plugin code resides in it.
namespace MPEG4SinfDRMPlugin {

/*! \brief  Original format atom.

    Contained in protection scheme info atom.
*/
class IMP4FrmaAtom {
public:
  virtual ~IMP4FrmaAtom() {
  }

  /*! \brief  Get original data format.

      \returns    4CC code representing original data format.
  */
  virtual UInt32T GetDataFormat() = 0;

  /*! \brief  Set original data format.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetDataFormat(UInt32T format) = 0;
};

/*! \brief IPMP descriptor.
*/
class IMP4IPMPDescriptor {
public:
  virtual ~IMP4IPMPDescriptor() {
  }

  /*! \brief  Get IPMP descriptor identifier.

      \returns    IPMP descriptor identifier.
  */
  virtual ByteT GetIPMPDescriptorIdentifier() = 0;

  /*! \brief  Get IPMP descriptor type.

      \returns    IPMP descriptor type.
  */
  virtual UInt16T GetIPMPDescriptorType() = 0;

  /*! \brief  Get IPMP data length.

      \returns    IPMP data length, if contains IPMP data.
      \returns    0, if does not contain IPMP data.
  */
  virtual UInt32T GetIPMPDataLength() = 0;

  /*! \brief  Get IPMP data.

      \returns    IPMP data, if contains one.
      \returns    0, if does not contain IPMP data.
  */
  virtual ByteT* GetIPMPData() = 0;

  /*! \brief  Set IPMP descriptor identifier.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetIPMPDescriptorIdentifier(ByteT id) = 0;

  /*! \brief  Set IPMP descriptor type.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetIPMPDescriptorType(UInt16T type) = 0;

  /*! \brief  Set IPMP data.
  
      If IPMP data already exists, it must be cleaned and replaced by
      newly created one. Data representing ipmp data must be locally copied.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetIPMPData(ByteT* data, UInt32T len) = 0;
};

/*! \brief IPMP info atom.

    Contained in protection scheme info atom.
*/
class IMP4ImifAtom {
public:
  virtual ~IMP4ImifAtom() {
  }

  /*! \brief  Get MP4 atom version.

      \returns    MP4 atom version.
  */
  virtual ByteT GetAtomVersion() = 0;

  /*! \brief  Get MP4 atom flags.

      \returns    MP4 atom flags.
  */
  virtual UInt32T GetAtomFlags() = 0;

  /*! \brief  Get number of IPMP descriptors contained. Must be > 0.

      \returns    Positive number of IPMP descriptors contained.
  */
  virtual UInt32T GetIPMPDescriptorCount() = 0;

  /*! \brief  Get IPMP descriptor with index descIndex.

      \returns    IPMP descriptor pointer, if descIndex is in contained
                  range.
      \returns    0, if descIndex is out of contained range (error).
  */
  virtual IMP4IPMPDescriptor* GetIPMPDescriptor(UInt32T descIndex) = 0;

  /*! \brief  Set MP4 atom version.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomVersion(ByteT version) = 0;

  /*! \brief  Set MP4 atom flags.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomFlags(UInt32T flags) = 0;

  /*! \brief  Create new IPMP descriptor. Must be != 0.

      \returns    IPMP descriptor pointer, if one is created.
      \returns    0, if new IPMP descriptor wasn't created (error).
  */
  virtual IMP4IPMPDescriptor* CreateIPMPDescriptor() = 0;
};

/*! \brief Scheme type atom.

    Contained in protection scheme info atom.
*/
class IMP4SchmAtom {
public:
  virtual ~IMP4SchmAtom() {
  }

  /*! \brief  Get MP4 atom version.

      \returns    MP4 atom version.
  */
  virtual ByteT GetAtomVersion() = 0;

  /*! \brief  Get MP4 atom flags.

      \returns    MP4 atom flags.
  */
  virtual UInt32T GetAtomFlags() = 0;

  /*! \brief  Get scheme code.

      \returns    4CC code identifying the scheme.
  */
  virtual UInt32T GetSchemeCode() = 0;

  /*! \brief  Get scheme version.

      \returns    Integer representing the scheme version.
  */
  virtual UInt32T GetSchemeVersion() = 0;

  /*! \brief  Get scheme URI (null terminated string). Can be 0.

      \returns    Scheme URI, if contains one.
      \returns    0, if does not contain scheme URI.
  */
  virtual char* GetSchemeURI() = 0;

  /*! \brief  Set MP4 atom version.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomVersion(ByteT version) = 0;

  /*! \brief  Set MP4 atom flags.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomFlags(UInt32T flags) = 0;

  /*! \brief  Set scheme code.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetSchemeCode(UInt32T code) = 0;

  /*! \brief  Set scheme version.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetSchemeVersion(UInt32T version) = 0;

  /*! \brief  Set scheme URI (null terminated string).
  
      If scheme URI already exists, it must be removed and replaced with
      a newly created one. Data representing scheme URI must be locally copied.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetSchemeURI(char* uri) = 0;
};

/*! \brief OMA DRM headers atom.

    Contained in OMA DRM key management atom. It must contain content identifier.
*/
class IMP4OhdrAtom {
public:
  virtual ~IMP4OhdrAtom() {
  }

  /*! \brief  Get MP4 atom version.

      \returns    MP4 atom version.
  */
  virtual ByteT GetAtomVersion() = 0;

  /*! \brief  Get MP4 atom flags.

      \returns    MP4 atom flags.
  */
  virtual UInt32T GetAtomFlags() = 0;

  /*! \brief  Get encryption method code.

      \returns    Encryption method code.
  */
  virtual ByteT GetEncryptionMethod() = 0;

  /*! \brief  Get encryption padding code.

      \returns    Encryption padding code.
  */
  virtual ByteT GetEncryptionPadding() = 0;

  /*! \brief  Get plaintext length.

      \returns    Plaintext length.
  */
  virtual UInt64T GetPlaintextLength() = 0;

  /*! \brief  Get content identifier (null terminated string). Must be != 0.

      \returns    Content identifier, if contains one.
      \returns    0, if does not contain content identifier (error).
  */
  virtual const char* GetContentIdentifier() = 0;

  /*! \brief  Get rights issuer URL (null terminated string).

      \returns    Rights issuer URL, if contains rights issuer URL.
      \returns    0, if does not contain rights issuer URL.
  */
  virtual const char* GetRightsIssuerURL() = 0;

  /*! \brief  Get textual headers length.

      \returns    Textual headers length, if contains textual headers.
      \returns    0, if does not contain textual headers.
  */
  virtual UInt16T GetTextualHeadersLength() = 0;

  /*! \brief  Get textual headers. Can be 0.

      \returns    Textual headers, if contains one.
      \returns    0, if does not contain textual headers.
  */
  virtual ByteT* GetTextualHeaders() = 0;

  /*! \brief  Set MP4 atom version.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomVersion(ByteT version) = 0;

  /*! \brief  Set MP4 atom flags.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomFlags(UInt32T flags) = 0;

  /*! \brief  Set encryption method code.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetEncryptionMethod(ByteT code) = 0;

  /*! \brief  Set encryption padding code.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetEncryptionPadding(ByteT code) = 0;

  /*! \brief  Set plaintext length.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetPlaintextLength(UInt64T len) = 0;

  /*! \brief  Set content identifier (null terminated string).
  
      If content identifier already exists, it must be removed and replaced
      by newly created one. Data representing content identifier must be
      locally copied.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetContentIdentifier(const char* id) = 0;

  /*! \brief  Set rights issuer URL (null terminated string).
  
      If rights issuer URL already exists, it must be removed and replaced
      by newly created one. Data representing content identifier must be
      locally copied.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetRightsIssuerURL(const char* url) = 0;

  /*! \brief  Set textual headers.
  
      If textual headers already exists, it must be removed and replaced
      by newly created one. Data representing textual headers must be locally
      copied.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetTextualHeaders(ByteT* data, UInt16T len) = 0;
};

/*! \brief OMA DRM key management atom.

    Contained in scheme information atom. It must contain OMA headers atom.

    Obligatory members (one can see if an element is obligatory or not by
    inspecting the documentation of the get function on that element; if it's
    return value can be 0, it is not obligatory, otherwise it is) do not have
    create functions, they are accessed and used via get functions, thus if a
    get function on an obligatory element returns 0, this is considered an
    error.
    For non obligatory elements, interface provides create functions, which
    must create the pointed element, and if they return 0, it is considered
    an error.
*/
class IMP4OdkmAtom {
public:
  virtual ~IMP4OdkmAtom() {
  }

  /*! \brief  Get MP4 atom version.

      \returns    MP4 atom version.
  */
  virtual ByteT GetAtomVersion() = 0;

  /*! \brief  Get MP4 atom flags.

      \returns    MP4 atom flags.
  */
  virtual UInt32T GetAtomFlags() = 0;

  /*! \brief  Get OMA DRM headers atom. Must be != 0.

      \returns    OMA DRM headers atom pointer, if contains one.
      \returns    0, if does not contain OMA DRM headers atom (error).
  */
  virtual IMP4OhdrAtom* GetOMADRMHeaders() = 0;

  /*! \brief  Set MP4 atom version.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomVersion(ByteT version) = 0;

  /*! \brief  Set MP4 atom flags.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomFlags(UInt32T flags) = 0;
};

/*! \brief ISMA key management system atom.

    Contained in scheme information atom. It must contain key management system URI.
*/
class IMP4IKMSAtom {
public:
  virtual ~IMP4IKMSAtom() {
  }

  /*! \brief  Get MP4 atom version.

      \returns    MP4 atom version.
  */
  virtual ByteT GetAtomVersion() = 0;

  /*! \brief  Get MP4 atom flags.

      \returns    MP4 atom flags.
  */
  virtual UInt32T GetAtomFlags() = 0;

  /*! \brief  Get key management system URI (null terminated string).
              Must be != 0.

      \returns    key management system URI, if contains one.
      \returns    0, if does not contain key management system URI (error).
  */
  virtual const char* GetKeyManagementSystemURI() = 0;

  /*! \brief  Set MP4 atom version.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomVersion(ByteT version) = 0;

  /*! \brief  Set MP4 atom flags.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomFlags(UInt32T flags) = 0;

  /*! \brief  Set key management system URI (null terminated string).
  
      If key management system URI already exists, it must be removed and
      replaced by newly created one.
      Data representing key management system URI must be locally copied.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetKeyManagementSystemURI(const char* uri) = 0;
};

/*! \brief ISMA sample format atom.

    Contained in scheme information atom.
*/
class IMP4ISFMAtom {
public:
  virtual ~IMP4ISFMAtom() {
  }

  /*! brief Get MP4 atom version.

      \returns    MP4 atom version.
  */
  virtual ByteT GetAtomVersion() = 0;

  /*! \brief  Get MP4 atom flags.

      \returns    MP4 atom flags.
  */
  virtual UInt32T GetAtomFlags() = 0;

  /*! \brief  Get selective encryption indicator.

      \returns    Selective encryption indicator.
  */
  virtual bool GetSelectiveEncryption() = 0;

  /*! \brief  Get key indicator length.

      \returns    Key indicator length.
  */
  virtual ByteT GetKeyIndicatorLength() = 0;

  /*! \brief  Get initialization vector length.

      \returns    Initialization vector length.
  */
  virtual ByteT GetIVLength() = 0;

  /*! \brief  Set MP4 atom version.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomVersion(ByteT version) = 0;

  /*! \brief  Set MP4 atom flags.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetAtomFlags(UInt32T flags) = 0;

  /*! \brief  Set selective encryption indicator.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetSelectiveEncryption(bool selective) = 0;

  /*! \brief  Set key indicator length.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetKeyIndicatorLength(ByteT len) = 0;

  /*! \brief  Set initialization vector length.

      \returns    Boolean indicating success or not.
  */
  virtual bool SetIVLength(ByteT len) = 0;
};

/*! \brief Scheme information atom.

    Contained in protection scheme info atom. It contains DRM scheme specific data.
    We support OMA and ISMA DRM schemes, therefore we investigate atoms
    specific for those DRM schemes.
    If it contains ISMA key management system atom, it must contain ISMA
    sample format atom, and vice versa.

    Obligatory members (one can see if an element is obligatory or not by
    inspecting the documentation of the get function on that element; if it's
    return value can be 0, it is not obligatory, otherwise it is) do not have
    create functions, they are accessed and used via get functions, thus if a
    get function on an obligatory element returns 0, this is considered an
    error.
    For non obligatory elements, interface provides create functions, which
    must create the pointed element, and if they return 0, it is considered
    an error.
*/
class IMP4SchiAtom {
public:
  virtual ~IMP4SchiAtom() {
  }

  /*! \brief  Get OMA DRM key management atom. Can be 0.

      \returns    OMA DRM key management atom pointer, if contains one.
      \returns    0, if does not contain OMA DRM key management atom.
  */
  virtual IMP4OdkmAtom* GetOMADRMAtom() = 0;

  /*! \brief  Get ISMA key management system atom. Can be 0 (see above).

      \returns    ISMA key management system atom pointer, if contains one.
      \returns    0, if does not contain ISMA key management system atom.
  */
  virtual IMP4IKMSAtom* GetISMAKMSAtom() = 0;

  /*! \brief  Get ISMA sample format atom. Can be 0 (see above).

      \returns    ISMA sample format atom pointer, if contains one.
      \returns    0, if does not contain ISMA sample format atom.
  */
  virtual IMP4ISFMAtom* GetISMASFMAtom() = 0;

  /*! \brief  Create new OMA DRM key management atom.
  
      If one already exists, it must be removed and replaced with new one.
      Must be != 0.

      \returns    OMA DRM key management atom pointer, if one is created.
      \returns    0, if new OMA DRM key management atom wasn't created (error).
  */
  virtual IMP4OdkmAtom* CreateOMADRMAtom() = 0;

  /*! \brief  Create new ISMA key management system atom.
  
      If one already exists, it must be removed and replaced with new one.
      Must be != 0.

      \returns    ISMA key management system atom pointer, if one is created.
      \returns    0, if new ISMA key management system atom wasn't created (error).
  */
  virtual IMP4IKMSAtom* CreateISMAKMSAtom() = 0;

  /*! \brief  Create new ISMA sample format atom.
  
      If one already exists, it must be removed and replaced with new one.
      Must be != 0.

      \returns    ISMA sample format atom pointer, if one is created.
      \returns    0, if new ISMA sample format atom wasn't created (error).
  */
  virtual IMP4ISFMAtom* CreateISMASFMAtom() = 0;
};

/*! \brief Protection scheme info atom.

    Contained in protected sample entry atom. It must contain original format atom.
    If it contains scheme type atom, it must contain scheme information atom,
    and vice versa.

    Obligatory members (one can see if an element is obligatory or not by
    inspecting the documentation of the get function on that element; if it's
    return value can be 0, it is not obligatory, otherwise it is) do not have
    create functions, they are accessed and used via get functions, thus if a
    get function on an obligatory element returns 0, this is considered an
    error.
    For non obligatory elements, interface provides create functions, which
    must create the pointed element, and if they return 0, it is considered
    an error.
*/
class IMP4SinfAtom {
public:
  virtual ~IMP4SinfAtom() {
  }

  /*! \brief  Get original format atom. Must be != 0.

      \returns    Original format atom pointer, if contains one.
      \returns    0, if does not contain original format atom (error).
  */
  virtual IMP4FrmaAtom* GetOriginalFormat() = 0;

  /*! \brief  Get IPMP info atom. Can be 0.

      \returns    IPMP info atom pointer, if contains one.
      \returns    0, if does not contain IPMP info atom.
  */
  virtual IMP4ImifAtom* GetIPMPInfo() = 0;

  /*! \brief  Get scheme type atom. Can be 0 (see above).

      \returns    Scheme type atom pointer, if contains one.
      \returns    0, if does not contain scheme type atom.
  */
  virtual IMP4SchmAtom* GetSchemeType() = 0;

  /*! \brief  Get scheme information atom. Can be 0 (see above).

      \returns    Scheme information atom pointer, if contains one.
      \returns    0, if does not contain scheme information atom.
  */
  virtual IMP4SchiAtom* GetSchemeInformation() = 0;

  /*! \brief  Create new IPMP info atom.
  
      If one already exists, it must be removed and replaced with new one. 
      Must be != 0.

      \returns    IPMP info atom pointer, if one is created.
      \returns    0, if new IPMP info atom wasn't created (error).
  */
  virtual IMP4ImifAtom* CreateIPMPInfo() = 0;

  /*! \brief  Create new scheme type atom.
  
      If one already exists, it must be removed and replaced with new one.
      Must be != 0.

      \returns    scheme type atom pointer, if one is created.
      \returns    0, if new scheme type atom wasn't created (error).
  */
  virtual IMP4SchmAtom* CreateSchemeType() = 0;

  /*! \brief  Create new scheme information atom.
  
      If one already exists, it must be removed and replaced with new one.
      Must be != 0.

      \returns    scheme information atom pointer, if one is created.
      \returns    0, if new scheme information atom wasn't created (error).
  */
  virtual IMP4SchiAtom* CreateSchemeInformation() = 0;
};

} // namespace MPEG4SinfDRMPlugin

} // namespace DRMPlugin

#endif // !defined(IMPEG4DRMATOM_H)
