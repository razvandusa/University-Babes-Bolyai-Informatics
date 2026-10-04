;2modul.asm
bits 32
global selectie
extern printf
import printf msvcrt.dll
segment data use32 class=data
    len_s2 dd 0
    offset_s2 dd 0
    
    octeti times 10 db 0   ; sirul de octeti distincti, pozitivi si pari
    numar_octeti dd 0       ; numarul de octeti distincti, pozitivi si pari
    
    format db "Suma: %xh", 13, 10, 0
    formatO db "%x ",0
    
segment code use32 class=code
        ; intrare:  argumente puse pe stivă
        ; iesire:   EAX = numar octeti care indeplinesc conditiile
    selectie:
        ; stochez local valorile argumentelor
        mov eax, [esp+4]
        mov [offset_s2], eax    ; offset-ul sirului s2
        mov eax, [esp+8]
        mov [len_s2], eax       ; numarul de octeti din s2
        
        ; parcurg sirul de octeti
        xor ebx, ebx            ; contor octeti
        mov ecx, [len_s2]
        mov esi, [offset_s2]
        mov edi, octeti
    cauta:
        lodsb                   ; AL <- [octet din s] + inc esi
        
        ; verific ca e POZITIV sau ZERO
        cmp al, 0
        je zero                 ; ZERO e PAR, sar peste verificare
        jl altul
        
        ; verific ca e PAR
        test al, 1
        jnz altul
        
    zero:
        ; daca e primul octet adaugat, nu mai verific ca e UNIC
        ; pentru ca numarul de octeti curent e 0, bucla de verificare va fi INFINITA 
        cmp ebx, 0
        je primul
        
        ; verific ca e UNIC
        mov [numar_octeti], ebx ; stochez numarul de octeti curent
        call verifica
        cmp edx, 1
        je altul
        
    primul:
        stosb                   ; octeti <- [octet din AL] + inc EDI
        inc ebx                 ; am mai adaugat un octet
        
    altul:
        loop cauta

        ; stochez numarul de octeti final
        mov [numar_octeti], ebx
        
        ; calculez suma octetilor
        mov ecx, [numar_octeti]
        mov esi, octeti
        xor eax, eax
        lodsb           ; EAX <- [primul octet] + inc ESI
        xor ebx, ebx    ; calculez suma in EBX
        mov bl, al      ; EBX <- [primul octet]
        dec ecx         ; sunt mai putini cu un octet
    aduna:
        xor eax, eax
        lodsb           ; EAX <- [octet curent] + inc ESI
        add ebx, eax
        loop aduna
        
        ; afisez suma calculata
        push ebx
        push dword format
        call [printf]
        add esp, 2*4
        
        
        ; afisez octetii calculata
        mov ecx, [numar_octeti]
        mov esi, octeti
        repA:
        push ecx
        xor eax,eax
        lodsb
        push dword eax
        push dword formatO
        call [printf]
        add esp, 2*4
        pop ecx
        loop repA
        
       
        
        ; returnez rezultatul in registrul EAX
        mov eax, [numar_octeti]
        
        ret
        
        
        ; --------------------------------------------------------
        ; verifica daca octetul din AL exista in sirul de octeti
        ; intrare:  AL = octet
        ; iesire:   EDX = 0 daca AL nu exista in sirul de octeti d
    verifica:
        push edi
        push ecx
        
        mov ecx, [numar_octeti]
        mov edi, octeti     ; offset-ul sirului de octeti
        xor edx, edx        ; EDX = 0
    .repeta:
        scasb               ; cmp AL, <ES:EDI> + inc EDI
        je .exista
        loop .repeta
        
        jmp .nu_exista
        
    .exista:
        mov edx, 1          ; octetul din AL exista in sirul de octeti
        
    .nu_exista:
        pop ecx
        pop edi
        
        ret
