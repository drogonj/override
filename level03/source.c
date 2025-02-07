#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void decrypt(int key) {
    char password[] = "Q}|u`sfg~sf{}|a3";
    int len = strlen(password);
    
    for (int i = 0; i < len; i++) {
        password[i] ^= key;
    }
    
    if (strcmp(password, "Congratulations!") == 0) {
        system("/bin/sh");
    } else {
        puts("\nInvalid Password");
    }
}

void test(int a, int b) {
    int diff = b - a;
    
    if (diff > 0x15) { // 21d
        decrypt(rand());
        return;
    }
    
    switch (diff) {
        case 1: decrypt(diff); break;
        case 2: decrypt(diff); break;
        case 3: decrypt(diff); break;
        case 4: decrypt(diff); break;
        case 5: decrypt(diff); break;
        case 6: decrypt(diff); break;
        case 7: decrypt(diff); break;
        case 8: decrypt(diff); break;
        case 9: decrypt(diff); break;
        case 10: decrypt(diff); break;
        case 11: decrypt(diff); break;
        case 12: decrypt(diff); break;
        case 13: decrypt(diff); break;
        case 14: decrypt(diff); break;
        case 15: decrypt(diff); break;
        case 16: decrypt(diff); break;
        case 17: decrypt(diff); break;
        case 18: decrypt(diff); break;
        case 19: decrypt(diff); break;
        case 20: decrypt(diff); break;
        case 21: decrypt(diff); break;
        default: decrypt(rand()); break;
    }
}

int main() {
    int input;
    srand(time(0));
    
    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    printf("Password:");
    scanf("%d", &input);
    
    test(input, 0x1337d00d); // 322424845d
    
    return 0;
}