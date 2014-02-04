#include <iostream>
#include <sstream>
#include <vector>
#include "tokens.h"

extern int _yylex(void);
extern void yysetstream(std::istream*);

typedef std::vector<token_t> tokenstack_t;
tokenstack_t::iterator i;

// A place to store the tokens
tokenstack_t tokenstack;

int yylex(void)
{
    if (i!=tokenstack.end())
    {
	int retval = (int)(*i);
	i++;
	return retval;
    }
    else
	return NULLTOKEN;
}

void yylex_init(void)
{
    i = tokenstack.begin();
}

int main(int argc, char** argv )
{
    // Set up the input stream
    std::stringstream ss;
    ss << "123;";

    // Set the reference
    yysetstream(&ss);


    // Do the thing
    token_t token;
    while ( token=(token_t)_yylex() )
	{
	    std::cout << token << std::endl;
	    tokenstack.push_back(token);
	}

    yylex_init();
    
    while ( auto tk = yylex() )
    {
	std::cout << tk << std::endl;
    }
}
