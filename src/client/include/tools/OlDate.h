#ifndef _OLDATE_HH
#define _OLDATE_HH

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
//#include <conio.h>
#include <stdio.h>
#include <time.h>

class OlDate
{
public:
	time_t m_value;
	bool m_isNull;
	OlDate()
	{
		setNull();
	}
	OlDate(const time_t value)
	{
		OlDate();
		set(value);
	}
	const time_t get() const {return m_value;}
	void set(const time_t value){m_value=value;m_isNull=false;}
	void set(const OlDate* value){m_value=value->m_value;m_isNull=value->m_isNull;}
	bool isNull() const{return m_isNull;}
	void setNull() {m_isNull=true;m_value=0;}
	void print(const char* name) const
	{
		printf("%s = %ld %s\n",name,m_value,(isNull()?"(NULL)":ctime(&m_value)));
	}
};
#endif
