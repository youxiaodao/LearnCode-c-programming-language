// 假定最多只压回一个字符, 请相应的修改getch和ungetch
#include <stdio.h>

char buf = 0;

int getch(void) {
    int c;

    if (buf != 0) {
        c = buf;
    } else {
        c = getchar();
    }
    buf = 0;
    return c;
}

void ungetch(int c) {
    if (buf != 0) {
        printf("ungetch: too many characters\n");
    } else {
        buf = c;
    }
}

/*
    buf的初值是0
    而每次getch函数在读取一个字符后,
    会再次把buf设置为0
    ungetch函数在把每一个字符重新压回输入缓冲区之前都要检查该缓冲区是否为空，
    如果缓冲区不为空，ungetch函数将会产生一条出错信息
    buf不用再是数组了，也不用bufp了
*/