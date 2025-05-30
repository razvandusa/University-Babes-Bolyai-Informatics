bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;Se dau doua siruri de caractere ordonate alfabetic s1 si s2.
    ;Sa se construiasca prin interclasare sirul ordonat s3 care sa contina toate elementele din s1 si s2.
    s1 db "abcdefgh", 0
    len dd $-s1 
    s2 db "defghijkl", 0
    len2 dd $-s2
    s3 resb 100
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, 0
        mov edx, 0
        mov eax, 0
        mov ecx,[len] ;mutam in ecx contorul care este lungimea lui s1
        dec ecx ;actualizam contorul la valoarea corecta
        mov esi,s1 ;mutam in esi adresa primului caracter din s1
        mov edi,s3 ;mutam in edi adresa sirului in care facem concatenarea
        start_loop:
            mov al,[esi];mutam in eax literele pe rand
            mov ebx,ecx ;salvam contorul initial
            mov ecx,[len2];mutam in ecx contorul care este lungimea lui s2
            dec ecx;actualizam contorul la valoarea corecta
            mov edx,s2;mutam in edx adresa de la inceputul sirului s2
            start_second_loop:
                cmp al,[edx];comparam literele sa vedem daca sunt egale
                jne not_gasit;daca nu sunt egale nu facem mutarea
                    mov [edi],al;actualizam s3
                    inc edi
                not_gasit:
                inc edx
            loop start_second_loop
            mov ecx,ebx
            inc esi
        loop start_loop
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
