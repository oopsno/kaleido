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
    IMPORT  "import"
    MODULE  "module"
    DEF     "def"
    I64     "f64"
    F64     "i64"
    RET     "return"
;

%token <std::string> IDENTIFIER "identifier"
%token <double>      FLOAT
%token <int64_t>     INTEGER


%type <AExp>       atom;
%type <AExp>       factor;
%type <AExp>       term;
%type <AExp>       aexp;
%type <Identifier> id;
%type <Stmt>       stmt;
%type <Stmt>       top_stmt;
%type <AExp>       call;
%type <Assign>     assign;
%type <Block>      block;
%type <Loop>       loop;
%type <RawAExp>    rawaexp;
%type <Type>       type_spec
%type <Decl>       decl;
%type <Defun>      defun;
%type <Import>     import;
%type <ModDecl>    module_decl;
%type <ModDef>     module_def;
%type <Return>     return;
%type < std::vector<Import> > imports;
%type < std::vector<Decl> > decl_list;
%type < std::vector<Type> > type_spec_list;
%type < std::vector<Stmt> > stmts;
%type < std::vector<Stmt> > top_stmts;
%type < std::vector<AExp> > arg_list;
%type <std::string>         module_name

%%

%start kaleido;

kaleido : module_def { driver.result = $1; }

module_def : module_decl imports top_stmts { $$ = ModDef($1.name, $2, $3); }
           | top_stmts                     { $$ = ModDef($1); }

imports : import imports { $2.push_back($1); $$ = $2; }
        | %empty { $$ = std::vector<Import>(); }

import : "import" module_name { $$ = Import($2); }

module_decl : "module" module_name { $$ = ModDecl($2); }

module_name : module_name "." id { $$ = $3 + $1.value; }
            | id                 { $$ = $1; }

top_stmts : top_stmt top_stmts { $2.push_back($1); $$ = $2; }
          | %empty { $$ = std::vector<Stmt>(); }

top_stmt : defun   { $$ = Stmt(Stmt::stmt_defun, &$1); }
         | stmt    { $$ = $1; }

defun : "def" id "(" decl_list ")" block { $$ = Defun($2, $4, $6); }

stmts : stmt stmts { $2.push_back($1); $$ = $1; }
      | %empty     { $$ = std::vector<Stmt>(); }

stmt : rawaexp { $$ = Stmt(Stmt::stmt_aexp,   &$1); }
     | assign  { $$ = Stmt(Stmt::stmt_assign, &$1); }
     | loop    { $$ = Stmt(Stmt::stmt_loop,   &$1); }
     | block   { $$ = Stmt(Stmt::stmt_block,  &$1); }
     | decl    { $$ = Stmt(Stmt::stmt_decl,   &$1); }
     | return  { $$ = Stmt(Stmt::stmt_ret,    &$1); }

block : "{" stmts "}" { $$ = Block($2); }

return : "return" aexp { $$ = Return($2); }

rawaexp : aexp { $$ = RawAExp($1); }

decl_list : decl               { $$ = std::vector<Decl>(); $$.push_back($1); }
          | decl_list "," decl { $1.push_back($3); $$ = $1; }
          | %empty             { $$ = std::vector<Decl>(); }

decl : type_spec id            { $$ = Decl($1, $2); }

type_spec : "i64"                     { $$ = Type(Type::type_int); }
          | "f64"                     { $$ = Type(Type::type_double); }  
          | "(" type_spec_list ")"    { $$ = Type($2); }
          | type_spec "[" "]"         { $$ = Type($1); }
          | type_spec "[" INTEGER "]" { $$ = Type($1); }

type_spec_list
    : type_spec { $$ = std::vector<Type>(); $$.push_back($1); }
    | type_spec_list "," type_spec { $1.push_back($3); $$ = $1; }
    | %empty  { $$ = std::vector<Type>(); }

assign : id "=" aexp { $$ = Assign($1, $3); }
       | SET id aexp { $$ = Assign($2, $3); }

loop : FOR id FROM aexp TO aexp STEP aexp stmt { $$ = Loop($2, $4, $6, $8, &$9); }

atom : id            { $$ = AExp($1); }
     | "(" aexp ")"  { $$ = $2; }
     | INTEGER       { $$ = AExp($1); }
     | FLOAT         { $$ = AExp($1); }
     | call          { $$ = $1; }

factor : "-" factor      { $$ = AExp(AExp::aexp_negate, $2);  }
       | "+" factor      { $$ = $2; }
       | atom            { $$ = $1; }

term : factor          { $$ = $1; }
     | factor "+" term { $$ = AExp(AExp::aexp_add, $1, $3); } 
     | factor "-" term { $$ = AExp(AExp::aexp_sub, $1, $3); } 

aexp : term          { $$ = $1; }
     | term "*" aexp { $$ = AExp(AExp::aexp_mul, $1, $3); }
     | term "/" aexp { $$ = AExp(AExp::aexp_div, $1, $3); }

call : id "(" arg_list ")" { $$ = AExp($1, $3); }

arg_list : aexp "," arg_list { $3.push_back($1); $$ = $3; }
         | %empty            { $$ = std::vector<AExp>(); }

id : IDENTIFIER      { $$ = Identifier($1); }

%%

void kaleido::parser::KaleidoParser::error (const location_type& l, const std::string& m) {
    driver.error (l, m);
}
