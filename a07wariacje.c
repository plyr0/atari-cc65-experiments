#include <stdio.h>
#include <stdint.h>

uint32_t doFactorial(uint32_t a) {
  uint32_t factorial, i;

  if(a==0 || a==1)
    return 1;
  
  factorial=1UL;
  for(i=1; i<=a; ++i){
    factorial *= i;
  }
  return factorial;
}

int main()
{
  uint32_t r, n, c;
  printf("Wariacje bez powtorzen V(n,r) podaj n i r:\n");
  scanf("%lu %lu", &n, &r);
  c = doFactorial(n) / doFactorial(n - r);
  printf("%lu", c);
}