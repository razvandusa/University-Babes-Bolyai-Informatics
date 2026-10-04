bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    s db 5, 25, 55, 127
    len equ $-s         ; numarul de elemente ale sirului s (in octeti)
    d times len db 0    ; rezervam len OCTETI pentru stocarea sirului d
    
; 3. Se dă un șir de octeți s.
; Să se construiască șirul de octeți d, care conține pe fiecare poziție
; numărul de biți care au valoarea 1 din octetul de pe poziția corespunzătoare din s.
; Exemplu:
; s: 5, 25, 55, 127
; elementele sirului s convertite in baza 2:
; 101, 11001, 10111, 1111111
; d: 2, 3, 5, 7
segment code use32 class=code
    start:
        mov ecx, len        ; ciclul se executa de len ori
        jecxz final         ; prevenim intrarea intr-un ciclu infinit
        ; pregatim executia intructiunilor pe siruri
        cld                 ; DF = 0
        mov esi, s          ; ESI = offset-ul primului element al sirului s
        mov edi, d          ; EDI = offset-ul primului element al sirului d
    repeta:
        push ecx            ; salvam ECX pe stiva
        
        ; citim octetul curent
        lodsb               ; AL <- <DS:ESI> si inc ESI
        
        ; numaram bitii de 1 din octetul curent
        mov ecx, 8          ; vom repeta ciclul de 8 ori (un OCTET = 8 biti)
        mov bl, 0           ; vom numara bitii de 1 in registrul BL
    numara:
        shl al, 1           ; bitul care iese e retinut in CF (daca bitul a fost 1, atunci CF=1, altfel CF=0)
        adc bl, 0           ; BL = BL + CF (daca CF=1 => BL = BL+1, daca CF=0 => nu modificam valoarea lui BL)
        loop numara
    
        ; stocam numarul de biti de 1
        mov al, bl          ; AL = numarul de biti de 1 din octetul curent
        stosb               ; <ES:EDI> <- AL si inc EDI
        
        pop ecx             ; refacem ECX de pe stiva
        loop repeta
    
    final:
        push dword 0
        call [exit]
