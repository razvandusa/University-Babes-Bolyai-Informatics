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
    a db -2
    b dw 256
    c dd 1000
    d dq -2000
    res resq 1
    res2 resq 1
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ECX, [c]
        mov EAX, dword[d]
        mov EDX, dword[d+4]
        add EAX,ECX
        adc EDX, 0
        
        push EDX
        push EAX
        pop dword[res]
        pop dword[res+4]
        
        mov EBX, dword[d]
        mov ECX, dword[d+4]
        mov AL, [a]
        cbw
        cwde
        cdq
        add EAX,EBX
        adc EDX,ECX
        push EDX
        push EAX
        pop dword[res2]
        pop dword[res2+4]
        mov EAX,dword[res]
        mov EDX,dword[res+4]
        
        sub EAX,dword[res2]
        sbb EDX,dword[res2+4]
        add EAX,EBX
        adc EDX,ECX
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
