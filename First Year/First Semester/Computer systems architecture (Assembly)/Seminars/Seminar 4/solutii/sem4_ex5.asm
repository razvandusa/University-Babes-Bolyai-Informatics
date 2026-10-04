bits 32
global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
	s1 db 12h, 23h, 56h, 34h, 45h, 67h, 78h, 89h
    len equ $-s1                ; numarul de elemente ale sirului s (in octeti)
    s2 db 34h, 12h, 56h, 45h, 23h, 78h, 89h, 67h
    p db 0
    format db 'Pozitia p este %d', 13, 10, 0

; 5. Se dau două șiruri de octeți s1 și s2 de lungimi egale.
; Să se determine poziția p în care elementele ambelor șiruri sunt egale.
segment code use32 class=code
    start:
    ; -----------------------------------------------------------
        ; ; Varianta 1: fara instructiuni pe siruri
        ; mov ecx, len            ; ciclul se executa de len ori
        ; jecxz final             ; prevenim intrarea intr-un ciclu infinit
        ; mov esi, 0              ; i = 0
    ; cauta:
        ; ; citim elementele
        ; mov al, [s1+esi]        ; AL = s1[i]
        ; mov dl, [s2+esi]        ; DL = s2[i]
        
        ; ; comparam elementele
        ; cmp al, dl              ; comparam s1[i] cu s2[i]
        ; je gasit                ; sunt egale (ZF=1), sari la eticheta 'gasit'
        
        ; ; nu sunt egale, continuam cautarea
        ; inc esi                 ; i++
        ; loop cauta
    
        ; ; afisam la consola pozitia p determinata
    ; gasit:
        ; push dword esi          ; pozitia p
        ; push dword format
        ; call [printf]
        ; add esp, 4*2
        
    ; -----------------------------------------------------------
        ; Varianta 2: folosind instructiuni pe siruri
        mov ecx, len            ; ciclul se executa de len ori
        jecxz final             ; prevenim intrarea intr-un ciclu infinit
        ; pregatim executia intructiunilor pe siruri
        cld
        mov esi, s1             ; ESI = offset-ul primului element al sirului s1
        mov edi, s2             ; EDI = offset-ul primului element al sirului s2
    cauta:
        lodsb                   ; AL = s1[i] si inc ESI
        scasb                   ; cmp AL, s2[i] si inc EDI
        
        ; cele 2 instructiuni de mai sus pot fi inlocuite cu:
        ; cmpsb                   ; cmp s1[i], s2[i] si inc ESI si inc EDI
        
        je gasit
        loop cauta
    
    gasit:
        ; calculam pozitia p
        mov eax, esi        ; EAX = offset-ul curent din ESI
        dec eax             ; decrementam (pentru ca ESI a fost deja incrementat de LODSB)
        sub eax, s1         ; EAX = pozitia = (offset-ul curent) - (offset-ul primului element al lui s1)
        mov [p],esi
        sub [p],dword s1
        ; afisam la consola pozitia p determinata
        push dword eax
        push dword format
        call [printf]
        add esp, 4*2
        
    final:
        push dword 0
        call [exit]
