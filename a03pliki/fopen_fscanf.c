#include <stdio.h>
#include <conio.h>  // kbhit()

int main() {
    char c[1000];
    FILE *fptr;
    if ((fptr = fopen("hello.txt", "r")) == NULL) {
        printf("Error! File cannot be opened.");
    } else {
        fscanf(fptr, "%[^\n]", c);
        printf("Data from the file:\n%s", c);
        fclose(fptr);
    }
    while(!kbhit());
    return 0;
}