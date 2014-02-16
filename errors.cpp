#include <exception>
#include <string>
#include <map>
#include <vector>
using namespace std;

#include "ast.h"
using namespace ecc::ast;

#include "errors.h"

namespace ecc
{
    /**
     * Default constructor - does nothing
     */
    exception::exception()
    {

    }

    /**
     * Returns a generic string. Subclasses should provide their own implementation 
     */
    const char* exception::what(void) const noexcept
    {
	return "Unspecified ecc error";
    }

    /**
     * Default constructor - does nothing 
     */
    parseexception::parseexception(const parse_error_t en) : errCode(en)
    {

    }
    
    /**
     * Returns a generic string. Subclasses should provide their own implementation. 
     */
    const char* parseexception::what(void) const noexcept
    {
	return "Unspecified parse error";
    }


   /**
     * Constructs the error from the enum def and the line number. 
     */
    duplicateenumexception::duplicateenumexception(const string* pName, int line)
	: parseexception(EnDuplicateEnum), 
	  customErrMsg("Duplicate enum definition " + *pName + " found on line xx")
    {

    }
    
    /**
     * Returns a generic string. Subclasses should provide their own implementation 
     */
    const char* duplicateenumexception::what(void) const noexcept
    {
	return customErrMsg.c_str();
    }
}

