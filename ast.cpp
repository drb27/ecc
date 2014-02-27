#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <set>
#include <exception>

using std::vector;
using std::string;
using std::set;
using std::exception;

#include "sassert.h"
#include "ctree.h"
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
	    members.push_back(pair.first);
	    values.insert(pair);
	    longstrings[pair.first] =  longstr;
	}

	void enumdef::setname(std::string* pName)
	{
	    name = *pName;
	    delete pName;
	}

	void enumdef::setnamespace(const ctree<enumdef>* pn)
	{
	    pNamespace = pn;
	}
	
	const ctree<enumdef>* enumdef::nspace(void) const
	{
	    return pNamespace;
	}

	const values_t& enumdef::getvalues() const
	{
	    return values;
	}

	const vector<string>& enumdef::getmembers() const
	{
	    return members;
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
