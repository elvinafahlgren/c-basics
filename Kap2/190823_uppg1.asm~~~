
@ a)

@ int j;
j:		.SPACE	4
		.ALIGN

@ char vecc[80];
vecc:		.SPACE	80
		.ALIGN
@ vecc[j]->R0
		LDR	R0,=j
		LDR	R0,[R0]
		LDR	R1,=vecc
		STRB	R0,[R1,R0]

@ b)

a:		.SPACE	4
		.ALIGN
b:		.SPACE	4
		.ALIGN
c:		.SPACE	4
		.ALIGN

@ (a + b * c) << 1
		LDR	R0,=a
		LDR	R0,[R0]		@ R0 = a
		LDR	R1,=b
		LDR	R1,[R1]		@ R1 = b
		LDR	R2,=c
		LDR	R2,[R2]		@ R2 = c
		MUL	R1,R1,R2	@ R1 = b * c
		ADD	R0,R0,R1	@ R0 = a + R0
		LSL	R0,R0,#1
		