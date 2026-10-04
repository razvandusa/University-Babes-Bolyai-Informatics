bits 32
global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    max equ 10
    sir times max dd 0, 0
    
    format_citire db "%d", 0
    msg db "Dati elementele sirului (maxim 100): ", 0
    n dd 0                                              ; numarul curent
    len dd 0                                            ; numarul de elemente citite
    
    text db "Sirul: ", 0
    format_afisare db "%d ", 0

; 3. Scrieți un program care citește de la tastatură un șir de numere întregi și îl afișează în ordine crescătoare/descrescătoare.
segment code use32 class=code
    sortare:
        mov ecx, [len]              ; ECX = numarul de elemente
        cmp ecx, 0
        je final
        dec ecx                     ; 0 <= i < len-1
        mov esi, 0                  ; i = 0
    loop_1:
        mov eax, [sir+4*esi]        ; EAX = s[i]
        
        mov ebx, esi
        inc ebx                     ; i+1 <= j < len
        loop_2:
            mov edx, [sir+4*ebx]    ; EDX = s[j]
            
            cmp eax, edx
            ja no_swap
            
            ; daca sir[i] >= sir[j], interschimb elementele
            mov [sir+4*ebx], eax
            mov [sir+4*esi], edx
            mov eax, edx
            
            ; daca sir[i] < sir[j], nu interschimb elementele
        no_swap:
            inc ebx                 ; j++
            cmp ebx, [len]          ; verific daca am ajuns la ultimul element
            jb loop_2               ; daca j < len, reiau ciclul

    next:
        inc esi                     ; i++
        loop loop_1
        
        ret

    start:
        ; afisez mesaj
        ; printf(msg)
        push dword msg
        call [printf]
        add esp, 1*4
        
        ; citesc elementele
        cld
        mov ebx, 0      ; numarul de elemente
        mov edi, sir
    citire:
        ; scanf(format_citire, &n)
        push dword n
        push dword format_citire
        call [scanf]
        add esp, 2*4
        
        mov eax, [n]
        cmp eax, ' '
        je e_spatiu
        cmp eax, 0
        je mai_departe
        
        stosd           ; stochez numarul citit
        inc ebx         ; incrementez numarul de elemente
        
    e_spatiu:
        jmp citire
        
    mai_departe:
        mov [len], ebx
        call sortare
    
        ; afisez text
        ; printf(text)
        push dword msg
        call [printf]
        add esp, 1*4
        
        ; afisez fiecare element
        mov ecx, [len]
        mov esi, sir
    afisare:
        push ecx
        lodsd
        
        ; printf(format, eax)
        push eax
        push dword format_afisare
        call [printf]
        add esp, 2*4
        
        pop ecx
        loop afisare
    
    final:
        push dword 0
        call [exit]
