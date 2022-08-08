	.file	"timer.c"
.text
	.global	timeCount
.data
	.balign 2
	.type	timeCount, @object
	.size	timeCount, 2
timeCount:
	.zero	2
	.global	seconds
	.balign 2
	.type	seconds, @object
	.size	seconds, 2
seconds:
	.zero	2
	.global	blinkLimit
	.balign 2
	.type	blinkLimit, @object
	.size	blinkLimit, 2
blinkLimit:
	.short	5
	.global	blinkCount
	.balign 2
	.type	blinkCount, @object
	.size	blinkCount, 2
blinkCount:
	.zero	2
	.global	__mspabi_remi
.text
	.balign 2
	.global	timeChange
	.type	timeChange, @function


timeChange:
	ADD.W	#1, &timeCount
	MOV.W	&timeCount, R12
	MOV.B	#50, R13
	CALL	#__mspabi_remi
	CMP.W	#0, R12 { JNE	.L2
	ADD.W	#1, &seconds
.L2:
	MOV.W	&seconds, R13
	MOV.B	#69, R12
	CMP.W	R13, R12 { JGE	.L3
	MOV.W	#0, &seconds
.L3:
	MOV.W	&timeCount, R13
	MOV.B	#249, R12
	CMP.W	R13, R12 { JGE	.L5
	MOV.W	#0, &timeCount
	MOV.W	&blinkLimit, R12
	ADD.W	#1, R12
	MOV.W	R12, &blinkLimit
	MOV.W	&blinkLimit, R13
	MOV.B	#7, R12
	CMP.W	R13, R12 { JGE	.L5
	MOV.W	#0, &blinkLimit
.L5:
	NOP
	; epilogue
	RET
	.size	timeChange, .-timeChange
	.balign 2
	.global	dimmer
	.type	dimmer, @function
dimmer:
; start of function
	MOV.W	&blinkCount, R12
	ADD.W	#1, R12
	MOV.W	R12, &blinkCount
	MOV.W	&blinkCount, R13
	MOV.W	&blinkLimit, R12
	CMP.W	R12, R13 { JL	.L7
	MOV.W	#0, &blinkCount
	MOV.B	&P1OUT, R12
	BIS.B	#1, R12
	AND	#0xff, R12
	MOV.B	R12, &P1OUT
	MOV.B	&P1OUT, R12
	AND.B	#-65, R12
	AND	#0xff, R12
	MOV.B	R12, &P1OUT
	BR	#.L9
.L7:
	MOV.B	&P1OUT, R12
	BIC.B	#1, R12
	AND	#0xff, R12
	MOV.B	R12, &P1OUT
	MOV.B	&P1OUT, R12
	BIS.B	#64, R12
	AND	#0xff, R12
	MOV.B	R12, &P1OUT
.L9:
	NOP
	; start of epilogue
	RET
	.size	dimmer, .-dimmer
	.ident	"GCC: (Mitto Systems Limited - msp430-gcc 8.2.0.52) 8.2.0"
