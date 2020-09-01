/* 将其中的连续多个空格替换为1个空格*/
#include <stdio.h>

#define NONBLANK 'a'
/* replace string of blanks with a single blank */
void main() {
    int c,lastc;

    lastc = NONBLANK;
    while ((c=getchar()) != EOF) {
        if (c != ' ' || lastc != ' ') {
            putchar(c);
        }
        lastc = c;
    }
}