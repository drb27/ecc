%{
#include <math.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "ast.h"
#include "ecc.tab.h"

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
	if (pStream->peek()==EOF) \
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
ID    [a-z][a-z0-9_]*
%%

typedef    { std::cout << "TYPEDEF"; return TYPEDEF; }
enum       { std::cout << "ENUM"; return ENUM; }
\{          { std::cout << "CURLY_OPEN"; return CURLY_OPEN; }
\}          { std::cout << "CURLY_CLOSE"; return CURLY_CLOSE; }
\;          { return SEMICOLON; }
,          { return COMMA; }
=          { return EQUALS; }
{DIGIT}+   { yylval.int_val = atoi(yytext); return INTEGER; }
{ID}       { yylval.string_val = new std::string(yytext); std::cout << yytext; return IDENTIFIER; }

%%
