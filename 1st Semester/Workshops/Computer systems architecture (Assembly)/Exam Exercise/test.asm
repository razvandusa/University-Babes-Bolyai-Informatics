bits 32

global start

extern exit,printf,scanf,fopen,fclose,fread,fprintf
import exit msvcrt.dll              ;exit
import printf msvcrt.dll            ;print la consola - printf(format,text)
import scanf msvcrt.dll             ;citire la consola - scanf(format,text)
import fopen msvcrt.dll             ;deschidere fisier - fopen(fisier,mod_acces)
import fclose msvcrt.dll            ;inchidere fisier - fclose(descriptor)
import fread msvcrt.dll             ;citire din fisier - fread(text,size,len,descriptor)
import fprintf msvcrt.dll           ;print in fisier - fprintf(descriptor,format,text)

segment data use32 class=data
    fisier_input db "input.txt",0
    fisier_output db "output.txt",0
    descriptor dd -1
    descriptor_I dd -1
    mod_acces_I db "r",0
    mod_acces_II db "w",0
    format_afisare db "%s %d",0
    
    propozitii times 101 db 0
    contor dw 0
    spatiu db ' ',0
    cuvant times 100 db 0
    endl db 10 ;caracterul \n
segment code use32 class=code
    start:
        ;deschidem fisierul input.txt - fopen(fisier,mod_acces)
        push dword mod_acces_I
        push dword fisier_input
        call[fopen]
        mov [descriptor],eax
        add esp,4*2
        
        ;verificam daca s-a deschis fisierul (eax!=0)
        cmp eax,0
        je exit
        mov eax,0
        
        ;deschidem fisierul output.txt - fopen(fisier,mod_acces)
        push dword mod_acces_II
        push dword fisier_output
        call[fopen]
        mov [descriptor_I],eax
        add esp,4*2
        
        ;verificam daca s-a deschis fisierul (eax!=0)
        cmp eax,0
        je exit
        
        ;citim continutul din fisier - fread(text,size,len,descriptor)
        push dword [descriptor]
        push dword 101
        push dword 1
        push dword propozitii
        call [fread]
        add esp,4*4
        
        ;prelucram propozitia
        mov esi, propozitii ;punem in esi adresa de unde incep propozitiile
        mov edi, cuvant ;punem in edi adresa penultimului cuvant
        iterare_litere:
            lodsb ;mutam in al literele pe rand din propozitii
            
            ;verificam daca am terminat o propozitie
            cmp al,'.'
            je propozitie_terminata
            
            movsb
            dec esi
            ;verificam daca am terminat propozitiile
            cmp al,0
            je exit
            
            ;verificam daca am terminat un cuvant
            cmp al,' '
            je cuvant_terminat
            
            ;revenim la urmatoarea litera
            jmp iterare_litere
        
        cuvant_terminat:
            ;incrementam un contor pentru un cuvant
            inc dword[contor]
            ;punem in edi urmatorul cuvant
            mov edi, cuvant
            jmp iterare_litere
            
        propozitie_terminata:
            dec edi
            mov byte[edi], 0
            ;afisam cuvantul in fisier - fprintf(descriptor,format,text)
            push dword [contor]
            push dword spatiu
            push dword cuvant
            push dword format_afisare
            push dword [descriptor_I]
            call[fprintf]
            add esp,4*5
            
            mov dword[contor], 0
            jmp iterare_litere
    exit:
        push dword [descriptor]
        call [fclose]
        add esp, 4
        
        push dword [descriptor_I]
        call [fclose]
        add esp, 4
        
        push dword 0
        call [exit]