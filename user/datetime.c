#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct datetime r;
  // 1. Check the syscall function is available
  if (datetime(&r) < 0) {
    fprintf(2, "datetime: syscall failed\n");
    exit(1);
  }

  // 2. Print the results returned from the kernel
  printf("Current System Time:\n");
  printf("  Date: %d/%d/%d\n",r.day, r.month, r.year);
  printf("  Time: %d:%d:%d\n", r.hour, r.minute, r.second);

  exit(0);
}
