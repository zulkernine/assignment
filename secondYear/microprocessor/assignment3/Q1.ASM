JMP START

START:	LXI H,2600H
	XCHG; DE stores the starting address where storing starts
	LXI H,2500H
	MOV B,M; B stores the number of numbers

LOOP:	INX H
	MOV A,M
	RRC
	JNC CHECKD0; jump to COND2 if D7 is zero
	RLC
	XCHG
	MOV M,A
	INX H
	XCHG
	JMP SKIP
	

CHECKD0:	RLC
	RLC
	JNC SKIP; if D0 also not = 1 then skip
	RRC; if D0=1
	XCHG
	MOV M,A
	INX H
	XCHG

SKIP:	DCR B
	JNZ LOOP
	HLT
