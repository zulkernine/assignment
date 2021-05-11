	   LDA 2200		;Load data to accumulator from memory
	   MOV B,A		;A -> B or B=A
	   LDA 2201		;Load data to accumulator from memory
	   MVI C,00		;C=0
	   ADD B		; A = A+B
	   JNC L1		;if no carry, jump to l1
	   INR C		;if carry, increment C

L1:	   STA 2203		;store sum at 2203H
	   MOV A,C		;A=C
	   STA 2202		;store carry at 2202H
	   HLT
