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
#ifndef DOI_h
#define DOI_h 1

class DOI 
{

  public:

      // Constructor
      DOI();

      // Copy Constructor
      DOI(DOI* right);

      // Destructor
      ~DOI();

      // status enumeration and check method
      enum DOI_status
      {
        DOI_NEEDS_MASTER_ASSIGNED,
        DOI_IS_EXTERNALLY_GENERATED,
        DOI_IS_INSTANCE_DOI
      };
      int get_Status();

      // Get and Set Operations for Class Attributes
  
      /** DOI id string */   
      const char* get_DOI_idStr () const;
      void set_DOI_idStr (char* pDOI_idStr);

// TODO: Do we also need a DOIApplicationProfile? It's mentioned in the handbook
//       (http://www.doi.org/handbook_2000/metadata.html), but is not found in the example ...

      /** Structural Type */     
// TODO: This should be an enumeration with the following items:
    // TangibleFixation (Physical)
    // Intangible Fixation (Digital)
    // Performance (SpatioTemporal)
    // Abstraction (Abstract)
      const char* get_StructuralType () const;
      void set_StructuralType (char* pStructuralType);

      /** Mode */     
// TODO: These should be flags
    // Visual
    // Audio
    // Audiovisual
    // Abstract 
      const char* get_Mode () const;
      void set_Mode (char* pMode);

// TODO: This should support an array
      /** Identifier Type */     
      const char* get_IdentifierType () const;
      void set_IdentifierType (char* pIdentifierType);

// TODO: This should support an array
      /** Identifier Value */     
      const char* get_IdentifierValue () const;
      void set_IdentifierValue (char* pIdentifierValue);

// TODO: This should support an array
      /** Title */     
      const char* get_Title () const;
      void set_Title (char* pTitle);

// TODO: This should support an array
      /** Primary Agent (Artist) */     
      const char* get_PrimaryAgent () const;
      void set_PrimaryAgent (char* pPrimaryAgent);

// TODO: This should support an array (of enumerated items from a namespace, e.g. Author, Publisher, Editor).
      /** Primary Agent Role */     
      const char* get_PrimaryAgentRole () const;
      void set_PrimaryAgentRole (char* pPrimaryAgentRole);

      /** raw XML string */     
      const char* get_XML_str () const;
      void set_XML_str (char* pXMLstr);

  protected:
  
  private:

      // Data Members for Class Attributes
      char* m_DOI_idStr;
      char* m_StructuralType;
      char* m_Mode;
      char* m_IdentifierType;
      char* m_IdentifierValue;
      char* m_Title;
      char* m_PrimaryAgent;
      char* m_PrimaryAgentRole;

      char* m_XML_str;

};

// Class DOI 

#endif
