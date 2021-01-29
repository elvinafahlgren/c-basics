@
@ dice.asm
@
start:	
	MOV	R4,#0
	MOV	R5,#0
loop:	BL	dice	@ l�gger returadress i LR
	CMP	R0,#4
	BCC	less
	ADD	R4,#1
	B	start
less:	
	ADD	R5,#1
	B	loop

dice:	LDR	R0,seed
	LDR	R1,a
	MUL	R0,R1
	LDR	R1,c
	ADD	R0,R1
	LDR	R1,m
	AND	R0,R1
	LDR	R1,=seed
	STR	R0,[R1]
	MOV	R1,#0x7
	AND	R0,R1
	BX	LR
	
	

	.ALIGN 4
seed:	.WORD	123456789
a:	.WORD	1103515245
c:	.WORD	12345
m:	.WORD	0x7FFFFFFF	