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
    ; (b+b)+(c-a)+d
    a db -2
    b dw 256
    c dd 1000
    d dq -2000
    res resq 1
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov BX,[b]
        add BX,[b]
        
        mov AL,[a]
        cbw
        cwde
        mov ECX,dword[c]
        sub ECX,EAX
        mov AX,BX
        cwde
        
        add ECX,EAX
        mov EAX,dword[d]
        mov EDX,dword[d+4]
        add EAX,ECX
        adc EDX,0
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
