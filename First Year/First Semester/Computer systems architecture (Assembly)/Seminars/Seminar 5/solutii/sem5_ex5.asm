bits 32
global start

extern exit, printf, fopen, fclose, fscanf
import exit msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll

segment data use32 class=data
	nume_fisier db "numere.txt", 0
    mod_acces db "r", 0
    descriptor_fisier dd 0
    
    n dd 0
    format_citire db "%d", 0
    format_afisare db "Suma: %d", 0
    
; 5. Se dă un nume de fișier (definit în segmentul de date).
; Fișierul conține numerele întregi cu semn separate prin spații.
; Să se calculeze și să se afișeze suma numerelor din fișier.
segment code use32 class=code
    start:
        ; deschid fisierul
        ; EAX = fopen(nume_fisier, mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 2*4
        
        ; verific daca fisierul a fost deschis
        cmp eax, 0
        je eroare
        mov [descriptor_fisier], eax
        
        ; citesc continutul fisierului
        xor ebx, ebx    ; suma = 0
    citire:
        ; citesc numarul
        ; EAX = fscanf(descriptor_fisier, format_citire, &n)
        push dword n
        push dword format_citire
        push dword [descriptor_fisier]
        call [fscanf]
        add esp, 3*4
        
        cmp eax, 1
        jne afisare
        
        ; adun numarul curent
        add ebx, [n]
        jmp citire
   
   afisare:
        ; printf(format_afisare, EBX)
        push dword ebx
        push dword format_afisare
        call [printf]
        add esp, 2*4
   
        ; inchid fisierul
        ; fclose(descriptor_fisier)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 1*4
        
    eroare:
        push dword 0
        call [exit]
