#include "tools/OlCharArray.h"

	OlCharArray::OlCharArray(int size)
    {
		if(size<=0)
		{
			m_size=0;
			m_value=NULL;
			return;
		}
		m_size=size;
		OlMemMan::construct(&m_value);
		OlMemMan::alloc(&m_value,size+1);
		setNull();
    }
	OlCharArray::OlCharArray(const char* value)
	{
		int size =0;
		if(value!=NULL)
		{
			size=strlen(value);
		}
///////////////////////
		m_size=size;
		OlMemMan::construct(&m_value);
		OlMemMan::alloc(&m_value,size+1);
		setNull();
///////////////////////
		set(value);
	}
	OlCharArray::~OlCharArray()
	{
		OlMemMan::destruct(&m_value);
	}
	const char* OlCharArray::get() const
	{
		return m_value;
	}
	void OlCharArray::set(const OlCharArray* value)
	{
		memcpy(m_value,value->get(),m_size);
	}
	void OlCharArray::set(const char* value)
	{
		strncpy(m_value,value,m_size);
//		memcpy(m_value,value,m_size);
	}

	bool OlCharArray::isNull()const
	{
		if(m_value==NULL || m_value[0]=='\0') return true;
		else return false;
	}
	void OlCharArray::setNull()
	{
		if(m_size!=0)
		memset(m_value,0,m_size+1);
	}
	void OlCharArray::print (const char* name) const
	{
		printf("%s = %s %s\n",name,m_value,(isNull()?"(NULL)":""));
	}
