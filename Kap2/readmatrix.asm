@
@ readmatrix.asm
@
readmatrix:	LDR	R0,i		@ R0 = i
		LSL	R1,R0,#1	@ R1 = i*2
		ADD	R0,R1,R0	@ R0 = i*(2+1)
		LDR	R1,j		@ R1 = j
		ADD	R0,R0,R1	@ R0 = (i*3)+j
		LDR	R1,=m3		@ R1 = &m3[0]
		LDR	R0,[R1,R0]	@ R0 = m3[i][j]
		LDR	R1,=ch		@ R1 = &ch
		STRB	R0,[R1]		@ ch = R0

		.ALIGN
i:		.SPACE	4
j:		.SPACE	4
m3:		.BYTE	1,2,3,4,5,6,7,8,9
ch:		.SPACE	1

