#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
    if(argc != 3){
        printf("Usage: cp <source> <destination>\n");
        exit(1);
    }

    int src, dest;
    char buf[512];
    int n;

    src = open(argv[1], O_RDONLY);
    if(src < 0){
        printf("cp: cannot read %s\n", argv[1]);
        exit(1);
    }

    dest = open(argv[2], O_WRONLY | O_CREATE);
    if(dest < 0){
        printf("cp: cannot write %s\n", argv[2]);
        close(src);
        exit(1);
    }

    while((n = read(src, buf, sizeof(buf))) > 0){
        if(write(dest, buf, n) != n){
            printf("cp: write error\n");
            close(src);
            close(dest);
            exit(1);
        }
    }

    close(src);
    close(dest);

    exit(0);
}
