bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    

; 4. Scrieți un program care citește de la tastatură cuvinte (șiruri de caractere),
; verifică și, apoi, afișează dacă aceste cuvinte sunt de tip palindrom.
segment code use32 class=code
    start:
        
    

        push dword 0
        call [exit]
