section .data                           ;Data segment
   name db 'My name: Mohiuddin Mondal', 0ah ;My name
   lenName equ $-name             ;The length of the message
   pTitle db 'Program title: Assembly Programming',0ah
   lenTitle equ $-pTitle                 
   linefeed db 13, 10, "$"
section .bss           ;Uninitialized data
	
section .text          ;Code Segment
   global _start
	
_start:                ;name
   mov eax, 4
   mov ebx, 1
   mov ecx, name
   mov edx, lenName
   int 80h
	


   ;Output 2nd message 
   mov eax, 4
   mov ebx, 1
   mov ecx, pTitle
   mov edx, lenTitle
   int 80h  
   
   ; Exit code
   mov eax, 1
   mov ebx, 0
   int 80h
