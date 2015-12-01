%skeleton "lalr1.cc"

%defines
%define parser_class_name { KaleidoParser }
%define api.namespace { kaleido::parser }
%define api.token.constructor
%define api.value.type variant
%define parse.assert

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
    END 0  "EOF"
    ASSIGN  "="
    LPAREN  "("
    RPAREN  ")"
    MINUS   "-"
    PLUS    "+"
    STAR    "*"
    SLASH   "/"
    COMMA   ","
    LBRACE  "{"
    RBRACE  "}"
    FOR     "for"
    FROM    "from"
    TO      "to"
    STEP    "step"
    SET     "set"
;

%token <std::string> IDENTIFIER "identifier"
%token <double>      FLOAT
%token <int64_t>     INTEGER

%type <AExp>       aexp;
%type <Identifier> id;
%type <Stmt>       stmt;
%type <Call>       call;
%type <Assign>     assign;
%type <Block>      block;
%type <Loop>       loop;
%type < std::vector<Stmt> > stmts;
%type < std::vector<AExp> > arg_list;

%type <Loop>       entry;


%%

%start entry;

entry : loop { driver.result = $1; }

module_def : module_decl imp_list top_stmts
           | imp_list top_stmts
           | top_stmts

imp_list : imp
         | imp_list imp

imp : "import" module_name

module_decl : "module" module_name

module_name : id
            | module_name "." id

top_stmts : top_stmt
          | top_stmts top_stmt
          | %empty

top_stmt : defun
         | stmt

defun : "def" id "(" decl_list ")" block

stmts : stmt       { $$ = std::vector<Stmt>(); $$.push_back($1); }
      | stmts stmt { $1.push_back($2); std::swap($$, $1); }
      | %empty     { $$ = std::vector<Stmt>(); }

stmt : call   { $$ = Stmt(Stmt::stmt_call,   &$1); }
     | assign { $$ = Stmt(Stmt::stmt_assign, &$1); }
     | loop   { $$ = Stmt(Stmt::stmt_loop,   &$1); }
     | block  { $$ = Stmt(Stmt::stmt_block,  &$1); }

decl_list : decl
          | decl_list "," decl
          | %empty

decl : id id 

block : "{" stmts "}" { $$ = Block($2); }

assign : id "=" aexp { $$ = Assign($1, $3); }
       | SET id aexp { $$ = Assign($2, $3); }
loop : FOR id FROM aexp TO aexp STEP aexp stmt { $$ = Loop($2, $4, $6, $8, &$9); }

%left "+" "-";
%left "*" "/";
aexp : aexp "+" aexp { $$ = AExp(AExp::aexp_add, $1, $3); } 
     | aexp "-" aexp { $$ = AExp(AExp::aexp_sub, $1, $3); } 
     | aexp "*" aexp { $$ = AExp(AExp::aexp_mul, $1, $3); }
     | aexp "/" aexp { $$ = AExp(AExp::aexp_div, $1, $3); }
     | "(" aexp ")"  { std::swap($$, $2); }
     | id            { $$ = AExp($1); }
     | INTEGER       { $$ = AExp($1); }
     | FLOAT         { $$ = AExp($1); }

call : id "(" arg_list ")" { $$ = Call($1, $3); }

arg_list : aexp              { $$ = std::vector<AExp>(); $$.push_back($1); }
         | arg_list "," aexp { $1.push_back($3); std::swap($$, $1); }
         | %empty            { $$ = std::vector<AExp>(); }

id : IDENTIFIER      { $$ = Identifier($1); }

%%

void kaleido::parser::KaleidoParser::error (const location_type& l, const std::string& m) {
    driver.error (l, m);
}
