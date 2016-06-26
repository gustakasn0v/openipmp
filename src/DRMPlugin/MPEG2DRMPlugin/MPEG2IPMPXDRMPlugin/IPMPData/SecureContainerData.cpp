/**	\file SecureContainerData.cpp

	Secure container classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "SecureContainerData.h"

#include "BasicTypes.h"
#include <vector>
#include "CryptoProvider.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief  Secure container IPMP data with encryption.
*/
/*! \brief  Get encrypted data.

    \returns  Encrypted data.
*/
const ByteSeq& EncSecureContainerIPMPData::GetEncryptedData() const {
  return encrypted;
}

/*!	\brief  Secure container IPMP data with encryption, with MAC and without
            MAC encrypted.
*/
/*! \brief  Get MAC.

    \returns  MAC.
*/
const ByteSeq& MACEncSecureContainerIPMPData::GetMAC() const {
  return mac;
}

/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool MACEncSecureContainerIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPData::MPEG2Encode(0x09, ByteSeq((ByteT)0xc0) + encrypted.MPEG2Encode()
    + mac.MPEG2Encode(), encoded);
}

/*! \brief  Check and decrypt contained data.

    Possible errors are decryption error and MAC check error.

    \param  oper          input, symmetric operator.
    \param  plain         output, checked and decrypted data.

    \returns  Boolean indicating success or failure.
*/
bool MACEncSecureContainerIPMPData::CheckDecrypt(SymmetricOperator* oper,
    ByteSeq& plain) {
  return oper->DecryptAuthenticate(encrypted, mac, plain);
}

/*!	\brief  Secure container IPMP data with encryption, without MAC.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool NMACEncSecureContainerIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPData::MPEG2Encode(0x09, ByteSeq((ByteT)0x80) + encrypted.MPEG2Encode(),
    encoded);
}

/*! \brief  Check and decrypt contained data.

    Possible errors are decryption error and MAC check error.

    \param  oper          input, symmetric operator.
    \param  plain         output, checked and decrypted data.

    \returns  Boolean indicating success or failure.
*/
bool NMACEncSecureContainerIPMPData::CheckDecrypt(SymmetricOperator* oper,
    ByteSeq& plain) {
  return oper->Decrypt(encrypted, plain);
}

/*!	\brief  Secure container IPMP data with encryption, with MAC encrypted.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool EncMACEncSecureContainerIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPData::MPEG2Encode(0x09, ByteSeq((ByteT)0xe0) + encrypted.MPEG2Encode(),
    encoded);
}

/*! \brief  Check and decrypt contained data.

    Possible errors are decryption error and MAC check error.

    \param  oper          input, symmetric operator.
    \param  plain         output, checked and decrypted data.

    \returns  Boolean indicating success or failure.
*/
bool EncMACEncSecureContainerIPMPData::CheckDecrypt(SymmetricOperator* oper,
    ByteSeq& plain) {
  return oper->DecryptAuthenticate(encrypted, plain);
}

/*!	\brief  Secure container IPMP data without encryption.
*/
/*! \brief  Get message.

    \returns  Message.
*/
const ByteSeq& NEncSecureContainerIPMPData::GetMessage() const {
  return message;
}

/*!	\brief  Secure container IPMP data without encryption and with MAC.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool MACNEncSecureContainerIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPData::MPEG2Encode(0x09, ByteSeq((ByteT)0x40) + message.MPEG2Encode()
    + mac.MPEG2Encode(), encoded);
}

/*! \brief  Check and decrypt contained data.

    Possible errors are decryption error and MAC check error.

    \param  oper          input, symmetric operator.
    \param  plain         output, checked and decrypted data.

    \returns  Boolean indicating success or failure.
*/
bool MACNEncSecureContainerIPMPData::CheckDecrypt(SymmetricOperator* oper,
    ByteSeq& plain) {
  plain = message;
  return oper->CheckMAC(message, mac);
}

/*! \brief  Get MAC.

    \returns  MAC.
*/
const ByteSeq& MACNEncSecureContainerIPMPData::GetMAC() const {
  return mac;
}

/*!	\brief  Secure container IPMP data without encryption and without MAC.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool NMACNEncSecureContainerIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPData::MPEG2Encode(0x09, ByteSeq((ByteT)0x00) + message.MPEG2Encode(),
    encoded);
}

/*! \brief  Check and decrypt contained data.

    Possible errors are decryption error and MAC check error.

    \param  oper          input, symmetric operator.
    \param  plain         output, checked and decrypted data.

    \returns  Boolean indicating success or failure.
*/
bool NMACNEncSecureContainerIPMPData::CheckDecrypt(SymmetricOperator* oper,
    ByteSeq& plain) {
  plain = message;
  return true;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
