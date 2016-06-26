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

import com.mutable.drmPlugin.roap.ro.odd.DisplayPermission;
import com.mutable.drmPlugin.roap.ro.odd.ExecutePermission;
import com.mutable.drmPlugin.roap.ro.odd.PermissionElementAbstract;
import com.mutable.drmPlugin.roap.ro.odd.PlayPermission;
import com.mutable.drmPlugin.roap.ro.odd.PrintPermission;
import com.mutable.drmPlugin.roap.ro.omadd.ExportPermissionAbstract;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.xml.XmlChild;

public class Permission extends XmlChild {
	
	protected Constraint constraint;
	protected PermissionAssets assets;
	protected PlayPermission play;
	protected DisplayPermission display;
	protected ExecutePermission execute;
	protected PrintPermission print;
	protected ExportPermissionAbstract export;


	public Permission(Constraint constraint, PermissionAssets assets, 
			PlayPermission play, DisplayPermission display, 
			ExecutePermission execute, PrintPermission print,
			ExportPermissionAbstract export			) {
		super();
		this.assets = (assets==null
						? null
						: (PermissionAssets) assets.nonEmptyOrNull());
		this.constraint = constraint;
		this.display = display;
		this.execute = execute;
		this.export = export;
		this.play = play;
		this.print = print;
	}

	public PermissionAssets getAssets() {
		return assets;
	}

	public Constraint getConstraint() {
		return constraint;
	}

	public DisplayPermission getDisplay() {
		return display;
	}

	public ExecutePermission getExecute() {
		return execute;
	}

	public ExportPermissionAbstract getExport() {
		return export;
	}

	public PlayPermission getPlay() {
		return play;
	}

	public PrintPermission getPrint() {
		return print;
	}
	
	public IElement asDomChildOf(IElement father,String path) {
		IElement newElem = super.asDomChildOf(father,path);
		if (getConstraint()!=null) getConstraint().asDomChildOf(newElem);
		if (getAssets()!=null) getAssets().asDomChildrenOf(newElem);
		if (getPlay()!=null) getPlay().asDomChildOf(newElem);
		if (getDisplay()!=null) getDisplay().asDomChildOf(newElem);
		if (getExecute()!=null) getExecute().asDomChildOf(newElem);
		if (getPrint()!=null) getPrint().asDomChildOf(newElem);
		if (getExport()!=null) getExport().asDomChildOf(newElem);
		return newElem;
	}
	
	public String domName() { return "permission"; }
	
	public static Permission instanceFromDomElement(IElement elem) {
		IElement ctnElem = elem.getChildElement("constraint");
		Constraint ctn = (ctnElem==null) ? null : Constraint.instanceFromDomElement(ctnElem);
		IElements assetElems = elem.getChildElements("asset");
		PermissionAssets assets = (assetElems==null)
									? null
									: PermissionAssets.instanceFromDomElements(assetElems);
		IElement playElem = elem.getChildElement("play");
		PlayPermission play = (playElem==null) ? null : (PlayPermission)PermissionElementAbstract.instanceFromDomElement(playElem);
		IElement displayElem = elem.getChildElement("display");
		DisplayPermission display = (displayElem==null) ? null : (DisplayPermission)PermissionElementAbstract.instanceFromDomElement(displayElem);
		IElement execElem = elem.getChildElement("execute");
		ExecutePermission exec = (execElem==null) ? null : (ExecutePermission)PermissionElementAbstract.instanceFromDomElement(execElem);
		IElement printElem = elem.getChildElement("print");
		PrintPermission print = (printElem==null) ? null : (PrintPermission)PermissionElementAbstract.instanceFromDomElement(printElem);
		IElement exportElem = elem.getChildElement("export");
		ExportPermissionAbstract export = (exportElem==null) ? null : (ExportPermissionAbstract)PermissionElementAbstract.instanceFromDomElement(exportElem);
		return new Permission(ctn,assets,play,display,exec,print,export);
	}

}
