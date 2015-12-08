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
#include <cstdint>

#include "parser_assist.hpp"
using namespace kaleido::ast;

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
    NOT     "not"
    AND     "and"
    OR      "or"
    XOR     "xor"
    LANGLE  "<"
    RANGLE  ">"
    EQ      "=="
    LE      "<=" 
    GE      ">="
    NE      "!="
    MINUS   "-"
    PLUS    "+"
    STAR    "*"
    DIV     "/"
    IDIV    "//"
    EXP     "^"
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
    RET     "return"
    IF      "if"
    ELSE    "else"
    I1      "i1"
    I8      "i8"
    I16     "i16"
    I32     "i32"
    I64     "i64"
    F16     "half"
    F32     "float"
    F64     "double"
;

%token <std::string> NAME
%token <std::string> CAPNAME 
%token <int64_t>     INTEGER
%token <double>      FLOAT
%token <bool>        TRUE
%token <bool>        FALSE

%type <Statement*>   top_level;
%type <ModuleImport*> imp;
%type <ModuleDefinition*> modef;
%type <std::string> module_name
%type <Function*>    defun;
%type < std::vector<Statement*>* > stmt_list;
%type < std::vector<Statement*>* > top_level_list;
%type < std::vector<Declaration*>* > var_decl_list;
%type < std::vector<Assign*>* > assign_list; 
%type <Statement*> stmt;
%type <Declaration*> var_decl; 
%type <Declaration*> var_def; 
%type <Loop*> loop;
%type <If*> cond;
%type <Block*> block;
%type <Assign*>      assign;
%type <Arithmetic*>  ar;
%type <Boolean*>     bool;
%type <Type*>        type;
/* %type <NameRef*>     name; */
%type <AST*>         expr;
%type <RVal*>        tuple;
%type < std::vector<AST*>* > expr_list;
%type <Statement*>   return;

%%

%left  "or" "xor";
%left  "and";
%right "not";
%left  ">" "<" "==" ">=" "<=";
%left  "+" "-";
%left  "*" "/" "//";
%precedence UNARY;
%right "^";

%start kaleido;

kaleido : modef top_level_list { driver.result = new Module($1, $2); }
        | top_level_list { driver.result = new Module($1); }

/* top-level statements */
top_level_list : top_level_list top_level { $$ = $1; $$->push_back($2); }
               | top_level { $$ = new std::vector<Statement *>(); $$->push_back($1); }

top_level : defun { $$ = $1; } 
          | stmt  { $$ = $1; }
          | imp   { $$ = $1; }

/* module */
modef : "module" module_name { $$ = new ModuleDefinition($2); }

/* import */
imp : "import" module_name { $$ = new ModuleImport($2); }

module_name : CAPNAME { $$ = $1; }
            | module_name "." CAPNAME { $$ = $1 + "." + $3; }

/* function */
defun : type NAME "(" var_decl_list ")" block { $$ = new Function($1, $2, $4, $6); }
      | type NAME "(" ")" block { $$ = new Function($1, $2, $5); }

var_decl : type NAME { $$ = new Declaration($1, $2); }

var_decl_list : var_decl { $$ = new std::vector<Declaration*>(); $$->push_back($1); }
              | var_decl_list "," var_decl { $1->push_back($3); $$ = $1; }

/* loop */
loop : FOR NAME FROM ar TO ar STEP ar stmt { $$ = new Loop($2, $4, $6, $8, $9); }
     | FOR NAME FROM ar TO ar stmt { $$ = new Loop($2, $4, $6, $7); }

/* statement */
stmt : assign   { $$ = $1; }
     | var_decl { $$ = $1; }
     | var_def  { $$ = $1; }
     | loop     { $$ = $1; }
     | block    { $$ = $1; }
     | cond     { $$ = $1; }
     | return   { $$ = $1; }
     | expr     { $$ = new Expression($1); }

return : "return" expr { $$ = new Return($2); }

stmt_list : stmt { $$ = new std::vector<Statement*>(); $$->push_back($1); }
          | stmt_list stmt { $1->push_back($2); $$ = $1; }

block : "{" stmt_list "}" { $$ = new Block($2); }

/* variable define */
var_def : type assign_list  { $$ = new Declaration($1, $2); }

assign_list : assign { $$ = new std::vector<Assign*>(); $$->push_back($1); }
            | assign_list "," assign { $1->push_back($3); $$ = $1; }

/* assign */
assign : NAME "=" expr { $$ = new Assign($1, $3); }

/* if-else */
%precedence "if";
%precedence "else";
cond : "if" bool stmt { $$ = new If($2, $3); }
     | "if" bool stmt "else" stmt { $$ = new If($2, $3, $5); }

/* expr */
expr : ar    { $$ = $1; }
     | bool  { $$ = $1; }
     | tuple { $$ = $1; }

expr_list : expr { $$ = new std::vector<AST*>(); $$->push_back($1); }
          | expr_list "," expr { $1->push_back($3); $$ = $1; }
          | %empty { $$ = new std::vector<AST*>(); }

tuple : "(" expr_list ")" { $$ = new Tuple($2); }

/* boolexp */
bool : TRUE  { $$ = new BooleanTrue(); }
     | FALSE { $$ = new BooleanFalse(); }
     | ar    { $$ = new Nonzero($1); }
     | ar "<"  ar { $$ = new Compare(op::LT, $1, $3); }
     | ar ">"  ar { $$ = new Compare(op::GT, $1, $3); }
     | ar "=>" ar { $$ = new Compare(op::GE, $1, $3); }
     | ar "<=" ar { $$ = new Compare(op::LE, $1, $3); } 
     | ar "==" ar { $$ = new Compare(op::EQ, $1, $3); } 
     | ar "!=" ar { $$ = new Compare(op::NE, $1, $3); } 
     | bool "and" bool { $$ = new BBO(op::AND, $1, $3); }
     | bool "or"  bool { $$ = new BBO(op::OR,  $1, $3); }
     | bool "xor" bool { $$ = new BBO(op::XOR, $1, $3); }
     | "not" bool %prec UNARY { $$ = new UBO(op::NOT, $2); }
     | "(" bool ")" { $$ = $2; }

/* ar[ithmetic] */
ar : FLOAT   { $$ = new Immediate<double>($1);  }
   | INTEGER { $$ = new Immediate<int64_t>($1); }
   | NAME    { $$ = new VariableRef($1); }
   | ar "+" ar  { $$ = new BinaryArithmeticOperate(op::ADD, $1, $3); }
   | ar "-" ar  { $$ = new BinaryArithmeticOperate(op::SUB, $1, $3); }
   | ar "*" ar  { $$ = new BinaryArithmeticOperate(op::MUL, $1, $3); }
   | ar "/" ar  { $$ = new BinaryArithmeticOperate(op::DIV, $1, $3); }
   | ar "//" ar { $$ = new BinaryArithmeticOperate(op::IDIV, $1, $3); }
   | "+" ar %prec UNARY { $$ = $2; }
   | "-" ar %prec UNARY { $$ = new UnaryArithmeticOperate(op::NEGATE, $2); }
   | ar "^" ar    { $$ = new BinaryArithmeticOperate(op::EXP, $1, $3); }
   | "(" ar ")"   { $$ = $2; }
   | NAME "(" expr_list ")" { $$ = new Call($1, $3); }

/* name : NAME    { $$ = NameRef($1); } */

type : I1      { $$ = new Int1();      }
     | I8      { $$ = new Int8();      }
     | I16     { $$ = new Int16();     }
     | I32     { $$ = new Int32();     }
     | I64     { $$ = new Int64();     }
     | F16     { $$ = new Half();      }
     | F32     { $$ = new Float();     }
     | F64     { $$ = new Double();    }
     | CAPNAME { $$ = new TypeRef($1); }

%%

void kaleido::parser::KaleidoParser::error (const location_type& l, const std::string& m) {
    driver.error (l, m);
}
