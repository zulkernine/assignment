.model small
printmsg macro msg
        lea dx,msg
        mov ah,09h
        int 21h
endm
.data
        inputMsg1 db 0ah,0dh,"Enter the binary number(0 and 1):$"
        inputMsg2 db 0ah,0dh,"Decimal is:$"
        inputMsg3 db 0ah,0dh,"Invalid Number$"
        spc db 0ah,0dh,"$"
        num dw 0
        cnt dw 0
.code
        mov ax,@data
        mov ds,ax
        printmsg inputMsg1
        xor bx,bx
     l2:mov cx,0
        mov ah,01h
        int 21h
        cmp al,0dh
        je l1
        cmp al,30h
        jb l3
        cmp al,31h
        ja l3
        sub al,30h
        and ax,00ffh
        mov cx,ax
        shl bx,1
        add bx,cx
        jmp l2
      l1:  printmsg inputMsg2
           mov num,bx
           call print
           jmp e1
        l3:printmsg inputMsg3
          e1: mov ah,4ch
           int 21h
print proc near
        push ax
        push bx
        push cx
        push dx
        mov ax,num
        mov bx,10
     lu1: mov dx,00
          div bx
          push dx
          inc cnt
          cmp ax,00
          jne lu1
     lu2: cmp cnt,00
          je ext
          pop dx
          add dl,30h
          dec cnt
          mov ah,02h
          int 21h
          jmp lu2
      ext: pop dx
           pop cx
           pop bx
           pop ax
           ret
        print endp
        end