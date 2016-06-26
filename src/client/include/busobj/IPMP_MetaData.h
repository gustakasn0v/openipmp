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
#ifndef IPMP_MetaData_h
#define IPMP_MetaData_h 1

#include "busobj/AuxData.h"

// forward declaration to avoid circular reference
#include "busobj/IPMP_ContentIdentity.h"
//class IPMP_ContentIdentity : public ContentIdentity;
class IPMP_ContentIdentity;

class IPMP_MetaData 
{

  public:
  
      // Constructor
      IPMP_MetaData();

      // Copy Constructor
      IPMP_MetaData(IPMP_MetaData* right);

      // Destructor
      ~IPMP_MetaData();

      // initializers
      // Note: Additional content id schemes can be supported by overloading
      //       the init() function. Might want to consider
      //       implementing abstract interfaces to deal with this in a more
      //       elegant fashion.
      bool init(IPMP_ContentIdentity* pIPMP_ContentId, AuxData* pAuxData);
  
      // Get and Set Operations for Class Attributes

      // rights resolution host
      const char* get_RightsHost () const;
      void set_RightsHost (char* value);

      // plug in dll name
      const char* get_PlugInName () const;
      void set_PlugInName (char* value);

      // content id
      const char* get_ContentId () const;
      void set_ContentId (char* value);

      // content id length
      const int get_ContentIdLength () const;
      void set_ContentIdLength (int value);

      // content id type
      const int get_ContentIdType () const;
      void set_ContentIdType (int value);

      // content id flag
      const int get_ContentIdFlag () const;
      void set_ContentIdFlag (int value);

      // content type (?)
      const int get_ContentType () const;
      void set_ContentType (int value);

      // content type flag (?)
      const int get_ContentTypeFlag () const;
      void set_ContentTypeFlag (int value);

      // compatibility (?)
      const int get_Compatibility () const;
      void set_Compatibility (int value);

      // protected content flag
      const int get_ProtectedContentFlag () const;
      void set_ProtectedContentFlag (int value);

      // tool id
      const char* get_ToolId () const;
      void set_ToolId (char* value);

      // language code
      const char* get_LanguageCode () const;
      void set_LanguageCode (char* value);

  private:

      // Data Members for Class Attributes
      char*		m_RightsHost;      
      char*		m_PlugInName;
      char*		m_ContentId;
      int		m_ContentIdLength;
      int		m_ContentIdType;
      int		m_ContentIdFlag;
      int		m_ContentType;
      int		m_ContentTypeFlag;
      int		m_Compatibility;
      int		m_ProtectedContentFlag;
      char*		m_ToolId;
      char*		m_LanguageCode;

};

#endif
