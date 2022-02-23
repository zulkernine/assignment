	LXI H,204FH	
	MOV C,M			;C stores number of numbers
	LDA 204EH
	MOV B,A			; B stores the number to be searched
	MVI D,01H		;D stores the position of the number
	LXI H,2050H

L2:	MOV A,M
	CMP B			;Compare each element with B
	JNZ L1			;If do not match, skip to L1
	MOV A,E			;Else if match,
	STA 204DH		;store position in 204DH
	HLT				;Stop

L1:	MVI A,FF		
	STA 204DH		;If no match found, store FFH in 204DH
	INX H			;Goto the next element
	INR D			;Increament position counter
	DCR C			;Decreament counter
	JNZ L2			;If not zero, continue the loop L2
	HLT
