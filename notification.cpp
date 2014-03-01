#include "std.h"
#include "sassert.h"
#include "warning.h"

namespace ecc
{
    notification::notification(int code, bool fatal, int line, const string& cat)
	:fatal_(fatal), category_(cat), code_(code)
    {
	push_token("#line",line);
    }

    notification::~notification()
    {

    }

    void notification::push_token(const string& tk, const string& val)
    {
	dict_[tk] = val;
    }

    void notification::push_token(const string& tk, int val)
    {
	stringstream ss;
	ss << val;
	dict_[tk] = ss.str();
    }

    bool notification::is_fatal() const
    {
	return fatal_;
    }

    void notification::sub_tokens_in_place(string& tmpl) const
    {
	size_t idx;
	while ( (idx=tmpl.find("#")) != string::npos )
	{
	    size_t idx_end = tmpl.find(" ",idx);
	    const string& token = tmpl.substr(idx,idx_end-idx);

	    if (dict_.count(token))
		tmpl.replace(idx,idx_end-idx,dict_.at(token));
	    else
	    {
		assert(false);
		tmpl.replace(idx,idx_end-idx,"??");
	    }
	}
    }

    string& notification::operator[](const string& key)
    {
	return dict_[key];
    }

    string notification::prep_string(void) const
    {
	string ws = get_template();

	// Substitute tokens
	sub_tokens_in_place(ws);

	stringstream str;
	str << category_ << setfill('0') << setw(3) << code_ << ": " 
	    << ws << setfill(' ');

	return str.str();

    }
    
    ostream& operator<<(ostream& str,const notification& n)
    {
	str << n.prep_string();
	return str;
    }
}
