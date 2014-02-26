#include <iostream>
using namespace std;

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

    ostream& operator<<(ostream& str,const warning& w)
    {
	str << getstr_warningcode(w.code_,true);
	return str;
    }
}
