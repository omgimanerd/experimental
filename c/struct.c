#include <stdio.h>
#include <stdlib.h>

int main() {

  typedef struct {
    int i;
    char c;
  } foo;

  foo s;
  foo* t = (foo*) malloc(sizeof(foo));

  s.i = 53;
  s.c = 'w';
  (*t).i = 64; // t->a = 75;

  printf("s.i = %d, s.c = %c, t.a = %d\n", s.i, s.c, t->i);

  return 0;
}
