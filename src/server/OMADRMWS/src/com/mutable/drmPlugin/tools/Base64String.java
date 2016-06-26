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
/**
 * 
 */
package com.mutable.drmPlugin.tools;

import java.io.IOException;

import sun.misc.BASE64Decoder;
import sun.misc.BASE64Encoder;

/**
 * Represents a base64 String encoding of a byte array. Instances are guaranteed
 * to be correct base64 encodings.
 * 
 * 
 */


public class Base64String extends StringValue {

	private static final long serialVersionUID = 1260900946031976733L;
	

	
	
	

	
	private boolean validate(String s) {
		try {
			Base64Coder.encode(Base64Coder.decode(s));
			
		} catch(Exception ex) { return false; };
		
		return true; 
	}

	/**
	 * The constructor validates whether the argument is a valid base64 String
	 * and throws an IllegalArgumentException if it is not. It DOES NOT encode the input.
	 */
	public Base64String(String string)throws IllegalArgumentException {
		super(string);
		if (!validate(string)) throw new IllegalArgumentException("bad string for base64");
	}
	
	/**
	 *  This constructor DOES encode the input byte array.
	 */
	public Base64String(byte[] b) {
		super(new String(Base64Coder.encode(b)));
	}
	
	/**
	 * Decoding conversion.
	 * @return encoded bytes
	 */
	public byte[] asByteArray() {
		byte[] res = null;
		try {
			res = Base64Coder.decode(data.toCharArray());
		} catch (RuntimeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		};
		return res;
	}
	
	public boolean equals(Object o) {
		if (!Base64String.class.isInstance(o)) return false;
		return toString().equals(((Base64String)o).toString());
	}
	

}
