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

/**
 * <p>Title: Timer</p>
 * <p>Description: Utility class for timing</p>
 * @version 1.0
 */

import java.util.Date;
import com.mutable.io.OlLogger;

public class Timer
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(m_logger!=null)m_logger.debug(className,method+"() : "+message);}
	private void logWarning(String method,String message){if(m_logger!=null)m_logger.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(m_logger!=null)m_logger.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(m_logger!=null)m_logger.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(m_logger!=null)m_logger.info(className,method+"() : "+message);}

	OlLogger m_logger=new OlLogger();

	public Timer(String p_timerName)
	{
		setTimerName(p_timerName);
		Date now = new Date();
		setStartTime(now.getTime());
		logDebug("","Start Time for " + getTimerName() + " Timer is: " + new Date(this.getStartTime()).toString());
	}

	//Timer Name
	private String m_timerName;
	public String getTimerName()
	{
		return m_timerName;
	}
	public void setTimerName(String p_timerName)
	{
		m_timerName = p_timerName;
	}

	//Elapsed Time
	private long m_elapsedTime;
	public long getElapsedTime()
	{
		return m_elapsedTime;
	}
	public void setElapsedTime(long p_elapsedTime)
	{
		m_elapsedTime = p_elapsedTime;
	}

	//Start Time
	private long m_startTime;
	public long getStartTime()
	{
		return m_startTime;
	}
	public void setStartTime(long p_startTime)
	{
		m_startTime = p_startTime;
	}


	//Stop Time
	private long m_stopTime;
	public long getStopTime()
	{
		return m_stopTime;
	}
	public void setStopTime(long p_stopTime)
	{
		m_stopTime = p_stopTime;
	}

	public void stopTimer()
	{
		Date now = new Date();
		setStopTime(now.getTime());
		setElapsedTime(this.getStopTime() - this.getStartTime());
		logDebug("","Stop Time for " + getTimerName() + " Timer is: " + new Date(this.getStopTime()).toString());
		logDebug("","Elapsed Time for " + getTimerName() + " Timer is: " + (this.getElapsedTime()/1000) +  " seconds");
	}

	public void resetTimer()
	{
		Date now = new Date();
		setStartTime(now.getTime());
		setElapsedTime(0);
		setStopTime(0);
		logDebug("","*** " + getTimerName() + " was reset!!");
		logDebug("","Start Time for " + getTimerName() + " Timer is: " + new Date(this.getStartTime()).toString());
	}
}

