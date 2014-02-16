#ifndef GENERATOR_H_
#define GENERATOR_H_

namespace ecc
{

    /** 
     * Abstract base class for classes that generate compilable output for the 
     * provided list of enum definitions 
     */
    class generator
    {
    public:
	generator();
	virtual ~generator();

	/** Translate the given enum definitions, and write to the given stream. 
	 *
	 * @param ostr_c a reference to the output stream to receive the code output
	 * @param ostr_h a reference to the output stream to receive the header output
	 * @param items the list of enum definitions to translate
	 * @param fHeader the file name of the header file (might not be leaf)
	 * @param fCode the file name of the c file (might not be leaf)
	 */
	virtual void translate(const ast::elist_t& items, 
	                       const std::string& fHeader,
	                       const std::string& fCode,
			       std::ostream& ostr_c = std::cout, 
			       std::ostream& ostr_h = std::cout)=0;
	
    protected:

	/**
	 * Return a string representation of the current date and time.
	 *
	 * @returns A string representing the current date/time in local time
	 */
	static string currenttime(void);

    };

    class defgen : public generator
    {
    public:
	virtual void translate(const ast::elist_t& items, 
			       const std::string& fHeader,
			       const std::string& fCode,
			       std::ostream& ostr_c, 
			       std::ostream& ostr_h);
	
    protected:
	virtual const std::string tl_header() const;
	virtual const std::string tl_typedef(const ast::enumdef& ed) const;
	virtual const std::string tl_strings(const ast::elist_t& items) const;
	virtual const std::string tl_functions(const ast::enumdef& ed) const;
	virtual const std::string tl_functions_flags(const ast::enumdef& ed) const;
	virtual const std::string tl_functions_prototypes(const ast::elist_t& items) const;
    };
}

#endif
