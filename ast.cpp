#include <vector>
#include <string>
#include <map>
#include <set>
#include "ast.h"

using std::set;

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

    const std::string& enumdef::get_name(void) const
    {
	return name;
    }
  
    bool enumdef::has_duplicate_values(void) const
    {

	set<int> processed;
	for ( auto p : values )
	{
	    if (p.second!=AST_DEFAULT_ENUM_VALUE)
	    {
		if ( processed.find(p.second)!=processed.end() )
		{
		    // Duplicate detected - abort
		    return true;
		}
		else
		    processed.insert(p.second);
	    }
	}

	return false;
    }
}
}
