
#ifndef AST_H_
#define AST_H_


#define AST_DEFAULT_ENUM_VALUE (-1)

namespace ecc
{
    namespace ast
    {

        /** Enumeration of different attributes that can be set on the enum definition */ 
        typedef enum class 
	{
	  flags
	} enumattr;

	/** map of string to int for holding enum values */
	typedef std::map<std::string,int> values_t;

	/** Quick access to the pair type */
	typedef values_t::value_type pair_t;

	/** complete definition of an enum */
	class enumdef
	{
	public:
	    enumdef(const std::vector<ecc::ast::enumattr>& attr);
	    enumdef();
	    virtual ~enumdef();

	    virtual const values_t& getvalues() const;
	    virtual void insert_value( const pair_t& pPair);
	    virtual void setname( std::string* nm);
	    virtual const std::string& get_name(void) const final;

	    inline bool is_flags(void) const { return flags; }

	protected:
	    std::string name;
	    values_t values; 
	    bool flags;
	};
    
	/** list type for the list of enumdefs at the top of the tree */
	typedef std::vector<enumdef*> elist_t;

    }
}
#endif
