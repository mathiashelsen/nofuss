#include "codegen.h"

void emitInitial(FILE *fp, struct memoryState *mem)
{
    // We put R0 to the initial stackPtr;
    char *outStr = malloc(sizeof(char)*1024);
    
    memset(outStr, 0, sizeof(outStr));
    sprintf(outStr, "MOV\tR0\t%d A R0\n", mem->stackBasePtr);
    fprintf(fp, "%s", outStr);
}

void emitCode(FILE *fp, 
    enum emitType type, 
    struct ast *a,
    struct memoryState *mem)
{
    switch(type)
    {
        case DEFINE_LITERAL: ;
            {
            struct numval *ptr = (struct numval *)a; 
            if(mem->stackDepth < MAX_STACK & ptr->number < 2048)
            {
                mem->stackDepth++;
                char *outStr = malloc(sizeof(char)*1024);
                memset(outStr, 0, sizeof(outStr));

                fprintf(fp, "// Incrementing stack pointer and writing value to MEM\n");
                sprintf(outStr, "ADD\tR0\t1\tA\tR0\n");
                fprintf(fp, "%s", outStr);

                // Write value to old pointer
                memset(outStr, 0, sizeof(outStr));
                sprintf(outStr, "MOV\tR0\t%d\tA\t*R0\n", ptr->number);
                fprintf(fp, "%s", outStr);

                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
               
                free(outStr);
            }
            }
            break;
        case ASSIGN: ;
            {
            struct symbol *ptr = ((struct symasgn *)a)->s; 
            if(ptr->allocated)
            {
                printf("Symbol was allocated\n");
                printf("Going to store value from stack (%d) to %d\n", 
                    mem->stackBasePtr + mem->stackDepth,
                    ptr->heapAddr);
            }
            else
            {
                printf("Have to allocate symbol on the heap\n"); 
                printf("Going to store value from stack (%d) to %d\n",
                    mem->stackBasePtr + mem->stackDepth,
                    mem->heapBasePtr + mem->heapDepth);
            }
            }
            break;
        default:
            break;
    }
};
