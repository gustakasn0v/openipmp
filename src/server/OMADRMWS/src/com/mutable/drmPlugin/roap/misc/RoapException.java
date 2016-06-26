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
package com.mutable.drmPlugin.roap.misc;

/**
 * @author Dean
 *
 */
public class RoapException extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1499532890162142566L;

	/**
	 * 
	 */
	public RoapException() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param message
	 */
	public RoapException(String message) {
		super(message);
	}

	/**
	 * @param cause
	 */
	public RoapException(Throwable cause) {
		super(cause);
	}

	/**
	 * @param message
	 * @param cause
	 */
	public RoapException(String message, Throwable cause) {
		super(message, cause);
	}

}
