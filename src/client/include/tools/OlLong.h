#ifndef _OLLONG_HH
#define _OLLONG_HH

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
//#include <conio.h>
#include <stdio.h>
#include <time.h>


class OlLong
{
public:
        long m_value;
        bool m_isNull;
        OlLong()
        {
			setNull();
        }
		OlLong(const long value)
		{
			OlLong();
			set(value);
		}
        long get()
		{
			return m_value;
		}

		void set(const long value)
		{
			m_value=value;
			m_isNull=false;
		}
		void set(const OlLong* value)
		{

			m_value=value->m_value;
			m_isNull=value->m_isNull;
		}

        bool isNull() const
		{
			return m_isNull;
		}
        void setNull()
		{
			m_isNull=true;
			m_value=0;
		}
		void print(const char* name)
		{
		    printf("%s = %ld %s\n",name,m_value,(isNull()?"(NULL)":""));
		}
};
#endif
