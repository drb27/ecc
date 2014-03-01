%{
#include "std.h"
#include "warning.h"
#include "sassert.h"
#include "ctree.h"
#include "ast.h"

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
%token IDENTIFIER_SCOPED
%token INTEGER
%token SEMICOLON
%token TYPEDEF
%token COLON
%token ATTR_FLAGS
%token SB_OPEN
%token SB_CLOSE
%token DBL_QUOTE
%token STRING
%token NAMESPACE

%type <int_val> INTEGER
%type <string_val> IDENTIFIER
%type <string_val> IDENTIFIER_SCOPED
%type <string_val> STRING
%type <string_val> longstring_option

%start input

%%

input:   /* empty */ 
     | stmts
     | error { ac_raise_error(SyntaxError); }
     ;

attr: ATTR_FLAGS;

attrlist : attr { ac_register_attribute(ecc::ast::enumattr::flags); }
    | attrlist COMMA attr { ac_register_attribute(ecc::ast::enumattr::flags); }
    ;

stmt: enumdef | directive;

nsspec: NAMESPACE IDENTIFIER_SCOPED SEMICOLON { ac_set_namespace($2); }
      | NAMESPACE IDENTIFIER SEMICOLON { ac_set_namespace($2); }

directive: nsspec;

stmts: stmt
     | stmts stmt;

typedefspec: TYPEDEF ENUM { ac_begin_enumdef(); }  
     | TYPEDEF ENUM COLON attrlist { ac_begin_enumdef(); } 
     ;


enumdef: typedefspec 
         CURLY_OPEN valuelist CURLY_CLOSE IDENTIFIER SEMICOLON 
         { ac_push_enumdef($5); }
       | typedefspec CURLY_OPEN valuelist CURLY_CLOSE IDENTIFIER { ac_push_enumdef($5); }
         error { ac_raise_error(MissingSemicolon); } SEMICOLON;
       | TYPEDEF error { ac_raise_error(MalformedEnumdef,true); } SEMICOLON
       ;
    
    
valuelist: valuepair  
	| valuepair COMMA valuelist
	;
    
longstring_option: SB_OPEN STRING SB_CLOSE { $$=$2; } | { $$=new std::string(""); } ;
    
valuepair:   
    IDENTIFIER longstring_option { ac_insert_member($1,AST_DEFAULT_ENUM_VALUE,$2); }
  | IDENTIFIER EQUALS INTEGER longstring_option { ac_insert_member($1,$3,$4); };
    
%%
	  
