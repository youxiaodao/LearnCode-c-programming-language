#include <stdio.h>

#define MAXLINE 1000  /* 允许输入行的最大长度 */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* 打印输出最长的行 */
void main() {
    int len;  /* 当前行长度 */
    int max;  /* 当前最长行长度 */
    char line[MAXLINE];  /* 当前输入行 */
    char longset[MAXLINE]; /* 用于保存最长的行 */

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longset, line);
        }
    }
    if (max > 0) {
        printf("%s", longset);
    }
    return 0;
}

/* 将一行读入s中，并返回其长度 */
int getline(char s[], int lim) {
    int c,i;
    for (i=0;i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[]) {
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}
