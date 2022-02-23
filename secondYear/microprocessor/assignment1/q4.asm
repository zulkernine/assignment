	LXI H,2500H
	MOV A,M
	MVI B,00H	;COUNT 0
	MVI C,00H	;COUNT 1
	MVI D,08H	;D=8, nimber of bit

S1: RLC			;Rotate left through carry
	JNC I0		;if no carry or bit is 0, goto I0
	INR C		;else increament C, (number of 0)
    JMP D1		;Goto D1
I0:	INR B		;Increament B, (number of 1)
D1:	DCR D		;Decreament count
	JNZ S1		;if count not zero, repeat loop or goto s1
    
    MOV A,C		;
    STA 2610H	;Store value of C(A) t0 2610
    MOV A,B
    STA 2511H	;Store value of B at 2511
    
	HLT
