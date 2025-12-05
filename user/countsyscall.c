#include "kernel/types.h"
#include "user/user.h"

int main() {
    int count = countsyscall();
    printf("System calls since boot: %d\n", count);

    // Test by making more syscalls
    printf("Making some syscalls...\n");
    getpid();
    fork();

    int new_count = countsyscall();
    printf("System calls after getpid and fork: %d\n", new_count);

    exit(0);
}
