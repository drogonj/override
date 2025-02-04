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