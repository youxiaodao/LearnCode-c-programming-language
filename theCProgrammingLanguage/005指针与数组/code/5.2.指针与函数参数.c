#include <ctype.h>
#include <stdio.h>  // EOF需要

#define SIZE    100
int main(int argc, char const *argv[]) {
    int n, array[SIZE], getint(int *);

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++) {
        ;
    }
    return 0;
}

int getch(void);
void ungetch(int);

int getint(int *pn) {
    int c, sign;
    while (isspace(c = getch())) {
        ;
    }
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }
    for (*pn = 0; isdigit(c);c = getch) {
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign;
    if (c != EOF) {
        ungetch(c);
    }
    return c;
}