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

import java.io.*;
import java.text.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;


import squashxml.xml.XMLMessageBean;
/**
 *	%JAVA_HOME%/bin/javac -classpath \jakarta-servletapi-4\lib\servlet.jar SimpleServletServer.java
 */

public class SquashXMLServletServer extends HttpServlet
{
	public SquashXMLServletServer()
	{
	}

	// NOTE:
	// Extend this class and overwrite this method.to process your application specific messages.
	// See ExampleServletServer in the root directory of the java source for an example.
	//
	public XMLMessageBean processRequestMessage(HttpServletRequest request, XMLMessageBean inMessage)
	{
		return null;
	}


	public void doGet(HttpServletRequest request, HttpServletResponse response)
		throws IOException, ServletException
	{
		doPost(request, response);
	}


	public void doPost(HttpServletRequest request, HttpServletResponse response)
		throws IOException, ServletException
	{
		System.out.println("doPost CALLED!\n");
		/** Prepare to output
		 *
		 */
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();

		/** Get the input request
		 *
		 */
		String inStr = null;
		if (request.getContentLength() <= 0 || (inStr = gatherInput(request)) == null)
		{
			String errStr = "HTTP/1.0 400 Bad Request - <Empty Input>\r\n\r\n";
			System.out.println(errStr);
			out.println(errStr);
			return;
		}
		System.out.println("Input Below:=============================");
		System.out.println(inStr);
		System.out.println("=========================================");

		/** Convert the input text into a request object
		 *
		 */
		XMLMessageBean inMessageBean = XMLMessageBean.decode(inStr.getBytes());
		if (inMessageBean == null)
		{
			String errStr = "HTTP/1.0 400 Bad Request - <HTTP POST payload is not a XMLMessageBean class.>\r\n\r\n";
			System.out.println(errStr);
			out.println(errStr);
			return;
		}

		/** Process the request into a Response.
		 *
		 */
		XMLMessageBean outMessageBean = processRequestMessage(request, inMessageBean);
		if (outMessageBean == null)
		{
			// TODO: Put this in an generic error XMLMessageBean instead of plain text
			String errStr = "HTTP/1.0 400 Bad Request - <Request did not produce an XMLMessageBean Response.>\r\n\r\n";
			System.out.println(errStr);
			out.println(errStr);
			return;
		}

		/** Convert the response object to output text
		 *
		 */
		String outStr = new String(outMessageBean.encode());
		System.out.println("Output Below:============================");
		System.out.println(outStr);
		System.out.println("=========================================");
		out.println(outStr);
	}


	/** Get the input (the body of the HTTP 'POST') as a big String
	 *
	 */
	private String gatherInput(HttpServletRequest request)
		throws IOException
	{
		ServletInputStream in = request.getInputStream();
		int inlen = request.getContentLength();
		byte inbytes[] = new byte[inlen];
		int rinlen = in.readLine(inbytes, 0, inlen);
		String result = "";
		if (rinlen > 0)
		{
			String partStr = new String(inbytes, 0, rinlen);
			result += partStr;
			while (rinlen < inlen)
			{
				inlen -= rinlen;
				rinlen = in.readLine(inbytes, 0, inlen);
				if (rinlen > 0)
				{
					partStr = new String(inbytes, 0, rinlen);
					result += partStr;
				}
			}
		}
		return result;
	}


	/** Session Management
	 *
	 */
	private final String mDefaultSessionObjectName = "UserObject";

	public boolean hasSession(HttpServletRequest request)
	{
		if (request == null)
			return false;

		HttpSession session = request.getSession();
		if (session == null || session.getAttribute(mDefaultSessionObjectName) == null)
			return false;

		return true;
	}

	public Object getSessionObject(HttpServletRequest request)
	{
		if (request == null)
			return null;

		HttpSession session = request.getSession();
		if (session == null)
			return null;

		return session.getAttribute(mDefaultSessionObjectName);
	}

	public boolean startSession(HttpServletRequest request, Object objectRef)
	{
		if (request == null || objectRef == null)
			return false;

		HttpSession session = request.getSession(true);
		if (session == null)
			return false;

		session.setAttribute(mDefaultSessionObjectName, objectRef);
		return true;
	}

	public void stopSession(HttpServletRequest request)
	{
		if (request == null)
			return;

		HttpSession session = request.getSession();
		if (session == null)
			return;

		session.invalidate();
	}

}

