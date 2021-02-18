@
@ invstate.asm
@
main:
	LDR	R0,=func1
	BLX	R0
	LDR	R0,=func2
	BLX	R0
	.thumb_func	@ anger att func1 ska exekveras i "Thumb-state"
func1:
	BX 	LR
func2:
	BX	LR