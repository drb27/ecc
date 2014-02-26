#ifndef WARNING_H_
#define WARNING_H_

#include "warn.h"

namespace ecc
{
    class warning
    {
    public:

	warning(warningcode cde,int line);
	virtual ~warning();

	void push_token(const string& tk, const string& val);
	void push_token(const string& tk, int val);

    protected:
	const warningcode code_;
	const int line_;
	map<string,string> dict_;

	const string prep_string(void) const;

	friend ostream& operator<<(ostream&, const warning&);
    };
    
    ostream& operator<<(ostream&, const warning&);
}
#endif
