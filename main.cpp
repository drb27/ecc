#include <iostream>
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

    typedef enum
    {
	EcOk=0,
	EcBadParams=1
    } exitstatus_t;

}

/**
 * Included for future use
 */
int yylex(void) { return _yylex(); }

/** Parses input options */
static ecc::exitstatus_t parse_options(int argc, char** argv)
{
    // Skip over executable name
    argc--; argv++;

    // Check minimum params
    if (argc<2)
	goto malformed;

    // Loop over param pairs
    while (argc)
    {
	const std::string option(*argv);
	argc--; argv++;
    }

    return ecc::EcOk;

malformed:
    std::cerr << StrMalformed << std::endl;
    return ecc::EcBadParams;
}

/**
 * Main execution loop of the ecc utility
 */
int main(int argc, char** argv)
{
    ecc::exitstatus_t exit_code=ecc::EcOk;

    // Parse the command line parameters
    if (0!=(exit_code = parse_options(argc,argv)))
	exit(exit_code);

    // Set up example input
    std::stringstream ss;
    
    ss << "typedef enum { frog=9, tree, banana = 7 } enum_t;"
       << "typedef enum { willow } other_t;";
    
    // Tell the scanner where to get its input
    pStream = &ss;

    // Parse the stream
    yyparse();

    // Generate the output (defaults to std::cout)
    ecc::generator* pGen = new ecc::defgen();
    pGen->translate( ecc::MasterList );
    delete pGen;

    exit(ecc::EcOk);
}
