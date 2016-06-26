/* ***** BEGIN LICENSE BLOCK *****
 *	The contents of this file are subject to the Mozilla Public License
 *	Version 1.1 (the "License"); you may not use this file except in
 *	compliance with the License. You may obtain a copy of the License at
 *	http://www.mozilla.org/MPL/
 *
 *	Software distributed under the License is distributed on an "AS IS"
 *	basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 *	License for the specific language governing rights and limitations
 *	under the License.
 *
 *	The Original Code is SquashXML.
 *
 *	The Initial Developer of the Original Code is Ayman A. Gebrail.
 *	Portions created by Ayman A. Gebrail are
 *	Copyright (C) 2002 Ayman A. Gebrail. All Rights Reserved.
 *
 *  Contributor(s):
 *
 * ***** END LICENSE BLOCK ***** */

package squashxml.socket;

public class MessageContainer
{
	private final int HEADER_SIZE = 8;
	public int getFixedHeaderLength()
	{
		return HEADER_SIZE;
	}
	public byte[] getMessage()
	{
		if (!this.hasPayload())
			return null;
		byte[] header = encodePayloadLength();
		byte[] message = new byte[header.length + payload.length];
		int idx = 0;
		for (int j = 0; j < header.length; j++)
		  message[idx++] = header[j];
		for (int j = 0; j < payload.length; j++)
		  message[idx++] = payload[j];
		return message;
	}
	public void setMessage(byte[] blob)
	{
		if (blob.length < HEADER_SIZE)
		{
			return;
		}
		byte[] message = new byte[blob.length - HEADER_SIZE];
		for (int i = 0; i < blob.length - HEADER_SIZE; i++)
		{
			message[i] = blob[i + HEADER_SIZE];
		}
		setPayload(message);
		return;
	}

	private byte[] payload;
	public byte[] getPayload()
	{
		return payload;
	}
	public void setPayload(byte[] blob)  // Sets length in JAVA
	{
		if (blob == null)
		{
			length = 0;
			payload = null;
			return;
		}
		length = blob.length;
		payload = new byte[length];
		for (int i = 0; i < length; i++)
			payload[i] = blob[i];
	}
	public boolean hasPayload()
	{
	  if (payload == null)
		return false;
	  else
		return true;
	}
	// Length of PayLoad.
	// Don't write a setLength; leave it to JAVA to determine length of byte[] payload
	private int length;
	public int getLength()
	{
	  return length;
	}
	// Length is encoded as a string of length HEADER_SIZE with leading 0's
	// (e.g. HEADER_SIZE = 8, payload len of 2048 bytes, encode len = 00002048
	private byte[] encodePayloadLength()
	{
	  String lenStr = new Integer(length).toString();
	  if (lenStr.length() > HEADER_SIZE)
	  {
		System.out.println("ERROR olMessage.encodeLength(): Payload length of " + lenStr.length() + " too big for header of size " + HEADER_SIZE);
		return null;
	  }
	  StringBuffer sbuff = new StringBuffer(HEADER_SIZE);
	  for (int i = 0; i < HEADER_SIZE - lenStr.length(); i++)
		  sbuff.append("0");
	  sbuff.append(lenStr);
	  return (new String(sbuff)).getBytes();
	}
	public int decodePayloadLength(byte[] blob)
	{
	  if (blob.length != HEADER_SIZE)
	  {
		return -1;
	  }
	  String lenStr = new String(blob);
	  int lenStrlen = lenStr.length();
	  int idx = 0;
	  while (idx < lenStrlen && lenStr.charAt(idx) == '0')
		  idx++;
	  if (idx == lenStrlen)
		return -1;
	  length = (new Integer(lenStr.substring(idx))).intValue();
	  return length;
	}
}

