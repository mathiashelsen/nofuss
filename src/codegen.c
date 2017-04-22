#include "codegen.h"
// TODO: Make sure all function operations (e.g. excluding stack increment),
// update the status register. This will come in handy for if/else and while
// loops
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
            printf("Pushing literal %d onto the stack\n", ptr->number);
            mem->stackDepth++;
            /*
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
            */
            }
            break;
        case ASSIGN: ;
            {
            struct symbol *ptr = ((struct symasgn *)a)->s; 
            printf("Got symbol at %p\n", ptr);
            //mem->stackDepth--;
            if(ptr->allocated)
            {
                printf("Symbol was allocated\n");
                printf("Going to store value from stack (%d) to %d\n", 
                    mem->stackBasePtr + mem->stackDepth,
                    ptr->heapAddr);
                mem->stackDepth--;
            }
            else
            {
                printf("Have to allocate symbol on the heap\n"); 
                printf("Going to store value from stack (%d) to %d\n",
                    mem->stackBasePtr + mem->stackDepth,
                    mem->heapBasePtr + mem->heapDepth);
                ptr->allocated = 1;
                mem->heapDepth++;
                mem->stackDepth--;
            }
            }
            break;

        case RECALL: ;
            {
            //mem->stackDepth++;
            struct symbol *ptr = ((struct symref *)a)->s; 
            if(ptr->allocated)
            {
                printf("Symbol was allocated\n");
                printf("Going to retrieve value from %d and store on the stack (%d)\n", 
                    ptr->heapAddr,
                    mem->stackBasePtr + mem->stackDepth);
                mem->stackDepth++;
            }
            }
            break;
        default:
            break;
    }
};
