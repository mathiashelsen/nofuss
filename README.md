# nofuss
Compiler for the WolfCore cpu architecture

Does not support:
- functions because
- ... it does not support scoping (yet, might be handy)
- any other datatype then signed int
- syntax checking (it will simply say "syntax error", lovely...)
- pretty coding: this thing (the compiler itself) uses external variables all over the place, and does not free memory after allocation
- dynamic memory (might be interesting to implement, so lets see in the future)

It will support (hopefully):
- if/else construction (check, done!)
- while loops
- pointers to variables

## How does it work:
It is a stack based machine: all expressions will be evaluated by pushing values on the stack (literals, previous results or things copied from hte heap), and popping them (copy to the heap, evaluate if/else or while loops).

## Registers used:
- R0: stack register, this is a ptr to an "empty box" not to the latest value added
- R1: second operand register for operations requiring two inputs (add, bit shift, etc.)
- R4: value of heap base
