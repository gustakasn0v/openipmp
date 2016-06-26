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

import java.io.*;

public class Logger {
	
	public static String logFilePath = "../openIPMP/OMADRM/drmserver.log";
//		System.getProperty("user.dir")+"\\config\\drmserver.log";
	

	public static void log(String header, String message) {
		PrintWriter pw=null;
		try {
			pw = new PrintWriter(new FileWriter(logFilePath,true));
			pw.println(header);
			if (message!=null) pw.println(message);
			pw.println("");
			pw.close();
		} catch (IOException e) {
			if (pw!=null) pw.close();
			e.printStackTrace();
		}
		
		
	}

}
