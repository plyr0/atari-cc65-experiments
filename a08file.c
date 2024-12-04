#include <stdio.h>

int main() {
    char c[1000];
    FILE *fptr;
    if ((fptr = fopen("hello.txt", "r")) == NULL) {
        printf("Error! File cannot be opened.");
        return 1;
    }

    fscanf(fptr, "%[^\n]", c);
    printf("Data from the file:\n%s", c);
    fclose(fptr);

    getchar();

    return 0;
}