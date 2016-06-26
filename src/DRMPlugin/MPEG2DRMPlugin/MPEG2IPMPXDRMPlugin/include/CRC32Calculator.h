/**	\file CRC32Calculator.h

	Calculator for 32-bit CRC codes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (CRC32CALCULATOR_H)
#define CRC32CALCULATOR_H

#include "BasicTypes.h"
#include <map>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Calculator for 32-bit CRC codes.

    Takes input bytes and calculates corrsponding CRC code.
*/
class CRC32Calculator {
public:
  /*! \brief  Create new CRCCalculator.

      Takes as input key (polynomial). If none given, default value is
      0x04c11db7 (MPEG2 polynomial).
  */
  CRC32Calculator(UInt32T k = 0x04c11db7): key(k), table(), reg(0) {
    // for all possible byte values
    for (UInt32T i = 0; i < 256; i++) {
      UInt32T reg = (i << 24);
      // for all bits in a byte
      for (unsigned int j = 0; j < 8; j++) {
        bool topBit = (reg & 0x80000000) != 0;
        reg <<= 1;
        if (topBit) {
          reg ^= key;
        }
      }
      table[(ByteT)i] = reg;
    }
  }
  /*! \brief  Update CRC calculation with new data.

      \param  data      input, data.
      \param  dataLen   input, size of the data.
  */
  void Update(const ByteT* data, unsigned int dataLen) {
    for (unsigned int i = 0; i < dataLen; i++) {
      UpdateByte(*data); data++;
    }
  }
  /*! \brief  Calculate CRC for data. If previously any data was given via
              Update() function, it will be the CRC of the previous data
              and the data given in this function.

      \param  data      input, data.
      \param  dataLen   input, size of the data.

      \returns  Number representing CRC.
  */
  UInt32T GetCRC(const ByteT* data, unsigned int dataLen) {
    for (unsigned int i = 0; i < dataLen; i++) {
      UpdateByte(*data); data++;
    }
    return reg;
  }

private:
  /*! \brief  Update CRC calculation with data byte.

      \param  byte      input, data byte.
  */
  void UpdateByte(const ByteT byte) {
    ByteT top = reg >> 24;
    top ^= byte;
    reg = (reg << 8) ^ table[top];
  }
  //! Key polynomial.
  UInt32T key;
  //! Precomputed table of remainder values for all possible input bytes.
  std::map<ByteT, UInt32T> table;
  //! Current value of remainder.
  UInt32T reg;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(CRC32CALCULATOR_H)
