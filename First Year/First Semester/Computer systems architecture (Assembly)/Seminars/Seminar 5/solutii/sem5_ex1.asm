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
    
    len equ 32
    biti times len+1 db 0
    format_afisare db "%d: %s", 13, 10, 0
    
; 1. Scrieți un program care citește de la tastatură un număr întreg și îl afișează în baza 2.
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
        
        ; obtin reprezentarea in baza 2
        mov ecx, len
        cld
        mov edi, biti
        repeta:
            xor al, al
            shl edx, 1
            adc al, '0'
            stosb
            loop repeta
        
        ; afisez sirul de biti
        ; printf(format_afisare, a, biti)
        push dword biti
        push dword [a]
        push dword format_afisare
        call [printf]
        add esp, 3*4
    
        jmp citire
    
    final:
        push dword 0
        call [exit]
