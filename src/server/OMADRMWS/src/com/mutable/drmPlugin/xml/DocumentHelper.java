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

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.StringWriter;

import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

public class DocumentHelper implements IDocument {
	
	protected org.w3c.dom.Document domDocument;

	public DocumentHelper(org.w3c.dom.Document document) {
		domDocument = document;
	}
	
	public String output(boolean pretty) {
		StringWriter sw;
		try {
			Transformer tr = TransformerFactory.newInstance().newTransformer();
			if (pretty) {
//				tr.setOutputProperty(OutputKeys.STANDALONE,"true");
				tr.setOutputProperty(OutputKeys.INDENT, "yes");
				tr.setOutputProperty(OutputKeys.METHOD,"xml");
				tr.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "3");
			} else {
				tr.setOutputProperty(OutputKeys.INDENT, "false");
				tr.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "yes");
			};
			sw = new StringWriter();
			tr.transform( new DOMSource(domDocument),new StreamResult(sw));
			return sw.toString();
		} catch (Exception e) {
			e.printStackTrace(); return null;
		}
	}
	
	public String encode() {
		return output(false);
	}


	public void fileOut(String path) throws IOException {
		FileOutputStream os = new FileOutputStream(path);
		String s = output(true);
		os.write(s.getBytes());
		os.close();
	}

	public IElement getRootElement() {
		return new ElementHelper(domDocument.getDocumentElement());
	}

}
