@
@ binTo7seg.asm
@

init:		LDR	R6,=0x55555555	@ initiera port D som utport
		LDR	R5,=0x40020C00
		STR	R6,[R5]
		LDR	R5,=0x40020C14	@ adressen till port D:s ut-dataregiser till R5
		LDR	R6,=0x40021010	@ adressen till port E:s in-dataregister till R6
		LDR	R4,=SegCodes	@ R4 = &SegCodes[0]

main:		LDRB	R0,[R6]		@ läs inport till R0
		CMP	R0,#16		@ R0 - 16 -> APSR
		BLO	ja
		MOV	R0,#0		@ Utport <- 0
		B	main

ja:		ADD	R0,R4,R0	@ R0 <- (R4 + R0)
		LDRB	R0,[R0]		@ ladda R0 me det som ligger på adressen R4+inport
		STRB	R0,[R5]		@ Utport <- R0
		B	main

		.ALIGN
SegCodes:	.BYTE	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7F, 0x39, 0x3F, 0x79, 0x71

