
#include <vector>
#include <string>
#include <map>
#include "ast.h"

namespace ecc
{
namespace ast
{

    enumdef::enumdef(const std::string* pName) : name(*pName)
    {
	delete pName;
    }

    enumdef::~enumdef()
    {

    }

    void enumdef::setvalues(const values_t& vs)
    {
	// Just do a copy
	values = vs;
    }

    const std::string& enumdef::get_name(void)
    {
	return name;
    }

}
}
