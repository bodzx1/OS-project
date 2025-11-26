#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[512];

void
wc(int fd, char *name,int mode)
{
  int i, n;
  int l, w, c, inword;
  int curr_L=0;
  int max_L=0;

  l = w = c = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){ //char count
       c++;
       curr_L++; //to keep track of longest line length
      if(buf[i] == '\n'){
       //line count
        l++;
        if(curr_L>max_L)
        {
          max_L=curr_L;
          curr_L=0;
        }
        else curr_L=0;
      }
      if(strchr(" \r\t\n\v", buf[i])) //skips white spaces and tabs
        inword = 0;
      else if(!inword){ //word count
        w++;
        inword = 1;
      }
    }
  }
  if (curr_L > 0) {
      ///last line doesnt have /n
      if (curr_L > max_L)
          max_L = curr_L;
  }
  if(n < 0){
    printf("wc: read error\n");
    exit(1);
  }
  if(mode==1)
  printf("%d ",l);
  else if (mode==2)
  printf("%d ",w);
  else if (mode==3)
  printf("%d ",c);
  else if (mode==4)
  printf("%d %d ",l,w);
  else if(mode==5)
  printf("%d %d ",w,c);
  else if(mode==6)
  printf("%d ",max_L);
  else
  printf("%d %d %d ", l, w, c);
  printf("%s",name);


  //printf("%d %d %d %s\n", l, w, c, name);

}

int
main(int argc, char *argv[])
{
  //case one already implemented wc filename
  //case two wc -l filename
  int fd, i;
  int mode=0;

  if(argc <= 1){
    wc(0, "",-1);
    exit(0);
  }
  if(argc>2)
  {
    if(strcmp(argv[1],"-l")==0) mode=1;
    else if(strcmp(argv[1],"-w")==0) mode=2;
    else if(strcmp(argv[1],"-c")==0) mode=3;
    else if(strcmp(argv[1],"-lw")==0) mode=4;
    else if(strcmp(argv[1],"-wc")==0) mode=5;
    else if(strcmp(argv[1],"-L")==0) mode=6;
    for(i = 2; i < argc; i++){
    if((fd = open(argv[i], O_RDONLY)) < 0)
    {
      printf("wc: cannot open %s\n", argv[i]);
      exit(1);
    }
    wc(fd, argv[i],mode);
    close(fd);
  }
  }
  else
  {
    for(i = 1; i < argc; i++)
    {
      if((fd = open(argv[i], O_RDONLY)) < 0)
      {
        printf("wc: cannot open %s\n", argv[i]);
        exit(1);
      }
    wc(fd, argv[i],0);
    close(fd);
  }
  }
  exit(0);
}
