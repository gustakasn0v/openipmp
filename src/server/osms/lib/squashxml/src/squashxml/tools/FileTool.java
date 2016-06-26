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

package squashxml.tools;

import java.io.*;

public class FileTool
{
	public static byte[] readFile(String filename) throws Exception
	{
		FileInputStream fios = new FileInputStream(filename);
		if (fios == null)
			return null;
		int total = fios.available();
		if (total == 0)
			return null;
		byte[] bytes = new byte[total];

		int nRead = 0;
		while (nRead < total)
			nRead += fios.read(bytes, nRead, total-nRead);
		fios.close();
		return bytes;
	}

	public static boolean writeFile(String filename, byte[] bytes) throws Exception
	{
		FileOutputStream fos = new FileOutputStream(filename);
		if (fos == null)
			return false;
		if (bytes != null)
		{
			fos.write(bytes);
			fos.flush();
		}
		fos.close();
		return true;
	}
}