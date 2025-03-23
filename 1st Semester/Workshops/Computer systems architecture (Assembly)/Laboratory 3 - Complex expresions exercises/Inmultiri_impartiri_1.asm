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
    a db 2
    b dw 275
    c dq -1000
    value dw 7
    value_1 dw 2
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al,[a]
        cbw
        add ax,[value_1]
        mov cx,ax
        
        mov al,[a]
        imul byte[a]
        sub ax,[b]
        add ax,[value]
        cwd
        idiv cx
        cwde
        cdq
        add EAX,dword[c]
        adc EDX,dword[c+4]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
