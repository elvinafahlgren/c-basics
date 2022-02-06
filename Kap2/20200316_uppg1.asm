@ a)
@ Vi har deklarationerna: 
@ char j;
@ int k;
@ Visa en kodsekvens, i ARMv6 assemblerspråk, som evaluerar uttrycket j+(2*k)-1 till register R0.(2p)

@ char j;
j: 		.SPACE	1
		.ALIGN
@ int k;
k:		.SPACE	4
		.ALIGN

@ j+(2*k)-1 till R0
		LDR	R0,=j		@ R1 = &j (adress till j)
		LDRB	R0,[R0]		@ R1 = j (värdet)
		SXTB	R0,R0		@ teckenutvidga j
		LDR	R1,=k		@ R2 = &k (adressen)
		LDR	R1,[R1]		@ R2 = k (värdet)
		LSL	R1,R1,#1	@ R2 = 2*k
		ADD	R0,R0,R1	@ R0 = j + (2*k)
		SUB	R0,R0,#1	@ R0 = j + (2*k) - 1


@ b) 
@ I funktionen g har vi registerallokeringen:
@ R4: lokal variabel my_g
@ R5: lokal variabel my_rv
@ I funktionen void g(int param) görs följande funktionsanrop:
@ my_rv = f( my_g, param );
@ Visa hur detta då kodas i ARMv6 assemblerspråk. (2p)

@ my_rv = f( my_g, param );
		MOV	R1,R0
		MOV	R0,R4
		BL 	f
		MOV	R5,R0
f:		

@ c)
@ Visa koden för allokeringen av dessa fyravariabler med det minsta möjliga minnesutrymme (2p)
@ int i1;
@ char c1;
@ short s1;
@ unsigned char c2;

i1: 		.SPACE	4
c1:		.SPACE	1
c2:		.SPACE	1
s1:		.SPACE	2


