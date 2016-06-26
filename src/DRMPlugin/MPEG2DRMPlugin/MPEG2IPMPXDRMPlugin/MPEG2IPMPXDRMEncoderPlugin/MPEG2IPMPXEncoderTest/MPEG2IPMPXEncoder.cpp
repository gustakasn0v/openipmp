/**   \file MPEG2IPMPXEncoder.cpp

      \ingroup mpeg2drmencoder

      Test implementation of MPEG2 encoder with IPMPX signalling.

      The Initial Developer of the Original Code is Mutable, Inc. <br>
      Portions created by Mutable, Inc. are <br>
      Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

      
*/

#include "MPEG2IPMPXEncoder.h"

#include "BasicTypes.h"
#include "IIPMPControlInfoPart.h"

#include "IPMPControlInfoPart.h"
#include "IMPEG2IPMPXEncoder.h"

#include "MPEG2IPMPXDRMEncoder.h"
#include "IPMPDescriptor.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  MPEG2 transport stream encoder with IPMPX signalling.

    MPEG2 transport stream encoder is used by DRM encoder for adding DRM
    information to MPEG2 transport stream.
*/
/*! \brief  Create new intermediate part of the IPMP control information
            structure.

    The newly created intermediate part is the intermediate part in a row of
    parts constituting an IPMP control information structure. DRM encoder must
    take care of the correct indexing and calling of this and corresponding IPMP
    control information parts creating functions.

    \param  interPart     output, newly created intermediate part pointer
                          (if successful).

    \returns  Boolean indicating success or failure.
*/
bool MPEG2IPMPXTStreamEncoder::CreateInterIPMPControlInfoPart(
    IInterTStreamIPMPControlInfoPart** interPart) {
  inter.push_back(new InterTStreamIPMPControlInfoPart());
  *interPart = inter.back();
  return true;
}

/*! \brief  Create new last part of the IPMP control information structure.

    The newly created last part is the last part in a row of parts constituting
    an IPMP control information structure. DRM encoder must take care of the
    correct indexing and calling of this and corresponding IPMP control
    information parts creating functions.

    \param  lastPart    output, newly created last part pointer (if successful).

    \returns  Boolean indicating success or failure.
*/
bool MPEG2IPMPXTStreamEncoder::CreateLastIPMPControlInfoPart(
    ILastTStreamIPMPControlInfoPart** lastPart) {
  if (last != 0) delete last;
  last = new LastTStreamIPMPControlInfoPart();
  *lastPart = last;
  return true;
}

/*! \brief  Encode file.

    Encoding order is: intermediate control info parts, last control info part,
    IPMP descriptor.

    \param  in        input, name of the input file.
    \param  out       input, name of the output file.
    \param  xml       input-output, XML document containing necessary
                      information for protecting content.
    \param  method    input, encryption method.

    \returns  Boolean indicating success or failure.
*/
bool MPEG2IPMPXTStreamEncoder::Encode(std::string& in, const std::string& out,
    IXMLElement* xml, EncMethod method) {
  MPEG2IPMPXDRMEncoder drmEncoder(encLogger);
  IMPEG2IPMPXDRMEncryptor* encryptor = 0;

  //  Create MPEG2Encryptor that will protect the content.
  if (drmEncoder.CreateMPEG2IPMPXDRMEncryptor(in, xml, method, &encryptor) == false) {
    return false;
  }

  //  Create new IPMP descriptor for this stream which will contain
  //  DRM information.
  IPMPDescriptor* ipmpDesc = new IPMPDescriptor();

  //  Add DRM information to IPMP descriptor for this stream.
  if (encryptor->AddDRMInfo(ipmpDesc) == false) {
    return false;
  }

  //  Finally add DRM information for all streams (control class infos).
  if (drmEncoder.AddDRMInfo(this) == false) {
    return false;
  }

  //  Now write everything to output file.
  FILE* output = fopen(out.data(), "wb");
  if (output == NULL) {
    delete ipmpDesc;
    return false;
  }

  ByteSeq encoded;
  for (unsigned int i = 0; i < inter.size(); i++) {
    if (inter[i]->Encode(encoded) == false) {
      fclose(output);
      delete ipmpDesc;
      return false;
    }
    fwrite(encoded.GetFirst(), encoded.GetLength(), 1, output);
  }
  if (last->Encode(encoded) == false) {
    fclose(output);
    delete ipmpDesc;
    return false;
  }
  fwrite(encoded.GetFirst(), encoded.GetLength(), 1, output);

  if (ipmpDesc->Encode(encoded) == false) {
    fclose(output);
    delete ipmpDesc;
    return false;
  }
  fwrite(encoded.GetFirst(), encoded.GetLength(), 1, output);
  delete ipmpDesc;

  //  This should be done before adding DRM information, but it complicates
  //  test encoding, and provides no new test cases, thus we do it here.
  //  Read from input file and write to output file.
  FILE* input = fopen(in.data(), "rb");
  ByteT buffer[200*1024];
  unsigned int read = 0;
  while ((read = fread(buffer, 200*1024, 1, input)) > 0) {
    //  Create ByteSeq, pass it to encryptor for protection and write
    //  to output file.
    ByteSeq plain(buffer, read*(200*1024)), encrypted;
    if (encryptor->EncryptData(plain, encrypted) == false) {
      fclose(input);
      fclose(output);
      return false;
    }
    //  Write length of the encrypted data, for the decoder to be able to
    //  correctly read it later.
    UInt32T length = encrypted.GetLength();
    ByteT len[4];
    len[0] = (ByteT)((length >> 24) & 0xff);
    len[1] = (ByteT)((length >> 16) & 0xff);
    len[2] = (ByteT)((length >> 8) & 0xff);
    len[3] = (ByteT)(length & 0xff);
    fwrite(len, 4, 1, output);
    fwrite(encrypted.GetFirst(), encrypted.GetLength(), 1, output);
  }
  fclose(input);
  fclose(output);

  return true;
}

/*! \brief  MPEG2 program stream encoder with IPMPX signalling.

    MPEG2 program stream encoder is used by DRM encoder for adding DRM
    information to MPEG2 program stream.
*/
/*! \brief  Create new intermediate part of the IPMP control information
            structure.

    The newly created intermediate part is the intermediate part in a row of
    parts constituting an IPMP control information structure. DRM encoder must
    take care of the correct indexing and calling of this and corresponding IPMP
    control information parts creating functions.

    \param  interPart     output, newly created intermediate part pointer
                          (if successful).

    \returns  Boolean indicating success or failure.
*/
bool MPEG2IPMPXPStreamEncoder::CreateInterIPMPControlInfoPart(
    IInterPStreamIPMPControlInfoPart** interPart) {
  inter.push_back(new InterPStreamIPMPControlInfoPart());
  *interPart = inter.back();
  return true;
}

/*! \brief  Create new last part of the IPMP control information structure.

    The newly created last part is the last part in a row of parts constituting
    an IPMP control information structure. DRM encoder must take care of the
    correct indexing and calling of this and corresponding IPMP control
    information parts creating functions.

    \param  lastPart    output, newly created last part pointer (if successful).

    \returns  Boolean indicating success or failure.
*/
bool MPEG2IPMPXPStreamEncoder::CreateLastIPMPControlInfoPart(
    ILastPStreamIPMPControlInfoPart** lastPart) {
  if (last != 0) delete last;
  last = new LastPStreamIPMPControlInfoPart();
  *lastPart = last;
  return true;
}

/*! \brief  Encode file.

    Encoding order is: intermediate control info parts, last control info part,
    IPMP descriptor.

    \param  in        input, name of the input file.
    \param  out       input, name of the output file.
    \param  xml       input-output, XML document containing necessary
                      information for protecting content.
    \param  method    input, encryption method.

    \returns  Boolean indicating success or failure.
*/
bool MPEG2IPMPXPStreamEncoder::Encode(std::string& in, const std::string& out,
    IXMLElement* xml, EncMethod method) {
  MPEG2IPMPXDRMEncoder drmEncoder(encLogger);
  IMPEG2IPMPXDRMEncryptor* encryptor = 0;

  //  Create MPEG2Encryptor that will protect the content.
  if (drmEncoder.CreateMPEG2IPMPXDRMEncryptor(in, xml, method, &encryptor) == false) {
    return false;
  }

  //  Create new IPMP descriptor for this stream which will contain
  //  DRM information.
  IPMPDescriptor* ipmpDesc = new IPMPDescriptor();

  //  Add DRM information to IPMP descriptor for this stream.
  if (encryptor->AddDRMInfo(ipmpDesc) == false) {
    return false;
  }

  //  Finally add DRM information for all streams (control class infos).
  if (drmEncoder.AddDRMInfo(this) == false) {
    return false;
  }

  //  Now write everything to output file.
  FILE* output = fopen(out.data(), "wb");
  if (output == NULL) {
    delete ipmpDesc;
    return false;
  }

  ByteSeq encoded;
  for (unsigned int i = 0; i < inter.size(); i++) {
    if (inter[i]->Encode(encoded) == false) {
      fclose(output);
      delete ipmpDesc;
      return false;
    }
    fwrite(encoded.GetFirst(), encoded.GetLength(), 1, output);
  }
  if (last->Encode(encoded) == false) {
    fclose(output);
    delete ipmpDesc;
    return false;
  }
  fwrite(encoded.GetFirst(), encoded.GetLength(), 1, output);

  if (ipmpDesc->Encode(encoded) == false) {
    fclose(output);
    delete ipmpDesc;
    return false;
  }
  fwrite(encoded.GetFirst(), encoded.GetLength(), 1, output);
  delete ipmpDesc;

  //  This should be done before adding DRM information, but it complicates
  //  test encoding, and provides no new test cases, thus we do it here.
  //  Read from input file and write to output file.
  FILE* input = fopen(in.data(), "rb");
  ByteT buffer[200*1024];
  unsigned int read = 0;
  while ((read = fread(buffer, 200*1024, 1, input)) > 0) {
    //  Create ByteSeq, pass it to encryptor for protection and write
    //  to output file.
    ByteSeq plain(buffer, read*(200*1024)), encrypted;
    if (encryptor->EncryptData(plain, encrypted) == false) {
      fclose(input);
      fclose(output);
      return false;
    }
    //  Write length of the encrypted data, for the decoder to be able to
    //  correctly read it later.
    UInt32T length = encrypted.GetLength();
    ByteT len[4];
    len[0] = (ByteT)((length >> 24) & 0xff);
    len[1] = (ByteT)((length >> 16) & 0xff);
    len[2] = (ByteT)((length >> 8) & 0xff);
    len[3] = (ByteT)(length & 0xff);
    fwrite(len, 4, 1, output);
    fwrite(encrypted.GetFirst(), encrypted.GetLength(), 1, output);
  }
  fclose(input);
  fclose(output);

  return true;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
