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
package com.mutable.drmPlugin.xml;

import java.io.*;

import javax.xml.parsers.DocumentBuilder;

import org.apache.xerces.jaxp.DocumentBuilderFactoryImpl;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class FactoryHelper implements IFactory {
	

	public boolean initialize() {
		return true;
	}

	public boolean terminate() {
		return true;
	}

	public  IDocument createDocument(String name) {
		Document doc;
		try {
			DocumentBuilderFactoryImpl theFactory = new DocumentBuilderFactoryImpl();
			DocumentBuilder builder = theFactory.newDocumentBuilder();
			doc = builder.newDocument();
			Element docElem = doc.createElement(name);
			doc.appendChild(docElem);
		} catch (Exception e) {
			return null;
		};
		return new DocumentHelper(doc);
	}
		
		
		
		
		
		
		
		

	public IDocument decodeDocument(String xml) {
		Document doc;
		try {
			DocumentBuilderFactoryImpl theFactory = new DocumentBuilderFactoryImpl();
			DocumentBuilder builder = theFactory.newDocumentBuilder();
			ByteArrayInputStream is = new ByteArrayInputStream(xml.getBytes());
//			StringBufferInputStream is = new StringBufferInputStream(xml);
			doc = builder.parse(is);
		} catch (Exception e) {
			return null;
		} ;
		return new DocumentHelper(doc);
}
	
	public IDocument fileInDocument(String path) {
		Document doc;
		try {
			DocumentBuilderFactoryImpl theFactory = new DocumentBuilderFactoryImpl();
			DocumentBuilder builder = theFactory.newDocumentBuilder();
			FileInputStream is = new FileInputStream(path);
			doc = builder.parse(is);
		} catch (Exception e) {
			return null;
		} ;
		return new DocumentHelper(doc);
}


	public FactoryHelper() {
		super();
		// TODO Auto-generated constructor stub
	}
	

}
