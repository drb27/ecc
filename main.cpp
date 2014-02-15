#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <vector>
#include <ostream>
#include <string>
#include "ast.h"
#include "generator.h"
#include "ecc.tab.h"

extern int _yylex(void);

#define YY_NULL (0)

using std::string;
using std::cerr;
using std::cout;
using std::endl;
using std::ofstream;
using std::istream;
using std::ifstream;
using std::vector;

namespace ecc
{
    extern const string version = "ecc v0.1beta";       /**< Version string */
    ast::elist_t MasterList;				/**< Parser places output here */
    ast::enumdef* CurrentEnumDef;			/**< Used during parsing */
    vector<ast::enumattr> CurrentAttributes;
    int CurrentLine=1;		                        /**< Current line of input file */
}

namespace
{
    /** Holds a pointer to the current input stream, for ecc::input to access */
    istream* pStream;

    /** String to print in the event that the command line is malformed */
    const string StrMalformed = "Usage: ecc -c <infile> [-o <outfile>]";
    const string StrFilespec = "ERROR: Input cannot be the same file as the output";
    const string StrOpenInputFailed = "ERROR: Cannot open input file ";
    const string StrOpenOutputFailed = "ERROR: Cannot open output file ";

    /** Name of the input file */
    string inputFile="";

    /** Name of the output file (compilation unit) */
    string outputFileCode="";

    /** Name of the output file (header) */
    string outputFileHeader="";

    /** Valid set of exit status codes */
    enum class es
    {
	ok=0,			/**< Command completed successfully */
	badParams=1,		/**< Bad command line / options */
	inputError=2,		/**< Couldn't open or read the input file */
        outputError=3,	        /**< Couldn't create or write the output file */
	syntaxError=4 	        /**< Malformed input file */
    };

}

namespace ecc
{
    /** Provides stream input functionality to the lexer. */
    void input(char* buf, int& result, size_t max_size)
    {
 	if (pStream->peek()==EOF)
 	    result = YY_NULL;			
 	else 
	{ 
	    pStream->read(buf,max_size); 
	    result = pStream->gcount(); 
 	} 

    }

}

/**
 * Included for future use
 */
int yylex(void) { return _yylex(); }

/** Calculates the default output file name from the input file name */
static string default_outfile(const string& ifn, const string& fext)
{

    size_t index_ext = ifn.rfind('.');
    size_t index_leaf = ifn.rfind('/');
    string ofn;

    if ( (index_ext == string::npos) 
	 || ( index_leaf!=string::npos && (index_leaf > index_ext) ) )
	// There's no file extension, simply add one
	ofn = ifn + "." + fext;
    else
	// There is a file extension
	ofn = ifn.substr(0,index_ext) + "." + fext;

    return ofn;
}

/** Parses input options */
static es parse_options(int argc, char** argv)
{
    // Skip over executable name
    argc--; argv++;

    // Check minimum params
    if (argc<2)
	goto malformed;

    // Loop over param pairs
    while (argc)
    {
	const string option(*argv); argc--; argv++;
	
	if ( (!argc) || (option[0]!='-') ) goto malformed;

	const string param(*argv); argc--; argv++;

	switch (option[1])
	{
	case 'c':
	    inputFile = param;
	    break;

	case 'o':
	    outputFileCode = param;
	    break;

	case 'h':
	    outputFileHeader = param;
	    break;

	default:
	    goto malformed;
	}

    }

    // Check that we got mandatory options
    if ( inputFile.length() < 1 )
	goto malformed;
    
    // If no output file (code) was set, calculate name from input file
    if ( outputFileCode.length() < 1 )
	outputFileCode = default_outfile(inputFile,"c");
    
    // If no output file (header) was set, calculate name from input file
    if ( outputFileHeader.length() < 1 )
	outputFileHeader = default_outfile(inputFile,"h");
    
    // Check that the input and output files are different
    if ( inputFile==outputFileCode) goto filespec;
    if ( inputFile==outputFileHeader) goto filespec;
    if ( outputFileCode==outputFileHeader) goto filespec;

    // All good
    return es::ok;

malformed:
    cerr << StrMalformed << endl;
    return es::badParams;

filespec:
    cerr << StrFilespec << endl;
    return es::badParams;

}

/** 
 * Called when the parser/scanner encounters an error.
 * At the moment, just show the error and the line number
 */
void yyerror(const char* s)
{
    std::cout << "ERROR: " << s << "  at line " << ecc::CurrentLine <<std::endl;
}


/**
 * Main execution loop of the ecc utility
 */
int main(int argc, char** argv)
{
    es exit_code=es::ok;

    // Parse the command line parameters
    if (es::ok!=(exit_code = parse_options(argc,argv)))
	exit((int)exit_code);
    
    // Attempt to open the input file
    ifstream ifs(inputFile);
    
    if (ifs.fail() )
    {
	cerr << StrOpenInputFailed << inputFile << endl; 
	exit((int)es::inputError);
    }
    
    // Tell the scanner where to get its input
    pStream = &ifs;

    // Parse the stream, close the input
    yyparse();
    ifs.close();

    // Attempt to open the output file (code)
    ofstream ofsc(outputFileCode, ofstream::trunc);
    
    if ( ofsc.fail() )
    {
	cerr << StrOpenOutputFailed << outputFileCode << endl;
	exit((int)es::outputError);	
    }

    // Attempt to open the output file (header)
    ofstream ofsh(outputFileHeader, ofstream::trunc);
    
    if ( ofsh.fail() )
    {
	cerr << StrOpenOutputFailed << outputFileHeader << endl;
	exit((int)es::outputError);	
    }

    // Generate the output (defaults to cout)
    ecc::generator* pGen = new ecc::defgen();
    pGen->translate( ecc::MasterList, outputFileHeader, outputFileCode, ofsc, ofsh );
    delete pGen;

    ofsc.close();
    ofsh.close();

    exit((int)es::ok);
}
