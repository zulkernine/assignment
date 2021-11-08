        .model small
        .stack 256
CR equ 13d
LF equ 10d
        .data
prompt1 db 'Enter numbers: $'
maxOutput db CR, LF,'max is: $'
minOutput db CR, LF, 'min is: $'
max1 dw ?
; max2 dw ? 
min1 dw ? 
; min2 dw ? 
        .code
start:
        mov ax, @data
        mov ds, ax
        mov max1,0
      ;  mov max2,0
        mov min1,9999
      ;  mov min2,9999
        mov dx, offset prompt1
        mov ah,9
        int 21h
        l0:  mov bx,0
        l1:  mov ah,1
        int 21h
        cmp al,13
        je l3
        cmp al,32
        je l2
        sub al,'0'
        push ax
        mov ax,bx
        mov cx,10
        mul cx
        mov bx,ax
        pop ax
        mov ah,0
        add bx,ax
        jmp l1
        l2:  cmp max1,bx
        jnl lb2
       ; mov cx,max1
       ; mov max2,cx
        mov max1,bx
        jmp lb2
       ; l4:  cmp max2,bx
       ; jnl lb2
       ; mov max2,bx
       ; jmp lb2
        lb2:  cmp min1,bx
       jng l0
        mov cx,min1
       ; mov min2,cx
        mov min1,bx
        jmp l0
       ; lb4:  cmp min2,bx
       ; jng l0
       ; mov min2,bx
       ; jmp l0
        l3:  mov dx, offset maxOutput
        mov ah,9
        int 21h
        mov ax,max1
        call putn
        mov dx, offset minOutput
        mov ah,9
        int 21h
        mov ax,min1
        call putn
        mov ax, 4c00h
        int 21h
putn:               ; display number in ax
                ; ax contains number (and also div C in above)
                ; dx contains remainder (rem in C above)
                ; cx contains 10 for division
    push    bx
    push    cx
    push    dx
 
    mov     dx, 0           ; dx = 0
    push    dx          ; push 0 as sentinel
    mov     cx, 10      ; cx = 10
 
    cmp     ax, 0
    jge     calc_digits     ; number is negative
    neg     ax          ; ax = -ax; ax is now positive
    push    ax          ; save ax
    mov al, '-'     ; display - sign
    call    putc
    pop ax          ; restore ax
 
calc_digits:
    div cx          ; dx:ax = ax / cx
                    ; ax = result, dx = remainder
    add dx, '0'     ; convert dx to digit
    cmp dx,57
    jle l33
    add dx,7
    l33:		push    dx          ; save digit on stack
    mov dx, 0       ; dx = 0
    cmp ax, 0           ; finished ?
    jne calc_digits     ; no, repeat process
 
;   all digits now on stack, display them in reverse
 
disp_loop:
    pop dx          ; get last digit from stack
    cmp dx, 0           ; is it sentinel
    je  end_disp_loop   ; if yes, we are finished 
    mov al, dl      ; al = dl
    call    putc            ; otherwise display digit
    jmp disp_loop
 
end_disp_loop:
    pop dx          ; restore registers
    pop cx
    pop bx
    ret
 
putc: ; display character in al
 
        push ax ; save ax
        push bx ; save bx 
        push cx ; save cx
        push dx ; save dx
 
        mov dl, al
        mov ah, 2h
        int 21h
 
        pop dx ; restore dx
        pop cx ; restore cx
        pop bx ; restore bx
        pop ax ; restore ax
        ret
end start
