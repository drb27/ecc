#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

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
    void ac_register_enumdef(enumdef* ped)
    {
	CurrentEnumDef = ped;
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
	/** @todo Check duplicate members */

	// Check duplicate values
	if ( CurrentEnumDef->has_duplicate_values() )
	{
	    ac_register_warning( 
		warning(warningcode::DuplicateValue, CurrentLine) );
	}

	// Check duplicate name
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
