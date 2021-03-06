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
            fprintf(fp, "// Pushing literal %d onto the stack (%d)\n", ptr->number, mem->stackDepth);
            mem->stackDepth++;
            
            if(mem->stackDepth < MAX_STACK & ptr->number < 2048)
            {
                fprintf(fp, "// Incrementing stack pointer and writing value to MEM\n");

                // Write value to old pointer
                fprintf(fp, "MOV\tR0\t%d\tA\t*R0 +cmp\n", ptr->number);
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");

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
                fprintf(fp, "SUBS\tR0\t1\tA\tR0\n");
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "MOV\tR0\t*R0\tA\t*R1 +cmp\n");
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
                fprintf(fp, "SUBS\tR0\t1\tA\tR0\n");
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "MOV\tR0\t*R0\tA\t*R1 +cmp\n");
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);

                (mem->heapDepth)++;
                (mem->stackDepth)--;


            }
            }
            break;

        case ASSIGN_PTR: ;
            {
                fprintf(fp, "// Going to store value from stack (%d) to address at stack-1\n");

                mem->stackDepth--;
                
                fprintf(fp, "SUBS\tR0\t1\tA\tR0\n");
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "MOV\tR0\t*R0\tA\tR1\n");
                fprintf(fp, "SUBS\tR0\t1\tA\tR0\n");
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "MOV\tR0\t*R0\tA\tR2\n");
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "MOV\tR1\tR2\tA\t*R1 +cmp\n");
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
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
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");
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
                fprintf(fp, "SUBS\tR0\t2\tA\tR0\n"); // Pop stack, R0 - 1 -> R0
                fprintf(fp, "SUBS\tR0\t1\tA\tR1\n"); // Pop stack, R0 - 1 -> R0
                //fprintf(fp, "MOV\tR0\tR0\tA\tR1\n"); // stack+1 -> R1 
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "ADD\t*R0\t*R1\tA\t*R0 +cmp\n"); // Math thingy -> *R0
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");

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
                fprintf(fp, "SUBS\tR0\t2\tA\tR0\n"); // Pop stack, R0 - 1 -> R0
                fprintf(fp, "MOV\tR0\tR0\tA\tR1\n"); // stack+1 -> R1 
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "SUBS\t*R0\t*R1\tA\t*R0 +cmp\n"); // Math thingy -> *R0
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");

                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);

            }
            break;
        case AND: ;
            {
                (mem->stackDepth)--;
                fprintf(fp, "// Add two values on the stack, pop one and store result on the stack\n");
                fprintf(fp, "SUBS\tR0\t2\tA\tR0\n"); // Pop stack, R0 - 1 -> R0
                fprintf(fp, "MOV\tR0\tR0\tA\tR1\n"); // stack+1 -> R1 
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "AND\t*R0\t*R1\tA\t*R0 +cmp\n"); // Math thingy -> *R0
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");

                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);

            }
            break;
        case OR: ;
            {
                (mem->stackDepth)--;
                fprintf(fp, "// Add two values on the stack, pop one and store result on the stack\n");
                fprintf(fp, "SUBS\tR0\t2\tA\tR0\n"); // Pop stack, R0 - 1 -> R0
                fprintf(fp, "MOV\tR0\tR0\tA\tR1\n"); // stack+1 -> R1 
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "OR\t*R0\t*R1\tA\t*R0 +cmp\n"); // Math thingy -> *R0
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");

                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);

            }
            break;
        case XOR: ;
            {
                (mem->stackDepth)--;
                fprintf(fp, "// Add two values on the stack, pop one and store result on the stack\n");
                fprintf(fp, "SUBS\tR0\t2\tA\tR0\n"); // Pop stack, R0 - 1 -> R0
                fprintf(fp, "MOV\tR0\tR0\tA\tR1\n"); // stack+1 -> R1 
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "XOR\t*R0\t*R1\tA\t*R0 +cmp\n"); // Math thingy -> *R0
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");

                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);

            }
            break;
        case BSL: ;
            {
                (mem->stackDepth)--;
                fprintf(fp, "// Add two values on the stack, pop one and store result on the stack\n");
                fprintf(fp, "SUBS\tR0\t2\tA\tR0\n"); // Pop stack, R0 - 1 -> R0
                fprintf(fp, "MOV\tR0\tR0\tA\tR1\n"); // stack+1 -> R1 
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "BSL\t*R0\t*R1\tA\t*R0 +cmp\n"); // Math thingy -> *R0
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");

                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);

            }
            break;
        case BSR: ;
            {
                (mem->stackDepth)--;
                fprintf(fp, "// Add two values on the stack, pop one and store result on the stack\n");
                fprintf(fp, "SUBS\tR0\t2\tA\tR0\n"); // Pop stack, R0 - 1 -> R0
                fprintf(fp, "MOV\tR0\tR0\tA\tR1\n"); // stack+1 -> R1 
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "BSR\t*R0\t*R1\tA\t*R0 +cmp\n"); // Math thingy -> *R0
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");

                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);

            }
            break;
        case NOT: ;
            {
                (mem->stackDepth)--;
                fprintf(fp, "// Add two values on the stack, pop one and store result on the stack\n");
                fprintf(fp, "SUBS\tR0\t1\tA\tR0\n"); // Pop stack, R0 - 1 -> R0
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "NOT\t*R0\t*R0\tA\t*R0 +cmp\n"); // Math thingy -> *R0
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");

                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);

            }
            break;
        case CREATEPTR: ;
            {
            struct symbol *ptr = ((struct pointer *)a)->s; 
            printf("Going to create pointer code \n"); 
            if(ptr->allocated)
            {
                (mem->stackDepth)++;
                fprintf(fp, "// Adding symbol address on the stack\n");
                fprintf(fp, "ADD\tR4\t%d\tA\tR1\n", ptr->heapAddr - mem->heapBasePtr);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "%s", NOP_STR);
                fprintf(fp, "MOV\tR0\tR1\tA\t*R0\t+cmp\n");
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");
                fprintf(fp, NOP_STR);
                fprintf(fp, NOP_STR);
                fprintf(fp, NOP_STR);
            }
            else
            {
                yyerror("Symbol was not yet allocated and/or defined.\n");
            }
            }
            break;
        case DEREF: ;
            {
                fprintf(fp, "SUBS\tR0\t1\tA\tR0\n");
                fprintf(fp, NOP_STR);
                fprintf(fp, NOP_STR);
                fprintf(fp, NOP_STR);
                fprintf(fp, "MOV\tR0\t*R0\tA\tR1\n");
                fprintf(fp, NOP_STR);
                fprintf(fp, NOP_STR);
                fprintf(fp, NOP_STR);
                fprintf(fp, "MOV\tR0\t*R1\tA\t*R0\n");
                fprintf(fp, "ADD\tR0\t1\tA\tR0\n");
                fprintf(fp, NOP_STR);
                fprintf(fp, NOP_STR);
                fprintf(fp, NOP_STR);
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
    fprintf(fp, "SUBS\tR0\t1\tA\tR0\n"); // Pop stack, R0 - 1 -> R0
    fprintf(fp, "MOV\tR0\tLabel_If_%d\tNZ\tPC\n", i);
    fprintf(fp, "MOV\tR0\tLabel_Else_%d\tZ\tPC\n", i);
};

void emitIfFinalJmp( int i )
{
    fprintf(fp, "\n\n// Jump the final for If/Else number %d\n", i);
    fprintf(fp, "MOV\tR0\tLabel_IfFinal_%d\tA\tPC\n", i);
}

void emitIfLabel( int i )
{
    fprintf(fp, "\n\n// IF block for If/Else number %d\n", i);
    fprintf(fp, "#label Label_If_%d\n\n", i);
}
void emitElseLabel( int i)
{
    fprintf(fp, "\n\n// ELSE block for If/Else number %d\n", i);
    fprintf(fp, "#label Label_Else_%d\n\n", i);
}

void emitIfFinalLabel( int i )
{
    fprintf(fp, "\n\n//Closing the If/Else number %d\n", i);
    fprintf(fp, "#label Label_IfFinal_%d\n\n", i);
}
