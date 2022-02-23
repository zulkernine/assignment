      LXI H,2041H
      MOV D,M		;COUNT
      LXI H,2050H
      MOV B,M		;STORE MAX
      MOV C,M		;STORE MIN
    
LS:	MOV A,M           
      CMP B             ;Compare A,B
      JC MIN            ;If carry, then check for MIN
      MOV B,A           ;Else store for max
MIN:  CMP C             ;Now compare A,C
      JNC SKIP          ;if no carry, goto SKIP
      MOV C,A           ;else store for min
SKIP: INR L             ;Increament address
	DCR D             ;Decreament counter
      JNZ LS            ;if count not zero, continue loop
      MOV A,B
      STA 2090H         ;Store max at 2090
      MOV A,C
      STA 2091H         ;Store min at 2091
      HLT
