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

import squashxml.xml.XMLMessageBean;

public class XMLMessageExampleBase extends XMLMessageBean
{
	// Application specific messages
	public final static int GENERIC_ERROR = 0;
	public final static int WHAT_DAY_OF_WEEK = 1;
	public final static int WHAT_DAY_OF_WEEK_RESPONSE = 2;

	public XMLMessageExampleBase(int messageType)
	{
		super(messageType);
	}
}
