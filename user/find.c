#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

// Check if two strings are equal
int
match(char *path, char *filename)
{
  int i = 0;
  while(path[i] && filename[i]) {
    if(path[i] != filename[i])
      return 0;
    i++;
  }
  return path[i] == 0 && filename[i] == 0;
}

// The recursive search function
void
find(char *path, char *target)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  // Open directory
  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  // Get info about path
  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  // If directory, scan children
  switch(st.type){
  case T_FILE:
    // If the file matches the target name
    if(match((char*)path + strlen(path) - strlen(target), target))
      printf("%s\n", path);
    break;

  case T_DIR:
    // Prepare buffer for joining paths
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path too long\n");
      break;
    }

    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';

    // Read each directory entry
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      // Skip empty entries
      if(de.inum == 0)
        continue;

      // Skip "." and ".."
      if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;

      // Build "path/filename"
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;

      if(stat(buf, &st) < 0){
        printf("find: cannot stat %s\n", buf);
        continue;
      }

      // If filename matches, print it
      if(match(de.name, target))
        printf("%s\n", buf);

      // If it's a directory, recurse
      if(st.type == T_DIR)
        find(buf, target);
    }
    break;
  }

  close(fd);
}

// MAIN
int
main(int argc, char *argv[])
{
  if(argc != 3){
    fprintf(2, "Usage: find <directory> <filename>\n");
    exit(1);
  }

  find(argv[1], argv[2]);
  exit(0);
}
