#include <iostream>
using namespace std;

#include "warning.h"

namespace ecc
{
    warning::warning(code cde, int line)
	:code_(cde), line_(line)
    {

    }

    warning::~warning()
    {

    }

    ostream& operator<<(ostream& str,const warning& w)
    {
	str << "WRN" << w.code_ << ": at line" << w.line_;
	return str;
    }
}
