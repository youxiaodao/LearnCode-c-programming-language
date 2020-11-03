// 另一种方法是通过getline函数读入整行输入, 这种情况下可以不使用getch与ungetch函数, 请运用这一方法修改计算器程序.
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100
#define NUMBER  '/'

int getline(char line[], int limit);

int li = 0;         // input line index
char line[MAXLINE];     // one input line

int getop(char s[]) {
    int c, i;
    if (line[li] == '\0') {
        if (getline(line, MAXLINE) == 0) {
            return EOF; 
        } else {
            li = 0;
        }
    }
    while ((s[0] = c = line[li++]) == ' ' || c == '\t') {
        ;
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    i = 0;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = line[li++])) {
            ;
        }
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = line[li++])) {
            ;
        }
    }
    s[i] = '\0';
    li--;
    return NUMBER;
}

/* 
    用 getline来取代 getch 和 ungetch

    li是line中下一个字符的索引

    再c中, 任何函数都能使用和改变另一个函数的外部变量, 

    想要阻止这种情况, 就应该把外部变量声明为static变量
    
*/