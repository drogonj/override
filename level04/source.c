#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <signal.h>

int main(int argc, char** argv, char** envp) {
    pid_t pid;
    int stat_loc = 0;
    char buffer[128];  // var_a0

    pid = fork();

    if (pid != 0) {  // Parent process
        while (1) {
            wait(&stat_loc);
            
            if (WIFEXITED(stat_loc) || WIFSIGNALED(stat_loc)) {
                puts("child is exiting...");
                break;
            }
            
            if (ptrace(PTRACE_PEEKUSER, pid, 4*ORIG_EAX, NULL) != 11) {  // 11 is the syscall number for execve
                continue;
            }
            
            puts("no exec() for you");
            kill(pid, SIGKILL);
            break;
        }
    } else {  // Child process
        prctl(PR_SET_PDEATHSIG, SIGTERM);
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        puts("Give me some shellcode, k");
        gets(buffer);  // Vulnerable to buffer overflow
    }
    
    return 0;
}
