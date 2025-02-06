#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clear_stdin() {
    char c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
    return 0;
}

int get_unum() {
    int result = 0;
    
    // Vide le buffer de stdout
    fflush(stdout);
    
    // Lecture d'un entier non signé
    if (scanf("%u", &result) != 1) {
        // Gestion d'une erreur de lecture
        result = 0;
    }
    
    // Nettoie le reste de la ligne d'entrée
    clear_stdin();
    
    return result;
}

int store_number(unsigned int *data) {
    unsigned int number, index;

    printf(" Number: ");
    number = get_unum();
    
    printf(" Index: ");
    index = get_unum();

    // Vérification de l'index
    if ((index % 3 == 0) || ((number >> 24) == 0xb7)) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    // Stockage du nombre à l'index spécifié
    data[index] = number;
    return 0;
}

int read_number(unsigned int *data) {
    unsigned int index;

    printf(" Index: ");
    index = get_unum();

    printf(" Number at data[%u] is %u\n", index, data[index]);
    return 0;
}

int main(int argc, char **argv, char **envp) {
    unsigned int data[100] = {0};
    char command[20];

    // Efface le contenu des arguments
    while (*argv) {
        memset(*argv, 0, strlen(*argv));
        argv++;
    }

    // Efface le contenu des variables d'environnement
    while (*envp) {
        memset(*envp, 0, strlen(*envp));
        envp++;
    }

    puts("--------------------------------");
    puts("Input command: ");
    
    while (1) {
        printf("Input command: ");
        fgets(command, sizeof(command), stdin);
        
        // Supprime le newline
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "store") == 0) {
            if (store_number(data) != 0) {
                printf(" Failed to do %s command\n", command);
            } else {
                printf(" Completed %s command successfully\n", command);
            }
        }
        else if (strcmp(command, "read") == 0) {
            if (read_number(data) != 0) {
                printf(" Failed to do %s command\n", command);
            } else {
                printf(" Completed %s command successfully\n", command);
            }
        }
        else if (strcmp(command, "quit") == 0) {
            break;
        }

        // Réinitialise la commande
        memset(command, 0, sizeof(command));
    }

    return 0;
}
