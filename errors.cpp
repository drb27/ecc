#include "std.h"
#include "sassert.h"
#include "ctree.h"
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


    static string err_helper(const string& prefix, const string* pName, int line)
    {
	stringstream ss;
	ss << *pName << ": " << prefix << " at line " << line;
	return ss.str();
    }

   /**
     * Constructs the error from the enum def and the line number. 
     */
    duplicateenumexception::duplicateenumexception(const string* pName, int line)
	: parseexception(EnDuplicateEnum), 
	  customErrMsg(err_helper("Duplicate enum type name",pName,line))
    {

    }
    
    /**
     * Returns a generic string. Subclasses should provide their own implementation 
     */
    const char* duplicateenumexception::what(void) const noexcept
    {
	return customErrMsg.c_str();
    }

    longstringonflagexception::longstringonflagexception(const string* pName, int line)
	: parseexception(EnLongstringOnFlags),
	  customErrMsg(err_helper("Combination of longstrings and flag attribute",pName,line))
    {

    }

    /**
     * Returns a generic string. Subclasses should provide their own implementation 
     */
    const char* longstringonflagexception::what(void) const noexcept
    {
	return customErrMsg.c_str();
    }

}


