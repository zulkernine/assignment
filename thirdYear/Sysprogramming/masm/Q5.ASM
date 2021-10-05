.MODEL SMALL
.STACK 100H

.DATA

  TERM_PROMPT DB '################# My terminate message ###################$'

.CODE
  MAIN PROC
    MOV AX,@DATA
    MOV DS,AX

    LEA DX, TERM_PROMPT
    MOV AH,9
    INT 21H

    MOV AH,4CH
    INT 21H
  MAIN ENDP
END MAIN
