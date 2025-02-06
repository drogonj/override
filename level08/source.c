#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int64_t log_wrapper(FILE* log_file, char* prefix, char* message) {
    char buffer[264] = {0};
    strcpy(buffer, prefix);

    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "%s", message);
    buffer[strcspn(buffer, "\n")] = '\0';
    fprintf(log_file, "LOG: %s\n", buffer);

    int64_t result;
    __asm__ volatile (
        "movq %%fs:0x28, %0;"
        "xorq %%fs:0x28, %0;"
        : "=r" (result)
    );

    if (result != 0) {
        __stack_chk_fail();
    }

    return result;
}

int32_t main(int32_t argc, char** argv, char** envp) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE* log_file = fopen("./backups/.log", "w");
    if (log_file == NULL) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }

    log_wrapper(log_file, "Starting back up: ", argv[1]);

    FILE* source_file = fopen(argv[1], "r");
    if (source_file == NULL) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
    }

    char backup_path[100] = "./backups/";
    strncat(backup_path, argv[1], sizeof(backup_path) - strlen(backup_path) - 1);

    int fd = open(backup_path, O_WRONLY | O_CREAT | O_TRUNC, 0640);
    if (fd < 0) {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(1);
    }

    char buf;
    while ((buf = fgetc(source_file)) != EOF) {
        write(fd, &buf, 1);
    }

    log_wrapper(log_file, "Finished back up ", argv[1]);

    fclose(source_file);
    close(fd);

    int64_t result;
    __asm__ volatile (
        "movq %%fs:0x28, %0;"
        "xorq %%fs:0x28, %0;"
        : "=r" (result)
    );

    if (result != 0) {
        __stack_chk_fail();
    }

    return 0;
}