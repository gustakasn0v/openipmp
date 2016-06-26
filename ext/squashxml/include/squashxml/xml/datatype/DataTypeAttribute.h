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

#ifndef DataTypeAttribute_H
#define DataTypeAttribute_H

#include <string.h>

class DataTypeAttribute
{
public:
  DataTypeAttribute(char* n, char* v)
  {
    strcpy(name, n);
    strcpy(value, v);
  }
  char* getName(){ return name; }
  char* getValue(){ return value; }


private:
  char name[256];		// TODO: Change to constant
  char value[256];

};

#endif // DataTypeAttribute_H
