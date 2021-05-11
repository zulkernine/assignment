ST:	LXI H,204FH
	MVI D,00H
	MOV C,M         ; C stores number of elements
	DCR C
	LXI H,2050H
	
L1:	MOV A,M
	INX H
	CMP M
	JNC L2	        ;If A>M skip to L2
	JZ L2	        ;If A==M skip to L2
	MOV B,M         ;Else  swap the two elements
	MOV M,A
	DCX H
	MOV M,B
	INX H
	INR D	        ;Indicates that swapping happened
	
L2:	DCR C           ;Decreament counter
	JNZ L1          ;If not zero, continue L1 loop
	MOV A,D
	CPI 00H         ;compare number of swapping 
	JNZ ST          ; if any changes occurred , start for next iteration
	HLT
