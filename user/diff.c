#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
int read_line(int fd,char* line_buf) //read a single line,return line length,return 0 on eof
{
  int i=0;
  char c;
  while (i < 512 - 1 && read(fd, &c, 1) == 1)
   {
        line_buf[i++] = c;
        if (c == '\n')
            break;
   }
    line_buf[i] = '\0'; // Null-terminate the string
    return i; // Return the length of the line read

}
void
compare_files(int fd1, int fd2, char *name1, char *name2)
{
    char line1[512];
    char line2[512];
    int len1, len2;
    int line_num = 1;
    int is_identical = 1;

    while (1) {
        // Read one line from each file
        len1 = read_line(fd1, line1);
        len2 = read_line(fd2, line2);

        // Case 1: Both files reached EOF simultaneously
        if (len1 == 0 && len2 == 0) {
            break;
        }

        // Case 2: Line difference or different content
        if (len1 > 0 && len2 > 0) {
            // Compare the content of the two lines
            if (strcmp(line1, line2) != 0) {
                printf("Line %d differs:\n", line_num);
                printf("<< %s", line1); // line1 already contains '\n' or '\0'
                printf(">> %s", line2);
                is_identical = 0;
            }
        }
        // Case 3: File 1 ended, but File 2 still has lines
        else if (len1 == 0 && len2 > 0) {
            printf("Line %d only in %s:\n", line_num, name2);
            printf(">> %s", line2);
            is_identical = 0;
            // Keep printing the rest of file 2 until EOF
            while ((len2 = read_line(fd2, line2)) > 0) {
                line_num++;
                printf("Line %d only in %s:\n", line_num, name2);
                printf(">> %s", line2);
            }
            break; // Finished both files
        }
        // Case 4: File 2 ended, but File 1 still has lines
        else if (len1 > 0 && len2 == 0) {
            printf("Line %d only in %s:\n", line_num, name1);
            printf("<< %s", line1);
            is_identical = 0;
            // Keep printing the rest of file 1 until EOF
            while ((len1 = read_line(fd1, line1)) > 0) {
                line_num++;
                printf("Line %d only in %s:\n", line_num, name1);
                printf("<< %s", line1);
            }
            break; // Finished both files
        }

        line_num++;
    }

    // Example 3: Identical Files
    if (is_identical) {
        printf("Files are identical\n");
    }
}

int
main(int argc, char *argv[])
{
  int fd1,fd2;
  fd1=fd2=0;
  if(argc==1)
  {
  printf("prints the diffrences between two files");
  exit(0);
  }
  if(argc>3 || argc<3)
  {
    printf("too many arguments passed,or too few"); //if more than two files or less than two files
    exit(0);
  }
  //check if any of the files wont open
  fd1= open(argv[1], O_RDONLY);
  fd2=open(argv[2], O_RDONLY);
  if(fd1<0 || fd2<0)
  {
    printf("error opening one of the files");
    exit(1);
  }
  compare_files(fd1,fd2,argv[1],argv[2]);

  exit(0);
}
