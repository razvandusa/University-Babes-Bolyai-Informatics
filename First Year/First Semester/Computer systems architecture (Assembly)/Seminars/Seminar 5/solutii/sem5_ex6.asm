bits 32
global start

extern exit, fopen, fread, fwrite, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import fwrite msvcrt.dll

segment data use32 class=data
	nume_fisier db "cuvinte.txt", 0
    mod_acces db "r+", 0
    descriptor_fisier dd 0
    
    max equ 100
    buffer times max+1 db 0
    result times max+1 db 0
    len dd 0
    
    speciale db "!@#$%^&*()_+{}[]"
    len_s equ $-speciale
    
; 6. Se dă un nume de fișier (definit în segmentul de date).
; Fișierul conține litere mici, litere mari, cifre și caractere speciale.
; Să se înlocuiască toate caracterele speciale din fișier cu caracterul 'X'.
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
        
        ; citesc continutul intregului fisier
        ; EAX = fread(void* buffer, int size, int count, FILE* stream)
        push dword [descriptor_fisier]
        push dword max
        push dword 1
        push dword buffer
        call [fread]
        add esp, 4*4

        mov ebx, 0
        mov esi, 0
    repeta:
        mov al, [buffer+esi]
        
        cmp al, 0
        je scrie
        
        mov byte [result+esi], al
        
        ; verific daca e caracter special
        call verifica
        cmp edx, 1
        jne nu_e_special
        
        ; inlocuiesc caracterul curent cu 'X'
        mov byte [result+esi], 'X'
        
    nu_e_special:
        inc ebx
        inc esi
        jmp repeta
        
    scrie:
        mov [len], ebx
        
        ; fwrite(void* buffer, int size, int count, FILE* stream)
        push dword [descriptor_fisier]
        push dword [len]
        push dword 1
        push dword result
        call [fwrite]
        add esp, 4*4
        
        ; inchid fisierul
        ; fclose(descriptor_fisier)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 1*4
        
    eroare:
        push dword 0
        call [exit]
    
        ; AL = caracterul curent
        ; verifica daca caracterul din AL e special
    verifica:
        push esi
        mov ecx, len_s
        mov esi, 0
    cauta:
        mov dl, [speciale+esi]
        
        cmp al, dl
        je e_special
        
        inc esi
        loop cauta
        
        mov edx, 0
        jmp nu_e
        
    e_special:
        mov edx, 1
        
    nu_e:
        pop esi
        ret
