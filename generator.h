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

	/**
	 * Write both the header and code file to the given output streams. 
	 *
	 * The default implementation of this function just calls
	 * translate_header() and translate_code().
	 *
	 * @param ostr_c a reference to the output stream to receive the code output
	 * @param ostr_h a reference to the output stream to receive the header output
	 * @param items the list of enum definitions to translate
	 * @param fHeader the file name of the header file (might not be leaf)
	 * @param fCode the file name of the c file (might not be leaf)
	 */
	virtual void translate(const elist_t& items, 
	                       const string& fHeader,
	                       const string& fCode,
			       ostream& ostr_c = cout, 
			       ostream& ostr_h = cout);

    protected:
	
	/**
	 * Write the header file to the given output stream.
	 *
	 * @param ostr_h a reference to the output stream to receive the header output
	 * @param items the list of enum definitions to translate
	 * @param fHeader the file name of the header file (might not be leaf)
	 */
	virtual void translate_header(const elist_t& items, 
				      const string& fHeader,
				      ostream& ostr_h = cout);
	
	/**
	 * Write the code file to the given output stream.
	 *
	 * @param ostr_c a reference to the output stream to receive the code output
	 * @param items the list of enum definitions to translate
	 * @param fHeader the file name of the header file (might not be leaf)
	 */
	virtual void translate_code(const elist_t& items, 
				    const string& fHeader,
				    ostream& ostr_c = cout); 

	typedef enum class 
	{
	    headerFile,
	    codeFile
	} outfile_t;

	/** Translate the header block */
	virtual string tl_head(outfile_t fileType, const string& fHeader)=0;

	/** Translate type definition */
	virtual string tl_typedef(const enumdef& ed)=0;

	/** Function prototype generator */
	virtual string tl_prototype(const enumdef& item, outfile_t fileType)=0;

	/** Main code generation */
	virtual string tl_codebody(const elist_t& items)=0;

	/**
	 * Return a string representation of the current date and time.
	 *
	 * @returns A string representing the current date/time in local time
	 */
	static string currenttime(void);

        /**
	 * Returns the leaf (filename) given a file path. 
	 *
	 * @param fPath can be an absolute or relative path
	 * @returns a string with just the file name (including extension, if any)
	 */
	static string leaf(const string& fPath);

	/**
	 * Converts the given file name into a guard symbol.
	 *
	 * For use in generating include file guards. If the file name given is
	 * a path, its leaf name will be taken first. 
	 *
	 * @param   fPath the file name or file path for the header
	 * @param   prefix an optional string which is prepended to the guard
	 * @returns a string which can be used in an include guard directive
	 */
	static string guard(const string& fPath, const string& prefix="_HG_");

	/** Indent object for keeping track of indent levels */
	indent ind;
    };

}

#endif
