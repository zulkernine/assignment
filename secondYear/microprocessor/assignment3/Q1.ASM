	LXI H,2600H
	XCHG		; DE stores the starting address where storing starts
	LXI H,2500H
	MOV B,M		; B stores the number of numbers

L1:	INX H
	MOV A,M
	RRC			;Right rotation to check lsb through carry
	JNC L2		;Jump to L2 if D7 is zero
	RLC			;Else
	XCHG		;
	MOV M,A		;Store it
	INX H
	XCHG
	JMP L3
	

L2:	RLC			;2 Left rotation through carry to check D0(msb)
	RLC
	JNC L3		;If D0 != 1 then skip
	RRC			;Else
	XCHG
	MOV M,A		;Store the number
	INX H
	XCHG

L3:	DCR B		;Decreament counter
	JNZ L1		;Continue if counter not zero
	HLT
