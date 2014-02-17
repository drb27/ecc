#include <string>
using namespace std;

#include "indent.h"

namespace ecc
{
    indent::indent(int width) : indentWidth(width), indentLevel(0), indentString("")
    {
    }

    indent::~indent()
    {
    }

    void indent::reset(void)
    {
	indentLevel=0;
	update_cache();
    }

    indent& indent::operator++(int)
    {
	indentLevel++;
	update_cache();
	return *this;
    }

    indent& indent::operator--(int)
    {
	indentLevel--;
	update_cache();
	return *this;
    }

    const string& indent::operator() () const
    {
	return indentString;
    }

    void indent::update_cache(void)
    {
	indentString = string(indentLevel*indentWidth,' ');
    }
}
