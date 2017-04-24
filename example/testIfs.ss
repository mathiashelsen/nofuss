MOV	R0	0 A R0
MOV	R0	100	A	R4
// Pushing literal 5 onto the stack (0)
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	5	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (1) to 100
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Pushing literal 1 onto the stack (0)
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	1	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (1) to 101
ADD	R4	1	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to retrieve value from 100 and store on the stack (0)
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R1	A	*R0 +cmp
ADD	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


// If/else jump for If/Else number 0
MOV	R0	Label_If_0	NZ	PC
MOV	R0	Label_Else_0	Z	PC


// IF block for If/Else number 0
#label Label_If_0

// Pushing literal 6 onto the stack (1)
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	6	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (2) to 100
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to retrieve value from 101 and store on the stack (1)
ADD	R4	1	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R1	A	*R0 +cmp
ADD	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


// If/else jump for If/Else number 1
MOV	R0	Label_If_1	NZ	PC
MOV	R0	Label_Else_1	Z	PC


// IF block for If/Else number 1
#label Label_If_1

// Going to retrieve value from 100 and store on the stack (2)
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R1	A	*R0 +cmp
ADD	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Pushing literal 1 onto the stack (3)
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	1	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Add two values on the stack, pop one and store result on the stack
SUBS	R0	1	A	R0
MOV	R0	R0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
ADD	*R0	*R1	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (3) to 101
ADD	R4	1	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


// Jump the final for If/Else number 1
MOV	R0	Label_IfFinal_1	A	PC


// ELSE block for If/Else number 1
#label Label_Else_1

// Pushing literal 1 onto the stack (2)
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	1	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (3) to 101
ADD	R4	1	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


//Closing the If/Else number 1
#label Label_IfFinal_1



// Jump the final for If/Else number 0
MOV	R0	Label_IfFinal_0	A	PC


// ELSE block for If/Else number 0
#label Label_Else_0

// Pushing literal 7 onto the stack (2)
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	7	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (3) to 100
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to retrieve value from 101 and store on the stack (2)
ADD	R4	1	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R1	A	*R0 +cmp
ADD	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


// If/else jump for If/Else number 2
MOV	R0	Label_If_2	NZ	PC
MOV	R0	Label_Else_2	Z	PC


// IF block for If/Else number 2
#label Label_If_2

// Pushing literal 4 onto the stack (3)
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	4	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (4) to 100
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


// Jump the final for If/Else number 2
MOV	R0	Label_IfFinal_2	A	PC


// ELSE block for If/Else number 2
#label Label_Else_2

// Pushing literal 3 onto the stack (3)
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	3	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (4) to 100
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


//Closing the If/Else number 2
#label Label_IfFinal_2



//Closing the If/Else number 0
#label Label_IfFinal_0

