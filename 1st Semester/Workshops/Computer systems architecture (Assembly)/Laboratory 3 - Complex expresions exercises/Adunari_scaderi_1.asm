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
    ; c-(a+d)+(b+d)
    a db -2
    b dw 256
    c dd 1000
    d dq -2000
    res resq 1
    res2 resq 2
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov AL,[a]
        cbw
        cwde
        cdq
        mov EBX,[d+0]
        mov ECX,[d+4]
        add EBX,EAX
        adc ECX,EDX
        clc
        push ECX
        push EBX
        pop dword[res]
        pop dword[res+4]
        
        mov AX,[b]
        cwde
        cdq
        mov EBX,[d+0]
        mov ECX,[d+4]
        add EBX,EAX
        adc ECX,EDX
        clc
        push ECX
        push EBX
        pop dword[res2]
        pop dword[res2+4]
        
        mov EAX,[c]
        cdq
        sub EAX,dword[res]
        sbb EDX,dword[res+4]
        clc
        
        add EAX,dword[res2]
        adc EDX,dword[res2+4]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
