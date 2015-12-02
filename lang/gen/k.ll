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

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
float [0-9]+\.[0-9]+
blank [ \t]
semi  ;

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

"-"      { return kaleido::parser::KaleidoParser::make_MINUS(loc);  }
"+"      { return kaleido::parser::KaleidoParser::make_PLUS(loc);   }
"*"      { return kaleido::parser::KaleidoParser::make_STAR(loc);   }
"/"      { return kaleido::parser::KaleidoParser::make_SLASH(loc);  }
"="      { return kaleido::parser::KaleidoParser::make_ASSIGN(loc); }
"("      { return kaleido::parser::KaleidoParser::make_LPAREN(loc); }
")"      { return kaleido::parser::KaleidoParser::make_RPAREN(loc); }
"{"      { return kaleido::parser::KaleidoParser::make_LBRACE(loc); }
"}"      { return kaleido::parser::KaleidoParser::make_RBRACE(loc); }
","      { return kaleido::parser::KaleidoParser::make_COMMA(loc);  }
"for"    { return kaleido::parser::KaleidoParser::make_FOR(loc);    }
"from"   { return kaleido::parser::KaleidoParser::make_FROM(loc);   }
"to"     { return kaleido::parser::KaleidoParser::make_TO(loc);     }
"step"   { return kaleido::parser::KaleidoParser::make_STEP(loc);   }
"set"    { return kaleido::parser::KaleidoParser::make_SET(loc);    }
"import" { return kaleido::parser::KaleidoParser::make_IMPORT(loc); }
"module" { return kaleido::parser::KaleidoParser::make_MODULE(loc); }
"def"    { return kaleido::parser::KaleidoParser::make_DEF(loc);    }
"i64"    { return kaleido::parser::KaleidoParser::make_I64(loc);    }
"f64"    { return kaleido::parser::KaleidoParser::make_F64(loc);    }
"return" { return kaleido::parser::KaleidoParser::make_RET(loc);    }


{int}    { errno = 0;
           int64_t n = strtol (yytext, NULL, 10);
           if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
              driver.error (loc, "integer is out of range");
           return kaleido::parser::KaleidoParser::make_INTEGER(n, loc);
         }
{float}  { errno = 0;
           double n = strtod (yytext, NULL);
           return kaleido::parser::KaleidoParser::make_FLOAT(n, loc);
         }
{id}     { return kaleido::parser::KaleidoParser::make_IDENTIFIER(yytext, loc); }
.        { driver.error (loc, "invalid character"); }
<<EOF>>  { return kaleido::parser::KaleidoParser::make_END(loc); }

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

