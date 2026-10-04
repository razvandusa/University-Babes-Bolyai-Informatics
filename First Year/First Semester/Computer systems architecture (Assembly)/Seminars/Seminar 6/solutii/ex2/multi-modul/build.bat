nasm -fobj ex2_main.asm
nasm -fobj ex2_modul.asm

alink ex2_main.obj ex2_modul.obj -oPE -subsys console -entry start
