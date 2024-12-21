#include <atari.h>
#include <unistd.h> // read()
#include <fcntl.h>  // open()
#include <stdio.h>  // printf()

int main() {
    char c[1000];
    int i = 0;
    int fptr;

    fptr = open("hello.txt", O_RDONLY);
    if(fptr == -1){
        printf("error");
    } else {
        while(read(fptr, c + i, 1)) {
            ++i;
        }
        printf("Data from the file:\n%s", c);
        close(fptr);
    }
    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}