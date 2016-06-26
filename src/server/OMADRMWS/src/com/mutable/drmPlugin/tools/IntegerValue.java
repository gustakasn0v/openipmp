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

import org.apache.axis.types.UnsignedInt;

/**
 * A wrapper around org.apache.axis.types.UnsignedInt, possibly an overkill. Ordinary
 * java integers might have done as well, but I don't feel like scrapping it now.
 * 
 * 
 *
 */
public abstract class IntegerValue implements  Comparable {
	
	protected UnsignedInt data;

	
	/**
	 * 
	 * the method contains a workaround around a weird bug in 
	 * org.apache.axis.types.UnsignedInt
	 */
	 
	 public int compareTo(IntegerValue anotherIV) {
		return (new Long(data.longValue())).compareTo(new Long(anotherIV.getData().longValue()));
	}

	public  int compareTo(Object o) {
		return data.compareTo(o);
	}
	
	
	public boolean equals(Object o) {
		if (!IntegerValue.class.isInstance(o)) return false;
		return data.equals(((IntegerValue)o).getData());
	}
	
	public int hashCode() {
		return data.hashCode();
	}



	public IntegerValue(UnsignedInt data) {
		super();
		if (data==null) throw new IllegalArgumentException();
		this.data = data;
	}

	public UnsignedInt getData() {
		return data;
	}
	
	public String toString() {
		return data.toString();
	}

}
