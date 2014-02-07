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

namespace ecc
{
    extern const std::string version = "ecc v0.0alpha"; /**< Version string */
    ast::elist_t MasterList;				/**< Parser places output here */
    ast::enumdef* CurrentEnumDef;			/**< Used during parsing */
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
    yysetstream(&ss);

    // Parse the stream
    yyparse();

    // Generate the output (defaults to std::cout)
    ecc::generator* pGen = new ecc::defgen();
    pGen->translate( ecc::MasterList );
    delete pGen;
}
