	.arch msp430g2553
	.p2align 1,0
	.text

	.global blinkUpdate
	.extern blinkLimit

blinkCount:	.word 0
	
blinkUpdate:
	sub #2, r1
	mov &blinkCount, r12 		;blinkCount == 0
	add #1, &blinkCount
	cmp &blinkCount, &blinkLimit	;bl - bc jnc
	jnc fi
	mov #0, &blinkCount
	call #greenControl
	jmp end

fi:
	call #greenControl

end:
	pop r0
