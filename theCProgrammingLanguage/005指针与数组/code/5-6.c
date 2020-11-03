// 采用指针而非数组索引的方式改写前面章节和练习中的某些程序
// 例如: getline atoi itoa 
// reverse
// strindex getop


// 1
#include <stdio.h>
int getline(char *s, int lim) {
    int c;
    char *t = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '/n') {
        *s++ = c;
    }
    if (c == '/n') {
        *s++ = c;
    }
    *s = '\0';
    return s - t;
}
/*
用 *s 代替 s[i] 来 引用字符数组中的元素, 还要用递增指针s的办法来遍历那个字符数组
char *t = s, 将字符数组的第一个字符的地址保存在t中
是为了在函数结束返回字符长度s - t
*/

// 2
#include <stdio.h>
int atoi(char *s) {
    int n, sign;
    for (; isspace(*s); s++) {
        ;
    }
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-') {
        s++;
    }
    for (n= 0; isdigit(*s); s++) {
        n = 10 * n + *s - '0';
    }
    return sign * n;
}


// 3
void reverse(char *);
void itoa(int n, char *s) {
    int sign;
    char *t = s;

    if ((sign = n) < 0) {
        n = -n;
    }
    do {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) {
        *s++ = '-';
    }
    *s = '\0';
    reverse(t);
}

//4
#include <string.h>
void reverse(char *s) {
    int c;
    char *t;

    for (t = s + (strlen(s) - 1); s < t; s++, t--) {
        c = *s;
        *s = *t;
        *t = c;
    }
}

// 5
int strindex(char *s, char *t) {
    char *b = s;
    char *p, *r;

    for (; *s != '\0'; s++) {
        for (p = s, r=t; *r != '\0' && *p == *r; p++, r++) {
            ;
        }
        if (* r > t && *r == '\0') {
            return s -b;
        }
    }
    return -1;
}

// 6
#include <ctype.h>
double atof(char *s) {
    double val, power;
    int sign;

    for (; isspace(*s); s++) {
        ;
    }
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-') {
        s++;
    }
    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

// 7
#include <stdio.h>
#include <ctype.h>

#define NUMBER  '0'
int getch(void);
void ungetch(int);
int getop(char *s) {
    int c;

    while ((*s = c = getch()) == ' ' || c == '\t') {
        ;
    }
    *(s+1) = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    if (isdigit(c)) {
        while (isdigit(*++s = c = getch())) {
            ;
        }
    }
    if (c == '\0') {
        while(isdigit(*++s = c = getch())) {
            ;
        }
    }
    *s = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return NUMBER ;
}
