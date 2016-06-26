#include "tools/OlMemMan.h"



void OlMemMan::construct(char** dest)
{
	*dest=NULL;
}
void OlMemMan::construct(unsigned char** dest)
{
	*dest=NULL;
}
void OlMemMan::construct(long* dest)
{
	*dest=0;
}
void OlMemMan::construct(int* dest)
{
	*dest=0;
}

void OlMemMan::construct(unsigned int* dest)
{
	*dest=0;
}



void OlMemMan::destruct(char** dest)
{
	if(*dest)
	{
		delete[] *dest;
		*dest=NULL;
	}
}
void OlMemMan::destruct(unsigned char** dest)
{
	if(*dest)
	{
		delete[] *dest;
		*dest=NULL;
	}
}
void OlMemMan::destruct(long* dest)
{
	*dest=0;
}
void OlMemMan::destruct(int* dest)
{
	*dest=0;
}
void OlMemMan::destruct(unsigned int* dest)
{
	*dest=0;
}





void OlMemMan::copy(char** dest, const char* src)
{
	destruct(dest);

	if (src == NULL)
	{
		*dest = NULL;
		return;
	}
	*dest = new char[strlen(src)+1];
	strcpy(*dest, src);
}
void OlMemMan::copy(char** dest, const char* src, int maxLen)
{
	destruct(dest);
	if (maxLen == 0 || src == NULL)
	{
		*dest = NULL;
		return;
	}
	*dest = new char[maxLen];
	memcpy(*dest,src,maxLen);
}
void OlMemMan::copy(unsigned char** dest, const unsigned char* src)
{
	destruct(dest);

	if (src == NULL)
	{
		*dest = NULL;
		return;
	}
	*dest = new unsigned char[strlen((const char*)src)+1];
	memcpy(*dest, src,strlen((const char*)src));
}
void OlMemMan::copy(unsigned char** dest, const unsigned char* src, int maxLen)
{
	destruct(dest);
	if (maxLen == 0 || src == NULL)
	{
		*dest = NULL;
		return;
	}
	*dest = new unsigned char[maxLen];
	memcpy(*dest,src,maxLen);
}
void OlMemMan::copy(long* dest, long src)
{
	*dest= src;
}
void OlMemMan::copy(int* dest, int src)
{
	*dest= src;
}
void OlMemMan::copy(unsigned int* dest,unsigned int src)
{
	*dest= src;
}

void OlMemMan::alloc(char **dest,int size)
{
	destruct(dest);
	if (size ==0)
	{
		*dest = NULL;
		return;
	}
	*dest = new char[size+1];
	memset(*dest,0,size+1);
}
