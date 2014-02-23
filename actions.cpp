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
    void ac_register_enumdef(enumdef* ped)
    {
	CurrentEnumDef = ped;
    }

    /**
     * Pushes the current enumdef (set with ac_create_enumdef) onto the mater
     * list, with the given name. 
     * @param pName The name to use. Note that this string will be deleted during the call
     */
    void ac_push_enumdef(string* pName)
    {
	if (!chk_enum_exists(*pName,MasterList))
	{
	    CurrentEnumDef->setname(pName);
	    MasterList.push_back( CurrentEnumDef );
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
}
