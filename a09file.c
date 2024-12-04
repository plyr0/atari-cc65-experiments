#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    char c[1000];
    int fptr;
    fptr = open("hello.txt", O_RDONLY);
    if(fptr == -1){
        printf("error");
        getchar();
        return 1;
    }

    read(fptr, c, 16);
    printf("Data from the file:\n%s", c);
    close(fptr);

    getchar();

    return 0;
}