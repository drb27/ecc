%{
#include <math.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "ast.h"
#include "ecc.tab.h"

#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) ecc::input(buf,result,max_size);

#undef YY_DECL
#define YY_DECL int _yylex(void)

namespace ecc
{
    extern void input(char*,int&,size_t);
}

%}

DIGIT [0-9]
ID    [a-z][a-z0-9_]*
WS    [ \t\n]+
%%

typedef    { return TYPEDEF; }
enum       { return  ENUM; }
\{         { return CURLY_OPEN; }
\}         { return CURLY_CLOSE; }
\;         { return SEMICOLON; }
,          { return COMMA; }
=          { return EQUALS; }
{DIGIT}+   { yylval.int_val = atoi(yytext); return INTEGER; }
{ID}       { yylval.string_val = new std::string(yytext); return IDENTIFIER; }
{WS}
%%
