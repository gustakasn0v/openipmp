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


public class DSAKeyValue extends KeyValue {
	
	private DSAKeyValuePQ ppqq;
	private CryptoBinary gg, yy, jj;
	private DSAKeyValueSeedCtr sctr;
	


	
	/**
	 * 
	 * @param ppqq , @param gg , @param jj and @param sctr are optional elements, while
	 * @param yy is a mandatory element
	 */

	public DSAKeyValue(DSAKeyValuePQ ppqq, CryptoBinary yy, 
			CryptoBinary gg, CryptoBinary jj,  
			DSAKeyValueSeedCtr sctr) {
		super();
		if (yy==null) throw new IllegalArgumentException();
		this.gg = gg;
		this.jj = jj;
		this.ppqq = ppqq;
		this.sctr = sctr;
		this.yy = yy;
	}

	public CryptoBinary getGg() {
		return gg;
	}

	public CryptoBinary getJj() {
		return jj;
	}

	public DSAKeyValuePQ getPpqq() {
		return ppqq;
	}

	public DSAKeyValueSeedCtr getSctr() {
		return sctr;
	}

	public CryptoBinary getYy() {
		return yy;
	}

	public CryptoBinary getP() {
		return ppqq.getP();
	}

	public CryptoBinary getQ() {
		return ppqq.getQ();
	}

	public CryptoBinary getPGenCounter() {
		return sctr.getPGenCounter();
	}

	public CryptoBinary getSeed() {
		return sctr.getSeed();
	}

}
