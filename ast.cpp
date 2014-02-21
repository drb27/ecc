#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using std::string;

#include "sassert.h"
#include "ast.h"

namespace ecc
{
namespace ast
{

    enumdef::enumdef() : name("")
    {
    }

    enumdef::enumdef(const std::vector<ecc::ast::enumattr>& attr) : name("")
    {
      for (auto a : attr)
      {
	if ( a == ecc::ast::enumattr::flags)
	  flags=true;
      }
    }

    enumdef::~enumdef()
    {

    }

    void enumdef::insert_value(const pair_t& pair, const std::string& longstr)
    {
	values.insert(pair);
        longstrings[pair.first] =  longstr;
    }

    void enumdef::setname(std::string* pName)
    {
	name = *pName;
	delete pName;
    }

    const values_t& enumdef::getvalues() const
    {
	return values;
    }

    const string& enumdef::getlstring(const string& member) const
    {
	assert(longstrings.find(member)!=longstrings.end());
	return longstrings.at(member);
    }

    const std::string& enumdef::get_name(void) const
    {
	return name;
    }

}
}
