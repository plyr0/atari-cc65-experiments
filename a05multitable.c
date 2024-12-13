#include<stdio.h>
#include <conio.h>

int main()
{
    int i,j;    
    
    printf("\n   ");
    for(i=1; i<=10; i++){
        printf("%3d", i);
    }
    printf("\n");
    
    for(i=1; i<=10; i++){
        printf("%3d", i);
        for(j=1; j<=10; j++){
            printf("%3d", i*j);
        }
        printf("\n");
    }
    getchar();
    return 0;
}