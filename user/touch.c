#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  if(argc==1)
  printf("creates an empty file if file does not exist , raises an error if it does"),exit(0);
  char* file_name=argv[1];
  int fd=open(file_name,0);
  if(fd>=0)
  {//file exists
  printf("error,this file %s exists",file_name);
  close(fd);
  exit(1);//returns 1 if it exists
  }
  else
  {
    fd=open(file_name,O_CREATE|O_WRONLY);//for file permission
    if(fd<=0)
    printf("cannot create file"),exit(2);
  }
  printf("file %s successfully created",file_name);
  close(fd);
  exit(0);
}
