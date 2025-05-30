bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a/2+b*b-a*b*c+e+x; a,b,c-byte; e-doubleword; x-qword
    a db 8
    b db 3
    c db 2
    e dd 100
    x dq 1000
    var db 2

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al,[a]
        cbw
        idiv byte[var]
        cbw
        mov bx,ax
        mov al,[b]
        imul byte[b]
        add ax,bx
        cwd
        mov bx,ax
        mov si,dx
        
        mov al,[a]
        imul byte[b]
        mov cx,ax
        mov al,[c]
        cbw 
        imul cx
        sub si,dx
        sbb bx,ax
        push si
        push bx
        pop eax
        add eax,dword[e]
        cdq
        add eax,dword[x]
        add edx,dword[x+4]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
