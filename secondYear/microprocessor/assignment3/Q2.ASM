    LXI H,21FFH
	MOV B,M			;B stores count or number of total elements
	LXI H,2200H
	MVI C,00H		; C=0, C stores carry
	MVI D,00H		; D=0, D stores sum
	
L1:	MOV A,M			; number moved to Accumulator
	ANI 81H			; 1000 0001 ANDed
	CPI 81H			;Compare msb and lsb with 1
	JNZ J2			;If not 1, then goto J1
    MOV A,M			;Else A = M
	ADD D			;Add previous sum
	MOV D,A			;Store new sum at D
	JNC J2
	INR C			;If carry increament C

J2:	INX H
	DCR B			;DECREAMENT COUNTER
	JNZ L1			;If not zero, continue loop L1

	MOV A,D
	STA 2501H		;Store sum
	MOV A,C
	STA 2500H		;Store carry
	HLT
