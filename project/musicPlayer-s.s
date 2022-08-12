	.arch msp430g2553
	.p2align 1,0
	.text

playMLL:
	#call timeChange
	#call MLLNotes
	#call MLLLights
	#call soundSwitch

playSiren:
	#call timeChange
	#call sirenNotes
	#call sirenLED
	#call soundSwitch

play3:
	#call timeChange
	#call song3Notes
	#call song3LED
	#call soundSwitch
	
play4:	
	#call timeChange
	#call song4Notes
	#call song4LED
	#call soundSwitch
	
	
jt:	.word default
	.word case1
	.word case2
	.word case3
	.word case4

	.global player
	.extern buttonState

player:
	cmp #4, &buttonState	;buttonState-4
	jnc default

	mov &buttonState, r12
	add r12, r12		;doubles for offset of size
	mov jt(r12), r0 	


case1:
	#call playMLL
	jmp end

case2:
	#call playSiren
	jmp end

case3:
	#call play3
	jmp end

case4:
	#call play4
	jmp end

default:
	mov #0, &buttonState
	#call buzzer_set_period

end:
	pop r0
