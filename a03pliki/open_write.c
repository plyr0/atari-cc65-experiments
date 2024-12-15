#include <unistd.h> // read()
#include <fcntl.h>  // open()
#include <stdio.h>  // printf()
#include <conio.h>  // kbhit()
#include <string.h>

int main() {
    char c[1000];
    int fptr;
    unsigned len, result;

    fptr = open("hello.txt", O_WRONLY);
    if(fptr == -1){
        printf("error");
    } else {
        printf("Enter string for to write:\n");
        scanf("%[^\n]", c);
        len = strlen(c);
        result = write(fptr, c, len);
        if(result != len)
            printf("Error writing:%d/%d\n", result, len);
        close(fptr);
    }
    while(!kbhit());
    return 0;
}