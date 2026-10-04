bits 32 
global start        
extern exit, printf, procesare            
import exit msvcrt.dll   
import printf msvcrt.dll

segment data use32 class=data
    sir db 'Ana are mere Ada are fructul pasiunii Gigel are ananas Tudor are portocale si facem salata de fructe',0  
    nr dd 0 
    format db '%c',0
    counter dd 0
    cifrehexa db '0123456789ABCDEF'
    adresaCuvant dd 0
    final db 0

segment code use32 class=code
    start:
        mov esi, sir 
        mov ebx, 0 
        
        bucla:
        mov [adresaCuvant], esi     ;stocam adresa pt afisare
        
        push dword 0   ;pt nr vocale
        push dword 0   ;pt nr consoane 
        push esi       	 ;adresa secventei curente
        call procesare 	;returneaza pe stiva numar vocale si numar litere 
        add esp, 4
        pop eax     ;eax = nr consoane
        pop edx     ;edx = nr vocale
        
        
        dec esi    	 ;lodsb in functie crescuse esi, dar revenim pe spatiu sau 0
        cmp byte [esi], 0  ;daca deja e 0 suntem la final, setam final pe 1 
        jne notTheEnd
        mov byte [final], 1 ;Atentie! Sa nu sara peste ultimul cuvant, trebuie afisat si el daca respecta conditiile
         
        notTheEnd:
        test edx, 1 
        jnz nextWord        ;sare direct peste daca nu e numar par de vocale
                                
        test eax, 1 ;ebx = numar de consoane
        jz nextWord         ; sare peste daca nu e numar impar de consoane
        
        inc dword [nr]      ;counter pt cuvintele care trebuie afisate
        
        
        
        mov byte [esi], 0  ;trebuie afisat cuvantul, inlocuim spatiul cu 0 ca sa putem afisa direct (daca suntem la final il suprascriem, dar nu conteaza)
        push dword [adresaCuvant] 
        call [printf]
        add esp, 4                                     
        
        nextWord:  
        inc esi     ;ca sa trecem la urmatorul cuvant 
        cmp byte [final], 1
        jne bucla
        
        ;print nr in base 16 
        mov eax, [nr]
        mov ebx, 16 
        mov ecx, 0 ;counter for number of digits
        
        convert:
        mov edx, 0 
        div ebx 
        push edx 
        inc ecx             
        cmp eax, 0 
        jne convert 
        
        print: 
        mov [counter],ecx        ;nu putem face push ecx!!! atunci nu mai avem numarul pentru afisare pe stiva, ci afiseaza ecx  
        
        ;"cifra" e pe stiva, dar trebuie inlocuita cu o litera fie folosind xlat, fie cu comparatii manuale 
        pop eax 
        mov ebx, cifrehexa
        xlat                ;transforma 10 -> A, 11 -> B 
         
        push eax
        push dword format
        call [printf]
        add esp,4*2   ;!! we take two parameters out from the stack 
        
        mov ecx,[counter]
        loop print 
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program






