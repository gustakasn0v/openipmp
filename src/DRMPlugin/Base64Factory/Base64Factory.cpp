/**	\file Base64Factory.cpp

	Base64 encoding and decoding tool using openSSL library.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include <string>
#include "BasicTypes.h"
#include "Base64Factory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

static inline bool isb64(char in) {
  return (((in >= 'A') && (in <= 'Z')) || ((in >= 'a') && (in <= 'z')) ||
    ((in >= '0') && (in <= '9')) || (in == '+') || (in == '/'));
}

static char bytetochar[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*
static inline char bytetochar(ByteT in) {
  if ((in >= 0) && (in < 26)) return (in + 'A');
  if ((in >= 26) && (in < 52)) return (in - 26 + 'a');
  if ((in >= 52) && (in < 62)) return (in - 52 + '0');
  if (in == 62) return '+';
  if (in == 63) return '/';
  return '=';
}
*/

static inline bool chartobyte(char in, ByteT& out) {
  if (!isb64(in)) return false;
  if ((in >= 'A') && (in <= 'Z')) (out = (in - 'A'));
  if ((in >= 'a') && (in <= 'z')) (out = (in + 26 - 'a'));
  if ((in >= '0') && (in <= '9')) (out = (in + 52 - '0'));
  if (in == '+') (out = 62);
  if (in == '/') (out = 63);
  return true;
}

static inline void convert1to4(ByteT* in, char* out) {
//*
  out[0] = bytetochar[in[0] >> 2];
  out[1] = bytetochar[((in[0] & 0x3) << 4) & 0x3f];
/*/
  out[0] = bytetochar(in[0] >> 2);
  out[1] = bytetochar(((in[0] & 0x3) << 4) & 0x3f);
//*/
  out[2] = '=';
  out[3] = '=';
}

static inline void convert2to4(ByteT* in, char* out) {
//*
  out[0] = bytetochar[in[0] >> 2];
  out[1] = bytetochar[((in[0] & 0x3) << 4) | ((in[1] & 0xf0) >> 4) & 0x3f];
  out[2] = bytetochar[((in[1] & 0xf) << 2) & 0x3f];
/*/
  out[0] = bytetochar(in[0] >> 2);
  out[1] = bytetochar(((in[0] & 0x3) << 4) | ((in[1] & 0xf0) >> 4) & 0x3f);
  out[2] = bytetochar(((in[1] & 0xf) << 2) & 0x3f);
//*/
  out[3] = '=';
}

static inline void convert3to4(ByteT* in, char* out) {
//*
  out[0] = bytetochar[(in[0]) >> 2];
  out[1] = bytetochar[((in[0] & 0x3) << 4) | ((in[1] & 0xf0) >> 4) & 0x3f];
  out[2] = bytetochar[((in[1] & 0xf) << 2) | ((in[2] & 0xc0) >> 6) & 0x3f];
  out[3] = bytetochar[in[2] & 0x3f];
/*/
  out[0] = bytetochar((in[0]) >> 2);
  out[1] = bytetochar(((in[0] & 0x3) << 4) | ((in[1] & 0xf0) >> 4) & 0x3f);
  out[2] = bytetochar(((in[1] & 0xf) << 2) | ((in[2] & 0xc0) >> 6) & 0x3f);
  out[3] = bytetochar(in[2] & 0x3f);
//*/
}

static inline bool convert4to1(char* in, ByteT* out) {
  ByteT oout[2];
  if (chartobyte(in[0], oout[0]) == false) return false;
  if (chartobyte(in[1], oout[1]) == false) return false;
  if ((oout[1] & 0xf) != 0) return false;
  out[0] = ((oout[0] << 2) | ((oout[1] & 0x30) >> 4));
  return true;
}

static inline bool convert4to2(char* in, ByteT* out) {
  ByteT oout[3];
  if (chartobyte(in[0], oout[0]) == false) return false;
  if (chartobyte(in[1], oout[1]) == false) return false;
  if (chartobyte(in[2], oout[2]) == false) return false;
  if ((oout[2] & 0x3) != 0) return false;
  out[0] = ((oout[0] << 2) | ((oout[1] & 0x30) >> 4));
  out[1] = (((oout[1] & 0xf) << 4) | (oout[2] & 0x3c) >> 2);
  return true;
}

static inline bool convert4to3(char* in, ByteT* out) {
  if (in[3] == '=') {
    if (in[2] == '=') return convert4to1(in, out);
    return convert4to2(in, out);
  }
  ByteT oout[4];
  if (chartobyte(in[0], oout[0]) == false) return false;
  if (chartobyte(in[1], oout[1]) == false) return false;
  if (chartobyte(in[2], oout[2]) == false) return false;
  if (chartobyte(in[3], oout[3]) == false) return false;
  out[0] = ((oout[0] << 2) | ((oout[1] & 0x30) >> 4));
  out[1] = (((oout[1] & 0xf) << 4) | (oout[2] & 0x3c) >> 2);
  out[2] = (((oout[2] & 0x3) << 6) | oout[3]);
  return true;
}

/*! \brief  Helper routine for base64 encoding.

    \param  data        input, byte data.
    \param  b64         output, base64 encoded data.

    \returns  Boolean indicating success or failure.
*/
bool Base64Factory::Encode(const ByteSeq& data, Base64StringT& b64) {
  char *b = (char*)malloc(((data.GetLength()+2)/3)*4+1);
  char* bb = b;
  ByteT* dd = (ByteT*)data.GetFirst();
  unsigned int llen = (unsigned int)data.GetLength();
  while (llen >= 3) {
    convert3to4(dd, bb);
    dd += 3;
    bb += 4;
    llen -= 3;
  }
  if (llen == 1) {
    convert1to4(dd, bb);
    bb += 4;
  } else if (llen == 2) {
    convert2to4(dd, bb);
    bb += 4;
  }
  *bb = '\0';
  b64 = Base64StringT(std::string((const char*)b));
  free(b);
  return true;
}

/*! \brief  Helper routine for base64 decoding.

    \param  b64         input, base64 encoded data.
    \param  data        output, byte data.

    \returns  Boolean indicating success or failure.
*/
bool Base64Factory::Decode(const Base64StringT& b64, ByteSeq& data) {
  char* b = (char*)(b64.BString().data());
  unsigned int llen = b64.GetLength();
  unsigned int i = llen;
  while ((i >= 1) && (b[i-1] == '=') && ((llen-i) < 3)) {
    i--;
  }
  if ((llen-i) == 3) {
    return false;
  }
  unsigned int dbinsize = (i/4)*3;
  if (i != llen) {
    dbinsize += (((llen-i) == 1)? (2): (1));
  }
  ByteT* dta = (unsigned char*)malloc(((llen+3)/4)*3);
  if (dta == NULL) {
    return false;
  }
  char* bb = b;
  ByteT* dd = dta;
  while (llen > 0) {
    if (convert4to3(bb, dd) == false) {
      free(dta);
      return false;
    }
    bb += 4;
    dd += 3;
    llen -= 4;
  }
  data = ByteSeq(dta, dbinsize);
  free(dta);
  return true;
}
  
} // namespace DRMPlugin
