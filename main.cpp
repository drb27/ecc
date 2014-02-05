#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include "ast.h"
#include "ecc.tab.h"

extern int _yylex(void);
extern void yysetstream(std::istream*);

namespace ecc
{
    ecc::ast::elist_t MasterList;
    ecc::ast::enumdef* CurrentEnumDef;
}

int yylex(void) { return _yylex(); }

int main(void)
{
    std::stringstream ss;
    ss << "typedef enum { frog=9, banana = 7 } enum_t; typedef enum { willow } other_t;";
    yysetstream(&ss);
    yyparse();

    for (auto i : ecc::MasterList)
    {
	std::cout << i->get_name() << ":" << std::endl;
	
	for (auto v : i->getvalues() )
	{
	    std::cout << v.first << ", "  << v.second <<  std::endl;
	}
    }
}
