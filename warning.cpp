#include "std.h"
#include "sassert.h"
#include "warning.h"

namespace ecc
{
    warning::warning(warningcode cde, int line)
	:code_(cde)
    {
	push_token("#line",line);
    }

    warning::~warning()
    {

    }

    void warning::push_token(const string& tk, const string& val)
    {
	dict_[tk] = val;
    }

    void warning::push_token(const string& tk, int val)
    {
	stringstream ss;
	ss << val;
	dict_[tk] = ss.str();
    }

    string& warning::operator[](const string& key)
    {
	return dict_[key];
    }
    
    const string warning::prep_string() const
    {
	// Fetch copy of longstring for warning code
	string ws = getstr_warningcode(code_,true);
	
	// Substitute tags
	size_t idx;
	while ( (idx=ws.find("#")) != string::npos )
	{
	    size_t idx_end = ws.find(" ",idx);
	    const string& token = ws.substr(idx,idx_end-idx);

	    if (dict_.count(token))
		ws.replace(idx,idx_end-idx,dict_.at(token));
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
	str << "WRN" << setfill('0') << setw(3) <<  w.code_ << ": " 
	    << w.prep_string() << setfill(' ');
	return str;
    }
}
