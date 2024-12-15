#include <unistd.h> // read()
#include <fcntl.h>  // open()
#include <stdio.h>  // printf()
#include <conio.h>  // kbhit()

int main() {
    char c[1000];
    int fptr;
    fptr = open("hello.txt", O_RDONLY);
    if(fptr == -1){
        printf("error");
    } else {
        read(fptr, c, 16);
        printf("Data from the file:\n%s", c);
        close(fptr);
    }
    while(!kbhit());
    return 0;
}