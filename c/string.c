#include <stdio.h>
#include <string.h>

int the_strlen(char* s) {
  int size = 0;
  while(*s++)
    size++;
  return size;
}

int the_strcmp(char* s1, char* s2) {
  int i = 0;
  while(s1[i + 1] && s2[i + 1]) {
    if (s1[i] != s2[i]) {
      return s1[i] - s2[i];
    }
    i++;
  }
  return 0;
}

char* the_strcpy(char* dest, char* src) {
  int i = 0;
  while (i < the_strlen(src)) {
    dest[i] = i[src];
    i++;
  }
  return dest;
}

char* the_strcat(char* dest, char* src) {
  int i = the_strlen(dest);
  int j = 0;
  while (j < the_strlen(src)) {
    dest[i++] = src[j++];
  }
  return dest;
}

char* the_strchr(char* s, int c) {
  int i = 0;
  while (i < the_strlen(s)) {
    if (s[i] == c) {
      return &s[i];
    }
    i++;
  }
  return 0;
}

char* the_strstr(char* haystack, char* needle) {
  int i = 0;
  int j = 0;
  while (i < the_strlen(haystack) - the_strlen(needle)) {
    j = 0;
    while (j < the_strlen(needle)) {
      if (haystack[i + j] == needle[j]) {
        j++;
      } else {
        break;
      }
    }
    if (j == the_strlen(needle)) {
      return &haystack[i];
    }
    i++;
  }
  return 0;
}

int main() {
  char string1[256] = "string";
  char string2[] = "turing";
  
  printf("Length of string: %d\n", the_strlen(string1));
  printf("Length of string: %lu\n", strlen(string1));
  printf("the_strcmp: %d\n", the_strcmp(string1, string2));
  printf("strcmp: %d\n", strcmp(string1, string2));

  printf("strchr: %s\n", strchr(string1, 'r'));
  printf("the_strchr: %s\n", the_strchr(string1, 'r'));

  printf("strstr: %s\n", strstr(string1, "in"));
  printf("the_strstr: %s\n", the_strstr(string1, "in"));

  return 0;
}
