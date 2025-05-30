bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dd 0
    b dd 0
    format_mesaj db "Introduce cele doua numerele: ",0
    format_citire db "%d %d",0
    format_afisare db "Media aritmetica este: %x", 0
    ;scanf("%d %d",a,b)
; our code starts here
segment code use32 class=code
    start:
        push dword format_mesaj             ;punem formatul pe stiva
        call [printf]                       ;facem printf
        add esp, 4 * 1                      ;eliberam stiva
        
        push dword b                        ;il punem pe b pe stiva
        push dword a                        ;il punem pe a pe stiva 
        push dword format_citire            ;punem formatul pe stiva
        call [scanf]                        ;apelam functia scanf
        add esp, 4 * 3                      ;eliberam stiva
        
        mov ax, word[a]                     ;mutam in ax primul numar
        add ax, word[b]                     ;adunam in ax al doilea numar
        mov bl, 2                           ;mutam in bl pe 2
        idiv bl                             ;impartim ce e in ax la 2             
        cbw 
        cwde
            
        push eax                            ;punem rezultatul pe stiva
        push dword format_afisare           ;punem mesajul pe stiva
        call [printf]                       ;facem printf
        add esp, 4 * 2                      ;eliberam stiva
        ; exit(0)
        push    dword 0                     ; push the parameter for exit onto the stack
        call    [exit]                      ; call exit to terminate the program
