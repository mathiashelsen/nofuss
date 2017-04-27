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
"{" |
"}" |
"(" |
"&" |
")"         { return yytext[0]; }
"&&"        { return AND_t; }
"||"        { return OR_t; }
"^"         { return XOR_t; }
">>"        { return BSR_t; }
"<<"        { return BSL_t; }
"!"         { return NOT_t; }
"if"        { return IF; }
"else"      { return ELSE; }
[a-zA-Z]    { yylval.s = lookup(yytext); return NAME; }
[0-9]+      { yylval.d = atoi(yytext); return NUMBER; }
"//".*      {}
[ \t\n]     {}
.           { yyerror("Mystery character %c\n", *yytext); }
%%
