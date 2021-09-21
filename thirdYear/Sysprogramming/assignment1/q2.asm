  

 section .data                           ;Data segment
    str1 db "Enter a letter: "
	str2 db "The letter you entered (in lowercase): "
    str3 db "Output: "
    lens1 equ $-str1             ;The length of the message
    lens2 equ $-str2             ;The length of the message
    lens3 equ $-str3             ;The length of the message

    SYS_EXIT  equ 1
    SYS_READ  equ 3
    SYS_WRITE equ 4
    STDIN     equ 0
    STDOUT    equ 1 

segment .bss
    num1 resb 1

section .text
    global _start

_start:	
    mov eax, SYS_WRITE  ;write message
    mov ebx, STDOUT
    mov ecx, str1
    mov edx, lens1
    int 80h             ;call kernel

    mov eax, SYS_READ   ;read character
    mov ebx, STDIN  
    mov ecx, num1 
    mov edx, 2
    int 0x80

    mov eax, SYS_WRITE  ;write message
    mov ebx, STDOUT
    mov ecx, str2
    mov edx, lens2
    int 80h 

    mov eax, SYS_WRITE  ;show char
    mov ebx, STDOUT
    mov ecx, num1
    mov edx, 1
    int 80h

    MOV BL, num1		;store the letter in BL

    CMP BL, 'A'		;if the character is <A goto loop1
    JL LOOP1
    CMP BL, 'Z'		;if the character is >Z goto loop1
    JG LOOP1
    ADD BL, 20H		;else convert into lowercase 
    MOV [num1],BL

LOOP1:
    MOV [num1],BL
    mov eax, SYS_WRITE  ;write message
    mov ebx, STDOUT
    mov ecx, str3
    mov edx, lens3
    int 80h 

    mov eax, SYS_WRITE  ;write message
    mov ebx, STDOUT
    mov ecx, num1
    mov edx, 1
    int 80h 

    ; Exit code
    mov eax, 1
    mov ebx, 0
    int 80h
