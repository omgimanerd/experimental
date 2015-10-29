#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main() {
  
  int fd1, fd2;

  fd1 = open("foo", 8);
  printf("fd1: %d\n", fd1);
  if (fd1 < 0) {
    printf("Error: %d, %s\n", errno, strerror(errno));
  }

  printf("%d   %d", O_WRONLY | O_RDONLY | O_TRUNC,
         O_WRONLY + O_RDONLY + O_TRUNC);

  char a[256] = "hi dere\n";
  write(STDOUT_FILENO, a, sizeof(a));
  
  return 0;
}
