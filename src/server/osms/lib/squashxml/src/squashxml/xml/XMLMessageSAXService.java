/* ***** BEGIN LICENSE BLOCK *****
 *	The contents of this file are subject to the Mozilla Public License
 *	Version 1.1 (the "License"); you may not use this file except in
 *	compliance with the License. You may obtain a copy of the License at
 *	http://www.mozilla.org/MPL/
 *
 *	Software distributed under the License is distributed on an "AS IS"
 *	basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 *	License for the specific language governing rights and limitations
 *	under the License.
 *
 *	The Original Code is SquashXML.
 *
 *	The Initial Developer of the Original Code is Ayman A. Gebrail.
 *	Portions created by Ayman A. Gebrail are
 *	Copyright (C) 2002 Ayman A. Gebrail. All Rights Reserved.
 *
 *  Contributor(s):
 *
 * ***** END LICENSE BLOCK ***** */

package squashxml.xml;

import squashxml.tools.*;

//======================================================================
// THE GRAMMER FOR XMLMessage
//======================================================================

/****************************************************************************
<?xml version=\"1.0\"?>
<BeanClassName>
  <BeanAttribute1 type="some-known-datatype">text-of-datatype</BeanAttribute1>
  <BeanAttribute2 type="some-known-datatype">text</BeanAttribute2>
...
  <BeanAttributeN type="some-known-datatype">text</BeanAttributeN>
</BeanClassName>
****************************************************************************/

import java.io.*;
import java.util.*;
import java.lang.reflect.*;

import org.xml.sax.*;
import org.xml.sax.helpers.*;

import squashxml.xml.datatype.*;

// Package (not public) class (i.e. only to be used by classes in this package)
class XMLMessageSAXService implements ContentHandler
{
	// Contains one of SAX's XMLReader instances.
	XMLReader mReader;

	// Default parser to user
	private String vendorParserClass = "org.apache.xerces.parsers.SAXParser";

	//======================================================================
	// Default constructor creates a reader and maps supported datatypes
	//======================================================================
	public XMLMessageSAXService()
	{
		try
		{
			// Create SAX Parser (XMLReader)
			//

			// Create Reader, and (create and) Register content handler
			mReader = XMLReaderFactory.createXMLReader(vendorParserClass);
			mReader.setContentHandler(this);
			// Register error handler

			// Map Supported Datatypes
			//
			datatypeNameMap = new HashMap(8);
			datatypeClassMap = new HashMap(8);

			mapDatatype(new DataTypeInt());
			mapDatatype(new DataTypeLong());
			mapDatatype(new DataTypeCharArray());
			mapDatatype(new DataTypeByteArray());
			mapDatatype(new DataTypeDate());
		}
		catch (Exception e)
		{
			e.printStackTrace();
			mReader = null;
		}
	}

	//======================================================================
	// XML DOCUMENT ENCODER/DECODER for XMLMessage
	//======================================================================
	public String encode(Object obj)
	{
		String reservedChars = "<>&'\"";
		String result;
		try
		{
			Class cls = obj.getClass();
			Vector v = ReflectionTool.getBeanMethods(obj, true);
			result = "<?xml version=\"1.0\"?>\n";
			result += "<" + cls.getName() + ">\n";
			for (Iterator i = v.iterator(); i.hasNext(); )
			{
				Method m = (Method)i.next();

				// Start the element which is the parameter

				String methName = m.getName().substring(3);
				String newItem = "\t <" + methName;


				String returnType = m.getReturnType().getName();
				DataTypeCodex dataTypeCodex = getDatatypeClassName(returnType);
				if (dataTypeCodex == null)
				{
					System.out.println("Encountered and Skipped UNKNOWN TYPE: \"" + returnType + "\"");
					continue;
				}
				newItem += " type=\"" + dataTypeCodex.getShortName() + "\"";

				// Get the value
				String encodedData = dataTypeCodex.encode(m.invoke(obj, null));  // Black Magic!
				if (encodedData == null)
					encodedData = "";
				newItem += ">";

				boolean bSpecialChars = false;
				for (int j = 0; j < encodedData.length(); j++)
				{
					char ch = encodedData.charAt(j);
					if (reservedChars.indexOf(ch) != -1)
					{
						bSpecialChars = true;
						break;
					}
				}
				if (bSpecialChars == false)
				{
					newItem += encodedData;
				}
				else
				{
					newItem += "<![CDATA[" + encodedData + "]]>";
				}

				newItem += "</" + methName +">\n";

				result += newItem;
			}

			result += "</" + cls.getName() + ">\n";

			return result;
		}
		catch (Throwable e)
		{
			e.printStackTrace();
			System.err.println(e);
			return null;
		}
	}

	public Object decode(byte bytes[])
	{
		try
		{
			ByteArrayInputStream inputStream = new ByteArrayInputStream(bytes);
			InputSource inputSource = new InputSource(inputStream);
			mReader.parse(inputSource);
		}
		catch (Exception e)
		{
			System.err.println(e);
		}
		finally
		{
			if (mBean == null)
			{
				System.out.println("XMLMessageReader read input source which resulted in NULL bean");
			}
		}
		return mBean;
	}

	//======================================================================
	//
	// Implemenation of the ContentHandler Interface required for Reader
	// THIS IS THE DECODER
	//
	//======================================================================

	private Object mBean;
	private Class mClass;
	private Method mMethods[];
	private String mCurrValue;
	private boolean bAcceptChars;
	private DataTypeCodex mDataTypeCodex;
	private Locator mLocator;


	public void setDocumentLocator(Locator locator)
	{
		mLocator = locator;
	}

	// Document Init/De-init
	public void startDocument()
			throws SAXException
	{
		mBean = null;
		mClass = null;
		mMethods = null;
		bAcceptChars = false;
	}

	public void endDocument()
			throws SAXException
	{
		// Could "push around" an fully instaniated object at this point.
	}


	// ELEMENT CALLBACKS
	//

	public void startElement(String namespaceURI, String localName, String qName, Attributes atts)
			throws SAXException
	{
		if (atts.getLength() == 0)
		{
			try
			{
				mBean = Class.forName(localName).newInstance();
				mClass = mBean.getClass();
				mMethods = mClass.getMethods();
			}
			catch (Exception e)
			{
				throw new SAXException(new SAXParseException("No Class Information for attribute " + localName + ". Exception = [" + e.toString() + "]", mLocator));
			}
			//System.out.println("Created instance of " + mBean.getClass().getName());
		}
		else
		{
			if (atts.getLength() < 1)
			{
				throw new SAXException(new SAXParseException("Required Attribute 'type' is missing", mLocator));
			}
			// Get the "type" attribute and create a DataTypeCodex for it
			if (atts.getLocalName(0).compareTo("type") != 0)
			{
				throw new SAXException(new SAXParseException("Required First Attribute 'type' is missing.", mLocator));
			}
			String dataType = atts.getValue(0);
			if (dataType == null)
			{
				throw new SAXException(new SAXParseException("Data Type Missing", mLocator));
			}
			mDataTypeCodex = getDatatypeShortName(dataType);
			if (mDataTypeCodex == null)
			{
				throw new SAXException(new SAXParseException("Unknown Data Type: " + dataType, mLocator));
			}

			// Get ready for the data
			bAcceptChars = true;
			mCurrValue = "";
		}
	}

	public void characters(char[] ch, int start, int length)
			throws SAXException
	{
		if (bAcceptChars)
		{
			mCurrValue += new String(ch, start, length);
		}
	}

	public void endElement(String namespaceURI, String localName, String qName)
			throws SAXException
	{
		bAcceptChars = false;

		String endClassName = mClass.getName();
		if (endClassName.compareTo(localName) == 0)
		{
			return;
		}
		// Decode the "value"
		String value = mCurrValue;
		if (value == null)
		{
			throw new SAXException(new SAXParseException("Data Value Missing", mLocator));
		}
		Object dataTypeInstance = mDataTypeCodex.decode(value);

		/*  NULL values are allowed
		if (dataTypeInstance == null)
		{
		System.out.println("Object of " + dataType + " was decoded to NULL");
		return; // NULL not allowed
		}
		*/

		try
		{
			// search for and call set() method
			Object args[] = new Object[1];
			boolean isInvolked = false;
			for (int i = 0; i < mMethods.length; i++)
			{
				String methodName = mMethods[i].getName();
				//System.out.println("Method " + methodName);
				if (methodName.compareTo("set" + localName) == 0)
				{
					//System.out.println("FOUND set Method " + methodName);
					Class params[] = mMethods[i].getParameterTypes();
					Class returnType = mMethods[i].getReturnType();
					if (params.length == 1 && params[0].getName() == mDataTypeCodex.getClassName() && returnType.getName().equals("void"))
					{
						//System.out.println("Method params MATCH, involking");
						args[0] = dataTypeInstance;
						mMethods[i].invoke(mBean, args);
						//System.out.println("Involked Method " + methodName);
						isInvolked = true;
						break;
					}
					//else
					//{
					//System.out.println("Method params don't match.  params.length = " + params.length + " params[0].getName = " + params[0].getName() + " datatype = " + mDataTypeCodex.getClassName() + " return = " + returnType.getName());
					//}
				}
			}
			if (!isInvolked)
	   throw new Exception();
		}
		catch (Exception e)
		{
			throw new SAXException(new SAXParseException("No method for: set" + localName + "(" + mDataTypeCodex.getClassName() + ")", mLocator));
		}

	}

	public void ignorableWhitespace(char[] ch, int start, int length)
	{
		// Don't display
	}

	public void skippedEntity(String name)
			throws SAXException
	{
		// No events
	}

	// Processing Instructions
	public void processingInstruction(String target, String data)
			throws SAXException
	{
		// No events
	}


	// Prefix Mapping
	public void startPrefixMapping(String prefix, String uri)
	{
		// No events
	}

	public void endPrefixMapping(String prefix)
	{
		// No events
	}

	//======================================================================
	//
	// Datatype Codex "handlers" are cross-referenced
	// by ShortName and ClassName
	//
	//======================================================================
	private HashMap datatypeNameMap;
	private HashMap datatypeClassMap;
	private void mapDatatype(DataTypeCodex interfacedC)
	{
		//          System.out.println("Mapping " + interfacedC.getShortName() + " and " + interfacedC.getClassName() + " to datatype converter class.");
		datatypeNameMap.put(interfacedC.getShortName(), interfacedC);
		datatypeClassMap.put(interfacedC.getClassName(), interfacedC);
	}
	public DataTypeCodex getDatatypeShortName(String shortName)
	{
		return (DataTypeCodex)datatypeNameMap.get(shortName);
	}
	public DataTypeCodex getDatatypeClassName(String className)
	{
		return (DataTypeCodex)datatypeClassMap.get(className);
	}
}


