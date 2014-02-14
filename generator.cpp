#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include "version.h"
#include "ast.h"
#include "generator.h"

using std::string;
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

    void defgen::translate(const ast::elist_t& items, 
	                   const string& fHeader, 
			   const string& fCode,
			   std::ostream& ostr_c, 
			   std::ostream& ostr_h)
    {
	ostr_h << tl_header();
	ostr_c << tl_header();

	/** c file needs to include <string>, and our header */
	ostr_c << "#include <string>" << endl;

	string headerLeaf;
	int pos = fHeader.rfind('/');
	if ( pos == string::npos )
	{
	    // File is already a leaf
	    headerLeaf = fHeader;
	}
	else
	{
	    // File is not leaf, use everything after the last '/'
	    headerLeaf = fHeader.substr(pos+1, fHeader.length()-pos);
	}
	
	ostr_c << "#include \"" << headerLeaf << "\"" << std::endl;
	ostr_c << endl <<  "using std::string;" << endl;

	string guard = "_HG_" + headerLeaf + "_";
	for ( auto i = guard.begin(); i!=guard.end(); i++ )
	{
	    if ( (*i) == '.') 
		(*i) = '_';
	    else
		(*i) = toupper(*i);
	}

	ostr_h << "#ifndef " << guard << std::endl;
	ostr_h << "#define " << guard << std::endl;

	for ( auto pEnum : items )
	{
	    ostr_h << tl_typedef(*pEnum);
	}

	ostr_c << tl_strings(items);

	for (auto pEnum : items )
	{
	    ostr_c << tl_functions(*pEnum);
	}

	ostr_h << std::endl << "#endif // " << guard << std::endl;

    }

    const string defgen::tl_header(void) const
    {
	stringstream ss;
	ss <<"/** Generated by " << ecc::version << "*/" << endl;
	return ss.str();
    }
    
    const string defgen::tl_typedef(const ast::enumdef& ed) const
    {
	stringstream ss;
	ss << endl << "/** typedef " << ed.get_name() << " */" << endl;
	ss << "typedef enum {";

	string sep = "";

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

    const string defgen::tl_strings(const ast::elist_t& items) const
    {
	stringstream ss;

	ss << endl << "namespace {" << endl;
	ss << "    static const string notfound=\"\";" << endl;
	
	for ( auto pItem : items )
	{
	    for ( auto vp : pItem->getvalues() )
	    {
		ss << "    static const string " << pItem->get_name() << "_"
		   << vp.first << " = " << "\"" << vp.first << "\";" << endl;
	    }
	}

	ss << "}" << endl;

	return ss.str();
    }

    const string defgen::tl_functions(const ast::enumdef& ed) const
    {
	stringstream ss;

	ss << endl << "const string& getstr_" << ed.get_name() << "("
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
