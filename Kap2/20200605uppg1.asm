@
@ uppg1
@;

@define global variables

@unsigned short student_year[4]; 
student_year:	.SPACE	8
		.ALIGN

@unsigned char student_grade[MAX]; 
student_grade:	.SPACE	4
		.ALIGN

@int c; 
c:		.SPACE	4
		.ALIGN

@void init_data(){
init_data: 	
	@student_year[0] = 2000; 
		LDR	R0,=student_year
		LDR	R2,=2000
		STRH	R2,[R0]
	@student_grade[0] = 4; 
		LDR	R1,=student_grade
		LDR	R2,=4
		STRB	R2,[R1]

	@student_year[1] = 2000; 
		ADD	R0,R0,#2
		LDR	R2,=2000
		STRH	R2,[R0]
	@student_grade[1] = 3; 
		ADD	R1,R1,#1
		LDR	R2,=3
		STRB	R2,[R1]

	@student_year[2] = 1998;
		ADD	R0,R0,#2
		LDR	R2,=1998
		STRH	R2,[R0]
	@student_grade[2] = 5; 
		ADD	R1,R1,#1
		LDR	R2,=5
		STRB	R2,[R1]

	@student_year[3] = 2002;
		ADD	R0,R0,#2
		LDR	R2,=2002
		STRH	R2,[R0]
	@student_grade[3] = 4;
		ADD	R1,R1,#1
		LDR	R2,=4
		STRB	R2,[R1]

@}

@ implementation of the sum_grade function
sum_grade:
		@year is in R0
		PUSH	{R4,R5,LR}
		LDR	R1,=0;	@ use R1 for x
		LDR	R2,=0;	@ use R2 for i
	@ use R3 for student_year access
		LDR	R3,=student_year
	@ use r4 for student_grade access
loop:
		CMP	R2,#4
		BGE	loop_exit
		LSL	R5,R2,#2	@ i<<1 -> R5
		LDRH	R5,[R3,R5]	@ student_year[R5] -> R5
		CMP	R5,R0
		BNE	if_exit
		LDRB	R5,[R4,R2]	@ student_grade[i]
		ADD	R1,R1,R5

if_exit:	ADD	R2,R2,#1	@ i++
		B	loop

loop_exit:	MOV	R0,R1
		POP 	{R3,R5,PC}

@int main( void ) {
main:		
	@init_data(); 
		BL	init_data
		LDR	R0,=2020	@ year = 2020
	@a = sum_grade(2020); 
		BL	sum_grade
		MOV	R2,R3		@ R2 = a = sum_grade(2020)
		LDR	R0,=2000
	@b = sum_grade(2000);
		BL	sum_grade	@ R3 = a = sum_grade(2020)
	@c = a+b; 
		ADD	R0,R2,R3	@ R1 = c = a + b
		LDR	R1,=c
		STR	R1,[R0]
	



@ett tappert försök, lite krånger med alla Rx bara
@@int sum_grade( int year ) { 
@sum_grade:
@	@year is in R0
@		PUSH	{R4,R5,LR}
@	@int x = 0; 
@		MOV	R3,#0
@	@for( int i=0; i < MAX; i++) { 
@		MOV	R5,#0
@		B	.L2
@		@if( student_year[i] == year )  
@.L0:		LDR	R2,=student_year
@		LSL	R5,R5,#1	@ eftersom short har två bytes
@		ADD	R4,R2,R5	@ R2+R5->R4 (i=R2+R5=R4)
@		LDRH	R4,[R4]		@ student_year[2i]
@		LSR	R5,R5,#1	@ shifta tillbaka
@		CMP	R4,R0
@		BNE	.L1
@			@x += student_grade[i]; 
@		LDR	R2,=student_grade
@		ADD	R4,R2,R5	@ R2+R5->R4 (i=R2+R5=R4)
@		LDRB	R4,[R4]		@ student_grade[i]
@		ADD	R3,R3,R4
@
@.L1		ADD	R5,R5,#1		@i++
@
@.L2:		CMP	R5,#4
@		BLE	.L0
@		POP	{R4,R5,PC}
@		
@




















	