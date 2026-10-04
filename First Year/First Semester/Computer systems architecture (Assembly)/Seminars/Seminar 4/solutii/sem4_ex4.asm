bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
	s dw 1122h, 3344h, 5566h, 7788h
    len equ ($-s)/2         ; numarul de elemente ale sirului s (in cuvinte)
    b1 times len db 0
    b2 times len db 0
    
; 4. Se dă un șir de cuvinte s.
; Să se construiască două șiruri de octeți:
; - b1 care are ca elemente partea superioară a cuvintelor din s
; - b2 care are ca elemente partea inferioară a cuvintelor din s
segment code use32 class=code
    start:
        mov ecx, len        ; ciclul se executa de len ori
        jecxz final         ; prevenim intrarea intr-un ciclu infinit
        ; pregatim executia intructiunilor pe siruri
        cld                 ; DF = 0
        mov esi, s          ; ESI = offset-ul primului element al sirului s
        mov ebx, b1         ; EBX = offset-ul primului element al sirului b1
        mov edi, b2         ; EDI = offset-ul primului element al sirului b2
    repeta:
        lodsw               ; AX = (cuvantul din s) si ESI = ESI + 2
        stosb               ; stocam partea inferioara din AL in sirul b2 si inc EDI
        
        ; Varianta 1
        ; mov [b1+ebx], ah    ; stocam partea superioara din AH in sirul b1
        ; inc ebx
        
        ; Varianta 2: folosind instructiuni pe siruri
        push edi            ; salvam EDI pe stiva (pentru ca il vom modifica)
        mov edi, ebx        ; EDI = offset-ul curent din sirul b1
        ror ax, 8           ; mutam partea superioara din AH in AL
        stosb               ; stocam partea superioara din AL in sirul b1 si inc EDI
        mov ebx, edi        ; stocam offset-ul curent din sirul b1
        pop edi             ; refacem EDI de pe stiva
        loop repeta
        
    final:
        push dword 0
        call [exit]
