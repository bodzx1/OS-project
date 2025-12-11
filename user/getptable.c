#include "kernel/types.h"
#include "user/user.h"
const char *states[] = {
  [0] "UNUSED  ",
  [1] "USED    ",
  [2] "SLEEPING",
  [3] "RUNNABLE",
  [4] "RUNNING ",
  [5] "ZOMBIE  "
};
int main(int argc, char *argv[]) {
    struct pinfo ptable[10]; // Small buffer to fit on stack
    int nproc = 10;

    printf("PID\tPPID\tSTATE\tSIZE\tNAME\n");

    if (getptable(nproc, ptable) == 1) {
        for (int i = 0; i < nproc; i++) {
            if (ptable[i].pid != 0) {
                printf("%d\t%d\t%s %d\t%s\n",
                       ptable[i].pid,
                       ptable[i].ppid,
                       states[ptable[i].state],
                       (int)ptable[i].sz,
                       ptable[i].name);
            }
        }
    } else {
        printf("getptable failed\n");
    }
    exit(0);
}
