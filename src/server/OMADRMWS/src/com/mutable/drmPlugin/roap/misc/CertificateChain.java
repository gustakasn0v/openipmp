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
package com.mutable.drmPlugin.roap.misc;

import java.util.*;

import com.mutable.drmPlugin.tools.*;
import com.mutable.drmPlugin.xml.*;

public class CertificateChain extends Base64StringVector {

	public CertificateChain(Vector data) {
		super(data);
	}
	

	public CertificateChain(){super();}





	public Vector certificateVector() { return getData(); }
	
	public IElement asDomChildOf(IElement father) {
		IElement newElem = father.addChildElement("certificateChain");
		for(int i=data.size()-1;i>=0;i--)
			newElem.addChildElement("certificate",data.elementAt(i).toString());
		
//		for (Iterator i=iterator();i.hasNext();)
//			newElem.addChildElement("certificate",i.next().toString());
		return newElem;
	}
	
	public static CertificateChain instanceFromDomElement(IElement elem) {
		if (elem==null) return null;
		IElements certs = elem.getChildElements("certificate");
		Vector v = new Vector();
//		for(Iterator i=certs.iterator(); i.hasNext();)
		for(int i=certs.getData().size()-1;i>=0;i--)		
			v.add(new Base64String(((IElement)certs.getData().elementAt(i)).getStringValue()));
		return new CertificateChain(v);
	}
}
