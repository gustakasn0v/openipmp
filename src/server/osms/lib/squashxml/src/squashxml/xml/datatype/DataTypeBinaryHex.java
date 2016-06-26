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

package squashxml.xml.datatype;


public class DataTypeBinaryHex extends DataTypeCodexImpl implements DataTypeCodex
{

	public DataTypeBinaryHex()
	{
	}

	 public String getShortName()
	 {
		return "binaryHex";
	 }
	 public String getClassName()
	 {
		return "[B";	// use JAVA byte[]
	 }

	 public String encode(Object data)
	 {
		byte[] blob = (byte[])data;
		if (blob == null || blob.length == 0)
		  return null;

		StringBuffer sb = new StringBuffer((2*blob.length)+1);  // each byte in 2 byte hex.
				for (int i = 0; i < blob.length; i++)
				{
					int bi = (int)blob[i];
					if (bi < 0)
						bi += 256;
					int hr = bi % 16;
					char cr;
					if (hr < 10)
					  cr = (char)((int)'0' + hr);
					else
					  cr = (char)((int)'A' + (hr - 10));
					int hl = (bi - hr) / 16;
					char cl;
					if (hl < 10)
					  cl = (char)((int)'0' + hl);
					else
					  cl = (char)((int)'A' + (hl - 10));
					sb.append(cl);
					sb.append(cr);
				}


		return (String)new String(sb);
	 }

	 public Object decode(String str)
	 {
		int length;
		if (str == null || (length = str.length()) == 0)
		  return null;

		byte[] blob = new byte[length/2];
				for (int i = 0; i < length - 1; i += 2)
				{
				  char cl = str.charAt(i);
				  char cr = str.charAt(i+1);

				  int hl;
				  if (cl < 'A')
					hl = (int)cl - (int)'0';
				  else
					hl = ((int)cl - (int)'A') + 10;

				  int hr;
				  if (cr < 'A')
					hr = (int)cr - (int)'0';
				  else
					hr = ((int)cr - (int)'A') + 10;

				  blob[i/2] = (byte)((hl * 16) + hr);
				}
		return (Object)blob;
	 }
}
