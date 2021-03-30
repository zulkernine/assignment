	   LXI H,2500H
	   LDA 2200H
	   MOV D,A
	   MVI A,00H
	   MVI C,00H

L1:	   ADD M
	   INR L
	   JNC L2
	   INR C

L2:	   DCR D
	   JNZ L1
	   STA 2300H
	   MOV A,C
	   STA 2301H
	   HLT
