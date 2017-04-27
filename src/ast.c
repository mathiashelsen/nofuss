#include "ast.h"

void init_ast()
{
    mem.heapBasePtr     = 100;
    mem.heapDepth       = 0;
    mem.stackBasePtr    = 0;
    mem.stackDepth      = 0;

    mem.numberOfIFs     = 0;

    emitInitial(&mem);
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

struct ast *newptr(struct symbol *s)
{
    struct pointer *a = malloc(sizeof(struct pointer));

    if(!a) {
        yyerror("out of space");
        exit(0);
    }   

    a->nodetype = '&';
    a->s = s;

    return (struct ast*)a;
}

struct ast *newdeptr(struct ast *v)
{
    struct derefPointer *a = malloc(sizeof(struct derefPointer));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }   

    a->nodetype = '*';
    a->v = v;

    return (struct ast*)a;

}

struct ast *newAstNodeIF(struct ast *cond, struct ast *ifNode,
    struct ast *elseNode)
{
    struct astNodeIF *a = malloc(sizeof(struct astNodeIF));

    if(!a) {
        yyerror("Out of space");
        exit(0);
    }

    a->nodetype = '?';
    a->cond     = cond;
    a->ifNode   = ifNode;
    a->elseNode = elseNode; 

    return (struct ast*)a;
}

void eval_ast(struct ast *a)
{
    //printf("Node type: %c\n", a->nodetype);
    switch(a->nodetype)
    {
        case '0':   eval_ast(a->l);
                    eval_ast(a->r);
                    break;
        case 'K':   emitCode(DEFINE_LITERAL, a, &mem);
                    break;
        case '+':   eval_ast(a->l);
                    eval_ast(a->r);
                    emitCode(ADD, a, &mem);
                    break;
        case '-':   eval_ast(a->l);
                    eval_ast(a->r);
                    emitCode(SUB, a, &mem);
                    break;
        case 'A':   eval_ast(a->l);
                    eval_ast(a->r);
                    emitCode(AND, a, &mem);
                    break;
        case 'O':   eval_ast(a->l);
                    eval_ast(a->r);
                    emitCode(OR, a, &mem);
                    break;
        case 'X':   eval_ast(a->l);
                    eval_ast(a->r);
                    emitCode(XOR, a, &mem);
                    break;
        case 'L':   eval_ast(a->l);
                    eval_ast(a->r);
                    emitCode(BSL, a, &mem);
                    break;
        case 'R':   eval_ast(a->l);
                    eval_ast(a->r);
                    emitCode(BSR, a, &mem);
                    break;
        case '!':   eval_ast(a->l);
                    emitCode(NOT, a, &mem);
                    break;
        case '*':   eval_ast( ((struct derefPointer*)a)->v );
                    emitCode(DEREF, a, &mem);
                    break;
        case '&':   emitCode(CREATEPTR, a, &mem);
                    break;
        case 'N':   emitCode(RECALL, a, &mem);
                    break;
        case '=':   eval_ast( ((struct symasgn *)a)->v );
                    emitCode(ASSIGN, a, &mem);
                    break;
        case '?':   ;
                    int currentLabel = mem.numberOfIFs;
                    mem.numberOfIFs++;

                    eval_ast( ((struct astNodeIF *)a)->cond );

                    emitIfElseJmp( currentLabel );
                    emitIfLabel( currentLabel );

                    eval_ast( ((struct astNodeIF *)a)->ifNode );    

                    emitIfFinalJmp( currentLabel );
                    emitElseLabel( currentLabel );

                    eval_ast( ((struct astNodeIF *)a)->elseNode );

                    emitIfFinalLabel( currentLabel );
                    break;
        default:    fprintf("Error: unknown nodetype \"%c\" in AST\n", a->nodetype);
                    
    } 
}
