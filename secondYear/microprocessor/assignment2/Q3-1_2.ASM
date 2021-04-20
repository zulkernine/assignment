      LXI H,2041H
      MOV D,M			;COUNT
      LXI H,2050H
      MOV B,M			;STORE MAX
      MOV C,M			;STORE MIN
    
LS:	  MOV A,M
      CMP B
      JC MIN
      MOV B,A
MIN:  CMP C
      JNC SKIP
      MOV C,A
SKIP: INR L
	  DCR D
      JNZ LS
      MOV A,B
      STA 2090H
      MOV A,C
      STA 2091H
      HLT
    