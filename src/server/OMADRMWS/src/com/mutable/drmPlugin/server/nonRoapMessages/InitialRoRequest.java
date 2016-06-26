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
 * The Initial Developer of the Original Code is Mutable, Inc.
 * Portions created by Mutable, Inc. are
 * Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved.
 * 
 *
 */
package com.mutable.drmPlugin.server.nonRoapMessages;

import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.roap.messages.ServerMessage;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.tools.UriVector;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;

/**
 * Device request to be triggered
 * for rights acquisition for specific contents
 * 
 * 
 *
 */

public class InitialRoRequest extends ServerMessage {

	protected RoapIdentifier deviceId;
	protected UriVector contents;
	

	/**
	 * constructor
	 */

	public InitialRoRequest(RoapIdentifier id, UriVector contents) {
		super();
		if (id==null || contents==null) throw new IllegalArgumentException();
		this.contents = contents;
		deviceId = id;
	}

	/**
	 * accessors
	 */

	public UriVector getContents() {
		return contents;
	}

	public RoapIdentifier getDeviceId() {
		return deviceId;
	}


	/** 
	 * implementing @see XmlDocument
	 * 
	 */
	public void setDomElement(IElement root) {
		deviceId.asDomChildOf(root,"deviceID");
		for (Iterator i=contents.iterator();i.hasNext();)
			root.addChildElement("contentID",i.next().toString());
	}
	
	public String documentName() { return "initialRoRequest"; }
	
	/** 
	 * instance creation from xml
	 * 
	 */

	public static InitialRoRequest instanceFromDomElement(IElement elem) {
		RoapIdentifier id = RoapIdentifier.instanceFromDomElement(elem.getChildElement("deviceID"));
		Vector v = new Vector();
		IElements contentElems = elem.getChildElements("contentID");
		for (Iterator i=contentElems.iterator();i.hasNext();)
			v.add(new UriValue(((IElement)i.next()).getStringValue()));
		return new InitialRoRequest(id, new UriVector(v));
		
	}

}
