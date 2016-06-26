#include "tools/OlRaw.h"

	OlRaw::OlRaw()
	{
		OlMemMan::construct(&m_value);
		m_size=0;
	}
	OlRaw::OlRaw(const unsigned char* value,const int size)
	{
		OlMemMan::construct(&m_value);
		m_size=0;
		set(value,size);
	}
	OlRaw::~OlRaw()
	{
		OlMemMan::destruct(&m_value);
	}
	const unsigned char* OlRaw::get() const
	{
		return m_value;
	}
	const int OlRaw::getSize() const
	{
		return m_size;
	}
	void OlRaw::set(const unsigned char* value,const int size)
	{
		m_size=size;
		OlMemMan::copy(&m_value,value, m_size );
	}
	void OlRaw::set(const OlRaw* value)
	{
		if(&value==NULL)
		{
			setNull();
			return;
		}
		m_size=value->getSize();
		if(m_size>0)
		{
			OlMemMan::copy(&m_value,value->get(), value->getSize() );
		}
	}
	bool OlRaw::isNull()const
	{
		if(m_size==0) return true;
		else return false;
	}
	void OlRaw::setNull()
	{
		OlMemMan::destruct(&m_value);
		m_size=0;
	}

	void OlRaw::print(const char* name) const
	{
	    printf("%s size= %d\n",name,m_size);//RAW
	}

