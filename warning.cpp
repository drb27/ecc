#include <iostream>
using namespace std;

#include "warning.h"

namespace ecc
{
    warning::warning(code cde,const string& file, int line)
	:code_(cde), file_(file), line_(line)
    {

    }

    warning::~warning()
    {

    }

    ostream& operator<<(ostream& str,const warning& w)
    {
	str << "WRN" << w.code_ << ": " << w.file_ << ":" << w.line_;
	return str;
    }
}
