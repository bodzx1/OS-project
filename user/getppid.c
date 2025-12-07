#include "kernel/types.h"
#include "user/user.h"

int main() {
    int pid = getpid();
    int ppid = getppid();

    printf("My PID: %d\n", pid);
    printf("My Parent's PID: %d\n", ppid);

    // Test with fork
    int child_pid = fork();
    if(child_pid == 0) {
        // Child process
        printf("Child: My PID: %d\n", getpid());
        printf("Child: My Parent's PID: %d\n", getppid());
        exit(0);
    } else {
        // Parent process
        wait(0);
        printf("Parent: I'm still PID: %d\n", getpid());
    }

    exit(0);
}
