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

#ifndef _XMLMessageExampleBase_H
#define _XMLMessageExampleBase_H

#include "squashxml/xml/XMLDocument.h"
#include "squashxml/xml/XMLMessageBean.h"
#include "squashxml/tools/FileLogger.h"
#include "squashxml/tools/HashMap.h"
#include "squashxml/tools/ByteArray.h"

class XMLMessageExampleBase : public XMLMessageBean
{

public:
	/**
	 *	The message numbers for the example application
	 */
    enum Message_Number
    {
		GENERIC_ERROR 					= 0,
		WHAT_DAY_OF_WEEK 				= 1,
		WHAT_DAY_OF_WEEK_RESPONSE 		= 2
	};

	XMLMessageExampleBase(int messageType, const char* name);
	virtual ~XMLMessageExampleBase();

	// Derived Classes must implement these methods
	virtual char* encode() = 0;
	virtual bool decode(char* xmlText) = 0;
	virtual char* xmlTemplate() = 0;

	// This method should be implemented here
	virtual XMLMessageBean* getXMLMessageBean(int messageType);

};

#endif // _XMLMessageExampleBase_H
