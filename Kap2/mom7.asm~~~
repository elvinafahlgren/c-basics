@
@ mom7.asm
@
start:
@ initiera port D och E som utportar
	LDR	R6,=0x55555555
	LDR	R5,=0x40020C00
	STR	R6,[R5]
	LDR	R5,=0x40021000
	STR	R6,[R5]
@ adressen till port D:s ut-dataregister till R5
	LDR	R5,=0x40020C14
@ adressen till port E:s ut-dataregister till R6
	LDR	R6,=0x40021014

main:
@ R0 = R0 << R1
@ Skriv registervärden före skift till Bargraph
	LSR	R2,R0,#16
	STRH	R2,[R5]
	STRH	R0,[R6]
@ Utför skift
	LSL	R0,R1
@ Skriv registervärden efter skift till Bargraph
	LSR	R2,R0,#16
	STRH	R2,[R5]
	STRH	R0,[R6]
	B	main