#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* gnu_getcwd () {
  size_t size = 100;
  while (1) {
    char *buffer = (char *) malloc (size);
    if (getcwd (buffer, size) == buffer) {
      return buffer;
    }
    free (buffer);
    if (errno != ERANGE) {
      return 0;
    }
    size *= 2;
  }
}

int main(int argc, char** argv) {
  printf("%s\n", gnu_getcwd());
  return 0;
};
