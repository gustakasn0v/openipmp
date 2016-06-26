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
package com.mutable.drmPlugin.server;

import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.ro.ProtectedRo;
import com.mutable.drmPlugin.roap.ro.oex.Rights;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.Pair;
import com.mutable.drmPlugin.tools.UriValue;

/** 
 * The rigths related book-keeping services that the server relies on.
 *  
 * 
 *
 */
public interface IRoDatabase {
	
	public boolean addRights(RoapIdentifier deviceId, UriValue contentId, Rights rights);
	public Rights getRights(RoapIdentifier deviceId, UriValue contentId);
	
	
	public boolean addContentKey(UriValue contentId, Base64String encKey);
	public Base64String getContentKey(UriValue contentId);
	
	public boolean addRoId(RoapIdentifier deviceId, UriValue contentId, IdValue roId);
	public IdValue getRoId(RoapIdentifier deviceId, UriValue contentId); 
	
	public boolean addRights(RoapIdentifier deviceId, UriValue contentId,
								IdValue roId, Rights rights);
	
	public Pair getContentIdRights(IdValue roId);
	
	public ProtectedRo makeProtectedRo(RoapIdentifier devId, UriValue contentId, IdValue roId);

}
