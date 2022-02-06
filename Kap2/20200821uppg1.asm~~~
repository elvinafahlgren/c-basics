@
@ uppg1
@

@ char result[100]
result:		.SPACE	100
.GLOBL	result

@ int precentage
		.ALIGN
presentage:	.SPACE	4


main:		PUSH	{R4,LR}
@ precentage = 0;
		LDR	R3,=presentage
		MOV	R2,#0
		STR	R2,[R3,#0]
@ for(int i=0; i<100; i++)
		MOV	R4,#0
		B	.L1
@ saveRelation( comparePorts() ) 
.L0:		BL	comparePorts
		BL	saveRelation
		ADD	R4,#1		@i++

.L1:		CMP	R4,#99
		BLE	.L0

@ int i = 0;
		MOV	R4,#0

 @ while( i < 100 )
		B	.L3
.L2:		
@ 	if( result[i] )
		LDR	R2,=result
		ADD	R3,R2,R4	@ R2+R4->R3 (i=R2+R4)
		LDRB	R3,[R3]		@ innehållet från result[i] placeras i R3
		CMP	R3,#0
		BEQ	.L3
@		percentage++;
		LDR	R3,=presentage
		LDR	R2,[R3]
		ADD	R2,#1
		STR	R2,[R3]
		

.L3:		CMP	R4,#99
		BLE	.L2
		POP	{R4,PC}

@ static int items = 0;
items:		.WORD	0
		
saveRelation:
@ result[items++] = relation; 
		LDR	R3,=items
		ADD	R1,R3,#1	
		LDR	R2,=items	@ R2 håller adressen till items
		STR	R1,[R2]		@ placerar värdet i items
		LDR	R2,=result	@ R2 håller adressen till result
		STRB	R0,[R2,R3]	@ result[items++] = relation
		BX	LR

comparePorts:
@ 	if (*port8ptrA <= *port8ptrB){
		LDR	R3,=0x100000
		LDRB	R2,[R3]
		LDR	R3,=0x100001
		LDRB	R3,[R1]
		CMP	R2,R3
		BHI	.L4
@ 	return 1; 
		MOV	R0,#3
		B	.L5
		
.L4:
@ return 0; 
		MOV	R0,#0
@}
.L5:		BX	LR


