#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc==1)
  printf("sleeps for a certain amount of time\n");
  else if(argc>2)
  printf("too many arguments passed\n");
  else
  {
  int sleeptime=atoi(argv[1]);
  printf("will sleep for %d \n",sleeptime);
  sleep(sleeptime);
  printf("Sleep Done\n");
  }

  exit(0);
}
