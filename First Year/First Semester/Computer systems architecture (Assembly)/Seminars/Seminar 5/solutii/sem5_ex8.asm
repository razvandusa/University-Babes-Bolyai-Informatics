bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    

; 8. Se dă un nume de fișier (definit în segmentul de date).
; Fișierul conține propoziții (șiruri de caractere separate prin spații sau punct).
; Să se determine și să se afișeze numărul de propoziții din fișier.
segment code use32 class=code
    start:
        
    

        push dword 0
        call [exit]
