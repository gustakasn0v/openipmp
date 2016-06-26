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
package com.mutable.drmPlugin.roap.imports.ds;

import org.apache.axis.types.UnsignedInt;

import com.mutable.drmPlugin.tools.Base64String;

public class X509IssuerSerial implements BasicX509Data {
	
	private Base64String issuerName;
	private UnsignedInt serialNumber;



	/**
	 * 
	 * @param name and @param number are mandatory elements
	 */
	
	public X509IssuerSerial(Base64String name, UnsignedInt number) {
		super();
		if (name==null || number==null) throw new IllegalArgumentException();
		issuerName = name;
		serialNumber = number;
	}

	public Base64String getIssuerName() {
		return issuerName;
	}

	public UnsignedInt getSerialNumber() {
		return serialNumber;
	}

}
