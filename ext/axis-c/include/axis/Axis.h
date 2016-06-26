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
 *
 *
 *
 */
#ifndef AXIS_INCLUDED
#define AXIS_INCLUDED


/**
 * @class Axis
 *
 * Contains methods to initialize and terminate the Axis runtime. Creating a stub also initializes
 * the Axis runtime and deleting the stub terminates it. So simple applications that only ever
 * use one stub at a time do not need to call these methods. More complicated applications that 
 * initialize multiple stubs, use them and delete them later, should initialize Axis at the start
 * of their application using Axis::initialize and terminate Axis at the very end of their 
 * application with Axis::terminate. Applications that use Axis in multiple threads should also 
 * call Axis:: initialize and terminate.
 */
/**
	 * Initializes the Axis runtime.
	 * @param bIsServer should be set to false for client applications.
	 */
AXISC_STORAGE_CLASS_INFO void axiscInitializeAxis(AxiscBool bIsServer);

/**
	 * Terminates the Axis runtime.
	 */
AXISC_STORAGE_CLASS_INFO void axiscTerminate();


#endif // AXIS_INCLUDED
