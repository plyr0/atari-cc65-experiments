#include <conio.h>

int main (void)
{
    cputs("Hello, world!");
    while(!kbhit());
    return 0;
}