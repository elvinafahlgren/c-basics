
@ program som 
@ initierar port D och E 
@ och kontinuerligt läser värdena  från DIL-strömbrytarna, 
@ subtraherar DIL1 från DIL2 och slkriver till displayen

start:	
@	initiera port D0-D7 som utport
	LDR	R0,=0x00005555
	LDR	R1,=0x40020C00
	STR	R0,[R1]
@	initiera port E0-E15 som inport
	LDR	R0,=0
	LDR	R1,=0x40021000
	STR	R0,[R1]

@ adressen till port D:s ut-dataregister till R5
	LDR	R5,=0x40020C14
@ adressen till port E:s in-dataregister till R6
	LDR	R6,=0x40021000

main:
	LDRB	R1,[R6]
	LDRB	R0,[R6,#1]
	SUB	R0,R0,R1
	STRB	R0,[R5]
	B	main