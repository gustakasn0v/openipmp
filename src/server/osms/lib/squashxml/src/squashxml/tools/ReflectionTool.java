/* ***** BEGIN LICENSE BLOCK *****
 *	The contents of this file are subject to the Mozilla Public License
 *	Version 1.1 (the "License"); you may not use this file except in
 *	compliance with the License. You may obtain a copy of the License at
 *	http://www.mozilla.org/MPL/
 *
 *	Software distributed under the License is distributed on an "AS IS"
 *	basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 *	License for the specific language governing rights and limitations
 *	under the License.
 *
 *	The Original Code is SquashXML.
 *
 *	The Initial Developer of the Original Code is Ayman A. Gebrail.
 *	Portions created by Ayman A. Gebrail are
 *	Copyright (C) 2002 Ayman A. Gebrail. All Rights Reserved.
 *
 *  Contributor(s):
 *
 * ***** END LICENSE BLOCK ***** */

package squashxml.tools;


import java.util.Vector;
import java.lang.reflect.*;


public class ReflectionTool
{

	public static Vector getBeanMethods(Object obj, boolean bParentsToo)
	{
		Class c = obj.getClass();
		Method methods[];
		if (bParentsToo)
			methods = c.getMethods();
		else
			methods = c.getDeclaredMethods();
		Vector v = new Vector();

		// search for get()'s
		for (int i = 0; i < methods.length; i++)
		{
			String methodName = methods[i].getName();
			if (methodName.startsWith("get") /*&& methodName.compareTo("getClass") != 0*/)
			{
				Class params[] = methods[i].getParameterTypes();
				Class returnType = methods[i].getReturnType();
				if (params.length == 0)
				{
					// Have to start at 0, set() may come before associated get(); Order (n^2) needs better (hash?) lookup.
					for (int iset = 0; iset < methods.length; iset++)
					{
						String name2 = methods[iset].getName();
						if (name2.startsWith("set") && methodName.substring(3).compareTo(name2.substring(3)) == 0)
						{
							Class params2[] = methods[iset].getParameterTypes();
							Class returnType2 = methods[iset].getReturnType();
							if (params2.length == 1 && params2[0] == returnType && returnType2.getName().equals("void"))
							{
								v.add(methods[i]);
								break;
							}
						}
					}
				}
			}
		}
		return v;
	}

}

