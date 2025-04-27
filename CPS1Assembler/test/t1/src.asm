arch_Z80

ld A, $C0			;Load 192
ld B, ($04)			;Load from $04
ld C, 5				;Load 5
ld DE, $0410		;Load 192
ld IXH, %01010000	;Load 80

MainLabel:
	sub A, B
	jp MainLabel

db $01
dw $0201
dl $04030201