bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da dublucuvantul A. Sa se obtina numarul intreg n reprezentat de bitii 14-17 ai lui A. Sa se obtina apoi in B dublucuvantul rezultat prin rotirea spre stanga a lui A cu n pozitii. Sa se obtina apoi octet C astfel:
    ;bitii 0-5 ai lui C coincid cu bitii 1-6 ai lui B
    ;bitii 6-7 ai lui C coincid cu bitii 17-18 ai lui B
    a dd 00011010010010001010100110001000b
        ;01101001001000101010011000100000
    b dd 0b
    c db 0b
    masca db 0b
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ECX,0
        mov EAX,[a] 
        ror EAX,14
        mov DL,AL
        rol EAX,14
        shl DL, 4
        shr DL, 4
        mov CL,DL
        
        rol EAX,CL
        mov EBX,EAX
        ror EAX,CL
        
        mov ECX,0
        ror EBX,1
        or CL,BL
        rol EBX,1
        
        mov DL, 00000011b
        ror EBX,17
        ror CL,6
        and DL,BL
        or CL,DL
        rol EBX,17
        rol CL,6
 
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
