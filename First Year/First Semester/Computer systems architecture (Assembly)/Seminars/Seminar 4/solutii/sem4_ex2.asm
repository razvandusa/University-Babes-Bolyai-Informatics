bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    s db 'a', 'b', 'c', 'd', 'e', 'f'
    len equ $-s         ; numarul de elemente ale sirului s (in octeti)
    d times len db 0    ; rezervam len OCTETI pentru stocarea sirului d
    
; 2. Se dă un șir de caractere s format din litere mici.
; Să se construiască un șir de caractere d care să conțină literele
; din șirul inițial transformate în majuscule, folosind instrucțiuni pe șiruri.
segment code use32 class=code
    start:
        mov ecx, len        ; ciclul se executa de len ori
        jecxz final         ; prevenim intrarea intr-un ciclu infinit
        ; pregatim executia intructiunilor pe siruri
        cld                 ; DF = 0
        mov esi, s          ; ESI = offset-ul primului element al sirului s
        mov edi, d          ; EDI = offset-ul primului element al sirului d
    repeta:
        ; citim litera mica
        lodsb               ; AL <- <DS:ESI> si inc ESI
        
        ; transformam litera mica in majuscula
        mov bl, 'a'-'A'     ; BL = diferenta dintre codurile ASCII ale literelor a si A
        sub al, bl          ; AL = codul ASCII al majusculei corespunzatoare
        
        ; stocam codul ASCII din AL in sirul d
        stosb               ; <ES:EDI> <- AL si inc EDI
        loop repeta
    
    final:
        push dword 0
        call [exit]
