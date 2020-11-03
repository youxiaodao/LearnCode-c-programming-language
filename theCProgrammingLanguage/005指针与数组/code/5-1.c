 // 在上面的例子中, 如果符号+ — 的后面紧跟的不是数字, 
 // getint 函数 将把 符号视为数字0的有效形式.
 // 将这种形式的 + - 符号重写回输入流

#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getint(int *pn) {
    int c, d, sign;
    while (isspace(c = getch())) {
        ;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        d = c;
        if (!isdigit(c = getch())) {
            if ( c != EOF) {
                ungetch(c);
            }
            ungetch(d);
            return d;
        }
    }
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign;
    if (c != EOF) {
        ungetch(c);
    }
    return c;
}