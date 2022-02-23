	LXI H,2050H
    MOV B,M			;B->2050H(MN)
    INR L
    MOV C,M			;C->2051H(KL)
    MOV A,B
    ANI F0H			;A->M0H
    RRC
    RRC
    RRC
    RRC
    MOV D,A			;D->0MH
    MOV A,C
    ANI 0FH			;A->0LH
    RRC
    RRC
    RRC
    RRC				;A->L0H
    ADD D			;A-> OM + L0
    STA 2053H		;A(LMH) -> M[2051]H
    MOV A,B
    ANI 0FH
    RRC
    RRC
    RRC
    RRC
    MOV D,A			;D->N0H
    MOV A,C
    ANI F0H			;A->K0H
    RRC
    RRC
    RRC
    RRC				;A->0KH
    ADD D			;A -> NKH
    STA 2052H
L2:	HLT