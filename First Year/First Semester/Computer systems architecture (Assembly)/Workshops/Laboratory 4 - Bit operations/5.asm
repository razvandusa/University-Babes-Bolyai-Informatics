bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se dau octetii A si B. Sa se obtina dublucuvantul C:
    ;bitii 16-31 ai lui C sunt 1
    ;bitii 0-3 ai lui C coincid cu bitii 3-6 ai lui B
    ;bitii 4-7 ai lui C au valoarea 0
    ;bitii 8-10 ai lui C au valoarea 110
    ;bitii 11-15 ai lui C coincid cu bitii 0-4 ai lui A
    a db 01100101b
    b db 10101010b
    c dd 0b
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ECX, 0
        mov EBX, 0
        mov BL, [b]
        mov EAX, 11111111111111110000000000000000b
        or ECX,EAX
        shl BL,1
        shr BL,4
        or ECX,EBX
        mov EAX, 00000000000000000000011000000000b
        or ECX,EAX
        ror ECX,11
        mov EAX,0
        mov AL, [a]
        shl AL,4
        shr AL,4
        or ECX,EAX
        rol ECX,11
        mov [c],ECX
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
