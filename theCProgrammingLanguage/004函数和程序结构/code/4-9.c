// 以上介绍的getch 和ungetch 函数不能正确的处理压回的EOF, 考虑压回EOF时应该如何处理。
#include <stdio.h> 
#define BUFSIZE     100

int buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/*
    C语言不要求char变量是signed或者unsigned类型

    char类型转换为int类型的时候，转换结果不应该是一个负值

    需要把缓冲区buf声明为一个整数数组
    int buf[BUFSIZE]
    这样, 就不需要上面提到的哪些转换
    而EOF(-1)或其他负数也都能得到正确的处理
*/