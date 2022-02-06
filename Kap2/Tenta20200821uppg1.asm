
 @ implementation of the sum_grade function 
sum_grade:         
	@ year is in R0         
	PUSH 	{R4, R5, LR}         
	LDR  	R1, =0 		@ use R1 for x         
	LDR  R2, =0 		@ use R2 for i 
@ use R3 for student_year access         
	LDR  R3, =student_year  
@ use R4 for student_grade access         
	LDR  R4, =student_grade  loop:         
	CMP  R2, #4         
	BGE  loop_exit         
	LSL  R5, R2, #2         
	LDRH R5, [R3,R5]         
	CMP  R5, R0         
	BNE  if_exit         
	LDRB R5, [R4,R2]         
	ADD  R1, R1, R5 

if_exit: 
	ADD  R2, R2, #1         
	B    loop 
loop_exit:         
	MOV  R0, R1         
	POP  {R4, R5, PC} 
@ implementation of the main function 
main:         
	@ R4 used for a and R5 for b         
	@ init_data();         
	BL   init_data         
	@ a = sum_grade(2020);         
	LDR  R0, =2020         
	BL   sum_grade         
	MOV  R4, R0         
	@ b = sum_grade(2000);         
	LDR  R0, =2000         
	BL   sum_grade         
	MOV  R5, R0         
	@ c = a+b;         
	ADD  R4, R4, R5         
	LDR  R0, =c         
	STR  R4, [R0] 