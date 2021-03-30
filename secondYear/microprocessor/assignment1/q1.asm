	   LDA 2200
	   MOV B,A
	   LDA 2201
	   MVI C,00
	   ADD B
	   JNC L1
	   INR C

L1:	   STA 2203
	   MOV A,C
	   STA 2204
	   HLT
