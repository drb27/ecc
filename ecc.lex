%{
#include <math.h>
#include <iostream>
#include <sstream>
#include "tokens.h"

namespace {

    static std::istream* pStream;

}

void yysetstream(std::istream* ps)
{
    pStream = ps;
}

#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
    { \
	char c; \
	if (pStream->eof()) \
	    result = YY_NULL;			\
	else { \
	pStream->read(&c,1); \
	buf[0] = c; \
	result = 1; \
	} \
    }

#undef YY_DECL
#define YY_DECL int _yylex(void)

%}

DIGIT [0-9]
ID    [a-z][a-z0-9]*

%%

;          { return SEMICOLON; }
{DIGIT}+   { return INTEGER; }
{ID}       { return IDENTIFIER; }
%%
