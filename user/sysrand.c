#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    printf("sysrand() test program\n");
    printf("======================\n\n");

    // Simple test - generate 5 numbers
    for(int i = 0; i < 5; i++) {
        printf("Random number %d: %d\n", i+1, sysrand());
    }

    // Test with fork
    printf("\nTesting with fork():\n");

    int pid = fork();
    if(pid == 0) {
        printf("Child:  sysrand() = %d\n", sysrand());
        exit(0);
    } else {
        wait(0);
        printf("Parent: sysrand() = %d\n", sysrand());
    }

    exit(0);
}
