
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

    enumdef::enumdef() : name("")
    {

    }

    enumdef::~enumdef()
    {

    }

    void enumdef::insert_value(const pair_t& pair)
    {
	values.insert(pair);
    }

    void enumdef::setname(std::string* pName)
    {
	name = *pName;
	delete pName;
    }

    const values_t& enumdef::getvalues()
    {
	return values;
    }

    const std::string& enumdef::get_name(void) const
    {
	return name;
    }

}
}
