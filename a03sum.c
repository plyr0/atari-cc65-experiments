#include <stdio.h>
#include <stdint.h>

int main()
{
  int32_t number1, number2, sum;
 
  printf(" Enter two integer values \n ");
  scanf("%ld %ld", &number1, &number2);
  
  sum = number1 + number2;

  printf(" Sum of the two integer values is %ld\n", sum);
  return 0;
}