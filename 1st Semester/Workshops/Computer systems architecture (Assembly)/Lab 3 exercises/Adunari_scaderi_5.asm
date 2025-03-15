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
    res1 resq 1
    res2 resq 1
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov AL,[a]
        cbw
        cwde
        mov ECX,[c]
        neg EAX
        add ECX,EAX
        mov EAX,ECX
        cdq
        sub EAX,dword[d]
        sbb EDX,dword[d+4]
        push EDX
        push EAX
        pop dword[res1]
        pop dword[res1+4]
        
        mov ECX,[c]
        mov AX,[b]
        cwde
        sub ECX,EAX
        mov EAX,ECX
        cdq
        push EDX
        push EAX
        pop dword[res2]
        pop dword[res2+4]
        
        mov EAX,dword[res1]
        mov EDX,dword[res1+4]
        add EAX,dword[res2]
        adc EDX,dword[res2+4]
        
        push EDX
        push EAX
        pop dword[res1]
        pop dword[res1+4]
        mov AL,[a]
        cbw
        cwde
        mov ECX,EAX
        mov EAX,dword[res1]
        mov EDX,dword[res1+4]
        neg ECX
        add EAX,ECX
        sbb EDX,0
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
