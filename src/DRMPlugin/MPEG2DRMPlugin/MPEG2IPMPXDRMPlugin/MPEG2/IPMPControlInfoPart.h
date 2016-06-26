/**	\file IPMPControlInfoPart.h

    \ingroup drmplayer
    \ingroup drmencoder

	Test implementation of the IPMP control information structure.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPMPCONTROLINFOPART_H)
#define IPMPCONTROLINFOPART_H

#include "BasicTypes.h"
#include "SigCertContainer.h"
#include "CRC32Calculator.h"

#include "IIPMPControlInfoPart.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief Last transport stream IPMP control information part.

    Last part of the structure containing IPMP control information classes in a
    transport stream.

    \warning  Syntactically, in a last part, the (syntactic) values of part number
              and last part number MUST be equal.
*/
class LastTStreamIPMPControlInfoPart: public ILastTStreamIPMPControlInfoPart {
public:
  /*! \brief  Constructor.
  */
  LastTStreamIPMPControlInfoPart(): cVersion(0), nextIndicator(false),
    part(0), infos(), crcCode(0), table(0), syntaxIndicator(false),
    cLen(0), sigCert(0) {
  }

  /*! \brief  Constructor.

      \param  version         control info version.
      \param  indicator       current next indicator.
      \param  number          part number.
      \param  classes         control info classes (encoded).
      \param  crc             CRC32 code.
      \param  tableID         table identifier.
      \param  sIndicator      section syntax indicator.
      \param  len             total control info classes length.
      \param  sig             signature and certificate container.
  */
  LastTStreamIPMPControlInfoPart(const Bit5T& version, const bool& indicator,
    const ByteT& number, const ByteSeq& classes, const UInt32T& crc,
    const ByteT& tableID, const bool& sIndicator, const UInt16T& len,
    ISigCertContainer* sig): cVersion(version), nextIndicator(indicator),
    part(number), infos(classes), crcCode(crc), table(tableID),
    syntaxIndicator(sIndicator), cLen(len), sigCert(sig) {
  }


  virtual ~LastTStreamIPMPControlInfoPart() {
    if (sigCert != 0) delete sigCert; sigCert = 0;
  }

  /*! \brief  Get IPMP control information version.

      \returns  5-bit number representing version.
  */
  virtual const Bit5T& GetIPMPControlInfoVersion() const {
    return cVersion;
  }

  /*! \brief  Set IPMP control information version.

      If a previous IPMP control information version existed, it must be
      replaced with the one given.

      \param    version       input, version to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPControlInfoVersion(const Bit5T& version) {
    cVersion = version;
    return true;
  }

  /*! \brief  Get indicator whether the control information is currently
              applicable.

      If indicator is true, the control information is currently applicable,
      if not it is the next control information to become applicable.

      \returns  Boolean indicating current applicability.
  */
  virtual const bool& GetCurrentNextIndicator() const {
    return nextIndicator;
  }

  /*! \brief  Set indicator whether the control information is currently
              applicable.

      If a previous indicator existed, it must be replaced with the one given.

      \param    indicator       input, current applicability indicator to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCurrentNextIndicator(const bool& indicator) {
    nextIndicator = indicator;
    return true;
  }

  /*! \brief  Get part number.

      Part number respresents index of the part in a row of parts constituting
      IPMP control information.

      \returns  Part number.
  */
  virtual const ByteT& GetPartNumber() const {
    return part;
  }

  /*! \brief  Set part number.

      If previous part number existed, it must be replaced with the one given.

      \param    number       input, part number to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPartNumber(const ByteT& number) {
    part = number;
    return true;
  }

  /*! \brief  Get encoded control info classes.

      \returns  Encoded control info classes.
  */
  virtual const ByteSeq& GetIPMPControlInfos() const {
    return infos;
  }

  /*! \brief  Set encoded control info classes.

      If previous encoded control info classes existed, it must be replaced
      with the one given.

      \param    classes       input, encoded control info classes to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPControlInfos(const ByteSeq& classes) {
    infos = classes;
    return true;
  }

  /*! \brief  Get 32-bit CRC code.

      \returns  Number representing 32-bit CRC code.
  */
  virtual const UInt32T& GetCRC32Code() {
    return crcCode;
  }

  /*! \brief  Set 32-bit CRC code.

      If a previous CRC code existed, it must be replaced with the one given.

      \param    crc       input, CRC code to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCRC32Code(const UInt32T& crc) {
    crcCode = crc;
    return true;
  }

  /*! \brief  Get table identifier.

      \returns  Number representing identifier.
  */
  virtual const ByteT& GetTableID() const {
    return table;
  }

  /*! \brief  Set table identifier.

      If a previous table identifier existed, it must be replaced with the 
      one given.

      \param    tableID       input, table identifier to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetTableID(const ByteT& tableID) {
    table = tableID;
    return true;
  }

  /*! \brief  Get section syntax indicator.

      \returns  Section syntax indicator.
  */
  virtual const bool& GetSectionSyntaxIndicator() const {
    return syntaxIndicator;
  }

  /*! \brief  Set section syntax indicator.

      If a previous section syntax indicator existed, it must be replaced
      with the one given.

      \param    indicator       input, section syntax indicator to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetSectionSyntaxIndicator(const bool& indicator) {
    syntaxIndicator = indicator;
    return true;
  }

  /*! \brief  Get total control information classes length.

      Total control information classes length is the total length in all
      the parts constituting the same IPMP control information structure.

      \returns  total control information classes length.
  */
  virtual const UInt16T& GetTotalControlInfoClassesLen() const {
    return cLen;
  }

  /*! \brief  Set total control information classes length.

      If a previous total control information classes length existed, it must
      be replaced with the one given.

      \param    length        input, total control information classes length
                              to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetTotalControlInfoClassesLen(const UInt16T& length) {
    cLen = length;
    return true;
  }

  /*! \brief  Signature and certificate container.

      Since signature and certificate container is not mandatory, zero value of
      the pointer indicates that the last part doesn't contain signature, thus
      that the control information classes contained in the control information
      are not signed.

      \returns  Signature and certificate container pointer. Zero value
                indicates that it's not present.
  */
  virtual ISigCertContainer* GetSigCertContainer() const {
    return sigCert;
  }

  /*! \brief  Create new signature and certificate container and save it as
              signature and certificate container contained in this part.

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

      \param  encoded     output, encoded class.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(ByteSeq& encoded) const {
    if (ILastTStreamIPMPControlInfoPart::MPEG2Encode(encoded) == false) {
      return false;
    }
    CRC32Calculator crc;
    UInt32T crc32 = crc.GetCRC(encoded.GetFirst(), encoded.GetLength());
    encoded += ByteSeq(crc32);
    return true;
  }

private:
  Bit5T cVersion;
  bool nextIndicator;
  ByteT part;
  ByteSeq infos;
  UInt32T crcCode;
  ByteT table;
  bool syntaxIndicator;
  UInt16T cLen;
  ISigCertContainer* sigCert;
};

/*!	\brief Intermediate transport stream IPMP control information part.

    Intermediate part of the structure containing IPMP control information
    classes in a transport stream.
*/
class InterTStreamIPMPControlInfoPart: public IInterTStreamIPMPControlInfoPart {
public:
  /*! \brief  Constructor.
  */
  InterTStreamIPMPControlInfoPart(): cVersion(0), nextIndicator(false),
    part(0), infos(), crcCode(0), table(0), syntaxIndicator(false),
    cLen(0), last(0) {
  }

  /*! \brief  Constructor.

      \param  version         control info version.
      \param  indicator       current next indicator.
      \param  number          part number.
      \param  classes         control info classes (encoded).
      \param  crc             CRC32 code.
      \param  tableID         table identifier.
      \param  sIndicator      section syntax indicator.
      \param  len             total control info classes length.
      \param  lst             last part number.
  */
  InterTStreamIPMPControlInfoPart(const Bit5T& version, const bool& indicator,
    const ByteT& number, const ByteSeq& classes, const UInt32T& crc,
    const ByteT& tableID, const bool& sIndicator, const UInt16T& len,
    const ByteT& lst): cVersion(version), nextIndicator(indicator), part(number),
    infos(classes), crcCode(crc), table(tableID), syntaxIndicator(sIndicator),
    cLen(len), last(lst) {
  }

  virtual ~InterTStreamIPMPControlInfoPart() {
  }

  /*! \brief  Get IPMP control information version.

      \returns  5-bit number representing version.
  */
  virtual const Bit5T& GetIPMPControlInfoVersion() const {
    return cVersion;
  }

  /*! \brief  Set IPMP control information version.

      If a previous IPMP control information version existed, it must be
      replaced with the one given.

      \param    version       input, version to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPControlInfoVersion(const Bit5T& version) {
    cVersion = version;
    return true;
  }

  /*! \brief  Get indicator whether the control information is currently
              applicable.

      If indicator is true, the control information is currently applicable,
      if not it is the next control information to become applicable.

      \returns  Boolean indicating current applicability.
  */
  virtual const bool& GetCurrentNextIndicator() const {
    return nextIndicator;
  }

  /*! \brief  Set indicator whether the control information is currently
              applicable.

      If a previous indicator existed, it must be replaced with the one given.

      \param    indicator       input, current applicability indicator to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCurrentNextIndicator(const bool& indicator) {
    nextIndicator = indicator;
    return true;
  }

  /*! \brief  Get part number.

      Part number respresents index of the part in a row of parts constituting
      IPMP control information.

      \returns  Part number.
  */
  virtual const ByteT& GetPartNumber() const {
    return part;
  }

  /*! \brief  Set part number.

      If previous part number existed, it must be replaced with the one given.

      \param    number       input, part number to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPartNumber(const ByteT& number) {
    part = number;
    return true;
  }

  /*! \brief  Get encoded control info classes.

      \returns  Encoded control info classes.
  */
  virtual const ByteSeq& GetIPMPControlInfos() const {
    return infos;
  }

  /*! \brief  Set encoded control info classes.

      If previous encoded control info classes existed, it must be replaced
      with the one given.

      \param    classes       input, encoded control info classes to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPControlInfos(const ByteSeq& classes) {
    infos = classes;
    return true;
  }

  /*! \brief  Get 32-bit CRC code.

      \returns  Number representing 32-bit CRC code.
  */
  virtual const UInt32T& GetCRC32Code() {
    return crcCode;
  }

  /*! \brief  Set 32-bit CRC code.

      If a previous CRC code existed, it must be replaced with the one given.

      \param    crc       input, CRC code to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCRC32Code(const UInt32T& crc) {
    crcCode = crc;
    return true;
  }

  /*! \brief  Get table identifier.

      \returns  Number representing identifier.
  */
  virtual const ByteT& GetTableID() const {
    return table;
  }

  /*! \brief  Set table identifier.

      If a previous table identifier existed, it must be replaced with the 
      one given.

      \param    tableID       input, table identifier to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetTableID(const ByteT& tableID) {
    table = tableID;
    return true;
  }

  /*! \brief  Get section syntax indicator.

      \returns  Section syntax indicator.
  */
  virtual const bool& GetSectionSyntaxIndicator() const {
    return syntaxIndicator;
  }

  /*! \brief  Set section syntax indicator.

      If a previous section syntax indicator existed, it must be replaced
      with the one given.

      \param    indicator       input, section syntax indicator to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetSectionSyntaxIndicator(const bool& indicator) {
    syntaxIndicator = indicator;
    return true;
  }

  /*! \brief  Get total control information classes length.

      Total control information classes length is the total length in all
      the parts constituting the same IPMP control information structure.

      \returns  total control information classes length.
  */
  virtual const UInt16T& GetTotalControlInfoClassesLen() const {
    return cLen;
  }

  /*! \brief  Set total control information classes length.

      If a previous total control information classes length existed, it must
      be replaced with the one given.

      \param    length        input, total control information classes length
                              to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetTotalControlInfoClassesLen(const UInt16T& length) {
    cLen = length;
    return true;
  }

  /*! \brief  Get last part number.

      Last part number represents index of the last part in a row of parts
      constituting an IPMP control information.

      \returns  Last part number.
  */
  virtual const ByteT& GetLastPartNumber() const {
    return last;
  }

  /*! \brief  Set last part number.

      If previous last part number existed, it must be replaced with the one given.

      \param    number       input, last part number to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetLastPartNumber(const ByteT& number) {
    last = number;
    return true;
  }

  /*! \brief  Encode.

      \param  encoded     output, encoded class.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(ByteSeq& encoded) const {
    if (IInterTStreamIPMPControlInfoPart::MPEG2Encode(encoded) == false) {
      return false;
    }
    CRC32Calculator crc;
    UInt32T crc32 = crc.GetCRC(encoded.GetFirst(), encoded.GetLength());
    encoded += ByteSeq(crc32);
    return true;
  }

private:
  Bit5T cVersion;
  bool nextIndicator;
  ByteT part;
  ByteSeq infos;
  UInt32T crcCode;
  ByteT table;
  bool syntaxIndicator;
  UInt16T cLen;
  ByteT last;
};

/*!	\brief Last program stream IPMP control information part.

    Last part of the structure containing IPMP control information classes in a
    program stream.

    \warning  Syntactically, in a last part, the (syntactic) values of part number
              and last part number MUST be equal.
*/
class LastPStreamIPMPControlInfoPart: public ILastPStreamIPMPControlInfoPart {
public:
  /*! \brief  Constructor.
  */
  LastPStreamIPMPControlInfoPart(): cVersion(), nextIndicator(false),
    part(0), infos(), crcCode(0), packet((UInt32T)0), stream(0),
    pesFlag(false), pesFlag2(false), streamIDExtFlag(false), streamIDExt(0),
    sigCert(0) {
  }

  /*! \brief  Constructor.

      \param  version         control info version.
      \param  indicator       current next indicator.
      \param  number          part number.
      \param  classes         control info classes (encoded).
      \param  crc             CRC32 code.
      \param  pack            packet start code prefix.
      \param  streamID        stream identifier.
      \param  flag            PES flag.
      \param  flag2           PES flag 2.
      \param  extFlag         stream ID extension flag.
      \param  ext             stream ID extension.
      \param  sig             signature and certificate container.
  */
  LastPStreamIPMPControlInfoPart(const Bit5T& version, const bool& indicator,
    const ByteT& number, const ByteSeq& classes, const UInt32T& crc,
    const Bit24T& pack, const ByteT streamID, const bool& flag,
    const bool& flag2, const bool& extFlag, const Bit7T& ext,
    ISigCertContainer* sig): cVersion(version), nextIndicator(indicator), part(number),
    infos(classes), crcCode(crc), packet(pack), stream(streamID), pesFlag(flag),
    pesFlag2(flag2), streamIDExtFlag(extFlag), streamIDExt(ext), sigCert(sig) {
  }

  virtual ~LastPStreamIPMPControlInfoPart() {
    if (sigCert != 0) delete sigCert; sigCert = 0;
  }

  /*! \brief  Get IPMP control information version.

      \returns  5-bit number representing version.
  */
  virtual const Bit5T& GetIPMPControlInfoVersion() const {
    return cVersion;
  }

  /*! \brief  Set IPMP control information version.

      If a previous IPMP control information version existed, it must be
      replaced with the one given.

      \param    version       input, version to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPControlInfoVersion(const Bit5T& version) {
    cVersion = version;
    return true;
  }

  /*! \brief  Get indicator whether the control information is currently
              applicable.

      If indicator is true, the control information is currently applicable,
      if not it is the next control information to become applicable.

      \returns  Boolean indicating current applicability.
  */
  virtual const bool& GetCurrentNextIndicator() const {
    return nextIndicator;
  }

  /*! \brief  Set indicator whether the control information is currently
              applicable.

      If a previous indicator existed, it must be replaced with the one given.

      \param    indicator       input, current applicability indicator to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCurrentNextIndicator(const bool& indicator) {
    nextIndicator = indicator;
    return true;
  }

  /*! \brief  Get part number.

      Part number respresents index of the part in a row of parts constituting
      IPMP control information.

      \returns  Part number.
  */
  virtual const ByteT& GetPartNumber() const {
    return part;
  }

  /*! \brief  Set part number.

      If previous part number existed, it must be replaced with the one given.

      \param    number       input, part number to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPartNumber(const ByteT& number) {
    part = number;
    return true;
  }

  /*! \brief  Get encoded control info classes.

      \returns  Encoded control info classes.
  */
  virtual const ByteSeq& GetIPMPControlInfos() const {
    return infos;
  }

  /*! \brief  Set encoded control info classes.

      If previous encoded control info classes existed, it must be replaced
      with the one given.

      \param    classes       input, encoded control info classes to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPControlInfos(const ByteSeq& classes) {
    infos = classes;
    return true;
  }

  /*! \brief  Get 32-bit CRC code.

      \returns  Number representing 32-bit CRC code.
  */
  virtual const UInt32T& GetCRC32Code() {
    return crcCode;
  }

  /*! \brief  Set 32-bit CRC code.

      If a previous CRC code existed, it must be replaced with the one given.

      \param    crc       input, CRC code to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCRC32Code(const UInt32T& crc) {
    crcCode = crc;
    return true;
  }

  /*! \brief  Get packet start code prefix.

      \returns  Number representing packet start code prefix.
  */
  virtual const Bit24T& GetPacketStartCodePrefix() const {
    return packet;
  }

  /*! \brief  Set packet start code prefix.

      If a previous packet start code prefix existed, it must be replaced
      with the one given.

      \param    prefix       input, packet start code prefix to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPacketStartCodePrefix(const Bit24T& prefix) {
    packet = prefix;
    return true;
  }

  /*! \brief  Get stream identifier.

      \returns  Number representing stream identifier.
  */
  virtual const ByteT& GetStreamID() const {
    return stream;
  }

  /*! \brief  Set stream identifier.

      If a previous stream identifier existed, it must be replaced with
      the one given.

      \param    streamID       input, stream identifier to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStreamID(const ByteT& streamID) {
    stream = streamID;
    return true;
  }

  /*! \brief  Get PES extension flag.

      \returns  PES extension flag.
  */
  virtual const bool& GetPESExtensionFlag() const {
    return pesFlag;
  }

  /*! \brief  Set PES extension flag.

      If a previous PES extension flag existed, it must be replaced with
      the one given.

      \param    flag       input, PES extension flag to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPESExtensionFlag(const bool& flag) {
    pesFlag = flag;
    return true;
  }

  /*! \brief  Get PES extension flag 2.

      \returns  PES extension flag 2.
  */
  virtual const bool& GetPESExtensionFlag2() const {
    return pesFlag2;
  }

  /*! \brief  Set PES extension flag 2.

      If a previous PES extension flag 2 existed, it must be replaced with
      the one given.

      \param    flag       input, PES extension flag 2 to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPESExtensionFlag2(const bool& flag) {
    pesFlag2 = flag;
    return true;
  }

  /*! \brief  Get stream identifier extension flag.

      \returns  Stream identifier extension flag.
  */
  virtual const bool& GetStreamIDExtensionFlag() const {
    return streamIDExtFlag;
  }

  /*! \brief  Set stream identifier extension flag.

      If a previous stream identifier extension flag existed, it must be
      replaced with the one given.

      \param    flag       input, stream identifier extension flag to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStreamIDExtensionFlag(const bool& flag) {
    streamIDExtFlag = flag;
    return true;
  }

  /*! \brief  Get stream identifier extension.

      \returns  Stream identifier extension.
  */
  virtual const Bit7T& GetStreamIDExtension() const {
    return streamIDExt;
  }

  /*! \brief  Set stream identifier extension.

      If a previous stream identifier extension existed, it must be
      replaced with the one given.

      \param    streamIDExtension       input, stream identifier extension to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStreamIDExtension(const Bit7T& streamIDExtension) {
    streamIDExt = streamIDExtension;
    return true;
  }

  /*! \brief  Signature and certificate container.

      Since signature and certificate container is not mandatory, zero value of
      the pointer indicates that the last part doesn't contain signature, thus
      that the control information classes contained in the control information
      are not signed.

      \returns  Signature and certificate container pointer. Zero value
                indicates that it's not present.
  */
  virtual ISigCertContainer* GetSigCertContainer() const {
    return sigCert;
  }

  /*! \brief  Create new signature and certificate container and save it as
              signature and certificate container contained in this part.

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

      \param  encoded     output, encoded class.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(ByteSeq& encoded) const {
    if (ILastPStreamIPMPControlInfoPart::MPEG2Encode(encoded) == false) {
      return false;
    }
    CRC32Calculator crc;
    UInt32T crc32 = crc.GetCRC(encoded.GetFirst(), encoded.GetLength());
    encoded += ByteSeq(crc32);
    return true;
  }

private:
  Bit5T cVersion;
  bool nextIndicator;
  ByteT part;
  ByteSeq infos;
  UInt32T crcCode;
  Bit24T packet;
  ByteT stream;
  bool pesFlag;
  bool pesFlag2;
  bool streamIDExtFlag;
  Bit7T streamIDExt;
  ISigCertContainer* sigCert;
};

/*!	\brief Intermediate program stream IPMP control information part.

    Intermediate part of the structure containing IPMP control information
    classes in a program stream.
*/
class InterPStreamIPMPControlInfoPart: public IInterPStreamIPMPControlInfoPart {
public:
  /*! \brief  Constructor.
  */
  InterPStreamIPMPControlInfoPart(): cVersion(), nextIndicator(false),
    part(0), infos(), crcCode(0), packet((UInt32T)0), stream(0),
    pesFlag(false), pesFlag2(false), streamIDExtFlag(false), streamIDExt(0),
    last(0) {
  }

  /*! \brief  Constructor.

      \param  version         control info version.
      \param  indicator       current next indicator.
      \param  number          part number.
      \param  classes         control info classes (encoded).
      \param  crc             CRC32 code.
      \param  pack            packet start code prefix.
      \param  streamID        stream identifier.
      \param  flag            PES flag.
      \param  flag2           PES flag 2.
      \param  extFlag         stream ID extension flag.
      \param  ext             stream ID extension.
      \param  lst             last part number.
  */
  InterPStreamIPMPControlInfoPart(const Bit5T& version, const bool& indicator,
    const ByteT& number, const ByteSeq& classes, const UInt32T& crc,
    const Bit24T& pack, const ByteT streamID, const bool& flag,
    const bool& flag2, const bool& extFlag, const Bit7T& ext,
    const ByteT& lst): cVersion(version), nextIndicator(indicator), part(number),
    infos(classes), crcCode(crc), packet(pack), stream(streamID), pesFlag(flag),
    pesFlag2(flag2), streamIDExtFlag(extFlag), streamIDExt(ext), last(lst) {
  }

  virtual ~InterPStreamIPMPControlInfoPart() {
  }

  /*! \brief  Get IPMP control information version.

      \returns  5-bit number representing version.
  */
  virtual const Bit5T& GetIPMPControlInfoVersion() const {
    return cVersion;
  }

  /*! \brief  Set IPMP control information version.

      If a previous IPMP control information version existed, it must be
      replaced with the one given.

      \param    version       input, version to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPControlInfoVersion(const Bit5T& version) {
    cVersion = version;
    return true;
  }

  /*! \brief  Get indicator whether the control information is currently
              applicable.

      If indicator is true, the control information is currently applicable,
      if not it is the next control information to become applicable.

      \returns  Boolean indicating current applicability.
  */
  virtual const bool& GetCurrentNextIndicator() const {
    return nextIndicator;
  }

  /*! \brief  Set indicator whether the control information is currently
              applicable.

      If a previous indicator existed, it must be replaced with the one given.

      \param    indicator       input, current applicability indicator to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCurrentNextIndicator(const bool& indicator) {
    nextIndicator = indicator;
    return true;
  }

  /*! \brief  Get part number.

      Part number respresents index of the part in a row of parts constituting
      IPMP control information.

      \returns  Part number.
  */
  virtual const ByteT& GetPartNumber() const {
    return part;
  }

  /*! \brief  Set part number.

      If previous part number existed, it must be replaced with the one given.

      \param    number       input, part number to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPartNumber(const ByteT& number) {
    part = number;
    return true;
  }

  /*! \brief  Get encoded control info classes.

      \returns  Encoded control info classes.
  */
  virtual const ByteSeq& GetIPMPControlInfos() const {
    return infos;
  }

  /*! \brief  Set encoded control info classes.

      If previous encoded control info classes existed, it must be replaced
      with the one given.

      \param    classes       input, encoded control info classes to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetIPMPControlInfos(const ByteSeq& classes) {
    infos = classes;
    return true;
  }

  /*! \brief  Get 32-bit CRC code.

      \returns  Number representing 32-bit CRC code.
  */
  virtual const UInt32T& GetCRC32Code() {
    return crcCode;
  }

  /*! \brief  Set 32-bit CRC code.

      If a previous CRC code existed, it must be replaced with the one given.

      \param    crc       input, CRC code to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetCRC32Code(const UInt32T& crc) {
    crcCode = crc;
    return true;
  }

  /*! \brief  Get packet start code prefix.

      \returns  Number representing packet start code prefix.
  */
  virtual const Bit24T& GetPacketStartCodePrefix() const {
    return packet;
  }

  /*! \brief  Set packet start code prefix.

      If a previous packet start code prefix existed, it must be replaced
      with the one given.

      \param    prefix       input, packet start code prefix to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPacketStartCodePrefix(const Bit24T& prefix) {
    packet = prefix;
    return true;
  }

  /*! \brief  Get stream identifier.

      \returns  Number representing stream identifier.
  */
  virtual const ByteT& GetStreamID() const {
    return stream;
  }

  /*! \brief  Set stream identifier.

      If a previous stream identifier existed, it must be replaced with
      the one given.

      \param    streamID       input, stream identifier to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStreamID(const ByteT& streamID) {
    stream = streamID;
    return true;
  }

  /*! \brief  Get PES extension flag.

      \returns  PES extension flag.
  */
  virtual const bool& GetPESExtensionFlag() const {
    return pesFlag;
  }

  /*! \brief  Set PES extension flag.

      If a previous PES extension flag existed, it must be replaced with
      the one given.

      \param    flag       input, PES extension flag to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPESExtensionFlag(const bool& flag) {
    pesFlag = flag;
    return true;
  }

  /*! \brief  Get PES extension flag 2.

      \returns  PES extension flag 2.
  */
  virtual const bool& GetPESExtensionFlag2() const {
    return pesFlag2;
  }

  /*! \brief  Set PES extension flag 2.

      If a previous PES extension flag 2 existed, it must be replaced with
      the one given.

      \param    flag       input, PES extension flag 2 to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetPESExtensionFlag2(const bool& flag) {
    pesFlag2 = flag;
    return true;
  }

  /*! \brief  Get stream identifier extension flag.

      \returns  Stream identifier extension flag.
  */
  virtual const bool& GetStreamIDExtensionFlag() const {
    return streamIDExtFlag;
  }

  /*! \brief  Set stream identifier extension flag.

      If a previous stream identifier extension flag existed, it must be
      replaced with the one given.

      \param    flag       input, stream identifier extension flag to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStreamIDExtensionFlag(const bool& flag) {
    streamIDExtFlag = flag;
    return true;
  }

  /*! \brief  Get stream identifier extension.

      \returns  Stream identifier extension.
  */
  virtual const Bit7T& GetStreamIDExtension() const {
    return streamIDExt;
  }

  /*! \brief  Set stream identifier extension.

      If a previous stream identifier extension existed, it must be
      replaced with the one given.

      \param    streamIDExtension       input, stream identifier extension to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStreamIDExtension(const Bit7T& streamIDExtension) {
    streamIDExt = streamIDExtension;
    return true;
  }

  /*! \brief  Get last part number.

      Last part number represents index of the last part in a row of parts
      constituting an IPMP control information.

      \returns  Last part number.
  */
  virtual const ByteT& GetLastPartNumber() const {
    return last;
  }

  /*! \brief  Set last part number.

      If previous last part number existed, it must be replaced with the one given.

      \param    number       input, last part number to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetLastPartNumber(const ByteT& number) {
    last = number;
    return true;
  }

  /*! \brief  Encode.

      \param  encoded     output, encoded class.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(ByteSeq& encoded) const {
    if (IInterPStreamIPMPControlInfoPart::MPEG2Encode(encoded) == false) {
      return false;
    }
    CRC32Calculator crc;
    UInt32T crc32 = crc.GetCRC(encoded.GetFirst(), encoded.GetLength());
    encoded += ByteSeq(crc32);
    return true;
  }

private:
  Bit5T cVersion;
  bool nextIndicator;
  ByteT part;
  ByteSeq infos;
  UInt32T crcCode;
  Bit24T packet;
  ByteT stream;
  bool pesFlag;
  bool pesFlag2;
  bool streamIDExtFlag;
  Bit7T streamIDExt;
  ByteT last;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(IPMPCONTROLINFOPART_H)
