/**	\file BasicTypes.h

  Basic types used for DRM.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (BASICTYPES_H)
#define BASICTYPES_H

/*! \brief  Default wait time for event waiting routines.

    This is the time spent in waiting for events that are externally dependent,
    such as waiting for communication response or similar. To prevent infinite
    waiting and possible external problem, we set timeouts to these values.
*/
#if defined _DEBUG
#define EVENT_WAIT_TIME   10000
#else
#define EVENT_WAIT_TIME   10000
#endif

/* disabled warning
	  'identifier' : identifier was truncated to 'number' characters in
	  the debug information
*/
#pragma warning(disable: 4786)

#include <cstring>
#include <algorithm>

#include <strstream>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

#if defined(WIN32)

//! 5-bit data.
typedef unsigned char     Bit5T;
//! 7-bit data.
typedef unsigned char     Bit7T;
//! Byte.
typedef unsigned char     ByteT;
//! 16-bit data.
typedef unsigned __int16  Bit16T;
//typedef unsigned __int32  Bit24T;
//! 32-bit data.
typedef unsigned __int32  Bit32T;
//! 16-bit number.
typedef unsigned __int16  UInt16T;
//! 32-bit number.
typedef unsigned __int32  UInt32T;
//! 64-bit number.
typedef unsigned __int64  UInt64T;

#elif defined(LINUX)

#include <sys/types.h>

//! 5-bit data.
typedef unsigned char     Bit5T;
//! 7-bit data.
typedef unsigned char     Bit7T;
//! Byte.
typedef unsigned char     ByteT;
//! 16-bit data.
typedef __uint16_t  Bit16T;
//typedef unsigned __int32  Bit24T;
//! 32-bit data.
typedef __uint32_t  Bit32T;
//! 16-bit number.
typedef __uint16_t  UInt16T;
//! 32-bit number.
typedef __uint32_t  UInt32T;
//! 64-bit number.
typedef __uint64_t  UInt64T;

#endif

/*! \brief  Exception used for basic types error.
*/
class BasicException {
};

/*! \brief  24-bit data.
*/
class Bit24T {
public:
  /*! \brief  Constructor.
  */
  Bit24T(): data() {
    memset(data, 0, 3);
  }

  /*! \brief  Constructor.

      \param  dta     data.
  */
  Bit24T(const UInt32T& dta): data() {
    data[0] = (dta & 0xff0000) >> 16;
    data[1] = (dta & 0xff00) >> 8;
    data[2] = (dta & 0xff);
  }

  /*! \brief  Constructor.

      \param  dta     data.
  */
  Bit24T(const ByteT dta[3]): data() {
    memcpy(data, dta, 3);
  }

  /*! \brief  Copy constructor.

      \param  rhs     24-bit data.
  */
  Bit24T(const Bit24T& rhs): data() {
    memcpy(data, rhs.data, 3);
  }

  /*! \brief  Get data.

      \returns Data.
  */
  const ByteT* GetData() const {
    return data;
  }

  /*! \brief  Comparation operator.

      \param  rhs     24-bit data.

      \returns  Whether two 24-bit datas are equal.
  */
  bool operator == (const Bit24T& rhs) const {
    return ((memcmp(data, rhs.data, 3) == 0)? (true): (false));
  }

  /*! \brief  Comparation operator.

      \param  rhs     24-bit data.

      \returns  Whether two 24-bit datas are equal.
  */
  bool operator != (const Bit24T& rhs) const {
    return (!((*this) == rhs));
  }

  /*! \brief  Cast operator.

      \returns  Unsigned integer.
  */
  operator UInt32T () const {
    return ((data[0] << 16) || (data[1] << 8) || data[2]);
  }

private:
  ByteT data[3];
};

/*! \brief  128-bit data.
*/
class Bit128T {
public:
  /*! \brief  Constructor.
  */
  Bit128T(): data() {
  }

  /*! \brief  Constructor.

      \param  dta     data.
  */
  Bit128T(const std::string& dta): data() {
    if (dta.size() == 16) {
      memcpy(data, dta.data(), 16);
    }
  }

  /*! \brief  Constructor.

      \param  dta     data.
  */
  Bit128T(const ByteT dta[16]): data() {
    memcpy(data, dta, 16);
  }

  /*! \brief  Copy constructor.

      \param  rhs     128-bit data.
  */
  Bit128T(const Bit128T& rhs): data() {
    memcpy(data, rhs.data, 16);
  }

  /*! \brief  Get data.

      \returns Data.
  */
  const ByteT* GetData() const {
    return data;
  }

  /*! \brief  Comparation operator.

      \param  rhs     128-bit data.

      \returns  Whether two 128-bit datas are equal.
  */
  bool operator == (const Bit128T& rhs) const {
    return ((memcmp(data, rhs.data, 16) == 0)? (true): (false));
  }

  /*! \brief  Comparation operator.

      \param  rhs     128-bit data.

      \returns  Whether two 128-bit datas are equal.
  */
  bool operator != (const Bit128T& rhs) const {
    return (!((*this) == rhs));
  }

  /*! \brief  Comparation operator.

      \param  rhs     string.

      \returns  Whether 128-bit data is equal to rhs. If size of rhs is != 16,
                it's false.
  */
  bool operator == (const std::string& rhs) const {
    if (rhs.size() != 16) {
      return false;
    }
    return ((memcmp(data, rhs.data(), 16) == 0)? (true): (false));
  }

  /*! \brief  Comparation operator.

      \param  rhs     128-bit data.

      \returns  Whether this 128-bit data is less than rhs.
  */
  bool operator < (const Bit128T& rhs) const {
    for (unsigned int i = 0; i < 16; i++) {
      if (data[i] < rhs.data[i]) {
        return true;
      }
    }
    return false;
  }

private:
  ByteT data[16];
};

/*! \brief  Exception used for ByteSeq error.
*/
class ByteSeqException {
};

/*! \brief  Bytes container.
*/
class ByteSeq {
public:
  /*! \brief  Constructor.
  */
  ByteSeq(): array() {
  }

  /*! \brief  Constructor.

      \param  data    byte.
  */
  ByteSeq(const ByteT& data): array(&data, 1) {
  }

  /*! \brief  Constructor.

      \param  data    bytes.
      \param  len     bytes length.
  */
  ByteSeq(const ByteT* data, const unsigned int len): array(data, len) {
  }

  /*! \brief  Constructor.

      \param  data    bytes.
  */
  ByteSeq(const std::basic_string<ByteT>& data): array(data) {
  }

  /*! \brief  Constructor.

      \param  data    bytes.
  */
  ByteSeq(const std::string& data): array((ByteT*)data.data(), data.size()) {
  }

  /*! \brief  Constructor.

      \param  data    16-bit data.
  */
  ByteSeq(const Bit16T& data): array(2, 0) {
    array[0] = (data & 0xff00) >> 8;
    array[1] = (data & 0xff);
  }

  /*! \brief  Constructor.

      \param  data    24-bit data.
  */
  ByteSeq(const Bit24T& data): array(3, 0) {
    memcpy((void*)array.data(), data.GetData(), 3);
  }

  /*! \brief  Constructor.

      \param  data    32-bit data.
  */
  ByteSeq(const Bit32T& data): array(4, 0) {
    array[0] = (data & 0xff000000) >> 24;
    array[1] = (data & 0xff0000) >> 16;
    array[2] = (data & 0xff00) >> 8;
    array[3] = (data & 0xff);
  }

  /*! \brief  Constructor.

      \param  data    128-bit data.
  */
  ByteSeq(const Bit128T& data): array(data.GetData(), 16) {
  }

  /*! \brief  Constructor.

      \param  data    16-bit number.
  */
/*
  ByteSeq(const UInt16T& data): array(2, 0) {
    array[0] = (data & 0xff00) >> 8;
    array[1] = (data & 0xff);
  }
*/
  /*  \brief  Constructor.

      \param  data    32-bit number.
  */
  /*
  ByteSeq(const UInt32T& data): array(4, 0) {
    array[0] = (data & 0xff000000) >> 24;
    array[1] = (data & 0xff0000) >> 16;
    array[2] = (data & 0xff00) >> 8;
    array[3] = (data & 0xff);
  }
  */

  /*! \brief  Constructor.

      \param  data    64-bit number.
  */
  ByteSeq(const UInt64T& data): array(8, 0) {
    UInt64T d = data;
	  for (int i = 7; i >= 0; i--) {
		  array[i] = (ByteT)(d & 0xff); d >>= 8;
	  }
  }

  /*! \brief  Copy constructor.

      \param  rhs     byte array.
  */
  ByteSeq(const ByteSeq& rhs): array(rhs.array) {
  }

  /*! \brief  Get array of first num bytes and remove them from array.

      \param  num         input, number of bytes requested.

      \warning  In case of an error, throws ByteSeqException.

      \returns  Requested byte array.
  */
  ByteSeq GetBytes(const UInt32T& num) {
    if (num > array.length()) {
      throw ByteSeqException();
    }
    std::basic_string<ByteT> ret(array.begin(), array.begin() + num);
    array = std::basic_string<ByteT>(array.begin() + num, array.end());
    return ByteSeq(ret);
  }

  /*! \brief  Get first byte and remove it from array.

      \warning  In case of an error, throws ByteSeqException.

      \returns  Requested byte.
  */
  ByteT GetByte() {
    if (array.length() == 0) {
      throw ByteSeqException();
    }
    ByteT byte = *(array.begin());
    array.erase(array.begin());
    return byte;
  }

  /*! \brief  Get 16-bit data and remove it from array.

      \warning  In case of an error, throws ByteSeqException.

      \returns  Requested 16-bit data.
  */
  Bit16T GetBit16() {
    if (array.length() < 2) {
      throw ByteSeqException();
    }
    Bit16T bit16 = (array[0] << 8) | (array[1]);
    array = std::basic_string<ByteT>(array.begin() + 2, array.end());
    return bit16;
  }

  /*! \brief  Get 24-bit data and remove it from array.

      \warning  In case of an error, throws ByteSeqException.

      \returns  Requested 24-bit data.
  */
  Bit24T GetBit24() {
    if (array.length() < 3) {
      throw ByteSeqException();
    }
//    Bit24T bit24 = (array[0] << 16) | (array[1] << 8) | (array[2]);
    Bit24T bit24(array.data());
    array = std::basic_string<ByteT>(array.begin() + 3, array.end());
    return bit24;
  }

  /*! \brief  Get 32-bit data and remove it from array.

      \warning  In case of an error, throws ByteSeqException.

      \returns  Requested 32-bit data.
  */
  Bit32T GetBit32() {
    if (array.length() < 4) {
      throw ByteSeqException();
    }
    Bit32T bit32 = (array[0] << 24) | (array[1] << 16) | (array[2] << 8) | (array[3]);
    array = std::basic_string<ByteT>(array.begin() + 4, array.end());
    return bit32;
  }

  /*! \brief  Get 128-bit data and remove it from array.

      \warning  In case of an error, throws ByteSeqException.

      \returns  Requested 128-bit data.
  */
  Bit128T GetBit128() {
    if (array.length() < 16) {
      throw ByteSeqException();
    }
    ByteT data[16];
    memcpy(data, array.data(), 16);
    array = std::basic_string<ByteT>(array.begin() + 16, array.end());
    return Bit128T(data);
  }

  /*! \brief  Get 16-bit number and remove it from array.

      \warning  In case of an error, throws ByteSeqException.

      \returns  Requested 16-bit number.
  */
  UInt16T GetUInt16() {
    if (array.length() < 2) {
      throw ByteSeqException();
    }
    UInt16T uint16 = (array[0] << 8) | (array[1]);
    array = std::basic_string<ByteT>(array.begin() + 2, array.end());
    return uint16;
  }

  /*! \brief  Get 32-bit number and remove it from array.

      \warning  In case of an error, throws ByteSeqException.

      \returns  Requested 32-bit number.
  */
  UInt32T GetUInt32() {
    if (array.length() < 4) {
      throw ByteSeqException();
    }
    UInt32T uint32 = (array[0] << 24) | (array[1] << 16) | (array[2] << 8) | (array[3]);
    array = std::basic_string<ByteT>(array.begin() + 4, array.end());
    return uint32;
  }

  /*! \brief  Get 64-bit number and remove it from array.

      \warning  In case of an error, throws ByteSeqException.

      \returns  Requested 64-bit number.
  */
  UInt64T GetUInt64() {
    if (array.length() < 8) {
      throw ByteSeqException();
    }
    UInt64T uint64 = 0;
	  for (unsigned int i = 0; i < 8; i++) {
		  uint64 <<= 8; uint64 |= array[i];
	  }
    array = std::basic_string<ByteT>(array.begin() + 8, array.end());
    return uint64;
  }

  /*! \brief  Get first byte pointer.

      \returns  First byte pointer.
  */
  const ByteT* GetFirst() const {
    return array.data();
  }

  /*! \brief  Get array length.

      \returns  Array length.
  */
  const UInt32T GetLength() const {
    return array.length();
  }

  /*! \brief  Concatenation operator.

      \param  rhs     byte array.

      \returns  Concatenation of byte arrays.
  */
  ByteSeq operator + (const ByteSeq& rhs) const {
    return ByteSeq(array + rhs.array);
  }

  /*! \brief  Concatenation and assignment operator.

      \param  rhs     byte array.
  */
  void operator += (const ByteSeq& rhs) {
    array += rhs.array;
  }

  /*! \brief  Concatenation and assignment operator.

      \param  rhs     byte.
  */
  void operator += (const ByteT& rhs) {
    array += std::basic_string<ByteT>(&rhs, 1);
  }

  /*! \brief  Assignment operator.

      \param  rhs     byte array.
  */
  void operator = (const ByteSeq& rhs) {
    array = rhs.array;
  }

  /*! \brief  Cast operator.
  */
  operator std::string () const {
    return std::string((char*)array.data(), array.size());
  }

  /*! \brief  Equality operator.

      \param  rhs     byte array.
  */
  bool operator == (const ByteSeq& rhs) const {
    if (array.length() != rhs.array.length()) {
      return false;
    }
    return (memcmp(array.data(), rhs.array.data(), array.length()) == 0);
  }

  /*! \brief  Equality operator.

      \param  rhs     string.
  */
  bool operator == (const std::string& rhs) const {
    if (array.length() != rhs.size()) {
      return false;
    }
    return (memcmp(array.data(), rhs.data(), array.length()) == 0);
  }

  /*! \brief  Encode array with leading size of instance.

      \returns Encoded array with leading size of instance.
  */
  ByteSeq MPEG2Encode() const {
    UInt64T sz = array.length();
    std::basic_string<ByteT> tmp(1, (ByteT)(sz & 0x7f));
	  sz >>= 7;
	  while (sz > 0) {
      tmp += std::basic_string<ByteT>(1, (ByteT)(0x80 | (sz & 0x7f)));
      sz >>= 7;
	  }
    std::reverse(tmp.begin(), tmp.end());
	  return ByteSeq(tmp + array);
  }

  /*! \brief  Get leading size of instance and remove it from array.

      \param  maxSize           input, maximal size of instance.

      \warning  In case of an error, throws ByteSeqException.

      \returns  Requested leading size of instance.
  */
  UInt64T GetSizeOfInstance(UInt64T maxSize) {
	  if (maxSize == 0) {
#if defined (WIN32)
		  maxSize = 0xffffffffffffffff;
#elif defined (LINUX)
		  maxSize = 0xffffffffffffffffLLU;
#else
		  maxSize = 0xffffffffffffffff;
#endif
	  }
	  UInt64T sizeOfInstance = 0;
	  ByteT more;
    ByteT tmp;
	  do {
      tmp = GetByte();
		  more = tmp & 0x80;
		  sizeOfInstance = (sizeOfInstance << 7) | (tmp & 0x7f);
		  if (sizeOfInstance > maxSize) {
        throw ByteSeqException();
		  }
	  } while (more != 0);
    return sizeOfInstance;
  }

private:
  std::basic_string<ByteT> array;
};

/*! \brief  Base64 encoded string.
*/
class Base64StringT {
public:
  /*! \brief  Constructor.
  */
  Base64StringT(): bString() {
  }

  /*! \brief  Constructor.

      \param  s         character array.

      If fails, throws BasicException.
  */
  Base64StringT(const char s[]): bString(s) {
    unsigned int i = 0;
    for (i = 0; i < bString.size(); i++) {
      char in = bString[i];
      if (!(((in >= 'A') && (in <= 'Z')) || ((in >= 'a') && (in <= 'z')) ||
          ((in >= '0') && (in <= '9')) || (in == '+') || (in == '/'))) {
        if ((in != '=') || (i < (bString.size() - 2))) {
          throw BasicException();
        } else {
          break;
        }
      }
    }
    if (++i < bString.size()) {
      if (bString[i] != '=') {
        throw BasicException();
      }
    }
  }

  /*! \brief  Constructor.

      \param  s         string.

      If fails, throws BasicException.
  */
  Base64StringT(const std::string& s): bString(s) {
    unsigned int i = 0;
    for (i = 0; i < bString.size(); i++) {
      char in = bString[i];
      if (!(((in >= 'A') && (in <= 'Z')) || ((in >= 'a') && (in <= 'z')) ||
          ((in >= '0') && (in <= '9')) || (in == '+') || (in == '/'))) {
        if ((in != '=') || (i < (bString.size() - 2))) {
          throw BasicException();
        } else {
          break;
        }
      }
    }
    if (++i < bString.size()) {
      if (bString[i] != '=') {
        throw BasicException();
      }
    }
  }

  /*! \brief  Copy constructor.

      \param  rhs       Base64 encoded string.
  */
  Base64StringT(const Base64StringT& rhs): bString(rhs.bString) {
  }

  /*! \brief  Assignment operator.

      \param  rhs       Base64 encoded string.

      \returns  Assigned string.
  */
  Base64StringT& operator = (const Base64StringT& rhs) {
    bString = rhs.bString;
    return (*this);
  }

  /*! \brief  Less than operator.

      \param  rhs       Base64 encoded string.

      \returns  Boolean indicating if this string is less than rhs.
  */
  bool operator < (const Base64StringT& rhs) const {
    return (bString < rhs.bString);
  }

  /*! \brief  Concatenation operator.

      \param  rhs       Base64 encoded string.
  */
  void operator += (const Base64StringT& rhs) {
    bString += rhs.BString();
  }

  /*! \brief  Concatenation operator.

      \param  rhs       Base64 encoded string.

      \returns  Concatenated string.
  */
  Base64StringT operator + (const Base64StringT& rhs) const {
    return Base64StringT(bString + rhs.BString());
  }

  /*! \brief  Equality operator.

      \param  rhs       Base64 encoded string.

      \returns  Boolean indicating if this string is equal to rhs.
  */
  bool operator == (const Base64StringT& rhs) const {
    return (bString == rhs.bString);
  }

  /*! \brief  Inequality operator.

      \param  rhs       Base64 encoded string.

      \returns  Boolean indicating if this string is not equal to rhs.
  */
  bool operator != (const Base64StringT& rhs) const {
    return (bString != rhs.bString);
  }

  /*! \brief  Get string representation.

      \returns  String representation.
  */
  const std::string& BString() const {
    return bString;
  }

  /*! \brief  Get length.

      \returns  Length.
  */
  UInt32T GetLength() const {
    return bString.size();
  }

private:
  std::string bString;
};

/*! \brief  Create string representation of an integer.

    \param  num         input, number.

    \returns  String representation of input number.
*/
static std::string IntToString(UInt32T num) {
  char str[65];
  std::strstream ret(str, sizeof(str)/sizeof(char));
  ret << (unsigned int)num << '\0';
  return ret.str();
/*
  char str[65];
  std::itoa(num, str, 10);
  return std::string(str);
*/
}

/*! \brief  Create integer from string representation.

    \param  str         input, string.

    \returns  Integer created from string representation.
*/
static int StringToInt(const std::string& str) {
  return atoi(str.data());
}

} // namespace DRMPlugin

#endif // !defined(BASICTYPES_H)
