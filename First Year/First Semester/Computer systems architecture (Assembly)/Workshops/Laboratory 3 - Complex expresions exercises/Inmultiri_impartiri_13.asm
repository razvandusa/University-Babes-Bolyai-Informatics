bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; x-(a+b+c*d)/(9-a); a,c,d-byte; b-doubleword; x-qword
    a db 7
    c db 3
    d db 3
    b dd 100
    x dq 1000
    var db 9

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al,[c]
        imul byte[d]
        cwd
        add ax,word[b]
        add dx,word[b+2]
        mov bx,ax
        mov cx,dx
        mov al,[a]
        cbw
        add bx,ax
       
        mov al,[a]
        neg al
        add al,[var]
        cbw
        mov si,ax
        
        mov ax,bx
        mov dx,cx
        idiv si
        cwde
        cdq
        neg EAX
        neg EDX
        add EAX,dword[x]
        add EDX,dword[x+4]
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
