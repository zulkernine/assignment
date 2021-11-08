.MODEL SMALL
.STACK 100H
.DATA 
    PROMPT1 db 13,10,"Enter the 1st number: $"
    PROMPT2 db 13,10,"Enter the 2nd number: $"
    PROMPT3 db 13,10,"The result of the addition is: $"

.CODE
   MAIN PROC
          MOV AX,@DATA                                ;for moving data to data segment
          MOV DS,AX
          
          XOR BX,BX                                   ;initially BX value is equal to 0
          MOV CL,4      
          
          LEA DX, PROMPT1                             ;show num1 prompt
          MOV AH, 9
          INT 21H

          MOV AH,1                                    ;for taking input
          INT 21h
      
      
      INPUT1:
          CMP AL,0DH                                  ;compare whether the pressed key is 'ENTER' or not
          JE LINE1                                    ;If it is equal to 'Enter' then stop taking first value
         
          CMP AL,39h                                  ;compare the input whether it is letter or digit.39h is the ascii value of 9
          JG LETTER1
          
          AND AL,0FH                                  ;if it is digit then convert it's ascii value to real value by masking
          JMP SHIFT1
          
      LETTER1:                                        ;if it is letter then subtract 37h from it to find it's real value
          SUB AL,37h
       
      SHIFT1:
          SHL BX, CL
          OR  BL,AL                                   ;making 'or' will add the current value with previous value
          
          INT 21h
          JMP INPUT1
      LINE1:
          LEA DX, PROMPT2                             ;show num2 prompt
          MOV AH, 9
          INT 21H

          XOR DX,DX                                   ;set dx value zero

          MOV AH,1
          INT 21h

      
      INPUT2:
          CMP AL,0DH                                  ;compare whether the pressed key is 'ENTER' or not
          JE LINE2                                    ;If it is equal to 'Enter' then stop taking first value
         
          CMP AL,39h                                  ;compare the input whether it is letter or digit.39h is the ascii value of 9
          JG LETTER2
          
          AND AL,0FH                                  ;if it is digit then convert it's ascii value to real value by masking
          JMP SHIFT2
          
      LETTER2:                                        ;if it is letter then subtract 37h from it to find it's real value
          SUB AL,37H
       
      SHIFT2:
          SHL DX, CL
          OR  DL,AL                                   ;making 'or' will add the current value with previous value
            
          INT 21h
          JMP INPUT2
      LINE2:
          XOR CX,CX
          MOV CX,DX

          MOV DH,16
      
      SUM:
          ADD BX,CX                                 ;add two number which are stored in bx and cs register
          JC PC1                                    ;if the register is overflowed then print an extra 1

          mov cl, 4
      
          LEA DX, PROMPT3                           ;show answer prompt
          MOV AH, 9
          INT 21H

          OUTPUT:                                   ;level for printing their sum
          
          MOV CH,BH
          SHR CH, CL
          AND CH,0FH

          CMP CH,10                                 ;convert decimal to binary
          add cH,'0'
          cmp cH,':'
          jL TAG
          add ch,7
      TAG:MOV DL,CH
          MOV AH,2
          INT 21h

          MOV CH,BH
          AND CH,0FH
          CMP CH,10
          add cH,'0'
          cmp cH,':'
          jL TAG1
          add ch,7
      TAG1:MOV DL,CH
          MOV AH,2
          INT 21h

          MOV CH,BL
          SHR CH, CL
          AND CH,0FH
          CMP CH,10
          add cH,'0'
          cmp cH,':'
          jL TAG2
          add ch,7
      TAG2:MOV DL,CH
          MOV AH,2
          INT 21h

          MOV CH,BL
          AND CH,0FH
          CMP CH,10
          add cH,'0'
          cmp cH,':'
          jL TAG3
          add ch,7
      TAG3:MOV DL,CH
          MOV AH,2
          INT 21h

          JMP EXIT
      PC1:                                          ;level for printing overflowed 1
          MOV DL,'1'
          MOV AH,2
          INT 21h
          JMP OUTPUT
      
      EXIT:
          MOV AH, 4CH                               ;return control to DOS
          INT 21H
        
    MAIN ENDP
   END MAIN