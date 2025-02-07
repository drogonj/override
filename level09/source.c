#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 0x7fffffffe3f0
struct s_data {
    char message[140];  // data+0
    char username[40];  // data+140
    int32_t msg_length; // data+180
} t_data;

int64_t secret_backdoor() {
    char buffer[128]
    fgets(buffer, 128, stdin);
    return system(buffer);
}

int64_t handle_msg() {
    t_data user_data;
    memset(user_data.username, 0, 40);
    user_data.msg_length = 140;

    set_username(&user_data);
    set_msg(&user_data);

    return puts(">: Msg sent!");
}

char* set_msg(t_data* user_data) {
    char buffer[1024];
    memset(buffer, 0, 1024);

    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets(buffer, 1024, stdin);

    return strncpy(user_data->message, buffer, user_data->msg_length);
}

int64_t set_username(t_data *user_data) {
    char buffer[128];
    memset(buffer, 0, 128);

    puts(">: Enter your username");
    printf(">>: ");
    fgets(buffer, 128, stdin);

    for (int32_t i = 0; i <= 40; i++) {
        if (buffer[i] == 0) {
                    break;
        }
        user_data->username[i] = buffer[i];
    }

    return printf(">: Welcome, %s", user_data->username);
}

int32_t main(int32_t argc, char** argv, char** envp) {
    puts("--------------------------------…");
    handle_msg();
    return 0;
}