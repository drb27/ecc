#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <ctime>
#include <exception>
#include <functional>

using std::function;
using std::exception;
using std::string;
using std::stringstream;
using std::endl;
using std::ostream;
using std::cout;
using std::vector;
using std::map;

#include "sassert.h"
#include "ctree.h"
#include "version.h"
#include "ast.h"
using namespace ecc::ast;

#include "warning.h"
#include "indent.h"
#include "generator.h"
#include "globals.h"

namespace ecc
{
    generator::generator()
    {

    }

    generator::~generator()
    {
	
    }
    
    void generator::translate(const ast::elist_t& items, 
			      const string& fHeader, 
			      const string& fCode,
			      std::ostream& ostr_c, 
			      std::ostream& ostr_h)
    {
	ind.reset();
	translate_header(items,fHeader,ostr_h);

	ind.reset();
	translate_code(items,fHeader,ostr_c);
    }

    void generator::translate_header(const elist_t& items, 
				     const string& fHeader,
				     ostream& ostr_h)
    {
	// Output comment block at the head of the file
	ostr_h << tl_head(outfile_t::headerFile,fHeader);

	// Include guard
	{
	    string grd = guard(fHeader);
	    ostr_h << endl << "#ifndef " << grd;
	    ostr_h << endl << "#define " << grd << endl;
	}

	ostr_h << namespace_structures(NsTree);

	// Terminate include guard
	ostr_h << endl << "#endif" << endl;
    }
    
    void generator::translate_code(const elist_t& items, 
				   const string& fHeader,
				   ostream& ostr_c)
    {
	ostr_c << tl_head(outfile_t::codeFile,fHeader);
	ostr_c << endl;

	ostr_c << tl_codebody(items);
    }

    string generator::leaf(const string& fPath)
    {
    	string headerLeaf;
    	int pos = fPath.rfind('/');
    	if ( pos == string::npos )
    	{
    	    // File is already a leaf
    	    headerLeaf = fPath;
    	}
    	else
    	{
    	    // File is not leaf, use everything after the last '/'
    	    headerLeaf = fPath.substr(pos+1, fPath.length()-pos);
    	}

	return headerLeaf;
    }

    string generator::guard(const string& fPath, const string& prefix)
    {
    	string guard = prefix + leaf(fPath) + "_";
    	for ( auto i = guard.begin(); i!=guard.end(); i++ )
    	{
    	    if ( ( (*i) == '.') || ( (*i) == '-') ) 
    		(*i) = '_';
    	    else
    		(*i) = toupper(*i);
    	}

	return guard;
    }

    string generator::currenttime()
    {
	time_t now = time(0);
	return asctime(localtime(&now));
    }
}
