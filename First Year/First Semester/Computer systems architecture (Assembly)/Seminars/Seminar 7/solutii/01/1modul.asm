;1modul.asm
bits 32 ; assembling for the 32 bits architecture
global procesare       
segment data use32 class=data
    vocale db 'aeiouAEIOU'

segment code use32 class=code
    
        procesare:
        ;esp - ret adr
        ;esp +4 - adresa sir
        ;esp +8 - pt nr consoane
        ;esp + 12 - pt nr vocale
        
        mov ebx, 0 
        mov edx, 0        
        bucla:
        lodsb 
        cmp al, 0   ;Atentie! Sa nu sara peste ultimul cuvant
        je done
        
        cmp al,' '      ;next word 
        je done
        
        mov edi, vocale
        mov ecx, 10
        repne scasb     
        jne consoane
        inc ebx     ;counter vocale  
        jmp nextLetter
        
        consoane:
        inc edx     ;counter consoane
        nextLetter:
        jmp bucla 
        
        done:
        mov [esp+8], edx 
        mov [esp+12], ebx
        
        ret       

