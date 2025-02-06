Un serialKey est genere en fonction du login en parametre.
On pourrait reverse la fonction de hash mais nous on va juste utiliser GDB.
ya un ptit ptrace() pour proteger mais trql on s'en fou.

Dans auth():
0x080487b5 <+109>:   call   0x80485f0 <ptrace@plt>
0x080487ba <+114>:   cmp    $0xffffffff,%eax    // Donc breakpoint ici pour set $eax=0

ici auth() compare notre serialKey a celui-ci genere dans le code.
0x08048863 <+283>:   mov    0xc(%ebp),%eax
0x08048866 <+286>:   cmp    -0x10(%ebp),%eax    // Breakpoint ici (-0x10(%ebp) est le serial genere)
0x08048869 <+289>:   je     0x8048872 <auth+298>

Essayons avc le login "aaaaaaaa":

(gdb) r
Starting program: /home/users/level06/level06 
***********************************
*               level06           *
***********************************
-> Enter Login: aaaaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 1234                           // On met un truc au pif
Breakpoint 1, 0x080487ba in auth ()             // Breakpoint apres le ptrace()
(gdb) set $eax=0                                // Bypass ptrace()
(gdb) c
Continuing.

Breakpoint 2, 0x08048866 in auth ()             // Breakpoint a la comparaison entre notre serial et le serial genere
(gdb) x/d $ebp-0x10                             // On print le serial genere
0xffffd5a8:     6233748


Plus qu'a relancer le code sans gdb et a entrer le serial.

level06@OverRide:~$ ./level06 
***********************************
*               level06           *
***********************************
-> Enter Login: aaaaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6233748
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8

# Level06

## Analyse

- On a ici une fonction main avec un buffer login et un int serial comme variable.

- Le login est recupere par fgets() via stdin

- Le serial est recupere par l'entree scanf()

- Les deux variables sont passes en parametre a la fonction auth().

- La fonction auth() : 
    - null-terminate le buffer login
    - Protege le debug via ptrace()
    - la variable hash est initialise avec login[3] xor 0x1337 + 0x5eeded
    - Une boucle parcours le buffer login avec un check si le char est <= 31 dans ce cas return 1
    - Ensuite le hash est constitue avec un login[i] xor hash modulo 539
    - Si serial == hash return 0, sinon 1.

## Exploitation

- Ici on pourrait reverse l'algorithme qui calcule qui le hash mais ce serait beaucoup trop de boulot parce qu'on a ici une belle variable hash qui est donc dans la stack et que l'on peut tres facilement read en memoire.

- Le seul probleme est la fonction ptrace() qui bloque le debug mais encore ici nous avons la solution. Voyons cela en detail :

- Voici un exemple d'execution du programme via gdb, on voit bien que ptrace() detecte bien le debug.

```nasm
(gdb) r
Starting program: /home/users/level06/level06 
***********************************
*               level06           *
***********************************
-> Enter Login: aaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: aaaaaa
.---------------------------.
| !! TAMPERING DETECTED !!  |
'---------------------------'
[Inferior 1 (process 1742) exited with code 01]
```

- Pour contourner cette protection nous devons modifier le retour de la fonction ptrace() au lieu de retourner -1 nous voulons modifier cette valeur a 0.

```
0x080487b5 <+109>:   call   0x80485f0 <ptrace@plt>
0x080487ba <+114>:   cmp    $0xffffffff,%eax
```

- Dans ce code asm on observe le call a ptrace qui ensuite fait une operation de comparaison entre le registre eax et -1.

- Il suffit donc de mettre un breakpoint a l'instruction +114 et modifie eax :

```
(gdb) b *auth+114
(gdb) set $eax=0
```

- Une fois cette protection passee nous pouvons continuer notre debug pour aller lire notre variable hash en memoire.

- Dans le code disas a la fin de la fonction auth on a une comparaison interessante et un jump si cette comparaison est egale avec un return 0.  

```
0x08048866 <+286>:   cmp    -0x10(%ebp),%eax
0x08048869 <+289>:   je     0x8048872 <auth+298>
0x08048872 <+298>:   mov    $0x0,%eax
0x08048877 <+303>:   leave  
0x08048878 <+304>:   ret   
```