#include "tools/MemMan.h"
#include <stdlib.h>


void MemMan::construct(OctetString** dest)
{
	*dest = NULL;
}

void MemMan::destruct(OctetString** dest)
{
	if ((*dest))
	{
		
		if ((*dest)->len)
		{
			free((*dest)->octets);
			(*dest)->octets = NULL;
			(*dest)->len = 0;
		}
		delete (*dest);
		(*dest) = NULL;
	}

}


void MemMan::copy(OctetString** dest, OctetString* src)
{
	destruct(dest);

	if (src == NULL)
	{
		(*dest) = src;
		return;
	}

	*dest = new OctetString();
	(*dest)->octets = (unsigned char*)malloc(src->len*(sizeof(unsigned char)));
	memcpy((*dest)->octets, src->octets, src->len);
	(*dest)->len = src->len;
}

void MemMan::construct(char** dest)
{
        *dest=NULL;
}
void MemMan::construct(unsigned char** dest)
{
		*dest=NULL;
}
void MemMan::construct(char* dest)
{
        *dest='\0';
}
void MemMan::construct(long* dest)
{
        *dest=0;
}
void MemMan::construct(int* dest)
{
        *dest=0;
}

void MemMan::construct(unsigned int* dest)
{
        *dest=0;
}

void MemMan::destruct(unsigned char** dest)
{
		if (*dest)
		{
			delete[] *dest;
			*dest=NULL;
		}
}

void MemMan::destruct(char** dest)
{
        if(*dest)
        {
                delete[] *dest;
                *dest=NULL;
        }
}
void MemMan::destruct(char* dest)
{
        *dest='\0';
}
void MemMan::destruct(long* dest)
{
        *dest=0;
}
void MemMan::destruct(int* dest)
{
        *dest=0;
}
void MemMan::destruct(unsigned int* dest)
{
        *dest=0;
}

void MemMan::copy(char** dest, char* src)
{
        destruct(dest);

        if (src == NULL)
        {
                *dest = src;
                return;
        }
        *dest = new char[strlen(src)+1];
        strcpy(*dest, src);
}

void MemMan::copy(unsigned char** dest, unsigned char* src, int length)
{
        destruct(dest);

        if (src == NULL)
        {
                *dest = src;
                return;
        }
        *dest = (unsigned char*)malloc(length*sizeof(unsigned char));
        memcpy(*dest, src, length);
}


void MemMan::copy(char* dest, char src)
{
        *dest=src;
}
void MemMan::copy(long* dest, long src)
{
        *dest= src;
}
void MemMan::copy(int* dest, int src)
{
        *dest= src;
}
void MemMan::copy(unsigned int* dest,unsigned int src)
{
        *dest= src;
}