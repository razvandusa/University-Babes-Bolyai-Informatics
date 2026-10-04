bits 32
global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    text db "ana are mere capac un cojoc otto "
    len equ $-text      ; numarul de caractere din text
    
    cuvant times 50 db 0    ; are
    invers times 50 db 0    ; era
    
    format db "Cuvant: %s", 13, 10, 0
    
; 7. Se dă un unui șir de octeți reprezentând un text
; (o succesiune de șiruri de caractere separate prin spații).
; Să se determine cuvintele din șirul p care sunt palindroame
; (de exemplu: ana, coc, capac, cojoc etc.).
segment code use32 class=code
    verific:
        dec ecx             ; am iesit din ciclu deci ECX nu a fost decrementat
        push ecx
        push esi
        push edi
        
        ; inversez cuvantul
        mov ecx, ebx
        mov esi, cuvant
        mov edi, invers
        add edi, ebx
        dec edi
    inverseaza:
        cld
        lodsb
        std
        stosb
        loop inverseaza
        
        ; verific daca e palindrom
        mov ecx, ebx
        cld
        mov esi, cuvant
        mov edi, invers
        repe cmpsb
        
        cmp ecx, 0
        je e_palindrom
        jmp peste
    
    e_palindrom:
        ; afisez cuvantul
        cld
        push dword cuvant
        push dword format
        call [printf]
        add esp, 4*2
    
    peste:
        pop edi
        pop esi
        pop ecx
        cmp ecx, 0
        je final
        jmp urmator

        ; programul incepe aici
    start:
        mov ecx, len
        jecxz final
        cld
        mov esi, text
    urmator:
        mov ebx, 0          ; numar literele din cuvant
        mov edi, cuvant
    repeta:
        ; citim caracterul curent
        lodsb
        
        ; verificam daca e spatiu
        cmp al, ' '
        je verific
        
        ; nu e spatiu, deci il stocam in sirul 'cuvant'
        stosb
        inc ebx             ; am adaugat inca o litera in cuvant
        loop repeta

    final:
        push dword 0
        call [exit]
