%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include "symtable.h"
    #include "ast.h"

%}

%union{
    struct ast *a;
    int d;
    struct symbol *s;
}

%token <d> NUMBER
%token <s> NAME

%type <a> statement exp

%right '='
%left '+' '-'
%nonassoc '|' UMINUS

%initial-action{
    init_ast();
};

%%

program:
    | program ';' statement { eval_ast($3); }
    ;

statement: NAME '=' exp  { $$ = newasgn($1, $3); }
    ;

exp: exp '+' exp    { $$ = newast('+', $1, $3); }
    | exp '-' exp   { $$ = newast('-', $1, $3); }
    | '(' exp ')'   { $$ = $2; }
    | NUMBER        { $$ = newnum($1); }
    | NAME          { $$ = newref($1); }
    ;

%%
