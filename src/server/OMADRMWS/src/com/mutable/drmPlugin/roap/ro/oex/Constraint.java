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
package com.mutable.drmPlugin.roap.ro.oex;

import com.mutable.drmPlugin.roap.ro.odd.*;
import com.mutable.drmPlugin.roap.ro.omadd.*;
import com.mutable.drmPlugin.xml.*;
import java.util.*;

public class Constraint extends XmlChild {
	
	protected CountConstraint count;
	protected TimedCountConstraint timedCount;
	protected DateTimeConstraint dateTime;
	protected IntervalConstraint interval;
	protected AccumulatedConstraint accumulate;
	protected IndividualConstraint individual;
	protected SystemConstraints system;

	public String XmlEncode() {
		// TODO Auto-generated method stub
		return null;
	}

	public String XmlEncode(String varName) {
		// TODO Auto-generated method stub
		return null;
	}

	public Constraint(CountConstraint count, TimedCountConstraint tcount,  
			DateTimeConstraint time, IntervalConstraint interval,  
			AccumulatedConstraint accumulate, IndividualConstraint individual,
			SystemConstraints system) {
		super();
		this.accumulate = accumulate;
		this.count = count;
		dateTime = time;
		this.individual = individual;
		this.interval = interval;
		this.system = (system==null
						? null
						: (SystemConstraints) system.nonEmptyOrNull());
		timedCount = tcount;
	}

	public AccumulatedConstraint getAccumulate() {
		return accumulate;
	}

	public CountConstraint getCount() {
		return count;
	}

	public DateTimeConstraint getDateTime() {
		return dateTime;
	}

	public IndividualConstraint getIndividual() {
		return individual;
	}

	public IntervalConstraint getInterval() {
		return interval;
	}

	public SystemConstraints getSystem() {
		return system;
	}

	public TimedCountConstraint getTimedCount() {
		return timedCount;
	}
	
	public IElement asDomChildOf(IElement father, String path) {
		IElement newElem = super.asDomChildOf(father, path);
		if (count!=null) count.asDomChildOf(newElem);
		if (timedCount!=null) timedCount.asDomChildOf(newElem);
		if (dateTime!=null) dateTime.asDomChildOf(newElem);
		if (interval!=null) interval.asDomChildOf(newElem);
		if (accumulate!=null) accumulate.asDomChildOf(newElem);
		if (individual!=null) individual.asDomChildOf(newElem);
		if (system!=null)
			for(int i=0;i<system.getData().size();i++)
				((SystemConstraint)system.getData().elementAt(i)).asDomChildOf(newElem);
		return newElem;		
	}
	
	public String domName() { return "constraint"; }
	
	public static Constraint instanceFromDomElement(IElement elem) {
		IElement child;
		CountConstraint c = ((child=elem.getChildElement("count"))==null) 
								? null
				                : CountConstraint.instanceFromDomElement(child);
		TimedCountConstraint tc = ((child=elem.getChildElement("timedcount"))==null) 
								? null
                                : TimedCountConstraint.instanceFromDomElement(child);
		DateTimeConstraint dt = ((child=elem.getChildElement("datetime"))==null) 
								? null
                                : DateTimeConstraint.instanceFromDomElement(child);
		IntervalConstraint in = ((child=elem.getChildElement("interval"))==null) 
								? null
                                : IntervalConstraint.instanceFromDomElement(child);
		AccumulatedConstraint ac = ((child=elem.getChildElement("accumulated"))==null) 
								? null
                                : AccumulatedConstraint.instanceFromDomElement(child);
		IndividualConstraint ind = ((child=elem.getChildElement("individual"))==null) 
								? null
                                : IndividualConstraint.instanceFromDomElement(child);
		IElements children = elem.getChildElements("system");
		Vector v = new Vector();
		for(Iterator i=children.iterator();i.hasNext();)
			v.add(SystemConstraint.instanceFromDomElement(((IElement)i.next())));
		return new Constraint(c,tc,dt,in,ac,ind,new SystemConstraints(v));

	}

}
