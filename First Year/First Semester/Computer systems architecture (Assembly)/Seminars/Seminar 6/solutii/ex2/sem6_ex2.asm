bits 32
global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    n dd 0
    text db "Dati n: ", 0
    
    format_r db "%d", 0
    format_p db "%d! = %d", 0
	
; Scrieți un program care calculează factorialul unui număr natural n citit de la tastatură.
segment code use32 class=code
    start:
        ; afisez mesaj
        ; printf(text)
        push dword text
        call [printf]
        add esp, 1*4
        
        ; citesc n
        ; scanf(format_r, &n)
        push dword n
        push dword format_r
        call [scanf]
        add esp, 4*2
        
        ; calculez factorial
        mov eax, [n]        ; transmit argumentul
        call factorial
        
        ; afisez factorial
        ; printf(format_p, n, eax)
        push dword eax
        push dword [n]
        push dword format_p
        call [printf]
        add esp, 3*4
    
        push dword 0
        call [exit]

    factorial:
        ; n! = 1*2*3*...*n
        mov ecx, eax    ; ecx = n
        mov eax, 1      ; eax = 1
    repeta:
        mul ecx         ; edx:eax = eax*ecx
        loop repeta
        
        ret
        