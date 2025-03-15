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
        mov al,[a]
        cbw
        add ax,[b]
        cwde
        add eax,[c]
        cdq
        add eax,dword[d]
        add edx,dword[d+4]
        push edx
        push eax
        pop dword[res1]
        pop dword[res1+4]
        
        mov al,[a]
        cbw
        add ax,[b]
        cwde
        cdq
        mov ebx,eax
        mov ecx,edx
        mov eax,dword[res1]
        mov edx,dword[res1+4]
        
        sub eax,ebx
        sbb edx,ecx
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
