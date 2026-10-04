bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    d times 4 db 'abc', 0

segment code use32 class=code
    start:
        
    

        push dword 0
        call [exit]
