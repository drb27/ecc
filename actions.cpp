#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <exception>
#include <iostream>
#include <sstream>

using namespace std;

#include "sassert.h"
#include "ctree.h"
#include "ast.h"
using namespace ecc::ast;

#include "warning.h"
#include "actions.h"
#include "check.h"
#include "globals.h"
#include "errors.h"

namespace ecc
{
    /**
     * Registers a new enumdef as the current enum def for parsing. 
     * Calls to ac_push_enumdef will act on this object. 
     *
     * @param ped the newly created object 
     */
    void ac_begin_enumdef()
    {
	CurrentEnumDef = new enumdef(CurrentAttributes);
    }

    /**
     * Pushes the current enumdef (set with ac_create_enumdef) onto the mater
     * list, with the given name. 
     *
     * At the point this call is made, the end definition is complete, with all
     * member/value pairs assigned. The name is assigned as part of this call.
     *
     * @param pName The name to use. Note that this string will be deleted during the call
     */
    void ac_push_enumdef(string* pName)
    {
	// Check duplicate values
	if ( CurrentEnumDef->has_duplicate_values() )
	{
	    warning w(warningcode::DuplicateValue, CurrentLine);
	    w["#enum"] = *pName;
	    ac_register_warning(w);
	}

	// Clear the attributes list ready for the next one
	CurrentAttributes.clear();

	// Check duplicate name
	if (!chk_enum_exists(*pName,MasterList))
	{
	    // Set name and namespace, push onto list
	    CurrentEnumDef->setname(pName);
	    CurrentEnumDef->setnamespace(CurrentNamespace);
	    MasterList.push_back( CurrentEnumDef );
	    
	    // Add to the namespace tree
	    CurrentNamespace->insert_member(CurrentEnumDef);

	}
	else
	{
	    throw duplicateenumexception(pName,CurrentLine);
	    delete pName;
	}

    }

    /**
     * Inserts a new member into the current enum def.
     * This function acts on the enumdef most recently passed to ac_register_enumdef. 
     * It deletes its string arguments during the call. 
     *
     * @param pMember the name of the member, i.e. its token string representation
     * @param val the integer value of the member (pass AST_DEFAULT_ENUM_VALUE for none)
     * @param longstr longer text associated with the member (can be empty string)
     */
    void ac_insert_member(string* pMember, int val, string* pLongStr)
    {
	// Ensure strings get deleted when this block goes out of scope
	unique_ptr<string> mpMember(pMember), mpLongStr(pLongStr);

	// If this has a longstring, and the enumdef as the flags attribute, raise error
	if ( CurrentEnumDef->is_flags() &&  pLongStr->length() )
	{
	    throw longstringonflagexception(pMember,CurrentLine);
	}
	else
	{
	    // If we got here, we're good. Do the insert.
	    CurrentEnumDef->insert_value(pair_t(*pMember,val),*pLongStr);
	}
    }

    /** 
     * Applies the given attribute to the attributes list. During the
     * parsing of the current enumdef, the parser calls 
     * ac_register_enumdef(), which applies the attributes in the 
     * attribute list.
     *
     * @param attr the attribute to apply
     */
    void ac_register_attribute( ast::enumattr attr)
    {
	CurrentAttributes.push_back(attr);
    }

    /**
     * Sets the namespace that following typedefs will be generated within.
     *
     * @param valid c++ namespace name. May be nested, e.g. name::subname::package
     */
    void ac_set_namespace(string* pNamespace)
    {
	// Ensure the namespace exists in the tree
	unique_ptr<string> mpNamespace(pNamespace);
	NsTree.create_path(*mpNamespace);

	// Point to it
	CurrentNamespace = &NsTree.lookup(*mpNamespace);
    }
 /** 
     * Allows the scanner/parser to register a warning. 
     *
     * The reference is copied onto a list as part of this call. 
     * The caller can disband the warning object after the call has
     * returned. 
     *
     * @param wn A reference to a temporary warning object. 
     */
    void ac_register_warning(const warning& wn)
    {
	Warnings.push_back(wn);
	std::cerr << wn << std::endl;
    }
}
