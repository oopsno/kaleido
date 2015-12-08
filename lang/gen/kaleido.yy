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

%type <Arithmetic*> ar;
%type <Boolean*>    bool;
%type <Type*>       type;
%type <AST*>        name;

%%

%left  "or" "xor";
%left  "and";
%right "not";
%left  ">" "<" "==" ">=" "<=";
%left  "+" "-";
%left  "*" "/" "//";
%precedence UNARY;
%right "^";

%start top_level;

/* top-level statements */
top_level : defun
          | stmt
          | modef  
          | imp  

/* module */
modef : "module" module_name

/* import */
imp : "import" module_name

module_name : CAPNAME
            | module_name "." CAPNAME

/* function */
defun : type name "(" var_decl_list ")" func_body
      | type name "(" ")" func_body

func_body : "{" "}"
          | "{" stmt_list "}"

var_decl : type name

var_decl_list : var_decl
              | var_decl_list "," var_decl

/* loop */
loop : FOR name FROM ar TO ar STEP ar block
     | FOR name FROM ar TO ar block

/* statement */
stmt : assign
     | var_def
     | loop
     | block
     | cond

stmt_list : stmt
          | stmt_list stmt

block : "{" stmt_list "}"

/* assign */
assign : name "=" ar

/* variable define */
var_def : type var_def_list

var_def_list : assign
             | name
             | var_def "," assign
             | var_def "," name

/* if-else */
%precedence "if";
%precedence "else";
cond : "if" bool stmt
     | "if" bool stmt "else" stmt;

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
   | ar "^" ar  { $$ = new BinaryArithmeticOperate(op::EXP, $1, $3); }
   | "(" ar ")"  { $$ = $2; }

name : NAME    { $$ = NameRef($1); }

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
