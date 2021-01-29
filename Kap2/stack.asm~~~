@ stack.asm
start:	BL	sub
	B	start

sub:	PUSH	{LR}
	MOV	R0,#0x10
	PUSH	{R0}
	BL	sub2
	POP	{R0}
	POP	{PC}

sub2:	PUSH	{R7}
	MOV	R7,SP
	LDR	R1,[R7,#4]
	POP	{R7}
	BX	LR