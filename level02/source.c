#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv, char** envp) {
    char username[100] = {0}; 
    char password[100] = {0};
    char stored_password[41] = {0}; 

    FILE* fp = fopen("/home/users/level03/.pass", "r");
    if (fp == NULL) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }

    size_t bytes_read = fread(stored_password, 1, 40, fp);
    stored_password[strcspn(stored_password, "\n")] = '\0';

    if (bytes_read != 40) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        fclose(fp);
        exit(1);
    }

    fclose(fp);
    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\***************************************/");

    printf("--[ Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("--[ Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    puts("****************************************");

    if (strncmp(stored_password, password, 40) == 0) {
        printf("Greetings, %s!\n", username);
        system("/bin/sh");
        return 0;
    } else {
        printf("%s does not have access!\n", username);
        exit(1);
    }
}