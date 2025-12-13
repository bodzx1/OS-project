#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int fact(int x)
{
  if(x==1)
  return 1;
  else return x*fact(x-1);

}
int
main(int argc, char *argv[])
{
  if(argc==1)
  printf("returns the factorial of a given number\n"),exit(0);
  if(argc!=2)
  {
  printf("error,arguments missing or too many arguments\n");
  exit(0);
  }

  int num1=atoi(argv[1]);
  int res=fact(num1);
  printf("factorial is %d \n",res);
  exit(0);
}
