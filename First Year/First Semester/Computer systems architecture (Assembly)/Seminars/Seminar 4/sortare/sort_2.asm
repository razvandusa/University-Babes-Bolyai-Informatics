bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    s db 4, 2, 7, 1, 9, 8, 3, 5, 6
    len equ $-s

; Another implementation of bubble sort in assembly language
; The string s is sorted in-place.
; Use 'Debug program' option to run it.
segment code use32 class=code
    start:
        cld
        mov esi, s
        mov ecx, len
        dec ecx                         ; 0 <= i < len-1
    outer_loop:
        push ecx
        
        lodsb
        push esi
        
        dec esi
        mov ebx, 1                  ; j = i+1
        inner_loop:
            mov dl, [esi + ebx]
            
            cmp al, dl
            jb skip_swap
            
            ; swap
            ; mov [esi + ebx], al
            ; mov [esi], dl
            ; mov al, dl
            
            mov edi, esi    ; USE xchg
            add edi, ebx
            movsb
            dec esi
            
            mov al, dl
            mov edi, esi
            stosb
            
        skip_swap:
            inc ebx
            cmp ebx, len
            je next  
            loop inner_loop

    next:
        pop esi
        pop ecx
        loop outer_loop
    
        ; exit(0)
        push dword 0                    ; push the parameter for exit onto the stack
        call [exit]                     ; call exit to terminate the program
