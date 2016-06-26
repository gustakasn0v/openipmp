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

package squashxml.xml;
import com.mutable.osms.common.io.message.*;
import java.sql.Timestamp;
import java.util.Date;
public class XMLMessageBean
{
	public XMLMessageBean(int messageType)
	{
		m_messageType = messageType;
	}


	private int m_messageType = 0;

	public Integer getMessageType()
	{
		return new Integer(m_messageType);
	}

	public void setMessageType(Integer messageType)
	{
		// This is only here for the 'ReflectionTool' to pick up the get/set pair
	}

	public static XMLMessageBean decode(byte[] ba)
	{
		XMLMessage xmlMessage = new XMLMessage();
		xmlMessage.setMessage(ba);
		Object bean = xmlMessage.getBean();
		return (XMLMessageBean) bean;
	}

	public byte[] encode()
	{
		XMLMessage xmlMessage = new XMLMessage(this);
		return xmlMessage.getMessage();
	}
	public static void main(String[] args)
	{

		String xml=
		"00000376<?xml version=\"1.0\"?>"
			+"<com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest>"
			+"<MessageType type=\"int\">207</MessageType>"
			+"<ContentId type=\"int\">3</ContentId>"
			+"<UserName type=\"char[]\">joen</UserName>"
			+"<StartDate type=\"Date\">2003-01-01</StartDate>"
			+"<EndDate type=\"Date\">2004-01-01</EndDate>"
			+"</com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest>";
/*
		xml=
		"<?xml version=\"1.0\"?>"
		+"<com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest>"
		+"<UserName type=\"char[]\">joen</UserName>"
		+"<ContentId type=\"int\">3</ContentId>"
		+"<LicenseType type=\"char[]\"></LicenseType>"
		+"<MessageType type=\"int\">201</MessageType>"
	 +"</com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest>";
//		System.out.println(xml);
		*/


		xml=
"00000440<?xml version=\"1.0\"?>"
+"<com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest>"
+"	 <MessageType type=\"int\">201</MessageType>"
+"	 <ContentId type=\"int\">3</ContentId>"
+"	 <UserName type=\"char[]\">joen</UserName>"
+"	 <StartDate type=\"date\">2003-05-21 22:38:52</StartDate>"
+"	 <EndDate type=\"date\"></EndDate>"
+"	 <LicenseType type=\"char[]\">ODRL</LicenseType>"
+"</com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest>";

		xml=
"00000376<?xml version=\"1.0\"?><com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest><MessageType type=\"int\">207</MessageType><ContentId type=\"int\">3</ContentId><UserName type=\"char[]\">joen</UserName><StartDate type=\"date\">2003-01-01</StartDate><EndDate type=\"date\">2004-01-01</EndDate></com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest>";
		osmsMessageRightsAuthorizationRequest req = new osmsMessageRightsAuthorizationRequest();
		req.setUserName("joen");
//		req.setContentId(new Integer(3));
		req.setLicenseType("ODRL");
		req.setStartDate(new Timestamp(new Date().getTime()));
//		System.out.println( new String(req.encode()));
		XMLMessageBean message = XMLMessageBean.decode(xml.getBytes());
		System.out.println( new String(message.encode()));
	}
}