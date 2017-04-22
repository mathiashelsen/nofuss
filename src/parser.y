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
    | program statement { eval_ast($2); }
    ;

statement: NAME '=' exp ';'  { $$ = newasgn($1, $3); }
    ;

exp: exp '+' exp    { $$ = newast('+', $1, $3); }
    | exp '-' exp   { $$ = newast('-', $1, $3); }
    | '(' exp ')'   { $$ = $2; }
    | NUMBER        { $$ = newnum($1); }
    | NAME          { $$ = newref($1); }
    ;
/*
    | &NAME         { $$ = newptr($1); } -> look up symbol, put address on stack
        MOV x %d A *R0
    | *(exp)        { $$ = newdeptr($2); } -> calc expression, look up value at
        address=stack, put value on stack
        MOV x *R0 A R1
        MOV x *R1 A *R0
*/

%%
