bits 32
global start

extern sum_1, sum_2, sum_3

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    a dd 0
    b dd 0
    sum dd 0
    
    msg_a db "a: ", 0
    msg_b db "b: ", 0
    
    format_r db "%d", 0
    format_p db "Suma: %d", 0

; 1. Scrieți un program care calculează valoarea expresiei a+b.
segment code use32 class=code
    start:
        push dword msg_a
        call [printf]
        add esp, 4*1
        
        push dword a
        push dword format_r
        call [scanf]
        add esp, 4*2
        
        push dword msg_b
        call [printf]
        add esp, 4*1
        
        push dword b
        push dword format_r
        call [scanf]
        add esp, 4*2
        
        ; EAX = sum_1(a, b)
        ; mov eax, [a]
        ; mov edx, [b]
        ; call sum_1
        ; mov [sum], eax
        
        ; EAX = sum_2(a, b)
        ; mov eax, [a]
        ; push eax
        ; mov edx, [b]
        ; push edx
        ; call sum_2
        ; mov [sum], eax
        
        ; stiva = sum_3(a, b)
        push dword 0            ; am rezervat 4 octeti pentru rezultat
        push dword [a]
        push dword [b]
        call sum_3
        pop eax
        mov [sum], eax
        
        push dword [sum]
        push dword format_p
        call [printf]
        add esp, 4*2
    
        ; exit(0)
        push dword 0        ; push the parameter for exit onto the stack
        call [exit]         ; call exit to terminate the program
