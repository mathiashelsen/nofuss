MOV	R0	0 A R0
MOV	R0	256	A	R4
// Pushing literal 5 onto the stack
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	5	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (2) to 256
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Pushing literal 1 onto the stack
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	1	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (3) to 257
ADD	R4	1	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to retrieve value from 256 and store on the stack (2)
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R1	A	*R0 +cmp
ADDS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


// If/else jump for If/Else number 0
MOV	R0	_IfLabel_0	NZ	PC
MOV	R0	_ElseLabel_0	Z	PC


// IF block for If/Else number 0
#_IfLabel_0

// Pushing literal 6 onto the stack
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	6	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (5) to 256
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


// Jump the final for If/Else number 0
MOV	R0	_IfFinalLabel_0	A	PC


// ELSE block for If/Else number 0
#_ElseLabel_0

// Pushing literal 7 onto the stack
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	7	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (6) to 256
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to retrieve value from 257 and store on the stack (5)
ADD	R4	1	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R1	A	*R0 +cmp
ADDS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


// If/else jump for If/Else number 1
MOV	R0	_IfLabel_1	NZ	PC
MOV	R0	_ElseLabel_1	Z	PC


// IF block for If/Else number 1
#_IfLabel_1

// Pushing literal 4 onto the stack
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	4	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (8) to 256
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


// Jump the final for If/Else number 1
MOV	R0	_IfFinalLabel_1	A	PC


// ELSE block for If/Else number 1
#_ElseLabel_1

// Pushing literal 3 onto the stack
// Incrementing stack pointer and writing value to MEM
ADD	R0	1	A	R0
MOV	R0	3	A	*R0 +cmp
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
// Going to store value from stack (9) to 256
ADD	R4	0	A	R1
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0
MOV	R0	*R0	A	*R1 +cmp
SUBS	R0	1	A	R0
MOV	R0	R0	N	R0
MOV	R0	R0	N	R0


//Closing the If/Else number 1
#_IfFinalLabel_1



//Closing the If/Else number 0
#_IfFinalLabel_0

