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

package com.mutable.osms.common.io.message;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * @version 1.0
 */

public class osmsMessageQueryResponse extends osmsMessage
{

	private String results;
    private int length;
    private String heading;
	public osmsMessageQueryResponse()
	{
		super(osmsMessage.osmsMESSAGE_QUERY_RESPONSE);
	}
	public String getResults()
	{
		return results;
	}
	public void setResults(String results)
	{
		this.results = results;
	}
    public void setLength(int length)
    {
        this.length = length;
    }
    public int getLength()
    {
        return length;
    }
    public void setHeading(String heading)
    {
        this.heading = heading;
    }
    public String getHeading()
    {
        return heading;
    }
}