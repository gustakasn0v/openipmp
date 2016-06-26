/**	\file IIPMPControlInfoPart.h

	Interface for part of the IPMP control information structure.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IIPMPCONTROLINFOPART_H)
#define IIPMPCONTROLINFOPART_H

#include "BasicTypes.h"
#include "ISigCertContainer.h"
#include "CRC32Calculator.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief IPMP control information part.

    Part of the structure containing IPMP control information classes.
*/
class IIPMPControlInfoPart {
public:
  virtual ~IIPMPControlInfoPart() {};

  /*! \brief  Get IPMP control information version.

      \returns  5-bit number representing version.
  */
  virtual const Bit5T& GetIPMPControlInfoVersion() const = 0;

  /*! \brief  Set IPMP control information version.

      If a previous IPMP control information version existed, it must be
      replaced with the one given.

      \param    version       input, version to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPControlInfoVersion(const Bit5T& version) = 0;

  /*! \brief  Get indicator whether the control information is currently
              applicable.

      If indicator is true, the control information is currently applicable,
      if not it is the next control information to become applicable.

      \returns  Boolean indicating current applicability.
  */
  virtual const bool& GetCurrentNextIndicator() const = 0;

  /*! \brief  Set indicator whether the control information is currently
              applicable.

      If a previous indicator existed, it must be replaced with the one given.

      \param    indicator       input, current applicability indicator to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCurrentNextIndicator(const bool& indicator) = 0;

  /*! \brief  Get part number.

      Part number respresents index of the part in a row of parts constituting
      IPMP control information.

      \returns  Part number.
  */
  virtual const ByteT& GetPartNumber() const = 0;

  /*! \brief  Set part number.

      If previous part number existed, it must be replaced with the one given.

      \param    number       input, part number to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPartNumber(const ByteT& number) = 0;

  /*! \brief  Get encoded control info classes.

      \returns  Encoded control info classes.
  */
  virtual const ByteSeq& GetIPMPControlInfos() const = 0;

  /*! \brief  Set encoded control info classes.

      If previous encoded control info classes existed, it must be replaced
      with the one given.

      \param    classes       input, encoded control info classes to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPControlInfos(const ByteSeq& classes) = 0;

  /*! \brief  Get 32-bit CRC code.

      \returns  Number representing 32-bit CRC code.
  */
  virtual const UInt32T& GetCRC32Code() = 0;

  /*! \brief  Set 32-bit CRC code.

      If a previous CRC code existed, it must be replaced with the one given.

      \param    crc       input, CRC code to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCRC32Code(const UInt32T& crc) = 0;

  /*! \brief  Encode the class as a byte array.

      This function is used for calculating CRC codes.

      \param  encoded     output, encoded class.

      \returns  Boolean indicating success or failure. If failed, log
                will contain error description.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const = 0;
};

/*!	\brief Transport stream IPMP control information part.

    Part of the structure containing IPMP control information classes in a
    transport stream.
*/
class ITStreamIPMPControlInfoPart: public IIPMPControlInfoPart {
public:
  virtual ~ITStreamIPMPControlInfoPart() {};

  /*! \brief  Get table identifier.

      \returns  Number representing identifier.
  */
  virtual const ByteT& GetTableID() const = 0;

  /*! \brief  Set table identifier.

      If a previous table identifier existed, it must be replaced with the 
      one given.

      \param    tableID       input, table identifier to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetTableID(const ByteT& tableID) = 0;

  /*! \brief  Get section syntax indicator.

      \returns  Section syntax indicator.
  */
  virtual const bool& GetSectionSyntaxIndicator() const = 0;

  /*! \brief  Set section syntax indicator.

      If a previous section syntax indicator existed, it must be replaced
      with the one given.

      \param    indicator       input, section syntax indicator to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetSectionSyntaxIndicator(const bool& indicator) = 0;

  /*! \brief  Get total control information classes length.

      Total control information classes length is the total length in all
      the parts constituting the same IPMP control information structure.

      \returns  total control information classes length.
  */
  virtual const UInt16T& GetTotalControlInfoClassesLen() const = 0;

  /*! \brief  Set total control information classes length.

      If a previous total control information classes length existed, it must
      be replaced with the one given.

      \param    length        input, total control information classes length
                              to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetTotalControlInfoClassesLen(const UInt16T& length) = 0;
};

/*!	\brief Program stream IPMP control information part.

    Part of the structure containing IPMP control information classes in a
    program stream.
*/
class IPStreamIPMPControlInfoPart: public IIPMPControlInfoPart {
public:
  virtual ~IPStreamIPMPControlInfoPart() {};

  /*! \brief  Get packet start code prefix.

      \returns  Number representing packet start code prefix.
  */
  virtual const Bit24T& GetPacketStartCodePrefix() const = 0;

  /*! \brief  Set packet start code prefix.

      If a previous packet start code prefix existed, it must be replaced
      with the one given.

      \param    prefix       input, packet start code prefix to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPacketStartCodePrefix(const Bit24T& prefix) = 0;

  /*! \brief  Get stream identifier.

      \returns  Number representing stream identifier.
  */
  virtual const ByteT& GetStreamID() const = 0;

  /*! \brief  Set stream identifier.

      If a previous stream identifier existed, it must be replaced with
      the one given.

      \param    streamID       input, stream identifier to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStreamID(const ByteT& streamID) = 0;

  /*! \brief  Get PES extension flag.

      \returns  PES extension flag.
  */
  virtual const bool& GetPESExtensionFlag() const = 0;

  /*! \brief  Set PES extension flag.

      If a previous PES extension flag existed, it must be replaced with
      the one given.

      \param    flag       input, PES extension flag to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPESExtensionFlag(const bool& flag) = 0;

  /*! \brief  Get PES extension flag 2.

      \returns  PES extension flag 2.
  */
  virtual const bool& GetPESExtensionFlag2() const = 0;

  /*! \brief  Set PES extension flag 2.

      If a previous PES extension flag 2 existed, it must be replaced with
      the one given.

      \param    flag       input, PES extension flag 2 to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPESExtensionFlag2(const bool& flag) = 0;

  /*! \brief  Get stream identifier extension flag.

      \returns  Stream identifier extension flag.
  */
  virtual const bool& GetStreamIDExtensionFlag() const = 0;

  /*! \brief  Set stream identifier extension flag.

      If a previous stream identifier extension flag existed, it must be
      replaced with the one given.

      \param    flag       input, stream identifier extension flag to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStreamIDExtensionFlag(const bool& flag) = 0;

  /*! \brief  Get stream identifier extension.

      \returns  Stream identifier extension.
  */
  virtual const Bit7T& GetStreamIDExtension() const = 0;

  /*! \brief  Set stream identifier extension.

      If a previous stream identifier extension existed, it must be
      replaced with the one given.

      \param    streamIDExtension       input, stream identifier extension to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStreamIDExtension(const Bit7T& streamIDExtension) = 0;
};

/*!	\brief Last transport stream IPMP control information part.

    Last part of the structure containing IPMP control information classes in a
    transport stream.

    \warning  Syntactically, in a last part, the (syntactic) values of part number
              and last part number MUST be equal.
*/
class ILastTStreamIPMPControlInfoPart: public ITStreamIPMPControlInfoPart {
public:
  virtual ~ILastTStreamIPMPControlInfoPart() {};

  /*! \brief  Signature and certificate container.

      Since signature and certificate container is not mandatory, zero value of
      the pointer indicates that the last part doesn't contain signature, thus
      that the control information classes contained in the control information
      are not signed.

      \returns  Signature and certificate container pointer. Zero value
                indicates that it's not present.
  */
  virtual ISigCertContainer* GetSigCertContainer() const = 0;

  /*! \brief  Create new signature and certificate container and save it as
              signature and certificate container contained in this part.

      \warning  If a previous signature and certificate container existed,
                it must be replaced with the newly created one.

      \param  container      output, newly created signature and certificate
                             container pointer (if successful).

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateSigCertContainer(ISigCertContainer** container) = 0;

  /*! \brief  Encode the class as a byte array (without CRC code).

      This function is used for calculating CRC codes.

      \param  encoded     output, encoded class.

      \returns  Boolean indicating success or failure. If failed, log
                will contain error description.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const {
    encoded = ByteSeq();
    encoded += GetTableID();
    ByteT tmp = (GetSectionSyntaxIndicator() == true)? (0x80): (0x0);
    UInt16T sectionLength = 12 + GetIPMPControlInfos().GetLength();
    ByteSeq sigEnc;
    if (GetSigCertContainer() != 0) {
      if (GetSigCertContainer()->MPEG2Encode(sigEnc) == false) {
        return false;
      }
      sectionLength += (UInt16T)(sigEnc.GetLength());
    }
    if ((sectionLength & 0xf000) != 0) {
      //  Invalid section length (greater or equal 1 << 12).
      return false;
    }
    sectionLength |= (tmp << 8);
    encoded += ByteSeq(sectionLength);
    tmp = (ByteT)(GetIPMPControlInfoVersion() << 1);
    tmp |= (GetCurrentNextIndicator() == true)? (1): (0);
    encoded += tmp;
    encoded += GetPartNumber();
    encoded += GetPartNumber();
    encoded += ByteSeq(GetTotalControlInfoClassesLen());
    if (GetIPMPControlInfos().GetLength() >= (1 << 16)) {
      return false;
    }
    encoded += ByteSeq((UInt16T)(GetIPMPControlInfos().GetLength()));
    encoded += GetIPMPControlInfos();
    if (GetSigCertContainer() != 0) {
      encoded += 0x80;
      encoded += sigEnc;
    } else {
      encoded += 0x0;
    }
    return true;
  }
};

/*!	\brief Intermediate transport stream IPMP control information part.

    Intermediate part of the structure containing IPMP control information
    classes in a transport stream.
*/
class IInterTStreamIPMPControlInfoPart: public ITStreamIPMPControlInfoPart {
public:
  virtual ~IInterTStreamIPMPControlInfoPart() {};

  /*! \brief  Get last part number.

      Last part number represents index of the last part in a row of parts
      constituting an IPMP control information.

      \returns  Last part number.
  */
  virtual const ByteT& GetLastPartNumber() const = 0;

  /*! \brief  Set last part number.

      If previous last part number existed, it must be replaced with the one given.

      \param    number       input, last part number to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetLastPartNumber(const ByteT& number) = 0;

  /*! \brief  Encode the class as a byte array (without CRC code).

      This function is used for calculating CRC codes.

      \param  encoded     output, encoded class.

      \returns  Boolean indicating success or failure. If failed, log
                will contain error description.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const {
    encoded = ByteSeq(GetTableID());
    ByteT tmp = (GetSectionSyntaxIndicator() == true)? (0x80): (0x0);
    UInt16T sectionLength = 11 + GetIPMPControlInfos().GetLength();
    if ((sectionLength & 0xf000) != 0) {
      //  Invalid section length (greater or equal 1 << 12).
      return false;
    }
    sectionLength |= (tmp << 8);
    encoded += ByteSeq(sectionLength);
    tmp = (ByteT)(GetIPMPControlInfoVersion() << 1);
    tmp |= (GetCurrentNextIndicator() == true)? (1): (0);
    encoded += tmp;
    encoded += GetPartNumber();
    encoded += GetLastPartNumber();
    encoded += ByteSeq(GetTotalControlInfoClassesLen());
    if (GetIPMPControlInfos().GetLength() >= (1 << 16)) {
      return false;
    }
    encoded += ByteSeq(GetIPMPControlInfos().GetLength());
    encoded += GetIPMPControlInfos();
    return true;
  }
};

/*!	\brief Last program stream IPMP control information part.

    Last part of the structure containing IPMP control information classes in a
    program stream.

    \warning  Syntactically, in a last part, the (syntactic) values of part number
              and last part number MUST be equal.
*/
class ILastPStreamIPMPControlInfoPart: public IPStreamIPMPControlInfoPart {
public:
  virtual ~ILastPStreamIPMPControlInfoPart() {};

  /*! \brief  Signature and certificate container.

      Since signature and certificate container is not mandatory, zero value of
      the pointer indicates that the last part doesn't contain signature, thus
      that the control information classes contained in the control information
      are not signed.

      \returns  Signature and certificate container pointer. Zero value
                indicates that it's not present.
  */
  virtual ISigCertContainer* GetSigCertContainer() const = 0;

  /*! \brief  Create new signature and certificate container and save it as
              signature and certificate container contained in this part.

      \warning  If a previous signature and certificate container existed,
                it must be replaced with the newly created one.

      \param  container      output, newly created signature and certificate
                             container pointer (if successful).

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateSigCertContainer(ISigCertContainer** container) = 0;

  /*! \brief  Encode the class as a byte array (without CRC code).

      This function is used for calculating CRC codes.

      \param  encoded     output, encoded class.

      \returns  Boolean indicating success or failure. If failed, log
                will contain error description.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const {
    encoded = ByteSeq(GetPacketStartCodePrefix());
    encoded += GetStreamID();
    UInt16T sectionLength = 16 + GetIPMPControlInfos().GetLength();
    ByteSeq sigEnc;
    if (GetSigCertContainer() != 0) {
      if (GetSigCertContainer()->MPEG2Encode(sigEnc) == false) {
        return false;
      }
      sectionLength += (UInt16T)(sigEnc.GetLength());
    }
    if ((sectionLength & 0xf000) != 0) {
      //  Invalid section length (greater or equal 1 << 12).
      return false;
    }
    encoded += ByteSeq(sectionLength);
    UInt16T tmp16 = 0x8100;
    tmp16 |= (GetPESExtensionFlag() == true)? (1): (0);
    encoded += ByteSeq(tmp16);
    encoded += 0x03;
    encoded += (ByteT)((GetPESExtensionFlag2() == true)? (1): (0));
    encoded += 0x81;
    ByteT tmp8 = (GetStreamIDExtensionFlag() == true)? (0x80): (0);
    tmp8 |= GetStreamIDExtension();
    encoded += tmp8;
    tmp8 = GetIPMPControlInfoVersion() << 3;
    tmp8 |= (GetCurrentNextIndicator() == true)? (0x4): (0);
    encoded += tmp8;
    encoded += GetPartNumber();
    encoded += GetPartNumber();
    if (GetIPMPControlInfos().GetLength() >= (1 << 16)) {
      return false;
    }
    encoded += ByteSeq((UInt16T)(GetIPMPControlInfos().GetLength()));
    encoded += GetIPMPControlInfos();
    if (GetSigCertContainer() != 0) {
      encoded += 0x80;
      encoded += sigEnc;
    } else {
      encoded += 0x0;
    }
    return true;
  }
};

/*!	\brief Intermediate program stream IPMP control information part.

    Intermediate part of the structure containing IPMP control information
    classes in a program stream.
*/
class IInterPStreamIPMPControlInfoPart: public IPStreamIPMPControlInfoPart {
public:
  virtual ~IInterPStreamIPMPControlInfoPart() {};

  /*! \brief  Get last part number.

      Last part number represents index of the last part in a row of parts
      constituting an IPMP control information.

      \returns  Last part number.
  */
  virtual const ByteT& GetLastPartNumber() const = 0;

  /*! \brief  Set last part number.

      If previous last part number existed, it must be replaced with the one given.

      \param    number       input, last part number to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetLastPartNumber(const ByteT& number) = 0;

  /*! \brief  Encode the class as a byte array (without CRC code).

      This function is used for calculating CRC codes.

      \param  encoded     output, encoded class.

      \returns  Boolean indicating success or failure. If failed, log
                will contain error description.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const {
    encoded = ByteSeq(GetPacketStartCodePrefix());
    encoded += GetStreamID();
    UInt16T sectionLength = 15 + GetIPMPControlInfos().GetLength();
    if ((sectionLength & 0xf000) != 0) {
      //  Invalid section length (greater or equal 1 << 12).
      return false;
    }
    encoded += ByteSeq(sectionLength);
    UInt16T tmp16 = 0x8100;
    tmp16 |= (GetPESExtensionFlag() == true)? (1): (0);
    encoded += ByteSeq(tmp16);
    encoded += 0x03;
    encoded += (ByteT)((GetPESExtensionFlag2() == true)? (1): (0));
    encoded += 0x81;
    ByteT tmp8 = (GetStreamIDExtensionFlag() == true)? (0x80): (0);
    tmp8 |= GetStreamIDExtension();
    encoded += tmp8;
    tmp8 = GetIPMPControlInfoVersion() << 3;
    tmp8 |= (GetCurrentNextIndicator() == true)? (0x4): (0);
    encoded += tmp8;
    encoded += GetPartNumber();
    encoded += GetLastPartNumber();
    if (GetIPMPControlInfos().GetLength() >= (1 << 16)) {
      return false;
    }
    encoded += ByteSeq(GetIPMPControlInfos().GetLength());
    encoded += GetIPMPControlInfos();
    return true;
  }
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(IIPMPCONTROLINFOPART_H)
