	.file	"switches.c"
.text
	.global	buttonState
.data
	.balign 2
	.type	buttonState, @object
	.size	buttonState, 2
buttonState:
	.zero	2
	.comm	note,1,1
.text
	.balign 2
	.type	switch_update_interrupt_sense, @function
switch_update_interrupt_sense:
; start of function
; framesize_regs:     0
; framesize_locals:   2
; framesize_outgoing: 0
; framesize:          2
; elim ap -> fp       2
; elim fp -> sp       2
; saved regs:(none)
	; start of prologue
	SUB.W	#2, R1
	; end of prologue
	MOV.B	&P2IN, 1(R1)
	MOV.B	1(R1), R12
	SXT	R12
	AND.B	#15, R12
	MOV.B	R12, R13
	SXT	R13
	MOV.B	&P2IES, R12
	SXT	R12
	BIS.B	R13, R12
	SXT	R12
	AND	#0xff, R12
	MOV.B	R12, &P2IES
	MOV.B	1(R1), R12
	SXT	R12
	BIS.B	#-16, R12
	MOV.B	R12, R13
	SXT	R13
	MOV.B	&P2IES, R12
	SXT	R12
	AND.B	R13, R12
	SXT	R12
	AND	#0xff, R12
	MOV.B	R12, &P2IES
	MOV.B	1(R1), R12
	; start of epilogue
	ADD.W	#2, R1
	RET
	.size	switch_update_interrupt_sense, .-switch_update_interrupt_sense
	.balign 2
	.global	switches_init
	.type	switches_init, @function
switches_init:
; start of function
; framesize_regs:     0
; framesize_locals:   0
; framesize_outgoing: 0
; framesize:          0
; elim ap -> fp       2
; elim fp -> sp       0
; saved regs:(none)
	; start of prologue
	; end of prologue
	MOV.B	&P2REN, R12
	BIS.B	#15, R12
	AND	#0xff, R12
	MOV.B	R12, &P2REN
	MOV.B	#15, &P2IE
	MOV.B	&P2OUT, R12
	BIS.B	#15, R12
	AND	#0xff, R12
	MOV.B	R12, &P2OUT
	MOV.B	&P2DIR, R12
	AND.B	#-16, R12
	AND	#0xff, R12
	MOV.B	R12, &P2DIR
	CALL	#switch_update_interrupt_sense
	NOP
	; start of epilogue
	RET
	.size	switches_init, .-switches_init
	.balign 2
	.global	switch_interrupt_handler
	.type	switch_interrupt_handler, @function
switch_interrupt_handler:
; start of function
; framesize_regs:     0
; framesize_locals:   2
; framesize_outgoing: 0
; framesize:          2
; elim ap -> fp       2
; elim fp -> sp       2
; saved regs:(none)
	; start of prologue
	SUB.W	#2, R1
	; end of prologue
	CALL	#switch_update_interrupt_sense
	MOV.B	R12, 1(R1)
	MOV.W	&buttonState, R12
	CMP.W	#0, R12 { JNE	.L5
	MOV.B	1(R1), R12
	AND.B	#1, R12
	CMP.W	#0, R12 { JEQ	.L5
	MOV.B	1(R1), R12
	AND.B	#2, R12
	CMP.W	#0, R12 { JEQ	.L5
	MOV.B	1(R1), R12
	AND.B	#4, R12
	CMP.W	#0, R12 { JEQ	.L5
	MOV.B	1(R1), R12
	AND.B	#8, R12
	CMP.W	#0, R12 { JEQ	.L5
	MOV.B	#0, R12
	CALL	#buzzer_set_period
	MOV.W	#0, &buttonState
	BR	#.L6
.L5:
	MOV.B	1(R1), R12
	AND.B	#1, R12
	CMP.W	#0, R12 { JNE	.L7
	MOV.W	#0, &seconds
	MOV.W	#1, &buttonState
	BR	#.L6
.L7:
	MOV.B	1(R1), R12
	AND.B	#2, R12
	CMP.W	#0, R12 { JNE	.L8
	MOV.W	#0, &seconds
	MOV.W	#1, &buttonState
	BR	#.L6
.L8:
	MOV.B	1(R1), R12
	AND.B	#4, R12
	CMP.W	#0, R12 { JNE	.L9
	MOV.W	#0, &seconds
	MOV.W	#3, &buttonState
	BR	#.L6
.L9:
	MOV.B	1(R1), R12
	AND.B	#8, R12
	CMP.W	#0, R12 { JNE	.L6
	MOV.W	#0, &seconds
	MOV.W	#4, &buttonState
.L6:
	CALL	#player
	NOP
	; start of epilogue
	ADD.W	#2, R1
	RET
	.size	switch_interrupt_handler, .-switch_interrupt_handler
	.balign 2
	.global	Port_2
	.section	__interrupt_vector_4,"ax",@progbits
	.word	Port_2
	.text
	.type	Port_2, @function
Port_2:
; start of function
; attributes: interrupt 
; framesize_regs:     24
; framesize_locals:   0
; framesize_outgoing: 0
; framesize:          24
; elim ap -> fp       26
; elim fp -> sp       0
; saved regs: R4 R5 R6 R7 R8 R9 R10 R11 R12 R13 R14 R15
	; start of prologue
	PUSH	R15
	PUSH	R14
	PUSH	R13
	PUSH	R12
	PUSH	R11
	PUSH	R10
	PUSH	R9
	PUSH	R8
	PUSH	R7
	PUSH	R6
	PUSH	R5
	PUSH	R4
	; end of prologue
	MOV.B	&P2IFG, R12
	AND.B	#15, R12
	CMP.W	#0, R12 { JEQ	.L12
	MOV.B	&P2IFG, R12
	AND.B	#-16, R12
	AND	#0xff, R12
	MOV.B	R12, &P2IFG
	CALL	#switch_interrupt_handler
.L12:
	NOP
	; start of epilogue
	POP	R4
	POP	R5
	POP	R6
	POP	R7
	POP	R8
	POP	R9
	POP	R10
	POP	R11
	POP	R12
	POP	R13
	POP	R14
	POP	R15
	RETI
	.size	Port_2, .-Port_2
	.ident	"GCC: (Mitto Systems Limited - msp430-gcc 8.2.0.52) 8.2.0"
