#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

#include "version.h"
#include "ast.h"
using namespace ecc::ast;

#include "indent.h"
#include "generator.h"
#include "defgen.h"

namespace ecc
{
    string defgen::tl_head(outfile_t fileType, const string& fHeader)
    {
    	stringstream ss;

    	ss << "/**" << endl;
    	ss << " * Generated by:         " << ecc::version << endl;
    	ss << " * Generation timestamp: " << currenttime();
    	ss << " */" << endl;
	
	if (fileType==outfile_t::codeFile)
	{
	    ss << "#include <string>" << endl;
	    ss << "#include <sstream>" << endl;
	    ss << "using namespace std;" << endl << endl;
	    ss << "#include \"" << leaf(fHeader) << "\"" << endl;
	}

    	return ss.str();
    }

    string defgen::tl_typedef(const enumdef& ed)
    {
    	stringstream ss;
    	ss << endl << "typedef enum {";
	ind++;

    	string sep = "";

    	for ( auto vp : ed.getvalues() )
    	{
    	    ss << sep << endl << ind() << vp.first;
    	    if (vp.second!=AST_DEFAULT_ENUM_VALUE)
    		ss << "=" << vp.second;
    	    sep = ",";
    	}

    	ss << endl << "} " << ed.get_name() << ";" << endl;
	ind--;
    	return ss.str();
    }

    string defgen::tl_prototype(const enumdef& item, outfile_t fileType)
    {
    	stringstream ss;
	string ext,trm,name;
	
	if (fileType==outfile_t::headerFile)
	{
	    ext = "extern ";
	    trm = ";";
	}

	name = item.get_name();

	if (item.is_flags())
	    ss << ext << "string getstr_" << name << "("
	       << name << " v)" << trm << endl;
	else
	    ss << ext << "const string& getstr_" << name << "("
	       << name << " v)" << trm << endl;
	
    	return ss.str();
    }

    string defgen::tl_codebody(const elist_t& items)
    {
	stringstream ss;

	// Constants first
	ss << tl_constants(items);

	// Then access functions
	for ( auto i : items )
	{
	    if (i->is_flags())
		ss << tl_function_flags_attr(*i);
	    else
		ss << tl_function_regular(*i);
	}

	return ss.str();
    }

    string defgen::tl_constants(const elist_t& items)
    {
	stringstream ss;
	ss << ind() << "namespace {" << endl;
	ind++;
	ss << ind() << "static const string notfound=\"\";" << endl;
	
    	for ( auto pItem : items )
    	{
    	    for ( auto vp : pItem->getvalues() )
    	    {
    		ss << ind() << "static const string " << pItem->get_name() << "_"
    		   << vp.first << " = " << "\"" << vp.first << "\";" << endl;
    	    }
    	}

	ind--;
    	ss << ind() << "}" << endl;
	return ss.str();
    }

    string defgen::tl_function_regular(const enumdef& item)
    {
	stringstream ss;

	// Generate code prototype
	ss << endl << ind() << tl_prototype(item,outfile_t::codeFile);

	// Body
	ss << ind() << "{" << endl;
	ind++;

    	ss << ind() << "switch (v) {" << endl;
	ind++;
	
    	for ( auto vp : item.getvalues() )
    	{
    	    ss << ind() << "case " << vp.first << ":" << endl;
	    ind++;
    	    ss << ind() << "return " << item.get_name() << "_" << vp.first << ";" << endl; 
	    ind--;
    	}

    	ss << ind() << "default: " << endl;
	ind++;
    	ss << ind() << "return notfound;" << endl;
	ind--;

	ind--;
    	ss << ind() << "}" << endl;

	ind--;
    	ss << ind() << "}" << endl;

	return ss.str();
    }

    string defgen::tl_function_flags_attr(const enumdef& item)
    {
	stringstream ss;

	// Generate code prototype
	ss << endl << ind() << tl_prototype(item,outfile_t::codeFile);
	ss << ind() << "{" << endl;
	ind++;
	
    	ss << ind() << "stringstream ss;" << endl;
    	ss << ind() << "bool sep=false;" << endl;
	
    	for ( auto vp : item.getvalues() )
    	{
    	    ss << ind() << "if ( v & " << vp.first << ") { if (sep) ss << \",\"; "
    	       << " ss << " << item.get_name() << "_" << vp.first 
    	       << "; sep=true; }" << endl;
    	}
    	ss << ind() << "return ss.str();" << endl;
    	
	ind--;
	ss << "}" << endl;

	return ss.str();
    }

}   
