/*

 * LICENSE AND COPYRIGHT INFORMATION:

 *

 * The contents of this file are subject to the Mozilla Public

 * License Version 1.1 (the "License"); you may not use this file

 * except in compliance with the License. You may obtain a copy of

 * the License at http://www.mozilla.org/MPL/

 *

 * Software distributed under the License is distributed on an "AS

 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or

 * implied. See the License for the specific language governing

 * rights and limitations under the License.

 *

 * The Original Code is OpenIPMP.

 *

 * The Initial Developer of the Original Code is Mutable, Inc.

 * Portions created by Mutable, Inc. are

 * Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved.

 * 

 *

 */



/**

 * @version 1.0

 */

package com.mutable.io.tools;



import java.io.*;



public class FileTool

{

	public static String sreadFile(String fileName)	throws Exception

	{

		byte[] ba = readFile(fileName);

		if (ba==null) return null;

		else return new String(ba);

	}

	public static byte[] readFile(String filename) throws Exception

	{

		FileInputStream fios = new FileInputStream(filename);

		int total = fios.available();

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

		fos.write(bytes);

		fos.flush();

		fos.close();

		return true;

	}

	public static boolean writeFile(String filename, String data) throws Exception

	{

		if(data==null) return false;

		else return writeFile(filename,data.getBytes());

	}

}