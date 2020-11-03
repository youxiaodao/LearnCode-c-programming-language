// 修改getop函数, 使其不必使用ungetch函数, 
// 提示: 可以使用一个static类型的内部变量解决该问题

#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'  // signal that a number was found

int getch(void);
int getop(char s[]) {
    int c, i;
    static int lastc = 0;

    if (lastc == 0) {
        c = getch();
    } else {
        c = lastc;
        lastc = 0;
    }
    
    while ((s[0] = c) == ' ' || c == '\t') {
        c = getch();
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    i = 0;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch())){
            ;
        }
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF) {
        lastc = c;
    }
    return NUMBER; 
}

/*
    先检查lastc中是否保存有前一个字符
    如果没有, getop将调用getch读取一个新字符
    如果有,   getop将将把这个字符复制到变量c并对变量lastc清零

    修改了第一个while循环
        先将c赋值给s, 再调用getch()
*/


