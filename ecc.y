%{
#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;

#include "warning.h"
#include "ast.h"
#include "globals.h"

using namespace ecc;
using namespace ecc::ast;

#include "actions.h"

int yylex(void);
void yyerror(const char*);

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
%token COLON
%token ATTR_FLAGS

%type <int_val> INTEGER
%type <string_val> IDENTIFIER
%start input

%%

input:   /* empty */ 
     | enumlist
     ;

attr: ATTR_FLAGS;

attrlist : attr { CurrentAttributes.push_back(ecc::ast::enumattr::flags); }
    | attrlist COMMA attr { CurrentAttributes.push_back(ecc::ast::enumattr::flags); }
    ;

enumlist: enumdef
     | enumlist enumdef;

typedefspec: TYPEDEF ENUM { ac_register_enumdef( new enumdef() ); }  
     | TYPEDEF ENUM COLON { CurrentAttributes.clear(); } 
       attrlist { ac_register_enumdef( new enumdef(CurrentAttributes) ); } 
     ;


enumdef: typedefspec 
         CURLY_OPEN valuelist CURLY_CLOSE IDENTIFIER SEMICOLON 
         { ac_push_enumdef($5); }
       | error SEMICOLON;
    
    
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
	  
