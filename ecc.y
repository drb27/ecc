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
    extern ecc::ast::enumdef * CurrentEnumDef;
}

using namespace ecc;
using namespace ecc::ast;

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
    | enumlist
     ;

enumlist: enumdef
	| enumlist enumdef;

enumdef: TYPEDEF 
    { CurrentEnumDef = new enumdef(); } 
    ENUM CURLY_OPEN valuelist CURLY_CLOSE IDENTIFIER SEMICOLON 
    { CurrentEnumDef->setname($7); MasterList.push_back( CurrentEnumDef ); };
    
    
valuelist:   firstvaluepair  
	| firstvaluepair subsequentlist
	;
    
subsequentlist:   subsequentvaluepair 
	| subsequentlist subsequentvaluepair
	;
    
firstvaluepair:   
    IDENTIFIER  
    { CurrentEnumDef->insert_value(pair_t(*$1,AST_DEFAULT_ENUM_VALUE) ); delete $1; }
    | IDENTIFIER EQUALS INTEGER 
    { CurrentEnumDef->insert_value(pair_t(*$1,$3) ); delete $1; }
    ;
    
subsequentvaluepair:   
    COMMA IDENTIFIER 
    { CurrentEnumDef->insert_value(pair_t(*$2,AST_DEFAULT_ENUM_VALUE) ); delete $2; }
    | COMMA IDENTIFIER EQUALS INTEGER 
    { CurrentEnumDef->insert_value(pair_t(*$2,$4) ); delete $2; }
    ;
    
%%
	  
void yyerror(const char* s)
{
    std::cout << s << std::endl;
}
	  
