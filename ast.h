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

	/** map of string to string for holding longstrings */
	typedef std::map<std::string,std::string> longstring_map_t;
	
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
	    virtual const string& getlstring(const string& member) const;
	    virtual void insert_value( const pair_t& pPair, 
				       const std::string& longstr = std::string("") );
	    virtual const vector<string>& getmembers() const;
	    virtual void setname( std::string* nm);
	    virtual void setnamespace( const ctree<enumdef>* );
	    virtual const ctree<enumdef>* nspace(void) const;
	    virtual const std::string& get_name(void) const final;

	    bool has_duplicate_values(void) const;
	    inline bool is_flags(void) const { return flags; }

	protected:
	    std::string name;                 /**< The name of the enum type */
	    values_t values;                  /**< Map of members to values */
	    vector<string> members;           /**< List of members, in declared order */
	    longstring_map_t longstrings;	    
	    bool flags;                       /**< True if the enum is a set of flags */
	    const ctree<enumdef>* pNamespace; /**< Owning namespace node */
	};
    
	/** list type for the list of enumdefs at the top of the tree */
	typedef std::vector<enumdef*> elist_t;

    }
}
#endif
