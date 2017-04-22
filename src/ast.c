#include "ast.h"

void init_ast()
{
    mem.heapBasePtr     = 0x100;
    mem.heapDepth       = 0;
    mem.stackBasePtr    = 0;
    mem.stackDepth      = 0;

    emitInitial(stdout, &mem);
}

struct ast *newast(int nodetype, struct ast *l, struct ast *r)
{
    struct ast *a = malloc(sizeof(struct ast));

    if(!a)
    {
        yyerror("Could not allocate sufficient memory\n");
        exit(-1);
    }

    a->nodetype = nodetype;
    a->l = l;
    a->r = r;

    return a;
}

struct ast *newnum(int value)
{
    struct numval *a = malloc(sizeof(struct numval));

    if(!a)
    {
        yyerror("Could not allocate sufficient memory\n");
        exit(-1);
    }

    a->nodetype = 'K';
    a->number = value;

    return (struct ast *)a;
}

struct ast *newref(struct symbol *s)
{
    struct symref *a = malloc(sizeof(struct symref));

    if(!a) {
        yyerror("Out of space");
        exit(0);
    }
    a->nodetype = 'N';
    a->s = s;
    return (struct ast *)a;
}

struct ast *newasgn(struct symbol *s, struct ast *v)
{
    struct symasgn *a = malloc(sizeof(struct symasgn));

    if(!a) {
        yyerror("out of space");
        exit(0);
    }   

    a->nodetype = '=';
    a->s = s;
    a->v = v;
    return (struct ast*)a;
}

void eval_ast(struct ast *a)
{
    switch(a->nodetype)
    {
        case 'K':   emitCode(stdout, DEFINE_LITERAL, a, &mem);
                    break;
        case '+':   eval_ast(a->r);
                    eval_ast(a->l);
                    break;
        case '-':   eval_ast(a->r);
                    eval_ast(a->l);
                    break;
        case 'N':   break;
        case '=':   eval_ast( ((struct symasgn *)a)->v );
                    emitCode(stdout, ASSIGN, a, &mem);
                    break;
        default:    printf("Error: unknown nodetype in AST\n");
                    
    } 
}
