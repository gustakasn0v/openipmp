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


 //
 // "YYYY-MM-DD HH:MM:SS"
 //

import java.util.Date;
import java.util.Calendar;

public class DataTypeDate extends DataTypeCodexImpl implements DataTypeCodex
{

    public DataTypeDate()
    {
    }

     public String getShortName()
     {
		return "date";
     }
     public String getClassName()
     {
		return "java.util.Date";
     }

     public String encode(Object data)
     {
          if (data == null)
              return "";

          Calendar cal = Calendar.getInstance();
          cal.setTime((Date)data);

          StringBuffer sb = new StringBuffer(32);

          int y = cal.get(Calendar.YEAR);
          sb.append(y);
          sb.append('-');

          int m = cal.get(Calendar.MONTH)+1;
          if (m < 10)
              sb.append('0');
          sb.append(m);
          sb.append('-');

          int d = cal.get(Calendar.DAY_OF_MONTH);
          if (d < 10)
              sb.append('0');
          sb.append(d);

          int h = cal.get(Calendar.HOUR_OF_DAY);
          int n = cal.get(Calendar.MINUTE);
          int s = cal.get(Calendar.SECOND);

          if (!(h == 0 && n == 0 && s == 0))
          {
              sb.append(' ');
              if (h < 10)
                  sb.append('0');
              sb.append(h);
              sb.append(':');

              if (n < 10)
                  sb.append('0');
              sb.append(n);
              sb.append(':');

              if (s < 10)
                  sb.append('0');
              sb.append(s);
          }

          return (String)new String(sb);
     }

     public Object decode(String str)
     {
          if (str == null || str.length() < 10)
            return (Date)null;
          try
          {
              Calendar cal = Calendar.getInstance();
              int y = new Integer(str.substring(0, 4)).intValue();
              int m = new Integer(str.substring(5, 7)).intValue() - 1;
              int d = new Integer(str.substring(8, 10)).intValue();

              if (str.length() >= 19)
              {
                  int h = new Integer(str.substring(11, 13)).intValue();
                  int n = new Integer(str.substring(14, 16)).intValue();
                  int s = new Integer(str.substring(17, 19)).intValue();

                  cal.set(y, m, d, h, n, s);
              }
              else
              {
                  cal.set(y, m, d);
              }
              return cal.getTime();
          }
          catch(Exception e)
          {
				  return (Date)null;
          }
     }
}

