%skeleton "lalr1.cc"

%defines
%define parser_class_name { KaleidoParser }
%define api.namespace { kaleido::parser }
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%output "parser.cpp"

%code requires
{
#include <string>
#include <vector>
#include <cstdint>
#include "node.hpp"
namespace kaleido {
namespace parser {
class KaleidoDriver;
}
}
}

%param { KaleidoDriver& driver }

%locations
%initial-action
{
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

%define parse.trace
%define parse.error verbose

%code
{
# include "driver.hpp"
}

%define api.token.prefix {TK_}
%token
    END 0  "met EOF"
    ASSIGN "="
    MINUS   "-"
    PLUS    "+"
    STAR    "*"
    SLASH   "/"
    LPAREN  "("
    RPAREN  ")"
;

%token <std::string> IDENTIFIER "identifier"
%token <double>      FLOAT
%token <int64_t>     INTEGER

%type <AExp> aexp;

%%

%start module_def;

module_def : module_decl imp_list top_stmts

imp_list : imp
         | imp_list imp

imp : "import" module_name

module_decl : "module" module_name

module_name : IDENTIFIER
            | module_name "." IDENTIFIER

top_stmts : top_stmt
          | top_stmts top_stmt

top_stmt : defun
         | stmt

defun : "def" IDENTIFIER "(" decl_list ")" block

stmts : stmt
      | stmts stmt

stmt : call
     | assign

call : IDENTIFIER "(" param_list ")"

param_list : param
           | param_list "," param
           | 

param : IDENTIFIER

decl_list : decl
          | decl_list "," decl
          |   

decl : IDENTIFIER IDENTIFIER

block : '{' stmts '}' 

assign : lval '=' rval
       | "set" lval rval

lval : IDENTIFIER
rval : IDENTIFIER
     | call
     | literal
     | aexp

literal : INTEGER
        | FLOAT

%left '+' '-';
%left '*' '/';
aexp : aexp '+' aexp  
     | aexp '-' aexp  
     | aexp '*' aexp  
     | aexp '/' aexp  
     | '(' aexp ')'  { std::swap($$, $2); }
     | IDENTIFIER    { auto id = Identifier($1); $$ = AExp(id); }
/*     | literal        */

%%

void kaleido::parser::KaleidoParser::error (const location_type& l, const std::string& m) {
    driver.error (l, m);
}
