bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    s db 'a', 'b', 'c', 'd', 'e', 'f'
    len equ $-s         ; numarul de elemente ale sirului s (in octeti)
    d times len db 0    ; rezervam len OCTETI pentru stocarea sirului d
    
; 1. Se dă un șir de caractere s.
; Să se copieze elementele șirului s într-un alt șir de caractere d,
; folosind instrucțiuni pe șiruri.
segment code use32 class=code
    start:
    ; -----------------------------------------------------------
        ; ; Varianta 1: folosind instructiunile LODSB si STOSB
        ; mov ecx, len        ; ciclul se executa de len ori
        ; jecxz final         ; prevenim intrarea intr-un ciclu infinit
        ; ; pregatim executia intructiunilor LODSB si STOSB
        ; cld                 ; DF = 0
        ; mov esi, s          ; ESI = offset-ul primului element al sirului s
        ; mov edi, d          ; EDI = offset-ul primului element al sirului d
    ; repeta:
        ; lodsb               ; AL <- <DS:ESI> si inc ESI
        ; stosb               ; <ES:EDI> <- AL si inc EDI
        ; loop repeta
    
    ; -----------------------------------------------------------
        ; ; Varianta 2: folosind instructiunea MOVSB
        ; mov ecx, len        ; ciclul se executa de len ori
        ; jecxz final         ; prevenim intrarea intr-un ciclu infinit
        ; ; pregatim executia intructiunii MOVSB
        ; cld                 ; DF = 0
        ; mov esi, s          ; ESI = offset-ul primului element al sirului s
        ; mov edi, d          ; EDI = offset-ul primului element al sirului d
    ; repeta:
        ; movsb               ; <ES:EDI> <- <DS:ESI> si inc ESI si inc EDI
        ; loop repeta
        
    ; -----------------------------------------------------------
        ; Varianta 3: folosind prefixul REP
        mov ecx, len        ; REP se executa de len ori
        jecxz final         ; prevenim intrarea intr-un ciclu infinit
        ; pregatim executia intructiunii MOVSB
        cld                 ; DF = 0
        mov esi, s          ; ESI = offset-ul primului element al sirului s
        mov edi, d          ; EDI = offset-ul primului element al sirului d
        rep movsb
        
    final:
        push dword 0
        call [exit]
