#ifndef _AST_H
#define _AST_H

#include "symtable.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_STACK 0x100

enum emitType
{
    DEFINE_LITERAL,
    ASSIGN,
    RECALL,
    ADD,
    SUB,
    AND,
    OR,
    XOR,
    BSL,
    BSR,
    NOT,
    DEREF,
    CREATEPTR
};

// Functions to process the AST
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(int value);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newptr(struct symbol *s);
struct ast *newdeptr(struct ast *v);

// Evaluates the AST
void eval_ast(struct ast *a);

// Initializes global variables (heaps, stacks, etc.)
void init_ast();


struct memoryState
{
    int heapBasePtr;
    int heapDepth;
    int stackBasePtr;
    int stackDepth;

    int numberOfIFs;
} mem;

struct ast{
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct numval{
    int nodetype;
    int number;
};

struct symref{
    int nodetype;
    struct symbol *s;
};

struct symasgn {
    int nodetype;
    struct symbol *s;
    struct ast *v;
};

struct pointer{
    int nodetype;
    struct symbol *s;
};

struct derefPointer{
    int nodetype;
    struct ast *v;
};

struct astNodeIF{
    int nodetype;
    struct ast *cond;
    struct ast *ifNode;
    struct ast *elseNode;
};

#endif
