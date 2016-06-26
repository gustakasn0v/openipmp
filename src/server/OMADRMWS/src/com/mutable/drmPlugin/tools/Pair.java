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

/**
 * My astonishment at the fact that this class does not exist in java, 
 * and that everybody
 * has to reimplement it for himself, refuses to fade away.
 * 
 * 
 *
 */
public class Pair {
	protected Object fst;
	protected Object snd;
	
	public boolean equals(Object x) {
		if (Pair.class.isInstance(x))
			return (fst.equals(((Pair) x).getFst()) && snd.equals(((Pair) x).getSnd()));
		return false;
	}

	public int hashCode() {
		return fst.hashCode()+snd.hashCode();
	}

	public Object getFst() {
		return fst;
	}

	public Object getSnd() {
		return snd;
	}

	public Pair(Object fst, Object snd) {
		this.fst = fst;
		this.snd = snd;
	}

}
