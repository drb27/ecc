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

namespace ecc
{
    extern const std::string version = "ecc v0.0alpha"; /**< Version string */
    ast::elist_t MasterList;				/**< Parser places output here */
    ast::enumdef* CurrentEnumDef;			/**< Used during parsing */
}

namespace
{
    /** Holds a pointer to the current input stream, for ecc::input to access */
    std::istream* pStream;

    /** String to print in the event that the command line is malformed */
    const std::string StrMalformed = "Usage: ecc -c <infile> [-o <outfile>]";
    const std::string StrFilespec = "ERROR: Input cannot be the same file as the output";
    const std::string StrOpenInputFailed = "ERROR: Cannot open input file ";
    const std::string StrOpenOutputFailed = "ERROR: Cannot open output file ";

    /** Name of the input file */
    std::string inputFile="";

    /** Name of the output file */
    std::string outputFile="";

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
	const std::string option(*argv); argc--; argv++;
	
	if ( (!argc) || (option[0]!='-') ) goto malformed;

	const std::string param(*argv); argc--; argv++;

	switch (option[1])
	{
	case 'c':
	    inputFile = param;
	    break;

	case 'o':
	    outputFile = param;
	    break;

	default:
	    goto malformed;
	}

    }

    // Check that we got mandatory options
    if ( inputFile.length() < 1 )
	goto malformed;
    
    // If no output file was set, calculate name from input file
    if ( outputFile.length() < 1 )
    {
	size_t index_ext = inputFile.rfind('.');
	size_t index_leaf = inputFile.rfind('/');

	if ( (index_ext == std::string::npos) 
	     || ( index_leaf!=std::string::npos && (index_leaf > index_ext) ) )
	{
	    // There's no file extension, simply add one
	    outputFile = inputFile + ".c";
	}
	else
	{
	    // There is a file extension
	    outputFile = inputFile.substr(0,index_ext) + ".c";
	}
    }
    
    // Check that the input and output files are different
    if ( inputFile==outputFile) goto filespec;

    // All good
    return es::ok;

malformed:
    std::cerr << StrMalformed << std::endl;
    return es::badParams;

filespec:
    std::cerr << StrFilespec << std::endl;
    return es::badParams;

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
    std::ifstream ifs(inputFile);
    
    if (ifs.fail() )
    {
	std::cerr << StrOpenInputFailed << inputFile << std::endl; 
	exit((int)es::inputError);
    }
    
    // Tell the scanner where to get its input
    pStream = &ifs;

    // Parse the stream, close the input
    yyparse();
    ifs.close();

    // Attempt to open the output file
    std::ofstream ofs(outputFile, std::ofstream::trunc);
    
    if ( ofs.fail() )
    {
	std::cerr << StrOpenOutputFailed << outputFile << std::endl;
	exit((int)es::outputError);	
    }

    // Generate the output (defaults to std::cout)
    ecc::generator* pGen = new ecc::defgen();
    pGen->translate( ecc::MasterList, ofs );
    delete pGen;

    ofs.close();

    exit((int)es::ok);
}
