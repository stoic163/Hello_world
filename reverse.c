#include<stdio.h>

void main(void)
{
  char *p = "I like Linux , I study Linux";
  char *q = NULL;
  char *m = NULL;
  int i = 0;
  int j = 0;
  
  while ( *p++ != '\0' ) {
    i++;
  }
  q = p;
  i = i + 1;
  
  while ( i > = 0 ) {
    q--;
    j++;
    if ( *q == ' ' ) {
      m = q;
      m = m + 1;
      j = j - 1;
      while ( j > 0 ) {
        printf("%c", *m++);
        j--;
      }
      printf(" ");
    }
    if ( i == 0 ) {
      m = q;
      while ( *q++ != ' ' ) {
        printf("%c", *m++);
      }
    }
    i--;
  }
  printf("\n");
}
