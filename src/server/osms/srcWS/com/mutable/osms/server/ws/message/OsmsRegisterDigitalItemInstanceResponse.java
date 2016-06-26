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

package com.mutable.osms.server.ws.message;

public class OsmsRegisterDigitalItemInstanceResponse implements java.io.Serializable {
	private String metadataType=null;
	private String metadataXml=null;
	private String signatureXml=null;
	private String auxDataXml=null;
	
	public OsmsRegisterDigitalItemInstanceResponse(String xml, String type, String xml2, String xml3) {
		auxDataXml = xml;
		metadataType = type;
		metadataXml = xml2;
		signatureXml = xml3;
	}

	public OsmsRegisterDigitalItemInstanceResponse() {
	}

	public String getAuxDataXml() {
		return auxDataXml;
	}

	public void setAuxDataXml(String auxDataXml) {
		this.auxDataXml = auxDataXml;
	}

	public String getMetadataType() {
		return metadataType;
	}

	public void setMetadataType(String metadataType) {
		this.metadataType = metadataType;
	}

	public String getMetadataXml() {
		return metadataXml;
	}

	public void setMetadataXml(String metadataXml) {
		this.metadataXml = metadataXml;
	}

	public String getSignatureXml() {
		return signatureXml;
	}

	public void setSignatureXml(String signatureXml) {
		this.signatureXml = signatureXml;
	}
}
