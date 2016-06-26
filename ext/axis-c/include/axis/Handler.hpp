/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
 
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(__HANDLER_OF_AXIS_INCLUDED__)
#define __HANDLER_OF_AXIS_INCLUDED__

#include "BasicHandler.hpp"

/**
 * @class Handler
 * @brief interface for handlers.
 *
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 */

/*
 * Revision 1.1  2004/06/14 roshan
 * Added doxygen comments to help autobuild API docs
 * Added the implementations of getOption(const string& sArg) and 
 *  setOptionList(const map<string, string>* OptionList), because these methods
 *  are not needed to be implemented by the users. These are generic methods.
 */

AXIS_CPP_NAMESPACE_START

class Handler : public HandlerBase
{
public:
	/**
	  * Constructor.
	  */
    Handler(){};

	/**
	  * Destructor.
	  */
    virtual ~Handler(){};

	/**
	  * Returns the value of the given option.
	  *
	  * @param sArg The option name, i.e key
	  * @return The option value.
	  */
    const string& getOption(const string& sArg)
	{
		m_sEmpty = "";

		map<string, string>::const_iterator it = m_pOption->find(sArg);
		if (it != m_pOption->end())
		{
			return (*it).second;
		}
		return m_sEmpty;	
	}

	/**
	  * This method is automatically called by the Axis Engine when it loads a
	  * Handler. The purpose of this method is described below:
	  * For each Handler we could configure various parameters/options in the
	  * Server.wsdd or Client.wsdd. If the engine finds any such options then
	  * the engine will automaticaly call this method of each handler and will
	  * set those options to each Handler by calling this method of each 
	  * Handler which those configuration options belong to. Normaly a Handler
	  * writer doesn't need to interact/deal with this method.
	  *
	  * @param OptionList The map which contains the options to be set.
	  */
    void setOptionList(const map<string, string>* OptionList) {m_pOption = OptionList;};

	/**
	  * Gets and returns the type of the handler. The return value here is
	  * always NORMAL_HANDLER.
	  *
	  *	@return returns the type of the handler. The return value here is
	  * always NORMAL_HANDLER.
	  */
    int AXISCALL getType(){return NORMAL_HANDLER;};

protected:
	/**
	  * Used to store the options which are configured in the WSDD.
	  */
	const map<string, string>* m_pOption;

	/**
	  * Represents an empty string.
	  */
	string m_sEmpty;
};

AXIS_CPP_NAMESPACE_END

#endif 

