/*
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
 */
#ifndef __MEMMAN_HPP
#define __MEMMAN_HPP

#include <memory.h>
#include <string.h>
#include "OctetString.h"

/**
        Class: MemMan
        Description: Memory Management

*/

class MemMan
{
public:
        static void construct(char** dest);
        static void construct(char* dest);
        static void construct(long* dest);
        static void construct(int* dest);
        static void construct(unsigned int* dest);
		static void construct(unsigned char** dest);
		static void construct(OctetString** dest);

        static void destruct(char** dest);
        static void destruct(char* dest);
        static void destruct(long* dest);
        static void destruct(int* dest);
        static void destruct(unsigned int* dest);
		static void destruct(unsigned char** dest);
		static void destruct(OctetString** dest);

        static void copy(unsigned char** dest, unsigned char* src, int length);
		static void copy(char** dest, char* src);
        static void copy(char* dest, char src);
        static void copy(long* dest, long src);
        static void copy(int* dest, int src);
        static void copy(unsigned int* dest,unsigned int src);
		static void copy(OctetString** dest, OctetString* src);
};
#endif






