
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

#include "ast.h"
#include "symtable.h"

extern int yylineno;
extern FILE *fp;
void yyerror(char *s, ...);

int main(int argc, char **argv)
{ 
    fp = NULL;

    if(argc == 1)
    {
        fp = fopen("default.ss", "w");
    } 
    else if(argc == 2)
    {
        fp = fopen(argv[1], "w"); 
    }
    else
    {
        printf("Too many arguments\n");
        return -1;
    }

    return yyparse();

    fclose(fp);
}

void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error\n", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}
