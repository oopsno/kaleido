%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include "driver.hpp"
#include "parser.hpp"
#undef yywrap
#define yywrap() 1
#define register      // Deprecated in C++11.

    // The location of the current token.
    static kaleido::parser::location loc;
%}

%option noyywrap nounput batch debug noinput
%option outfile="lexer.cpp" header-file="lexer.hpp"

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t]

%{
    // Code run each time a pattern is matched.
    # define YY_USER_ACTION  loc.columns (yyleng);
%}

%%

%{
    // Code run each time yylex is called
    loc.step ();
%}

{blank}+ { loc.step(); }
[\n]+    { loc.lines (yyleng); loc.step(); }

"-"      { return  kaleido::parser::KaleidoParser::make_MINUS(loc);  }
"+"      { return  kaleido::parser::KaleidoParser::make_PLUS(loc);   }
"*"      { return  kaleido::parser::KaleidoParser::make_STAR(loc);   }
"/"      { return  kaleido::parser::KaleidoParser::make_SLASH(loc);  }
"("      { return  kaleido::parser::KaleidoParser::make_LPAREN(loc); }
")"      { return  kaleido::parser::KaleidoParser::make_RPAREN(loc); }
"="      { return  kaleido::parser::KaleidoParser::make_ASSIGN(loc); }

{int}    { errno = 0;
           long n = strtol (yytext, NULL, 10);
           if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
              driver.error (loc, "integer is out of range");
           return  kaleido::parser::KaleidoParser::make_INTEGER(n, loc);
         }
{id}     { return  kaleido::parser::KaleidoParser::make_IDENTIFIER(yytext, loc); }
.        { driver.error (loc, "invalid character"); }
<<EOF>>  { return  kaleido::parser::KaleidoParser::make_END(loc); }

%%

void kaleido::parser::KaleidoDriver::scan_begin() {
    yy_flex_debug = trace_scanning;
    if (file.empty() || file == "-")
    yyin = stdin;
    else if (!(yyin = fopen(file.c_str(), "r"))) {
        error("cannot open " + file + ": " + strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void kaleido::parser::KaleidoDriver::scan_end() {
    fclose(yyin);
}

