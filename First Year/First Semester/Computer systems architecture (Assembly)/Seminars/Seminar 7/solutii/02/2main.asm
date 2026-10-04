bits 32
global start

extern selectie

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    s1 dd 630C018Fh, 640E0563h, 6102DF07h, 6202CF00h, 6506BF02h
    len equ ($-s1)/4        ; numarul de dublucuvinte
    s2 times 2*len db 0     ; sirul de octeti ce vor fi extrasi
    
    format db 13,10, "Numar octeti: %d", 13, 10, 0

segment code use32 class=code
    start:
        ; extrag sirul de octeti s2 din sirul de dublucuvinte s1
        mov ecx, len
        cld
        mov esi, s1
        mov edi, s2
    extrage:
        lodsw           ; AX = cuvantul inferior
        shr ax, 8
        stosb           ; octetul superior -> s2
        lodsw           ; AX = cuvantul superior
        stosb           ; octetul inferior -> s2
    loop extrage
        
        ; apelez procedura selectie
        ; selectie(len, s2)
        push dword 2*len
        push dword s2
        call selectie
        add esp, 2*4
        
        ; afisez numarul de octeti returnat
        ; EAX = numarul de octeti
        ; printf(format, eax)
        push dword eax
        push dword format
        call [printf]
        add esp, 2*4

        push dword 0
        call [exit]
