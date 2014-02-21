#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;

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

    void enumdef::insert_value(const pair_t& pair)
    {
	members.push_back(pair.first);
	values.insert(pair);
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

    const vector<string>& enumdef::getmembers() const
    {
	return members;
    }

    const std::string& enumdef::get_name(void) const
    {
	return name;
    }

}
}
