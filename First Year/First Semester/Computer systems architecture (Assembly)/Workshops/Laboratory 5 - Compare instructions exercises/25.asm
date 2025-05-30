bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;Se dau doua siruri de caractere S1 si S2. Sa se construiasca sirul D ce contine toate elementele din S1 care nu apar in S2.
    ;Exemplu:
    ;S1: '+', '4', '2', 'a', '8', '4', 'X', '5'
    ;S2: 'a', '4', '5'
    ;D: '+', '2', '8', 'X'
    sir_sursa db "+42a84X5", 0
    lung_sir db $-sir_sursa
    sir_sursa2 db "a45", 0
    lung_sir2 db $-sir_sursa2 
    sir_destinatie resb 10
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, 0
        movzx ecx, byte[lung_sir] ;contorul = lungimea sirului
        dec ecx ;actualizam lungimea sirului
        mov esi, sir_sursa  ;esi primeste adresa de inceput a sirului
        mov edi, sir_destinatie ;edi primeste adresa de inceput a celui de al doilea sir
        start_loop:
            mov ebx,ecx  ;salvam contorul
            mov al,[esi] ;al primeste caracterele pe rand din s1
            mov ecx, 0
            movzx ecx, byte[lung_sir2]    ;actualizam contorul
            dec ecx
            mov edx, sir_sursa2 ;edx primeste adresa de inceput a celui de al doilea sir
            start_second_loop:
                cmp [edx],al ;comparam fiecare element din al doilea sir cu cel elementul din primul
                je nu_convine
                inc edx
            LOOP start_second_loop
            mov [edi],al
            inc edi
            nu_convine:
            
            mov ecx,ebx
            inc esi
        LOOP start_loop
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
