bits 32
global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    a dd 0
    b dd 0
    sum db 0
    
    text_a db "a: ", 0
    text_b db "b: ", 0
    
    format_r db "%d", 0
    format_p db "Suma: %d", 0

; 1. Scrieți un program care calculează valoarea expresiei a+b.
segment code use32 class=code
    ; EAX = sum_1(a, b)
    ; calculeaza suma a 2 numere intregi
    ; input: EAX = a, EDX = b
    ; output: EAX = a+b
    sum_1:
        add eax, edx
        
        ret
    
    ; EAX = sum_2(a, b)
    ; calculeaza suma a 2 numere intregi
    ; input: stiva
    ;  --------------------
    ; | adresa de revenire | <-- ESP (varful stivei)
    ;  --------------------
    ;  --------------------
    ; | valoarea lui b     | ESP+4
    ;  --------------------
    ;  --------------------
    ; | valoarea lui a     | ESP+8
    ;  --------------------
    ;  --------------------
    ; | ....               | ESP initial 
    ;  --------------------
    ; output: EAX = a+b
    sum_2:
        mov eax, [esp+8]    ; EAX = a
        mov edx, [esp+4]    ; EAX = b
        
        add eax, edx        ; EAX = a+b
    
        ret 4*2
    
    ; calculeaza suma a 2 numere intregi
    ; input: stiva
    ;  --------------------
    ; | adresa de revenire | <-- ESP (varful stivei)
    ;  --------------------
    ;  --------------------
    ; | valoarea lui b     | ESP+4
    ;  --------------------
    ;  --------------------
    ; | valoarea lui a     | ESP+8
    ;  --------------------
    ;  --------------------
    ; | spatiu rezervat    | ESP+12
    ;  --------------------
    ;  --------------------
    ; | ....               | ESP initial
    ;  --------------------
    
    ; output: stiva
    ;  --------------------
    ; | suma               | ESP
    ;  --------------------
    sum_3:
        mov eax, [esp+8]    ; EAX = a
        mov edx, [esp+4]    ; EAX = b
        
        add eax, edx        ; EAX = a+b
        mov [esp+12], eax

        ret 4*2

    start:
        push dword text_a
        call [printf]
        add esp, 4*1
        
        push dword a
        push dword format_r
        call [scanf]
        add esp, 4*2
        
        push dword text_b
        call [printf]
        add esp, 4*1
        
        push dword b
        push dword format_r
        call [scanf]
        add esp, 4*2
        
        ; EAX = sum_1(a, b)
        ; mov eax, [a]
        ; mov edx, [b]
        ; ; add eax, edx
        ; call sum_1
        ; mov [sum], eax
        
        ; EAX = sum_2(a, b)
        ; mov eax, [a]
        ; push eax
        ; mov edx, [b]
        ; push edx
        ; ; add eax, edx
        ; call sum_2
        ; ; add esp, 4*2
        ; mov [sum], eax
        
        ; sum_3(a, b)
        push dword 0
        mov eax, [a]
        push eax
        mov edx, [b]
        push edx
        ; add eax, edx
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
