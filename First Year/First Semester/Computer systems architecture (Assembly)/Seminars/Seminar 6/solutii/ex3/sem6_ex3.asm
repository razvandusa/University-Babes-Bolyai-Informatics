bits 32
global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    max equ 50
    s1 times max+1 db 0
    s2 times max+1 db 0
    d times 2*max+1 db 0
    
    format_r db "%s", 0
    format_p db "Sir final: %s", 13, 10, 0
    text_1 db "Dati primul sir: ", 0
    text_2 db "Dati al doilea sir: ", 0

; 3. Scrieți un program care concatenează două șiruri de caractere citite de la tastatură.
segment code use32 class=code
    start:
        ; citesc primul sir
        
        ; citesc al doilea sir
        
        ; concatenez sirurile
        
        ; afisez rezultatul
    
        push dword 0
        call [exit]

    ; 
    concatenare:
        
        ret