bits 32

global sum_1, sum_2, sum_3

segment code use32 class=code
    ; calculeaza suma a 2 numere intregi
    ; input: EAX = a, EDX = b
    ; output: EAX = a+b
    sum_1:
        add eax, edx    ; EAX = a+b
        
        ret
    
    
    ; calculeaza suma a 2 numere intregi
    ; input: stiva
    ;  --------------------
    ; | adresa de revenire | <-- ESP
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
    ; output: EAX
    sum_2:
        mov eax, [esp+8]        ; EAX = a
        mov edx, [esp+4]        ; EDX = b
        
        add eax, edx            ; EAX = a+b
        
        ret 4*2

    
    ; calculeaza suma a 2 numere intregi
    ; input: stiva
    ;  --------------------
    ; | adresa de revenire | ESP
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
        mov eax, [esp+8]        ; EAX = a
        mov edx, [esp+4]        ; EDX = b
        
        add eax, edx            ; EAX = a+b
        mov [esp+12], eax
        
        ret 4*2
