#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZ];
int bufp = 0;

int getch(void) {
    printf("gettch::\n");
    return (bufp > 0) ? buf[--bufp] : getchar();  // 如果bufp是1 取得就是0,  下一个空闲位置这个解释真棒
}

void ungetch(int c) {  // 把字符压回到输入中
    printf("ungetch\n");
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
    printf("buf::<%s>", buf);
}
