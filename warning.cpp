#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

#include "sassert.h"
#include "warning.h"

namespace ecc
{
    warning::warning(warningcode cde, int line)
	:code_(cde), line_(line)
    {

    }

    warning::~warning()
    {

    }
    
    const string warning::prep_string( const map<string,string>& dict ) const
    {
	// Fetch copy of longstring for warning code
	string ws = getstr_warningcode(code_,true);
	
	// Substitute tags
	size_t idx;
	while ( (idx=ws.find("#")) != string::npos )
	{
	    size_t idx_end = ws.find(" ",idx);
	    const string& token = ws.substr(idx,idx_end-idx);

	    if (dict.count(token))
		ws.replace(idx,idx_end-idx,dict.at(token));
	    else
	    {
		assert(false);
		ws.replace(idx,idx_end-idx,"??");
	    }
	}

	return ws;
    }
    
    ostream& operator<<(ostream& str,const warning& w)
    {
	map<string,string> dict;
	stringstream ss;
	ss << w.line_;
	dict["#line"] = string(ss.str());
	str << "WRN" << setfill('0') << setw(3) <<  w.code_ << ": " 
	    << w.prep_string( dict ) << setfill(' ');
	return str;
    }
}
