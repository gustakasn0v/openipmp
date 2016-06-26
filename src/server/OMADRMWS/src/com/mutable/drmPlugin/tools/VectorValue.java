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

import java.util.Iterator;
import java.util.Vector;

/**
 * A wrapper around a homogenous java.util.Vector. Each concrete subclass must
 * implement the protected method elementClass. Instances of concrete subclasses
 * are guaranteed to be homogenous.  It exposes java.util.Vector.iterator(),
 * java.utilVector.contains and java.util.Vector.isEmpty, whereas the other
 * java.util.Vector methods can be accessed via getData(), providing the underlying 
 * java.util.Vector.
 * With generics this would not be needed.
 * 
 * 
 *
 */
public abstract class VectorValue {
	
	protected Vector data;
	
	protected abstract Class elementClass();
	
	/**
	 * exposing the underlying java.util.Vector.iterator()
	 */
	public Iterator iterator() {
		return data.iterator();
	}
	
	protected boolean validate(Vector v) {
		if (v==null) return false;
		for(Iterator i=v.iterator();i.hasNext();)
			if (!(elementClass().isInstance(i.next())))
				return false;
		return true;
	}


	/**
	 * constructor checks whether the argument is non-null homogenous, and throws
	 * IllegalArguemntException if not
	 * 
	 */
	public VectorValue(Vector data) throws IllegalArgumentException {
		super();
		if (!validate(data)) throw new IllegalArgumentException();
		this.data = data;
	}
	
	/**
	 *  VectorValue with empty data
	 *
	 */
	public VectorValue() {
		this(new Vector());
	}
	
/**
 * exposing the underlying java.util.Vector
 */
	public Vector getData() {
		return data;
	}
	
	/**
	 * exposing java.utilVector.isEmpty
	 */
	public boolean isEmpty() { return data.isEmpty(); }
	
	/**
	 * 
	 * @return null if data is empty, this otherwise
	 */
	
	public VectorValue nonEmptyOrNull(){ 
		return data.isEmpty() ? null : this;
	}
	
	/**
	 * exposing java.util.Vector.contains
	 */
	public boolean contains(Object o) {
		for (int i=0; i<getData().size();i++)
			if (getData().elementAt(i).equals(o)) return true;
		return false;
	}
	
	

	



}
