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

name    [a-z][a-zA-Z_0-9]*(\?|!)?'+
capname [a-zA-Z][a-zA-Z_0-9]*
int     [0-9]+
float   [0-9]+\.[0-9]+
blank   [ \t]
semi    ;

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
{semi}+  { loc.step(); }

[\n]+    { loc.lines (yyleng); loc.step(); }

%{
#define RET_TK(type) return kaleido::parser::KaleidoParser::type (loc)
%}

"-"      { RET_TK(make_MINUS);  }
"+"      { RET_TK(make_PLUS);   }
"*"      { RET_TK(make_STAR);   }
"/"      { RET_TK(make_DIV);  }
"//"      { RET_TK(make_IDIV);  }
"^"      { RET_TK(make_EXP);    }
"="      { RET_TK(make_ASSIGN); }
"("      { RET_TK(make_LPAREN); }
")"      { RET_TK(make_RPAREN); }
"{"      { RET_TK(make_LBRACE); }
"}"      { RET_TK(make_RBRACE); }
"<"      { RET_TK(make_LANGLE); }
">"      { RET_TK(make_RANGLE); }
"=="     { RET_TK(make_EQ);     }
"!="     { RET_TK(make_NE);     }
"<="     { RET_TK(make_LE);     }
">="     { RET_TK(make_GE);     }
","      { RET_TK(make_COMMA);  }
"and"    { RET_TK(make_AND);    }
"not"    { RET_TK(make_NOT);    }
"xor"    { RET_TK(make_XOR);    }
"or"     { RET_TK(make_OR);     } 
"for"    { RET_TK(make_FOR);    }
"from"   { RET_TK(make_FROM);   }
"to"     { RET_TK(make_TO);     }
"step"   { RET_TK(make_STEP);   }
"set"    { RET_TK(make_SET);    }
"import" { RET_TK(make_IMPORT); }
"module" { RET_TK(make_MODULE); }
"return" { RET_TK(make_RET);    }
"if"     { RET_TK(make_IF);     }
"else"   { RET_TK(make_ELSE);   }

%{
#undef RET_TK
%}

{int}     { errno = 0;
            int64_t n = strtol (yytext, NULL, 10);
            if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
               driver.error (loc, "integer is out of range");
            return kaleido::parser::KaleidoParser::make_INTEGER(n, loc);
          }

{float}   { errno = 0;
            double n = strtod (yytext, NULL);
            return kaleido::parser::KaleidoParser::make_FLOAT(n, loc);
          }

{name}    { return kaleido::parser::KaleidoParser::make_NAME(yytext, loc); }
{capname} { return kaleido::parser::KaleidoParser::make_CAPNAME(yytext, loc); }

.         { driver.error (loc, "invalid character"); }

<<EOF>>   { return kaleido::parser::KaleidoParser::make_END(loc); }

%%

void kaleido::parser::KaleidoDriver::scan_begin() {
    yy_flex_debug = trace_scanning;
    if (parse_on_the_fly) {
        FILE *tmp = std::tmpfile();
        const char *code_buffer = code.c_str();
        std::fputs(code_buffer, tmp);
        std::fflush(tmp);
        std::rewind(tmp);
        yyin = tmp;
    } else {
        if (file.empty() || file == "-")
        yyin = stdin;
        else if (!(yyin = fopen(file.c_str(), "r"))) {
            error("cannot open " + file + ": " + strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
}

void kaleido::parser::KaleidoDriver::scan_end() {
    fclose(yyin);
}
