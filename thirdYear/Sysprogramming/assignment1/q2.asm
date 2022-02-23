;Write and test a MASM program to Convert a letter from uppercase to lowercase.

.MODEL SMALL
 .STACK 100H

 .DATA
    INPUT db 13,10, "Enter a letter : $"
	OUTPUT db  13, 10, "The letter you entered (in lowercase) : $"

 .CODE
 	MAIN PROC
	 	MOV AX, @DATA	;initialize DS
	 	MOV DS, AX

	 	LEA DX, INPUT	;show the input prompt
	 	MOV AH, 9
	 	INT 21H

	 	MOV AH, 1		;read letter
	 	INT 21H

	 	LEA DX, OUTPUT	;show output prompt
	 	MOV AH, 9
	 	INT 21H

	 	MOV BL, AL		;store the letter in BL

	 	CMP BL, 'A'		;if the character is <A goto loop1
	 	JL LOOP1
	 	CMP BL, 'Z'		;if the character is >Z goto loop1
	 	JG LOOP1
	 	ADD BL, 20H		;else convert into lowercase 

	LOOP1:MOV AH, 2		;write the output letter
		MOV DL, BL
	 	INT 21H

	 	MOV AH, 4CH		;return control to DOS
	 	INT 21H

	 MAIN ENDP
END MAIN