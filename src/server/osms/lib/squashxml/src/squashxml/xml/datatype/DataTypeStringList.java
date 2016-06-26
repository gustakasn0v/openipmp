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

import java.util.Vector;

public class DataTypeStringList extends DataTypeCodexImpl implements DataTypeCodex
{
	private final String delimiter = ";";

	public DataTypeStringList()
	{
	}

	public String getShortName()
	{
		return "string[]";
	}

	public String getClassName()
	{
		return "[Ljava.lang.String;";
	}

	public String encode(Object data)
	{
		if (data == null)
			return null;

		String[] strList = (String[])data;
		String result = null;

		for (int i = 0; i < strList.length; i++)
			if (result == null)
				result = strList[i];
			else
				result += " " + delimiter + " " + strList[i];
		return result;
	}

	public Object decode(String str)
	{
		if (str == null || str.equals("") )
			return null;

		int pos = 0;
		int newpos = 0;
		Vector vStr = new Vector();
		do
		{
			newpos = str.indexOf(delimiter, pos);
			if (newpos == pos)
				vStr.add(null);
			else if (newpos > 0)
				vStr.add(str.substring(pos, newpos).trim());
			if (newpos >= 0)
				pos = newpos + 1;
		}while (newpos >= 0);

		if (pos != str.length())
			vStr.add(str.substring(pos, str.length()).trim());
		else
			vStr.add(null);


		int len = vStr.size();
		if (len == 0)
			return null;

		String strList[] = new String[len];
		for (pos = 0; pos < len; pos++)
			strList[pos] = (String)vStr.get(pos);

		return strList;
	}

}

