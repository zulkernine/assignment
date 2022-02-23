		LXI H,201EH
        MOV B,M 		;STORE N AT REG-B
        INR L
        MOV C,M     	;STORE M AT REG-C
        MOV A,B
        SUB C			;A = (N-M)
        LXI H,2050H		;HL -> LOCATION1
        ADD L			;A -> A+L
        JNC L1
        INR H
L1:		MOV L,A			;HL = (HL+A) OR HL->LOCATION2
		MOV C,B
        MVI B,00H
        DCX B			; BC -> N-1
        DAD B
        XCHG			; STORE THE END-ADDRESS OF LOCATION2 IN DE PAIR
        LXI H,2050H
        DAD B			;STORE END-ADDRESS OF LOCATION1 IN HL PAIR
        INX B			;C = N
        
LOOP:	MOV A,M
		XCHG
        MOV M,A			; SWAP CONTENT OF HL WITH DE
        DCX D
        DCX H
        XCHG
        DCR C			; DECREMENT N
        JNZ LOOP		; CONTINUE UNTIL N IS 0
       
        HLT
		