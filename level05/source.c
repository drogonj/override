#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv, char** envp) {
    char buffer[100] = {0};
    int index = 0;

    fgets(buffer, sizeof(buffer), stdin);

    while (1) {
        int length = strlen(buffer);

        if (index >= length) {
            break;
        }

        // Vérification si le caractère est une lettre majuscule (A-Z)
        if (buffer[index] > 0x40 && buffer[index] <= 0x5A) {
            // Conversion en minuscule en utilisant XOR avec 0x20
            buffer[index] ^= 0x20;
        }
        index++;
    }
    printf("%s", buffer);
    exit(0);
}