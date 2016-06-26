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

#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include "squashxml/tools/HashMap.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

//typedef map<string, void*, less<string>, allocator<void*> > StringHashMap;
typedef map<string, void*, less<string> > StringHashMap;

class HashMapImpl {
public:
	HashMapImpl();
	StringHashMap oMap;
	StringHashMap::iterator iMap;
};

HashMapImpl::HashMapImpl()
{
	iMap == oMap.end();
}


HashMap::HashMap()
{
	 hashImp = new HashMapImpl();
}

HashMap::~HashMap()
{
	 delete hashImp;
}

void HashMap::put(char *key, void *object)
{
	hashImp->oMap.insert(StringHashMap::value_type(key, object));
}

void* HashMap::get(char *key)
{
	hashImp->iMap = hashImp->oMap.find(key);
	if (hashImp->iMap == hashImp->oMap.end())
		return NULL;
	else
		return (*hashImp->iMap).second;
};

void HashMap::remove(char *key)
{
	hashImp->oMap.erase(key);
}

void HashMap::clear()
{
	hashImp->oMap.clear();
}

int HashMap::size()
{
	return hashImp->oMap.size();
}

void* HashMap::first()
{
	hashImp->iMap = hashImp->oMap.begin();
	if (hashImp->iMap == hashImp->oMap.end())
		return NULL;
	else
		return (*hashImp->iMap).second;
}

void* HashMap::next()
{
	if (hashImp->iMap == hashImp->oMap.end())
		return NULL;
	hashImp->iMap++;

	if (hashImp->iMap == hashImp->oMap.end())
		return NULL;
	else
		return (*hashImp->iMap).second;
}
