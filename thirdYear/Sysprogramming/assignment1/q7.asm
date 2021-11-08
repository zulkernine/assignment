        .model small
        .stack 256
 
CR equ 13d
LF equ 10d
 
        .data
prompt1 db 'Enter first number: $'
prompt2 db CR, LF,'Enter second number: $'
output1 db CR, LF, 'Both are Equal numbers$'
output2 db CR, LF, '2nd number is greater than 1st$'
output3 db CR, LF, '1st number is greater than 2nd$'
num1 dw ?
num2 dw ? 
 
        .code
start:
        mov ax, @data
        mov ds, ax
 
        mov ax, offset prompt1
        call puts ; display prompt1
 
        call getn ; read first number
        mov num1, ax
        mov ax, offset prompt2
        call puts ; display prompt2
 
        call getn ; read second number
 
        mov num2, ax
         
        mov ax, num1 ; ax = num1
        mov bx, num2 ; bx = num2
        cmp ax,bx
  je ll1
  jl ll2
  mov ax, offset output3
        call puts 
  jmp ll
  ll2:  mov ax, offset output2
        call puts 
  jmp ll
  ll1:  mov ax, offset output1
        call puts 
        ll: mov ax, 4c00h
        int 21h ; finished, back to dos
 
getn:           ; read a number from the keyboard
            ; return value in ax register
;                                       C variables
            ; dx records sign of number         sign variable
            ; bl stores each digit              digit variable
            ; cx stores the number read in so far   n variable
            ; al stores each character read in.     c variable
            ; ax is also used in the mul instruction
 
 
        push bx         ; save registers on stack
        push cx
        push dx
 
        mov dx, 1       ; record sign, 1 for positive
        mov bx, 0       ; initialise digit to 0
        mov cx, 0       ; initialise number to 0
 
        call getc       ; read first character
        cmp al, '-'     ; is it negative
        jne newline     ; if not goto newline
        mov dx, -1      ; else record sign 
    
        call getc       ; get next digit
newline:
        push dx     ; save sign on stack
        cmp al, 13      ; (al == CR) ?
        je  fin_read    ; if yes, goto fin_read
                    ; otherwise
        sub al, '0'     ; convert to digit
        cmp al,9
        jle l1
        sub al,7
        l1: mov cl, al      ; cl = first digit 
        call getc       ; get next character
 
read_loop:
        cmp al, 13      ; if (al == CR) 
        je fin_read     ; then goto fin_read
 
         sub al, '0'    ; otherwise, convert to digit
         cmp al,9
         jle l2
         sub al,7
         l2:  mov bl, al     ; bl = digit
         mov ax, 16     ; ax = 10
         mul cx     ; ax = cx * 10   
         mov cx, ax     ; cx = ax  n = n * 10
         add cx, bx     ; cx = cx + digit  n = n + digit
         call getc      ; read next digit
        jmp read_loop
 
fin_read:
        mov ax, cx      ; number returned in ax
        pop dx      ; retrieve sign from stack
        cmp dx, 1       ; ax = ax * dx
        je  fin_getn
        neg ax      ; ax = -ax
fin_getn:
        pop dx
        pop cx
        pop bx
        ret
 
puts:       ; display a string terminated by $
            ; dx contains address of string
 
        push ax ; save ax
        push bx ; save bx 
        push cx ; save cx
        push dx ; save dx
 
        mov dx, ax
        mov ah, 9h
        int 21h ; call ms-dos to output string
 
        pop dx ; restore dx
        pop cx ; restore cx
        pop bx ; restore bx
        pop ax ; restore ax
 
        ret
 
putn:               ; display number in ax
                ; ax contains number (and also div C in above)
                ; dx contains remainder (rem in C above)
                ; cx contains 10 for division
    push    bx
    push    cx
    push    dx
 
    mov     dx, 0           ; dx = 0
    push    dx          ; push 0 as sentinel
    mov     cx, 16      ; cx = 10
 
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
    jle l3
    add dx,7
    l3:   push    dx          ; save digit on stack
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
 
 
getc:   ; read character into al
 
        push bx ; save bx 
        push cx ; save cx
        push dx ; save dx
 
        mov ah, 1h
        int 21h
 
        pop dx ; restore dx
        pop cx ; restore cx
        pop bx ; restore bx
        ret
 
        end start