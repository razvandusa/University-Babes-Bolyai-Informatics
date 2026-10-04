bits 32
global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
	a dd 0
    mesaj db 'Dati un intreg: ', 0
    format db "%d", 0
    
    zece dd 10
    format_afisare db "Cifre: %d", 13, 10, 0
    
; 2. Scrieți un program care citește de la tastatură un număr întreg
; și afișează câte cifre are numărul citit în baza 10.
segment code use32 class=code
    start:
    citire:
        ; afisez mesaj
        ; printf(mesaj)
        push dword mesaj
        call [printf]
        add esp, 1*4
        
        ; citesc numarul
        ; scanf(format, &a)
        push dword a
        push dword format
        call [scanf]
        add esp, 2*4
        
        ; verific daca s-a introdus valoarea 0
        mov edx, [a]
        cmp edx, 0
        je final
        
        ; verific daca numarul e pozitiv/negativ
        mov eax, [a]
        cmp eax, 0
        jg pozitiv
        
        neg eax         ; e negativ, il negam
        
    pozitiv:
        ; determin numarul de cifre in baza 10
        mov edx, 0      ; edx:eax = a
        mov ebx, 1      ; contor
    repeta:
        div dword [zece]
        cmp eax, 0
        je afisare
        inc ebx
        mov edx, 0
        jmp repeta
        
    afisare:
        ; afisez numarul de cifre
        ; printf(format_afisare, EBX)
        push dword ebx
        push dword format_afisare
        call [printf]
        add esp, 2*4
    
        jmp citire

    final:
        push dword 0
        call [exit]
