%{
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "ast.h"



int yylex(void);
void yyerror(const char*);

namespace ecc
{
    extern ecc::ast::elist_t MasterList;
}
%}

%union
 {
    int                  int_val;
    std::string*         string_val;
 }

%token NULLTOKEN
%token COMMA
%token CURLY_OPEN
%token CURLY_CLOSE
%token ENUM
%token EQUALS
%token IDENTIFIER
%token INTEGER
%token SEMICOLON
%token TYPEDEF

%type <int_val> INTEGER
%type <string_val> IDENTIFIER
%start input

%%

input:   /* empty */ 
     | enumlist     { std::cout << "Matched input"; } 
     ;

enumlist: enumdef
	 | enumlist enumdef;

 enumdef: TYPEDEF ENUM CURLY_OPEN valuelist CURLY_CLOSE IDENTIFIER SEMICOLON 
     { ecc::MasterList.push_back( new ecc::ast::enumdef($6)); };


valuelist:   firstvaluepair 
           | firstvaluepair subsequentlist;

subsequentlist:   subsequentvaluepair 
                | subsequentvaluepair subsequentlist;

firstvaluepair:   IDENTIFIER 
    | IDENTIFIER EQUALS INTEGER
	 ;

subsequentvaluepair:   COMMA IDENTIFIER
	 | COMMA IDENTIFIER EQUALS INTEGER
	 ;

%%

	 void yyerror(const char* s)
	 {
	     std::cout << s << std::endl;
	 }
