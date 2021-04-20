JMP START

START:	LXI H,204FH; HL pair stores the number of numbers
	MOV C,M;C stores number of numbers
	LDA 204EH
	MOV B,A; B stores the number to be searched
	MVI E,01H
	LXI H,2050H

LOOP2:	MOV A,M
	CMP B
	JNZ LOOP1; transferred to LOOP1 if no comparison
	MOV A,E
	STA 204DH; if found, store position in 204DH
	HLT

LOOP1:	MVI A,FF
	STA 204DH; if not found, store FFH in 204DH
	DCR C
	INX H
	INR E
	JNZ LOOP2
	HLT
