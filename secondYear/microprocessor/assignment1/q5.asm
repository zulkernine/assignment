	LXI H,2500H	;BC - first 16bit number
	MOV B,M		;B - upper 8bit
    INR L
    MOV C,M		;C - lower 8 bit
    LXI H,2510H	;DE - second 16 bit number
    MOV D,M		;D - upper 8bit
    INR L
    MOV E,M		;E - lower 8bit
    LXI H,2522H	;STORE RESULT HERE(LOWER 8 BIT)
    
    MOV A,C
    ADD E		;ADD C+e
	STA 2522H		;STORE(C+D)
    MOV A,B		; to add B+D+CARRY(c)
    DCR L
    ADC D		;ADD B + D +CY
    STA 2521H
    JNC L2
    DCR L
    MVI A,01H
    STA 2520H
L2:	HLT
