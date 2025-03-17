%{
#include "analyzer.h"

token_t yylval;
%}

%option noyywrap
%option header-file="src/lexer.h"

%%
[0-9]+(\.[0-9]+)? {
    yylval.info = VALUE;
    yylval.value = stod(yytext);
    return VALUE;
}
[x-z] {
    yylval.info = VARIABLE;
    yylval.value = yytext[0];
    return VARIABLE;
}
\( { return OPENING_BR; }
\) { return CLOSING_BR; }
\+ {return ADD;}
\- { return SUBTRACT; }
\* { return MULTIPLY; }
\/ { return DIVISION; }
[ \t\n]   {}
. {return UNKNOWN; }

%%
