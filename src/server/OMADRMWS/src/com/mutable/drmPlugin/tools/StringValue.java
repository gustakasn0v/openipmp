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
package com.mutable.drmPlugin.tools;

import java.io.UnsupportedEncodingException;
import com.mutable.drmPlugin.xml.*;

/**
 * A wrapper around a String value.
 * Exposes all the nondestructive String examination methods,
 * delegating them to the protected String member.
 * 
 * 
 */


public  class StringValue implements java.io.Serializable, Comparable, CharSequence {


	protected String data;
	
	

	public  int compareTo(Object o) {
		if (StringValue.class.isInstance(o))
			return data.compareTo(((StringValue)o).getData());
		return -1;
	}
	
	
	public boolean equals(Object o) {
		if (StringValue.class.isInstance(o)) 
			return data.equals(((StringValue)o).getData());
		return false;
	}
	
	public int hashCode() {
		return data.hashCode();
	}
	


	public StringValue(String data) {
		super();
		if (data==null) throw new IllegalArgumentException();
		this.data = data;
	}
	


	public String getData() {
		return data;
	}
	
	public String toString() { return data.toString(); }

	public char charAt(int index) {
		return data.charAt(index);
	}

	public int compareTo(String anotherString) {
		return data.compareTo(anotherString);
	}
	

	public int compareToIgnoreCase(String str) {
		return data.compareToIgnoreCase(str);
	}

	public boolean endsWith(String suffix) {
		return data.endsWith(suffix);
	}

	public boolean equalsIgnoreCase(String anotherString) {
		return data.equalsIgnoreCase(anotherString);
	}

	public byte[] getBytes() {
		return data.getBytes();
	}

	public byte[] getBytes(String charsetName) throws UnsupportedEncodingException {
		return data.getBytes(charsetName);
	}

	public void getChars(int srcBegin, int srcEnd, char[] dst, int dstBegin) {
		data.getChars(srcBegin, srcEnd, dst, dstBegin);
	}

	public int indexOf(int ch, int fromIndex) {
		return data.indexOf(ch, fromIndex);
	}

	public int indexOf(int ch) {
		return data.indexOf(ch);
	}

	public int indexOf(String str, int fromIndex) {
		return data.indexOf(str, fromIndex);
	}

	public int indexOf(String str) {
		return data.indexOf(str);
	}

	public String intern() {
		return data.intern();
	}

	public int lastIndexOf(int ch, int fromIndex) {
		return data.lastIndexOf(ch, fromIndex);
	}

	public int lastIndexOf(int ch) {
		return data.lastIndexOf(ch);
	}

	public int lastIndexOf(String str, int fromIndex) {
		return data.lastIndexOf(str, fromIndex);
	}

	public int lastIndexOf(String str) {
		return data.lastIndexOf(str);
	}

	public int length() {
		return data.length();
	}

	public boolean matches(String regex) {
		return data.matches(regex);
	}

	public boolean regionMatches(boolean ignoreCase, int toffset, String other, int ooffset, int len) {
		return data.regionMatches(ignoreCase, toffset, other, ooffset, len);
	}

	public boolean regionMatches(int toffset, String other, int ooffset, int len) {
		return data.regionMatches(toffset, other, ooffset, len);
	}

	public boolean startsWith(String prefix, int toffset) {
		return data.startsWith(prefix, toffset);
	}

	public boolean startsWith(String prefix) {
		return data.startsWith(prefix);
	}

	public CharSequence subSequence(int beginIndex, int endIndex) {
		return data.subSequence(beginIndex, endIndex);
	}

	public String substring(int beginIndex, int endIndex) {
		return data.substring(beginIndex, endIndex);
	}

	public String substring(int beginIndex) {
		return data.substring(beginIndex);
	}

	public char[] toCharArray() {
		return data.toCharArray();
	}


	public IElement asDomChildOf(IElement father, String name) {
		IElement newElem = father.addChildElement(name,toString());
		return newElem;
		
	}

}
