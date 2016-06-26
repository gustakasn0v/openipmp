#ifndef __OLMEMMAN_HPP
#define __OLMEMMAN_HPP

#include <memory.h>
#include <string.h>
#include <stdio.h>

class OlMemMan
{
public:
	static void construct(char** dest);
	static void construct(unsigned char** dest);
	static void construct(long* dest);
	static void construct(int* dest);
	static void construct(unsigned int* dest);

	static void destruct(char** dest);
	static void destruct(unsigned char** dest);
	static void destruct(long* dest);
	static void destruct(int* dest);
	static void destruct(unsigned int* dest);

	static void copy(char** dest, const char* src);
	static void copy(char** dest, const char* src, int srcSize);
	static void copy(unsigned char** dest, const unsigned char* src);
	static void copy(unsigned char** dest, const unsigned char* src, int srcSize);
	static void copy(long* dest, long src);
	static void copy(int* dest, int src);
	static void copy(unsigned int* dest,unsigned int src);
	static void alloc(char** dest,int size);
};
#endif
