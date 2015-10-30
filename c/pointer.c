#include <stdio.h>
#include <stdlib.h>

int main() {
  int a = 9;
  double b = 2.0;
  char c = 'e';

  int* pa = &a;
  double* pb = &b;
  char* pc = &c;

  printf("a: %d, b: %f, c: %s\n", *pa, *pb, pc);
  pa++;
  pb++;
  pc++;
  printf("a: %d, b: %f, c: %s\n", *pa, *pb, pc);
  pa--;
  printf("de-reference pa: %d\n", *pa);

  return 0;
}
