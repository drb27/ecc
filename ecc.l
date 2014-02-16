%option noyywrap
%{
#include <math.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using std::string;
using std::vector;

#include "ast.h"
#include "ecc.tab.h"
#include "globals.h"

#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) ecc::input(buf,result,max_size);

#undef YY_DECL
#define YY_DECL int _yylex(void)

%}

%x MLC

DIGIT [0-9]
ID    [a-zA-Z_][a-zA-Z0-9_]*
WS    [ \t]+
%%

"/*"              { BEGIN(MLC); }
<MLC>[^*\n]*      // Eat anything that is not a star or newline
<MLC>"*"+[^*/\n]* // Eat stars not followed by a /
<MLC>\n           { ecc::CurrentLine++; }
<MLC>"*"+"/"      { BEGIN(INITIAL); }

typedef     { return TYPEDEF; }
enum        { return  ENUM; }
flags       { return ATTR_FLAGS; }
\{          { return CURLY_OPEN; }
\}          { return CURLY_CLOSE; }
\;          { return SEMICOLON; }
\:          { return COLON; }
,           { return COMMA; }
=           { return EQUALS; }
{DIGIT}+    { yylval.int_val = atoi(yytext); return INTEGER; }
{ID}        { yylval.string_val = new std::string(yytext); return IDENTIFIER; }
{WS}
\/\/[^\n]*\n // Chew single line comments
\n          { ecc::CurrentLine++; }
%%

