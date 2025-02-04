char a_user_name[256];

int32_t verify_user_name() {
    puts("verifying username....\n");

    if (strlen(&a_user_name) < 7)
        return -1;

    if (strncmp(&a_user_name, "dat_wil", 7) != 0)
        return -1;

    return 0;
}

int32_t verify_user_pass(char* arg1) {
    if (strlen(arg1) < 5)
        return -1;

    if (strncmp(arg1, "admin", 5) != 0)
        return -1;

    return 0;
}

int32_t main(int32_t argc, char** argv, char** envp) {
    char var_54[64];
    __builtin_memset(var_54, 0, sizeof(var_54));

    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(&a_user_name, 256, stdin);

    if (verify_user_name() != 0) {
        puts("nope, incorrect username...\n");
        return 1;
    }

    puts("Enter Password: ");
    fgets(var_54, 100, stdin);

    if (verify_user_pass(var_54) == 0) {
        puts("Access granted!");
        return 0;
    }

    puts("nope, incorrect password...\n");
    return 1;
}
