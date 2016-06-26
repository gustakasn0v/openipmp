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
package com.mutable.drmPlugin.roap.imports.xenc;

import com.mutable.drmPlugin.roap.imports.ds.KeyInfo;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.UriValue;

public class Encrypted  {
	
	protected EncryptionMethod encryptionMetod;
	protected KeyInfo keyInfo;
	protected CipherData cipherData;
	protected EncryptionProperties encryptionProperties;
	protected IdValue id;
	protected UriValue type;
	protected Base64String mimeType;
	protected UriValue encoding;
	



	/**
	 * @param data is a mandatory element, while 
	 * @param method , @param info and @param properties
	 * are optional elements, and 
	 * @param id , @param type , @param mime and @param encoding
	 * are optional attributes
	 */
	public Encrypted(EncryptionMethod method, KeyInfo info, 
			CipherData data, 
			EncryptionProperties props, IdValue id, 
			UriValue type, Base64String mime, UriValue encoding) {
		super();
		if ( data==null ) throw new IllegalArgumentException();
		cipherData = data;
		this.encoding = encoding;
		encryptionProperties = (props==null 
								? null
								: (EncryptionProperties) props.nonEmptyOrNull());
		this.id = id;
		keyInfo = info;
		this.type = type;
		mimeType = mime;
	}

	public CipherData getCipherData() {
		return cipherData;
	}

	public UriValue getEncoding() {
		return encoding;
	}

	public EncryptionProperties getEncryptionProperties() {
		return encryptionProperties;
	}

	public IdValue getId() {
		return id;
	}

	public KeyInfo getKeyInfo() {
		return keyInfo;
	}

	public UriValue getType() {
		return type;
	}

	public EncryptionMethod getEncryptionMetod() {
		return encryptionMetod;
	}

	public Base64String getMimeType() {
		return mimeType;
	}



}
