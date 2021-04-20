JMP START

;process for storing odd numbers start
START:	LXI H,2050H
	LXI D,2100H
	LDA 204FH
	MOV C,A;store number of numbers in C
	MVI B,00H

LOOP1:	MOV A,M
	ANI 01H
	JZ LOOP
	MOV A,M
	STAX D; store the odd number
	INX D; shift the location
	INR B; increment odd number count

LOOP:	INX H
	DCR C
	JNZ LOOP1
	MOV A,B
	STA 2301H; store number of odd numbers in 2301H

;process for storing even numbers start
	LXI H,2050H
	LXI D,2200H
	LDA 204FH
	MOV C,A
	MVI B,00H
	
LOOP4:	MOV A,M
	ANI 01H
	JNZ LOOP3
	MOV A,M
	STAX D; store the even number
	INX D; shift the location
	INR B; increment even number count

LOOP3:	INX H
	DCR C
	JNZ LOOP4
	MOV A,B
	STA 2300H; store number of even numbers in 2300H
HLT
