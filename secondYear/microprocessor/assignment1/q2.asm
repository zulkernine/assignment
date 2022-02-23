	   LXI H,2500H		;H=2500
	   LDA 2200H		;A=M(2200)
	   MOV D,A			;D = A, or D = M(2200)
	   MVI A,00H		;A=00
	   MVI C,00H		;C=00

L1:	   ADD M			;A = A+M(H)
	   JNC L2			;if no carry, junp to L2
	   INR C			;if carry, increament C

L2:	   INX H			;Increament HL
	   DCR D			;ddecreament D, D counts iteration number
	   JNZ L1			;if D!=0, goto L1
	   STA 2301H		;store sum at 2301H
	   MOV A,C			;A=C (carry)
	   STA 2300H		;store carry at 2300H
	   HLT
