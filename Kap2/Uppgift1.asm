@
@ Uppgift 1
@
@ Hann endast p�b�rja denna uppgift 

@ deklarerar dessa som globala arrayer ist�llet
@ char str1[] = {'H','e','l','l','o'};
str1:	.BYTE	'H','e','l','l','o'
	.ALIGN
@ char str2[] = {' ','W','o','r','l','d','!'};
str2:	.BYTE	' ','W','o','r','l','d','!'
	.ALIGN
@ char total[100];
total:	.SPACE	100
	
@ void mystrcat(char *out, char *in1, char *in2)
mystrcat:
	PUSH	{R4,R5,LR}
@ r0 = &str1
@ r1 = &str2
@ r2 = &total
	@ int i = 0;
        mov     r4, #0		@ l�t r4 vara i
	@ while(*in1)
        b       .L2

.L1:
        ldrb   	r2, [r0,r4]	@ r2 = in1	
.L2:
        ldrb    r3, [r0]        @ ladda r3 med nuvarande v�rdet p� r0
        cmp     r3, #0		@ j�mf�r med 0
        bne     .L1		@ om det inte �r tomt, hoppa tillbaka
        b       .L4



	POP	{R4,R5,PC}


@ int main( void )
main:
	@ char *str1="Hello";
        ldr     r0, =str1	@ ladda r0 med adressen till str1 ist�llet f�r v�rdet
        ldr     r1, =str2	@ ladda r1 med adressen till str2 ist�llet f�r v�rdet
	ldr     r2, =str2	@ ladda �ven r2 med adressen till total
        bl      mystrcat	@ hoppa till subrutinen mystrcat
