#include <stdio.h>

// Parcours tous les uint possibles, les multiplies par 4
// Et verifie si cela nous donne la valeur voulue
int main(void) {
    for (unsigned int i = 0; i < 4294967295; i++) {
        if (i << 2 == 456)
            printf("%d\n", i);
    }
}