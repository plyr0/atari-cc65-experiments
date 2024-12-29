#include <stdio.h>
#include <stdint.h>
#include <atari.h>

int main()
{
    double number1 = 3.14, number2 = 2.63;
    double sum;

    sum = number1 + number2;

    printf(" Sum of the two integers: %lf\n", sum); // not working 20241229
    printf(" Sum correctness: %d\n", sum == 5.77);
    printf(" Sum incorrectness: %d\n", sum == 5);
    printf(" Sum incorrectness: %d\n", sum == 6);
    printf(" Sum incorrectness: %d\n", sum == 5.77777777777);
    printf(" Sum incorrectness: %d\n", sum == 5.77000000001);

    OS.ch = 255;
    while(OS.ch == 255)
      asm volatile("");

    return 0;
}