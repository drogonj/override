#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>

#define BUFFER_SIZE 32

int auth(char* login, int serial) {
    size_t len;
    int i;
    unsigned int hash;

    login[strcspn(login, "\n")] = '\0';
    len = strnlen(login, BUFFER_SIZE);

    if (len <= 5) return 1;

    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
        puts("\033[32m.------------------------.");
        puts("\033[31m| !! TAMPERING DETECTED !!|");
        puts("\033[32m'------------------------'");
        return 1;
    }

    hash = ((login[3] ^ 0x1337) + 0x5eeded); /*(0x5eeded = 6221293d)*/
/*
    1337:
    00010011 00110111
*/
    for (i = 0; i < len; i++) {
        if (login[i] <= 0x1f) return 1; /*(0x1f = 31d)*/
        hash += ((login[i] ^ hash) % 0x539);  /*(0x539 == 1337d)*/
    }

    return (serial == hash) ? 0 : 1;
}

int main(int argc, char** argv) {
    char login[BUFFER_SIZE];
    int serial;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");

    printf("-> Enter Login: ");
    fgets(login, BUFFER_SIZE, stdin);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");

    printf("-> Enter Serial: ");
    scanf("%d", &serial);

    if (auth(login, serial) == 0) {
        puts("Authenticated!");
        system("/bin/sh");
        return 0;
    }

    return 1;
}
