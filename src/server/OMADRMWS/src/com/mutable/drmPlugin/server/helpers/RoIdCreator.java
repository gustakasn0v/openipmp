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
package com.mutable.drmPlugin.server.helpers;

import org.apache.axis.types.UnsignedInt;

import com.mutable.drmPlugin.roap.messages.*;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.X509SPKIHash;
import com.mutable.drmPlugin.server.IRoIdCreator;
import com.mutable.drmPlugin.server.ServerAbstract;
import com.mutable.drmPlugin.tools.*;
import java.io.*;
import java.util.*;

public class RoIdCreator implements IRoIdCreator {
	protected UnsignedInt lastId = new UnsignedInt(0);
	protected ServerAbstract server;


	public RoIdCreator(ServerAbstract server) {
		super();
		// TODO Auto-generated constructor stub
		this.server = server;
	}
	public IdValue createRoId(RoapIdentifier deviceId, UriVector contentIds) {
		StringWriter sw = new StringWriter();
		sw.write(((X509SPKIHash)deviceId.getIdentifier()).getHash().toString());
		sw.write(server.createNonce().toString());
		for(Iterator i=contentIds.iterator();i.hasNext();)
			sw.write(i.next().toString());
		return new IdValue(new Base64String(sw.toString().getBytes()).toString());
	}

}
