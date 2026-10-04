bits 32
global start

extern factorial

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    n dd 0
    msg db "n: ", 0
    format db "%d", 0
    format_p db "%d! = %d", 0
	
; Scrieți un program care calculează factorialul unui număr natural n citit de la tastatură.
segment code use32 class=code
    ; programul principal
    start:
        ; afisez mesaj
        ; printf(msg)
        push dword msg
        call [printf]
        add esp, 1*4
        
        ; citim n
        ; scanf("%d", &n)
        push dword n
        push dword format
        call [scanf]
        add esp, 4*2
        
        ; calculez factorial
        mov eax, [n]        ; transmit argumente
        call factorial
        
        ; afisez factorial
        push dword eax
        push dword [n]
        push dword format_p
        call [printf]
        add esp, 3*4
    
        ; exit(0)
        push dword 0
        call [exit]
