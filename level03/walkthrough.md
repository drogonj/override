# Level03

## Analyse 

- La fonction `main()` call `scanf()` avec un `%d` qui sera notre variable `password`
Ensuite la fonction `test()` est call avec `password` et `0x1337d00d` (qui vaut 322424845 en decimal)

- On a une fonction `decrypt()` qui prend en parametre un int, une fonction `test()` qui prend en parametre deux int(qui sera notre variable `password` et `0x1337d00d`).

- La fonction `test()` soustrait les deux int et appel `decrypt()` avec cette difference si le resultat est <= 21.

- Si le resultat de cette soustraction est > 21 `decrypt()` est appele avec un int random (rand()).

- `Decrypt()` a donc en parametre notre difference :
- Avec cet int il fait des operations xor charactere par charactere avec "Q}|u`sfg~sf{}|a3"
- Ensuite un `strcmp()` compare le resultat des ces operations avec "Congratulations".
- Si le comparaison est true un system("/bin/sh") est call.

Il faut donc qu'on trouve avec quel int entre 1 et 21 faire nos comparaisons xor.

```
18 en binaire 
00010010

Q = 01010001 
    ^
    00010010 = 01000011 = 'C'

} = 01111101
    ^
    00010010 = 01101111 = 'o'
    
| = 01111100
    ^
    00010010 = 01101110 = 'n'

u = 01110101
    ^
    00010010 = 01100111 = 'g'

` = 01100000
    ^
    00010010 = 01110010 = 'r'

s = 01110011
    ^
    00010010 = 01100001 = 'a'

f = 01100110
    ^
    00010010 = 01110100 = 't'

g = 01100111
    ^
    00010010 = 01110101 = 'u'

~ = 01111110
    ^
    00010010 = 01101100 = 'l'

s = 01110011
    ^
    00010010 = 01100001 = 'a'

f = 01100110
    ^
    00010010 = 01110100 = 't'

{ = 01111011
    ^
    00010010 = 01101001 = 'i'

} = 01111101
    ^
    00010010 = 01101111 = 'o'

| = 01111100
    ^
    00010010 = 01101110 'n'
    
a = 01100001
    ^
    00010010 = 01110011 's'

3 = 00110011
    ^
    00010010 = 00100001 '!'
```

322424845 - 18 = 322424827

On a donc notre password a envoye au programme pour ouvrir le shell.

## Commandes

```bash
./level03
Password: 322424827
```

## flag 
```
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```