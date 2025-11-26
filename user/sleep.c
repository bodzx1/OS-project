#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int sleeptime=atoi(argv[1]);
  printf("will sleep for %d \n",sleeptime);
  sleep(sleeptime);
  printf("Sleep Done\n");

  exit(0);
}
