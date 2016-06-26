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
 * <p>Title: </p>
 * <p>Description:  </p>
 * @version 1.0
 */

import java.io.*;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;


import javax.servlet.http.*;
import com.mutable.io.OlLogger;
import com.mutable.osms.server.app.osmsGlobalObjectManager;
import com.mutable.osms.server.bo.osmsUsers;

public class ServletUserKeyStore extends HttpServlet
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(m_logger!=null)m_logger.debug(className,method+" : "+message);}
	private void logWarning(String method,String message){if(m_logger!=null)m_logger.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(m_logger!=null)m_logger.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(m_logger!=null)m_logger.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(m_logger!=null)m_logger.info(className,method+"() : "+message);}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PROPERTIES
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	private OlLogger m_logger= osmsGlobalObjectManager.getInstance().getLogger();
	private osmsGlobalObjectManager gObjectManager = null;
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC MEMBERS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC METHODS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws IOException, ServletException
	{
		doPost(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse  response)
			throws java.io.IOException, ServletException
	{

		JspFactory _jspxFactory = null;
		PageContext pageContext = null;
		HttpSession session = null;
		ServletContext application = null;
		ServletConfig config = null;
		Object page = this;
		String  _value = null;
		try {

			_jspxFactory = JspFactory.getDefaultFactory();
			response.setContentType("text/html;ISO-8859-1");
			pageContext = _jspxFactory.getPageContext(this, request, response,"", true, 8192, true);

			application = pageContext.getServletContext();
			config = pageContext.getServletConfig();
			session = pageContext.getSession();
//            out = pageContext.getOut();

			osmsUsers user = null;
			boolean _jspx_specialuser  = false;
			synchronized (session)
			{
				user= (osmsUsers) pageContext.getAttribute("user",PageContext.SESSION_SCOPE);
				if ( user == null )
				{
					_jspx_specialuser = true;
					try
					{
						user = (osmsUsers) java.beans.Beans.instantiate(this.getClass().getClassLoader(), "com.mutable.osms.server.bo.osmsUsers");
					}
					catch (ClassNotFoundException exc)
					{
						throw new InstantiationException(exc.getMessage());
					}
					catch (Exception exc)
					{
						throw new ServletException (" Cannot create bean of class "+"com.mutable.osms.server.bo.osmsUsers", exc);
					}
					pageContext.setAttribute("user", user, PageContext.SESSION_SCOPE);
				}
			}
			if(_jspx_specialuser == true)
			{
			}
			response.setHeader("Content-disposition", "attachment; filename="+user.getUserName()+".p12");
			response.setContentType("application/octect-stream");
			response.setContentLength(user.getUserSecurityStore().length);
			response.getOutputStream().write(user.getUserSecurityStore());

		}
		catch (Throwable t)
		{
//            if (out != null && out.getBufferSize() != 0)
//                out.clearBuffer();
//            if (pageContext != null) pageContext.handlePageException(t);
		} finally
		{
			if (_jspxFactory != null) _jspxFactory.releasePageContext(pageContext);
		}
	}
}