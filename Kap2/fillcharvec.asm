@
@ fillcharvec.asm
@
start:	MOV	R0,#0		@ i = 0
	LDR	R1,=ca		@ R1 = &ca[0]

for:	CMP	R0,#0xA		@ i < sizeof(ca)
	BGE	forend
	STRB	R0,[R1,R0]	@ ca[i] = i
	ADD	R0,#1		@i = i + 1
	B	for
	
forend:	@MOV	R1,#5		@ R1
	MOV	R0,#0xFF
	STRB	R0,[R1,#5]	@ ca[5] = 0xFF;

	
ca:	.SPACE	10

