
#ifndef AST_H_
#define AST_H_

namespace ecc
{
    namespace ast
    {

	/** 
	 * map of string to int for holding enum values
	 */
	typedef std::map<std::string,int> values_t;

	/**
	 * a complete definition of an enum
	 */
	class enumdef
	{
	public:
	    enumdef(const std::string* );
	    virtual ~enumdef();

	    virtual void setvalues( const values_t& );
	    virtual const std::string& get_name(void) final;

	protected:
	    const std::string name;
	    values_t values; 
	};
    
	/**
	 * list type for the list of enumdefs at the top of the tree
	 */
	typedef std::vector<enumdef*> elist_t;

    }
}
#endif
