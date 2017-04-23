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

%token IF ELSE
%token <d> NUMBER
%token <s> NAME

%type <a> statement statementList codeblock exp

%right '='
%left '+' '-'
%nonassoc '|' UMINUS

%initial-action{
    
    init_ast();
};

%%

program:
    | program statementList             { eval_ast($2); }
    ;

codeblock:                              { $$ = 0; }
    | '{' statementList '}'             { $$ = $2; }
    ;

statementList:                          { $$ = 0; }
    | statementList statement           { $$ = newast('0', $1, $2); }
    | statement                         { $$ = $1; }
    ;

statement: NAME '=' exp ';'             { $$ = newasgn($1, $3); }
    | IF exp codeblock ELSE codeblock   { $$ = newAstNodeIF($2, $3, $5); }
    ;

exp: exp '+' exp                        { $$ = newast('+', $1, $3); }
    | exp '-' exp                       { $$ = newast('-', $1, $3); }
    | '(' exp ')'                       { $$ = $2; }
    | NUMBER                            { $$ = newnum($1); }
    | NAME                              { $$ = newref($1); }
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
