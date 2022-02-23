;Store odd number
	LXI H,2050H
	LXI D,2100H
	LDA 204FH
	MOV C,A		;Store number of numbers in C
	MVI B,00H

L1:	MOV A,M
	ANI 01H		; A = A&01H,
	JZ L2		;If zero, then even, so skip to L2
	MOV A,M		;Else
	STAX D		;Store the odd number
	INX D		;Increament the location
	INR B		;Increament odd number count

L2:	INX H		;Increament address
	DCR C		;Decreament count
	JNZ L1		;If count not zero, continue the loop L1
	MOV A,B
	STA 2301H	;Else store number of odd numbers in 2301H

;Store even number
	LXI H,2050H
	LXI D,2200H
	LDA 204FH
	MOV C,A
	MVI B,00H
	
L4:	MOV A,M
	ANI 01H
	JNZ L3		; If not zero, then odd, skip to L3
	MOV A,M		;Else
	STAX D		;Store the even number
	INX D		;Increament the location
	INR B		;Increament even number count

L3:	INX H
	DCR C
	JNZ L4		;If count not zero, continue loop L4
	MOV A,B		;Else
	STA 2300H	;Store number of even numbers in 2300H
HLT
