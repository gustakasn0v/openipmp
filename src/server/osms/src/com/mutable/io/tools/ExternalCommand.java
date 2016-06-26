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
 * The Original Code is OpenIPMP.
 * 
 * The Initial Developer of the Original Code is Mutable, Inc.
 * Portions created by Mutable, Inc. are
 * Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved.
 *  
 * 
 */

package com.mutable.io.tools;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;

import org.apache.tools.ant.taskdefs.Sleep;

import com.mutable.io.OlLogger;
import com.mutable.osms.server.app.osmsGlobalObjectManager;
import com.mutable.osms.server.app.osmsServerConfiguration;

/**
 * External command call. Stores output and error streams into strings.
 * 
 */
public class ExternalCommand {
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(log!=null)log.debug(className,method+"() : "+message);}
	private void logWarning(String method,String message){if(log!=null)log.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(log!=null)log.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(log!=null)log.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(log!=null)log.info(className,method+"() : "+message);}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// CONSTRUCTORS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	public ExternalCommand(){
		cmd = "";
		init();
	}
	
	public ExternalCommand(String cmd){
		this.cmd = cmd;
		init();
	}
	
    private void init(){
    	String methodName = "ExternalCommand()";
    	
		log=osmsGlobalObjectManager.getInstance().getLogger();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * The OlLogger object used for logging purposes.
	 */
	private OlLogger log  = null;

	private String cmd;
	public void setCmd(String cmd){
		this.cmd = cmd;
	}
	public String getCmd(){
		return cmd;
	}

	private String[] env;
	public String[] getEnv(){
		return env;
	}
	public void setEnv(String[] env){
		this.env = env;
	}

	protected String stdOut;
	public String getStdOut(){
		return stdOut;
	}
	protected String stdErr;
	public String getStdErr(){
		return stdErr;
	}
	
	protected long timeout = 0;
	public long getTimeout(){
		return timeout;
	}
	public void setTimeout(long timeout){
		this.timeout = timeout;
	}
	/**
	 * @warning Assumes the command will not require any input from stdin.
	 * 
	 * @return Value returned by the external command.
	 * 
	 * @throws IOException
	 * @throws InterruptedException
	 */
	public int exec() throws IOException, InterruptedException {
		String methodName = "exec";
		logDebug(methodName, "");
		Runtime rtime = Runtime.getRuntime();
		Process prc = rtime.exec(cmd, env);
		logDebug(methodName, "External process started.");
		InputStream errStream = prc.getErrorStream();
		InputStream outStream = prc.getInputStream();
		
		stdOut = "";
		stdErr = "";
		boolean finished = false;
		long timeoutCount = 0;
		while(!finished){
			try{
				if(outStream.available() > 0 || errStream.available() > 0){
					stdOut = stdOut + readOutputStream(outStream);
					stdErr = stdErr + readOutputStream(errStream);
					logDebug(methodName, "Reading from standard output and error streams.");
					timeoutCount = 0;
				}else{
					prc.exitValue();
					finished = true;
				}
			}catch (IllegalThreadStateException e){
				// process is not finished yet, continue
				if (timeoutCount * timeout > 1000){
					logDebug(methodName, "Nothing at standard output and error streams, but the process is still running.");
					timeoutCount = 0;
				}
				Thread.sleep(timeout);
			}
		}
		logDebug(methodName, "External process is finished.");
		prc.waitFor(); // this is redundant
		return prc.exitValue();
	}
	
	private String readOutputStream(InputStream outStream) throws IOException {
		int len = outStream.available();
		byte[] outMsg = new byte[len];
		outStream.read(outMsg);
		return new String(outMsg);
	}
}
