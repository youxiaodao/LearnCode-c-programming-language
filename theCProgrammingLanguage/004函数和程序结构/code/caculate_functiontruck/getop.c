#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[]) {
    //printf("s[] ::%s\n", s);
    // s[] main 中定义的栈
    int i, c;
    // 检查第一位
    while ((s[0] = c = getch())  == ' ' || c == '\t')
        printf("getop::::check the first<%c>\n", c);
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {          
        printf("getop::::no digit<%c>\n", c);
        return c;       //不是数
    }
    i = 0;

    if (isdigit(c)) {       
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    printf("getop::::has number\n");
    return NUMBER;
}
