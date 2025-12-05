#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
    if(argc != 3){
        fprintf(2, "Usage: mv source destination\n");
        exit(1);
    }

    char *src = argv[1];
    char *dst = argv[2];

    // Try to add a new link to the file (create new name)
    if(link(src, dst) < 0){
        fprintf(2, "mv: cannot move %s to %s (link failed)\n", src, dst);
        exit(1);
    }

    // Remove the old name
    if(unlink(src) < 0){
        // If unlink fails, we must remove the new link to avoid duplicates
        unlink(dst);
        fprintf(2, "mv: cannot remove old file %s\n", src);
        exit(1);
    }

    exit(0);
}
