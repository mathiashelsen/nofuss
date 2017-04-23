#include "codegen.h"
// TODO: Make sure all function operations (e.g. excluding stack increment),
// update the status register. This will come in handy for if/else and while
// loops
void emitInitial(struct memoryState *mem)
{
    // We put R0 to the initial stackPtr;
    char *outStr = malloc(sizeof(char)*1024);
    
    memset(outStr, 0, sizeof(outStr));
    sprintf(outStr, "MOV\tR0\t%d A R0\n", mem->stackBasePtr);
    fprintf(fp, "%s", outStr);
    fprintf(fp, "MOV\tR0\t%d\tA\tR4\n", mem->heapBasePtr);
}

void emitCode(
    enum emitType type, 
    struct ast *a,
    struct memoryState *mem)
{
    switch(type)
    {
        case DEFINE_LITERAL: ;
            {
            struct numval *ptr = (struct numval *)a; 
            fprintf(fp, "// Pushing literal %d onto the stack\n", ptr->number);
            mem->stackDepth++;
            
            if(mem->stackDepth < MAX_STACK & ptr->number < 2048)
            {
                mem->stackDepth++;

                fprintf(fp, "// Incrementing stack pointer and writing value to MEM\n");
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");

                // Write value to old pointer
                fprintf(fp, "MOV\tR0\t%d\tA\t*R0 +cmp\n", ptr->number);

                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
               
            }
           
            }
            break;
        case ASSIGN: ;
            {
            struct symbol *ptr = ((struct symasgn *)a)->s; 
            if(ptr->allocated)
            {
                fprintf(fp, "// Going to store value from stack (%d) to %d\n", 
                    mem->stackBasePtr + mem->stackDepth,
                    ptr->heapAddr);

                mem->stackDepth--;
                
                fprintf(fp, "ADD\tR4\t%d\tA\tR1\n", ptr->heapAddr - mem->heapBasePtr);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "MOV\tR0\t*R0\tA\t*R1 +cmp\n");
                fprintf(fp, "SUBS\tR0\t1\tA\tR0\n");
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
            }
            else
            {
                fprintf(fp, "// Going to store value from stack (%d) to %d\n",
                    mem->stackBasePtr + mem->stackDepth,
                    mem->heapBasePtr + mem->heapDepth);
                ptr->allocated = 1;
                ptr->heapAddr = mem->heapBasePtr + mem->heapDepth;                

                fprintf(fp, "ADD\tR4\t%d\tA\tR1\n", mem->heapDepth);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "MOV\tR0\t*R0\tA\t*R1 +cmp\n");
                fprintf(fp, "SUBS\tR0\t1\tA\tR0\n");
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);

                (mem->heapDepth)++;
                (mem->stackDepth)--;


            }
            }
            break;

        case RECALL: ;
            {
            struct symbol *ptr = ((struct symref *)a)->s; 
            if(ptr->allocated)
            {
                fprintf(fp, "// Going to retrieve value from %d and store on the stack (%d)\n", 
                    ptr->heapAddr,
                    mem->stackBasePtr + mem->stackDepth);
                (mem->stackDepth)++;

                fprintf(fp, "ADD\tR4\t%d\tA\tR1\n", ptr->heapAddr - mem->heapBasePtr);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "MOV\tR0\t*R1\tA\t*R0 +cmp\n");
                fprintf(fp, "ADDS\tR0\t1\tA\tR0\n");
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
            }
            else
            {
                yyerror("Symbol was not yet allocated and/or defined.\n");
            }
            }
            break;
        case ADD: ;
            {
                (mem->stackDepth)--;
                fprintf(fp, "// Add two values on the stack, pop one and store result on the stack\n");
                fprintf(fp, "SUBS\tR0\t1\tA\tR0\n"); // Pop stack, R0 - 1 -> R0
                fprintf(fp, "MOV\tR0\tR0\tA\tR1\n"); // stack+1 -> R1 
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "ADDS\t*R0\t*R1\tA\t*R0 +cmp\n"); // Math thingy -> *R0

                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
            }   
            break;
        case SUB: ;
            {
                (mem->stackDepth)--;
                fprintf(fp, "// Add two values on the stack, pop one and store result on the stack\n");
                fprintf(fp, "SUBS\tR0\t1\tA\tR0\n"); // Pop stack, R0 - 1 -> R0
                fprintf(fp, "MOV\tR0\tR0\tA\tR1\n"); // stack+1 -> R1 
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "SUBS\t*R0\t*R1\tA\t*R0 +cmp\n"); // Math thingy -> *R0

                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);

            }
            break;
        default:
            yyerror("Unknown request to emit code.\n");
            break;
    }
};

void emitIfElseJmp( int i )
{
    fprintf(fp, "\n\n// If/else jump for If/Else number %d\n", i);
    fprintf(fp, "MOV\tR0\t_IfLabel_%d\tNZ\tPC\n", i);
    fprintf(fp, "MOV\tR0\t_ElseLabel_%d\tZ\tPC\n", i);
};

void emitIfFinalJmp( int i )
{
    fprintf(fp, "\n\n// Jump the final for If/Else number %d\n", i);
    fprintf(fp, "MOV\tR0\t_IfFinalLabel_%d\tA\tPC\n", i);
}

void emitIfLabel( int i )
{
    fprintf(fp, "\n\n// IF block for If/Else number %d\n", i);
    fprintf(fp, "#_IfLabel_%d\n\n", i);
}
void emitElseLabel( int i)
{
    fprintf(fp, "\n\n// ELSE block for If/Else number %d\n", i);
    fprintf(fp, "#_ElseLabel_%d\n\n", i);
}

void emitIfFinalLabel( int i )
{
    fprintf(fp, "\n\n//Closing the If/Else number %d\n", i);
    fprintf(fp, "#_IfFinalLabel_%d\n\n", i);
}
