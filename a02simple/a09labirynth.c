#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  for(;;)
    putchar(6 + rand()%2);
  return 0;
}
