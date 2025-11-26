#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc!=3)
  {
  printf("error,arguments missing\n");
  exit(0);
  }

  int num1=atoi(argv[1]);
  int num2=atoi(argv[2]);
  int res=num1+num2;
  printf("sum is %d \n",res);
  exit(0);
}
