#include<stdio.h>

int main()
{
    int number;

    printf(" Enter an int value to check \n ");
    scanf("%d",&number);

    number%2 == 0 ? printf(" Even \n ") : printf(" Odd \n");

    return 0;
}