@ start

start: 	LDR	R0, =0x55555555
	LDR	R1, =0x40020C00	@ Konfigurationsport D
	STR	R0, [R1]
	LDR	R1, =0x40020C14	@ Utport GPIO D

 	MOV	R0, #0x1
main:	STR	R0, [R1]

	BL	delay
	
	LSL	R0, #1
	B	main

delay:
	LDR	R2, #100
delay_loop:
	SUB	R2, #1
	BNE	delay
	BX	LR
	
	