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



 /**

  * <p>Title: </p>

  * <p>Description: </p>

  * @version 1.0

  */



package com.mutable.io;

import java.io.*;

import java.util.*;

import javax.swing.*;

import javax.swing.text.JTextComponent;

public class OlLogger

{

	///////////////////////////////////////////////////////////////////////////////////////////////

	//

	// PRIVATE MEMBERS

	//

	//////////////////////////////////////////////////////////////////////////////////////////////

	private BufferedWriterArray m_DebugFile= new BufferedWriterArray();

	private BufferedWriterArray m_ErrorFile= new BufferedWriterArray();

	private BufferedWriterArray m_InfoFile= new BufferedWriterArray();

	private boolean m_bError=true;

	private boolean m_bWarning=true;

	private boolean m_bInfo=true;

	private boolean m_bDebug=true;

	private boolean m_bUI=true;

	private JTextComponent m_jtcDebug=null;

	private JTextComponent m_jtcInfo=null;

	private JTextComponent m_jtcError=null;

	private int maxHeaderLength=70;

	private long m_numErrors=0;



	///////////////////////////////////////////////////////////////////////////////////////////////

	//

	// PROPERTIES

	//

	//////////////////////////////////////////////////////////////////////////////////////////////

	public void setMaxHeaderLength(int length){maxHeaderLength=length;}

	public void setError(boolean b){m_bError=b;}

	public void setInfo(boolean b){m_bInfo=b;}

	public void setWarning(boolean b){m_bWarning=b;}

	public void setDebug(boolean b){m_bDebug=b;}

	public void setUI(boolean b){m_bUI=b;}

	public void setJTextComponent(JTextComponent jtc){m_jtcDebug=m_jtcInfo=m_jtcError=jtc;}

	public void setJTextComponentDebug(JTextComponent jtc){this.m_jtcDebug=jtc;}

	public void setJTextComponentInfo(JTextComponent jtc){this.m_jtcInfo=jtc;}

	public void setJTextComponentError(JTextComponent jtc){this.m_jtcError=jtc;}

	public void addFileDebug(BufferedWriter file){m_DebugFile.add(file);}

	public void addFileError(BufferedWriter file){m_ErrorFile.add(file);}

	public void addFileInfo(BufferedWriter file){m_InfoFile.add(file);}

	public long getNumErrors(){return m_numErrors;}

	public static final boolean LOG_BENCHMARK = false;



	///////////////////////////////////////////////////////////////////////////////////////////////

	//

	// PRIVATE METHODS

	//

	//////////////////////////////////////////////////////////////////////////////////////////////

	private String StringTime(Calendar cal)

	{

		int hour = cal.get(cal.HOUR);

		String shour="";if (hour< 10) shour="0";shour+=hour;

		int min = cal.get(cal.MINUTE);

		String smin="";if (min< 10) smin="0";smin+=min;

		int sec = cal.get(cal.SECOND);

		String ssec="";if (sec< 10) ssec="0";ssec+=sec;

		int  milliSec = cal.get(cal.MILLISECOND);

		String smilliSec="";

		if (milliSec< 10)smilliSec="00";

		else if (milliSec< 100)smilliSec="0";

		smilliSec+=milliSec;

		String result = " " + shour + ":" + smin + ":" + ssec + "." + smilliSec;

		return result;

	}

	private String logBuildMessage(String pHeader,String pMessage)

	{

		final int threadNameSize=10;

		String strThreadName = Thread.currentThread().getName();

		char[] threadName = new char[threadNameSize+1];

		for(int i=1;i<threadNameSize && strThreadName.length()>=i;i++)

		{

			threadName[i]=strThreadName.charAt(i-1);

		}

		for(int i=strThreadName.length()+1;i<threadNameSize ;i++)

		{

			threadName[i]=' ';

		}

		threadName[0]='[';

		threadName[threadNameSize]=']';

		Date dt = new Date();

		//set date

		Calendar cal = Calendar.getInstance();

		cal.setTime(dt);

		String message = StringTime(cal)+" ";

		message+=pHeader;

		for(int i=message.length();i<maxHeaderLength;i++)

		{

			message+=" ";

		}

		message+=" --- "+pMessage;

		return new String(threadName)+message;

	}

	private String logBuildMessage(String pHeader,String postHeader,String pMessage)

	{

		final int threadNameSize=10;

		String strThreadName = Thread.currentThread().getName();

		char[] threadName = new char[threadNameSize+1];

		for(int i=1;i<threadNameSize && strThreadName.length()>=i;i++)

		{

			threadName[i]=strThreadName.charAt(i-1);

		}

		for(int i=strThreadName.length()+1;i<threadNameSize ;i++)

		{

			threadName[i]='-';

		}

		threadName[0]='[';

		threadName[threadNameSize]=']';

		Date dt = new Date();

		//set date

		Calendar cal = Calendar.getInstance();

		cal.setTime(dt);

		String message = StringTime(cal)+" "+new String(threadName)+" "+pHeader;

		for(int i=message.length();i<maxHeaderLength+threadNameSize;i++)

		{

			message+=" ";

		}

		message+=postHeader+" --- "+pMessage;

		return   message;

	}

	private synchronized void write(String message,JTextComponent jtc,BufferedWriterArray fileArray)

	{



		if(jtc!=null && m_bUI)

		{

			jtc.setText(jtc.getText()+"\n"+message);

		}

		BufferedWriter[] files=fileArray.getFiles();

		for (int i = 0; files!=null && i < files.length; i++)

		{

			try

			{

				files[i].write(message+"\n");

				files[i].flush();

			}

			catch(Exception ex){}

		}

		System.out.println(message);

	}

	private String buildStackTrace(Exception e)

	{

		try

		{

			ByteArrayOutputStream os = new ByteArrayOutputStream();

			PrintStream ps = new PrintStream(os);

			e.printStackTrace(ps);

			os.flush();

			return os.toString();

		}

		catch (Exception ex)

		{

			return "";

		}

	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	//

	// PUBLIC METHODS

	//

	//////////////////////////////////////////////////////////////////////////////////////////////

	public void error(String header,String message)

	{

		m_numErrors++;

		if(!m_bError) return;

		if(message==null || message.equals("")) {write("",m_jtcError,m_ErrorFile);}

		else {write(logBuildMessage(header,"[ ERROR ] ",message),m_jtcError,m_ErrorFile);}

	}

	public void error(String header,String message,Exception e)

	{

		m_numErrors++;

		if(!m_bError) return;

		//build stack trace

		String stackTrace=buildStackTrace(e);

/*

		StackTraceElement ste[] = e.getStackTrace();

		stackTrace="\n"+e.toString();

		for (int i = 0; i < ste.length; i++)

		{

			stackTrace+="\n\tat "+ste[i].toString();

		}

*/



		if(message==null || message.equals(""))

		{write(logBuildMessage(header,"[ ERROR ] ",stackTrace),m_jtcError,m_ErrorFile);}

		else

		{write(logBuildMessage(header,"[ ERROR ] ",message+stackTrace),m_jtcError,m_ErrorFile);}

	}

	public void info(String header,String message)

	{

		if(!m_bInfo) return;

		if(message==null || message.equals("")) {write("",m_jtcInfo,m_InfoFile);return;}

		else {write(logBuildMessage(header,"[ info  ] ",message),m_jtcInfo,m_InfoFile);}

	}

	public void warning(String header,String message)

	{

		if(!m_bWarning) return;

		if(message==null || message.equals("")) {write("",m_jtcInfo,m_InfoFile);return;}

		else {write(logBuildMessage(header,"[WARNING] ",message),m_jtcInfo,m_InfoFile);}

	}

	public void debug(String header,String message)

	{

		if(!m_bDebug) return;

		if(message==null || message.equals("")) {write("",m_jtcDebug,m_DebugFile);return;}

		else {write(logBuildMessage(header,"[ debug ] ",message),m_jtcDebug,m_DebugFile);}

	}

	public void erase()

	{

		if(m_jtcDebug!=null)m_jtcDebug.setText("");

		if(m_jtcInfo!=null)m_jtcInfo.setText("");

		if(m_jtcError!=null)m_jtcError.setText("");

	}



	///////////////////////////////////////////////////////////////////////////////////////////////

	//

	// PRIVATE INNER CLASSES

	//

	//////////////////////////////////////////////////////////////////////////////////////////////

	private class BufferedWriterArray

	{

		private Vector m_vector = new Vector();

		public void add(BufferedWriter file)

		{

			m_vector.add(file);

		}

		public BufferedWriter[] getFiles()

		{

			if(m_vector.size()==0)return null;

			BufferedWriter[] array= new BufferedWriter[m_vector.size()];

			Enumeration enume = m_vector.elements();

			int i=0;

			while (enume.hasMoreElements())

			{

				Object item = enume.nextElement();

				array[i]=(BufferedWriter)item;

				i++;

			}

			return array;

		}

	}

}





