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
    POW     "**"
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
%type <AExp>       atom_expr;
%type <AExp>       power;
%type <AExp>       factor;
%type <AExp>       term;
%type <AExp>       aexp;
%type <Identifier> id;
%type <Stmt>       stmt;
%type <Stmt>       top_stmt;
%type <Assign>     assign;
%type <StmtList>   block;
%type <Loop>       loop;
%type <RawAExp>    rawaexp;
%type <Type>       type_spec
%type <Decl>       decl;
%type <Defun>      defun;
%type <Import>     import;
%type <ModDecl>    module_decl;
%type <ModDef>     module_def;
%type <Return>     return;
%type <ImportList> imports;
%type <DeclList> decl_list;
%type <TypeList> type_spec_list;
%type <StmtList> stmts;
%type <StmtList> top_stmts;
%type <AExpList> arg_list;
%type <AExpList> slice_list;
%type <std::string>         module_name

%%

%start kaleido;

kaleido : module_def { driver.result = $1; }

module_def : module_decl imports top_stmts { $$ = ModDef($1.name, $2, $3); }
           | top_stmts                     { $$ = ModDef($1); }

imports : imports import { $$ = $1.push($2);    }
        | import         { $$ = ImportList($1); }
        | %empty         { $$ = ImportList();   }

import : "import" module_name { $$ = Import($2); }

module_decl : "module" module_name { $$ = ModDecl($2); }

module_name : module_name "." id { $$ = $1 + $3.value; }
            | id                 { $$ = $1.value; }

top_stmts : top_stmt top_stmts { $$ = $2.push($1); }
          | top_stmt           { $$ = StmtList($1); }
          | %empty             { $$ = StmtList(); }

top_stmt : defun   { $$ = Stmt(Stmt::stmt_defun, &$1); }
         | stmt    { $$ = $1; }

defun : "def" id "(" decl_list ")" block { $$ = Defun($2, $4, $6); }

stmts : stmt stmts { $$ = $2.push($1); }
      | stmt       { $$ = StmtList($1); }
      | %empty     { $$ = StmtList(); }

stmt : rawaexp { $$ = Stmt(Stmt::stmt_aexp,   &$1); }
     | assign  { $$ = Stmt(Stmt::stmt_assign, &$1); }
     | loop    { $$ = Stmt(Stmt::stmt_loop,   &$1); }
     | decl    { $$ = Stmt(Stmt::stmt_decl,   &$1); }
     | return  { $$ = Stmt(Stmt::stmt_ret,    &$1); }

block : "{" stmts "}" { $$ = $2; }

return : "return" aexp { $$ = Return($2); }

rawaexp : aexp { $$ = RawAExp($1); }

decl_list : decl               { $$ = DeclList($1); }
          | decl_list "," decl { $$ = $1.push($3); }
          | %empty             { $$ = DeclList(); }

decl : type_spec id            { $$ = Decl($1, $2); }

type_spec : "i64"                     { $$ = Type(Type::type_int); }
          | "f64"                     { $$ = Type(Type::type_double); }  
          | "(" type_spec_list ")"    { $$ = Type($2); }
          | type_spec "[" "]"         { $$ = Type($1); }
          | type_spec "[" INTEGER "]" { $$ = Type($1); }

type_spec_list
    : type_spec { $$ = TypeList($1); }
    | type_spec_list "," type_spec { $$ = $1.push($3); }
    | %empty  { $$ = TypeList(); }

assign : id "=" aexp { $$ = Assign($1, $3); }
       | SET id aexp { $$ = Assign($2, $3); }

loop : FOR id FROM aexp TO aexp STEP aexp stmts { $$ = Loop($2, $4, $6, $8, $9); }

atom : id            { $$ = AExp($1); }
     | "(" aexp ")"  { $$ = $2; }
     | INTEGER       { $$ = AExp($1); }
     | FLOAT         { $$ = AExp($1); }

atom_expr : atom                            { $$ = $1; }
          | atom_expr "(" arg_list ")"      { $$ = AExp(AExp::aexp_call,  $1, $3); }
          | atom_expr "[" slice_list "]"    { $$ = AExp(AExp::aexp_slice, $1, $3); }
          | atom_expr "." id                { $$ = AExp(AExp::aexp_attr,  $1, $3.value); }

power : atom_expr             { $$ = $1; }
      | atom_expr "**" factor { $$ = AExp(AExp::aexp_pow, $1, $3); }

factor : "-" factor    { $$ = AExp(AExp::aexp_negate, $2);  }
       | "+" factor    { $$ = $2; }
       | power         { $$ = $1; }

term : factor          { $$ = $1; }
     | factor "+" factor { $$ = AExp(AExp::aexp_add, $1, $3); } 
     | factor "-" factor { $$ = AExp(AExp::aexp_sub, $1, $3); } 

aexp : term          { $$ = $1; }
     | term "*" term { $$ = AExp(AExp::aexp_mul, $1, $3); }
     | term "/" term { $$ = AExp(AExp::aexp_div, $1, $3); }

arg_list : arg_list "," aexp { $$ = $1.push($3); }
         | aexp              { $$ = AExpList($1); }
         | %empty            { $$ = AExpList();  }

slice_list : slice_list "," aexp { $$ = $1.push($3); }
           | aexp                { $$ = AExpList($1);  }

id : IDENTIFIER      { $$ = Identifier($1); }

%%

void kaleido::parser::KaleidoParser::error (const location_type& l, const std::string& m) {
    driver.error (l, m);
}
