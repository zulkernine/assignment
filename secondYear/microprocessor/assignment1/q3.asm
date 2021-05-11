LXI H,2500H     ;H=2500
MOV B,M         ;B = M(H)
MVI C,00H       ;C=00

MOV A,B         ;A = B
ANI 0FH         ; A = A && 0F or A = 0000xxxx (first 4 bit is converted to 0)
MOV C,A         ;C=A, C contains 4 lsb
MOV A,B         ;A=B
ANI F0H         ;A = A && F0 or A = xxxx0000
RRC             ;4 right rotation converts A to 0000xxxx
RRC
RRC
RRC             ;Now, A contains 4 msb
ADD C           ; add msb and lsb
STA 2550H       ; Store at 2550
HLT
