#ifndef _SYMTABLE_H
#define _SYMTABLE_H

struct symbol {
    char *name;
    int allocated;
    int heapAddr;
};

#define NHASH 9997
struct symbol symtable[NHASH];
struct symbol *lookup(char *);

#endif
