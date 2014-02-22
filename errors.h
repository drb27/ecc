#ifndef _ERRORS_H_
#define _ERRORS_H_

namespace ecc
{
    typedef enum
    {
	EnNoError=0,
	EnDuplicateEnum,
	EnLongstringOnFlags
    } parse_error_t;

    /**
     * Abstract base class for all exceptions in ecc
     */
    class exception : public std::exception
    {

    public:
	virtual const char* what(void) const noexcept;

    protected:
	exception();
    };

    /**
     * Abstract base class for all parse exceptions in ecc
     */
    class parseexception : public exception
    {
    public:
	virtual const char* what(void) const noexcept;

    protected:
	parseexception(const parse_error_t en);
	const parse_error_t errCode;
    };

    /**
     * Abstract base class for all parse exceptions in ecc
     */
    class duplicateenumexception : public parseexception
    {
    public:
	duplicateenumexception(const string* pName,int line);
	virtual const char* what(void) const noexcept;
    
    protected:
	const std::string customErrMsg;

    };

    class longstringonflagexception : public parseexception
    {
    public:
	longstringonflagexception(const string* pName,int line);
	virtual const char* what(void) const noexcept;
    
    protected:
	const std::string customErrMsg;
	
    };
}

#endif
