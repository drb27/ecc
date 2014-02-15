#include <string>
#include <vector>
#include <map>

using namespace std;

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
}
