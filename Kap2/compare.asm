@
@ compare.asm
@
start:	LDR	R0,=0x55555555	@ initiera port D som utport
	LDR	R1,=0x40020C00
	STR	R0,[R1]
	LDR	R5,=0x40020C14	@ adressen till port D:s ut-dataregister till R5
	LDR	R6,=0x40021010	@ adressen till port E:s in-dataregister till R6

main:	LDRB	R0,[R6]		@ l�s operand 1 till R0
	SXTB	R0,R0
	LDRB	R1,[R6,#1]	@ l�s operand 2 till R1
	SXTB	R1,R1
	CMP	R0,R1		@ op1 - op2 -> APSR
	BGT	main_1		@ hopp om ICKE negative
	MOV	R0,#0		
	B	main_2
	
main_1:	MOV	R0,#0xFF

main_2:	STRB	R0,[R5]
	B	main