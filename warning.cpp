#include "std.h"
#include "sassert.h"
#include "warning.h"

namespace 
{
    const string CategoryPrefix="WRN";
}

namespace ecc
{
    warning::warning(warningcode cde, int line)
	:notification((int)cde,false,line,CategoryPrefix)
    {
    }

    warning::~warning()
    {

    }

    string warning::get_template() const
    {
	// Fetch copy of longstring for warning code
	return getstr_warningcode(static_cast<warningcode>(code_),true);
    }
    
}
