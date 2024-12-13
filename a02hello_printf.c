#include <stdio.h>
#include <conio.h>

int main (void)
{
    printf("Hello, world!");
    while(!kbhit());
    return 0;
}