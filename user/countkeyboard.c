#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
 int cntr=kbdint();
 printf("keyboard interrupt counter is %d \n",cntr);
  exit(0);
}
