#ifndef _AST_H
#define _AST_H

#include "symtable.h"

struct ast{
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct numval{
    int nodetype;
    int number;
};

enum emitType {
    NEW_NUMBER,
    ADD,
    SUB,
    UNITARY_MINUS,
    RECALL_VALUE,
    STORE_VALUE
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

#endif
