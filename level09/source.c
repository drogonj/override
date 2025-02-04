#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fonction qui lit une commande depuis l'entrée standard et l'exécute
int64_t secret_backdoor() {
    char buffer[128]; // Buffer de 128 octets
    fgets(buffer, 128, stdin); // Lit jusqu'à 128 octets depuis stdin
    return system(buffer); // Exécute la commande lue
}

// Fonction qui gère la création et l'envoi d'un message
int64_t handle_msg() {
    char s[40]; // Buffer de 40 octets
    memset(s, 0, 40); // Initialise le buffer à 0
    int32_t msg_length = 140; // Longueur du message

    - // Buffer pour les données utilisateur
    set_username(user_data); // Définit le nom d'utilisateur
    set_msg(user_data); // Définit le message

    return puts(">: Msg sent!"); // Affiche un message de confirmation
}

// Fonction qui définit le message
char* set_msg(char* msg_buffer) {
    char buffer[1024]; // Buffer de 1024 octets
    memset(buffer, 0, 1024); // Initialise le buffer à 0

    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets(buffer, 1024, stdin); // Lit jusqu'à 1024 octets depuis stdin

    // Copie le message dans le buffer fourni, avec une longueur limitée
    return strncpy(msg_buffer, buffer, *(int32_t*)(msg_buffer + 180));
}

// Fonction qui définit le nom d'utilisateur
int64_t set_username(int64_t user_buffer) {
    char buffer[128]; // Buffer de 128 octets
    memset(buffer, 0, 128); // Initialise le buffer à 0

    puts(">: Enter your username");
    printf(">>: ");
    fgets(buffer, 128, stdin); // Lit jusqu'à 128 octets depuis stdin

    // Copie le nom d'utilisateur dans le buffer fourni
    for (int32_t i = 0; i <= 40; i++) {
        if (buffer[i] == 0) break; // Arrête si on rencontre un caractère nul
        *(char*)(user_buffer + 140 + i) = buffer[i]; // Copie caractère par caractère
    }

    return printf(">: Welcome, %s", (char*)(user_buffer + 140)); // Affiche un message de bienvenue
}

// Fonction principale
int32_t main(int32_t argc, char** argv, char** envp) {
    puts("--------------------------------…");
    handle_msg(); // Gère la création et l'envoi du message
    return 0;
}