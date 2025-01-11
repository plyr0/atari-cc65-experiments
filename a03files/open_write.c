#include <atari.h>
#include <unistd.h> // write()
#include <fcntl.h>  // open()
#include <stdio.h>  // printf()
#include <string.h> // strlen()

int main() {
    char c[] = "This is hello from open_write!!";
    int fptr;
    unsigned len, result;

    fptr = open("hello.txt", O_WRONLY);
    if(fptr == -1){
        printf("error");
    } else {
        len = strlen(c);
        result = write(fptr, c, len);
        if(result != len)
            printf("Error writing:%d/%d\n", result, len);
        close(fptr);
    }
    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}