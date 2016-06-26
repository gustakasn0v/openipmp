/**	\file IPMPDescriptor.h

    \ingroup drmplayer
    \ingroup drmencoder

	Test implementation of IPMP descriptor class.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPMPDESCRIPTOR_H)
#define IPMPDESCRIPTOR_H

#include "BasicTypes.h"
#include "ISigCertContainer.h"
#include <vector>

#include "IIPMPDescriptor.h"
#include "SigCertContainer.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief  IPMP descriptor.

    Descriptor containing IPMP data used for MPEG2 IPMP protection.
*/
class IPMPDescriptor: public IIPMPDescriptor {
public:
  /*! \brief  Constructor.
  */
  IPMPDescriptor(): ipmpDescriptorID(0), toolID(), controlP(0), seqCode(0),
    ipmpData(), sigCert(0) {
  }

  /*! \brief  Constructor.

      \param  id        IPMP descriptor identifier.
      \param  tID       tool identifier.
      \param  control   control point.
      \param  sCode     sequence code.
      \param  ipmp      IPMP data (encoded).
      \param  cont      signature and certificate container.
  */
  IPMPDescriptor(const Bit32T& id, const Bit128T& tID, const ByteT& control,
    const ByteT& sCode, const ByteSeq& ipmp, ISigCertContainer* cont):
    ipmpDescriptorID(id), toolID(tID), controlP(control), seqCode(sCode),
    ipmpData(ipmp), sigCert(cont) {
  }

  virtual ~IPMPDescriptor() {
    if (sigCert != 0) delete sigCert; sigCert = 0;
  }

  /*! \brief  Get IPMP descriptor identifier.

      IPMP descriptor identifier uniquely identifies the descriptor.

      \returns  IPMP descriptor identifier.
  */
  virtual const Bit32T& GetIPMPDescriptorID() const {
    return ipmpDescriptorID;
  }

  /*! \brief  Set IPMP descriptor identifier.

      If previous IPMP descriptor identifier existed, it must be replaced with
      the one given.

      \param  descID      input, IPMP descriptor identifier to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPDescriptorID(const Bit32T& descID) {
    ipmpDescriptorID = descID;
    return true;
  }

  /*! \brief  Get IPMP tool identifier.

      IPMP tool identifier identifies the tool which the descriptor is
      intended for.

      \returns  IPMP tool identifier.
  */
  virtual const Bit128T& GetIPMPToolID() const {
    return toolID;
  }

  /*! \brief  Set IPMP tool identifier.

      If previous IPMP tool identifier existed, it must be replaced with
      the one given.

      \param  id          input, IPMP tool identifier to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPToolID(const Bit128T& id) {
    toolID = id;
    return true;
  }

  /*! \brief  Get control point.

      Control point defines the point at which the IPMP processing must take
      place.

      \returns  Control point.
  */
  virtual const ByteT& GetControlPoint() const {
    return controlP;
  }

  /*! \brief  Set control point.

      If previous control point existed, it must be replaced with the one given.

      \param  cPoint     input, control point to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetControlPoint(const ByteT& cPoint) {
    controlP = cPoint;
    return true;
  }

  /*! \brief  Get sequence code.

      Sequence code defines the relation of the IPMP tool to other IPMP tools
      at the same control point. It is a priority code, thus a higher priority
      IPMP tool will get control before a lower priority IPMP tool at the same
      control point.

      \returns  Sequence code.
  */
  virtual const ByteT& GetSequenceCode() const {
    return seqCode;
  }

  /*! \brief  Set sequence code.

      If previous sequence code existed, it must be replaced with the one given.

      \param  sCode     input, sequence code to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetSequenceCode(const ByteT& sCode) {
    seqCode = sCode;
    return true;
  }

  /*! \brief  Get IPMP data.

      \returns  IPMP data.
  */
  virtual const ByteSeq& GetIPMPData() const {
    return ipmpData;
  }

  /*! \brief  Set IPMP data.

      If previous IPMP data existed, it must be replaced with the one given.

      \param  ipmp     input, IPMP data to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPData(const ByteSeq& ipmp) {
    ipmpData = ipmp;
    return true;
  }

  /*! \brief  Signature and certificate container.

      Since signature and certificate container is not mandatory, zero value of
      the pointer indicates that the IPMP descriptor doesn't contain signature,
      thus that it is not signed.

      \returns  Signature and certificate container pointer. Zero value
                indicates that it's not present.
  */
  virtual ISigCertContainer* GetSigCertContainer() const {
    return sigCert;
  }

  /*! \brief  Create new signature and certificate container and save it as
              signature and certificate container contained in this IPMP
              descriptor.

      \warning  If a previous signature and certificate container existed,
                it must be replaced with the newly created one.

      \param  container      output, newly created signature and certificate
                             container pointer (if successful).

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateSigCertContainer(ISigCertContainer** container) {
    if (sigCert != 0) delete sigCert;
    sigCert = new SigCertContainer();
    *container = sigCert;
    return true;
  }

  /*! \brief  Encode.

      \param  encoded       output, encoded data.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(ByteSeq& encoded) {
    ByteSeq tmp(GetIPMPDescriptorID());
    tmp += ByteSeq(GetIPMPToolID());
    tmp += GetControlPoint();
    tmp += GetSequenceCode();
    if (GetIPMPData().GetLength() >= (1 << 16)) {
      return false;
    }
    tmp += ByteSeq((UInt16T)(GetIPMPData().GetLength()));
    tmp += GetIPMPData();

    if (GetSigCertContainer() != 0) {
      tmp += (ByteT)(0x80);
      ByteSeq sigEnc;
      if (GetSigCertContainer()->MPEG2Encode(sigEnc) == false) {
        return false;
      }
      tmp += sigEnc;
    } else {
      tmp += (ByteT)(0x0);
    }

    //  Since rights data can easily become larger than 2^8, we have to
    //  increase allowed size of the IPMP descriptor. And this is definitely
    //  a bug in the specifications, cause the size of an IPMP descriptor
    //  is limited to 2^8, while at the same time size of contained IPMP
    //  data is limited to 2^16.
/*
    if (tmp.GetLength() > (1 << 8)) {
      return false;
    }
*/
    if (tmp.GetLength() > (1 << 16)) {
      return false;
    }
//    encoded = ByteSeq((ByteT)41) + ByteSeq((ByteT)(tmp.GetLength())) + tmp;
    encoded = ByteSeq((ByteT)41) + ByteSeq((UInt16T)(tmp.GetLength())) + tmp;
    return true;
  }

private:
  Bit32T ipmpDescriptorID;
  Bit128T toolID;
  ByteT controlP;
  ByteT seqCode;
  ByteSeq ipmpData;
  ISigCertContainer* sigCert;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(IPMPDESCRIPTOR_H)
