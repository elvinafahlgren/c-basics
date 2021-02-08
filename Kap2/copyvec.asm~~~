@
@ copyvec.asm
@
start:		LDR	R0,=intvec
		LDR	R1,=shortvec
		MOV	R2,#8
		BL	copyvec
		B	start

copyvec:	PUSH	{R4,R5}		@
		MOV	R3,#0		@ i = 1
copyvec1:	CMP	R3,R2		@ i < size
		BGE	copyvec2		
		LSL	R5,R3,#1	@ R5 = i*2
		LDRSH	R4,[R1,R5]	@ R4 = src[i]
		SXTH	R4,R4		@ teckenutvidga
		LSL	R5,R3,#2	@ R5 = i*4
		STR	R4,[R0,R5]	@ dest[i] = R4
		ADD	R3,R3,#1	@ i = i+1
		B	copyvec1
copyvec2:	POP	{R5,R4}
		BX	LR

		.ALIGN
@ Nästa direktiv är bara en utfyllnad för att data skall hamna på adress 0x20000030.
@ Det blir då lättare att kontrollera resultatet av funktionen.
		.SPACE	8
intvec:		.SPACE	32
shortvec:	.HWORD	1,2,3,4,-1,-2,-3,-4



