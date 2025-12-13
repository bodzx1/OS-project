#include "kernel/types.h"
#include "user/user.h"

int main() {
    printf("shutting down...\n");
    printf("QEMU: TERMINATED (using the function)\n");
    shutdown();
    return 0;
}
