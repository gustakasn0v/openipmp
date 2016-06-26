/**	\file SecureContainerData.h

	Secure container classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (SECURECONTAINERDATA_H)
#define SECURECONTAINERDATA_H

#include "BasicTypes.h"
#include <vector>
#include "CryptoProvider.h"
#include "IPMPData.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief  Secure container IPMP data.
*/
class SecureContainerIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  SecureContainerIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~SecureContainerIPMPData() {
  }

  /*! \brief  Check and decrypt contained data.

      Possible errors are decryption error and MAC check error.

      \param  oper          input, symmetric operator.
      \param  plain         output, checked and decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CheckDecrypt(SymmetricOperator* oper, ByteSeq& plain) = 0;
};

/*!	\brief  Secure container IPMP data with encryption.
*/
class EncSecureContainerIPMPData: public SecureContainerIPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
      \param  enc       input, encrypted data.
  */
  EncSecureContainerIPMPData(const ByteT& ver, const Bit32T& id, const
    ByteSeq& enc): SecureContainerIPMPData(ver, id), encrypted(enc) {
  }

  virtual ~EncSecureContainerIPMPData() {
  }

  /*! \brief  Get encrypted data.

      \returns  Encrypted data.
  */
  const ByteSeq& GetEncryptedData() const;

protected:
  ByteSeq encrypted;
};

/*!	\brief  Secure container IPMP data with encryption, with MAC and without
            MAC encrypted.
*/
class MACEncSecureContainerIPMPData: public EncSecureContainerIPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
      \param  enc       input, encrypted data.
      \param  mc        input, MAC.
      \param  logger    input, message logger.
  */
  MACEncSecureContainerIPMPData(const ByteT& ver, const Bit32T& id, const
    ByteSeq& enc, const ByteSeq& mc, DRMLogger& logger): EncSecureContainerIPMPData(ver, id, enc),
    mac(mc), dataLogger(logger) {
  }

  virtual ~MACEncSecureContainerIPMPData() {
  }

  /*! \brief  Get MAC.

      \returns  MAC.
  */
  const ByteSeq& GetMAC() const;

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Check and decrypt contained data.

      Possible errors are decryption error and MAC check error.

      \param  oper          input, symmetric operator.
      \param  plain         output, checked and decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CheckDecrypt(SymmetricOperator* oper, ByteSeq& plain);

private:
  ByteSeq mac;
  DRMLogger& dataLogger;
};

/*!	\brief  Secure container IPMP data with encryption, without MAC.
*/
class NMACEncSecureContainerIPMPData: public EncSecureContainerIPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
      \param  enc       input, encrypted data.
      \param  logger    input, message logger.
  */
  NMACEncSecureContainerIPMPData(const ByteT& ver, const Bit32T& id, const
    ByteSeq& enc, DRMLogger& logger): EncSecureContainerIPMPData(ver, id, enc), dataLogger(logger) {
  }

  virtual ~NMACEncSecureContainerIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Check and decrypt contained data.

      Possible errors are decryption error and MAC check error.

      \param  oper          input, symmetric operator.
      \param  plain         output, checked and decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CheckDecrypt(SymmetricOperator* oper, ByteSeq& plain);

private:
  DRMLogger& dataLogger;
};

/*!	\brief  Secure container IPMP data with encryption, with MAC encrypted.
*/
class EncMACEncSecureContainerIPMPData: public EncSecureContainerIPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
      \param  enc       input, encrypted data.
      \param  logger    input, message logger.
  */
  EncMACEncSecureContainerIPMPData(const ByteT& ver, const Bit32T& id, const
    ByteSeq& enc, DRMLogger& logger): EncSecureContainerIPMPData(ver, id, enc), dataLogger(logger) {
  }

  virtual ~EncMACEncSecureContainerIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Check and decrypt contained data.

      Possible errors are decryption error and MAC check error.

      \param  oper          input, symmetric operator.
      \param  plain         output, checked and decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CheckDecrypt(SymmetricOperator* oper, ByteSeq& plain);

private:
  DRMLogger& dataLogger;
};

/*!	\brief  Secure container IPMP data without encryption.
*/
class NEncSecureContainerIPMPData: public SecureContainerIPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
      \param  mess      input, message.
  */
  NEncSecureContainerIPMPData(const ByteT& ver, const Bit32T& id, const
    ByteSeq& mess): SecureContainerIPMPData(ver, id), message(mess) {
  }

  virtual ~NEncSecureContainerIPMPData() {
  }

  /*! \brief  Get message.

      \returns  Message.
  */
  const ByteSeq& GetMessage() const;

protected:
  ByteSeq message;
};

/*!	\brief  Secure container IPMP data without encryption and with MAC.
*/
class MACNEncSecureContainerIPMPData: public NEncSecureContainerIPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
      \param  mess      input, message.
      \param  mc        input, MAC.
      \param  logger    input, message logger.
  */
  MACNEncSecureContainerIPMPData(const ByteT& ver, const Bit32T& id, const
    ByteSeq& mess, const ByteSeq& mc, DRMLogger& logger): NEncSecureContainerIPMPData(ver, id, mess),
    mac(mc), dataLogger(logger) {
  }

  virtual ~MACNEncSecureContainerIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Check and decrypt contained data.

      Possible errors are decryption error and MAC check error.

      \param  oper          input, symmetric operator.
      \param  plain         output, checked and decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CheckDecrypt(SymmetricOperator* oper, ByteSeq& plain);

  /*! \brief  Get MAC.

      \returns  MAC.
  */
  const ByteSeq& GetMAC() const;

private:
  ByteSeq mac;
  DRMLogger& dataLogger;
};

/*!	\brief  Secure container IPMP data without encryption and without MAC.
*/
class NMACNEncSecureContainerIPMPData: public NEncSecureContainerIPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
      \param  mess      input, message.
      \param  logger    input, message logger.
  */
  NMACNEncSecureContainerIPMPData(const ByteT& ver, const Bit32T& id, const
    ByteSeq& mess, DRMLogger& logger): NEncSecureContainerIPMPData(ver, id, mess), dataLogger(logger) {
  }

  virtual ~NMACNEncSecureContainerIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Check and decrypt contained data.

      Possible errors are decryption error and MAC check error.

      \param  oper          input, symmetric operator.
      \param  plain         output, checked and decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CheckDecrypt(SymmetricOperator* oper, ByteSeq& plain);

private:
  DRMLogger& dataLogger;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(SECURECONTAINERDATA_H)
