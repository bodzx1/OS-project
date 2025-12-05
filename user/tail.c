#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define BUF_SIZE 1024


int
main(int argc, char *argv[])
{
    int nlines = 10;
    int fd = 0;
    int start_arg = 1;


    if(argc > 1 && strcmp(argv[1], "-n") == 0){
        if(argc < 4){
            printf("Usage: tail [-n N] file\n");
            exit(1);
        }
        nlines = atoi(argv[2]);
        if(nlines < 1) nlines = 1;
        start_arg = 3;
    }


    if(argc > start_arg){
        fd = open(argv[start_arg], O_RDONLY);
        if(fd < 0){
            printf("tail: cannot open %s\n", argv[start_arg]);
            exit(1);
        }
    }


    char *lines[300];
    int count = 0;

    for(int i = 0; i < 300; i++){
        lines[i] = malloc(BUF_SIZE);
        if(lines[i] == 0){
            printf("tail: out of memory\n");
            exit(1);
        }
    }

    char buf[1];
    int idx = 0;
    int current = 0;


    while(read(fd, buf, 1) == 1){
        if(buf[0] == '\n' || idx == BUF_SIZE - 1){
            lines[current][idx] = '\0';
            current = (current + 1) % 300;
            idx = 0;
            count++;
        } else {
            lines[current][idx++] = buf[0];
        }
    }


    if(idx > 0){
        lines[current][idx] = '\0';
        count++;
        current = (current + 1) % 300;
    }


    int to_print = nlines;
    if(to_print > count)
        to_print = count;


    int start = (current - to_print + 300) % 300;


    for(int i = 0; i < to_print; i++){
        int index = (start + i) % 300;
        printf("%s\n", lines[index]);
    }


    for(int i = 0; i < 300; i++)
        free(lines[i]);

    if(fd != 0)
        close(fd);

    exit(0);
}
