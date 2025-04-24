arch_Z80

ld B, #$04
ld A, #$10
nop
nop
nop

MainLabel:
	sub A, B
	jp MainLabel