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

#include "io/message/osmsMessageRegisterDigitalItemInstanceRequest.h"

osmsMessageRegisterDigitalItemInstanceRequest::osmsMessageRegisterDigitalItemInstanceRequest()
	: osmsMessage(osmsMessage::osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_REQUEST, "com.mutable.osms.common.io.message.osmsMessageRegisterDigitalItemInstanceRequest")
{
	m_MetadataType = NULL;
	m_MetadataXml = NULL;
	m_KeyXml = NULL;
	m_AuxDataXml = NULL;
}

osmsMessageRegisterDigitalItemInstanceRequest::~osmsMessageRegisterDigitalItemInstanceRequest()
{
	if (m_MetadataType != NULL)
		delete[] m_MetadataType;

	if (m_MetadataXml != NULL)
		delete[] m_MetadataXml;

	if (m_KeyXml != NULL)
		delete[] m_KeyXml;

	if (m_AuxDataXml != NULL)
		delete[] m_AuxDataXml;
}



char* osmsMessageRegisterDigitalItemInstanceRequest::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageRegisterDigitalItemInstanceRequest>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<MetadataType type=\"char[]\"></MetadataType>" \
			"<MetadataXml type=\"char[]\"></MetadataXml>" \
			"<KeyXml type=\"char[]\"></KeyXml>" \
			"<AuxDataXml type=\"char[]\"></AuxDataXml>" \
		"</com.mutable.osms.common.io.message.osmsMessageRegisterDigitalItemInstanceRequest>";
}

char* osmsMessageRegisterDigitalItemInstanceRequest::encode()
{
	XMLDocument* pDoc = new XMLDocument();
	if (pDoc == NULL)
		return NULL;

	if (!pDoc->decode(xmlTemplate(), getName()))
	{
		delete pDoc;
		return NULL;
	}

	pDoc->setInteger("MessageType", getMessageType());
	pDoc->setString("MetadataType", getMetadataType());
	pDoc->setString("MetadataXml", getMetadataXml());
	pDoc->setString("KeyXml", getKeyXml());
	pDoc->setString("AuxDataXml", getAuxDataXml());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageRegisterDigitalItemInstanceRequest::decode(char* xmlText)
{
	XMLDocument* pDoc = new XMLDocument();
	if (pDoc == NULL)
		return false;

	if (!pDoc->decode(xmlText, getName()))
	{
		delete pDoc;
		return false;
	}

	setMessageType(pDoc->getInteger("MessageType"));
  char* tmp = pDoc->getString("MetadataType");
	setMetadataType(tmp);
  delete[] tmp;
  tmp = pDoc->getString("MetadataXml");
	setMetadataXml(tmp);
  delete[] tmp;
  tmp = pDoc->getString("KeyXml");
	setKeyXml(tmp);
  delete[] tmp;
  tmp = pDoc->getString("AuxDataXml");
	setAuxDataXml(tmp);
  delete[] tmp;

	delete pDoc;

	return true;
}




//bean properties
char* osmsMessageRegisterDigitalItemInstanceRequest::getMetadataType()
{
	return m_MetadataType;
}

void osmsMessageRegisterDigitalItemInstanceRequest::setMetadataType(char* MetadataType)
{
	if (m_MetadataType != NULL)
	{
		delete[] m_MetadataType;
		m_MetadataType = NULL;
	}
	if (MetadataType != NULL)
	{
		m_MetadataType = new char[strlen(MetadataType)+1];
		strcpy(m_MetadataType, MetadataType);
	}
}


char* osmsMessageRegisterDigitalItemInstanceRequest::getMetadataXml()
{
	return m_MetadataXml;
}

void osmsMessageRegisterDigitalItemInstanceRequest::setMetadataXml(char* MetadataXml)
{
	if (m_MetadataXml != NULL)
	{
		delete[] m_MetadataXml;
		m_MetadataXml = NULL;
	}
	if (MetadataXml != NULL)
	{
		m_MetadataXml = new char[strlen(MetadataXml)+1];
		strcpy(m_MetadataXml, MetadataXml);
	}
}


char* osmsMessageRegisterDigitalItemInstanceRequest::getKeyXml()
{
	return m_KeyXml;
}

void osmsMessageRegisterDigitalItemInstanceRequest::setKeyXml(char* KeyXml)
{
	if (m_KeyXml != NULL)
	{
		delete[] m_KeyXml;
		m_KeyXml = NULL;
	}
	if (KeyXml != NULL)
	{
		m_KeyXml = new char[strlen(KeyXml)+1];
		strcpy(m_KeyXml, KeyXml);
	}
}

char* osmsMessageRegisterDigitalItemInstanceRequest::getAuxDataXml()
{
	return m_AuxDataXml;
}

void osmsMessageRegisterDigitalItemInstanceRequest::setAuxDataXml(char* AuxDataXml)
{
	if (m_AuxDataXml != NULL)
	{
		delete[] m_AuxDataXml;
		m_AuxDataXml = NULL;
	}
	if (AuxDataXml != NULL)
	{
		m_AuxDataXml = new char[strlen(AuxDataXml)+1];
		strcpy(m_AuxDataXml, AuxDataXml);
	}
}
