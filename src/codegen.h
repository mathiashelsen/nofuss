#ifndef _CODEGEN_H
#define _CODEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symtable.h"

#define NOP_STR "MOV\tR0\tR0\tN\tR0\n"

FILE *fp;

void emitInitial(struct memoryState *mem);
void emitCode(enum emitType type, struct ast *a, struct memoryState *mem);

#endif
