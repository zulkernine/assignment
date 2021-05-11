	LXI H,2060H
	MOV B,M		;Store arguement at B
    CALL FIB	;Call fibonacci function(subroutine) 
    MOV A,B		;Get result from B register
    STA 2050H	;Store result
    HLT
	
	
; Single arguement passed by B reg,
;result is also stored at B at the end of function 
FIB:MVI D,00H	; (n-2)th element
	MVI E,01H	; (n-1)th element
    DCR B		;Decrement counter twice
    DCR B
LP:	MVI A,00H	;Calculate n th element
	ADD D
	ADD E
	MOV D,E
	MOV E,A
	DCR B		;Decrement counter
	JNZ LP		;if counter not zero, continue loop
	MOV B,A		;store result at B register
    RET
	
