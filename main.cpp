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
extern void yysetstream(std::istream*);

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

/**
 * Main execution loop of the ecc utility
 */
int main(void)
{
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
}
