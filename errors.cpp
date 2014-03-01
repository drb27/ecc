#include "std.h"
#include "sassert.h"
#include "errors.h"

namespace 
{
    const string CategoryPrefix="ERR";
}

namespace ecc
{
    error::error(errorcode cde, int line)
	:notification((int)cde,true,line,CategoryPrefix)
    {
    }

    error::~error()
    {

    }

    string error::get_template() const
    {
	// Fetch copy of longstring for warning code
	return getstr_errorcode(static_cast<errorcode>(code_),true);
    }
    
}
