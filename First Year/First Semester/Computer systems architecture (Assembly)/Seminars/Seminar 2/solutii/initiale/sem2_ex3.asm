bits 32
global start

extern exit
import exit msvcrt.dll

; a, b, c - byte, d - word
segment data use32 class=data
    
; x = (a * b) / d - c
segment code use32 class=code
    start:
        
    
        ; exit(0)
        push dword 0
        call [exit]
