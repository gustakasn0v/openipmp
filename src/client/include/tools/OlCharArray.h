#ifndef _OLCHARARRAY_HH
#define _OLCHARARRAY_HH

#include <iostream>
#include <string.h>
#include <stdlib.h>
//#include <conio.h>
#include <stdio.h>
#include <time.h>
#include "OlMemMan.h"

class OlCharArray
{
public:
    char* m_value;
	int m_size;
    OlCharArray(int size);
	OlCharArray(const char* value);
	~OlCharArray();
	const char* get() const;
	void set(const OlCharArray* value);
	void set(const char* value);
	bool isNull()const;
	void setNull();
	void print (const char* name) const;
};
#endif
