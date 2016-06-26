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

import java.util.*;

abstract public class DataTypeCodexImpl implements DataTypeCodex
{
    public DataTypeCodexImpl()
    {
    }

    public String[] encode(Object[] objList)
    {
      if (objList == null)
          return null;

      String[] strList = new String[objList.length];
      for (int i = 0; i < objList.length; i++)
          strList[i] = encode(objList[i]);
      return strList;
    }

    public Object[] decode(String[] strList)
    {
      if (strList == null)
          return null;
      Object[] objList = makeList(strList.length);
      for (int i = 0; i < strList.length; i++)
          objList[i] = decode(strList[i]);
      return objList;
    }

    public Object[] makeList(int size)
    {
        return null;
    }

    public int getCount(Object obj)
    {
      return 1;
    }
}
