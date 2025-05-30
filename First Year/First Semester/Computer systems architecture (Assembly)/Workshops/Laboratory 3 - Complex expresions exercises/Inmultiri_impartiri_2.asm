bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword - Interpretare fara semn
    ; (c+d)-(a+d)+b
    a db -3
    b db 5
    c db 2
    d dd 200
    value dw 9
    value_1 dw 2
    e dq 1000
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al,[b]
        imul byte[c]
        mov bx,ax
        mov al,[a]
        cbw
        add ax,bx
        sub ax,[value]
        
        mov bx,ax
        mov ax,[value_1]
        cwd
        idiv bx
        cwde
        cdq
        add eax,dword[e]
        adc edx,dword[e+4]
        sub eax,[d]
        sbb edx,0
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
