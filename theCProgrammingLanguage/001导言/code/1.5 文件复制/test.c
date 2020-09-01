#include <stdio.h>

void main() {
    int c;
    while ((c = getchar())!=EOF) {
        printf("This is EOF: %d\n", EOF); 
        printf("get:%d\n", c != EOF);
    }
    
}