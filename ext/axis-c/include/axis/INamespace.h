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
/**
 * @file INamespace.h
 *
 *
 */
/**
 *   @class INamespace
 *   @brief interface for the Namespace.
 *
 *
 */
#ifndef INAMESPACE_INCLUDED
#define INAMESPACE_INCLUDED


/**
     * Gets the prefix of this Namespace.
     * 
     * @return prefix of this namespace.
     */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetPrefixINamespace(AXISCHANDLE iNamespace);

/**
    * Gets the namespace uri of this Namespace.
    * 
    * @return namespace uri of this Namespace
    */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetURIINamespace(AXISCHANDLE iNamespace);

/**
      * Sets the namespace uri of this Namespace.
      *
      * @param uri The namespace uri to set in.
      * @return AXIS_SUCCESS if successful AXIS_FAIL otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
      * 
      */
AXISC_STORAGE_CLASS_INFO int axiscSetURIINamespace(AXISCHANDLE iNamespace, const AxiscChar * achURI);

/**
     * Sets the prefix of this Namespace.
     *
     * @param prefix The prefix to set in.
     * @return AXIS_SUCCESS if successful AXIS_FAIL otherwise. NOTE: Passing NULL will result in a AXIS_FAIL
     */
AXISC_STORAGE_CLASS_INFO int axiscSetPrefixINamespace(AXISCHANDLE iNamespace, const AxiscChar * achPrefix);
AXISC_STORAGE_CLASS_INFO void axiscDestroyINamespace(AXISCHANDLE iNamespace);


#endif // INAMESPACE_INCLUDED
