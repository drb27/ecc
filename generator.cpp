#include <iostream>
#include <map>
#include <vector>
#include "ast.h"
#include "generator.h"

namespace ecc
{
    generator::generator()
    {

    }

    generator::~generator()
    {

    }

    void defgen::translate(const ast::elist_t& items, std::ostream& ostr)
    {
	ostr << tl_header();

	for ( auto pEnum : items )
	{
	    ostr << tl_typedef(*pEnum);
	}
    }

    const std::string defgen::tl_header(void) const
    {
	return "/** Header */\n#include <string>\n";
    }
    
    const std::string defgen::tl_typedef(const ast::enumdef& ed) const
    {
	return "/** typedef " + ed.get_name() + " */\n";
    }
}
