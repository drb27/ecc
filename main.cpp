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

#define VERSION "ecc v0.0alpha"

extern int _yylex(void);
extern void yysetstream(std::istream*);

namespace ecc
{
    static const std::string version = VERSION;
    ast::elist_t MasterList;
    ast::enumdef* CurrentEnumDef;
}

int yylex(void) { return _yylex(); }

int main(void)
{
    std::stringstream ss;
    ss << "typedef enum { frog=9, tree, banana = 7 } enum_t; typedef enum { willow } other_t;";
    yysetstream(&ss);
    yyparse();

    // for (auto i : ecc::MasterList)
    // {
    // 	std::cout << i->get_name() << ":" << std::endl;
	
    // 	for (auto v : i->getvalues() )
    // 	{
    // 	    std::cout << v.first << ", "  << v.second <<  std::endl;
    // 	}
    // }

    ecc::generator* pGen = new ecc::defgen();
    pGen->translate( ecc::MasterList );
    delete pGen;
}
