bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un sir de caractere S. Sa se construiasca sirul D care sa contina toate literele mari din sirul S.
    ; Exemplu:
    ; S: 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
    ; D: 'A', 'B', 'M'
    sir_sursa db "aAbB2%xM", 0
    lung_sir db $-sir_sursa
    sir_destinatie resb 10
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, [lung_sir] ;contorul = lungimea sirului
        dec ecx ;actualizam lungimea sirului
        mov esi, sir_sursa  ;esi primeste adresa de inceput a sirului
        mov edi, sir_destinatie ;edi primeste adresa de inceput a celui de al doilea sir
        start_loop:
            mov al,[esi]
            cmp al, 'A'
            jl nu_convine
            cmp al, 'Z'
            jg nu_convine
            mov al,[esi]
            mov [edi],al
            inc edi
        nu_convine:
        inc esi
        LOOP start_loop
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
