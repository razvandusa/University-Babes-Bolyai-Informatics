nasm -fobj ex1_main.asm
nasm -fobj ex1_modul.asm

alink ex1_main.obj ex1_modul.obj -oPE -subsys console -entry start
