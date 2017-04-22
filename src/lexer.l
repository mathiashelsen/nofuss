%option noyywrap nodefault yylineno
%{
    #include "symtable.h"
    #include "parser.tab.h"
%}

EXP ([Ee][-+]?[0-9]+)

%%
";" |
"=" |
"+" |
"-" |
"(" |
")"         { return yytext[0]; }
[a-zA-Z]    { yylval.s = lookup(yytext); return NAME; }
[0-9]+      { yylval.d = atoi(yytext); return NUMBER; }
"//".*      {}
[ \t\n]     {}
.           { yyerror("Mystery character %c\n", *yytext); }
%%
