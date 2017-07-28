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
%token AND_t OR_t XOR_t BSL_t BSR_t NOT_t DEREF_t
%token <d> NUMBER
%token <s> NAME

%type <a> statement statementList assignStatement ifStatement exp

%right '='
%left '+' '-' AND_t OR_t XOR_t BSL_t BSR_t
%nonassoc '|' UMINUS NOT_t '&'


%start program

%initial-action{
    init_ast();
};

%%

program
	: '{' statementList '}'				{ eval_ast($2); }
    ;

statementList:                          { $$ = 0; }
    | statementList statement           { $$ = newast('0', $1, $2); }
    ;

statement
	: assignStatement ';'				{ $$ = $1; }		
	| ifStatement						{ $$ = $1; }
	;


exp: exp '+' exp                        { $$ = newast('+', $1, $3); }
    | exp '-' exp                       { $$ = newast('-', $1, $3); }
    | exp AND_t exp                     { $$ = newast('A', $1, $3); }
    | exp OR_t exp                      { $$ = newast('O', $1, $3); }
    | exp XOR_t exp                     { $$ = newast('X', $1, $3); }
    | exp BSL_t exp                     { $$ = newast('R', $1, $3); }
    | exp BSR_t exp                     { $$ = newast('L', $1, $3); }
    | NOT_t exp                         { $$ = newast('!', $2, NULL); }
    | '(' exp ')'                       { $$ = $2; }
    | NUMBER                            { $$ = newnum($1); }
    | NAME                              { $$ = newref($1); }
    ;

assignStatement
	: NAME '=' exp						{ $$ = newasgn($1, $3); }
	;

ifStatement
	: IF '(' exp ')' '{' statementList '}' ELSE  '{' statementList '}'	{ $$ = newIfAst($3, $6, $10); }
	;
