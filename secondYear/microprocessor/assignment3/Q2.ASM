    LXI H,21FFH
	MOV B,M
	LXI H,2200H
	MVI C,00H; C=0
	MVI A,00H; A=0
	
LOOP:	STA 2600H
	MOV A,M; number moved to Accumulator
	ANI 81H; 1000 0001 ANDed
	CPI 81H; check if LSB=1 and MSB=1
	JNZ SKIP1; if LSB AND MSB not = 1 then goto SKIP1
	LDA 2600H; stores the existing sum
	ADD M; add the new number to sum
	JNC SKIP
	INR C
	JMP SKIP

SKIP1:	LDA 2600H
	INX H
	DCR B
	JNZ LOOP
	JMP LAST

SKIP:	INX H
	DCR B
	JNZ LOOP

LAST:	STA 2500H
	MOV A,C
	STA 2501H
	HLT
