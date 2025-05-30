bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; (a+b/c-1)/(b+2)-x; a-doubleword; b-byte; c-word; x-qword
    a dd 9
    b db -8
    c dw 4
    x dq 300

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al,[b]
        cbw
        cwd
        idiv word[c]
        add ax,[a]
        dec ax
        mov cx,ax
        mov bx,dx
        inc byte[b]
        inc byte[b]
        mov al,[b]
        cbw
        mov si,ax
        mov ax,cx
        mov dx,bx
        idiv si
        cwde 
        cdq
        sub eax,dword[x]
        sbb edx,dword[x+4]
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
