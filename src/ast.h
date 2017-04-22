#ifndef _AST_H
#define _AST_H

#include "symtable.h"

struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(int value);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);

void eval_ast(struct ast *a);

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

enum emitType {
    NEW_NUMBER,
    ADD,
    SUB,
    UNITARY_MINUS,
    RECALL_VALUE,
    STORE_VALUE
};

#endif
