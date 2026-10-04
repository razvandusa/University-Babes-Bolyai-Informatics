bits 32

global factorial

segment code use32 class=code
    factorial:
        ; n! = 1*2*3*...*n
        mov ecx, eax    ; ecx = n
        mov eax, 1      ; eax = 1
    repeta:
        mul ecx         ; edx:eax = eax*ecx
        loop repeta
        
        ret