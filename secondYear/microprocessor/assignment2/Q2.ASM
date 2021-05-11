	LXI H,2050H
    MOV B,M     ;B = operand 1
    INR L
    MOV E,M     ;E = operand 2
    MVI D,00H
	MVI A,00H
L1:	ADD E       ;A = A+E (do it until B is 0)
	JNC L2
    INR D       ;If carry, increament D
L2:	DCR B
	JNZ L1      ;If B not zero, continue loop
    STA 2053H   ;Store sum at 2053
    MOV A,D 
    STA 2052H   ;Store carry at 2052
	HLT