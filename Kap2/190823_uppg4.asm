

@ short f( short a, short b); given

@ Register:
@ R4 spill x
@ R5 spill y

@ int g(short x, short y){
g:	PUSH	{R4,R5,LR}
@ 	short a = f(x,y);
	MOV	R4,R0
	MOV	R5,R1
	BL	f
@ 	if(a==x)
	CMP	R0,R4
@		return y;
	BNE	.L0
@		return x;
	MOV	R0,R5
	B	.L1
.L0:	MOV	R0,R4
.L1:	POP	{R4,R5,PC}
@ }