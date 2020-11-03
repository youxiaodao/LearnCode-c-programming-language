// 模仿函数getint的实现方法, 编写一个读取浮点数的函数getfloat。
// getfloat函数的返回值应该是什么类型

#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getfloat(float *pn) {
    int c, sign;
    float power;

    while (isspace(c = getch())) {
        ;
    }

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }
    for (*pn = 0.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0;
    }
    *pn *= sign / power;
    if (c != EOF) {
        ungetch(c);
    }
    return c;
}