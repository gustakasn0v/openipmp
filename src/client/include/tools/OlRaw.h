#ifndef __OLRAW_HPP
#define __OLRAW_HPP

//#include <iostream.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
//#include <conio.h>
#include <stdio.h>
#include <time.h>
#include "tools/OlMemMan.h"

#include <memory.h>


class OlRaw
{
public:
	unsigned char* m_value;
	int m_size;

	OlRaw();
	OlRaw(const unsigned char* value,const int size);
	~OlRaw();
	const unsigned char* get() const;
	const int getSize() const;
	void set(const unsigned char* value,const int size);
	void set(const OlRaw* value);
	bool isNull()const;
	void setNull();
	void print(const char* name) const;

};
#endif
