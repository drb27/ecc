#include <iostream>
#include <sstream>
#include "tokens.h"

extern int yylex(void);
extern void yysetstream(std::istream*);

int main(int argc, char** argv )
{
    // Set up the input stream
    std::stringstream ss;
    ss << "123;";

    // Set the reference
    yysetstream(&ss);

    // Do the thing
    token_t token;
    while ( token=(token_t)yylex() )
	{
	    std::cout << token << std::endl;
	}
    
}
