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
    RET     "return"
    DATA    "data"
;

%token <std::string> NAME
%token <std::string> CAPNAME 
%token <int64_t>     INTEGER
%token <double>      FLOAT
%token <bool>        TRUE
%token <bool>        FALSE

%%

%left  "or" "xor";
%left  "and";
%right "not";
%left  ">" "<" "==" ">=" "<=";
%left  "+" "-";
%left  "*" "/";
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
bool : TRUE
     | FALSE
     | ar "<"  ar
     | ar ">"  ar
     | ar "=>" ar
     | ar "<=" ar
     | ar "==" ar
     | bool "and" bool
     | bool "or"  bool
     | bool "xor" bool
     | "not" bool %prec UNARY
     | "(" bool ")"

/* ar[ithmetic] */
ar : FLOAT
   | INTEGER
   | NAME 
   | ar "+" ar
   | ar "-" ar
   | ar "*" ar
   | ar "/" ar
   | "+" ar %prec UNARY
   | "-" ar %prec UNARY
   | ar "^" ar
   | "(" ar ")" 

name : NAME

type : CAPNAME

%%

void kaleido::parser::KaleidoParser::error (const location_type& l, const std::string& m) {
    driver.error (l, m);
}
