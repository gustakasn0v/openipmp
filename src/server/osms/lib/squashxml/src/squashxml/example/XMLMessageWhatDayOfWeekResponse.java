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

package squashxml.example;

import java.util.Date;
import java.util.Calendar;

public class XMLMessageWhatDayOfWeekResponse extends XMLMessageExampleBase
{
	// Constructor
	public XMLMessageWhatDayOfWeekResponse()
	{
		super(XMLMessageExampleBase.WHAT_DAY_OF_WEEK_RESPONSE);
	}


	// Bean Atttributes
	private String dayOfWeekDateInQuestion = null;

	public String getDayOfWeekDateInQuestion()
	{
		return dayOfWeekDateInQuestion;
	}

	public void setDayOfWeekDateInQuestion(String dowdiq)
	{
		dayOfWeekDateInQuestion = dowdiq;
	}



	/*
	 *	Note: Not Required (i.e. sample specific).
	 */
	public static XMLMessageWhatDayOfWeekResponse process(XMLMessageWhatDayOfWeek whatDayOfWeekRequest)
	{
		if (whatDayOfWeekRequest == null)
			return null;
		Calendar cal = Calendar.getInstance();
		cal.setTime(whatDayOfWeekRequest.getDateInQuestion());
		int idow = cal.get(Calendar.DAY_OF_WEEK);
		String strDow = null;
		switch (idow)
		{
			case Calendar.SUNDAY:    strDow = "Sunday";      break;
			case Calendar.MONDAY:    strDow = "Monday";      break;
			case Calendar.TUESDAY:   strDow = "Tuesday";     break;
			case Calendar.WEDNESDAY: strDow = "Wednesday";   break;
			case Calendar.THURSDAY:  strDow = "Thursday";    break;
			case Calendar.FRIDAY:    strDow = "Friday";      break;
			case Calendar.SATURDAY:  strDow = "Saturday";    break;
			default:    break;
		}
		XMLMessageWhatDayOfWeekResponse whatDayOfWeekResponse = new XMLMessageWhatDayOfWeekResponse();
		whatDayOfWeekResponse.setDayOfWeekDateInQuestion(strDow);
		return whatDayOfWeekResponse;
	}
}
