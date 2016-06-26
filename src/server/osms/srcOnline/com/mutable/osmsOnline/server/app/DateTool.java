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

package com.mutable.osmsOnline.server.app;

import java.sql.Timestamp;
import java.util.Date;
import java.util.Calendar;

public class DateTool
{
	public static String currentStringDate()
	{
		return convertToString(new Date());
	}
	public static String convertToString(Timestamp t)
	{
		if(t==null)return "";
		return convertToString(new Date(t.getTime()));
	}
    public static String convertToString(Date t)
    {
		if(t==null) return "";
		Calendar cal = Calendar.getInstance();
		cal.setTime(t);
		String str;
		int year   = cal.get(Calendar.YEAR);
		int month  = cal.get(Calendar.MONTH)+1;
		int day    = cal.get(Calendar.DAY_OF_MONTH);
		int hour   = cal.get(Calendar.HOUR_OF_DAY);
		int minute = cal.get(Calendar.MINUTE);
		int sec    = cal.get(Calendar.SECOND);

		StringBuffer sb = new StringBuffer();

		int i;
		String seperator;

		i=month;seperator="-";
		if(i>=10)sb.append(i).append(seperator);else sb.append("0").append(i).append(seperator);

		i=day;seperator="-";
		if(i>=10)sb.append(i).append(seperator);else sb.append("0").append(i).append(seperator);

		//year
		sb.append(year);


		return sb.toString();
    }
	public static Timestamp convertToDate(String d) throws Exception
	{
		try
		{
			if(d==null) return null;
			if(d.length()!=10) return null;
			// mm-dd-yyyy
			Calendar cal = Calendar.getInstance();
			int year=(new Integer(d.substring(6,10))).intValue();
			int month=(new Integer(d.substring(0,2))).intValue();
			int day=(new Integer(d.substring(3,5))).intValue();
			String temp;

			cal.set(Calendar.YEAR,year);
			cal.set(Calendar.MONTH,month-1);
			cal.set(Calendar.DAY_OF_MONTH,day);


			cal.set(Calendar.HOUR_OF_DAY,0);
			cal.set(Calendar.SECOND,0);
			cal.set(Calendar.MINUTE,0);
			cal.set(Calendar.MILLISECOND,0);
			return new Timestamp(cal.getTime().getTime());
		}
		catch (Exception ex)
		{
			return null;
		}
	}
	public static void main(String[] args)
	{
		try
		{
//			Integer i ;

//			i= Integer.decode("5");

//			i= Integer.decode("a");
//			i= Integer.decode("-");
//			i= Integer.decode("");

			Timestamp d = DateTool.convertToDate("03-28-1971");
			System.out.println(""+d.toString());
			d = DateTool.convertToDate("b3-28-1971");
			System.out.println(""+d.toString());
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}

	}
}