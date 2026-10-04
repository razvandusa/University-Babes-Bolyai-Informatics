bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    s db 4, 2, 7, 1, 9, 8, 3, 5, 6
    len equ $-s     ; numarul de elemente ale sirului s (in octeti) 
    
; 6. Se dă un șir de octeți s.
; Să se ordoneze crescător elementele șirului s.
segment code use32 class=code
    start:
        mov ecx, len                ; ECX = numarul de elemente ale lui s
        jecxz final
        dec ecx                     ; 0 <= i < len-1
        mov esi, 0                  ; i = 0
    loop_1:
        mov al, [s+esi]             ; AL = s[i]
        
        mov ebx, esi
        inc ebx                     ; i+1 <= j < len
        loop_2:
            mov dl, [s+ebx]         ; DL = s[j]
            
            cmp al, dl
            jb no_swap
            
            ; daca s[i] >= s[j], interschimb elementele
            mov [s+ebx], al
            mov [s+esi], dl
            mov al, dl
            
            ; daca s[i] < s[j], nu interschimb elementele
        no_swap:
            inc ebx                 ; j++
            cmp ebx, len            ; verific daca am ajuns la ultimul element
            jb loop_2               ; daca j < len, reiau ciclul

    next:
        inc esi                     ; i++
        loop loop_1
    
    final:
        push dword 0
        call [exit]
