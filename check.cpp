#include <string>
#include <vector>
#include <map>

using namespace std;

#include "ast.h"
using namespace ecc::ast;

#include "check.h"



namespace ecc
{
    /**
     * Checks to see if the enum name has already been defined.
     *
     * @param name the name of the enum type
     * @param list the current master list of enum definitions
     *
     * @returns true if the name already exists in the global list
     */ 
    bool chk_enum_exists(const std::string& name, const elist_t& list)
    {
	for (auto i : list)
	{
	    if ( i->get_name() == name )
		return true;
	}
	
	return false;
    }
}
