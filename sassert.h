
#ifndef SASSERT_H_
#define SASSERT_H_

#undef assert

/**
 * Exceptions of this class are raised when assert() is called with a false
 * argument, unless asserts are disabled with NDEBUG. */
class assertexception
{
public:
    
    /** 
     * Returns a string referencing the assert condition in source
     */
    virtual std::string what(void) const
    {
	std::stringstream ss;
	ss << "ASSERT FAILURE: [" << expression_ <<  "], function " << function_ 
	   << " at " << file_ << ":" << line_ << std::endl;
	return ss.str();
    }
    
    /**
     * The constructor will output a message to out immediately. Execution
     * continues as normal.
     *
     * @param ex The expression that evaluated to false
     * @param fl The file in which the assert statement resides
     * @param fn The function in which the assert statement resides
     * @param ln The line on which the assert statement resides
     * @param out The stream to which the assert message is written (defaults to std::cerr)
     */
    assertexception(const char* ex, const char* fl, const char* fn, 
		    int ln, std::ostream& out = std::cerr  )
	: expression_(ex), file_(fl), function_(fn), line_(ln), out_(out)
    {
	// Send the warning message to the output stream
	out_ << what();
    }
    
    /**
     * Doesn't do anything. 
     */
    virtual ~assertexception() {}
    
    
protected:
    const std::string expression_;  /**<  The failing expression */
    const int line_;                /**<  The line number of the assert() */
    const std::string function_;    /**<  The function calling assert() */
    const std::string file_;        /**<  The file containing the call to assert */
    std::ostream& out_;             /**<  The stream to which the warning message is written */
};

#ifndef NDEBUG
/** 
 * The assert() macro is provided as a convenient way of throwing an
 * assertexception
 */
#define assert(x) (x)?(void)0:throw assertexception(#x,__FILE__,__func__,__LINE__)
#else
#define assert(x) (void)0
#endif

#endif
