#include "kernel/types.h"
#include "user/user.h"

int main() {
    printf("shutting down...\n");
    printf("QEMU: TERMINATED (using function)");
    shutdown();
    return 0;
}
