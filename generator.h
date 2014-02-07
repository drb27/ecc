
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
	 * @param ostr a reference to the output stream to receive the output
	 * @param items the list of enum definitions to translate
	 */
	virtual void translate(const ast::elist_t& items, 
			       std::ostream& ostr = std::cout )=0;
	
    };

    class defgen : public generator
    {
    public:
	virtual void translate(const ast::elist_t& items,std::ostream& ostr);
	
    protected:
	virtual const std::string tl_header() const;
	virtual const std::string tl_typedef(const ast::enumdef& ed) const;
	virtual const std::string tl_strings(const ast::elist_t& items) const;
	virtual const std::string tl_functions(const ast::enumdef& ed) const;
    };
}

#endif
