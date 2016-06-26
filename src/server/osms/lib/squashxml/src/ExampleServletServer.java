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

import java.io.*;
import java.text.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

import squashxml.xml.*;
import squashxml.socket.*;
import squashxml.example.*;


/**
 *	%JAVA_HOME%/bin/javac -classpath \jakarta-servletapi-4\lib\servlet.jar SimpleServletServer.java
 */

public class ExampleServletServer extends SquashXMLServletServer
{
	public ExampleServletServer()
	{
	}

	//
	// (example) Application specific messages.
	//
	public XMLMessageBean processRequestMessage(HttpServletRequest request, XMLMessageBean inMessage)
	{
		// This should be a object such as sessionHistoryObject
		int sessionId = 0;
		if (!hasSession(request))
		{
			Integer newId = ExampleServletServer.getNextSessionID();
			startSession(request, newId);

			sessionId = newId.intValue();
		}
		else
		{
			sessionId = ((Integer)getSessionObject(request)).intValue();
		}


		if (inMessage == null)
		{
			XMLMessageGenericError genericError = new XMLMessageGenericError();
			genericError.setErrorString("Empty Request");
			return (XMLMessageBean)genericError;
		}

		XMLMessageBean response = null;
		switch (inMessage.getMessageType().intValue())
		{
			case XMLMessageExampleBase.WHAT_DAY_OF_WEEK:
			{
				XMLMessageWhatDayOfWeekResponse whatDayOfWeekResponse = XMLMessageWhatDayOfWeekResponse.process((XMLMessageWhatDayOfWeek)inMessage);
				response = whatDayOfWeekResponse;
				break;
			}
			default:
			{
				XMLMessageGenericError genericError = new XMLMessageGenericError();
				genericError.setErrorString("Unknown Request");
				response = genericError;
				break;
			}
		}
		return response;
	}

	public static int nextSessionId = 1000;
	public static Integer getNextSessionID()
	{
		nextSessionId++;
		nextSessionId %= 10000000;  // Avoid overflow, recycle every 10 million

		return new Integer(nextSessionId);
	}
}

