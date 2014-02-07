#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include "ast.h"
#include "generator.h"

using std::stringstream;
using std::endl;

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

	ostr << tl_strings(items);

	for (auto pEnum : items )
	{
	    ostr << tl_functions(*pEnum);
	}

    }

    const std::string defgen::tl_header(void) const
    {
	return "/** Header */\n#include <string>\n";
    }
    
    const std::string defgen::tl_typedef(const ast::enumdef& ed) const
    {
	stringstream ss;
	ss << endl << "/** typedef " << ed.get_name() << " */" << endl;
	ss << "typedef enum {";

	std::string sep = "";

	for ( auto vp : ed.getvalues() )
	{
	    ss << sep << endl << "    " << vp.first;
	    if (vp.second!=AST_DEFAULT_ENUM_VALUE)
		ss << "=" << vp.second;
	    sep = ",";
	}

	ss << endl << "} " << ed.get_name() << ";" << endl;

	return ss.str();
    }

    const std::string defgen::tl_strings(const ast::elist_t& items) const
    {
	stringstream ss;

	ss << endl << "namespace {" << endl;
	ss << "    static const std::string notfound=\"\";" << endl;
	
	for ( auto pItem : items )
	{
	    for ( auto vp : pItem->getvalues() )
	    {
		ss << "    static const std::string " << pItem->get_name() << "_"
		   << vp.first << " = " << "\"" << vp.first << "\";" << endl;
	    }
	}

	ss << "}" << endl;

	return ss.str();
    }

    const std::string defgen::tl_functions(const ast::enumdef& ed) const
    {
	stringstream ss;

	ss << endl << "const std::string& getstr_" << ed.get_name() << "("
	   << ed.get_name() << " v) {" << endl;
	
	ss << "    switch (v) {" << endl;
	
	for ( auto vp : ed.getvalues() )
	{
	    ss << "    case " << vp.first << ":" << endl;
	    ss << "        return " << ed.get_name() << "_" << vp.first << ";" << endl; 
	}

	ss << "    default: " << endl;
	ss << "        return notfound;" << endl;

	ss << "    }" << endl;

	ss << "}" << endl;

	return ss.str();
    }
}
