0x1337d00d -> 322424845

test() fait 322424845 - notre_entree
puis switch case.
Appel decrypt(rand()) si resultat > 0x15(21).

Sinon appel decrypt(resultat).

decrypt() possede une chaine encodee "Q}|u`sfg~sf{}|a3" puis fait un xor sur chaque caracteres de cette chaine avec notre argument.

De cette facon si la chaine encodee devient "Congratulations!" on a gagne et un bash s'ouvre.

Suffit de trouver le xor pour "Q"->"C" et c'est bon.

"Q" xor 18 -> "C"

322424845 - 18 = 322424827

kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf